#include "hzpch.h"
#include "Plateform/OpenGl/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace GameEngine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:
			return GL_FLOAT;
		case ShaderDataType::Float2:
			return GL_FLOAT;
		case ShaderDataType::Float3:
			return GL_FLOAT;
		case ShaderDataType::Float4:
			return GL_FLOAT;
		case ShaderDataType::Mat3:
			return GL_FLOAT;
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
			return GL_INT;
		case ShaderDataType::Int2:
			return GL_INT;
		case ShaderDataType::Int3:
			return GL_INT;
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		}

		GE_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		GE_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		GE_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &this->rendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		GE_PROFILE_FUNCTION();

		glBindVertexArray(this->rendererID);
	}

	void OpenGLVertexArray::unbind() const
	{
		GE_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer)
	{
		GE_PROFILE_FUNCTION();

		GE_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(this->rendererID);
		vertexBuffer->bind();

		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(this->vertexBufferIndex);
			glVertexAttribPointer(
				this->vertexBufferIndex,
				element.getComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)(intptr_t)element.offset
			);
			vertexBufferIndex++;
		}

		this->vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const Ref<IIndexBuffer>& indexBuffer)
	{
		GE_PROFILE_FUNCTION();

		glBindVertexArray(this->rendererID);
		indexBuffer->bind();

		this->indexBuffer = indexBuffer;
	}
}
