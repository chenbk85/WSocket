#include "stdafx.h"
#include "System.h"


#include "Network/Network.h"



std::unique_ptr< CSystem >	g_sys;



CSystem::CSystem( WSocket::ILogImpl* pLogImpl )
{
	m_pLogPipe = std::make_unique< CLogPipe >( pLogImpl );

	Initialize( );
}

CSystem::~CSystem( )
{
	//=> Does this cause a deadlock? 
	WSACleanup( );
}

void CSystem::Initialize( )
{
	if( WSAStartup( WINSOCK_VERSION, &m_wsaData ) != 0 )
	{
		throw std::runtime_error( "Failed to load WSA" );
	}

}

bool CSystem::CreateNetworkInstance( USHORT nPort, WSocket::INetworkImpl* pNetImpl )
{
	return false;
}

void CSystem::DestroyNetworkInstance( WSocket::INetworkImpl* pNetImpl )
{

}

void CSystem::PulseSystem( )
{

}

//bool CSystem::CreateNetwork( USHORT uPort, WSocket::Internal::INetwork** pNetworkOut )
//{
//	CNetwork* pNetwork = nullptr;
//
//	try
//	{
//		pNetwork = new CNetwork( );
//
//		pNetwork->CreateNetwork( uPort );
//	}
//	catch( std::exception e )
//	{
//		AddLog( char_to_wstring( e.what( ) ).c_str( ) );
//
//		SafeDelete( pNetwork );
//		return false;
//	}
//
//
//
//	*pNetworkOut = pNetwork;
//
//	return true;
//}
//
//




