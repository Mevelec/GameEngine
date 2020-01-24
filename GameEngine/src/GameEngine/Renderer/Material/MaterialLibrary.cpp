#include "hzpch.h"

#include <filesystem>

#include "MaterialLibrary.h"

#include <rapidjson/document.h>
#include "rapidjson/filereadstream.h"

namespace GameEngine {
	void MaterialLibrary::add(const Ref<Material>& material)
	{
		auto& name = material->getName();
		GE_CORE_ASSERT(!this->exists(name), "Material already exist");
		this->materials[name] = material;
	}

	void MaterialLibrary::add(const std::string& name, const Ref<Material>& material)
	{
		GE_CORE_ASSERT(!this->exists(name), "Material already exist");
		this->materials[name] = material;
	}

	Ref<Material> MaterialLibrary::get(const std::string& name)
	{
		GE_CORE_ASSERT(this->exists(name), "Material not found");
		return this->materials[name];
	}

	bool MaterialLibrary::exists(const std::string& name)
	{
		return this->materials.find(name) != this->materials.end();
	}



	Ref<Material> MaterialParser::loadJson(const std::string& path)
	{
		//// PARSE MATERIAL.json
		FILE* fb = fopen(path.c_str(), "r");
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

		Ref<Shader> shader = Shader::Create(
			d["shader"]["name"].GetString(),
			d["shader"]["path"].GetString()
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

				Ref<Texture> texture;
				if (values["type"] == "relative")
				{
					std::filesystem::path folderPath(path);
					auto a = folderPath.parent_path().append(values["path"].GetString());
					texture = Texture2D::Create(a.string());
				}
				else if(values["type"] == "absolute")
				{
					texture = Texture2D::Create(values["path"].GetString());
				}
				else
				{
					GE_ASSERT(false, "Material Texture pathType invalid");
				}

				material->addComponent(
					object["name"].GetString(),
					texture,
					values["slot"].GetInt()
				);
			}
			else
			{
				GE_ASSERT(false, "Material component type is unknow")
			}
		}

		return material;
	}

	std::string& MaterialParser::createPath(pathType type, const std::string& path)
	{
		if (type == pathType::relative)
		{
			std::filesystem::path folderPath(path);
			auto a = folderPath.parent_path().append(values["path"].GetString());
			texture = Texture2D::Create(a.string());
		}
		else if (type == pathType::absolute)
		{
			texture = Texture2D::Create(values["path"].GetString());
		}
		else
		{
			GE_ASSERT(false, "PathType not handled");
		}
	}
		
	pathType MaterialParser::stringToPathType(const std::string& type)
	{
		if (type == "absolute")
		{
			return pathType::absolute;
		}
		else if (type == "relative")
		{
			return pathType::relative;
		}
		else
		{
			return pathType::default;
		}
	}
}