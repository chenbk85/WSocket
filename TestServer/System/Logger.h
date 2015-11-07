#pragma once



class CLogger : public WSocket::ILogImpl
{
	struct sLogEntry
	{
		wchar_t		m_szMessage[ 512 ];

		WSocket::eLogType::e	m_eType;
	};

public:
	CLogger( );
	virtual ~CLogger( );

public:
	virtual void OnLog( WSocket::eLogType::e eType, const wchar_t* szMessage ) override;

	void Dispatch( );

private:
	HANDLE	m_hOutput = GetStdHandle( STD_OUTPUT_HANDLE );

	Concurrency::concurrent_queue< sLogEntry* >		m_queueLogs;
};


void AddError( const wchar_t* szFormat, ... );
void AddInfo( const wchar_t* szFormat, ... );
void AddSuccess( const wchar_t* szFormat, ... );