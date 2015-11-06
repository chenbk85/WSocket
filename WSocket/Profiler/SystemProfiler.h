#pragma once


class CSystemProfiler
{
public:
	CSystemProfiler( );
	~CSystemProfiler( );

public:

	void UpdateStats( );


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
	SYSTEM_INFO		m_systemInfo;
	MEMORYSTATUSEX	m_systemMemInfo;
	size_t			m_nMemoryUsed = 0;

	PDH_HQUERY					m_cpuQuery = INVALID_HANDLE_VALUE;
	PDH_HCOUNTER				m_cpuCounter = INVALID_HANDLE_VALUE;
	PROCESS_MEMORY_COUNTERS		m_memCounter;

};