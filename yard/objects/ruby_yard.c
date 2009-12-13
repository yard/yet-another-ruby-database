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
    Fetches a YARD object being given its id and cookie.
*/
VALUE rb_yard_fetch(VALUE id, VALUE cookie) {
  YID * yid = (YID *)malloc(sizeof(YID));
  
  yid->id = NUM2INT(id);
  yid->cookie = NUM2INT(cookie);
  
  return yard_get_object_by_yid(yid);
}

/*
    Configures the server and clients being provided an array of settings.
    The format is as follows:
    
      [[cookie, db_path], [is_master, cookie, host, port], [is_master, cookie, host, port], ...]
*/
VALUE rb_yard_configure(VALUE obj, VALUE settings) {
  VALUE local_settings = 0;
  YARD_VM_CONNECTION_SETTINGS * connection_settings = 0;
  int count = 0;
  int i = 0, cookie = 0, am_i_master = 0;
  char * host = 0;
  
  local_settings = rb_ary_entry(settings, 0);   
  
  cookie = NUM2INT(rb_ary_entry(local_settings, 0));            
  count = (RARRAY_LEN(settings) - 1);
  
  connection_settings = (YARD_VM_CONNECTION_SETTINGS *)malloc(sizeof(YARD_VM_CONNECTION_SETTINGS) * count);                              
                
  for(i = 0; i < count; i++) {
    local_settings = rb_ary_entry(settings, i + 1);
    
    connection_settings[i].master = rb_ary_entry(local_settings, 0) == Qtrue;  
    connection_settings[i].cookie = NUM2INT(rb_ary_entry(local_settings, 1));  
    
    am_i_master |= (cookie == connection_settings[i].cookie) && connection_settings[i].master;
    
    host = RSTRING_PTR(rb_ary_entry(local_settings, 2));
    memcpy(connection_settings[i].host, host, strlen(host) + 1);
    connection_settings[i].port = NUM2INT(rb_ary_entry(local_settings, 3));  
  }
  
  yard_net_configure(connection_settings, count);
    
  local_settings = rb_ary_entry(settings, 0);   
  
  yard_setup_storage_settings(cookie,
                              am_i_master,
                              RSTRING_PTR(rb_ary_entry(local_settings, 1)),
							  RSTRING_PTR(rb_ary_entry(local_settings, 2)));
                              
  return settings;
}

/*
    Handles object modification, storing the value passed if the object is yarded.
      
    VALUE obj: object being modified. Set to NULL in case of ObjectSpace.
    VALUE val: new value (assignment, push etc).
    int op: operation being performed.
    VALUE arg: modfying operation argument.
 */
void yard_object_modification(VALUE obj, VALUE val, enum yard_modification_ops op, VALUE arg) {
  YARD_MODIFICATION * modification = NULL;
  
  // nop in case of suspended yard
  if (!__yard_started) {
    return;
  }

  // nop in case of non-persistent object (but not global variable definition)
  if ((obj != NULL) && !YARD_OBJECT_SAVED(obj)) {
    return;
  }
  
  modification = malloc(sizeof(YARD_MODIFICATION));
  
  modification->object = obj;
  modification->data = val;
  modification->arg = arg;
  modification->operation = op;
  
  yard_apply_modification(modification);
}

