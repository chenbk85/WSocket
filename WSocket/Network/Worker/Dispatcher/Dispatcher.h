#pragma once

#include "System/SystemModule.h"


class CDispatcher : public TNetworkModule< CDispatcher >
{
public:
	CDispatcher( CNetwork* pNetwork );
	virtual ~CDispatcher( );

public:


private:
	//Concurrency::concurrent_queue< 
};