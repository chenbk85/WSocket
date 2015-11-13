#pragma once


#include "System/SystemModule.h"

class CUser;
class CUserManager : public TNetworkModule< CUserManager >
{
public:
	CUserManager( CNetwork* pNetwork );
	virtual ~CUserManager( );

public:
	void	AddUser( SOCKET hSocket, sockaddr_in* pRemoteAddress );
	CUser*	CreateUser( );


public:
	WSocket::IUserImpl*		UserToUserImpl( CUser* pUser );
	CUser*					UserImplToUser( WSocket::IUserImpl* pUserImpl );


public:
	inline CUser* GetUserById( size_t nId )
	{
		auto it = m_mapIdToUser.find( nId );
		return it != m_mapIdToUser.end( ) ? it->second : nullptr;
	}

	inline WSocket::IUserImpl* GetuserImplById( size_t nId )
	{
		CUser* pUser = GetUserById( nId );
		return pUser != nullptr ? UserToUserImpl( pUser ) : nullptr;
	}


private:
	std::atomic< size_t >	m_nNextId = 0;

	Concurrency::concurrent_unordered_map< size_t, CUser* >		m_mapIdToUser;

};