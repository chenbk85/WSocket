#pragma once


namespace WSocket
{
	namespace Internal
	{
		__interface INetwork
		{

		};
	}

	__interface ISystem
	{
		virtual bool CreateNetwork( u_short uPort, Internal::INetwork** pNetworkOut ) = 0;
		virtual void DestroyNetwork( Internal::INetwork* pNetwork ) = 0;


		//=> This function updates all internal structures. (Should be called once every second)
		virtual void UpdateSystem( ) = 0;
	};


}