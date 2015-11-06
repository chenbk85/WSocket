#include "stdafx.h"
#include "WSocket.h"

#include "System/System.h"


static std::once_flag	s_initFlag;


WSOCKET_API bool WSocket::InitializeWSocket( ISystemImpl* pSystemImpl )
{
	assert( pSystemImpl != nullptr );

	try
	{
		std::call_once( s_initFlag, [ & ]{
			g_sys = std::make_unique< CSystem >( pSystemImpl );
		} );
	}
	catch( std::exception e )
	{
		std::wstring szMessage = L"[WSocket] Failed to create System! " + char_to_wstring( e.what( ) );
		{
			pSystemImpl->OnLog( szMessage.c_str( ) );
		}
		return false;
	}

	return true;
}

WSOCKET_API bool WSocket::GetSystem( Internal::ISystem** pOutSystem )
{
	if( g_sys.get( ) == nullptr )
	{
		OutputDebugString( L"Initialize WSocket first! \n" );
		return false;
	}

	*pOutSystem = g_sys.get( );

	return true;
}
