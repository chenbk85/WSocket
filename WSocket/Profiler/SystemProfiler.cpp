#include "stdafx.h"
#include "SystemProfiler.h"

CSystemProfiler::CSystemProfiler( )
{
	ZeroMemory( &m_systemMemInfo, sizeof( MEMORYSTATUSEX ) );
	ZeroMemory( &m_systemInfo, sizeof( SYSTEM_INFO ) );

	m_systemMemInfo.dwLength = sizeof( MEMORYSTATUSEX );

	GetSystemInfo( &m_systemInfo );


	//=> Get Pdh
	if( !GetProcessMemoryInfo( GetCurrentProcess( ), &m_memCounter, sizeof( PROCESS_MEMORY_COUNTERS ) ) )
	{
		throw std::runtime_error( __FUNCTION__ " Failed to GetProcessMemoryInfo!" );
	}

	if( PdhOpenQuery( nullptr, NULL, &m_cpuQuery ) != ERROR_SUCCESS )
	{
		throw std::runtime_error( __FUNCTION__ " Failed to open PdhQuery" );
	}

	if( PdhAddEnglishCounter( m_cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &m_cpuCounter ) != ERROR_SUCCESS )
	{
		throw std::runtime_error( __FUNCTION__ " Failed to AddEnglishCounter" );
	}

	if( PdhCollectQueryData( m_cpuQuery ) != ERROR_SUCCESS )
	{
		throw std::runtime_error( __FUNCTION__ " CollectQueryData" );
	}

	
	this->UpdateStats( );
}

CSystemProfiler::~CSystemProfiler( )
{
	if( m_cpuQuery )
	{
		PdhCloseQuery( m_cpuQuery );
	}

}

void CSystemProfiler::UpdateStats( )
{
	//=> Update Memory
	GlobalMemoryStatusEx( &m_systemMemInfo );
	m_nMemoryUsed = m_systemMemInfo.ullTotalPageFile - m_systemMemInfo.ullAvailPageFile;

	//=> Read CPU Usage
	PDH_FMT_COUNTERVALUE counterVal;
	PdhCollectQueryData( m_cpuQuery );
	PdhGetFormattedCounterValue( m_cpuCounter, PDH_FMT_DOUBLE, NULL, &counterVal );
	double d = counterVal.doubleValue;


	return;
}
