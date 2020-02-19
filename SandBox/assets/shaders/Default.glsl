#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexId;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Transform;

out vec3 v_Position;
out vec2 v_TexCoord;
out vec4 v_Color;
flat out int v_TexId;


void main()
{
	v_Position = a_Position;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexId = int(a_TexId);

	gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_Position;
in vec2 v_TexCoord;
in vec4 v_Color;
flat in int v_TexId;

uniform vec4 u_Color;

uniform float u_TilingFactor;
uniform sampler2D u_Textures[2];

void main()
{
	color =  texture(u_Textures[v_TexId], v_TexCoord * u_TilingFactor) * u_Color * v_Color;
}