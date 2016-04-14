#include "stdafx.h"
#include "BrackerDispatcher.h"
#include "../Interface/IPluginCore.h"

//----------------------------------------------------------------------------- 
// Name        : BrackerDispatcher
// Parameters  : 
// Return      : 
// Description : Constructor
//-----------------------------------------------------------------------------
BrackerDispatcher::BrackerDispatcher()
{
	iRef_ = 1;
	bracker_ = null;
}

//----------------------------------------------------------------------------- 
// Name        : ~BrackerDispatcher
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
BrackerDispatcher::~BrackerDispatcher()
{	
	if (bracker_ != null)
	{
		delete bracker_;
		bracker_ = null;
	}
}

//----------------------------------------------------------------------------- 
// Name        : AddRef
// Parameters  : 
// Return      : 
// Description : Increase counter.
//-----------------------------------------------------------------------------
void BrackerDispatcher::AddRef()
{
	++iRef_;
}

//----------------------------------------------------------------------------- 
// Name        : DecRef
// Parameters  : 
// Return      : 
// Description : Decrease cunter.
//-----------------------------------------------------------------------------
void BrackerDispatcher::DecRef()
{
	--iRef_;
}

//----------------------------------------------------------------------------- 
// Name        : Release
// Parameters  : 
// Return      : 
// Description : Release if counter equal zero.
//-----------------------------------------------------------------------------
void BrackerDispatcher::Release()
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
// Description : Initialization plugin.
//-----------------------------------------------------------------------------
void BrackerDispatcher::Initial()
{
}

//----------------------------------------------------------------------------- 
// Name        : GetBracker
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
Bracker& BrackerDispatcher::ParseAndGetBracker(string _xmlDocument)
{
	if (bracker_ == null)
	{
		bracker_ = new Bracker();
	}

	if (bracker_->Parse(_xmlDocument))
	{
	}

	return *bracker_;
}

//----------------------------------------------------------------------------- 
// Name        : GetBracker
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
Bracker& BrackerDispatcher::GetBracker(XMLObject* _XMLO, string _xmlDocument)
{
	if (bracker_ == null)
	{
		bracker_ = new Bracker();
	}

	bracker_->XMLO_ = _XMLO;

	return *bracker_;
}

//----------------------------------------------------------------------------- 
// Name        : ReleaseBracker
// Parameters  : 
// Return      : 
// Description : 
//-----------------------------------------------------------------------------
IID_RESULTS::E_QUERY_RETURN BrackerDispatcher::ReleaseBracker(Bracker& _brackerDispatcher)
{
	if (bracker_ != null)
	{
		delete bracker_;
		bracker_ = null;
	}

	return IID_RESULTS::EID_OK;
}