 #include "hzpch.h"
#include "Plateform/OpenGl/OpenGLTexture.h"

#include <stb_image.h>

namespace GameEngine {
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: width(width), height(height)
	{
		GE_PROFILE_FUNCTION();

		// Determine image pixels Format and channel
		this->internalFormat = GL_RGBA8;
		this->dataFormat = GL_RGBA;

		// Create Texture
		glCreateTextures(GL_TEXTURE_2D, 1, &this->rendererID);
		glTextureStorage2D(this->rendererID, 1, this->internalFormat, this->width, this->height);

		glTextureParameteri(this->rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(this->rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(this->rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: path(path)
	{
		GE_PROFILE_FUNCTION();

		int channels;
		int width, height;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			GE_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string& path)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		GE_ASSERT(data, "Failed to load image");

		this->width = width;
		this->height = height;

		// Determine image pixels Format and channel
		switch (channels) {
		case 1:
			this->internalFormat = GL_R8;
			this->dataFormat = GL_R;
			break;
		case 3:
			this->internalFormat = GL_RGB8;
			this->dataFormat = GL_RGB;
			break;
		case 4:
			this->internalFormat = GL_RGBA8;
			this->dataFormat = GL_RGBA;
			break;

		}

		GE_ASSERT(internalFormat && dataFormat, "Image Format not supported");


		// Create Texture
		glCreateTextures(GL_TEXTURE_2D, 1, &this->rendererID);
		glTextureStorage2D(this->rendererID, 1, this->internalFormat, this->width, this->height);

		glTextureParameteri(this->rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(this->rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(this->rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTextureSubImage2D(this->rendererID, 0, 0, 0, this->width, this->height, this->dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		GE_PROFILE_FUNCTION();

		glDeleteTextures(1, &this->rendererID);
	}

	void OpenGLTexture2D::setData(void* data, uint32_t size)
	{
		GE_PROFILE_FUNCTION();

		uint32_t bpp = this->dataFormat == GL_RGBA ? 4 : 3;
		GE_CORE_ASSERT(size == this->width * this->height * bpp, "Data must be entire texture");
		glTextureSubImage2D(this->rendererID, 0, 0, 0, this->width, this->height, this->dataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		GE_PROFILE_FUNCTION();

		glBindTextureUnit(slot, this->rendererID);
	}

}

namespace GameEngine {

	OpenGLSampler::OpenGLSampler() {

	}

	OpenGLSampler::OpenGLSampler(std::vector<Ref<Texture>> texures) {
		this->texures = texures;
	}

	void OpenGLSampler::add(Ref<Texture> texture, int slot) {
		this->texures.push_back(texture);
		this->slots.push_back(slot);
	}

	void OpenGLSampler::bind() const {
		for (std::size_t i = 0; i < this->texures.size(); ++i) {
			this->texures[i]->bind(this->slots[i]);
		}

	}

	std::vector<int> OpenGLSampler::getSlots() {
		return this->slots;
	}

}