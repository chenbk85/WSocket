#include "stdafx.h"
#include "System.h"


#include "Network/Network.h"



std::unique_ptr< CSystem >	g_sys;



CSystem::CSystem( WSocket::ISystemImpl* pSystemImpl )
	: m_pSystemImpl( pSystemImpl )
{
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

bool CSystem::CreateNetwork( USHORT uPort, WSocket::Internal::INetwork** pNetworkOut )
{
	CNetwork* pNetwork = nullptr;

	try
	{
		pNetwork = new CNetwork( );

		pNetwork->CreateNetwork( uPort );
	}
	catch( std::exception e )
	{
		AddLog( char_to_wstring( e.what( ) ).c_str( ) );

		SafeDelete( pNetwork );
		return false;
	}



	*pNetworkOut = pNetwork;

	return true;
}

void CSystem::DestroyNetwork( WSocket::Internal::INetwork* pNetwork )
{
	throw std::logic_error( "The method or operation is not implemented." );
}

void CSystem::UpdateSystem( )
{
	m_pSystemProfiler->UpdateStats( );

	std::lock_guard< std::mutex > l( m_cs );

	for( auto i : m_vecNetwork )
		i->OnUpdateNetwork( );

}



void CSystem::AddLog( const wchar_t* szFormat, ... )
{
	wchar_t szMessage[ 512 ];

	va_list args;
	va_start( args, szFormat );
	if( vswprintf_s( szMessage, szFormat, args ) == _TRUNCATE )
	{
		GetClientImpl( )->OnLog( szFormat );
	}

	GetClientImpl( )->OnLog( szMessage );
}


