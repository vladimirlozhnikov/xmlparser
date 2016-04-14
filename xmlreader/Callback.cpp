// Callback.cpp: implementation of the Callback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Callback.h"
#include "../Interface/IParserDispatcher.h"

#include <stdio.h>

Callback::Callback( ICore* _pCore, char* _pXmlDocument )
{
	m_pCore = _pCore;
	m_pXmlDocument = _pXmlDocument;
}

Callback::~Callback()
{
}

void Callback::ElementParsed( XMLObject* _pXMLO )
{
	IParserDispatcher* pParserDispatcher = NULL;
	m_pCore->QueryDispatcher( IID_QUERY::EASCII_DISPATCHER,
		                      ( IPluginCore** )&pParserDispatcher );

	if( pParserDispatcher != NULL )
	{
		int iLen = 0;
		char* pName = pParserDispatcher->GetElement( m_pXmlDocument,
			                                         _pXMLO, &iLen );

		pParserDispatcher->Release();

		char* pElement = new char[ iLen + 1];

		memset( pElement, 0, iLen + 1 );
		memcpy( pElement, pName, iLen );

		printf( pElement );
		printf( "\n" );

		delete[] pElement;
	}
}