// xmlreader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../Interface/ICore.h"
#include "../Interface/IParserDispatcher.h"
#include "../Interface/ICallbackDispatcher.h"
#include "Callback.h"
#include <string>

using namespace std;

#define _STRING_GET_CORE "GetCore" 

typedef ICore* ( *GETCORE )();
string GetAppPath();
void Parse( ICore* pCore );
void LoadXmlDocument( LPSTR pFilePath );

char* pXmlDocument = "<aaa>111</aaa><bbb>222</bbb>";

int main(int argc, char* argv[])
{
	HANDLE hFind = NULL;
	string appPath = GetAppPath() + "easyxmlparser.dll";

	GETCORE GetCore = NULL;
	ICore* pCore = NULL;

	//LoadXmlDocument( "c:\\mscorlib.xml" );

	HMODULE hModule = ::LoadLibrary( appPath.c_str() );
	if( hModule != NULL )
	{
		GetCore = ( GETCORE )::GetProcAddress( hModule, _STRING_GET_CORE ); 
		if( GetCore != NULL )
		{
			pCore = GetCore();
			Parse( pCore );
		}
		else
		{
			::FreeLibrary( hModule );
		}
	}
	
	return 0;
}

string GetAppPath()
{
	string appPath;
	TCHAR szModule[_MAX_PATH] = {0};

	::GetModuleFileName( NULL, szModule, _MAX_PATH );

	appPath = ( const char* )szModule;
	size_t sizeFind = appPath.find_last_of('\\');
	if( sizeFind > 0 )
	{
		appPath.resize( sizeFind + 1 );
	}


	return appPath;
}

void Parse( ICore* _pCore )
{
	IParserDispatcher* pParserDispatcher = NULL;
	_pCore->QueryDispatcher( IID_QUERY::EASCII_DISPATCHER,
		                     ( IPluginCore** )&pParserDispatcher );

	if( pParserDispatcher != NULL )
	{
		if ( pXmlDocument != NULL )
		{
			pParserDispatcher->Initial();

			char *szNode = pXmlDocument;

			int iElementSize = 0;
			int wLen1 = strlen( szNode );
			int wLen2 = 0;
			int wSize = 0;
			int wErr = 0;
			int wErrOffset = 0;
			int err = 0;
			bool bRes = false;
			bool bStartTag = false;

			XMLObject XMLO = { 0 };

			DWORD dwStart = GetTickCount();

			while( true && ( wLen1 > 0 ) )
			{
				ICallbackDispatcher* pCallbackDispatcher = NULL;
				_pCore->QueryDispatcher( IID_QUERY::ECALLBACK_DISPATCHER,
						                 ( IPluginCore** )&pCallbackDispatcher );

				Callback* pCallback = new Callback( _pCore, szNode );

				if( pCallbackDispatcher != NULL )
				{
					pCallbackDispatcher->Attach( pParserDispatcher, pCallback );
				}

				pParserDispatcher->Initialize( &XMLO );
				if( !pParserDispatcher->Parse( &XMLO, szNode,
							                   wLen1, &wSize, &bStartTag, &wErr,
									           &wErrOffset ) )
				{
					pParserDispatcher->ReleaseXml( &XMLO );    
					wSize = iElementSize;

					printf( "\n\nFailed\n." );
					break;
				}
				else if( wSize > 0 ) //XML element parsed!
				{
				}
			
				wLen1 -= wSize;
				szNode = &szNode[ wSize ];
				pParserDispatcher->ReleaseXml( &XMLO );

				if( pCallbackDispatcher != NULL )
				{
					pCallbackDispatcher->Detach( pParserDispatcher );
				}

				delete pCallback;
			}
		
			pParserDispatcher->Release();

			DWORD dwEnd = GetTickCount() - dwStart;
			printf( "\n\nParsed at %u milliseconds.", dwEnd );
			free( pXmlDocument );
			Sleep( INFINITE );
		}
	}
}

void LoadXmlDocument( LPSTR pFilePath )
{
	HANDLE hFile = CreateFile( pFilePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL );
	if ( hFile != INVALID_HANDLE_VALUE )
	{
		DWORD dwFileSize = GetFileSize( hFile, NULL );
		DWORD dwReaded = 0;
		pXmlDocument = ( char* )malloc( dwFileSize );
		if ( pXmlDocument )
		{
			if ( !ReadFile( hFile, pXmlDocument, dwFileSize, &dwReaded, NULL ) )
			{
				free( pXmlDocument );
				pXmlDocument = NULL;
			}
		}
		CloseHandle( hFile );
	}
}