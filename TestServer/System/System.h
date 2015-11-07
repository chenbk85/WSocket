#pragma once

#include "Logger.h"

#include "TestNetwork/TestNetwork.h"



class CSystem
{
private:
	CSystem( );
	~CSystem( );

public:
	static CSystem* GetInstance( );


public:
	void CreateNetworks( );

	int Run( );



public:
	CLogger*	GetLogger( )		{ return m_pLogger.get( ); }


private:
	HANDLE	m_hCloseProcess = CreateEvent( nullptr, FALSE, FALSE, L"" );


	std::unique_ptr< CLogger >			m_pLogger = std::make_unique< CLogger >( );

	std::unique_ptr< CTestNetwork >		m_pTestNetwork = std::make_unique< CTestNetwork >( );
};