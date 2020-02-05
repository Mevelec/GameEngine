#pragma once

#include <memory>

#ifdef _WIN32
	/* Windows x64/x86 */
	#if _WIN64
		/* Windows x64  */
		#define GE_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define GE_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define GE_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
	 /* We also have to check __ANDROID__ before __linux__
	  * since android is based on the linux kernel
	  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define GE_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define GE_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

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


#define GE_PROFILE 1
#if GE_PROFILE
	#define GE_PROFILE_BEGIN_SESSION(name, filepath) ::GameEngine::Instrumentor::get().beginSession(name, filepath)
	#define GE_PROFILE_END_SESSION() ::GameEngine::Instrumentor::get().endSession()
	#define GE_PROFILE_SCOPE(name) ::GameEngine::InstrumentationTimer timer##__LINE__(name);
	#define GE_PROFILE_FUNCTION() GE_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define GE_PROFILE_BEGIN_SESSION(name, filepath)
	#define GE_PROFILE_END_SESSION()
	#define GE_PROFILE_SCOPE(name)
	#define GE_PROFILE_FUNCTION()
#endif 


#define BIT(x) (1 << x)

#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace GameEngine {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}



	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}