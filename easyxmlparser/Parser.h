#ifndef __XML_PARSERL_H__
#define __XML_PARSERL_H__

#include "../Interface/documentparameters.h"
#include "../Interface/ICallback.h"

class ParserDispatcher;

class XMLParser
{
	public:
		void Initialize(XMLObject* _pXMLO);
		void Release(XMLObject* _pXMLO);
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
                           int* _pwLen );
		int GetNumChildren(XMLObject* _pXMLO);
		XMLObject* GetChild(XMLObject* _pXMLO, int _n);
		char* GetAttributeByIndex(char* _pstrXmlDocument,
                                  XMLObject* _pXMLO,
                                  int _wIndex,
                                  int* _pwLen );

	private:
		bool _ExtractXMLFragmentFromStream(XMLObject* _pXMLO,
                                           const char* _pstrXmlDocument,
                                           int _wLen, 
                                           int* _pwConsume,
                                           bool* _pbStopAtStartTag,
                                           int* _pwErr,
                                           int* _pwErrOffset);
		bool _ExtractAttributes(const char* _pstrXmlDocument,
                                XMLObject* _pXMLO,
                                int* _pwNumAttrs,
                                int* _pwErr,
                                int* _pwErrOffset);

		int len1_;
		int elementname_len_;
		unsigned int wPosition_;
		bool bIntoQuotes_;
		char* pstrTagName_;
		char* lastTagName_;
		char* strCloseTagName_;
		char* strBeginTagName_;

		friend class ParserDispatcher;;
		ICallback* pCallback_;
};

#endif