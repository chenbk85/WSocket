#pragma once





template< size_t S >
class CLoadAnalyser
{
	struct sSnapshot
	{
		LARGE_INTEGER	m_tm;
		size_t			m_nCount;
	};

public:
	CLoadAnalyser( )
	{

	}

	~CLoadAnalyser( )
	{

	}

public:

private:
	size_t CalcMean( )
	{
		size_t nSum = 0;
		for( auto i : m_arrSnapshots )
		{
			nSum += i.m_nCount;
		}

		return reinterpret_cast< size_t >( floor( ( double )nSum / ( double )S ) );
	}

private:
	std::array< sSnapshot, S >	m_arrSnapshots;
};