#pragma once
#include "GameEngine/Core/Core.h"

#ifdef GE_PLATEFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv) {
	GameEngine::Log::Init();
	GE_CORE_WARN("Initialized Log !");
	GE_INFO("Initialized Log !");


	auto app = GameEngine::CreateApplication();
	app->run();
	delete app;
}

#endif // GE_PLATEFORM_WINDOWS
