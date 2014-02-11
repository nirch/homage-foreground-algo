#include "thread.h"

#if defined( MT_WIN32 )
typedef struct thr_run_s
{
	thr_func_t func;
	void * argument;
} thr_run_s;

DWORD WINAPI thread_func( LPVOID param )
{
	thr_run_s *p = (thr_run_s *)param;
	void * ret = p->func( p->argument );
	free( param );
	return (DWORD)ret;
}
#endif // MT_WIN32

int thrSpawn( thr_func_t func, void * arg,  long flags,
			  thr_id_t *t_id, thr_handle_t * t_handle,
			  long priority, void *stack, size_t stack_size)
{
  thr_id_t tmp_id;
  thr_handle_t tmp_handle;

  if ((flags & THR_DETACHED) == 0) 
	  flags |= THR_JOINABLE;


	if (stack_size < THR_MIN_STACKSIZE)
		stack_size = THR_MIN_STACKSIZE;

  if (t_id == 0)
    t_id = &tmp_id;

  if (t_handle == 0)
    t_handle = &tmp_handle;

#if defined( MT_WIN32 )
  {
	  thr_run_s * srun = (thr_run_s *)malloc(sizeof(thr_run_s));
	  srun->func = func;
	  srun->argument = arg;
	  *t_handle = CreateThread( 0L, stack_size, thread_func, srun, flags, t_id );
  }
#endif // MT_WIN32
  return 0;
}

size_t thrSpawn_n (size_t n, thr_func_t func, void *arg, long flags, 
				long priority, void *stack[],size_t stack_size[])
{
  thr_id_t t_id;
  size_t i;

  for (i = 0; i < n; i++)
    if (thrSpawn(func, arg, flags, &t_id, 0, priority,
		         stack == 0 ? 0 : stack[i],  stack_size == 0 ? 0 : stack_size[i]) != 0)
		break;
  return i;
}

size_t
thrSpawn_n2 (thr_id_t thread_ids[], size_t n,  thr_func_t func, 
		     void *arg,  long flags, long priority, void *stack[],
		     size_t stack_size[], thr_handle_t thread_handles[] )
{
  size_t i;

  for (i = 0; i < n; i++)
    {
      thr_id_t t_id;
      thr_handle_t t_handle;

      int result = thrSpawn(func, arg, flags, &t_id, &t_handle, priority,
							 stack == 0 ? 0 : stack[i],  stack_size == 0 ? 0 : stack_size[i]);
	  
	  if (result == 0)
		{
         if (thread_ids != 0)
            thread_ids[i] = t_id;
		 if (thread_handles != 0)
			thread_handles[i] = t_handle;
		}
      else break;
    }

  return i;
}


thr_handle_t thrSelfHandle()
{
#if defined ( MT_WIN32 )
  return GetCurrentThread();
#else  // MT_WIN32
  return thrSelf();
#endif // MT_WIN32
}

thr_id_t thrSelf (void)
{
#if defined( MT_WIN32 )
  return GetCurrentThreadId();
#elif defined( MT_POSIX )
  return thr_self();
#elif defined( MT_POSIX )
  return pthread_self();
#else 
  return THR_INVALID_ID;
#endif 
}

void thrYield( void )
{
#if defined( MT_WIN32 )
//	SwitchToThread();
#elif defined( MT_SUNOS )
	thr_yield();
#elif defined( MT_POSIX )
	//????
#else  // MT
		/* ??? */
#endif // MT
//	Sleep( 10 );
}

int thrJoin( thr_handle_t t_h, void **status )
{
	void *local_status = 0L;
	if (status == 0)
		status = &local_status;

#if defined( MT_WIN32 )
  if ( WaitForSingleObject (t_h, INFINITE) == WAIT_OBJECT_0
      && GetExitCodeThread (t_h, (LPDWORD)status) != FALSE )
    {
      CloseHandle (t_h);
      return 0;
    }
#elif defined( MT_SUNOS )
#elif defined( MT_POSIX )
#endif
	return -1;
}

// --------------------------------------------------------------------------- //
// *************************************************************************** //
// *************************************************************************** //
// *************************************************************************** //
// *************************************************************************** //
// *************************************************************************** //
// --------------------------------------------------------------------------- //
// *************************************************************************** //
// *************************************************************************** //
// *************************************************************************** //
// *************************************************************************** //
// *************************************************************************** //
// --------------------------------------------------------------------------- //
// *************************************************************************** //
// *************************************************************************** //
// *************************************************************************** //
// *************************************************************************** //
// *************************************************************************** //
// --------------------------------------------------------------------------- //

#if 0 

int
ACE_OS::thr_create (ACE_THR_FUNC func,
                    void *args,
                    long flags,
                    ACE_thread_t *thr_id,
                    ACE_hthread_t *thr_handle,
                    long priority,
                    void *stack,
                    size_t stacksize,
                    ACE_Base_Thread_Adapter *thread_adapter)
{
  ACE_OS_TRACE ("ACE_OS::thr_create");

  if (ACE_BIT_DISABLED (flags, THR_DETACHED) &&
      ACE_BIT_DISABLED (flags, THR_JOINABLE))
    ACE_SET_BITS (flags, THR_JOINABLE);

# if defined (ACE_NO_THREAD_ADAPTER)
#   define  ACE_THREAD_FUNCTION  func
#   define  ACE_THREAD_ARGUMENT  args
# else /* ! defined (ACE_NO_THREAD_ADAPTER) */
#   if defined (ACE_PSOS)
#     define  ACE_THREAD_FUNCTION (PSOS_TASK_ENTRY_POINT) thread_args->entry_point ()
#   else
#     define  ACE_THREAD_FUNCTION  thread_args->entry_point ()
#   endif /* defined (ACE_PSOS) */
#   define  ACE_THREAD_ARGUMENT  thread_args
# endif /* ! defined (ACE_NO_THREAD_ADAPTER) */


  ACE_Base_Thread_Adapter *thread_args;
  if (thread_adapter == 0)

# if defined (ACE_HAS_WIN32_STRUCTURAL_EXCEPTIONS)
    ACE_NEW_RETURN (thread_args,
                    ACE_OS_Thread_Adapter (func, args,
                                           (ACE_THR_C_FUNC) ace_thread_adapter,
                                           ACE_OS_Object_Manager::seh_except_selector(),
                                           ACE_OS_Object_Manager::seh_except_handler()),
                    -1);
# else
  ACE_NEW_RETURN (thread_args,
                  ACE_OS_Thread_Adapter (func, args,
                                         (ACE_THR_C_FUNC) ace_thread_adapter),
                  -1);

# endif /* ACE_HAS_WIN32_STRUCTURAL_EXCEPTIONS */
  else
    thread_args = thread_adapter;

# if defined (ACE_HAS_THREADS)

  // *** Set Stack Size
#   if defined (ACE_NEEDS_HUGE_THREAD_STACKSIZE)
  if (stacksize < ACE_NEEDS_HUGE_THREAD_STACKSIZE)
    stacksize = ACE_NEEDS_HUGE_THREAD_STACKSIZE;
#   endif /* ACE_NEEDS_HUGE_THREAD_STACKSIZE */

#   if !defined (VXWORKS)
  // On VxWorks, the OS will provide a task name if the user doesn't.
  // So, we don't need to create a tmp_thr.  If the caller of this
  // member function is the Thread_Manager, than thr_id will be non-zero
  // anyways.
  ACE_thread_t tmp_thr;

  if (thr_id == 0)
    thr_id = &tmp_thr;
#   endif /* ! VXWORKS */

  ACE_hthread_t tmp_handle;
  if (thr_handle == 0)
    thr_handle = &tmp_handle;

#   if defined (ACE_HAS_PTHREADS)

  int result;
  pthread_attr_t attr;
#     if defined (ACE_HAS_PTHREADS_DRAFT4)
  if (::pthread_attr_create (&attr) != 0)
#     else /* ACE_HAS_PTHREADS_DRAFT4 */
    if (::pthread_attr_init (&attr) != 0)
#     endif /* ACE_HAS_PTHREADS_DRAFT4 */
      return -1;

#     if defined (CHORUS)
  // If it is a super actor, we can't set stacksize.  But for the time
  // being we are all non-super actors.  Should be fixed to take care
  // of super actors!!!
  if (stacksize == 0)
    stacksize = ACE_CHORUS_DEFAULT_MIN_STACK_SIZE;
  else if (stacksize < ACE_CHORUS_DEFAULT_MIN_STACK_SIZE)
    stacksize = ACE_CHORUS_DEFAULT_MIN_STACK_SIZE;
#     endif /*CHORUS */

  if (stacksize != 0)
    {
      size_t size = stacksize;

#     if defined (PTHREAD_STACK_MIN)
      if (size < ACE_static_cast (size_t, PTHREAD_STACK_MIN))
        size = PTHREAD_STACK_MIN;
#     endif /* PTHREAD_STACK_MIN */

#     if !defined (ACE_LACKS_THREAD_STACK_SIZE)      // JCEJ 12/17/96
#       if defined (ACE_HAS_PTHREADS_DRAFT4) || defined (ACE_HAS_PTHREADS_DRAFT6)
      if (::pthread_attr_setstacksize (&attr, size) != 0)
#       else
        if (ACE_ADAPT_RETVAL(pthread_attr_setstacksize (&attr, size), result) == -1)
#       endif /* ACE_HAS_PTHREADS_DRAFT4, 6 */
          {
#       if defined (ACE_HAS_PTHREADS_DRAFT4)
            ::pthread_attr_delete (&attr);
#       else /* ACE_HAS_PTHREADS_DRAFT4 */
            ::pthread_attr_destroy (&attr);
#       endif /* ACE_HAS_PTHREADS_DRAFT4 */
            return -1;
          }
#     else
      ACE_UNUSED_ARG (size);
#     endif /* !ACE_LACKS_THREAD_STACK_SIZE */
    }

  // *** Set Stack Address
#     if !defined (ACE_LACKS_THREAD_STACK_ADDR)
  if (stack != 0)
    {
      if (::pthread_attr_setstackaddr (&attr, stack) != 0)
        {
#       if defined (ACE_HAS_PTHREADS_DRAFT4)
          ::pthread_attr_delete (&attr);
#       else /* ACE_HAS_PTHREADS_DRAFT4 */
          ::pthread_attr_destroy (&attr);
#       endif /* ACE_HAS_PTHREADS_DRAFT4 */
          return -1;
        }
    }
#     else
  ACE_UNUSED_ARG (stack);
#     endif /* !ACE_LACKS_THREAD_STACK_ADDR */

  // *** Deal with various attributes
  if (flags != 0)
    {
      // *** Set Detach state
#     if !defined (ACE_LACKS_SETDETACH)
      if (ACE_BIT_ENABLED (flags, THR_DETACHED)
          || ACE_BIT_ENABLED (flags, THR_JOINABLE))
        {
          int dstate = PTHREAD_CREATE_JOINABLE;

          if (ACE_BIT_ENABLED (flags, THR_DETACHED))
            dstate = PTHREAD_CREATE_DETACHED;

#       if defined (ACE_HAS_PTHREADS_DRAFT4)
          if (::pthread_attr_setdetach_np (&attr, dstate) != 0)
#       else /* ACE_HAS_PTHREADS_DRAFT4 */
#         if defined (ACE_HAS_PTHREADS_DRAFT6)
            if (::pthread_attr_setdetachstate (&attr, &dstate) != 0)
#         else
              if (ACE_ADAPT_RETVAL(::pthread_attr_setdetachstate (&attr, dstate),
                                   result) != 0)
#         endif /* ACE_HAS_PTHREADS_DRAFT6 */
#       endif /* ACE_HAS_PTHREADS_DRAFT4 */
                {
#       if defined (ACE_HAS_PTHREADS_DRAFT4)
                  ::pthread_attr_delete (&attr);
#       else /* ACE_HAS_PTHREADS_DRAFT4 */
                  ::pthread_attr_destroy (&attr);
#       endif /* ACE_HAS_PTHREADS_DRAFT4 */
                  return -1;
                }
        }

      // Note: if ACE_LACKS_SETDETACH and THR_DETACHED is enabled, we
      // call ::pthread_detach () below.  If THR_DETACHED is not
      // enabled, we call ::pthread_detach () in the Thread_Manager,
      // after joining with the thread.
#     endif /* ACE_LACKS_SETDETACH */

      // *** Set Policy
#     if !defined (ACE_LACKS_SETSCHED)
      // If we wish to set the priority explicitly, we have to enable
      // explicit scheduling, and a policy, too.
      if (priority != ACE_DEFAULT_THREAD_PRIORITY)
        {
          ACE_SET_BITS (flags, THR_EXPLICIT_SCHED);
          if (ACE_BIT_DISABLED (flags, THR_SCHED_FIFO)
              && ACE_BIT_DISABLED (flags, THR_SCHED_RR)
              && ACE_BIT_DISABLED (flags, THR_SCHED_DEFAULT))
            ACE_SET_BITS (flags, THR_SCHED_DEFAULT);
        }

      if (ACE_BIT_ENABLED (flags, THR_SCHED_FIFO)
          || ACE_BIT_ENABLED (flags, THR_SCHED_RR)
          || ACE_BIT_ENABLED (flags, THR_SCHED_DEFAULT))
        {
          int spolicy;

#       if defined (ACE_HAS_ONLY_SCHED_OTHER)
          // SunOS, thru version 5.6, only supports SCHED_OTHER.
          spolicy = SCHED_OTHER;
#       else
          // Make sure to enable explicit scheduling, in case we didn't
          // enable it above (for non-default priority).
          ACE_SET_BITS (flags, THR_EXPLICIT_SCHED);

          if (ACE_BIT_ENABLED (flags, THR_SCHED_DEFAULT))
            spolicy = SCHED_OTHER;
          else if (ACE_BIT_ENABLED (flags, THR_SCHED_FIFO))
            spolicy = SCHED_FIFO;
#         if defined (SCHED_IO)
          else if (ACE_BIT_ENABLED (flags, THR_SCHED_IO))
            spolicy = SCHED_IO;
#         else
          else if (ACE_BIT_ENABLED (flags, THR_SCHED_IO))
            {
              errno = ENOSYS;
              return -1;
            }
#         endif /* SCHED_IO */
          else
            spolicy = SCHED_RR;

#         if defined (ACE_HAS_FSU_PTHREADS)
          int ret;
          switch (spolicy)
            {
            case SCHED_FIFO:
            case SCHED_RR:
              ret = 0;
              break;
            default:
              ret = 22;
              break;
            }
          if (ret != 0)
            {
              ::pthread_attr_destroy (&attr);
              return -1;
            }
#         endif    /*  ACE_HAS_FSU_PTHREADS */

#       endif /* ACE_HAS_ONLY_SCHED_OTHER */

#       if defined (ACE_HAS_PTHREADS_DRAFT4)
          result = ::pthread_attr_setsched (&attr, spolicy);
#       elif defined (ACE_HAS_PTHREADS_DRAFT6)
          result = ::pthread_attr_setschedpolicy (&attr, spolicy);
#       else  /* draft 7 or std */
          ACE_ADAPT_RETVAL(::pthread_attr_setschedpolicy (&attr, spolicy),
                           result);
#       endif /* ACE_HAS_PTHREADS_DRAFT4 */
          if (result != 0)
            {
#       if defined (ACE_HAS_PTHREADS_DRAFT4)
              ::pthread_attr_delete (&attr);
#       else /* ACE_HAS_PTHREADS_DRAFT4 */
              ::pthread_attr_destroy (&attr);
#       endif /* ACE_HAS_PTHREADS_DRAFT4 */
              return -1;
            }
        }

      // *** Set Priority (use reasonable default priorities)
#       if defined(ACE_HAS_PTHREADS_STD)
      // If we wish to explicitly set a scheduling policy, we also
      // have to specify a priority.  We choose a "middle" priority as
      // default.  Maybe this is also necessary on other POSIX'ish
      // implementations?
      if ((ACE_BIT_ENABLED (flags, THR_SCHED_FIFO)
           || ACE_BIT_ENABLED (flags, THR_SCHED_RR)
           || ACE_BIT_ENABLED (flags, THR_SCHED_DEFAULT))
          && priority == ACE_DEFAULT_THREAD_PRIORITY)
        {
          if (ACE_BIT_ENABLED (flags, THR_SCHED_FIFO))
            priority = ACE_THR_PRI_FIFO_DEF;
          else if (ACE_BIT_ENABLED (flags, THR_SCHED_RR))
            priority = ACE_THR_PRI_RR_DEF;
          else // THR_SCHED_DEFAULT
            priority = ACE_THR_PRI_OTHER_DEF;
        }
#       endif /* ACE_HAS_PTHREADS_STD */
      if (priority != ACE_DEFAULT_THREAD_PRIORITY)
        {
          struct sched_param sparam;
          ACE_OS::memset ((void *) &sparam, 0, sizeof sparam);

#       if defined (ACE_HAS_IRIX62_THREADS)
          sparam.sched_priority = ACE_MIN (priority,
                                           (long) PTHREAD_MAX_PRIORITY);
#       elif defined (PTHREAD_MAX_PRIORITY) && !defined(ACE_HAS_PTHREADS_STD)
          /* For MIT pthreads... */
          sparam.prio = ACE_MIN (priority, PTHREAD_MAX_PRIORITY);
#       elif defined(ACE_HAS_PTHREADS_STD) && !defined (ACE_HAS_STHREADS)
          // The following code forces priority into range.
          if (ACE_BIT_ENABLED (flags, THR_SCHED_FIFO))
            sparam.sched_priority =
              ACE_MIN (ACE_THR_PRI_FIFO_MAX,
                       ACE_MAX (ACE_THR_PRI_FIFO_MIN, priority));
          else if (ACE_BIT_ENABLED(flags, THR_SCHED_RR))
            sparam.sched_priority =
              ACE_MIN (ACE_THR_PRI_RR_MAX,
                       ACE_MAX (ACE_THR_PRI_RR_MIN, priority));
          else // Default policy, whether set or not
            sparam.sched_priority =
              ACE_MIN (ACE_THR_PRI_OTHER_MAX,
                       ACE_MAX (ACE_THR_PRI_OTHER_MIN, priority));
#       elif defined (PRIORITY_MAX)
          sparam.sched_priority = ACE_MIN (priority,
                                           (long) PRIORITY_MAX);
#       else
          sparam.sched_priority = priority;
#       endif /* ACE_HAS_IRIX62_THREADS */

#       if defined (ACE_HAS_FSU_PTHREADS)
          if (sparam.sched_priority >= PTHREAD_MIN_PRIORITY
              && sparam.sched_priority <= PTHREAD_MAX_PRIORITY)
            attr.prio = sparam.sched_priority;
          else
            {
              pthread_attr_destroy (&attr);
              errno = EINVAL;
              return -1;
            }
#       else
          {
#         if defined (sun)  &&  defined (ACE_HAS_ONLY_SCHED_OTHER)
            // SunOS, through 5.6, POSIX only allows priorities > 0 to
            // ::pthread_attr_setschedparam.  If a priority of 0 was
            // requested, set the thread priority after creating it, below.
            if (priority > 0)
#         endif /* sun && ACE_HAS_ONLY_SCHED_OTHER */
              {
#         if defined (ACE_HAS_PTHREADS_DRAFT4) || defined (ACE_HAS_PTHREADS_DRAFT6)
                result = ::pthread_attr_setprio (&attr,
                                                 sparam.sched_priority);
#         else /* this is draft 7 or std */
                ACE_ADAPT_RETVAL(::pthread_attr_setschedparam (&attr, &sparam),
                                 result);
#         endif /* ACE_HAS_PTHREADS_DRAFT4, 6 */
                if (result != 0)
                  {
#         if defined (ACE_HAS_PTHREADS_DRAFT4)
                    ::pthread_attr_delete (&attr);
#         else /* ACE_HAS_PTHREADS_DRAFT4 */
                    ::pthread_attr_destroy (&attr);
#         endif /* ACE_HAS_PTHREADS_DRAFT4 */
                    return -1;
                  }
              }
          }
#       endif    /* ACE_HAS_FSU_PTHREADS */
        }

      // *** Set scheduling explicit or inherited
      if (ACE_BIT_ENABLED (flags, THR_INHERIT_SCHED)
          || ACE_BIT_ENABLED (flags, THR_EXPLICIT_SCHED))
        {
#       if defined (ACE_HAS_PTHREADS_DRAFT4)
          int sched = PTHREAD_DEFAULT_SCHED;
#       else /* ACE_HAS_PTHREADS_DRAFT4 */
          int sched = PTHREAD_EXPLICIT_SCHED;
#       endif /* ACE_HAS_PTHREADS_DRAFT4 */
          if (ACE_BIT_ENABLED (flags, THR_INHERIT_SCHED))
            sched = PTHREAD_INHERIT_SCHED;
          if (::pthread_attr_setinheritsched (&attr, sched) != 0)
            {
#       if defined (ACE_HAS_PTHREADS_DRAFT4)
              ::pthread_attr_delete (&attr);
#       else /* ACE_HAS_PTHREADS_DRAFT4 */
              ::pthread_attr_destroy (&attr);
#       endif /* ACE_HAS_PTHREADS_DRAFT4 */
              return -1;
            }
        }
#     else /* ACE_LACKS_SETSCHED */
      ACE_UNUSED_ARG (priority);
#     endif /* ACE_LACKS_SETSCHED */

      // *** Set Scope
#     if !defined (ACE_LACKS_THREAD_PROCESS_SCOPING)
      if (ACE_BIT_ENABLED (flags, THR_SCOPE_SYSTEM)
          || ACE_BIT_ENABLED (flags, THR_SCOPE_PROCESS))
        {
#         if defined (ACE_CONFIG_LINUX_H) || defined (HPUX)
          // LinuxThreads do not have support for PTHREAD_SCOPE_PROCESS.
          // Neither does HPUX (up to HP-UX 11.00, as far as I know).
          int scope = PTHREAD_SCOPE_SYSTEM;
#         else /* ACE_CONFIG_LINUX_H */
          int scope = PTHREAD_SCOPE_PROCESS;
#         endif /* ACE_CONFIG_LINUX_H */
          if (ACE_BIT_ENABLED (flags, THR_SCOPE_SYSTEM))
            scope = PTHREAD_SCOPE_SYSTEM;

          if (::pthread_attr_setscope (&attr, scope) != 0)
            {
#       if defined (ACE_HAS_PTHREADS_DRAFT4)
              ::pthread_attr_delete (&attr);
#       else /* ACE_HAS_PTHREADS_DRAFT4 */
              ::pthread_attr_destroy (&attr);
#       endif /* ACE_HAS_PTHREADS_DRAFT4 */
              return -1;
            }
        }
#     endif /* !ACE_LACKS_THREAD_PROCESS_SCOPING */

      if (ACE_BIT_ENABLED (flags, THR_NEW_LWP))
        {
          // Increment the number of LWPs by one to emulate the
          // SunOS semantics.
          int lwps = ACE_OS::thr_getconcurrency ();
          if (lwps == -1)
            {
              if (errno == ENOTSUP)
                // Suppress the ENOTSUP because it's harmless.
                errno = 0;
              else
                // This should never happen on SunOS:
                // ::thr_getconcurrency () should always succeed.
                return -1;
            }
          else if (ACE_OS::thr_setconcurrency (lwps + 1) == -1)
            {
              if (errno == ENOTSUP)
                {
                  // Unlikely:  ::thr_getconcurrency () is supported but
                  // ::thr_setconcurrency () is not?
                }
              else
                return -1;
            }
        }
    }

#     if defined (ACE_HAS_PTHREADS_DRAFT4)
  ACE_OSCALL (::pthread_create (thr_id, attr,
                                thread_args->entry_point (),
                                thread_args),
              int, -1, result);

#       if defined (ACE_LACKS_SETDETACH)
  if (ACE_BIT_ENABLED (flags, THR_DETACHED))
    {
#         if defined (HPUX_10)
      // HP-UX DCE threads' pthread_detach will smash thr_id if it's
      // just given as an argument.  This will cause
      // ACE_Thread_Manager (if it's doing this create) to lose track
      // of the new thread since the ID will be passed back equal to
      // 0.  So give pthread_detach a junker to scribble on.
      ACE_thread_t  junker;
      cma_handle_assign(thr_id, &junker);
      ::pthread_detach (&junker);
#         else
      ::pthread_detach (thr_id);
#         endif /* HPUX_10 */
    }
#       endif /* ACE_LACKS_SETDETACH */

  ::pthread_attr_delete (&attr);

#     elif defined (ACE_HAS_PTHREADS_DRAFT6)
  ACE_OSCALL (::pthread_create (thr_id, &attr,
                                thread_args->entry_point (),
                                thread_args),
              int, -1, result);
  ::pthread_attr_destroy (&attr);

#     else /* this is draft 7 or std */
  ACE_OSCALL (ACE_ADAPT_RETVAL (::pthread_create (thr_id,
                                                  &attr,
                                                  thread_args->entry_point (),
                                                  thread_args),
                                result),
              int, -1, result);
  ::pthread_attr_destroy (&attr);
#     endif /* ACE_HAS_PTHREADS_DRAFT4 */

  // This is a SunOS or POSIX implementation of pthreads, where we
  // assume that ACE_thread_t and ACE_hthread_t are the same.  If this
  // *isn't* correct on some platform, please let us know.
  if (result != -1)
    *thr_handle = *thr_id;

#     if defined (sun)  &&  defined (ACE_HAS_ONLY_SCHED_OTHER)
  // SunOS prior to 5.7:

  // If the priority is 0, then we might have to set it now because we
  // couldn't set it with ::pthread_attr_setschedparam, as noted
  // above.  This doesn't provide strictly correct behavior, because
  // the thread was created (above) with the priority of its parent.
  // (That applies regardless of the inherit_sched attribute: if it
  // was PTHREAD_INHERIT_SCHED, then it certainly inherited its
  // parent's priority.  If it was PTHREAD_EXPLICIT_SCHED, then "attr"
  // was initialized by the SunOS ::pthread_attr_init () to contain
  // NULL for the priority, which indicated to SunOS ::pthread_create
  // () to inherit the parent priority.)
  if (priority == 0)
    {
      // Check the priority of this thread, which is the parent
      // of the newly created thread.  If it is 0, then the
      // newly created thread will have inherited the priority
      // of 0, so there's no need to explicitly set it.
      struct sched_param sparam;
      int policy = 0;
      ACE_OSCALL (ACE_ADAPT_RETVAL (::pthread_getschedparam (thr_self (),
                                                             &policy,
                                                             &sparam),
                                    result), int,
                  -1, result);

      // The only policy supported by by SunOS, thru version 5.6,
      // is SCHED_OTHER, so that's hard-coded here.
      policy = ACE_SCHED_OTHER;

      if (sparam.sched_priority != 0)
        {
          ACE_OS::memset ((void *) &sparam, 0, sizeof sparam);
          // The memset to 0 sets the priority to 0, so we don't need
          // to explicitly set sparam.sched_priority.

          ACE_OSCALL_RETURN (ACE_ADAPT_RETVAL (::pthread_setschedparam (*thr_id,
                                                                        policy,
                                                                        &sparam),
                                               result),
                             int, -1);
        }
    }

#       if defined (ACE_NEEDS_LWP_PRIO_SET)
#         if 0
  // It would be useful if we could make this work.  But, it requires
  // a mechanism for determining the ID of an LWP to which another
  // thread is bound.  Is there a way to do that?  Instead, just rely
  // on the code in ACE_Thread_Adapter::invoke () to set the LWP
  // priority.

  // If the thread is bound, then set the priority on its LWP.
  if (ACE_BIT_ENABLED (flags, THR_BOUND))
    {
      ACE_Sched_Params sched_params (ACE_BIT_ENABLED (flags, THR_SCHED_FIFO) ||
                                     ACE_BIT_ENABLED (flags, THR_SCHED_RR)  ?
                                     ACE_SCHED_FIFO  :
                                     ACE_SCHED_OTHER,
                                     priority);
      result = ACE_OS::lwp_setparams (sched_params,
                                      /* ? How do we find the ID of the LWP
                                         to which *thr_id is bound? */);
    }
#         endif /* 0 */
#       endif /* ACE_NEEDS_LWP_PRIO_SET */

#     endif /* sun && ACE_HAS_ONLY_SCHED_OTHER */
  return result;
#   elif defined (ACE_HAS_STHREADS)
  int result;
  int start_suspended = ACE_BIT_ENABLED (flags, THR_SUSPENDED);

  if (priority != ACE_DEFAULT_THREAD_PRIORITY)
    // If we need to set the priority, then we need to start the
    // thread in a suspended mode.
    ACE_SET_BITS (flags, THR_SUSPENDED);

  ACE_OSCALL (ACE_ADAPT_RETVAL (::thr_create (stack, stacksize,
                                              thread_args->entry_point (),
                                              thread_args,
                                              flags, thr_id), result),
              int, -1, result);

  if (result != -1)
    {
      // With SunOS threads, ACE_thread_t and ACE_hthread_t are the same.
      *thr_handle = *thr_id;

      if (priority != ACE_DEFAULT_THREAD_PRIORITY)
        {
          // Set the priority of the new thread and then let it
          // continue, but only if the user didn't start it suspended
          // in the first place!
          if ((result = ACE_OS::thr_setprio (*thr_id, priority)) != 0)
            {
              errno = result;
              return -1;
            }

          if (start_suspended == 0)
            {
              if ((result = ACE_OS::thr_continue (*thr_id)) != 0)
                {
                  errno = result;
                  return -1;
                }
            }
        }
    }
  return result;
#   elif defined (ACE_HAS_WTHREADS)
  ACE_UNUSED_ARG (stack);
#     if defined (ACE_HAS_MFC) && (ACE_HAS_MFC != 0)
  if (ACE_BIT_ENABLED (flags, THR_USE_AFX))
    {
      CWinThread *cwin_thread =
        ::AfxBeginThread ((AFX_THREADPROC) thread_args->entry_point (),
                          thread_args,
                          priority,
                          0,
                          flags | THR_SUSPENDED);
      // Have to duplicate the handle because
      // CWinThread::~CWinThread() closes the original handle.
#       if !defined (ACE_HAS_WINCE)
      (void) ::DuplicateHandle (::GetCurrentProcess (),
                                cwin_thread->m_hThread,
                                ::GetCurrentProcess (),
                                thr_handle,
                                0,
                                TRUE,
                                DUPLICATE_SAME_ACCESS);
#       endif /* ! ACE_HAS_WINCE */
      *thr_id = cwin_thread->m_nThreadID;

      if (ACE_BIT_ENABLED (flags, THR_SUSPENDED) == 0)
        cwin_thread->ResumeThread ();
      // cwin_thread will be deleted in AfxThreadExit()
      // Warning: If AfxThreadExit() is called from within the
      // thread, ACE_TSS_Cleanup->exit() never gets called !
    }
  else
#     endif /* ACE_HAS_MFC */
    {
      int start_suspended = ACE_BIT_ENABLED (flags, THR_SUSPENDED);

      if (priority != ACE_DEFAULT_THREAD_PRIORITY)
        // If we need to set the priority, then we need to start the
        // thread in a suspended mode.
        ACE_SET_BITS (flags, THR_SUSPENDED);

      *thr_handle = (void *) ACE_BEGINTHREADEX (0,
                                                ACE_static_cast
                                                   (u_int, stacksize),
                                                thread_args->entry_point (),
                                                thread_args,
                                                flags,
                                                thr_id);

      if (priority != ACE_DEFAULT_THREAD_PRIORITY && *thr_handle != 0)
        {
          // Set the priority of the new thread and then let it
          // continue, but only if the user didn't start it suspended
          // in the first place!
          ACE_OS::thr_setprio (*thr_handle, priority);

          if (start_suspended == 0)
            ACE_OS::thr_continue (*thr_handle);
        }
    }
#     if 0
  *thr_handle = ::CreateThread
    (0,
     stacksize,
     LPTHREAD_START_ROUTINE (thread_args->entry_point ()),
     thread_args,
     flags,
     thr_id);
#     endif /* 0 */

  // Close down the handle if no one wants to use it.
  if (thr_handle == &tmp_handle)
    ::CloseHandle (tmp_handle);

  if (*thr_handle != 0)
    return 0;
  else
    ACE_FAIL_RETURN (-1);
  /* NOTREACHED */

#   elif defined (ACE_PSOS)

  // stack is created in the task's memory region 0
  ACE_UNUSED_ARG (stack);

  // task creation and start flags are fixed
  ACE_UNUSED_ARG (flags);

  // lowest priority is reserved for the IDLE pSOS+ system daemon,
  // highest are reserved for high priority pSOS+ system daemons
  if (priority < PSOS_TASK_MIN_PRIORITY)
    {
      priority = PSOS_TASK_MIN_PRIORITY;
    }
  else if (priority > PSOS_TASK_MAX_PRIORITY)
    {
      priority = PSOS_TASK_MAX_PRIORITY;
    }

  // set the stacksize to a default value if no size is specified
  if (stacksize == 0)
    stacksize = ACE_PSOS_DEFAULT_STACK_SIZE;

  ACE_hthread_t tid;
  *thr_handle = 0;

  // create the thread
  if (t_create ((char *) thr_id, // task name
                priority,        // (possibly adjusted) task priority
                stacksize,       // passed stack size is used for supervisor stack
                0,               // no user stack: tasks run strictly in supervisor mode
                T_LOCAL,         // local to the pSOS+ node (does not support pSOS+m)
                &tid)            // receives task id
      != 0)
    {
      return -1;
    }

  // pSOS tasks are passed an array of 4 u_longs
  u_long targs[4];
  targs[0] = (u_long) ACE_THREAD_ARGUMENT;
  targs[1] = 0;
  targs[2] = 0;
  targs[3] = 0;

  // start the thread
  if (t_start (tid,
               T_PREEMPT |            // Task can be preempted
               //             T_NOTSLICE |           // Task is not timesliced with other tasks at same priority
               T_TSLICE |             // Task is timesliced with other tasks at same priority
               T_NOASR |              // Task level signals disabled
               T_SUPV |               // Task runs strictly in supervisor mode
               T_ISR,                 // Hardware interrupts are enabled
               ACE_THREAD_FUNCTION,   // Task entry point
               targs)                 // Task argument(s)
      != 0)
    {
      return -1;
    }

  // store the task id in the handle and return success
  *thr_handle = tid;
  return 0;

#   elif defined (VXWORKS)
  // The hard-coded values below are what ::sp () would use.  (::sp ()
  // hardcodes priority to 100, flags to VX_FP_TASK, and stacksize to
  // 20,000.)  stacksize should be an even integer.  If a stack is not
  // specified, ::taskSpawn () is used so that we can set the
  // priority, flags, and stacksize.  If a stack is specified,
  // ::taskInit ()/::taskActivate() are used.

  // If called with thr_create() defaults, use same default values as ::sp ():
  if (priority == ACE_DEFAULT_THREAD_PRIORITY) priority = 100;
  // Assumes that there is a floating point coprocessor.  As noted
  // above, ::sp () hardcodes this, so we should be safe with it.
  if (flags == 0) flags = VX_FP_TASK;
  if (stacksize == 0) stacksize = 20000;

  const u_int thr_id_provided =
    thr_id  &&  *thr_id  &&  (*thr_id)[0] != ACE_THR_ID_ALLOCATED;

  ACE_hthread_t tid;
#     if 0 /* Don't support setting of stack, because it doesn't seem to work. */
  if (stack == 0)
    {
#     else
      ACE_UNUSED_ARG (stack);
#     endif /* 0 */
      // The call below to ::taskSpawn () causes VxWorks to assign a
      // unique task name of the form: "t" + an integer, because the
      // first argument is 0.
      tid = ::taskSpawn (thr_id_provided  ?  *thr_id  :  0,
                         priority,
                         (int) flags,
                         (int) stacksize,
                         thread_args->entry_point (),
                         (int) thread_args,
                         0, 0, 0, 0, 0, 0, 0, 0, 0);
#     if 0 /* Don't support setting of stack, because it doesn't seem to work. */
    }
  else
    {
      // If a task name (thr_id) was not supplied, then the task will
      // not have a unique name.  That's VxWorks' behavior.

      // Carve out a TCB at the beginning of the stack space.  The TCB
      // occupies 400 bytes with VxWorks 5.3.1/I386.
      WIND_TCB *tcb = (WIND_TCB *) stack;

      // The TID is defined to be the address of the TCB.
      int status = ::taskInit (tcb,
                               thr_id_provided  ?  *thr_id  :  0,
                               priority,
                               (int) flags,
                               (char *) stack + sizeof (WIND_TCB),
                               (int) (stacksize - sizeof (WIND_TCB)),
                               thread_args->entry_point (),
                               (int) thread_args,
                               0, 0, 0, 0, 0, 0, 0, 0, 0);

      if (status == OK)
        {
          // The task was successfully initialized, now activate it.
          status = ::taskActivate ((ACE_hthread_t) tcb);
        }

      tid = status == OK  ?  (ACE_hthread_t) tcb  :  ERROR;
    }
#     endif /* 0 */

  if (tid == ERROR)
    return -1;
  else
    {
      if (! thr_id_provided  &&  thr_id)
        {
          if (*thr_id  &&  (*thr_id)[0] == ACE_THR_ID_ALLOCATED)
            // *thr_id was allocated by the Thread_Manager.  ::taskTcb
            // (int tid) returns the address of the WIND_TCB (task
            // control block).  According to the ::taskSpawn()
            // documentation, the name of the new task is stored at
            // pStackBase, but is that of the current task?  If so, it
            // might be a bit quicker than this extraction of the tcb
            // . . .
            ACE_OS::strsncpy (*thr_id + 1, ::taskTcb (tid)->name, 10);
          else
            // *thr_id was not allocated by the Thread_Manager.
            // Pass back the task name in the location pointed to
            // by thr_id.
            *thr_id = ::taskTcb (tid)->name;
        }
      // else if the thr_id was provided, there's no need to overwrite
      // it with the same value (string).  If thr_id is 0, then we can't
      // pass the task name back.

      if (thr_handle)
        *thr_handle = tid;

      return 0;
    }

#   endif /* ACE_HAS_STHREADS */
# else
  ACE_UNUSED_ARG (func);
  ACE_UNUSED_ARG (args);
  ACE_UNUSED_ARG (flags);
  ACE_UNUSED_ARG (thr_id);
  ACE_UNUSED_ARG (thr_handle);
  ACE_UNUSED_ARG (priority);
  ACE_UNUSED_ARG (stack);
  ACE_UNUSED_ARG (stacksize);
  ACE_NOTSUP_RETURN (-1);
# endif /* ACE_HAS_THREADS */
}

#endif // 0
