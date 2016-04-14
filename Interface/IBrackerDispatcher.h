#if !defined IBRACKER_DISPATCHER
#define IBRACKER_DISPATCHER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "iid.h"
#include "IPluginCore.h"
#include "IParserDispatcher.h"
#include "Bracker.h"

class IBrackerDispatcher : public IPluginCore
{
	public:
		virtual Bracker& ParseAndGetBracker(string _xmlDocument) = 0;
		virtual Bracker& GetBracker(XMLObject* _XMLO, string _xmlDocument) = 0;

		virtual IID_RESULTS::E_QUERY_RETURN ReleaseBracker(Bracker& _brackerDispatcher) = 0;
};

#endif // !defined IBRACKER_DISPATCHER