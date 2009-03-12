#include "../include/yard.h"

/*
    Checks whether the object has been saved or not.
    It also considers the type of the object, keeping in mind we never mark
    strings and numbers as stored objects.
      
    VALUE object: object to check.
 */
VALUE rb_yard_saved_object(VALUE object) {
  if (!yard_type_persistable(object)) {
    return Qfalse;
  } 
   
  return (RBASIC(object)->yard_flags && YARD_SAVED_OBJECT) ? Qtrue : Qfalse;  
}

/*
    Returns a YARD id assigned to this object.
      
    VALUE object: object to get id from.
 */
VALUE rb_yard_id(VALUE object) {
  return INT2NUM(RBASIC(object)->yard_id.id);  
}

/*
    Handles object modification, storing the value passed if the object is yarded.
      
    VALUE obj: object being modified. Set to NULL in case of ObjectSpace.
    VALUE val: new value (assignment, push etc).
    int op: operation being performed.
    VALUE arg: modfying operation argument.
 */
void yard_object_modification(VALUE obj, VALUE val, enum yard_modification_ops op, VALUE arg) {
  struct YardModification modification;
  
  // nop in case of suspended yard
  if (!__yard_started) {
    return;
  }
  
  // nop in case of non-persistent object
  if (obj != NULL && !YARD_OBJECT_SAVED(obj)) {
    return;
  }
  
  modification.object = obj;
  modification.data = val;
  modification.arg = arg;
  modification.operation = op;
  
  yard_apply_modification(&modification);
}

