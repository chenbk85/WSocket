#pragma once


struct sPacketBuffer : public RIO_BUF
{
	static const size_t s_nBufferSize = 1024;
	static_assert( ( s_nBufferSize % 2 ) == 0, "PacketSize must be pow of 2!" );
	static_assert( s_nBufferSize <= 65535, "Buffer can't be larger as 65535!" );

	char*	m_pBuffer;
};

class CUser;
struct sRioResult
{
	inline void ReadResult( RIORESULT* pResult )
	{
		this->m_nStatus = static_cast< size_t >( pResult->Status );
		this->m_nTransferred = pResult->BytesTransferred;

		this->m_pUser = reinterpret_cast< CUser* >( pResult->SocketContext );
		this->m_pBuffer = reinterpret_cast< sPacketBuffer* >( pResult->RequestContext );
	}

	size_t			m_nStatus;
	size_t			m_nTransferred;
	CUser*			m_pUser;

	sPacketBuffer*	m_pBuffer;

};
