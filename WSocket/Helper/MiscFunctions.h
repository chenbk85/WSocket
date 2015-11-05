#pragma once




template< typename T >
inline void SafeDelete( T &t ) noexcept
{
	if( t != nullptr )
	{
		delete( t );
		t = nullptr;
	}
}

template< typename T >
inline void SafeDeleteArray( T &t ) noexcept
{
	if( t != nullptr )
	{
		delete[ ]( t );
		t = nullptr;
	}
}

inline void SafeCloseHandle( HANDLE &h )
{
	if( h != nullptr )
	{
		CloseHandle( h );
		h = nullptr;
	}
}

inline void SafeExitThread( HANDLE &hCloseEvent, std::thread* t )
{
	SetEvent( hCloseEvent );
	{
		if( t->joinable( ) )
		{
			t->join( );
		}
	}
	SafeCloseHandle( hCloseEvent );
}

inline std::wstring char_to_wstring( const char* szStr )
{
	std::wstring_convert< std::codecvt_utf8< wchar_t > > myconv;
	return myconv.from_bytes( szStr );
}



