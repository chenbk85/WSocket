#pragma once

/*
	WSocket - WebSocket C++ Lib
	(C) Clemens Susenbeth 2015


*/





#ifdef WSOCKET_EXPORTS
#define WSOCKET_API __declspec(dllexport)
#else
#define WSOCKET_API __declspec(dllimport)
#endif



#include "WSocketTypes.h"


namespace WSocket
{
	WSOCKET_API bool InitializeWSocket( ILogImpl* pLogImpl );

	WSOCKET_API void PulseSystem( );

	WSOCKET_API bool CreateNetworkInstance( USHORT nPort, INetworkImpl* pNetImpl );
	WSOCKET_API void DestroyNetworkInstance( INetworkImpl* pNetImpl );
}



#include "WSocketHelper.h"
#include "WSocketTemplates.h"