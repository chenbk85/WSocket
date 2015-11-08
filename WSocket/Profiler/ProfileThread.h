#pragma once

#include "Helper/ThreadHelper.h"

class CProfileThread
{
public:
	enum e {
		eBackgroundBegin = THREAD_MODE_BACKGROUND_BEGIN,
		eBackgroundEnd = THREAD_MODE_BACKGROUND_END,

		eAboveNormal = THREAD_PRIORITY_ABOVE_NORMAL
	};


public:
	CProfileThread( );
	~CProfileThread( );

public:

	void RunThread( std::function< bool( void ) > fCondition, std::function< void( void ) > f )
	{
		m_thread = std::thread( [ & ]{
			
			for( ;; )
			{
				if( m_bShutdownFlag == true )
				{
					break;
				}

				fCondition( );
				{
					f( );
				}
			}

		} );
	}




public:
	inline void Shutdown( )
	{
		if( m_thread.joinable( ) && !m_bShutdownFlag )
		{
			m_bShutdownFlag = true;

			m_thread.join( );
		}
		else
		{
			__debugbreak( );
		}
	}

	inline void Suspend( )
	{
		::SuspendThread( m_thread.native_handle( ) );
	}

	inline void Resume( )
	{
		::ResumeThread( m_thread.native_handle( ) );
	}

	inline void SetPriority( )
	{

	}

private:
	std::atomic< bool >		m_bShutdownFlag = false;

	std::thread				m_thread;
};