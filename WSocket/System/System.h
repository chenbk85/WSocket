#pragma once

#include "Profiler/SystemProfiler.h"


class CSystem
{
public:
	CSystem( );
	~CSystem( );

public:
	void Initialize( );

public:

private:
	WSADATA		m_wsaData;


	std::unique_ptr< CSystemProfiler>	m_pSystemProfiler = std::make_unique< CSystemProfiler >( );
};


extern std::unique_ptr< CSystem >	g_sys;
