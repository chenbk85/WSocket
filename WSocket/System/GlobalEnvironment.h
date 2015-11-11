#pragma once



#include "System/Manager/NetManager.h"

#include "Profiler/SystemProfiler.h"


#include "System/Threading/ThreadManager.h"


struct sGlobalEnvironment
{
	sGlobalEnvironment( );
	~sGlobalEnvironment( );


	std::unique_ptr< CNetManager >		m_pNetManager  = std::make_unique< CNetManager >( );
	std::unique_ptr< CSystemProfiler >	m_pSystemProfiler = std::make_unique< CSystemProfiler >( );


	std::unique_ptr< CThreadManager >	m_pThreadManager = std::make_unique< CThreadManager >( );
};



extern sGlobalEnvironment*	gEnv;