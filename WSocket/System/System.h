#pragma once

#include "Profiler/SystemProfiler.h"


class CSystem
{
public:
	CSystem(WSocket::ISystemImpl* pSystemImpl );
	~CSystem( );

public:
	void Initialize( );

	void AddLog( wchar_t* szFormat, ... );

public:


	inline WSocket::ISystemImpl* GetClientImpl( ) { return m_pSystemImpl; }

private:
	WSADATA					m_wsaData;
	WSocket::ISystemImpl*	m_pSystemImpl;


	std::unique_ptr< CSystemProfiler>	m_pSystemProfiler = std::make_unique< CSystemProfiler >( );
};


extern std::unique_ptr< CSystem >	g_sys;
