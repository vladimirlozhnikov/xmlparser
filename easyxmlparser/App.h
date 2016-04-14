// App.h: interface for the App class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APP_H__FA173B3A_4C79_4432_997B_E8C201746080__INCLUDED_)
#define AFX_APP_H__FA173B3A_4C79_4432_997B_E8C201746080__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Core.h"

class App  
{
	public:
		static App* Instance();
		void Start();
		void Stop();
		ICore* GetCore();

		void SetHinstance(HINSTANCE _hInstance);
		HINSTANCE GetHinstance();

	private:
		App();
		virtual ~App();

		static App* app_;
		ICore* core_;
		HINSTANCE hInstance_;
};

#endif // !defined(AFX_APP_H__FA173B3A_4C79_4432_997B_E8C201746080__INCLUDED_)
