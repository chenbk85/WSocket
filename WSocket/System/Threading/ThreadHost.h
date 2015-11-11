#pragma once




__interface IThread
{

};

template< class T >
class CThreadHost : public IThread
{
public:
	CThreadHost( )
	{

	}

	virtual ~CThreadHost( )
	{

	}

public:


private:
	CThreadHelper	m_thread;
};

