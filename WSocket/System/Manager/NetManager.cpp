#include "stdafx.h"
#include "NetManager.h"

#include "Network/Network.h"


CNetManager::CNetManager( )
{

}

CNetManager::~CNetManager( )
{
	for( auto i : m_vecNetwork )
		delete( i );

}

void CNetManager::RegisterNetwork( CNetwork* pNet )
{
	std::lock_guard< std::mutex > l( m_cs );

	if( std::find( m_vecNetwork.begin( ), m_vecNetwork.end( ), pNet ) != m_vecNetwork.end( ) )
	{
		throw std::runtime_error( "Network already registered!" );
	}

	m_vecNetwork.push_back( pNet );
}

CNetwork* CNetManager::Find( WSocket::INetworkImpl* pNetImpl )
{
	std::lock_guard< std::mutex > l( m_cs );

	for( auto i : m_vecNetwork )
	{
		if( i->GetNetImpl( ) == pNetImpl )
			return i;
	}

	return nullptr;
}
