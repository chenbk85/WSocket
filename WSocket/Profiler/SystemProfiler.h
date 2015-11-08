#pragma once



#include "System/SystemModule.h"

namespace eSystemStatus {
	enum e {
		eHighLoad, eNormalLoad, eIdle
	};
}

class CSystemProfiler : public TSystemModule< CSystemProfiler >
{
public:
	CSystemProfiler( );
	~CSystemProfiler( );

public:

	void OnUpdate( );


public:
	inline const size_t GetProcessorCount( )
	{
		return static_cast< size_t >( m_systemInfo.dwNumberOfProcessors );
	}

	inline const size_t GetAllocGranularity( )
	{
		return static_cast< size_t >( m_systemInfo.dwAllocationGranularity );
	}

private:
	SYSTEM_INFO					m_systemInfo;
	MEMORYSTATUSEX				m_memoryInfo;


	PDH_HQUERY					m_cpuQuery = INVALID_HANDLE_VALUE;
	PDH_HCOUNTER				m_cpuCounter = INVALID_HANDLE_VALUE;
	PROCESS_MEMORY_COUNTERS		m_memCounter;


	std::atomic< size_t >		m_nMemoryUsed = 0;
	std::atomic< size_t >		m_nMemoryFree = 0;

	std::atomic< size_t >		m_nMemoryLoad = 0;	//=> 0% -> 100%
	std::atomic< size_t >		m_nCpuLoad;
};