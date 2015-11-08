#pragma once

namespace eThreadPriority {
	enum e : int {
		eBackgroundBegin = THREAD_MODE_BACKGROUND_BEGIN,
		eBackgroundEnd = THREAD_MODE_BACKGROUND_END,

		eLowest = THREAD_PRIORITY_LOWEST,
		eBelowNoraml = THREAD_PRIORITY_BELOW_NORMAL,
		eNormal = THREAD_PRIORITY_NORMAL,
		eAboveNormal = THREAD_PRIORITY_ABOVE_NORMAL,
		eHighest = THREAD_PRIORITY_HIGHEST,
		
		eTimeCritical = THREAD_PRIORITY_TIME_CRITICAL,
		eIdle = THREAD_PRIORITY_IDLE
	};
}

class CThreadHelper
{
public:
	CThreadHelper( )
	{

	}

	~CThreadHelper( )
	{
		
	}

public:
	template< class _Fn, class... _Args >
	void Run( _Fn&& _Fx, _Args&&... _Ax )
	{
		assert( !m_thread.joinable( ) );
		 
		m_thread = std::thread( std::forward<_Fn>( _Fx ), std::forward<_Args>( _Ax )... );
	}

public:
	inline void Suspend( )
	{
		assert( m_thread.joinable( ) );

		::SuspendThread( m_thread.native_handle( ) );
	}

	inline void Resume( )
	{
		assert( m_thread.joinable( ) );

		::ResumeThread( m_thread.native_handle( ) );
	}

	inline void SetPriority( eThreadPriority::e ePriority )
	{
		assert( m_thread.joinable( ) );

		::SetThreadPriority( m_thread.native_handle( ), ePriority );
	}

private:
	
	
	std::thread			m_thread;
};