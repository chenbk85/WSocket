#pragma once


template< typename T >
class CProfileCompQueue
{
	static const size_t s_nBeginCount = 1024;

public:
	CProfileCompQueue( )
	{
		Realloc( s_nBeginCount );
	}

	~CProfileCompQueue( )
	{
		SafeDeleteArray( m_pQueueElements );
	}

public:

	
	void Realloc( size_t nCount )
	{
		SafeDeleteArray( m_pQueueElements );

		m_pQueueElements = new T[ nCount ];

		m_nElementCount = nCount;
	}

private:
	size_t	m_nElementCount = 0;


	T*		m_pQueueElements = nullptr;
};