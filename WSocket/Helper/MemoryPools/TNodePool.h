#pragma once



template< typename T >
class TNodePool
{
public:
	void Push( T* t )
	{
		std::lock_guard< CSpinLock > l( m_cs );

		t->m_pNext = m_pHead;
		m_pHead = t;
	}

	T* Pop( )
	{
		std::lock_guard< CSpinLock > l( m_cs );

		if( !m_pHead )
		{
			return nullptr;
		}


		auto t = m_pHead;
		m_pHead = m_pHead->m_pNext;

		return t;
	}

protected:
	CSpinLock	m_cs;

	T*			m_pHead = nullptr;
};