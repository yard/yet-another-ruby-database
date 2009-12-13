#include "../../include/yard.h"

YardStoreMethod yard_storage_method = NULL;

/*
    Being given a nicely prepared structure, applies ID updates to the object graph.
 
    struct YardModificationResult * replay: what to replay
 */
void replay_modification_result(YARD_MODIFICATION * replay) {
      
}

/*  
    Just stores the modification in the queue "to-be-executed-when-you-have-time".
    
    YARD_MODIFICATION * modification: modification to execute.
*/
void yard_apply_modification(YARD_MODIFICATION * modification) {
  // try to fetch current transaction
  YARD_TRANSACTION * txn = yard_fetch_transaction();
  
  // if any...
  if (txn) {
    // put all the changes into txn queue
    yard_txn_enqueue_modification(txn, modification);  
  } else {
    // otherwise, just add to the global queue
    yard_enqueue_single_modification(modification);  
  }
}

/*
    Reverts the object to the last remembered state.
    
    VALUE object: object to revert.
*/
void yard_revert_object_sync(VALUE object, char * gvar_name) {
  VALUE result = 0;
  struct global_entry * entry = NULL;
  
  if (object == NULL && gvar_name != NULL) {
    result = yard_fetch_global_variable(gvar_name, 0);
    entry = rb_global_entry(global_id(gvar_name));
    rb_gvar_do_set(entry, result);
  }
  
  if (YARD_OBJECT_SAVED(object)) {
    result = yard_fetch_stored_object(&YARD_ID(object), 0);
    yard_set_object_by_yid(&YARD_ID(object), result);
    
    RBASIC(object)->yard_flags = YARD_OBJECT_STUB;
    
    yard_resolve_stub(object);
  }
}

/*
    Being given a specially filled structure, invokes neccessary callbacks to store and
    update the objects.
    
    YardModification * modification: modification to perform.
 */
void yard_apply_modification_sync(YARD_MODIFICATION * modification) {
  YARD_MODIFICATION * replay = yard_storage_method(modification);
  
  replay_modification_result(replay);
  
  free(replay);   
}

/*
    Fetches the object from some storage being given its identity.
    
    struct YID * yid: id of the object to fetch.
    int flags: flags to apply.
 */
VALUE yard_fetch_stored_object(YID * yid, int flags) {
  int local_cookie = yard_local_cookie();
  
  if (yid->cookie == local_cookie) {
    // the object seems to be stored locally  
      return yard_local_load_object(yid);
  } else {
    // the object is on some remote machine  
    
  }
}

/*
    Fetches the global variable being given its name.
    
    char * name: Name of the variable to fetch.
    int flags: Depth and other auxilary flags.
*/
VALUE yard_fetch_global_variable(char * name, int flags) {
  if (yard_master()) {
    // we hold all the gvarss
    return yard_local_load_global_variable(name);
  } else {
    // have to fetch over the network   
  }
}

/*
    Processes the messsages from remote clients.

    YARD_NET_MESSAGE * message: message to process.
*/
void yard_network_dispatcher(YARD_NET_MESSAGE * message) {
  switch (message->operation) {
    case YARD_NET_DEFINE_GLOBAL_VARIABLE:
      yard_net_dispatch_global_variable_definition(message);                  
      break;
    case YARD_NET_FETCH_OBJECT:
      yard_net_dispatch_object_fetch(message);                  
      break;
  } 
}

void yard_net_initialize_network_dispatcher() {
  yard_net_on_data = &yard_network_dispatcher;
}