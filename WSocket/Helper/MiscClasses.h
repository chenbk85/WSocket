#pragma once



class FormattedException : public std::exception
{
public:
	FormattedException( char* szFormat, ... )
	{
		char szMessage[ 512 ];

		va_list args;
		va_start( args, szFormat );
		if( vsprintf_s( szMessage, szFormat, args ) == _TRUNCATE )
		{
			__debugbreak( );
		}

		__super::exception( ( const char* )szMessage );
	}
};



inline void _assert_with_exception( const char* szExpression, const char* szFile, size_t nLineNum )
{
	__debugbreak( );
	throw FormattedException( "Expression failed! %s, (%s:%I64d)", szExpression, szFile, nLineNum );
}

#ifndef assert
#ifdef _DEBUG
#define assert(expression) (void)(                                                       \
            (!!(expression)) ||                                                              \
            (_assert_with_exception((#expression), (__FILE__), (size_t)(__LINE__)), 0) \
        )
#else
#define assert(expression) ((void)0)
#endif
#endif