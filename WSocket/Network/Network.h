#pragma once

#include "Socket/ServerSocket.h"

#include "Buffer/BufferPool.h"

#include "User\UserManager.h"

class CNetwork : public WSocket::Internal::INetwork
{

public:
	CNetwork( );
	virtual ~CNetwork( );

public:
	void CreateNetwork( USHORT uPort );


public:
	std::unique_ptr< CBufferPool >		m_pBufferPool = std::make_unique< CBufferPool >( );

	std::unique_ptr< CServerSocket >	m_pServerSocket = std::make_unique< CServerSocket >( );


	std::unique_ptr< CUserManager >		m_pUserManager = std::make_unique< CUserManager >( );
};