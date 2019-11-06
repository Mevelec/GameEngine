#include "hzpch.h"
#include "Plateform/OpenGl/OpenGlBuffer.h"

#include <glad/glad.h>

namespace GameEngine {

	////////////////////////////////////////////////////////
	// VERTEXBUFFER /////////////////////////////////////////
	////////////////////////////////////////////////////////

	OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &this->rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, this->rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGlVertexBuffer::~OpenGlVertexBuffer()
	{
		glDeleteBuffers(1, &this->rendererID);
	}

	void OpenGlVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->rendererID);
	}

	void OpenGlVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	////////////////////////////////////////////////////////
	// INDEXBUFFER /////////////////////////////////////////
	////////////////////////////////////////////////////////
	OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indices, uint32_t count)
		:count(count)
	{
		glCreateBuffers(1, &this->rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGlIndexBuffer::~OpenGlIndexBuffer()
	{
		glDeleteBuffers(1, &this->rendererID);
	}

	void OpenGlIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererID);
	}

	void OpenGlIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}