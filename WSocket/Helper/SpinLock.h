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

				_ForceThreadSwitch( );
			}
		}
	}

	inline void lock_switch( )
	{
		while( m_cs.test_and_set( std::memory_order::memory_order_acquire ) )
		{
			_ForceThreadSwitch( );
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


	inline void _ForceThreadSwitch( )
	{
		if( !SwitchToThread( ) )
		{
			/*
			Note:  If a thread has a high-enough priority, it can prevent all other user threads on the system from running, even if it frequently calls Sleep(0)
			*/
			Sleep( 0 );	//> force new timeslice
		}
	}


private:
	std::atomic_flag	m_cs = ATOMIC_FLAG_INIT;
};