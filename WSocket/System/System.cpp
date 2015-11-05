#include "stdafx.h"
#include "System.h"

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

void CSystem::AddLog( wchar_t* szFormat, ... )
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
