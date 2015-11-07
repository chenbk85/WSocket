#include "stdafx.h"
#include "WSocket.h"

#include "System/System.h"


static std::once_flag		s_initFlag;

static std::atomic< bool >	s_bSysCreated = false;



bool _CheckSystemValid( )
{
	if( !s_bSysCreated.load( std::memory_order_acquire ) )
	{
		OutputDebugString( L"[WSocket] you need to initialize wsocket first!" );
		return false;
	}

	return true;
}



WSOCKET_API bool WSocket::InitializeWSocket( ILogImpl* pLogImpl )
{
	try
	{
		std::call_once( s_initFlag, [ & ]{
			g_sys = std::make_unique< CSystem >( pLogImpl );

			s_bSysCreated = true;
		} );
	}
	catch( const std::exception e )
	{
		std::wstring szMessage = L"[WSocket] " + char_to_wstring( e.what( ) );
		{
			pLogImpl->OnLog( eLogType::eError, szMessage.c_str( ) );
		}
		return false;
	}

	return true;
}



//> Note: only 'forwards' here but we have to make sure that g_sys is valid..
WSOCKET_API void WSocket::PulseSystem( )
{
	if( !_CheckSystemValid( ) )
	{
		return;
	}

	g_sys->PulseSystem( );
}

WSOCKET_API bool WSocket::CreateNetworkInstance( USHORT nPort, INetworkImpl* pNetImpl )
{
	if( !_CheckSystemValid( ) )
	{
		return false;
	}

	return g_sys->CreateNetworkInstance( nPort, pNetImpl );
}

WSOCKET_API void WSocket::DestroyNetworkInstance( INetworkImpl* pNetImpl )
{
	if( !_CheckSystemValid( ) )
	{
		return;
	}

	g_sys->DestroyNetworkInstance( pNetImpl );
}





