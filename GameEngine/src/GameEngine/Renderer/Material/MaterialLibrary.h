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
		void bind(const std::string& name, glm::mat4 viewProjectionMatrix, glm::mat4 transform);
		void bind(Ref<Material> mat, glm::mat4 viewProjectionMatrix, glm::mat4 transform);

		bool exists(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Material>> materials;
		std::string binded = "";

		GameEngine::ShaderLibrary shaderLib;



	// Singleton
	public:
		static MaterialLibrary& getInstance()
		{
			static MaterialLibrary    instance;
			return instance;
		}
	private:
		MaterialLibrary() {}

	public:
		MaterialLibrary(MaterialLibrary const&) = delete;
		void operator=(MaterialLibrary const&) = delete;
	};










	enum class PathType {
		default = 0,
		relative,
		absolute
	};
	//// PARSER
	class MaterialParser
	{
	public :
		Ref<Material> loadJson(const std::string& path);
		PathType stringToPathType(const std::string& type);
	private :
		static const std::string pathMaterialFolder;

		std::string createPath(const std::string& pathType, const std::string& path, const std::string& folderPath = "");
		std::string createPath(const PathType& pathType, const std::string& path, const std::string& folderPath = "");

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


