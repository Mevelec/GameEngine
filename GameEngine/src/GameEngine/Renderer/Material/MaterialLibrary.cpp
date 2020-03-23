#include "hzpch.h"

#include <filesystem>

#include "MaterialLibrary.h"

#include <rapidjson/document.h>
#include "rapidjson/filereadstream.h"

namespace GameEngine {
	void MaterialLibrary::add(const Ref<Material>& material)
	{
		GE_PROFILE_FUNCTION();

		auto& name = material->getName();
		GE_CORE_ASSERT(!this->exists(name), "Material already exist");
		this->materials[name] = material;
	}

	void MaterialLibrary::add(const std::string& name, const Ref<Material>& material)
	{
		GE_PROFILE_FUNCTION();

		GE_CORE_ASSERT(!this->exists(name), "Material already exist");
		this->materials[name] = material;
	}

	Ref<Material> MaterialLibrary::get(const std::string& name)
	{
		GE_PROFILE_FUNCTION();

		GE_CORE_ASSERT(this->exists(name), "Material not found");
		return this->materials[name];
	}

	void MaterialLibrary::bind(const std::string& name, glm::mat4 viewProjectionMatrix, glm::mat4 transform)
	{
		auto material = this->get(name);
		this->bind(material, viewProjectionMatrix, transform);
	}

	void MaterialLibrary::bind(Ref<Material> mat, glm::mat4 viewProjectionMatrix, glm::mat4 transform)
	{
		if (mat->getName() != this->binded)
		{
			mat->bind();
			this->binded = mat->getName();
		}
		mat->getShader()->setMat4("u_ViewProjectionMatrix", viewProjectionMatrix);
		mat->getShader()->setMat4("u_Transform", transform);
	}


	bool MaterialLibrary::exists(const std::string& name)
	{
		GE_PROFILE_FUNCTION();

		return this->materials.find(name) != this->materials.end();
	}
}

namespace GameEngine {


	static const std::string pathMaterialFolder = "assets/Materials";


	Ref<Material> MaterialParser::loadJson(const std::string& path)
	{
		GE_PROFILE_FUNCTION();

		//// PARSE MATERIAL.json
		FILE* fb = fopen(path.c_str(), "r");
		std::filesystem::path folderPath(path);
		GE_ASSERT(fb != 0, "Failed to open Material file.json");

		char buffer[65536];
		rapidjson::FileReadStream s(fb, buffer, sizeof(buffer));
		fclose(fb);

		rapidjson::Document d;
		d.ParseStream(s);

		if (d.HasParseError())
		{
			GE_ASSERT(false, "Error : {0}    Offset : {2}", d.GetParseError(), d.GetErrorOffset());
		}

		//// ASSERT CREATION MATERIAL
		assert(d.IsObject());

		assert(d.HasMember("name"));
		assert(d["name"].IsString());

		assert(d.HasMember("shader"));
		assert(d["shader"].IsObject());
		assert(d["shader"].HasMember("name"));
		assert(d["shader"]["name"].IsString());
		assert(d["shader"].HasMember("path"));
		assert(d["shader"]["path"].IsString());
		Ref<Shader> shader;
		PathType pathType = this->stringToPathType(d["shader"]["type"].GetString());

		
		shader = Shader::Create(
			d["shader"]["name"].GetString(), 
			this->createPath(
				d["shader"]["type"].GetString(),
				d["shader"]["path"].GetString(),
				folderPath.parent_path().string()
			)
		);

		Ref<Material> material = CreateRef<Material>(d["name"].GetString(), shader);

		for each (auto & it in d["components"].GetArray())
		{
			auto object = it.GetObject();
			std::string type = object["type"].GetString();
			if (type == "vec3")
			{
				material->addComponent(
					object["name"].GetString(),
					glm::fvec3(
						object["value"][0].GetFloat(),
						object["value"][1].GetFloat(),
						object["value"][2].GetFloat()
					)
				);
			}
			if (type == "vec4")
			{
				material->addComponent(
					object["name"].GetString(),
					glm::fvec4(
						object["value"][0].GetFloat(), 
						object["value"][1].GetFloat(), 
						object["value"][2].GetFloat(), 
						object["value"][3].GetFloat()
					)
				);
			}
			else if (type == "texture")
			{
				assert(object["value"].IsObject());
				auto values = object["value"].GetObject();
				assert(values["type"].IsString());
				assert(values["path"].IsString());
				assert(values["slot"].IsInt());

				Ref<Texture> texture = Texture2D::Create(
					this->createPath(
						values["type"].GetString(),
						values["path"].GetString(),
						folderPath.parent_path().string()
					)
				);
				material->addComponent(
					object["name"].GetString(),
					texture,
					values["slot"].GetInt()
				);
			}
			else if(type == "float")
			{
				material->addComponent(
					object["name"].GetString(),
					(float)(object["value"].GetDouble())
				);
			}
			else
			{
				GE_ASSERT(false, "Material component type is unknow")
			}
		}

		return material;
	}
		
	PathType MaterialParser::stringToPathType(const std::string& type)
	{
		if (type == "absolute")
		{
			return PathType::absolute;
		}
		else if (type == "relative")
		{
			return PathType::relative;
		}
		else
		{
			return PathType::default;
		}
	}

	std::string MaterialParser::createPath(const std::string& pathType, const std::string& path, const std::string& folderPath)
	{
		return this->createPath(
			this->stringToPathType(pathType),
			path,
			folderPath
		);
	}

	std::string MaterialParser::createPath(const PathType& pathType, const std::string& path, const std::string& folderPath)
	{
		if (pathType == PathType::relative)
		{
			return folderPath +"/"+ path;
		}
		else if (pathType == PathType::absolute)
		{
			return path;
		}
		else
		{
			GE_ASSERT(false, "Material Texture pathType invalid");
		}
	}
}