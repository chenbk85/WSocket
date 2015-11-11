#include "stdafx.h"
#include "SystemProfiler.h"

CSystemProfiler::CSystemProfiler( )
{
	ZeroMemory( &m_memoryInfo, sizeof( MEMORYSTATUSEX ) );
	ZeroMemory( &m_systemInfo, sizeof( SYSTEM_INFO ) );

	m_memoryInfo.dwLength = sizeof( MEMORYSTATUSEX );

	GetSystemInfo( &m_systemInfo );


	WinApi::Psapi::_GetProcessMemoryInfo( GetCurrentProcess( ), &m_memCounter, sizeof( PROCESS_MEMORY_COUNTERS ) );

	WinApi::Pdh::OpenQuery( nullptr, NULL, &m_cpuQuery );
	WinApi::Pdh::AddEnglishCounter( m_cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &m_cpuCounter );
	WinApi::Pdh::CollectQueryData( m_cpuQuery );


	this->OnUpdate( );
}

CSystemProfiler::~CSystemProfiler( )
{
	WinApi::Pdh::CloseQuery( m_cpuQuery );
}

void CSystemProfiler::OnUpdate( )
{
	//=> Update Memory
	WinApi::SysInfo::GlobalMemoryStatusEx( &m_memoryInfo );
	m_nMemoryUsed = m_memoryInfo.ullTotalPageFile - m_memoryInfo.ullAvailPageFile;
	m_nMemoryFree = m_memoryInfo.ullAvailPageFile - m_nMemoryUsed;
	m_nMemoryLoad = m_memoryInfo.dwMemoryLoad;


	//=> Read CPU Usage
	PDH_FMT_COUNTERVALUE counterVal;
	WinApi::Pdh::CollectQueryData( m_cpuQuery );


	//=> This operation can fail 
	if( PdhGetFormattedCounterValue( m_cpuCounter, PDH_FMT_LARGE, NULL, &counterVal ) == ERROR_SUCCESS )
	{
		size_t nCpuLoad = counterVal.largeValue;
		
		if( nCpuLoad > 0 && nCpuLoad < 100 )
		{
			m_nCpuLoad = nCpuLoad;
		}
	}

	//> #todo: add QueryIdleProcessorCycleTimeEx
	//wprintf( L"Cpu: %I64d Mem: %lf > %lf\n", m_nCpuLoad.load(), ( ( double )m_nMemoryUsed ) / 1024.0, ( ( double )m_nMemoryFree ) / 1024.0 );
}
