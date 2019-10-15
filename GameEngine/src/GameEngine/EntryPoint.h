#pragma once

#ifdef GE_PLATEFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv) {
	auto app = GameEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif // GE_PLATEFORM_WINDOWS
