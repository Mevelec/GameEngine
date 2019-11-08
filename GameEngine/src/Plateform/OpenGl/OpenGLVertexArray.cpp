#include "hzpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace GameEngine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case GameEngine::ShaderDataType::Float:
			return GL_FLOAT;
		case GameEngine::ShaderDataType::Float2:
			return GL_FLOAT;
		case GameEngine::ShaderDataType::Float3:
			return GL_FLOAT;
		case GameEngine::ShaderDataType::Float4:
			return GL_FLOAT;
		case GameEngine::ShaderDataType::Mat3:
			return GL_FLOAT;
		case GameEngine::ShaderDataType::Mat4:
			return GL_FLOAT;
		case GameEngine::ShaderDataType::Int:
			return GL_INT;
		case GameEngine::ShaderDataType::Int2:
			return GL_INT;
		case GameEngine::ShaderDataType::Int3:
			return GL_INT;
		case GameEngine::ShaderDataType::Int4:
			return GL_INT;
		case GameEngine::ShaderDataType::Bool:
			return GL_BOOL;
		}

		GE_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &this->rendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(this->rendererID);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer)
	{
		GE_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(this->rendererID);
		vertexBuffer->bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.getComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.offset
			);
			index++;
		}

		this->vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer)
	{
		glBindVertexArray(this->rendererID);
		indexBuffer->bind();

		this->indexBuffer = indexBuffer;
	}
}
