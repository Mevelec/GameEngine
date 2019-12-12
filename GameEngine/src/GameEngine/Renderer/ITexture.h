#pragma once

#include <string>

namespace GameEngine {
	class ITexture
	{
	public:
		virtual ~ITexture() = default;
		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void bind(uint32_t slot = 0) const = 0;
	};

	class ITexture2D : public ITexture
	{
	public:
		static Ref<ITexture2D> Create(const std::string& path);
	};
}