// ParserDispatcher.cpp: implementation of the ParserDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ParserDispatcher.h"

//----------------------------------------------------------------------------- 
// Name        : ParserDispatcher
// Parameters  : 
// Return      : 
// Description : Constructor
//-----------------------------------------------------------------------------
ParserDispatcher::ParserDispatcher()
{
	iRef_ = 1;
}

//----------------------------------------------------------------------------- 
// Name        : ~ParserDispatcher
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
ParserDispatcher::~ParserDispatcher()
{
	if (parser_ != null)
	{
		delete parser_;
	}
}

//----------------------------------------------------------------------------- 
// Name        : AddRef
// Parameters  : 
// Return      : 
// Description : Increase counter.
//-----------------------------------------------------------------------------
void ParserDispatcher::AddRef()
{
	++iRef_;
}

//----------------------------------------------------------------------------- 
// Name        : DecRef
// Parameters  : 
// Return      : 
// Description : Decrease cunter.
//-----------------------------------------------------------------------------
void ParserDispatcher::DecRef()
{
	--iRef_;
}

//----------------------------------------------------------------------------- 
// Name        : Release
// Parameters  : 
// Return      : 
// Description : Release if counter equal zero.
//-----------------------------------------------------------------------------
void ParserDispatcher::Release()
{
	if (--iRef_ <= 1)
	{
		delete this;
	}
}

//----------------------------------------------------------------------------- 
// Name        : Initial
// Parameters  : 
// Return      : 
// Description : Initialization plugin by window.
//-----------------------------------------------------------------------------
void ParserDispatcher::Initial()
{
	parser_ = new XMLParser();
}

//----------------------------------------------------------------------------- 
// Name        : Initialize
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
void ParserDispatcher::Initialize(XMLObject* _pXMLO)
{
	parser_->Initialize(_pXMLO);
}

//----------------------------------------------------------------------------- 
// Name        : Release
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
void ParserDispatcher::ReleaseXml(XMLObject* _pXMLO)
{
	parser_->Release(_pXMLO);
}

//----------------------------------------------------------------------------- 
// Name        : Parse
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
bool ParserDispatcher::Parse(XMLObject* _pXMLO, const char* _pstrXmlDocument,
                             int _wEnd, int* _pwElementSize,
                             bool* _pwShortCircuit, int* _pwErr,
                             int* _pwErrOffset)
{
	return parser_->Parse(_pXMLO, _pstrXmlDocument, _wEnd,
		                  _pwElementSize, _pwShortCircuit, _pwErr,
				          _pwErrOffset);
}

//----------------------------------------------------------------------------- 
// Name        : GetElement
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
char* ParserDispatcher::GetElement(char* _pstrXmlDocument,
                                   XMLObject* _pXMLO, int* _pwElementsize )
{
	return parser_->GetElement(_pstrXmlDocument, _pXMLO, _pwElementsize);
}

//----------------------------------------------------------------------------- 
// Name        : GetTagName
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
char* ParserDispatcher::GetTagName(char* _pstrXmlDocument,
                                   XMLObject* _pXMLO, int* _pwLen)
{
	return parser_->GetTagName(_pstrXmlDocument, _pXMLO, _pwLen);
}

//----------------------------------------------------------------------------- 
// Name        : GetContent
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
char* ParserDispatcher::GetContent(char* _pstrXmlDocument,
                                   XMLObject* _pXMLO,
                                   int* _pwLen,
                                   int* _pwNumEncodings)
{
	return parser_->GetContent(_pstrXmlDocument, _pXMLO,
		                       _pwLen, _pwNumEncodings);
}

//----------------------------------------------------------------------------- 
// Name        : GetChild
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
XMLObject* ParserDispatcher::GetChild(char* _pstrXmlDocument,
                                      char* _pstrChild,
                                      XMLObject* _pXMLO)
{
	return parser_->GetChild(_pstrXmlDocument, _pstrChild, _pXMLO);
}

//----------------------------------------------------------------------------- 
// Name        : GetAttribute
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
char* ParserDispatcher::GetAttribute(char* _pstrXmlDocument,
                                     char* _pstrAttribute,
                                     XMLObject* _pXMLO,
                                     int* _pwLen)
{
	return parser_->GetAttribute(_pstrXmlDocument, _pstrAttribute,
		                         _pXMLO, _pwLen);
}

//----------------------------------------------------------------------------- 
// Name        : GetNumChildren
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
int ParserDispatcher::GetNumChildren(XMLObject* _pXMLO)
{
	return parser_->GetNumChildren(_pXMLO);
}

//----------------------------------------------------------------------------- 
// Name        : GetChild
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
XMLObject* ParserDispatcher::GetChild(XMLObject* _pXMLO, int _n)
{
	return parser_->GetChild(_pXMLO, _n);
}

//----------------------------------------------------------------------------- 
// Name        : GetAttributeByIndex
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
char*  ParserDispatcher::GetAttributeByIndex(char* _pstrXmlDocument,
                                             XMLObject* _pXMLO,
                                             int _wIndex,
                                             int* _pwLen)
{
	return parser_->GetAttributeByIndex(_pstrXmlDocument, _pXMLO,
		                                _wIndex, _pwLen);
}

//----------------------------------------------------------------------------- 
// Name        : SetCallback
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
void ParserDispatcher::SetCallback(ICallback* _pCallback)
{
	parser_->pCallback_ = _pCallback;
}