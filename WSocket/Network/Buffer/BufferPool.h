#pragma once

#include "NetworkBuffer.h"

#include "System/SystemModule.h"

class CBufferPool : public TNetworkModule< CBufferPool >
{
public:
	CBufferPool( CNetwork* pNetwork );
	~CBufferPool( );

public:



};