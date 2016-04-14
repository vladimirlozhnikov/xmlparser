// Core.cpp: implementation of the Core class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Core.h"

//----------------------------------------------------------------------------- 
// Name        : Core
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
Core::Core()
{
	parserDispatcher_ = new ParserDispatcher();
	callbackDispatcher_ = new CallbackDispatcher();
	brackerDispatcher_ = new BrackerDispatcher();
}


//----------------------------------------------------------------------------- 
// Name        : ~Core
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
Core::~Core()
{
	/*if (m_pParserDispatcher != null)
	{
		delete pParserDispatcher_;
		pParserDispatcher_ = null;
	}*/
}


//----------------------------------------------------------------------------- 
// Name        : QueryDispatcher
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
IID_RESULTS::E_QUERY_RETURN Core::QueryDispatcher(IID_QUERY::E_QUERY _query,
												  IPluginCore** _iSkinCore)
{
	IID_RESULTS::E_QUERY_RETURN Res = IID_RESULTS::EID_OK;

	switch (_query)
	{
		case IID_QUERY::EASCII_DISPATCHER:
		{
			parserDispatcher_->AddRef();
			*_iSkinCore = (IPluginCore*)parserDispatcher_;
		}; break;
		case IID_QUERY::ECALLBACK_DISPATCHER:
		{
			callbackDispatcher_->AddRef();
			*_iSkinCore = (IPluginCore*)callbackDispatcher_;
		}; break;
		case IID_QUERY::EBRACKER_DISPATCHER:
		{
			brackerDispatcher_->AddRef();
			*_iSkinCore = (IPluginCore*)brackerDispatcher_;
		}; break;
	};

	return Res;
}
