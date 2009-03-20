#include "../../include/yard.h"
#include "ruby/variable.h"

#include <time.h>
#include <math.h>
#include <string.h>

static const char * VM_ID_KEY = "__yard_id_counter";

static const char * VM_GLOBAL_VARIABLES = "__vm_global_variables";

// this VM's cookie
long LocalCookie = 0;
// id counter used to compose IDs
long __id_counter = 1;

// forwarded declaration of storage routine
void __yard_local_persist_object(VALUE object, struct YardModificationResult * result);
// forwarded declaration of identity generator
static struct YID yard_new_identity();

/*
    Initializes the local cookie value, attempting to set it in such a way
    that it's unqiue across multiple VMs.
 */
static void initialize_local_cookie() {
  LocalCookie = 0;
}

/*
    Loads neccessary system variables like global variable ID table, cookie and id counter.
 */
static void load_system_variables() {
  STORAGE_DATA id_data;
  
  id_data = read_data(YARD_SYSTEM_SCHEMA, string_to_key(VM_ID_KEY));
 
  if (id_data.data) {
    __id_counter = *((long *)id_data.data);
    free(id_data.data);
  } 
}

/*
    Saves the global variable being given its name and ID.

	  char * name: Name of the variable to define.
 */
static void define_global_variable(char * name) {
  STORAGE_DATA data;
  GLOBAL_VARIABLE variable;
  STORAGE_TRANSACTION * txn = NULL;
}

/*
    Loads all the global variables it can find.
 */
static void load_global_variables() {
  STORAGE_DATA * vars = NULL;
  struct global_entry * entry = NULL;
  STORAGE_DATA ref;
  
  printf("Printing out saved vars\n");
  
  while (vars && vars->data) {
    GLOBAL_VARIABLE * gvar = (GLOBAL_VARIABLE *)vars->data;
    
    entry = rb_global_entry(gvar->name);

    // next variable
    vars++;
  }
}

/*
    Saves the reference from global variable to the object given.
    
    char * name: name of the global variable to affect.
    VALUE object: object to assign.
 */
static void assign_to_global_variable(char * name, VALUE object) {
  STORAGE_DATA data;
}

/*
    Initiales the local storage taking care of setting a proper DB control,
    updating default storage strategy and loading neccessary information.
    
    char * db_file_name: name of the DB file to create/load.   
*/
void initialize_local_storage(char * db_file_name) {
  // set storage strategy
  yard_storage_method = &yard_local_persist_objects;
  start_storage();
  load_system_variables();
  load_global_variables();
}

/*
    Generates a new identity.
 */
static struct YID yard_new_identity() {
  struct YID result;
  STORAGE_DATA data;
  
  // our id generation approach is simple: be atomic and you don't have to worry about sync :)
  result.id = __id_counter++;
  result.cookie = LocalCookie;
 
  data.data = &__id_counter;
  data.size = sizeof(long);
  write_data(YARD_SYSTEM_SCHEMA, string_to_key(VM_ID_KEY), data, NULL);   
   
  return result;
}

/*
    Is used to walk the Hash structure and persist everything it can found.
    
    VALUE key: key element, probably persistable.
    VALUE value: value elemement, probably persistable.
    struct YardModificationResult * result: our "logger" structure.
 */
static int __hash_persister(VALUE key, VALUE value, struct YardModificationResult * result) {
  // just save key
  __yard_local_persist_object(key, result);  
  // and value
  __yard_local_persist_object(value, result);
  
  // move to the next pair
  return ST_CONTINUE;
}

/*
    Just an iterator routine which walks the instance variable list and saves everything it finds.
    
    ID iv_name: instance variable's name.
    VALUE val: value of the variable.
    st_data_t arg: auxilary argument.
*/
int __yard_process_associated(ID iv_name, VALUE val, st_data_t arg) {
  __yard_local_persist_object(val, (struct YardModificationResult *)arg);
  
  return 0;
}

/*
    Stores a given object tracking the history of id assignemnts to be replayed.
    
    VALUE object: object to save
    struct YardModificationResult * result: result with id map to be replayed on source VM.
 */
void __yard_local_persist_object(VALUE object, struct YardModificationResult * result) {
  struct YardIdAssignment * assignment = NULL;
  int i = 0;
  
  // nop in case of scalar type
  if (!yard_type_persistable(object)) {
    return;  
  }
  
  // allocate a new identity assignemnt token
  assignment = (struct YardIdAssignment *)malloc(sizeof(struct YardIdAssignment));
  
  RBASIC(object)->yard_id = yard_new_identity();
  RBASIC(object)->yard_flags = YARD_SAVED_OBJECT;
  
  // update identity assignment token
  assignment->src_object_id = RBASIC(object)->src_object_id ? RBASIC(object)->src_object_id : object;
  assignment->yard_id = RBASIC(object)->yard_id;
    
  // attach identity assignment token to the end of linked list
  if (result->id_assignments != NULL) {
    assignment->next = result->id_assignments;
  } 
  
  result->id_assignments = assignment;
  
  rb_ivar_foreach(object, &__yard_process_associated, (st_data_t)result);
  
  // if the object is an Array, we have to save all its elements as well
  if (BUILTIN_TYPE(object) == RUBY_T_ARRAY) {
    for(i = 0; i < RARRAY_LEN(object); i++) {
      // perform save for every element
      __yard_local_persist_object(RARRAY_PTR(object)[i], result);  
    }
  }
  
  // if the object is an Hash, we have to save all its keys and values
  if (BUILTIN_TYPE(object) == RUBY_T_HASH) {
    st_foreach(RHASH_TBL(object), &__hash_persister, result);
  }
}

/*
    Persists the given object at local storage.
    
    VALUE object: object to persist along with associated ones.
 */
struct YardModificationResult * yard_local_persist_objects(struct YardModification * modification) {
  VALUE object = modification->data;
  struct YardModificationResult * result = (struct YardModificationResult *)malloc(sizeof(struct YardModificationResult));
 
  result->id_assignments = NULL;
   
  // a global symbol has been defined -- let's try to define it
  if (modification->operation == YARD_GV_SET) {
    define_global_variable((char *)modification->arg);    
  }

  // let's start saving objects from the very first one.
  __yard_local_persist_object(object, result);
 
  // a global variable has been assigned a value
  if (modification->operation == YARD_GV_SET) {
    assign_to_global_variable((char *)modification->arg, object);
  } 
   
  return result; 
}