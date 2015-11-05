#pragma once


class WSAHelper
{
public:
	static void Initialize( )
	{

	}

public:


private:
	static LPFN_ACCEPTEX					m_fnAcceptEx;
	static RIO_EXTENSION_FUNCTION_TABLE		m_rioTable;
};