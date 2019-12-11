#pragma once

#include <memory>

#ifdef GE_PLATEFORM_WINDOWS
	#if GE_DYNAMIC_LINK
		#ifdef GE_BUILD_DLL
			#define  GE_API __declspec(dllexport)
		#else
			#define  GE_API __declspec(dllimport)
		#endif // GE_BUILD_DLL
	#else
		#define GE_API
	#endif
#else
	#error GameEngine only support Windows 
#endif // GE_PLATEFORM_WINDOWS

#ifdef GE_DEBUG
	#define GE_ENABLE_ASSERTS
#endif // GE_DEBUG

#ifdef GE_ENABLE_ASSERTS
	#define GE_ASSERT(x, ...) {if(!(x)){GE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GE_CORE_ASSERT(x, ...) {if(!(x)){GE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GE_ASSERT(x, ...)
	#define GE_CORE_ASSERT(x, ...)
#endif // GE_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace GameEngine {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}