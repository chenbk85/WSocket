#pragma once


#include "TestDispatcher.h"
#include "TestUser.h"

class CTestNetwork : public WSocket::TNetworkImpl< CTestUser, CTestDispatcher >
{
public:
	CTestNetwork( );
	virtual ~CTestNetwork( );


public:

	virtual void OnLog( WSocket::eLogType::e eType, const wchar_t* szMessage ) override;


};