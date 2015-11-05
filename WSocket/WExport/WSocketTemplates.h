#pragma once


namespace WSocket
{
	template< class TUser, class TDispatcher >
	class TNetwork : public INetworkImpl
	{
		static_assert( std::is_base_of< IUserImpl, TUser >::value, "TUser must be a descendant of IUserImpl" );
		static_assert( std::is_base_of< IDispatcherImpl, TDispatcher >::value, "TDispatcher must be a descendant of IDispatcher" );

	public:
		TNetwork( )
		{
		}

		virtual ~TNetwork( )
		{
			if( m_pNetwork != nullptr )
			{
				GetSystem( )->DestroyNetwork( m_pNetwork );
			}
		}

	public:
		void CreateNetwork( USHORT nPort )
		{
			if( !GetSystem( )->CreateNetwork( nPort, &m_pNetwork ) )
			{
				throw std::runtime_error( "Failed to create network" );
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
		inline Internal::ISystem* GetSystem( )
		{
			Internal::ISystem* pSystem = nullptr;
			if( !WSocket::GetSystem( &pSystem ) )
			{
				throw std::runtime_error( "Initialize WSocket first!" );
			}

			return pSystem;
		}

	private:
		Internal::INetwork*				m_pNetwork = nullptr;

		std::unique_ptr< TDispatcher >	m_pDispatcher = std::make_unique< TDispatcher >( );
	};

}