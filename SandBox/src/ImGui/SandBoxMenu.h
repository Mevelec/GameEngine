#pragma once
#include <GameEngine.h>

#include <vector>

class SandBoxMenu : public GameEngine::Renderable
{
public:
	SandBoxMenu();

	void render() override;
private:
	void showChunkManager(bool* p_open);
	void showCameraManager(bool* p_open);

	void activate(bool* p_open);
private:
	bool show_ChunkManger = false;
	bool show_CameraManger = false;
};
