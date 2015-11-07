#pragma once


namespace WSocket
{
	template< class TUser, class TDispatcher >
	class TNetworkImpl : public INetworkImpl
	{
		static_assert( std::is_base_of< IUserImpl, TUser >::value, "TUser must be a descendant of IUserImpl" );
		static_assert( std::is_base_of< IDispatcherImpl, TDispatcher >::value, "TDispatcher must be a descendant of IDispatcher" );

	public:
		TNetworkImpl( )
		{ }

		virtual ~TNetworkImpl( )
		{
			WSocket::DestroyNetworkInstance( this );
		}

	public:
		void CreateNetwork( USHORT nPort )
		{
			if( !WSocket::CreateNetworkInstance( nPort, this ) )
			{
				throw std::runtime_error( "Failed to create network!" );
			}
		}

	public:
		virtual IUserImpl* ConstructUser( BYTE* pBuffer ) override
		{
			return new( pBuffer ) TUser( );
		}

		virtual size_t GetUserSize( ) override
		{
			return sizeof( TUser );
		}

		virtual IDispatcherImpl* GetDispatcher( ) override
		{
			return m_pDispatcher.get( );
		}

	private:
		std::unique_ptr< TDispatcher >	m_pDispatcher = std::make_unique< TDispatcher >( );
	};

}