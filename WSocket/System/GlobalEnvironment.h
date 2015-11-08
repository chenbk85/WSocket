#pragma once



#include "System/Misc/NetManager.h"

#include "Profiler/SystemProfiler.h"



struct sGlobalEnvironment
{
	sGlobalEnvironment( );
	~sGlobalEnvironment( );


	std::unique_ptr< CNetManager >		m_pNetManager  = std::make_unique< CNetManager >( );
	std::unique_ptr< CSystemProfiler >	m_pSystemProfiler = std::make_unique< CSystemProfiler >( );

};



extern sGlobalEnvironment*	gEnv;