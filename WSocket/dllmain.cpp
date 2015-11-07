#include "stdafx.h"


BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_DETACH )
	{
#ifdef _DEBUG
		/*
			Check NetworkRefCounter
		*/
#endif
	}
	
	return TRUE;
}