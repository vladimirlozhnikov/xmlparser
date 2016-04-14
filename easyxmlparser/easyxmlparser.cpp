// easyxmlparser.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#define	DLL_EXPORT __declspec( dllexport )
extern "C" DLL_EXPORT ICore* GetCore();

BOOL APIENTRY DllMain(HANDLE _hModule, 
                      DWORD _ul_reason_for_call, 
                      LPVOID _lpReserved)
{
    switch (_ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			App::Instance()->SetHinstance((HINSTANCE)_hModule);
			App::Instance()->Start();
		}; break;
		//case DLL_THREAD_ATTACH:
		//case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
		{
			App::Instance()->Stop();
		}; break;
    }

    return TRUE;
}

//----------------------------------------------------------------------------- 
// Name        : GetCoreSkin
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
extern "C" DLL_EXPORT ICore* GetCore()
{
	return App::Instance()->GetCore();
}