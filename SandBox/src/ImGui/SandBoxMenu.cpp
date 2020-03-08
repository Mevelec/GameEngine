#include "SandBoxMenu.h"
#include <imgui/imgui.h>

SandBoxMenu::SandBoxMenu()
{
	GameEngine::Application::get().GetWindow();
}

void SandBoxMenu::render()
{
	// Menu Bar
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_MenuBar;

	ImGui::Begin("GameEngine", NULL, window_flags);
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Settings"))
			{
				if (ImGui::MenuItem("Open..", NULL)) {}
				if (ImGui::MenuItem("Save", NULL)) {}
				if (ImGui::MenuItem("Close", NULL)) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Components"))
			{
				if (ImGui::MenuItem("ChunkManager", NULL, &show_ChunkManger)) { activate(&show_ChunkManger); }
				if (ImGui::MenuItem("Camera", NULL, &show_CameraManger)) { activate(&show_CameraManger); }
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}


		if (show_ChunkManger)            showChunkManager(&show_ChunkManger);
		if (show_CameraManger)           showCameraManager(&show_CameraManger);


	}
	ImGui::End();
}

void SandBoxMenu::activate(bool* p_open)
{
	show_ChunkManger = false;
	show_CameraManger = false;

	*p_open = true;
}


static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void SandBoxMenu::showChunkManager(bool* p_open)
{
	ImGui::LabelText("", "ChunkManager");
	static uint32_t i1 = 1;
	if (ImGui::DragScalar("drag s8", ImGuiDataType_U32, &i1, 1, 0, NULL))
	{
		auto e = GameEngine::ChunkSetRenderView(i1);
		GameEngine::Application::get().onEvent(e);
	}

	if (ImGui::Button("Apply"))
	{
		auto e = GameEngine::ChunkDoReload();
		GameEngine::Application::get().onEvent(e);
	}
}
void SandBoxMenu::showCameraManager(bool* p_open)
{
	ImGui::LabelText("", "Camera Position :");
}

