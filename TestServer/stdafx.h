#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//=> defines

#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOC


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//=> includes

#include "targetver.h"


#include <WinSock2.h>
#include <Mswsock.h>
#include <WS2tcpip.h>

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

#include <assert.h>
#include <profileapi.h>
#include <crtdbg.h>



//=> stl
#include <string>
#include <array>
#include <algorithm>
#include <future>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>
#include <exception>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <tuple>


//ConcRT
#include <ppl.h>
#include <ppltasks.h>
#include <pplawait.h>

#include <concrt.h>
#include <concurrent_queue.h>
#include <concurrent_unordered_map.h>
#include <concurrent_vector.h>
