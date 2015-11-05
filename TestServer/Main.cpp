#include "stdafx.h"

#include "SocketSystem.h"


int main()
{
	auto pSystem = std::make_unique< CSocketSystem >( );

	if( !WSocket::InitializeWSocket( pSystem.get( ) ) )
	{
		__debugbreak( );
	}


	pSystem->CreateNetwork( );



	_gettch( );

    return 0;
}

