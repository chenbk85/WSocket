#pragma once


/*
	Scale( 0 - 100 ):

	0 - 5		|-> eIdle
	5 - 70		|-> eAverageLoad
	70 - 100	|-> eHighLoad
*/

namespace eLaodState {
	enum e {
		eIdle, eAverageLoad, eHighLoad
	};
}


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