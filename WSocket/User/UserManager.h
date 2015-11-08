#pragma once


class CUser;
class CUserManager
{
public:
	CUserManager( );
	~CUserManager( );

public:

	WSocket::Internal::IUser* GetUserById( size_t nId );

private:

	Concurrency::concurrent_unordered_map< size_t, CUser* >		m_mapIdToUser;

};