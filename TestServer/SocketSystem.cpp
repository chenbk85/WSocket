#include "stdafx.h"
#include "SocketSystem.h"

CSocketSystem::CSocketSystem( )
{

}

CSocketSystem::~CSocketSystem( )
{

}

void CSocketSystem::OnLog( const wchar_t* szMessage )
{
	wprintf_s( L"%s\n", szMessage );
}

void CSocketSystem::CreateNetwork( )
{
	m_pTestNetwork.CreateNetwork( 2554 );
}
