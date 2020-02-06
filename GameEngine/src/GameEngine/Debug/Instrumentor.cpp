#include "hzpch.h"
#include "GameEngine/Debug/Instrumentor.h"

namespace GameEngine {
	Instrumentor::Instrumentor()
		: currentSession(nullptr)
	{
	}

	void Instrumentor::beginSession(const std::string& name, const std::string& filepath)
	{
		std::lock_guard lock(this->mutex);
		if (this->currentSession) {
			// If there is already a current session, then close it before beginning new one.
			// Subsequent profiling output meant for the original session will end up in the
			// newly opened session instead.  That's better than having badly formatted
			// profiling output.
			if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
				GE_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, this->currentSession->name);
			}
			this->internalEndSession();
		}
		this->outputStream.open(filepath);

		if (this->outputStream.is_open()) {
			this->currentSession = new InstrumentationSession({ name });
			this->writeHeader();
		}
		else {
			if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
				GE_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
			}
		}
	}

	void Instrumentor::endSession()
	{
		std::lock_guard lock(this->mutex);
		this->internalEndSession();
	}

	void Instrumentor::writeProfile(const ProfileResult& result)
	{
		std::stringstream json;

		std::string name = result.name;
		std::replace(name.begin(), name.end(), '"', '\'');

		json << std::setprecision(3) << std::fixed;
		json << ",{";
		json << "\"cat\":\"function\",";
		json << "\"dur\":" << (result.elapsedTime.count()) << ',';
		json << "\"name\":\"" << name << "\",";
		json << "\"ph\":\"X\",";
		json << "\"pid\":0,";
		json << "\"tid\":" << result.threadID << ",";
		json << "\"ts\":" << result.start.count();
		json << "}";

		std::lock_guard lock(this->mutex);
		if (this->currentSession) {
			this->outputStream << json.str();
			this->outputStream.flush();
		}
	}

	void Instrumentor::writeHeader()
	{
		this->outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
		this->outputStream.flush();
	}

	void Instrumentor::writeFooter()
	{
		this->outputStream << "]}";
		this->outputStream.flush();
	}

	// Note: you must already own lock on mutex before
	// calling InternalEndSession()
	void Instrumentor::internalEndSession() {
		if (this->currentSession) {
			this->writeFooter();
			this->outputStream.close();
			delete this->currentSession;
			this->currentSession = nullptr;
		}
	}
}

namespace GameEngine {
	InstrumentationTimer::InstrumentationTimer(const char* name)
		: name(name), stopped(false)
	{
		this->startTimepoint = std::chrono::steady_clock::now();
	}

	InstrumentationTimer::~InstrumentationTimer()
	{
		if (!this->stopped)
			this->stop();
	}

	void InstrumentationTimer::stop()
	{
		auto endTimepoint = std::chrono::steady_clock::now();
		auto highResStart = FloatingPointMicroseconds{ this->startTimepoint.time_since_epoch() };
		auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(this->startTimepoint).time_since_epoch();

		Instrumentor::Get().writeProfile({ this->name, highResStart, elapsedTime, std::this_thread::get_id() });

		this->stopped = true;
	}
}