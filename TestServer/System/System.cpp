#include "stdafx.h"
#include "System.h"

CSystem::CSystem( )
{
}

CSystem::~CSystem( )
{
}

CSystem* CSystem::GetInstance( )
{
	static CSystem s_system;
	return &s_system;
}

void CSystem::CreateNetworks( )
{
	m_pTestNetwork->CreateNetwork( 2554 );

}

int CSystem::Run( )
{
	while( WaitForSingleObject( m_hCloseProcess, 1 ) != WAIT_OBJECT_0 )
	{


	}

	return EXIT_SUCCESS;
}
