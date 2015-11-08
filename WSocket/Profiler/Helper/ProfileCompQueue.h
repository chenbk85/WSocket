#pragma once


template< typename T >
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
		return ::GetQueuedCompletionStatusEx( m_hIoCp, m_pQueueElements, &m_nElementCount, nElemRemoved, dwTimeout, bAlert );
	}


	void Realloc( size_t nCount )
	{
		SafeDeleteArray( m_pQueueElements );

		m_pQueueElements = new T[ nCount ];

		m_nElementCount = nCount;
	}

private:
	HANDLE	m_hIoCp;
	size_t	m_nElementCount = 0;


	T*		m_pQueueElements = nullptr;
};