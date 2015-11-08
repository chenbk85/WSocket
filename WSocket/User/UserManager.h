#pragma once


#include "System/SystemModule.h"

class CUser;
class CUserManager : public TNetworkModule< CUserManager >
{
public:
	CUserManager( CNetwork* pNetwork );
	~CUserManager( );

public:

	WSocket::Internal::IUser* GetUserById( size_t nId );

private:

	Concurrency::concurrent_unordered_map< size_t, CUser* >		m_mapIdToUser;

};