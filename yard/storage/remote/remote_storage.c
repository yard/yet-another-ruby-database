#include "../../include/yard.h"

/*
    Performs a request to save and assign to a global variable.  
*/
void yard_remote_assign_to_global_variable(char * name, VALUE object) {
  char * message = NULL;
  VALUE marshaled = rb_yard_marshal_dump(object, YARD_SHALLOW);
  
  int size = strlen(name) + 1 + RSTRING_LEN(marshaled);        
  
  message = (char *)malloc(size);
  memcpy(message, name, strlen(name) + 1);
  memcpy(message + strlen(name) + 1, RSTRING_PTR(marshaled), RSTRING_LEN(marshaled));
  
  yard_net_send_message(message, size, yard_master_cookie(), strlen(name), 0, YARD_NET_DEFINE_GLOBAL_VARIABLE, 0);
}

/*
    Fetches the object from some remote machine and returns it as the result.
    
    YID * id: id of the object to fetch.
*/
VALUE yard_remote_fetch_object(YID * id) {
  YARD_NET_MESSAGE * message = yard_net_send_message(id, sizeof(YID), id->cookie, 0, 0, YARD_NET_FETCH_OBJECT, YARD_NET_BLOCKING);
  
  if (message->operation == YARD_NET_FETCH_OBJECT_SUCCESS) {
    return rb_marshal_load(pchar_to_string(message->data, message->size));
  }
}
