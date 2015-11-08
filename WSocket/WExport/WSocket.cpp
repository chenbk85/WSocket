#include "stdafx.h"
#include "WSocket.h"

#include "Network/Network.h"

#include "System/GlobalEnvironment.h"





WSOCKET_API bool WSocket::CreateNetworkInstance( USHORT nPort, INetworkImpl* pNetImpl, Internal::INetwork** pOutNetwork )
{
	CNetwork* pNetwork = nullptr;
	try
	{
		pNetwork = new CNetwork( pNetImpl );
		{
			pNetwork->CreateNetwork( nPort );
		}

		gEnv->m_pNetManager->RegisterNetwork( pNetwork );
	}
	catch( const std::exception& e )
	{
		SafeDelete( pNetwork );
		pNetImpl->OnLog( eLogType::eError, char_to_wstring( e.what( ) ).c_str( ) );

		return false;
	}

	*pOutNetwork = pNetwork;

	return true;
}

WSOCKET_API void WSocket::DestroyNetworkInstance( INetworkImpl* pNetImpl )
{
	auto pNetwork = gEnv->m_pNetManager->Find( pNetImpl );
	if( pNetwork != nullptr )
	{
		SafeDelete( pNetwork );
	}
}

WSOCKET_API void WSocket::TickSystems( )
{
	gEnv->m_pSystemProfiler->OnUpdate( );

	gEnv->m_pNetManager->ForEach( [ ]( CNetwork* pNet ){
		pNet->OnUpdateNetwork( );
	} );
}




