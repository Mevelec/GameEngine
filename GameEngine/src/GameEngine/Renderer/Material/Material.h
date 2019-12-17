#pragma once

#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace GameEngine {
	class Material
	{
	public :
		Material();

		const inline Ref<Shader> getShader() { return this->shader; };
		void bind();

	private:
		Ref<Shader> shader;

		Ref<GameEngine::Texture> diffuse;
		glm::vec3 diffuseColor;

		//std::unordered_map<std::string, Ref<Texture>> texMap;
		//Diffuse
		//Mettalic
		//Speculars
		//Normal
		
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
