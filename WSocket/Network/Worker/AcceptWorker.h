#pragma once

#include "Profiler/ProfileThread.h"
#include "System/SystemModule.h"


struct sSocketAccept : public OVERLAPPED
{
	inline void Clear( )
	{
		ZeroMemory( reinterpret_cast< OVERLAPPED* >( this ), sizeof( OVERLAPPED ) );
		ZeroMemory( m_cIpBuff, sizeof( m_cIpBuff ) );
	}

	SOCKET		m_hSocket;
	char		m_cIpBuff[ 64 ];	//#Todo: add ipv6?
};


class CAcceptWorker : public TNetworkModule< CAcceptWorker >
{
public:
	CAcceptWorker( CNetwork* pNetwork );
	virtual ~CAcceptWorker( );

public:
	void CreateWorker( );

private:
	CProfileThread	m_thread;

};