#include "stdafx.h"
#include "System.h"

#include "Network/Helper/WSAHelper.h"

std::unique_ptr< CSystem >	g_sys;


CSystem::CSystem( )
{
}

CSystem::~CSystem( )
{
}

void CSystem::Initialize( )
{
	if( WSAStartup( WINSOCK_VERSION, &m_wsaData ) != 0 )
	{
		throw std::runtime_error( "Failed to load WSA" );
	}

	WSAHelper::Initialize( );

}
