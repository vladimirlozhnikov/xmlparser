#if !defined _I_PLUGIN_CORE_H
#define _I_PLUGIN_CORE_H

#include "iid.h"

class IPluginCore
{
	public:
		virtual void Initial() = 0;
		virtual void Release() = 0;
		virtual void AddRef() = 0;
		virtual void DecRef() = 0;

	protected:
		UINT iRef_;
};


#endif // !defined _I_PLUGIN_CORE_H