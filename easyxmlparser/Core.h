// Core.h: interface for the Core class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CORE_H__B8B72482_D6D8_42F7_B798_4CC6E036D4AF__INCLUDED_)
#define AFX_CORE_H__B8B72482_D6D8_42F7_B798_4CC6E036D4AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Interface/ICore.h"
#include "ParserDispatcher.h"
#include "CallbackDispatcher.h"
#include "BrackerDispatcher.h"

class Core : public ICore  
{
	public:
		Core();
		virtual ~Core();

		IID_RESULTS::E_QUERY_RETURN QueryDispatcher(IID_QUERY::E_QUERY _query,
												    IPluginCore** _iSkinCore);

	private:
		ParserDispatcher* parserDispatcher_;
		CallbackDispatcher* callbackDispatcher_;
		BrackerDispatcher* brackerDispatcher_;
};

#endif // !defined(AFX_CORE_H__B8B72482_D6D8_42F7_B798_4CC6E036D4AF__INCLUDED_)
