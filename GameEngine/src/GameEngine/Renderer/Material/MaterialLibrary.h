#pragma once
#include "Material.h"

#include <glm/glm.hpp>

namespace GameEngine {
	class MaterialLibrary
	{
	public:
		void add(const Ref<Material>& material);
		void add(const std::string& name, const Ref<Material>& material);

		Ref<Material> get(const std::string& name);

		bool exists(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Material>> materials;
	};


	enum class pathType {
		default = 0,
		relative,
		absolute
	};
	//// PARSER
	class MaterialParser
	{


	public :
		Ref<Material> loadJson(const std::string& path);
		pathType stringToPathType(const std::string& type);

	private:
		std::string& createPath(pathType type, const std::string& path);

	public:
		static MaterialParser& getInstance()
		{
			static MaterialParser    instance;
			return instance;
		}
	private:
		MaterialParser() {}

	public:
		MaterialParser(MaterialParser const&) = delete;
		void operator=(MaterialParser const&) = delete;

	};
}


