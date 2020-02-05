#pragma once

#include <vector>
#include <chrono>

namespace Profiler {
	struct ProfilResult
	{
		const char* name;
		float time;
	};

	std::vector<ProfilResult> profile;


	template<typename Fn>
	class Timer
	{
	public:
		Timer(const char* name, Fn&& func)
			: name(name), func(func), stopped(false)
		{
			this->startTimepoint = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			if (!this->stopped)
				this->stop();
		}

		void stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();


			std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(endTimepoint - this->startTimepoint);

			this->stopped = true;

			this->func({ this->name, time_span.count() });
		}

	private:
		const char* name;
		Fn func;
		std::chrono::time_point<std::chrono::steady_clock> startTimepoint;
		bool stopped;
	};
}

#define PROFILE_SCOPE(name) Profiler::Timer timer##__LINE__(name, [&](Profiler::ProfilResult profilResult) { Profiler::profile.push_back(profilResult);  })
