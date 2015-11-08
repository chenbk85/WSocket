#include "stdafx.h"
#include "AcceptWorker.h"

CAcceptWorker::CAcceptWorker( CNetwork* pNetwork )
	: TNetworkModule( pNetwork )
{
}

CAcceptWorker::~CAcceptWorker( )
{

}

void CAcceptWorker::CreateWorker( )
{
	DWORD i = 1337;
	AddError( L"Hello world %d", i );

// 	HANDLE hIoCp = INVALID_HANDLE_VALUE;
// 
// 	static const ULONG MAX_OVERLAPPED_RESULTS = 1024;
// 	OVERLAPPED_ENTRY* pEntries = new OVERLAPPED_ENTRY[ MAX_OVERLAPPED_RESULTS ];
// 	ULONG nRemoved = 0;






	//m_thread.RunThread( [ & ]{ 
	//	if( !GetQueuedCompletionStatusEx( hIoCp, pEntries, MAX_OVERLAPPED_RESULTS, &nRemoved, 100, FALSE ) )
	//	{
	//		/*??{
	//			if( this->IsCanceled() )
	//				return false;
	//		}??*/
	//	}
	//}, [ & ]{ 
	//	//for( size_t i = 0; i < )
	//
	//	/*??{
	//		SwitchTLS()-> >>ThreadContext??
	//	}??*/
	//} );



}
