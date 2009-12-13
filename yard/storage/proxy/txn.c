#include "../../include/yard.h"

// lock for safe txn updates
static THREAD_LOCK txn_push_lock;

static st_table * thread_transaction_map = NULL;

/*
    Sets a new txn and makes it current for the calling thread.
*/
YARD_TRANSACTION * yard_push_transaction() {
  // hope it's really atomic
  YARD_TRANSACTION * txn = malloc(sizeof(YARD_TRANSACTION));
  YARD_TRANSACTION * top_txn = NULL;
  VALUE ruby_thread = rb_thread_current();
  
  // prepare transaction queue
  yard_initialize_safe_op_queue(&txn->queue);
  
  // lock everything here
  yard_thread_lock_start(&txn_push_lock);
  
  // try to fetch the current thread txn
  st_lookup(thread_transaction_map, ruby_thread, &top_txn);
  
  // if found anything, form a stack structure: the new references the old
  if (top_txn != NULL) {
    txn->parent = top_txn;
  }
  
  // in anycase, add the new as the current of the thread
  st_add_direct(thread_transaction_map, ruby_thread, txn);
  
  // unlock everybody
  yard_thread_lock_end(&txn_push_lock);
  
  return txn;      
}

/*  
    Pops a transaction for the current thread, if any.
*/
YARD_TRANSACTION * yard_pop_transaction() {
  YARD_TRANSACTION * result = NULL;
  VALUE ruby_thread = rb_thread_current();
  
  yard_thread_lock_start(&txn_push_lock);
  
  st_lookup(thread_transaction_map, ruby_thread, &result);
  
  if (result != NULL) {
    st_add_direct(thread_transaction_map, ruby_thread, result->parent);
  }
  
  yard_thread_lock_end(&txn_push_lock);
  
  return result;
}
  
/*
    Adds the given modification to the transaction modification queue,
    unless the object has already been mentioned there.
    
    YARD_TRANSACTION * txn: transaction to append changes to.
    YARD_MODIFICATION * modification: modification to apply.
*/
void yard_txn_enqueue_modification(YARD_TRANSACTION * txn, YARD_MODIFICATION * modification) {
  yard_enqueue_modification(&txn->queue, modification);    
}

/*
    Attempts to get the current stack-top transaction for the current thread.
*/      
YARD_TRANSACTION * yard_fetch_transaction() {
  YARD_TRANSACTION * result = NULL;
  VALUE ruby_thread = rb_thread_current();
  
  st_lookup(thread_transaction_map, ruby_thread, &result);
  
  return result;    
}


/*  
    Starts a new YARD transaction and makes it current for
    the current context.
*/
VALUE rb_yard_begin_transaction(VALUE obj) {
  yard_push_transaction();      
  
  return Qtrue;     
}

/*
    Commits the current YARD transaction
*/
VALUE rb_yard_commit_transaction(VALUE obj) {
  YARD_TRANSACTION * txn = yard_pop_transaction();
  YARD_MODIFICATION * item = NULL;
  
  // if no transaction has been fetched, just exit
  if (txn == NULL) {
    return;
  }    
  
  yard_pause_storage_worker();
  
  item = yard_dequeue_modification(&txn->queue);
    
  while (item != NULL) {
      // perform all the stuff
      yard_apply_modification_sync(item);  
      item = yard_dequeue_modification(&txn->queue);
  }     
  
  yard_resume_storage_worker();
  
  return Qtrue;
}

/*
    Aborts the current YARD transaction.
*/
VALUE rb_yard_abort_transaction(VALUE obj) {
  YARD_TRANSACTION * txn = yard_pop_transaction();
  YARD_MODIFICATION * item = NULL;
  
  if (txn == NULL) {
    return Qfalse;
  }
  
  item = yard_dequeue_modification(&txn->queue);
  
  while (item != NULL) {
    yard_revert_object_sync(item->object, item->arg);
    
    item = yard_dequeue_modification(&txn->queue);    
  }
}

/*
    Initializes txn subsystem. Used to setup locks, 
    identity counters etc.
*/
void initialize_transaction_system() {
  yard_create_thread_lock(&txn_push_lock);
  thread_transaction_map = st_init_numtable();
}