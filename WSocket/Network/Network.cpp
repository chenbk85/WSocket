#include "stdafx.h"
#include "Network.h"

CNetwork::CNetwork( WSocket::INetworkImpl* pNetImpl )
	: m_pNetImpl( pNetImpl )
{
	WinApi::WinSock::WSAStartup( WINSOCK_VERSION, &m_wsaData );

}

CNetwork::~CNetwork( )
{
	WSACleanup( );

}

void CNetwork::CreateNetwork( USHORT uPort )
{


}

void CNetwork::OnUpdateNetwork( )
{

}

WSocket::Internal::IUser* CNetwork::GetUserById( size_t nId )
{
	return nullptr;
}
