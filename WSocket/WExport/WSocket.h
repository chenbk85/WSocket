#pragma once

/*
	WSocket - WebSocket C++ Lib
	(C) Clemens Susenbeth 2015
*/


#ifndef _M_AMD64
#error WSocket can only run on x64 systems!
#endif



#ifdef WSOCKET_EXPORTS
#define WSOCKET_API __declspec(dllexport)
#else
#define WSOCKET_API __declspec(dllimport)
#endif



#include "WSocketTypes.h"


namespace WSocket
{
	WSOCKET_API bool CreateNetworkInstance( USHORT nPort, INetworkImpl* pNetImpl, _Out_ Internal::INetwork** pOutNetwork );
	WSOCKET_API void DestroyNetworkInstance( INetworkImpl* pNetImpl );

	//> This should be called every second to update the systems.	
	WSOCKET_API void TickSystems( );
}



#include "WSocketHelper.h"
#include "WSocketTemplates.h"