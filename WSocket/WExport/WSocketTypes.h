#pragma once

/*
*/

namespace WSocket
{
	typedef void* __ptr64 UPacketBuffer;

	
	namespace Internal
	{
		__interface INetwork
		{

		};

		__interface IUser
		{
			

		};

		__interface ISystem
		{
			virtual bool CreateNetwork( USHORT uPort, Internal::INetwork** pNetworkOut ) = 0;
			virtual void DestroyNetwork( Internal::INetwork* pNetwork ) = 0;


			//=> This function updates all internal structures. (Should be called once every second)
			virtual void UpdateSystem( ) = 0;
		};
	}

	__interface IUserImpl
	{
		virtual void OnClear( ) = 0;
		virtual void OnConnect( ) = 0;
		virtual void OnDisconnect( ) = 0;
	};

	__interface IDispatcherImpl
	{
		virtual void OnDispatch( IUserImpl* pUser, UPacketBuffer* pPacket ) = 0;
	};

	__interface INetworkImpl
	{
		virtual IUserImpl*			ConstructUser( BYTE* pBuffer ) = 0;
		virtual size_t				GetUserSize( ) = 0;
		virtual IDispatcherImpl*	GetDispatcher( ) = 0;
	};

	__interface ISystemImpl
	{
		virtual void OnLog( const wchar_t* szMessage ) = 0;
		//virtual void OnCritcalError( IErrorInfo* pInfo ) = 0;
	};

}