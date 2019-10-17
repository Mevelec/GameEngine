#pragma once

#ifdef GE_PLATEFORM_WINDOWS
	#ifdef GE_BUILD_DLL
		#define  GE_API __declspec(dllexport)
	#else
		#define  GE_API __declspec(dllimport)
	#endif // GE_BUILD_DLL
#else
	#error GameEngine only support Windows 
#endif // GE_PLATEFORM_WINDOWS

#define BIT(x) (1 << x)