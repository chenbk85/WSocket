#include "stdafx.h"
#include "AcceptWorker.h"

#include "Network/Network.h"
#include "Network/Helper/WSAHelper.h"

#include "Helper/ThreadHelper.h"


#include "Profiler/Helper/FunctionMeasure.h"


CAcceptWorker::CAcceptWorker( CNetwork* pNetwork )
	: TNetworkModule( pNetwork )
{
}

CAcceptWorker::~CAcceptWorker( )
{
	CloseHandle( m_hAcceptIocp );
}

void CAcceptWorker::CreateWorker( )
{
	SOCKET hSocket = GetNetwork( )->m_pServerSocket->GetSocket( );
	WinApi::Io::CreateIoCompletionPort( reinterpret_cast< HANDLE >( hSocket ), m_hAcceptIocp, 0, 0 );

	OnUpdateModule( );

	RefillSockets( );

	m_ioThread.Run( m_hAcceptIocp, [ this ]( OVERLAPPED_ENTRY* pEntries, size_t nCount ){
		for( size_t i = 0; i < nCount; i++ )
		{
			sSocketAccept* pSocket = reinterpret_cast< sSocketAccept* >( pEntries[ i ].lpOverlapped );
			{
				GetNetwork( )->m_pUserManager->AddUser( pSocket->m_hSocket, pSocket->GetRemoteAddress( ) );
			}
		}
	} );
}

void CAcceptWorker::RefillSockets( )
{
	SOCKET hServerSocket = GetNetwork( )->m_pServerSocket->GetSocket( );


	sSocketAccept* pAcpSocket = new sSocketAccept; //> add mempool
	{
		pAcpSocket->Clear( );
	}

	pAcpSocket->m_hSocket = WSASocketW( AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP, nullptr, 0, WSA_FLAG_REGISTERED_IO );

	if( pAcpSocket->m_hSocket == INVALID_SOCKET )
	{
		AddError( __FUNCTIONW__ L" WSASocketW failed: %d", WSAGetLastError( ) );
	}

	DWORD dwBytes = 0;
	if( !g_wsa.AcceptEx( hServerSocket, pAcpSocket->m_hSocket, pAcpSocket->m_cIpBuff, 0, sizeof( sockaddr_in ) + 16, sizeof( sockaddr_in ) + 16, &dwBytes, pAcpSocket ) )
	{
		if( WSAGetLastError( ) != WSA_IO_PENDING )
		{
			AddError( L"AcceptEx failed: %d", WSAGetLastError( ) );
		}
	}
}

void CAcceptWorker::OnUpdateModule( )
{
	
	LONGLONG li = CFunctionMeasure::Measure( [ & ]( int n ){
		RefillSockets( );
	}, 0 );

	__debugbreak( );
}
