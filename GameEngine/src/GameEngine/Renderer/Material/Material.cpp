#include "hzpch.h"

#include "Material.h"
#include "../Renderer.h"

#include "Plateform/OpenGl/OpenGLShader.h"

#include <rapidjson/document.h>
#include "rapidjson/filereadstream.h"



namespace GameEngine {

	Material::Material(const std::string& path)
	{
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

		assert(d.IsObject());

		assert(d.HasMember("name"));
		assert(d["name"].IsString());
		this->name = d["name"].GetString();

		assert(d.HasMember("shader"));
		assert(d["shader"].IsObject());
		assert(d["shader"].HasMember("name"));
		assert(d["shader"]["name"].IsString());
		assert(d["shader"].HasMember("path"));
		assert(d["shader"]["path"].IsString());
		this->shader = Shader::Create(
			d["shader"]["name"].GetString(), 
			d["shader"]["path"].GetString()
		);


		for each (auto& it in d["components"].GetArray() )
		{
			auto object = it.GetObject();
			std::string type = object["type"].GetString();
			if (type == "vec3")
			{
				this->addComponent(
					object["name"].GetString(),
					glm::fvec3(object["value"][0].GetFloat(), object["value"][1].GetFloat(), object["value"][2].GetFloat())
					);
			}
			else if (type == "texture")
			{
				Ref<Texture2D> texture = Texture2D::Create(object["path"].GetString());

				this->addComponent(
					object["name"].GetString(),
					texture,
					object["slot"].GetInt()
				);
			}
			else
			{
				GE_ASSERT(false, "Material component type is unknow")
			}
		}
		/*
		mat = 
		mat->addComponent("u_Color", glm::vec4(1, 0, 0, 1));
		mat->addComponent("u_Texture", 0);
		this->uv_texture = GameEngine::Texture2D::Create("assets/textures/uv_check.png");
		this->materialLib.add(mat);*/

	}

	Material::Material(const std::string& name, const Ref<Shader>& shader)
		: name(name)
	{
		this->shader = shader;
	}

	Material::Material(const Ref<Shader>& shader)
		: name(shader->getName())
	{
		this->shader = shader;
	}

	Material::~Material()
	{
	}

	void Material::bind(glm::mat4 viewProjectionMatrix, glm::mat4 transform) 
	{
		this->shader->bind();
		this->shader->setMat4("u_ViewProjectionMatrix", viewProjectionMatrix);
		this->shader->setMat4("u_Transform", transform);

		for each (Ref<MaterialComponent> comp in this->components)
		{
			comp->bind(this->shader);
		}
	}



	template<>
	void MaterialComponentImpl<Ref<Texture>>::bind(const Ref<Shader>& shader)
	{
		this->value->bind(this->slot);
		shader->setInt(this->name, this->slot);
	}
	template<>
	void MaterialComponentImpl<int>::bind(const Ref<Shader>& shader)
	{
		shader->setInt(this->name, this->value);
	}
	template<>
	void MaterialComponentImpl<glm::fvec3>::bind(const Ref<Shader>& shader)
	{
		shader->setFloat3(this->name, this->value);
	}
	template<>
	void MaterialComponentImpl<glm::fvec4>::bind(const Ref<Shader>& shader)
	{
		shader->setFloat4(this->name, this->value);
	}
	template<>
	void MaterialComponentImpl<glm::fmat4>::bind(const Ref<Shader>& shader)
	{
		shader->setMat4(this->name, this->value);
	}
}
