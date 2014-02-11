#ifndef __UTHREAD_H__
#define __UTHREAD_H__

#include "base.h"

#if !defined DEF_VAL
#	if defined __cplusplus
#		define DEF_VAL( X ) = X
#	else 
#		define DEF_VAL( X )
#	endif // __cplusplus
#endif //DEF_VAL

#if defined __cplusplus
extern "C" {
#endif // __cplusplus


#define THR_DEFAULT_FLAGS  THR_NEW_LWP | THR_JOINABLE

typedef void *(*thr_func_t)(void *);

/**
 * Thread Flags:
 * THR_CANCEL_DISABLE, THR_CANCEL_ENABLE, THR_CANCEL_DEFERRED,
 * THR_CANCEL_ASYNCHRONOUS, THR_BOUND, THR_NEW_LWP, THR_DETACHED,
 * THR_SUSPENDED, THR_DAEMON, THR_JOINABLE, THR_SCHED_FIFO,
 * THR_SCHED_RR, THR_SCHED_DEFAULT, THR_EXPLICIT_SCHED,
 * THR_SCOPE_SYSTEM, THR_SCOPE_PROCESS
**/


int thrSpawn( thr_func_t func, void * arg DEF_VAL( 0 ), 
	  			long flags DEF_VAL( THR_DEFAULT_FLAGS ),
				thr_id_t *t_id DEF_VAL( 0 ), thr_handle_t * t_handle DEF_VAL( 0 ),
				long priority DEF_VAL( THR_DEFAULT_PRIORITY ),
				void *stack DEF_VAL( 0 ), size_t stack_size DEF_VAL( 0 ));
	

size_t thrSpawn_n( size_t n, thr_func_t func, void *arg DEF_VAL( 0 ), 
	  			long flags DEF_VAL( THR_DEFAULT_FLAGS ),
				long priority DEF_VAL( THR_DEFAULT_PRIORITY ),
				void *stack[] DEF_VAL( 0 ), size_t stack_size[] DEF_VAL( 0 ));

size_t thrSpawn_n2( thr_id_t thread_ids[],
					 size_t n, thr_func_t func, void *arg,
                     long flags, 
					 long priority DEF_VAL( THR_DEFAULT_PRIORITY ),
                     void *stack DEF_VAL( 0 ), size_t stack_size[] DEF_VAL( 0 ),
                     thr_handle_t thread_handles[] DEF_VAL( 0 ));

/// Get the priority of a particular thread.
int thrGetPrio (thr_handle_t, int *prio);

/// Set the priority of a particular thread.
int thrSetPrio (thr_handle_t, int prio);

/// Send a signal to the thread.
int thrKill (thr_id_t, int signum);

/// Yield the thread to another.
void thrYield (void);

thr_handle_t thrSelfHandle();

/// Continue the execution of a previously suspended thread.
int thrResume(thr_handle_t);

/// Suspend the execution of a particular thread.
int thrSuspend(thr_handle_t);

int thrJoin( thr_handle_t, void **status DEF_VAL( 0L ) );

//int thr_join (thr_handle_t, void ** DEF_VAL(0) );

/// Return the unique ID of the thread.
thr_id_t thrSelf (void);

/// Exit the current thread and return "status".
/// Should _not_ be called by main thread.
void thrExit( void * status DEF_VAL( 0 ));

/// Get the LWP concurrency level of the process.
int thrGetConcurrency (void);

/// Set the LWP concurrency level of the process.
int thrSetConcurrency (int );

/*
/// Change and/or examine calling thread's signal mask.
int thr_sigsetmask (int how, const sigset_t *sigset, sigset_t *osigset = 0);

int thr_keycreate (ACE_thread_key_t *keyp,
#if defined (ACE_HAS_THR_C_DEST)
                    ACE_THR_C_DEST destructor,
#else
                    ACE_THR_DEST destructor,
#endif 
                    void * = 0);

/// Free up the key so that other threads can reuse it.
int thr_keyfree (ACE_thread_key_t key);

/// Bind value to the thread-specific data key, <key>, for the calling
/// thread.
int thr_setspecific (ACE_thread_key_t key,
                      void *value);

/// Stores the current value bound to <key> for the calling thread
/// into the location pointed to by <valuep>.
int thr_getspecific (ACE_thread_key_t key,
                      void **valuep);

/// Disable thread cancellation.
int thr_disablecancel (struct cancel_state *old_state);

/// Enable thread cancellation.
int thr_enablecancel (struct cancel_state *old_state,
                       int flag);

/// Set the cancellation state.
int thr_setcancelstate (struct cancel_state &new_state,
                         struct cancel_state *old_state);

*/

/**
* Cancel a thread.  Note that this method is only portable on
* platforms, such as POSIX pthreads, that support thread
* cancellation.
*/
int thrCancel (thr_id_t t_id);

/// Test the cancel.
void thrTestCancel (void);


#if defined __cplusplus
}
#endif // __cplusplus
#endif // __UTHREAD_H__