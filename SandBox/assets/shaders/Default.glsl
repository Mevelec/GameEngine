#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 0) in vec2 a_TextCoord;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_Transform;

out vec2 v_TextCoord;

void main()
{
	v_TextCoord = a_TextCoord;
	gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextCoord;

uniform sampler2D u_ColorTex;
uniform sampler2D u_MetalTex;
uniform sampler2D u_SpecuTex;


uniform vec3 u_Color;
uniform vec3 u_Metal;
uniform vec3 u_Specu;


void main()
{
	color = texture(u_ColorTex, v_TextCoord) * vec4(u_Color, 1.0f);
}
