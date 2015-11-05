#pragma once


class CSocketSystem : public WSocket::ISystemImpl
{
public:
	CSocketSystem( );
	~CSocketSystem( );


public:

	virtual void OnLog( const wchar_t* szMessage ) override;



};