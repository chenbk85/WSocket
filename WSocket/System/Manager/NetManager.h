#pragma once


class CNetwork;
class CNetManager
{
public:
	CNetManager( );
	~CNetManager( );
	
public:
	void RegisterNetwork( CNetwork* pNet );

	CNetwork* Find( WSocket::INetworkImpl* pNetImpl );

public:
	void ForEach( std::function< void( CNetwork* pNet ) > f )
	{
		std::lock_guard< std::mutex > l( m_cs );
		{
			for( auto& i : m_vecNetwork )
				f( i );
		}
	}

	bool IsEmpty( )
	{
		std::lock_guard< std::mutex > l( m_cs );
		return m_vecNetwork.size( ) > 0;
	}

private:
	std::mutex		m_cs;

	std::vector< CNetwork* >	m_vecNetwork;
};