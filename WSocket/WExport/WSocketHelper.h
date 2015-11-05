#pragma once


namespace WSocket
{

	/*
		WSocket Buffer Read/Write Helpers:
		-> Change this to your needs. (Don't forget to change WSocket.js too!)

		Structure:
		+--------------------+--------------------+
		| 1 byte( PacketId ) | n bytes PacketData |
		+--------------------+--------------------+

	*/

	/*class CNetPacket
	{
	public:
		WSOCKET_API CNetPacket( sNetBuffer* pBuffer );
		WSOCKET_API CNetPacket( sNetResult* pResult, ULONG nBufferOffset );

	public:
		inline CNetPacket& operator << ( UCHAR n ) { return WriteVar( n ); }
		inline CNetPacket& operator << ( USHORT n ) { return WriteVar( n ); }
		inline CNetPacket& operator << ( UINT n ) { return WriteVar( n ); }
		inline CNetPacket& operator << ( size_t n ) { return WriteVar( n ); }

		inline CNetPacket& operator << ( float f )
		{
			UINT _f;
			memcpy( &_f, &f, sizeof( float ) );
			{
				WriteVar( _f );
			}
			return *this;
		}

		inline CNetPacket& operator << ( double d )
		{
			UINT64 _d;
			memcpy( &_d, &d, sizeof( double ) );
			{
				WriteVar( _d );
			}
			return *this;
		}

		inline CNetPacket& operator << ( const char* szStr )
		{
			size_t nStrLen = strlen( szStr );
#ifdef _DEBUG
			if( nStrLen > 1024 )
			{
				__debugbreak( );
			}
#endif
			*this << static_cast< USHORT >( nStrLen );

			return RawWrite( szStr, nStrLen );
		}

		inline CNetPacket& RawStringWrite( const char* szStr )
		{
			return RawWrite( szStr, strlen( szStr ) );
		}

		inline CNetPacket& RawStringWrite( const char* szStr, size_t nLen )
		{
			return RawWrite( szStr, nLen );
		}

		inline CNetPacket& RawWrite( const void* pBuffer, size_t nLen )
		{
			WriteCheckBound( nLen );
			{
				memcpy_s( m_pBuffPos, GetRemainSize( ), pBuffer, nLen );
				m_pBuffPos += nLen;
			}
			return *this;

		}

	private:
		template< typename T >
		CNetPacket& WriteVar( T t )
		{
			WriteCheckBound( sizeof( T ) );
			{
				*( T* )m_pBuffPos = t;
				m_pBuffPos += sizeof( T );
			}
			return *this;
		}

	public:
		template< size_t _S >
		inline CNetPacket ReadString( char( &szStr )[ _S ], size_t nLen )
		{
			if( nLen > _S )
			{
				nLen = _S;
			}

			ReadCheckBound( nLen );

			memcpy( szStr, m_pBuffPos, nLen );
			m_pBuffPos += nLen;

			return *this;
		}



	public:
		inline sNetBuffer* GetBuffer( )
		{
			EnsureWrite( );

			return m_source.pBuffer;
		}

		inline size_t GetRemainSize( )
		{
			return ( m_pBuffEnd - m_pBuffPos );
		}

		inline size_t GetUsedSize( )
		{
			return ( m_pBuffPos - m_pBuffBegin );
		}

	private:
		inline void WriteCheckBound( size_t n )
		{
			EnsureWrite( );

			if( GetRemainSize( ) < n )
			{
				__debugbreak( );
			}
		}

		inline void ReadCheckBound( size_t n )
		{
			EnsureRead( );

			if( GetRemainSize( ) < n )
			{
				__debugbreak( );
			}
		}

		inline void EnsureRead( )
		{
			if( !m_bRead )
			{
				__debugbreak( );
			}
		}

		inline void EnsureWrite( )
		{
			if( m_bRead )
			{
				__debugbreak( );
			}
		}

	private:
#ifdef _DEBUG
		bool	m_bRead;
#endif

		char*	m_pBuffBegin;
		char*	m_pBuffPos;
		char*	m_pBuffEnd;

		union {
			sNetBuffer* pBuffer;
			sNetResult* pResult;
		} m_source;
	};*/


	class CNetworkPacket
	{

	};

	class CPacketSelector
	{
		typedef std::function< void( IUserImpl* pUser, CNetworkPacket* pPacket ) >	tDispFunc;

	public:
		CPacketSelector( )
		{
			m_arrFuncs.assign( nullptr );
		}

		~CPacketSelector( )
		{

		}

	public:
		inline void AddHandler( BYTE bPacketId, tDispFunc fnHandler )
		{
			if( m_arrFuncs[ bPacketId ] )
			{
				throw std::runtime_error( "PacketId already registered" );
			}

			m_arrFuncs[ bPacketId ] = fnHandler;
		}




	protected:

		std::array< tDispFunc, 0xFF >	m_arrFuncs;
	};



}