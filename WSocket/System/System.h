#pragma once

#include "Profiler/SystemProfiler.h"


class CSystem : public WSocket::Internal::ISystem
{
public:
	CSystem(WSocket::ISystemImpl* pSystemImpl );
	~CSystem( );

public:
	void Initialize( );

public:

	virtual bool CreateNetwork( USHORT uPort, WSocket::Internal::INetwork** pNetworkOut ) override;
	virtual void DestroyNetwork( WSocket::Internal::INetwork* pNetwork ) override;

	virtual void UpdateSystem( ) override;


public:
	void AddLog( wchar_t* szFormat, ... );


public:

	inline WSocket::ISystemImpl* GetClientImpl( ) { return m_pSystemImpl; }


private:
	WSADATA					m_wsaData;
	WSocket::ISystemImpl*	m_pSystemImpl;


	std::unique_ptr< CSystemProfiler>	m_pSystemProfiler = std::make_unique< CSystemProfiler >( );
};


extern std::unique_ptr< CSystem >	g_sys;
