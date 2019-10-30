#type vertex
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textureCoords;

out vec2 v_textureCoords;

uniform mat4 u_MVP;

void main()
{
	v_textureCoords = in_textureCoords;
	gl_Position = u_MVP * vec4(in_position, 1.0);
}
#type fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_textureCoords;

uniform sampler2D u_texture;

void main()
{
	out_color = texture(u_texture, v_textureCoords);
}