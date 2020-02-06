#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>

namespace GameEngine {

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string name;

		FloatingPointMicroseconds start;
		std::chrono::microseconds elapsedTime;
		std::thread::id threadID;
	};

	struct InstrumentationSession
	{
		std::string name;
	};

	class Instrumentor
	{
	private:
		std::mutex mutex;
		InstrumentationSession* currentSession;
		std::ofstream outputStream;
	public:
		Instrumentor();

		void beginSession(const std::string& name, const std::string& filepath = "results.json");

		void endSession();

		void writeProfile(const ProfileResult& result);

		static Instrumentor& Get() {
			static Instrumentor instance;
			return instance;
		}

	private:

		void writeHeader();

		void writeFooter();

		// Note: you must already own lock on mutex before
		// calling InternalEndSession()
		void internalEndSession();

	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name);

		~InstrumentationTimer();

		void stop();
	private:
		const char* name;
		std::chrono::time_point<std::chrono::steady_clock> startTimepoint;
		bool stopped;
	};
}

#define GE_PROFILE 0
#if GE_PROFILE
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define GE_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define GE_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define GE_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define GE_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define GE_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define GE_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define GE_FUNC_SIG __func__
	#else
		#define GE_FUNC_SIG "GE_FUNC_SIG unknown!"
	#endif

	#define GE_PROFILE_BEGIN_SESSION(name, filepath) ::GameEngine::Instrumentor::Get().beginSession(name, filepath)
	#define GE_PROFILE_END_SESSION() ::GameEngine::Instrumentor::Get().endSession()
	#define GE_PROFILE_SCOPE(name) ::GameEngine::InstrumentationTimer timer##__LINE__(name);
	#define GE_PROFILE_FUNCTION() GE_PROFILE_SCOPE(GE_FUNC_SIG)
#else
	#define GE_PROFILE_BEGIN_SESSION(name, filepath)
	#define GE_PROFILE_END_SESSION()
	#define GE_PROFILE_SCOPE(name)
	#define GE_PROFILE_FUNCTION()
#endif