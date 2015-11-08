#pragma once

__interface ISystemModule
{
	virtual const wchar_t*		GetModuleName( ) = 0;
	//virtual void SizeModule( ISizer* pSizer ) = 0;
	//virtual void OnHandleMessage( eMessage e, void __ptr64* pData ) = 0
};

template< class T >
class TSystemModule : public ISystemModule
{
public:
	TSystemModule( )
	{
		std::string szClassName = typeid( T ).name();

		m_szClassName = char_to_wstring( szClassName.c_str( ) );
	}

	virtual ~TSystemModule( )
	{ }

public:
	virtual const wchar_t* GetModuleName( ) override
	{
		return m_szClassName.c_str( );
	}

private:
	std::wstring		m_szClassName;
};




class CNetwork;
//>#Todo ??{ better idea for resolving the dependency to CNetwork.h? }??
class CNetworkModule
{
public:
	CNetworkModule( CNetwork* pNetwork, ISystemModule* pModule );
	virtual ~CNetworkModule( );

public:
	void AddError( const wchar_t* szFormat, ... );
	void AddInfo( const wchar_t* szFormat, ... );
	void AddSuccess( const wchar_t* szFormat, ... );

private:
	void AddLog( WSocket::eLogType::e eType, const wchar_t* szFormat, va_list args );

public:
	inline CNetwork*	GetNetwork( )	{ return m_pNetwork; }

private:
	CNetwork*		m_pNetwork;
	ISystemModule*	m_pModule;
};


template< class T >
class TNetworkModule : public TSystemModule< T >, public CNetworkModule
{
public:
	TNetworkModule( CNetwork* pNetwork )
		: CNetworkModule( pNetwork, this )
	{
	}

	virtual ~TNetworkModule( )
	{ }
};

