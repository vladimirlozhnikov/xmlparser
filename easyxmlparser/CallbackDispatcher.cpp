// CallbackDispatcher.cpp: implementation of the CallbackDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CallbackDispatcher.h"

//----------------------------------------------------------------------------- 
// Name        : CallbackDispatcher
// Parameters  : 
// Return      : 
// Description : Constructor
//-----------------------------------------------------------------------------
CallbackDispatcher::CallbackDispatcher()
{
	iRef_ = 1;
}

//----------------------------------------------------------------------------- 
// Name        : ~CallbackDispatcher
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
CallbackDispatcher::~CallbackDispatcher()
{
}

//----------------------------------------------------------------------------- 
// Name        : AddRef
// Parameters  : 
// Return      : 
// Description : Increase counter.
//-----------------------------------------------------------------------------
void CallbackDispatcher::AddRef()
{
	++iRef_;
}

//----------------------------------------------------------------------------- 
// Name        : DecRef
// Parameters  : 
// Return      : 
// Description : Decrease cunter.
//-----------------------------------------------------------------------------
void CallbackDispatcher::DecRef()
{
	--iRef_;
}

//----------------------------------------------------------------------------- 
// Name        : Release
// Parameters  : 
// Return      : 
// Description : Release if counter equal zero.
//-----------------------------------------------------------------------------
void CallbackDispatcher::Release()
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
// Description : Initialization plugin
//-----------------------------------------------------------------------------
void CallbackDispatcher::Initial()
{
}

//----------------------------------------------------------------------------- 
// Name        : Attach
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
IID_RESULTS::E_QUERY_RETURN CallbackDispatcher::Attach(IParserDispatcher* _dispatcher, ICallback* _callback)
{
	_dispatcher->AddRef();
	_dispatcher->SetCallback(_callback);

	return IID_RESULTS::EID_OK;
}

//----------------------------------------------------------------------------- 
// Name        : Detach
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
IID_RESULTS::E_QUERY_RETURN CallbackDispatcher::Detach(IParserDispatcher* _dispatcher)
{
	IID_RESULTS::E_QUERY_RETURN ret = IID_RESULTS::EID_OK;

	_dispatcher->DecRef();
	_dispatcher->SetCallback(null);

	return ret;
}