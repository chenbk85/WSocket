#include "stdafx.h"
#include "System.h"

std::unique_ptr< CSystem >	g_sys;


CSystem::CSystem( )
{
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
