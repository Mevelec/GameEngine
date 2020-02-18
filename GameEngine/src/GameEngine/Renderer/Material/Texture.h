#pragma once

#include <string>
#include <vector>

namespace GameEngine {
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void setData(void* data, uint32_t size) = 0;

		virtual void bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};

	class Sampler
	{
	public:
		virtual void bind() const = 0;
		virtual void add(Ref<Texture> texture, int slot) = 0;
		virtual std::vector<int> getSlots() = 0;
	public:
		static Ref<Sampler> Create(std::vector<Ref<Texture>> textures);
		static Ref<Sampler> Create();
	private:
	};
}