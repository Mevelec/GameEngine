#pragma once

#include "GameEngine/Renderer/ITexture.h"

namespace GameEngine {

	class OpenGLTexture2D : public ITexture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual inline uint32_t getWidth() const override { return this->width; };
		virtual inline uint32_t getHeight() const override { return this->height; };

		virtual void bind(uint32_t slot = 0) const override;
	
	private:
		std::string path;
		uint32_t width, height;
		uint32_t rendererID;
	};
}