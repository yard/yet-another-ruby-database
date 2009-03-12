#include "../../include/yard.h"
#include "../../include/db.h"


// this VM's cookie
long LocalCookie = 0;
// id counter used to compose IDs
long __id_counter = 0;

void __yard_local_persist_object(VALUE object, struct YardModificationResult * result);


DB * db;

void initialize_storage() {
  db_create(&db, NULL, 0);
  db->open(db, NULL, "my_db.db", NULL, DB_BTREE, DB_CREATE, 0);
}

/*
    Generates a new identity.
 */
struct YID yard_new_identity() {
  struct YID result;
  // our id generation approach is simple: be atomic and you don't have to worry about sync :)
  result.id = __id_counter++;
  result.cookie = LocalCookie;
  
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
  
  return result; 
}