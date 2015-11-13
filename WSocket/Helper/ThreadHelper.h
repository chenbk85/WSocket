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
	{ }

	virtual ~CThreadHelper( )
	{
		assert( m_thread.joinable( ) );
	}

public:
	template< class _Fn, class... _Args >
	inline void Run( _Fn&& _Fx, _Args&&... _Ax )
	{
		assert( !m_thread.joinable( ) );

		m_thread = std::thread( std::forward<_Fn>( _Fx ), std::forward<_Args>( _Ax )... );
	}

public:
	inline DWORD Suspend( )
	{
		assert( m_thread.joinable( ) );

		DWORD dwResult = ::SuspendThread( m_thread.native_handle( ) );

		if( dwResult == MAXIMUM_SUSPEND_COUNT )
		{
			__debugbreak( );
		}
		return dwResult;
	}

	inline DWORD Resume( )
	{
		assert( m_thread.joinable( ) );

		return ::ResumeThread( m_thread.native_handle( ) );
	}

	inline void SetPriority( eThreadPriority::e ePriority )
	{
		assert( m_thread.joinable( ) );

		::SetThreadPriority( m_thread.native_handle( ), ePriority );
	}

	inline ULONG64 GetThreadCycleTime( )
	{
		assert( m_thread.joinable( ) );
		
		ULONG64 nCycleTime = 0;
		WinApi::Kernel32::QueryThreadCycleTime( m_thread.native_handle( ), &nCycleTime );

		return nCycleTime;
	}


protected:
	std::thread			m_thread;
};