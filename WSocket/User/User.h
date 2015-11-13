#pragma once


class CUser : public WSocket::Internal::IUser
{
public:
	CUser( );
	virtual ~CUser( );


public:

	virtual size_t GetId( ) override;



private:
	size_t		m_nId;

};