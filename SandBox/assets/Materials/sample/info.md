# Sample Material

## Infos
the `resources` folder is optional.

the `info.md` file is optional.

the `configuration.json` is mandatory.

## configuration.json
The `configuration.json` file descripe the material, it must comply the schema of configuration found at `.......`.

components availables types :
* vec3 => `MaterialComponent<glm::fvec3>`
* vec4 => `MaterialComponent<glm::fvec4>`
* texture => `MaterialComponent<Texture>`
	* need a specified slot

## resources folder
The `resources` folder may contain resources usefull to a material.
As `MaterialComonents` data like a `Texture` or a `shader` file.
These resources may be available only by this Material.
