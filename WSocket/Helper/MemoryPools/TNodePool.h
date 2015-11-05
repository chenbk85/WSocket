#pragma once


template< typename T >
class TNodePool
{
public:
	TNodePool( )
	{

	}
	~TNodePool( )
	{

	}

public:



	void Defrag( )
	{
		//=> free unused chunks..
	}


private:

	T*	m_pHead = nullptr;
};