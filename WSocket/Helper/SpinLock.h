#pragma once

class CSpinLock
{
	//#todo: is good value?
	static const size_t s_nPollLimit = 4000;

public:
	inline void lock( )
	{
		size_t i = 0;
		while( m_cs.test_and_set( std::memory_order::memory_order_acquire ) )
		{
			if( i++ > s_nPollLimit )
			{
				i = 0;

				if( !SwitchToThread( ) )
				{
					Sleep( 0 );	//> force new timeslice
				}
			}
		}
	}

	inline void lock_noswitch( )
	{
		while( m_cs.test_and_set( std::memory_order::memory_order_acquire ) );
	}

	inline void unlock( )
	{
		m_cs.clear( std::memory_order::memory_order_release );
	}

private:
	std::atomic_flag	m_cs = ATOMIC_FLAG_INIT;
};