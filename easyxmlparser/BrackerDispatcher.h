#pragma once
#include "../Interface/IBrackerDispatcher.h"
#include "Bracker.h"

class BrackerDispatcher : public IBrackerDispatcher
{
	public:
		BrackerDispatcher();
		virtual ~BrackerDispatcher();

		void AddRef();
		void DecRef();
		void Release();
		void Initial();

		Bracker& ParseAndGetBracker(string _xmlDocument);
		Bracker& GetBracker(XMLObject* _XMLO, string _xmlDocument);

		IID_RESULTS::E_QUERY_RETURN ReleaseBracker(Bracker& _brackerDispatcher);

	private:
		Bracker* bracker_;
};
