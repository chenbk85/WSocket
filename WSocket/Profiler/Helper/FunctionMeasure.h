#pragma once


class CFunctionMeasure
{
public:
	template< class _Fn, class... _Args >
	inline static LONGLONG Measure( _Fn&& _Fx, _Args&&... _Ax )
	{
		LARGE_INTEGER	tmBegin;
		QueryPerformanceCounter( &tmBegin );
		{
			_Fx( std::forward< _Args >( _Ax )... );
		}

		LARGE_INTEGER	tmEnd;
		QueryPerformanceCounter( &tmEnd );

		return tmEnd.QuadPart - tmBegin.QuadPart;
	}


};