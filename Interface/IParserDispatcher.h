// IParserDispatcher.h: interface for the IParserDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPARSERDISPATCHER_H__121966A5_D591_4888_B1AC_8A7D654544BC__INCLUDED_)
#define AFX_IPARSERDISPATCHER_H__121966A5_D591_4888_B1AC_8A7D654544BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "iid.h"
#include "IPluginCore.h"
#include "documentparameters.h"
#include "ICallback.h"

class CallbackDispatcher;

class IParserDispatcher : public IPluginCore  
{
	public:
		virtual void Initialize(XMLObject* _pXMLO) = 0;
		virtual void ReleaseXml(XMLObject* _pXMLO) = 0;
		virtual bool Parse(XMLObject* _pXMLO, const char* _pstrXmlDocument,
                           int _wEnd, int* _pwElementSize,
                           bool* _pwShortCircuit, int* _pwErr,
                           int* _pwErrOffset) = 0;
		virtual char* GetElement(char* _pstrXmlDocument,
                                 XMLObject* _pXMLO,
								 int* _pwElementsize) = 0;
		virtual char* GetTagName(char* _pstrXmlDocument,
                                 XMLObject* _pXMLO, int* _pwLen) = 0;
		virtual char* GetContent(char* _pstrXmlDocument,
                                 XMLObject* _pXMLO,
                                 int* _pwLen,
                                 int* _pwNumEncodings) = 0;
		virtual XMLObject* GetChild(char* _pstrXmlDocument,
                                    char* _pstrChild,
                                    XMLObject* _pXMLO) = 0;
		virtual char* GetAttribute(char* _pstrXmlDocument,
                                   char* _pstrAttribute,
                                   XMLObject* _pXMLO,
                                   int* _pwLen) = 0;
		virtual int GetNumChildren(XMLObject* _pXMLO) = 0;
		virtual XMLObject* GetChild(XMLObject* _pXMLO, int _n) = 0;
		virtual char* GetAttributeByIndex(char* _pstrXmlDocument,
                                          XMLObject* _pXMLO,
                                          int _wIndex,
                                          int* _pwLen) = 0;

	protected:
		friend class CallbackDispatcher;
		virtual void SetCallback(ICallback* _pCallback) = 0;
};

#endif // !defined(AFX_IPARSERDISPATCHER_H__121966A5_D591_4888_B1AC_8A7D654544BC__INCLUDED_)
