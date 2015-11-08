#pragma once


class CProfileCompQueue
{
	static const size_t s_nBeginCount = 1024;

public:
	CProfileCompQueue( HANDLE hIoCp )
		: m_hIoCp( hIoCp )
	{
		Realloc( s_nBeginCount );
	}

	~CProfileCompQueue( )
	{
		SafeDeleteArray( m_pQueueElements );
	}

public:
	bool Get( size_t* nElemRemoved, DWORD dwTimeout, BOOL bAlert = FALSE )
	{
		return false;
		//return ::GetQueuedCompletionStatusEx( m_hIoCp, m_pQueueElements, &m_nElementCount, nElemRemoved, dwTimeout, bAlert );
	}


	void Realloc( size_t nCount )
	{
		SafeDeleteArray( m_pQueueElements );

		m_pQueueElements = new OVERLAPPED_ENTRY[ nCount ];

		m_nElementCount = nCount;
	}

private:
	HANDLE	m_hIoCp;
	size_t	m_nElementCount = 0;


	OVERLAPPED_ENTRY*		m_pQueueElements = nullptr;
};