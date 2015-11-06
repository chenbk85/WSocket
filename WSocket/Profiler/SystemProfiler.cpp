#include "stdafx.h"
#include "SystemProfiler.h"

CSystemProfiler::CSystemProfiler( )
{
	ZeroMemory( &m_systemMemInfo, sizeof( MEMORYSTATUSEX ) );
	ZeroMemory( &m_systemInfo, sizeof( SYSTEM_INFO ) );

	m_systemMemInfo.dwLength = sizeof( MEMORYSTATUSEX );

	GetSystemInfo( &m_systemInfo );


	WinApi::Psapi::_GetProcessMemoryInfo( GetCurrentProcess( ), &m_memCounter, sizeof( PROCESS_MEMORY_COUNTERS ) );

	WinApi::Pdh::OpenQuery( nullptr, NULL, &m_cpuQuery );
	WinApi::Pdh::AddEnglishCounter( m_cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &m_cpuCounter );
	WinApi::Pdh::CollectQueryData( m_cpuQuery );


	this->UpdateStats( );
}

CSystemProfiler::~CSystemProfiler( )
{
	WinApi::Pdh::CloseQuery( m_cpuQuery );


}

void CSystemProfiler::UpdateStats( )
{
	for( ;; ){

		//=> Update Memory
		WinApi::SysInfo::GlobalMemoryStatusEx( &m_systemMemInfo );
		m_nMemoryUsed = m_systemMemInfo.ullTotalPageFile - m_systemMemInfo.ullAvailPageFile;

		//=> Read CPU Usage
		PDH_FMT_COUNTERVALUE counterVal;
		WinApi::Pdh::CollectQueryData( m_cpuQuery );

		if( PdhGetFormattedCounterValue( m_cpuCounter, PDH_FMT_DOUBLE, NULL, &counterVal ) != ERROR_SUCCESS ||
			counterVal.doubleValue == 0.0 ||
			counterVal.doubleValue == 100.0
			
			)
		{
		}
		else
		{
			double d = counterVal.doubleValue;
			wprintf( L"%lf Mem: %lf \n", d, ( (double)m_nMemoryUsed ) / 1024.0  );
		}



		Sleep( 100 );
	}

	return;
}
