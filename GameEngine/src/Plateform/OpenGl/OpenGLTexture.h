#pragma once

#include <glad/glad.h>

#include "GameEngine/Renderer/Material/Texture.h"

namespace GameEngine {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual inline uint32_t getWidth() const override { return this->width; };
		virtual inline uint32_t getHeight() const override { return this->height; };

		virtual void setData(void* data, uint32_t size) override;

		virtual void bind(uint32_t slot = 0) const override;
	
	private:
		std::string path;
		uint32_t width, height;
		uint32_t rendererID;
		GLenum internalFormat, dataFormat;
	};
}