#include "stdafx.h"
#include "User.h"

CUser::CUser( WSocket::IUserImpl* pUserImpl )
	: m_pUserImpl( pUserImpl )
{
	m_pUserImpl->OnSetIUser( this );
}

CUser::~CUser( )
{

}

void CUser::BindUser( size_t nId, SOCKET hSocket, sockaddr_in* pRemoteAddr )
{
	GetUserImpl( )->OnClear( );

	m_hSocket = hSocket;
	memcpy( &m_remoteAddress, pRemoteAddr, sizeof( sockaddr_in ) );


	GetUserImpl( )->OnConnect( );


}




