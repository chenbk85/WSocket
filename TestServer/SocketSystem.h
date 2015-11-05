#pragma once


#include "TestNetwork/TestUser.h"
#include "TestNetwork/TestDispatcher.h"

class CSocketSystem : public WSocket::ISystemImpl
{
public:
	CSocketSystem( );
	~CSocketSystem( );


public:
	void CreateNetwork( );

public:
	virtual void OnLog( const wchar_t* szMessage ) override;



private:

	WSocket::TNetwork< CTestUser, CTestDispatcher >		m_pTestNetwork;
};