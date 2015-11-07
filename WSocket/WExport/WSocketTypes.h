#pragma once

/*
*/

namespace WSocket
{
	typedef void* __ptr64 UPacketBuffer;

	namespace eLogType {
		enum e { eSuccess, eInfo, eError };
	}
	
	namespace Internal
	{
		__interface INetwork
		{

		};

		__interface IUser
		{
			

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


	__interface ILogImpl
	{
		virtual void OnLog( eLogType::e eType, const wchar_t* szMessage ) = 0;
	};

}