#include "stdafx.h"
#include "TestNetwork.h"

CTestNetwork::CTestNetwork( )
{

}

CTestNetwork::~CTestNetwork( )
{

}

void CTestNetwork::OnLog( WSocket::eLogType::e eType, const wchar_t* szMessage )
{
	wprintf_s( L"[TestNet]: %s\r\n", szMessage );
}
