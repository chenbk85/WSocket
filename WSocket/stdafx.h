#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//=> Defines

#define WIN32_LEAN_AND_MEAN             


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//=> Includes

#include "targetver.h"

//=> Winsock
#include <WinSock2.h>
#include <Mswsock.h>
#include <WS2tcpip.h>

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include <VersionHelpers.h>


//=> Profiling
#include <profileapi.h>
#include <Psapi.h>
#include <Pdh.h>

//=> Std
#include <string>
#include <array>
#include <algorithm>
#include <vector>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>
#include <exception>
#include <locale>
#include <codecvt>
#include <tuple>


//ConcRT
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>
#include <concurrent_vector.h>


//=> Own
#include "Helper/SpinLock.h"
#include "Helper/MiscClasses.h"
#include "Helper/MiscFunctions.h"
#include "Helper/SafeWinApi.h"
#include "Helper/ThreadHelper.h"




#include <WExport/WSocket.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//=> Libs

#pragma comment( lib, "Ws2_32.lib" )
#pragma comment( lib, "pdh.lib" )
