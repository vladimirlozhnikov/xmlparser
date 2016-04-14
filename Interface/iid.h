#if !defined _IID_H
#define _IID_H


class IID_RESULTS
{
	public:
		enum E_QUERY_RETURN
		{
			EID_OK,
			EID_FALSE
		};
};



class IID_QUERY
{
	public:
		enum E_QUERY
		{
			EASCII_DISPATCHER,
			ECALLBACK_DISPATCHER,
			EBRACKER_DISPATCHER
		};
};


#endif // !defined _IID_H