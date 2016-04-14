// CallbackDispatcher.h: interface for the CallbackDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLBACKDISPATCHER_H__A1EFB86A_D7A3_4357_93F9_7164C70AC0E2__INCLUDED_)
#define AFX_CALLBACKDISPATCHER_H__A1EFB86A_D7A3_4357_93F9_7164C70AC0E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Interface/ICallbackDispatcher.h"
#include "../Interface/IParserDispatcher.h"

class CallbackDispatcher : public ICallbackDispatcher
{
	public:
		CallbackDispatcher();
		virtual ~CallbackDispatcher();

		void AddRef();
		void DecRef();
		void Release();
		void Initial();

		IID_RESULTS::E_QUERY_RETURN Attach(IParserDispatcher* _dispatcher, ICallback* _callback);
		IID_RESULTS::E_QUERY_RETURN Detach(IParserDispatcher* _dispatcher);
};

#endif // !defined(AFX_CALLBACKDISPATCHER_H__A1EFB86A_D7A3_4357_93F9_7164C70AC0E2__INCLUDED_)
