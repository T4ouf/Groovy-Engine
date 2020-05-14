#pragma once

#ifdef GE_PLATFORM_WINDOWS
	
	#ifdef GE_BUILD_DLL
		//Engine side => We export the DLL
		#define GE_API __declspec(dllexport)
	#else
		//Application side => we import the DLL
		#define GE_API __declspec(dllimport)
	#endif
#else
	#error The Groovy Engine only supports Windows!
#endif