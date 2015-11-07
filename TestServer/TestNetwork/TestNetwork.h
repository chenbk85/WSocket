#pragma once


#include "TestDispatcher.h"
#include "TestUser.h"

class CTestNetwork : public WSocket::TNetworkImpl< CTestUser, CTestDispatcher >
{
public:
	CTestNetwork( );
	virtual ~CTestNetwork( );

public:


};