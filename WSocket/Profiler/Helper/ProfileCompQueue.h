#pragma once


#include "Profiler/ProfileThread.h"


class CProfileCompThread : CProfileThread
{
public:
	CProfileCompThread( )
	{ }

	~CProfileCompThread( )
	{ }

public:
	void Run( HANDLE hIoCp, DWORD dwTimeout, std::function< void( OVERLAPPED_ENTRY* pEntries, size_t nCount ) > f )
	{
		this->RunThread( [ & ]{
			
			ULONG nCount = 0;
			BOOL bResult = ::GetQueuedCompletionStatusEx( hIoCp, m_pEntries, 1024, &nCount, dwTimeout, FALSE );
			if( !bResult )
			{
				if( GetLastError( ) != ERROR_ABANDONED_WAIT_0 )
				{
					__debugbreak( );
				}
				//> timeout?
			}
			else
			{
				f( m_pEntries, nCount );
			}


		} );
	}

private:


	
	OVERLAPPED_ENTRY*	m_pEntries = new OVERLAPPED_ENTRY[ 1024 ];

};