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
// whether the current VM is a master one
int __master = 1;

// forwarded declaration of storage routine
void __yard_local_persist_object(VALUE object, struct YardModificationResult * result);
// forwarded declaration of identity generator
static YID yard_new_identity();

/*
    Initializes the local cookie value, attempting to set it in such a way
    that it's unqiue across multiple VMs.
 */
static void initialize_local_cookie() {
  LocalCookie = 123;
}

int yard_local_cookie() {
  return LocalCookie; 
}

/*
    Loads neccessary system variables like global variable ID table, cookie and id counter.
 */
static void load_system_variables() {
  STORAGE_DATA * id_data;
  
  id_data = read_data(YARD_SYSTEM_SCHEMA, string_to_key(VM_ID_KEY));
 
  if (id_data->data) {
    __id_counter = *((long *)id_data->data);
    free(id_data->data);
  } 
}

/*
    Creates a new string from the data given.
    
    char * data: data for the string.
    long size: size of the string.
 */
static VALUE pchar_to_string(char * data, long size) {
  VALUE result;
  
  result = rb_str_buf_new(size);
  rb_str_buf_cat(result, data, size);
  
  return result;
}

/*
    Tests whether this is a local object.
    
    VALUE object: object to check.
 */
int is_object_local(VALUE object) {
  if (!yard_type_persistable(object) || !YARD_OBJECT_SAVED(object)) {
    return 0;
  }
  
  return (LocalCookie == YARD_ID(object).cookie);
}

/*
    Unmarshals the object from the data passed.
    
    STORAGE_DATA * data: data to instantiate object from.
 */
static VALUE instantiate_object_from_data(STORAGE_DATA * data) {  
  return rb_marshal_load(pchar_to_string(data->data, data->size));
}

/*
    Loads all the global variables it can find.
 */
static void load_global_variables() {
  struct global_entry * entry = NULL;
  VALUE value;
  STORAGE_DATA * global_variable;
  STORAGE_KEY key;
  STORAGE_PAIR * pairs = enumerate_records(YARD_GLOBAL_NAMES_SCHEMA);
  
  printf("Printing out saved vars\n");
  
  while (pairs != NULL) {
    printf("Getting %s", pairs->key.data);
    // fetch/initialize global entry for current var name
    entry = rb_global_entry(global_id(pairs->key.data));

    // fetch marshalled data for the object
    value = instantiate_object_from_data(&pairs->data);

    // update global variable entry
    rb_gvar_do_set(entry, value);
    
    pairs = pairs->next;
  }
}

/*
    Loads the object from local storage and returns the pointer to it.
    
    YID * yid: id of the object in the storage.
 */
VALUE yard_local_load_object(YID * yid) {
  STORAGE_DATA * data = read_data(YARD_OBJECT_SPACE_SCHEMA, yid_to_key(yid));
  VALUE result = instantiate_object_from_data(data);
  
  RBASIC(result)->yard_id = *yid;
  RBASIC(result)->yard_flags = YARD_SAVED_OBJECT;
  
  return result;
}

/*
    Stores the object in the local storage.
    
    VALUE object: object to store.
 */
void yard_local_store_object(VALUE object) {
  STORAGE_DATA data;
  VALUE result = rb_yard_marshal_dump(object, YARD_SHALLOW);
    
  data.size = RSTRING_LEN(result);
  data.data = RSTRING_PTR(result);
  data.flags = 0;
   
  write_data(YARD_OBJECT_SPACE_SCHEMA, yid_to_key(&RBASIC(object)->yard_id), &data, NULL);
}

/*
    Updates the passed object: if the object has been stored on this machine,
    just rewrites it. It the object came from some remote VM, sends the notification to that VM.
    If the object has not been stored before, stores it immediately.
 */
void yard_update_target_object(VALUE object) {
  // todo: what about extended objects (like Fixnum with ivars or so?)
  if (!yard_type_persistable(object)) {
    return;
  }
  
  if (!YARD_OBJECT_SAVED(object)) {
    RBASIC(object)->yard_id = yard_new_identity();
    RBASIC(object)->yard_flags |= YARD_SAVED_OBJECT;
  }
 
  if (is_object_local(object)) {
    yard_local_store_object(object);  
  }  
}

/*
    Saves the reference from global variable to the object given.
    
    char * name: name of the global variable to affect.
    VALUE object: object to assign.
 */
static void __local_assign_to_global_variable(char * name, VALUE object) {
  STORAGE_DATA data;
  
  VALUE result = rb_yard_marshal_dump(object, YARD_REF_ONLY);
  data.size = RSTRING_LEN(result);
  data.data = RSTRING_PTR(result);
  data.flags = 0;
  
  write_data(YARD_GLOBAL_NAMES_SCHEMA, string_to_key(name), &data, NULL);
}


/*
    Saves the reference from global variable to the object given.
    
    char * name: name of the global variable to affect.
    VALUE object: object to assign.
 */
static void assign_to_global_variable(char * name, VALUE object) {
  if (__master) {
    __local_assign_to_global_variable(name, object);     
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
static YID yard_new_identity() {
  YID result;
  STORAGE_DATA data;
  
  // our id generation approach is simple: be atomic and you don't have to worry about sync :)
  result.id = __id_counter++;
  result.cookie = LocalCookie;
 
  data.data = &__id_counter;
  data.size = sizeof(long);
  data.flags = 0;
  
  write_data(YARD_SYSTEM_SCHEMA, string_to_key(VM_ID_KEY), &data, NULL);   
   
  return result;
}

/*
    Is used to walk the Hash structure and persist everything it can found.
    
    VALUE key: key element, probably persistable.
    VALUE value: value elemement, probably persistable.
    YARD_MODIFICATION_RESULT * result: our "logger" structure.
 */
static int __hash_persister(VALUE key, VALUE value, YARD_MODIFICATION_RESULT * result) {
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
    YARD_MODIFICATION_RESULT * result: result with id map to be replayed on source VM.
 */
void __yard_local_persist_object(VALUE object, YARD_MODIFICATION_RESULT * result) {
  YARD_ID_ASSIGNMENT * assignment = NULL;
  int i = 0;
  
  // nop in case of scalar type
  if (!yard_type_persistable(object)) {
    return;  
  }
  
  // allocate a new identity assignemnt token
  assignment = (YARD_ID_ASSIGNMENT *)malloc(sizeof(YARD_ID_ASSIGNMENT));
  
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
  
  // finally, store the object itself
  yard_local_store_object(object);
}

/*
    Persists the given object at local storage.
    
    YARD_MODIFICATION * modification: what modification to perform.
 */
YARD_MODIFICATION_RESULT * yard_local_persist_objects(YARD_MODIFICATION * modification) {
  VALUE object = modification->data;
  YARD_MODIFICATION_RESULT * result = (YARD_MODIFICATION_RESULT *)malloc(sizeof(YARD_MODIFICATION_RESULT));
 
  result->id_assignments = NULL;
    
  // let's start saving objects from the very first one.
  __yard_local_persist_object(object, result);
 
  // a global variable has been assigned a value
  if (modification->operation == YARD_GV_SET) {
    assign_to_global_variable((char *)modification->arg, object);
  } 
  
  if (modification->object != NULL) {
    yard_update_target_object(modification->object);
  }
   
  return result; 
}