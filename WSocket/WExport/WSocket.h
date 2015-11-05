#pragma once



#ifdef WSOCKET_EXPORTS
#define WSOCKET_API __declspec(dllexport)
#else
#define WSOCKET_API __declspec(dllimport)
#endif

#include "WSocketTypes.h"

namespace WSocket
{

}

#include "WSocketHelper.h"