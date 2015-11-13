#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_ATTACH )
	{
		if( !IsWindows8OrGreater( ) )
		{
			MessageBox( nullptr, L"[WSocket] You need at least Windows 8!", L"WSocket Error!", MB_OK | MB_ICONERROR );
			return FALSE;
		}
	}
	else if( dwReason == DLL_PROCESS_DETACH )
	{

	}
	
	return TRUE;
}