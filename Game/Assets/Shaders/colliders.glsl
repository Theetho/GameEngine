#type vertex
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textureCoords;
layout(location = 2) in vec3 in_normal;

uniform mat4 u_ModelViewProjection;

void main()
{
	gl_Position = u_ModelViewProjection * vec4(in_position, 1.0);
}
#type fragment
#version 330 core

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(0.0, 1.0, 0.0, 1.0);
}