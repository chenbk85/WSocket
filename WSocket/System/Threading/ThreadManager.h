#pragma once

#include "System/SystemModule.h"

#include "ThreadHost.h"


namespace eThreadType{
	enum e{
		eProcess, eBlockedIoCp
	};
}

class CThreadManager : public TSystemModule< CThreadManager >
{
	static const size_t s_nFrame = 1000 / 60;

	struct sThread
	{
		CThreadHelper	m_thread;
	};

public:
	CThreadManager( );
	virtual ~CThreadManager( );


public:

	template< class _Fn, class... _Args >
	inline void AddThread( _Fn&& _f, _Args&&... _Ax )
	{

	}


private:
	CSpinLock	m_cs;
	std::vector< sThread* >	m_vecThread;
};