#include "hzpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace GameEngine {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: path(path)
	{
		int channels;
		int width, height;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		GE_ASSERT(data, "Failed to load image");

		this->width = width;
		this->height = height;

		// Determine image pixels Format and channel
		unsigned int size;
		unsigned int type;
		switch (channels) {
		case 3:
			size = GL_RGB8;
			type = GL_RGB;
			break;
		case 4:
			size = GL_RGBA8;
			type = GL_RGBA;
			break;
		default:
			GE_ASSERT(false, "Image colorFormat not handled");
			break;
		}

		// Create Texture
		glCreateTextures(GL_TEXTURE_2D, 1, &this->rendererID);
		glTextureStorage2D(this->rendererID, 1, size, this->width, this->height);

		glTextureParameteri(this->rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(this->rendererID, 0, 0, 0, this->width, this->height, type, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &this->rendererID);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, this->rendererID);
	}
}