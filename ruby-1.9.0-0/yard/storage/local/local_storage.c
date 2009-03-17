#include "../../include/yard.h"

#include <time.h>
#include <math.h>
#include <string.h>

static const char * VM_ID_KEY = "__yard_id_counter";

static const char * VM_GLOBAL_VARIABLES = "__vm_global_variables";

// this VM's cookie
long LocalCookie = 0;
// id counter used to compose IDs
long __id_counter = 0;

// forwarded declaration of stparge routine
void __yard_local_persist_object(VALUE object, struct YardModificationResult * result);

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
  
  id_data = read_data(string_to_key(VM_ID_KEY));
 
  if (id_data.data) {
    __id_counter = *((long *)id_data.data);
    free(id_data.data);
  } 
}

/*
    Saves the global variable being given its name and ID.
 */
static void save_global_variable(char * name, struct YID id) {
  STORAGE_DATA data;
  GLOBAL_VARIABLE variable;
  
  strcpy(variable.name, name);
  variable.id = id;
  
  data.size = sizeof(GLOBAL_VARIABLE);
  data.data = &variable;
  
  append_data(string_to_key(VM_GLOBAL_VARIABLES), data);
}

/*
    Loads all the global variables it can find.
 */
static void load_global_variables() {
  STORAGE_DATA * vars = read_multi_data(string_to_key(VM_GLOBAL_VARIABLES));
  
  printf("Printing out saved vars\n");
  
  while (vars->data) {
    GLOBAL_VARIABLE * gvar = (GLOBAL_VARIABLE *)vars->data;
    printf("%s (%d / %d)\n", gvar->name, gvar->id.id, gvar->id.cookie);
    
    vars += 1;
  }
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
struct YID yard_new_identity() {
  struct YID result;
  STORAGE_DATA data;
  
  // our id generation approach is simple: be atomic and you don't have to worry about sync :)
  result.id = __id_counter++;
  result.cookie = LocalCookie;
 
  data.data = &__id_counter;
  data.size = sizeof(long);
  write_data(string_to_key(VM_ID_KEY), data);   
   
  return result;
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
    result->id_assignments->next = assignment;
  } else {
    result->id_assignments = assignment;
  }
  
  rb_ivar_foreach(object, &__yard_process_associated, (st_data_t)result);
}

/*
    Persists the given object at local storage.
    
    VALUE object: object to persist along with associated ones.
 */
struct YardModificationResult * yard_local_persist_objects(struct YardModification * modification) {
  VALUE object = modification->data;
  struct YardModificationResult * result = (struct YardModificationResult *)malloc(sizeof(struct YardModificationResult));
  result->id_assignments = NULL;
   
  // let's start saving objects from the very first one.
  __yard_local_persist_object(object, result);

  // a global symbol has been defined -- let's save it
  if (modification->operation == GV_SET) {
    save_global_variable((char *)modification->arg, RBASIC(object)->yard_id);    
  }
  
  return result; 
}