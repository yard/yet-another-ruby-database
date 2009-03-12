/**********************************************************************

  thread_pthread.h -

  $Author: ko1 $
  $Date: 2007-12-25 13:35:17 +0900 (Tue, 25 Dec 2007) $

  Copyright (C) 2004-2007 Koichi Sasada

**********************************************************************/

#ifndef THREAD_PTHREAD_H_INCLUDED
#define THREAD_PTHREAD_H_INCLUDED

#include <pthread.h>
typedef pthread_t rb_thread_id_t;
typedef pthread_mutex_t rb_thread_lock_t;
typedef pthread_cond_t rb_thread_cond_t;

typedef struct native_thread_data_struct {
    void *signal_thread_list;
    pthread_cond_t sleep_cond;
} native_thread_data_t;

#endif /* THREAD_PTHREAD_H_INCLUDED */
