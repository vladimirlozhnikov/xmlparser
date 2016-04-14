#if !defined ICALLBACK
#define ICALLBACK

#include "documentparameters.h"

class ICallback
{
	public:
		virtual void ElementParsed(XMLObject* _pXMLO) = 0;
};

#endif // !defined ICALLBACK