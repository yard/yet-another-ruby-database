#include "../../include/yard.h"

static YARD_SAFE_OP_QUEUE queue;

static THREAD_LOCK manager_lock;
static THREAD manager_thread;

/*
    Enqueues the modification in a safe manner, taking care of locking/unlocking the queue.
    
    YARD_SAFE_OP_QUEUE * queue: queue to append element to.
    YARD_MODIFICATION * modification: modification to enqueue.
*/
void yard_enqueue_modification(YARD_SAFE_OP_QUEUE * queue, YARD_MODIFICATION * modification) {
  YARD_SAFE_OP_QUEUE_ITEM * element = NULL;
  
  yard_thread_lock_start(&queue->lock); 
  
  element = queue->first;
  // in case of object modification
  if (modification->operation == YARD_OBJECT_MODIFICATION) {
    while (element != NULL) {
      if ((element->data->operation == YARD_OBJECT_MODIFICATION) && 
          (modification->object == element->data->object)) {
            // don't care about replacement, we will serialize the object anyways
            break;
          }
      element = element->next;
    }
  }
  
  // in case of gvar setting
  if (modification->operation == YARD_GV_SET) {
    while (element != NULL) {
      if ((element->data->operation == YARD_GV_SET) && 
          (strcmp(element->data->arg, modification->arg) == 0)) {
            // we need the most recent version, huh?
            element->data = modification;
            break;
          }
      element = element->next;
    }
  }
  
  if (element != NULL) {
    printf("nop!\n");
  }
  
  
  if (element == NULL) {
    element = (YARD_SAFE_OP_QUEUE_ITEM *)malloc(sizeof(YARD_SAFE_OP_QUEUE_ITEM));
  
    element->data = modification;
    element->next = NULL;
  
    if (queue->last == NULL) {
      queue->last = element;
      queue->first = element;
    } else {
      queue->last->next = element;
      queue->last = element;
    }
  }
  
  yard_thread_lock_end(&queue->lock);
}

void yard_enqueue_single_modification(YARD_MODIFICATION * modification) {
  yard_enqueue_modification(&queue, modification); 
}

/*
    Pops one pending modification from the queue.
*/
YARD_MODIFICATION * yard_dequeue_modification(YARD_SAFE_OP_QUEUE * queue) {
  YARD_SAFE_OP_QUEUE_ITEM * element = NULL;
  YARD_MODIFICATION * result = NULL;
  
  // do we have to acquire sync object in case the queue is empty?
  // obviously we don't, and this case is about 99.99999% of all the cases happening.  
  if (queue->first == NULL) {
    return NULL;
  }
  
  yard_thread_lock_start(&queue->lock); 
  
  if (queue->first != NULL) {
    element = queue->first;
    queue->first = queue->first->next;
  }
  
  if (queue->first == NULL) {
    queue->last = NULL;
  }
  
  yard_thread_lock_end(&queue->lock);
  
  if (element != NULL) {
    result = element->data;
    //free(element);
  }
  
  return result;
}

/*
    This function takes care of extracting another piece of modification from the queue
    and applying it.
    
    void * data: thread param.
*/
void manager_work_function(void * data) {
  while (1) {
    YARD_MODIFICATION * item = yard_dequeue_modification(&queue);
    
    if (item != NULL) {  
      // we are trying to emulate posix threads' cancel points
      
      // try to obtain the lock;
      // if someone wants to pause the thread, he just tries to obtain the lock
      yard_thread_lock_start(&manager_lock);
      
      // perform all the stuff
      yard_apply_modification_sync(item);  
      
      // release the lock
      yard_thread_lock_end(&manager_lock);
    }    
    
    yard_thread_sleep(1);
  }
}


/*
    Initializes the storage worker thread.
*/
void yard_start_storage_worker() {
  manager_thread = yard_create_thread(0, manager_work_function, 0);
}

/*
    Resumes the paused worker thread.
*/
void yard_resume_storage_worker() {
  yard_thread_lock_end(&manager_lock);
}

/*
    Puases the worker thread.
    
    Takes care of interrupting the thread at a control point (pthread cancel points
    would work there well, but ...) using thread locks.
*/
void yard_pause_storage_worker() {
  yard_thread_lock_start(&manager_lock);
}

void yard_initialize_safe_op_queue(YARD_SAFE_OP_QUEUE * queue) {
  queue->first = queue->last = NULL;
  yard_create_thread_lock(&queue->lock);
}

void yard_init_storage_worker() {
  yard_initialize_safe_op_queue(&queue);
  
  yard_create_thread_lock(&manager_lock);

  yard_start_storage_worker();
}

