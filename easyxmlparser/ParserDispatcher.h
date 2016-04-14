// ParserDispatcher.h: interface for the ParserDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERDISPATCHER_H__F1ADBD90_D7CC_4B17_8108_0403EBD5FA43__INCLUDED_)
#define AFX_PARSERDISPATCHER_H__F1ADBD90_D7CC_4B17_8108_0403EBD5FA43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Interface/IParserDispatcher.h"
#include "Parser.h"

class ParserDispatcher : public IParserDispatcher
{
	public:
		ParserDispatcher();
		virtual ~ParserDispatcher();

		void AddRef();
		void DecRef();
		void Release();
		void Initial();

		void Initialize(XMLObject* _pXMLO);
		void ReleaseXml(XMLObject* _pXMLO);
		bool Parse(XMLObject* _pXMLO, const char* _pstrXmlDocument,
                   int _wEnd, int* _pwElementSize,
                   bool* _pwShortCircuit, int* _pwErr,
                   int* _pwErrOffset);
		char* GetElement(char* _pstrXmlDocument,
                         XMLObject* _pXMLO, int* _pwElementsize);
		char* GetTagName(char* _pstrXmlDocument,
                         XMLObject* _pXMLO, int* _pwLen);
		char* GetContent(char* _pstrXmlDocument,
                         XMLObject* _pXMLO,
                         int* _pwLen,
                         int* _pwNumEncodings);
		XMLObject* GetChild(char* _pstrXmlDocument,
                            char* _pstrChild,
                            XMLObject* _pXMLO);
		char* GetAttribute(char* _pstrXmlDocument,
                           char* _pstrAttribute,
                           XMLObject* _pXMLO,
                           int* _pwLen);
		int GetNumChildren(XMLObject* _pXMLO);
		XMLObject* GetChild(XMLObject* _pXMLO, int _n);
		char* GetAttributeByIndex(char* _pstrXmlDocument,
                                  XMLObject* _pXMLO,
                                  int _wIndex,
                                  int* _pwLen);

	private:
		void SetCallback(ICallback* _pCallback);

		XMLParser* parser_;
};

#endif // !defined(AFX_PARSERDISPATCHER_H__F1ADBD90_D7CC_4B17_8108_0403EBD5FA43__INCLUDED_)
