#include "stdafx.h"
#include "ServerSocket.h"

#include "Network/Helper/WSAHelper.h"

CWSAHelper g_wsa;



CServerSocket::CServerSocket( CNetwork* pNetwork )
	: TNetworkModule( pNetwork )
{
}

CServerSocket::~CServerSocket( )
{
}

void CServerSocket::CreateSocket( USHORT uPort )
{
	m_hSocket = WinApi::WinSock::WSASocketW( AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP, nullptr, 0, WSA_FLAG_REGISTERED_IO );

	g_wsa.Initialize( m_hSocket );

	BOOL opt = TRUE;
	WinApi::WinSock::setsockopt( m_hSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast< const char* >( &opt ), sizeof( BOOL ) );

	SOCKADDR_IN addr;
	ZeroMemory( &addr, sizeof( SOCKADDR_IN ) );
	{
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons( uPort );
	}

	WinApi::WinSock::bind( m_hSocket, reinterpret_cast< SOCKADDR* >( &addr ), sizeof( SOCKADDR_IN ) );
	WinApi::WinSock::listen( m_hSocket, SOMAXCONN );
}

void CServerSocket::ShutdownSocket( )
{
	closesocket( m_hSocket );
}
