#pragma once


class CLogPipe
{
public:
	CLogPipe( WSocket::ILogImpl* pLogImpl );
	~CLogPipe( );

public:
	void PushMessage( WSocket::eLogType::e eType, const wchar_t* szMessage );

private:
	WSocket::ILogImpl*		m_pLogImpl;
};

void AddError( const wchar_t* szFormat, ... );
void AddSuccess( const wchar_t* szFormat, ... );
void AddInfo( const wchar_t* szFormat, ... );

//inline void AddError( const wchar_t* szFormat, ... )
//{
//	wchar_t szMessage[ 512 ];
//
//	va_list args;
//	va_start( args, szFormat );
//	if( vswprintf_s( szMessage, szFormat, args ) == _TRUNCATE )
//	{
//		GetClientImpl( )->OnLog( szFormat );
//	}
//
//	GetClientImpl( )->OnLog( szMessage );
//}
//
//inline void AddSuccess( const wchar_t* szFormat, ... )
//{
//	wchar_t szMessage[ 512 ];
//
//	va_list args;
//	va_start( args, szFormat );
//	if( vswprintf_s( szMessage, szFormat, args ) == _TRUNCATE )
//	{
//		GetClientImpl( )->OnLog( szFormat );
//	}
//
//	GetClientImpl( )->OnLog( szMessage );
//}
//
//inline void AddInfo( const wchar_t* szFormat, ... )
//{
//	wchar_t szMessage[ 512 ];
//
//	va_list args;
//	va_start( args, szFormat );
//	if( vswprintf_s( szMessage, szFormat, args ) == _TRUNCATE )
//	{
//		GetClientImpl( )->OnLog( szFormat );
//	}
//
//	GetClientImpl( )->OnLog( szMessage );
//}