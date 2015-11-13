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
	/*
	> add user stack
	*/

	CUser* pUser = CreateUser( );
	{
		size_t nId = m_nNextId.fetch_add( 1, std::memory_order::memory_order_relaxed );

		pUser->BindUser( nId, hSocket, pRemoteAddress );

		m_mapIdToUser.insert( std::make_pair( nId, pUser ) );
	}
}

CUser* CUserManager::CreateUser( )
{

	/*
	CUserBuffer:

	We merge both classes of the internal server and the exe into one:

	1 'User'
	+-------------------+------------------------+
	|   sizeof( CUser ) |   sizeof( CTestUser )  |
	+-------------------+-------------------------
	*/

	auto pNetImpl = GetNetwork( )->GetNetImpl( );
	size_t nImplSize = pNetImpl->GetUserSize( );


	BYTE* pBuffer = new BYTE[ sizeof( CUser ) + nImplSize ];
	BYTE* pBufferPos = pBuffer;


	WSocket::IUserImpl* pUserImpl = pNetImpl->ConstructUser( pBufferPos + sizeof( CUser ) );
	CUser* pUser = new ( pBufferPos )CUser( pUserImpl );


	return pUser;
}

WSocket::IUserImpl* CUserManager::UserToUserImpl( CUser* pUser )
{
	return static_cast< WSocket::IUserImpl* >(
		static_cast< void* __ptr64 >( pUser + sizeof( CUser ) )
		);
}

CUser* CUserManager::UserImplToUser( WSocket::IUserImpl* pUserImpl )
{
	return static_cast< CUser* >(
		static_cast< void* __ptr64 >( pUserImpl - sizeof( CUser ) )
		);
}

