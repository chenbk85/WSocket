#pragma once




__interface IThread
{

};

template< class T >
class CThreadHost : public IThread
{
public:
	CThreadHost( )
	{

	}

	virtual ~CThreadHost( )
	{

	}

public:


private:
	CThreadHelper	m_thread;
};



class CIoThread : public CThreadHelper
{
public:
	CIoThread( )
	{ }

	virtual ~CIoThread( )
	{ 	}

public:


	void Run( HANDLE hIoPort, std::function< void( OVERLAPPED_ENTRY* pEntries, size_t nCount ) > f)
	{
		CThreadHelper::Run( [ & ]{
			for( ;; )
			{
				ULONG nResult = 0;
				BOOL dwResult = GetQueuedCompletionStatusEx( hIoPort, m_pEntryBuffer, 1024, &nResult, INFINITE, FALSE );
				if( !dwResult )
				{
					if( GetLastError( ) == ERROR_ABANDONED_WAIT_0 )
						break;
				}

				f( m_pEntryBuffer, static_cast< size_t >( nResult ) );

			}
		} );
	}



private:
	OVERLAPPED_ENTRY*	m_pEntryBuffer = new OVERLAPPED_ENTRY[ 1024 ];

	HANDLE	m_hIoCp;
};