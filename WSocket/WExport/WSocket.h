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
	WSOCKET_API bool InitializeWSocket( ISystemImpl* pSystemImpl );

}



#include "WSocketHelper.h"