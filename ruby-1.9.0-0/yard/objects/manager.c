#include "../include/yard.h"

int __yard_started = 0;

/*
  Checks if the passed object should be saved separately.
      
  VALUE object: object to check.
 */
int yard_type_persistable(VALUE object) {
  enum ruby_value_type object_type = TYPE(object);
  
  if (object_type == RUBY_T_FLOAT ||
      object_type == RUBY_T_STRING ||
      object_type == RUBY_T_BIGNUM ||
      object_type == RUBY_T_STRING ||
      object_type == RUBY_T_SYMBOL ||
      object_type == RUBY_T_TRUE ||
      object_type == RUBY_T_NIL ||
      object_type == RUBY_T_CLASS ||
      object_type == RUBY_T_MODULE ||
      object_type == RUBY_T_FALSE ||
      object_type == RUBY_T_FIXNUM) {
    return 0;
  }
  
  return 1;
}

/*
    Starts up the YARD engine. It sets global flag __yard_started,
    should also initialize storage (if attached), networking, preload
    all the objects.
      
 */
void launch_yard() {
  // launch local storage engine
  initialize_local_storage("default.db");
  // mark the yard engine as started
  __yard_started = 1;
}