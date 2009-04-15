#ifndef _TXN_H_
#define _TXH_H 1


typedef struct __yard_transaction YARD_TRANSACTION;

struct __yard_transaction {
  long id;
  long flags;
  
  YARD_SAFE_OP_QUEUE queue;
    
  YARD_TRANSACTION * parent;
};

/*  
    Starts a new YARD transaction and makes it current for
    the current context.
*/
VALUE rb_yard_begin_transaction(VALUE obj);

/*
    Commits the current YARD transaction
*/
VALUE rb_yard_commit_transaction(VALUE obj);

/*
    Aborts the current YARD transaction.
*/
VALUE rb_yard_abort_transaction(VALUE obj);

/*
    Sets a new txn and makes it current for the calling thread.
*/
YARD_TRANSACTION * yard_push_transaction();

/*  
    Pops a transaction for the current thread, if any.
*/
YARD_TRANSACTION * yard_pop_transaction();

/*  
    Fetches a transaction for the current thread, if any.
    Works pretty much the same as pop, but doesn't remove txn from the stack.
*/
YARD_TRANSACTION * yard_fetch_transaction();

/*
    Prepares all the neccessary variables and methods for working with TXNs.
*/
void initialize_transaction_system();

/*
    Add the moditication marker to transaction.
*/
void yard_txn_enqueue_modification(YARD_TRANSACTION *, YARD_MODIFICATION *);

#endif