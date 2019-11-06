#type vertex
#version 330 core

layout (location = 0) in vec3 in_position;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(in_position, 1.0);
}
#type fragment
#version 330 core

layout (location = 0) out vec4 out_color;

uniform vec4 u_color;

void main()
{
	out_color = u_color;
}