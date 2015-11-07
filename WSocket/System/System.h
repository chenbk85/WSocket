#pragma once

#include "System/Misc/LogPipe.h"

#include "Profiler/SystemProfiler.h"



class CNetwork;
class CSystem 
{
public:
	CSystem( WSocket::ILogImpl* pLogImpl );
	~CSystem( );

public:
	void Initialize( );

public:
	bool CreateNetworkInstance( USHORT nPort, WSocket::INetworkImpl* pNetImpl );
	void DestroyNetworkInstance( WSocket::INetworkImpl* pNetImpl );

	void PulseSystem( );

public:


public:


private:
	WSADATA					m_wsaData;

	std::mutex				m_cs;

	
	std::vector< CNetwork* >			m_vecNetwork;

	std::unique_ptr< CLogPipe >			m_pLogPipe;

	std::unique_ptr< CSystemProfiler >	m_pSystemProfiler = std::make_unique< CSystemProfiler >( );
};


extern std::unique_ptr< CSystem >	g_sys;
