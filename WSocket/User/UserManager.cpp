#include "stdafx.h"
#include "UserManager.h"

#include "Network/Network.h"

#include "User/User.h"


CUserManager::CUserManager( CNetwork* pNetwork )
	: TNetworkModule( pNetwork )
{

}

CUserManager::~CUserManager( )
{

}

void CUserManager::AddUser( SOCKET hSocket, sockaddr_in* pRemoteAddress )
{
	CUser* pUser = CreateUser( );
	/*
		> add user stack
	*/

}

CUser* CUserManager::CreateUser( )
{
	auto pNetImpl = GetNetwork( )->GetNetImpl( );
	BYTE* pBuffer = new BYTE[ sizeof( CUser ) + pNetImpl->GetUserSize() ];
	BYTE* pBufferPos = pBuffer;

	CUser* pUser = new ( pBufferPos )CUser;		pBufferPos += sizeof( CUser );
	auto pUserImpl = pNetImpl->ConstructUser( pBufferPos );


	return pUser;
}

WSocket::Internal::IUser* CUserManager::GetUserById( size_t nId )
{
	return nullptr;
}
