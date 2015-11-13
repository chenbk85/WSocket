#pragma once

#include "System/SystemModule.h"

#include "System/Threading/ThreadHost.h"




struct sSocketAccept : public OVERLAPPED
{
	inline void Clear( )
	{
		ZeroMemory( reinterpret_cast< OVERLAPPED* >( this ), sizeof( OVERLAPPED ) );
		ZeroMemory( m_cIpBuff, sizeof( m_cIpBuff ) );
	}

	inline sockaddr_in* GetLocalAddress( ) noexcept
	{
		return reinterpret_cast< sockaddr_in* >( m_cIpBuff );
	}

	inline sockaddr_in* GetRemoteAddress( ) noexcept
	{
		return reinterpret_cast< sockaddr_in* >( &m_cIpBuff[ sizeof( sockaddr_in ) + 16 ] );
	}

	SOCKET		m_hSocket;
	char		m_cIpBuff[ 64 ];	//#Todo: add ipv6?
};


class CAcceptWorker : public TNetworkModule< CAcceptWorker > //public IUpdateImpl
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
	void RefillSockets( );


	void OnUpdateModule( );

private:
	HANDLE		m_hAcceptIocp = WinApi::Io::CreateIoCompletionPort( INVALID_HANDLE_VALUE, nullptr, 0, 0 );

	CIoThread	m_ioThread;
};