#pragma once


template< typename T >
class TNodePoolChunked
{
	struct sNode : public T
	{
		sNode*	m_pNext;
	};

public:
	TNodePoolChunked( )
	{
		ReserveChunk( );
	}

	~TNodePoolChunked( )
	{

	}

public:
	void Push( T* t )
	{
		auto pNode = reinterpret_cast< sNode* >( t );
		
	}

	T* Pop( )
	{
		return reinterpret_cast< T* >( nullptr );
	}


public:
	void ReserveChunk( )
	{
		sNode* pNodes = new sNode[ 1024 ];

		for( size_t i = 0; i < 1024; i++ )
		{
			this->Push( &pNodes[ i ] );
		}

	}


private:
};