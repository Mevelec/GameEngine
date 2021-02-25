#pragma once

#include <vector>

#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace GameEngine {
	class  MaterialComponent;

	class Material
	{
	public :
		Material(const Ref<Shader>& shader);
		Material(const std::string& name, const Ref<Shader>& shader);

		~Material();

		const inline std::string& getName() const { return this->name; };

		const inline Ref<Shader> getShader() const { return this->shader; };

		void bind();

		template<typename  T>
		void addComponent(const std::string& name, const T& value, uint32_t slot = 0)
		{
			auto comp = GameEngine::MaterialComponent::Create(name, value, slot);
			this->components.push_back(comp);
		}

	protected:
		std::string name;
		Ref<Shader> shader;

		std::vector<Ref<MaterialComponent>> components;
		
	};


	// The Interface
	class  MaterialComponent
	{
	public:
		virtual void bind(const Ref<Shader>& shader) = 0;

		template<class T>
		static Ref<MaterialComponent> Create(const std::string& name, T value, uint32_t slot = 0)
		{
			return CreateRef<MaterialComponentImpl<T>>(name, value, slot);
		};
	};

	template<class T>
	class MaterialComponentImpl : public MaterialComponent
	{

	public:
		MaterialComponentImpl(const std::string& name, const T& value, uint32_t slot) { 
			static_assert(
				std::is_same<T, int>::value
				|| std::is_same<T, Ref<Texture>>::value
				|| std::is_same<T, Ref<Sampler>>::value
				|| std::is_same<T, glm::fvec2>::value
				|| std::is_same<T, glm::fvec3>::value
				|| std::is_same<T, glm::fvec4>::value
				|| std::is_same<T, glm::fmat4>::value
				|| std::is_same<T, float>::value,
				"MaterialComponent can not handle this type");
			this->name = name; 
			this->value = value; 
			this->slot = slot;
		};
		virtual void bind(const Ref<Shader>& shader) override;
	private:
		std::string name;
		uint32_t slot;
		T value;
	};

}
