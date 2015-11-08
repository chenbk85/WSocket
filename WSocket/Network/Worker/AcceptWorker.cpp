#include "stdafx.h"
#include "AcceptWorker.h"

#include "Network/Network.h"
#include "Network/Helper/WSAHelper.h"

#include "Helper/ThreadHelper.h"

CAcceptWorker::CAcceptWorker( CNetwork* pNetwork )
	: TNetworkModule( pNetwork )
{
}

CAcceptWorker::~CAcceptWorker( )
{

}

void CAcceptWorker::CreateWorker( )
{
	SOCKET hSocket = GetNetwork( )->m_pServerSocket->GetSocket( );

	HANDLE		m_hAcceptIocp = CreateIoCompletionPort( INVALID_HANDLE_VALUE, nullptr, 0, 0 );
	CreateIoCompletionPort( reinterpret_cast< HANDLE >( hSocket ), m_hAcceptIocp, 0, 0 );


// 	HANDLE hIoCp = INVALID_HANDLE_VALUE;
// 
// 	static const ULONG MAX_OVERLAPPED_RESULTS = 1024;
// 	OVERLAPPED_ENTRY* pEntries = new OVERLAPPED_ENTRY[ MAX_OVERLAPPED_RESULTS ];
// 	ULONG nRemoved = 0;


	m_compQueue.Run( INVALID_HANDLE_VALUE, 100, [ ]( OVERLAPPED_ENTRY* pEntry, size_t nCount ){
	
	} );


	//m_thread.RunThread( [ & ]{ 
	//	if( !GetQueuedCompletionStatusEx( hIoCp, pEntries, MAX_OVERLAPPED_RESULTS, &nRemoved, 100, FALSE ) )
	//	{
	//		/*??{
	//			if( this->IsCanceled() )
	//				return false;
	//		}??*/
	//	}
	//}, [ & ]{ 
	//	//for( size_t i = 0; i < )
	//
	//	/*??{
	//		SwitchTLS()-> >>ThreadContext??
	//	}??*/
	//} );

	/*
	
	m_threadWorker = std::thread( [ & ]{
		static const size_t s_nMaxResults = 128;
		static const size_t s_nReserveLimit = 60;

		size_t nAccepted = 0;


		OVERLAPPED_ENTRY* pEntries = new OVERLAPPED_ENTRY[ s_nMaxResults ];
		ULONG nRemoved = 0;

		for( ;; )
		{
			if( !GetQueuedCompletionStatusEx( m_hAcceptIocp, pEntries, s_nMaxResults, &nRemoved, INFINITE, FALSE ) )
			{
				GetServer( )->GetClient( )->OnLog( L"AcceptWorker - shutting down!" );
			}

			for( ULONG i = 0; i < nRemoved; i++ )
			{
				sSocketAccept* pSocket = reinterpret_cast< sSocketAccept* >( pEntries[ i ].lpOverlapped );
				{
					GetServer( )->GetUserManager( )->AddUser( pSocket->m_hSocket, pSocket->GetRemoteAddress( ) );
				}
				m_poolSockets.Push( pSocket );
			}

			if( nAccepted + static_cast< size_t > ( nRemoved ) > s_nReserveLimit )
			{
				CreateSockets( );
				nAccepted = 0;
			}
			else
			{
				nAccepted += nRemoved;
			}
		}

		SafeDeleteArray( pEntries );
	} );




	*/
}

void CAcceptWorker::CreateSockets( )
{
	SOCKET hServerSocket = GetNetwork( )->m_pServerSocket->GetSocket( );


	sSocketAccept* pAcpSocket = new sSocketAccept;
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
