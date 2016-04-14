#if !defined ICALLBACK_DISPATCHER
#define ICALLBACK_DISPATCHER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "iid.h"
#include "IPluginCore.h"
#include "IParserDispatcher.h"
#include "ICallback.h"

class ICallbackDispatcher : public IPluginCore
{
	public:
		virtual IID_RESULTS::E_QUERY_RETURN Attach(IParserDispatcher* _dispatcher, ICallback* _callback) = 0;
		virtual IID_RESULTS::E_QUERY_RETURN Detach(IParserDispatcher* _dispatcher) = 0;
};

#endif // !defined ICALLBACK_DISPATCHER