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
		GLenum internalFormat, dataFormat;
		switch (channels) {
		case 1:
			internalFormat = GL_R8;
			dataFormat = GL_R;
			break;
		case 3:
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
			break;
		case 4:
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			break;

		}
		GE_ASSERT(internalFormat && dataFormat, "Image Format not supported");


		// Create Texture
		glCreateTextures(GL_TEXTURE_2D, 1, &this->rendererID);
		glTextureStorage2D(this->rendererID, 1, internalFormat, this->width, this->height);

		glTextureParameteri(this->rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(this->rendererID, 0, 0, 0, this->width, this->height, dataFormat, GL_UNSIGNED_BYTE, data);

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