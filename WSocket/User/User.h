#pragma once

namespace eConnectionState{
	enum e{
		eHandshake, eConnected
	};
}

class CUser : public WSocket::Internal::IUser
{
public:
	CUser( WSocket::IUserImpl* pUserImpl );
	virtual ~CUser( );


public:
	void BindUser( size_t nId, SOCKET hSocket, sockaddr_in* pRemoteAddr );

public:
	virtual const size_t		GetId( ) override				{ return m_nId; }
	virtual const sockaddr_in*	GetRemoteAddress( ) override	{ return &m_remoteAddress; }


public:
	inline WSocket::IUserImpl*	GetUserImpl( )		{ return m_pUserImpl; }



private:
	WSocket::IUserImpl*		m_pUserImpl;



	size_t				m_nId;
	SOCKET				m_hSocket;
	sockaddr_in			m_remoteAddress;

};