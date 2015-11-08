#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_ATTACH )
	{
		if( !IsWindows8OrGreater( ) )
		{
			OutputDebugString( L"[WSocket] You need at least Windows 8!" );
			return FALSE;
		}
	}
	else if( dwReason == DLL_PROCESS_DETACH )
	{

	}
	
	return TRUE;
}