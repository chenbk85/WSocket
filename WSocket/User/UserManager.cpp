#include "stdafx.h"
#include "UserManager.h"

CUserManager::CUserManager( CNetwork* pNetwork )
	: TNetworkModule( pNetwork )
{

}

CUserManager::~CUserManager( )
{

}

WSocket::Internal::IUser* CUserManager::GetUserById( size_t nId )
{
	return nullptr;
}
