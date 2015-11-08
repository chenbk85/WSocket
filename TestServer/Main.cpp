#include "stdafx.h"
#include "System/System.h"


int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
#endif

	try
	{
		CSystem::GetInstance( )->CreateNetworks( );
	}
	catch( const std::exception& e )
	{
		Beep( 600, 200 );
		printf( "\n\nError occurred on startup\n> %s\n\n", e.what( ) );

		system( "pause" );
		return EXIT_FAILURE;
	}

	return CSystem::GetInstance( )->Run( );
}

