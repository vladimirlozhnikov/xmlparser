#if !defined _I_CORE_H
#define _I_CORE_H

#include "iid.h"
#include "IPluginCore.h"


class ICore
{
	public:
		virtual IID_RESULTS::E_QUERY_RETURN QueryDispatcher(
			                                  IID_QUERY::E_QUERY _query,
											  IPluginCore** _iPluginCore) = 0;
};


#endif // !defined _I_CORE_H