#ifndef __UTHR_BASE_H__
#define __UTHR_BASE_H__

/**
 * Macro
 *   MT_WIN32, MT_SUNOS, MT_POSIX
 *
 * Types:
 *    thr_id_t, thr_handle_t
 *
**/

#if !(defined( MT_WIN32) || defined( MT_SOLARIS ) || defined( MT_POSIX ))
#if defined( WIN32 )         // Windows
#	define MT_WIN32    
#elif defined( __SUNPRO_CC ) // Solaris
#	define MT_SUNOS
#elif defined( GNUC )        // GNU (use POSIX)
#	define MT_POSIX
#else 
#	error( "Unknown compiler" );
#endif
#endif

#if   defined( MT_WIN32 )
#	include <Windows.h>
	typedef DWORD thr_id_t;
	typedef void* thr_handle_t;
#elif defined( MT_SUNOS )
#	include <thread.h>
	typedef thread_t thr_id_t;
#	define  thr_handle_t  thr_id_t
#elif defined( MT_POSIX ) 
#	include <pthread.h>
	typedef pthread_t     thr_id_t;
#	define  thr_handle_t  thr_id_t
#else 
#	error( "Unknown threading model" );
#endif 



#define THR_MIN_STACKSIZE 1024

#if !defined( THR_CANCEL_DISABLE )
#	define THR_CANCEL_DISABLE 0
#endif // THR_CANCEL_DISABLE

#if !defined( THR_CANCEL_ENABLE )
#	define THR_CANCEL_ENABLE 0
#endif // THR_CANCEL_ENABLE

#if !defined( THR_CANCEL_DEFERRED )
#	define THR_CANCEL_DEFERRED 0
#endif // THR_CANCEL_DEFERRED

#if !defined( THR_CANCEL_ASYNCHRONOUS )
#	define THR_CANCEL_ASYNCHRONOUS 0
#endif // THR_CANCEL_ASYNCHRONOUS

#if !defined( THR_BOUND )
#	define THR_BOUND 0
#endif // THR_BOUND

#if !defined( THR_NEW_LWP )
#	define THR_NEW_LWP 0
#endif // THR_NEW_LWP

#if !defined( THR_DETACHED )
#	define THR_DETACHED 0
#endif // THR_DETACHED

#if !defined( THR_SUSPENDED )
#	define THR_SUSPENDED 0
#endif // THR_SUSPENDED

#if !defined( THR_DAEMON )
#	define THR_DAEMON 0
#endif // THR_DAEMON

#if !defined( THR_JOINABLE )
#	define THR_JOINABLE 0
#endif // THR_JOINABLE

#if !defined( THR_SCHED_FIFO )
#	define THR_SCHED_FIFO 0
#endif // THR_SCHED_FIFO

#if !defined( THR_SCHED_RR )
#	define THR_SCHED_RR 0
#endif // THR_SCHED_RR

#if !defined( THR_SCHED_DEFAULT )
#	define THR_SCHED_DEFAULT 0
#endif // THR_SCHED_DEFAULT

#if !defined( THR_EXPLICIT_SCHED )
#	define THR_EXPLICIT_SCHED 0
#endif // THR_EXPLICIT_SCHED

#if !defined( THR_SCOPE_SYSTEM )
#	define THR_SCOPE_SYSTEM 0
#endif // THR_SCOPE_SYSTEM

#if !defined( THR_SCOPE_PROCESS )
#	define THR_SCOPE_PROCESS 0
#endif // THR_SCOPE_PROCESS

#if !defined( THR_DEFAULT_PRIORITY )
#	define THR_DEFAULT_PRIORITY 0
#endif // THR_SCOPE_PROCESS
	
#endif // __UTHR_BASE_H__