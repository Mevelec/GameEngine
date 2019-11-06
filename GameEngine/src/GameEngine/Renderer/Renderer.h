#pragma once

namespace GameEngine {
	enum class RendererAPI
	{
		None = 0,
		OpengGL = 1,
	};

	class IRenderer
	{
	public:
		inline static RendererAPI GetAPI() { return rendererAPI; }
		inline static RendererAPI SetAPI(RendererAPI api) { rendererAPI = api; }
	private:
		static RendererAPI rendererAPI;
	};
}