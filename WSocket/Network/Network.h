#pragma once

#include "Socket/ServerSocket.h"

#include "Buffer/BufferPool.h"

#include "Worker/AcceptWorker.h"

#include "User\UserManager.h"


class CNetwork : public WSocket::Internal::INetwork
{

public:
	CNetwork( WSocket::INetworkImpl* pNetImpl );
	virtual ~CNetwork( );

public:
	void CreateNetwork( USHORT uPort );
	void OnUpdateNetwork( );


protected:
	virtual WSocket::Internal::IUser* GetUserById( size_t nId ) override;

public:
	inline WSocket::INetworkImpl*	GetNetImpl( )	{ return m_pNetImpl; }
	

public:
	WSADATA		m_wsaData;

private:
	WSocket::INetworkImpl*		m_pNetImpl;

public:

	std::unique_ptr< CBufferPool >		m_pBufferPool = std::make_unique< CBufferPool >( this );

	std::unique_ptr< CServerSocket >	m_pServerSocket = std::make_unique< CServerSocket >( this );
	std::unique_ptr< CAcceptWorker >	m_pAcceptWorker = std::make_unique< CAcceptWorker >( this );

	std::unique_ptr< CUserManager >		m_pUserManager = std::make_unique< CUserManager >( this );
};