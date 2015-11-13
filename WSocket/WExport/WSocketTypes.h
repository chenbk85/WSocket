#pragma once


namespace WSocket
{
	typedef void* __ptr64 UPacketBuffer;

	namespace eLogType {
		enum e { eSuccess, eInfo, eError };
	}

	namespace Internal
	{
		__interface IUser
		{
			//virtual void DropUser( eReason ) = 0;

			virtual const size_t		GetId( ) = 0;
			virtual const sockaddr_in*	GetRemoteAddress( ) = 0;
		};

		__interface INetwork
		{
			IUser*	GetUserById( size_t nId ) = 0;
		};


	}

	__interface IUserImpl
	{
		virtual void OnClear( ) = 0;

		virtual void OnConnect( ) = 0;
		virtual void OnDisconnect( ) = 0;

		virtual void OnSetIUser( WSocket::Internal::IUser* pUser );
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

		virtual void OnLog( eLogType::e eType, const wchar_t* szMessage ) = 0;
	};


}