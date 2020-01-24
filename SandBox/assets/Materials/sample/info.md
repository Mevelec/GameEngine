# Sample Material

## Infos
the `resources` folder is optional.

the `info.md` file is optional.

the `configuration.json` is mandatory.

## configuration.json
The `configuration.json` file descripe the material, it must comply the schema of configuration found at `.......`.

a component must have a `name`, `type`, `value`.
The name must be the same than the parameters required in the shader.

components types availables  :
* vec3 => `MaterialComponent<glm::fvec3>`
	* value is an array of 3 values
* vec4 => `MaterialComponent<glm::fvec4>`
	* value is an array of 4 values
* texture => `MaterialComponent<Texture>`
	* `value` is a string naminge the texture
	* `path` path from project root to image
	* need a specified `slot`

## resources folder
The `resources` folder may contain resources usefull to a material.
As `MaterialComonents` data like a `Texture` or a `shader` file.
These resources may be available only by this Material.
