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

#ifdef GE_ENABLE_ASSERTS
	// Windows only debugbreak for now...
	#define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GE_CORE_ASSERT(x, ...) { if(!(x)) { GE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GE_ASSERT(x, ...) 
	#define GE_CORE_ASSERT(x, ...) 
#endif

//Macro to left-shift a bit of x position
#define BIT(x) (1 << x)