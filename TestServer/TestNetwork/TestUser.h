#pragma once


class CTestUser : public WSocket::IUserImpl
{
public:
	CTestUser( );
	~CTestUser( );

public:
	virtual void OnClear( ) override;
	virtual void OnConnect( ) override;
	virtual void OnDisconnect( ) override;

	virtual void OnSetIUser( WSocket::Internal::IUser* pUser ) override
	{
		m_pIUser = pUser;
	}

public:

	WSocket::Internal::IUser*	m_pIUser = nullptr;

};