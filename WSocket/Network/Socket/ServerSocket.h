#pragma once


class CServerSocket
{
public:
	CServerSocket( );
	~CServerSocket( );

public:
	void CreateSocket( USHORT uPort );
	void ShutdownSocket( );


private:
	SOCKET	m_hSocket = INVALID_SOCKET;
};