#pragma once

namespace GameEngine {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case GameEngine::ShaderDataType::Float:
			return 4;
		case GameEngine::ShaderDataType::Float2:
			return 4 * 2;
		case GameEngine::ShaderDataType::Float3:
			return 4 * 3;
		case GameEngine::ShaderDataType::Float4:
			return 4 * 4;
		case GameEngine::ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case GameEngine::ShaderDataType::Mat4:
			return 4 * 4 * 4;
		case GameEngine::ShaderDataType::Int:
			return 4;
		case GameEngine::ShaderDataType::Int2:
			return 4 *2;
		case GameEngine::ShaderDataType::Int3:
			return 4 * 3;
		case GameEngine::ShaderDataType::Int4:
			return 4 * 4;
		case GameEngine::ShaderDataType::Bool:
			return 1;
		}

		GE_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}

	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t offset;
		uint32_t size;
		bool normalized;

		BufferElement() {};

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(0)
		{
		}

		uint32_t getComponentCount() const
		{
			switch (this->type)
			{
			case GameEngine::ShaderDataType::Float:
				return 1;
			case GameEngine::ShaderDataType::Float2:
				return 2;
			case GameEngine::ShaderDataType::Float3:
				return 3;
			case GameEngine::ShaderDataType::Float4:
				return 4;
			case GameEngine::ShaderDataType::Mat3:
				return 3 * 3;
			case GameEngine::ShaderDataType::Mat4:
				return 4 * 4;
			case GameEngine::ShaderDataType::Int:
				return 1;
			case GameEngine::ShaderDataType::Int2:
				return 2;
			case GameEngine::ShaderDataType::Int3:
				return 3;
			case GameEngine::ShaderDataType::Int4:
				return 4;
			case GameEngine::ShaderDataType::Bool:
				return 1;
			}

			GE_CORE_ASSERT(false, "Unknow ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {};
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements(elements)
		{
			CalculatOffsetAndStride();
		}

		inline const uint32_t& getStride() const { return this->stride; }
		inline const std::vector<BufferElement>& getElements() const { return this->elements; }

		std::vector<BufferElement>::iterator begin() { return this->elements.begin(); }
		std::vector<BufferElement>::iterator end() { return this->elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return this->elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return this->elements.end(); }

		bool inline empty() { return this->elements.empty(); };

	private:
		void CalculatOffsetAndStride()
		{
			uint32_t offset = 0;
			stride = 0;
			for (auto& element : elements)
			{
				element.offset = offset;
				offset += element.size;
				stride += element.size;
			}
		}
	private: 
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};
	
	class IVertexBuffer
	{
	public:
		virtual ~IVertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const  = 0;

		virtual const BufferLayout& getLayout() const = 0;
		virtual void setLayout(const BufferLayout& layout) = 0;

		static Ref<IVertexBuffer> Create(float* vertices, uint32_t size);
	};

	class IIndexBuffer
	{
	public:
		virtual ~IIndexBuffer() = default;

		virtual void bind() const  = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static Ref<IIndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}