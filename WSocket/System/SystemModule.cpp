#include "stdafx.h"
#include "SystemModule.h"

#include "Network/Network.h"



CNetworkModule::CNetworkModule( CNetwork* pNetwork, ISystemModule* pModule )
	: m_pNetwork( pNetwork ), m_pModule( pModule )
{
}

CNetworkModule::~CNetworkModule( )
{
}


void CNetworkModule::AddError( const wchar_t* szFormat, ... )
{
	va_list args;
	va_start( args, szFormat );
	{
		AddLog( WSocket::eLogType::eError, szFormat, args );
	}
}

void CNetworkModule::AddInfo( const wchar_t* szFormat, ... )
{
	va_list args;
	va_start( args, szFormat );
	{
		AddLog( WSocket::eLogType::eInfo, szFormat, args );
	}
}

void CNetworkModule::AddSuccess( const wchar_t* szFormat, ... )
{
	va_list args;
	va_start( args, szFormat );
	{
		AddLog( WSocket::eLogType::eSuccess, szFormat, args );
	}
}


void CNetworkModule::AddLog( WSocket::eLogType::e eType, const wchar_t* szFormat, va_list args )
{
	wchar_t szMessage[ 512 ];

	if( vswprintf_s( szMessage, szFormat, args ) == _TRUNCATE )
	{
		OutputDebugString( __FUNCTIONW__ L" Buffer too small!" );
		__debugbreak( );
	}

	//> #todo ??{ replace by std::string? }??
	wchar_t szOutput[ 512 ] = { 0, };

	wcscat_s( szOutput, m_pModule->GetModuleName( ) );
	wcscat_s( szOutput, L": " );
	wcscat_s( szOutput, szMessage );

	
	GetNetwork( )->GetNetImpl( )->OnLog( eType, szOutput );
}
