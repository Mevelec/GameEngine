#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Core/Application.h"
#include "GameEngine/Debug/Instrumentor.h"

#ifdef GE_PLATEFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv) {
	GameEngine::Log::Init();

	GE_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = GameEngine::CreateApplication();
	GE_PROFILE_END_SESSION();

	GE_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->run();
	GE_PROFILE_END_SESSION();

	GE_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Shutdown.json");
	delete app;
	GE_PROFILE_END_SESSION();
}

#endif // GE_PLATEFORM_WINDOWS
