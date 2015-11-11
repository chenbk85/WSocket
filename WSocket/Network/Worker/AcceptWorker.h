#pragma once


#include "System/SystemModule.h"

#include "Profiler/ProfileThread.h"
#include "Profiler/Helper/ProfileCompQueue.h"


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
	struct sSharedThreadData
	{
		void*	m_pMemoryPool;
	};

public:
	CAcceptWorker( CNetwork* pNetwork );
	virtual ~CAcceptWorker( );

public:
	void CreateWorker( );

public:
	void CreateSockets( );

private:
	CProfileCompThread	m_compQueue;

	//CThreadHost< sSharedThreadData >	m_threadHost;
};