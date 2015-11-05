#include "stdafx.h"
#include "ServerSocket.h"

#include "Network/Helper/WSAHelper.h"



CServerSocket::CServerSocket( )
{
}

CServerSocket::~CServerSocket( )
{
}

void CServerSocket::CreateSocket( USHORT uPort )
{
	

}

void CServerSocket::ShutdownSocket( )
{
	closesocket( m_hSocket );
}
