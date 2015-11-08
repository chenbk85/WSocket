#pragma once


/*
	Wrapped WinAPI with exceptions
*/

namespace WinApi
{
	namespace Internal
	{
		inline void CheckBOOL_LE( BOOL bResult, const char* szFunction )
		{
			if( bResult != TRUE )
			{
				throw FormattedException( "%s failed! ( LastError: %d )", szFunction, GetLastError( ) );
			}
		}

		inline void CheckBOOL( BOOL bResult, const char* szFunction )
		{
			if( bResult != TRUE )
			{
				throw FormattedException( "%s failed!", szFunction );
			}
		}

		inline void CheckInvalidSocket( SOCKET hSocket, const char* szFunction )
		{
			if( hSocket == INVALID_SOCKET )
			{
				throw FormattedException( "%s failed! ( LastError: %d WSA: %d )", szFunction, GetLastError( ), WSAGetLastError( ) );
			}
		}	

		inline void CheckSocketError( int nResult, const char* szFunction )
		{
			if( nResult == SOCKET_ERROR )
			{
				throw FormattedException( "%s failed! ( LastError: %d WSA: %d )", szFunction, GetLastError( ), WSAGetLastError( ) );
			}
		}
		
		inline void CheckPdhStatus( PDH_STATUS pdhStatus, const char* szFunction )
		{
			if( pdhStatus != ERROR_SUCCESS )
			{
				HANDLE hPdhLibrary = INVALID_HANDLE_VALUE;
				LPSTR pMessage = nullptr;
				DWORD_PTR pArgs[ ] = { ( DWORD_PTR )"<collectionname>" };
				DWORD dwErrorCode = pdhStatus;

				hPdhLibrary = LoadLibrary( L"pdh.dll" );
				if( hPdhLibrary != nullptr )
				{
					if( FormatMessageA( FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_ARGUMENT_ARRAY,
										 hPdhLibrary, dwErrorCode, 0, ( LPSTR )&pMessage, 0, ( va_list* )pArgs )
						)
					{
						throw FormattedException( "%s failed: %x ( LastError: %d ) %s", szFunction, pdhStatus, GetLastError( ), pMessage );
					}
				}

				throw FormattedException( "%s failed: %x ( LastError: %d )", szFunction, pdhStatus, GetLastError( ) );
			}
		}
	}

	namespace Pdh
	{
		inline void OpenQuery( LPCWSTR szDataSource, DWORD_PTR dwUserData, PDH_HQUERY* phQuery )
		{
			PDH_STATUS status = ::PdhOpenQueryW( szDataSource, dwUserData, phQuery );
			{
				Internal::CheckPdhStatus( status, __FUNCTION__ );
			}
		}

		inline 	void AddEnglishCounter( PDH_HQUERY hQuery, LPCWSTR szFullCounterPath, DWORD_PTR dwUserData, PDH_HCOUNTER* phCounter )
		{
			PDH_STATUS status = ::PdhAddEnglishCounter( hQuery, szFullCounterPath, dwUserData, phCounter );
			{
				Internal::CheckPdhStatus( status, __FUNCTION__ );
			}
		}

		inline void CollectQueryData( PDH_HQUERY hQuery )
		{
			PDH_STATUS status = ::PdhCollectQueryData( hQuery );
			{
				Internal::CheckPdhStatus( status, __FUNCTION__ );
			}
		}

		inline void CloseQuery( PDH_HQUERY hQuery )
		{
			PDH_STATUS status = ::PdhCloseQuery( hQuery );
			{
				Internal::CheckPdhStatus( status, __FUNCTION__ );
			}
		}

		inline void GetFormattedCounterValue( PDH_HCOUNTER hCounter, DWORD dwFormat, LPDWORD lpdwType, PPDH_FMT_COUNTERVALUE pValue )
		{
			PDH_STATUS status = ::PdhGetFormattedCounterValue( hCounter, dwFormat, lpdwType, pValue );
			{
				Internal::CheckPdhStatus( status, __FUNCTION__ );
			}
		}
	}

	namespace Psapi
	{
		inline void _GetProcessMemoryInfo( HANDLE hProcess, PPROCESS_MEMORY_COUNTERS ppsmemCounters, DWORD cb )
		{
			BOOL bResult = ::GetProcessMemoryInfo( hProcess, ppsmemCounters, cb );
			{
				Internal::CheckBOOL_LE( bResult, __FUNCTION__ );
			}
		}

		inline void _GetPerformanceInfo( PPERFORMANCE_INFORMATION pPerformanceInformation, DWORD cb )
		{
			BOOL bResult = ::GetPerformanceInfo( pPerformanceInformation, cb );
			{
				Internal::CheckBOOL_LE( bResult, __FUNCTION__ );
			}
		}
	}

	namespace SysInfo
	{
		inline void GlobalMemoryStatusEx( MEMORYSTATUSEX* lpBuffer )
		{
			BOOL bResult = ::GlobalMemoryStatusEx( lpBuffer );
			{
				Internal::CheckBOOL_LE( bResult, __FUNCTION__ );
			}
		}
	}

	namespace WinSock
	{
		inline void bind( SOCKET hSocket, const struct sockaddr FAR* name, int namelen )
		{
			int nResult = ::bind( hSocket, name, namelen );
			{
				Internal::CheckSocketError( nResult, __FUNCTION__ );
			}
		}

		inline SOCKET WSASocket( int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo, GROUP g, DWORD dwFlags )
		{
			SOCKET hSocket = ::WSASocketW( af, type, protocol, lpProtocolInfo, g, dwFlags );
			{
				Internal::CheckInvalidSocket( hSocket, __FUNCTION__ );
			}
			return hSocket;
		}

		inline void setsockopt( SOCKET s, int level, int optname, const char FAR * optval, int optlen )
		{
			int nResult = ::setsockopt( s, level, optname, optval, optlen );
			{
				Internal::CheckSocketError( nResult, __FUNCTION__ );
			}
		}

		inline void listen( SOCKET s, int backlog )
		{
			int nResult = ::listen( s, backlog );
			{
				Internal::CheckSocketError( nResult, __FUNCTION__ );
			}
		}
		
		inline void WSAStartup( WORD wVersionRequired, WSADATA* lpWSAData )
		{
			int nResult = ::WSAStartup( wVersionRequired, lpWSAData );
			if( nResult != 0 )
			{
				throw FormattedException( __FUNCTION__ " : startup failed ( %d ) LastError: %d WSA: %d", nResult, GetLastError( ), WSAGetLastError( ) );
			}
		}
	}
}