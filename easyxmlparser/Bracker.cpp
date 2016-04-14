#include "stdafx.h"
#include "Bracker.h"

//----------------------------------------------------------------------------- 
// Name        : Bracker::Bracker
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
Bracker::Bracker()
{
	XMLO_ = new XMLObject();
}

//----------------------------------------------------------------------------- 
// Name        : Bracker::~Bracker
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
Bracker::~Bracker()
{
	if (XMLO_ != null)
	{
		IParserDispatcher* parserDispatcher = null;
		ICore* core = App::Instance()->GetCore();
		core->QueryDispatcher(IID_QUERY::EASCII_DISPATCHER,
							  (IPluginCore**)&parserDispatcher);

		if (parserDispatcher != null)
		{
			parserDispatcher->ReleaseXml(XMLO_);
			parserDispatcher->Release();
		}

		delete XMLO_;
		XMLO_ = null;
	}
}

//----------------------------------------------------------------------------- 
// Name        : Bracker::Parse
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
bool Bracker::Parse(string _xmlDocument)
{
	xmlDocument_ = _xmlDocument;

	IParserDispatcher* parserDispatcher = null;
	ICore* core = App::Instance()->GetCore();
	core->QueryDispatcher(IID_QUERY::EASCII_DISPATCHER,
		                  (IPluginCore**)&parserDispatcher);

	if (parserDispatcher != null)
	{
		int iElementSize = 0;
		int wLen1 = _xmlDocument.length();
		int wLen2 = 0;
		int wSize = 0;
		int wErr = 0;
		int wErrOffset = 0;
		int err = 0;
		bool bRes = false;
		bool bStartTag = false;
		parserDispatcher->Initialize(XMLO_); 

		if (!parserDispatcher->Parse(XMLO_, _xmlDocument.c_str(),
									 wLen1, &wSize, &bStartTag, &wErr,
									 &wErrOffset))
		{
			parserDispatcher->ReleaseXml(XMLO_);    
			wSize = iElementSize;

			return false;
		}
		else if (wSize > 0) //XML element parsed!
		{
		}

		parserDispatcher->Release();
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------- 
// Name        : Bracker::operator []
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
const Node& Bracker::operator [] (string nodeName)
{
	Node& node = *(new Node());

	IParserDispatcher* parserDispatcher = null;
	ICore* core = App::Instance()->GetCore();
	core->QueryDispatcher(IID_QUERY::EASCII_DISPATCHER,
		                  (IPluginCore**)&parserDispatcher);

	if (parserDispatcher != null)
	{
		int len = 0;
		char* name = parserDispatcher->GetElement((char*)xmlDocument_.c_str(),
												   XMLO_, &len);

		if (name != null)
		{
			node.xmlDocument_ = xmlDocument_;
			node.XMLO_ = XMLO_;
			node.isCorrect_ = true;
		}

		parserDispatcher->Release();
	}

	return node;
}

//----------------------------------------------------------------------------- 
// Name        : Node::Node
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
Node::Node()
{
	XMLO_ = null;
	isCorrect_ = false;
}

//----------------------------------------------------------------------------- 
// Name        : Node::GetName
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
string Node::GetName()
{
	return "";
}

//----------------------------------------------------------------------------- 
// Name        : Node::GetContent
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
string Node::GetContent()
{
	return "";
}

//----------------------------------------------------------------------------- 
// Name        : Node::GetAttribute
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
string Node::GetAttribute()
{
	return "";
}

//----------------------------------------------------------------------------- 
// Name        : Node::operator []
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
const Node& Node::operator [] (string nodeName)
{
	return *(new Node());
}