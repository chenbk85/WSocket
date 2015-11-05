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

public:

};