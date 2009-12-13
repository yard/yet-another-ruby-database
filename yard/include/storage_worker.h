#ifndef _STORAGE_WORKER_H_
#define _STORAGE_WORKER_H_

#include "../../vm_core.h"
#include "../../vm.h"

struct __safe_op_queue_item {
  YARD_MODIFICATION * data;
  struct __safe_op_queue_item * next;
};

typedef struct __safe_op_queue_item YARD_SAFE_OP_QUEUE_ITEM;

struct __safe_op_queue {
  YARD_SAFE_OP_QUEUE_ITEM * first;
  YARD_SAFE_OP_QUEUE_ITEM * last; 
  
  THREAD_LOCK lock; 
};

typedef struct __safe_op_queue YARD_SAFE_OP_QUEUE;

/*
    Initializes the passed queue object.
*/
void yard_initialize_safe_op_queue(YARD_SAFE_OP_QUEUE *);

/*
    Pushes the given modification structure to the end of main modification queue.
*/
void yard_enqueue_single_modification(YARD_MODIFICATION *);

/*
    Pushes the given modification structure to the end of given modification queue.
*/
void yard_enqueue_modification(YARD_SAFE_OP_QUEUE *, YARD_MODIFICATION *);

/*
    Pops the modification element from the first element of the queue.
*/
YARD_MODIFICATION * yard_dequeue_modification(YARD_SAFE_OP_QUEUE *);

/*
    Initializes the storage worker thread.
*/
void yard_start_storage_worker();

/*
    Resumes the paused worker thread.
*/
void yard_resume_storage_worker();

/*
    Puases the worker thread.
*/
void yard_pause_storage_worker();

/*
    Initializes manager thread, queue, locks etc.
*/
void yard_init_storage_worker();


#endif
