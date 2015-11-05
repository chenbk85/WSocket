#pragma once


class CWSAHelper
{
public:
	void Initialize( SOCKET hSocket )
	{
		m_fnAcceptEx = nullptr;
		ZeroMemory( &m_rioTable, sizeof( RIO_EXTENSION_FUNCTION_TABLE ) );


		static std::once_flag _initFlag;
		std::call_once( _initFlag, [ & ]{ 

			InitializeRIO( hSocket );
			InitializeAcceptEx( hSocket );

		} );
	}
		
private:
	inline void InitializeRIO( SOCKET hSocket )
	{
		GUID guid = WSAID_MULTIPLE_RIO;

		DWORD dwBytes = 0;
		if( WSAIoctl( hSocket, SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER, &guid, sizeof( GUID ), reinterpret_cast< void* >( &m_rioTable ), sizeof( RIO_EXTENSION_FUNCTION_TABLE ), &dwBytes, nullptr, nullptr ) == INVALID_SOCKET )
		{
			throw FormattedException( __FUNCTION__ " failed, WSA: %d, LastError: %d", WSAGetLastError( ), GetLastError( ) );
		}
	}

	inline void InitializeAcceptEx( SOCKET hSocket )
	{
		GUID guid = WSAID_ACCEPTEX;

		DWORD dwBytes = 0;
		if( WSAIoctl( hSocket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof( GUID ), &m_fnAcceptEx, sizeof( m_fnAcceptEx ), &dwBytes, nullptr, nullptr ) == INVALID_SOCKET )
		{
			throw FormattedException( __FUNCTION__ " failed, WSA: %d, LastError: %d", WSAGetLastError( ), GetLastError( ) );
		}
	}

public:
	inline BOOL RIOReceive( RIO_RQ SocketQueue, PRIO_BUF pData, ULONG DataBufferCount, DWORD Flags, PVOID RequestContext )
	{
		return m_rioTable.RIOReceive( SocketQueue, pData, DataBufferCount, Flags, RequestContext );
	}

	inline int RIOReceiveEx( RIO_RQ SocketQueue, PRIO_BUF pData, ULONG DataBufferCount, PRIO_BUF pLocalAddress, PRIO_BUF pRemoteAddress, PRIO_BUF pControlContext, PRIO_BUF pFlags, DWORD Flags, PVOID RequestContext )
	{
		return m_rioTable.RIOReceiveEx( SocketQueue, pData, DataBufferCount, pLocalAddress, pRemoteAddress, pControlContext, pFlags, Flags, RequestContext );
	}


	inline BOOL RIOSend( RIO_RQ SocketQueue, PRIO_BUF pData, ULONG DataBufferCount, DWORD Flags, PVOID RequestContext )
	{
		return m_rioTable.RIOSend( SocketQueue, pData, DataBufferCount, Flags, RequestContext );
	}

	inline BOOL RIOSendEx( RIO_RQ SocketQueue, PRIO_BUF pData, ULONG DataBufferCount, PRIO_BUF pLocalAddress, PRIO_BUF pRemoteAddress, PRIO_BUF pControlContext, PRIO_BUF pFlags, DWORD Flags, PVOID RequestContext )
	{
		return m_rioTable.RIOSendEx( SocketQueue, pData, DataBufferCount, pLocalAddress, pRemoteAddress, pControlContext, pFlags, Flags, RequestContext );
	}


	inline void RIOCloseCompletionQueue( RIO_CQ CQ )
	{
		m_rioTable.RIOCloseCompletionQueue( CQ );
	}


	inline RIO_CQ RIOCreateCompletionQueue( DWORD QueueSize, PRIO_NOTIFICATION_COMPLETION NotificationCompletion )
	{
		return m_rioTable.RIOCreateCompletionQueue( QueueSize, NotificationCompletion );
	}

	inline RIO_RQ RIOCreateRequestQueue( SOCKET Socket, ULONG MaxOutstandingReceive, ULONG MaxReceiveDataBuffers, ULONG MaxOutstandingSend, ULONG MaxSendDataBuffers, RIO_CQ ReceiveCQ, RIO_CQ SendCQ, PVOID SocketContext )
	{
		return m_rioTable.RIOCreateRequestQueue( Socket, MaxOutstandingReceive, MaxReceiveDataBuffers, MaxOutstandingSend, MaxSendDataBuffers, ReceiveCQ, SendCQ, SocketContext );
	}


	inline int RIONotify( RIO_CQ CQ )
	{
		return m_rioTable.RIONotify( CQ );
	}

	inline ULONG RIODequeueCompletion( RIO_CQ CQ, PRIORESULT Array, ULONG ArraySize )
	{
		return m_rioTable.RIODequeueCompletion( CQ, Array, ArraySize );
	}


	inline RIO_BUFFERID RIORegisterBuffer( PCHAR DataBuffer, DWORD DataLength )
	{
		return m_rioTable.RIORegisterBuffer( DataBuffer, DataLength );
	}

	inline void RIODeregisterBuffer( RIO_BUFFERID BufferId )
	{
		m_rioTable.RIODeregisterBuffer( BufferId );
	}


	inline BOOL RIOResizeCompletionQueue( RIO_CQ CQ, DWORD QueueSize )
	{
		return m_rioTable.RIOResizeCompletionQueue( CQ, QueueSize );
	}

	inline BOOL RIOResizeRequestQueue( RIO_RQ RQ, DWORD MaxOutstandingReceive, DWORD MaxOutstandingSend )
	{
		return m_rioTable.RIOResizeRequestQueue( RQ, MaxOutstandingReceive, MaxOutstandingSend );
	}

public:
	inline BOOL AcceptEx( SOCKET sListenSocket, SOCKET sAcceptSocket, PVOID lpOutputBuffer, DWORD dwReceiveDataLength, DWORD dwLocalAddressLength, DWORD dwRemoteAddressLength, LPDWORD lpdwBytesReceived, LPOVERLAPPED lpOverlapped )
	{
		return m_fnAcceptEx( sListenSocket, sAcceptSocket, lpOutputBuffer, dwReceiveDataLength, dwLocalAddressLength, dwRemoteAddressLength, lpdwBytesReceived, lpOverlapped );
	}


private:
	LPFN_ACCEPTEX					m_fnAcceptEx;
	RIO_EXTENSION_FUNCTION_TABLE	m_rioTable;
};


extern CWSAHelper g_wsa;