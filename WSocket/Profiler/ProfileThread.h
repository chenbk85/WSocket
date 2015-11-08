#pragma once

#include "Helper/ThreadHelper.h"

class CProfileThread : CThreadHelper
{
public:
	CProfileThread( );
	~CProfileThread( );

public:
	void RunThread( std::function< void( void ) > f )
	{
		this->Run( [ & ]{

			for( ;; )
			{
				//>profiling here :)


				f( );

				//>
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

	inline void SetShutdownFlag( )
	{

	}

private:
	std::atomic< bool >		m_bShutdownFlag = false;
};


