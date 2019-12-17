#pragma once

#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace GameEngine {
	class Material
	{
	public :
		virtual ~Material() = default;

		const inline Ref<Shader> getShader() { return this->shader; };
		virtual void bind() const = 0;

		static Ref<Material> Create();

	protected:
		Ref<Shader> shader;

		Ref<GameEngine::Texture> diffuseTex;
		glm::vec3 diffuseColor = { 0.f, 0.f, 0.f };

		Ref<GameEngine::Texture> metallicTex;
		glm::vec3 metallicColor = { 0.f, 0.f, 0.f };

		Ref<GameEngine::Texture> specularTex;
		glm::vec3 specularColor = { 0.5f, 0.5f, 0.5f };

		Ref<GameEngine::Texture> normalTex;		
	};
}

/*


		What if I want to draw vertices with colors only?

Use a solid white texture (a 1x1 texture is fine).

		What if I want to draw image by texture only?

Set the colour to white.

		gl_FragColor = texture2D(uTexture, texCoord) + uColor;

It’s more common to multiply the texture with the colour. The most common use of a texture is as a diffuse reflection map, indicating the proportion of incoming light which is reflected. If you’re adding them, use black (rather than white) to leave the colour unchanged.

		Yes, you can swith between glsl programs by glUseProgram, but create program, compile, link, switch is not the zero cost.

You don’t have to re-create the program object each time. You just need to call glUseProgram to select the program. But for something this simple, you may as well use one program and just change the uniforms.
*/
