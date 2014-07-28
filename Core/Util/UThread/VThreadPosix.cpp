#include "VThreadPosix.h"

#include <assert.h> 

#include <pthread.h> 



CVThread::CVThread(void)
{
}

CVThread::~CVThread(void)
{
}

long CVThread::GetThreadId()
{
//	return ::GetCurrentThreadId();
}

void CVThread::Sleep(long milliseconds)
{
//	::Sleep(milliseconds);
}





int CVThread::ResumeThread()
{
int	ret;

//	ret = ::ResumeThread( m_handle );

	return ret;
}


int CVThread::SuspendThread()
{
int	ret;

//	ret = ::SuspendThread( m_handle );

	return ret;
}






//void CVThread::SetEventBegin()
//{
//	m_eBegin.Set();
//}

//void CVThread::SetEventEnd()
//{
//	m_eEnd.Set();
//}
//
//long CVThread::WaitEventBegin( long milliseconds )
//{
//	return m_eBegin.Wait( milliseconds );
//}
//
//long CVThread::WaitEventEnd( long milliseconds )
//{
//	return m_eEnd.Wait( milliseconds );
//
//}



void CVThread::StartThread( int flag ) 
{ 
	// Create the thread using POSIX routines. 
	pthread_attr_t  attr; 
	pthread_t       posixThreadID; 
	int             returnVal; 

	returnVal = pthread_attr_init(&attr); 
	assert(!returnVal); 
	returnVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 
	assert(!returnVal); 

	int     threadError = pthread_create(&posixThreadID, &attr, &ThreadFunc, this); 

	returnVal = pthread_attr_destroy(&attr); 
	assert(!returnVal); 
	if (threadError != 0) 
	{ 
		// Report an error. 
	} 
} 


