#include "stdafx.h"
#include "GlobalEnvironment.h"


sGlobalEnvironment _gEnv;
sGlobalEnvironment*	gEnv = &_gEnv;

sGlobalEnvironment::sGlobalEnvironment( )
{
}

sGlobalEnvironment::~sGlobalEnvironment( )
{
	if( !m_pNetManager->IsEmpty( ) )
	{
		OutputDebugString( L"[WSocket] you need to shutdown all networks before closing!" );
		__debugbreak( );
	}
}
