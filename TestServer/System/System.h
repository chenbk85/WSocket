#pragma once


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


private:
	HANDLE	m_hCloseProcess = CreateEvent( nullptr, FALSE, FALSE, L"" );


	std::unique_ptr< CTestNetwork >		m_pTestNetwork = std::make_unique< CTestNetwork >( );
};