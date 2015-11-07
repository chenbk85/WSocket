#include "stdafx.h"
#include "Logger.h"

#include "System/System.h"


CLogger::CLogger( )
{
}

CLogger::~CLogger( )
{
}

void CLogger::OnLog( WSocket::eLogType::e eType, const wchar_t* szMessage )
{
	sLogEntry* pEntry = new sLogEntry;
	{
		pEntry->m_eType = eType;
		wcscpy_s( pEntry->m_szMessage, szMessage );
	}
	m_queueLogs.push( pEntry );
}

void CLogger::Dispatch( )
{
	enum LogColor : int { Black = 0, DarkBlue, Green, Blue, Pink = 5, Brown, Silver, DeepSilver = 9, BrightGreen, Cyan, Red };


	sLogEntry* pEntry = nullptr;
	while( m_queueLogs.try_pop( pEntry ) )
	{
		switch( pEntry->m_eType )
		{
			case WSocket::eLogType::eSuccess:	SetConsoleTextAttribute( m_hOutput, Red );			break;
			case WSocket::eLogType::eInfo:		SetConsoleTextAttribute( m_hOutput, Green );		break;
			case WSocket::eLogType::eError:		SetConsoleTextAttribute( m_hOutput, Cyan );			break;
		}

		wprintf( L"%s\n", pEntry->m_szMessage );
		SetConsoleTextAttribute( m_hOutput, Silver );

		delete( pEntry );	//> Note: use memory pool here!
	}
}



void AddError( const wchar_t* szFormat, ... )
{
	wchar_t szMessage[ 512 ];

	va_list args;
	va_start( args, szFormat );
	if( vswprintf_s( szMessage, szFormat, args ) == _TRUNCATE )
	{
		__debugbreak( );
	}

	CSystem::GetInstance( )->GetLogger( )->OnLog( WSocket::eLogType::eError, szMessage );
}

void AddInfo( const wchar_t* szFormat, ... )
{
	wchar_t szMessage[ 512 ];

	va_list args;
	va_start( args, szFormat );
	if( vswprintf_s( szMessage, szFormat, args ) == _TRUNCATE )
	{
		__debugbreak( );
	}

	CSystem::GetInstance( )->GetLogger( )->OnLog( WSocket::eLogType::eInfo, szMessage );

}

void AddSuccess( const wchar_t* szFormat, ... )
{
	wchar_t szMessage[ 512 ];

	va_list args;
	va_start( args, szFormat );
	if( vswprintf_s( szMessage, szFormat, args ) == _TRUNCATE )
	{
		__debugbreak( );
	}

	CSystem::GetInstance( )->GetLogger( )->OnLog( WSocket::eLogType::eSuccess, szMessage );

}