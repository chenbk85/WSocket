#pragma once

class CTestDispatcher : public WSocket::IDispatcherImpl
{
public:
	CTestDispatcher( );
	~CTestDispatcher( );


public:
	virtual void OnDispatch( WSocket::IUserImpl* pUser, WSocket::UPacketBuffer* pPacket ) override;



};