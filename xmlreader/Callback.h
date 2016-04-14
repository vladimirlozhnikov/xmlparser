// Callback.h: interface for the Callback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLBACK_H__F17CD61D_2B2E_47F2_A05E_B1921B4FFF16__INCLUDED_)
#define AFX_CALLBACK_H__F17CD61D_2B2E_47F2_A05E_B1921B4FFF16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\INTERFACE\ICallback.h"
#include "../Interface/ICore.h"

class Callback : public ICallback  
{
	public:
		Callback( ICore* _pCore, char* _pXmlDocument );
		virtual ~Callback();

		void ElementParsed( XMLObject* _pXMLO );

		ICore* m_pCore;
		char* m_pXmlDocument;
};

#endif // !defined(AFX_CALLBACK_H__F17CD61D_2B2E_47F2_A05E_B1921B4FFF16__INCLUDED_)
