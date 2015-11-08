#pragma once

#include "System/SystemModule.h"

class CServerSocket : public TNetworkModule< CServerSocket >
{
public:
	CServerSocket( CNetwork* pNetwork );
	~CServerSocket( );

public:
	void CreateSocket( USHORT uPort );
	void ShutdownSocket( );


public:
	inline const SOCKET	GetSocket( ) const { return m_hSocket; }

private:
	SOCKET	m_hSocket = INVALID_SOCKET;
};