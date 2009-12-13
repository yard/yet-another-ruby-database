#ifndef _THREADS_H_
#define _THREADS_H_

typedef void (*YardThreadFunction)(void *);

#if defined(_WIN32)
#include "../threads/win32_threads.h"
#endif

/*
    Spawns a new thread being given a thread function to be used.
*/
THREAD yard_create_thread(int, YardThreadFunction, void *);

/*
    Initializes a lightweight lock entity.
*/
void yard_create_thread_lock(THREAD_LOCK *);

/*
    Attempts to acquire lightweight lock.
*/
void yard_thread_lock_start(THREAD_LOCK *);

/*
    Attempts to release lightweight lock.
*/
void yard_thread_lock_end(THREAD_LOCK *);

/*
    Gets this thread to sleep for some time.
*/
void yard_thread_sleep(int);

/*
    Returns the current thread.
*/
THREAD yard_get_current_thread();

#endif
