#type vertex
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textureCoords;
layout(location = 2) in vec3 in_normals;

out vec2 v_textureCoords;
out vec3 v_normals;

uniform mat4 u_MVP;

void main()
{
	v_textureCoords = in_textureCoords;
	v_normals = in_normals;
	gl_Position = u_MVP * vec4(in_position, 1.0);
}
#type fragment
#version 330 core

layout(location = 0) out vec4 out_color;

uniform vec4 u_color;
uniform vec4 u_lightColor;
uniform float u_ambient;

in vec2 v_textureCoords;
in vec3 v_normals;

void main()
{
	out_color = u_color * u_lightColor * u_ambient;
	out_color.a = 1.0;
}