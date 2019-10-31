#type vertex
#version 460 core

layout(location = 0) in vec3 in_position;

void main()
{
	gl_Position = vec4(in_position, 1.0);
}
#type fragment
#version 460 core

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = vec4(1.0, 0.0, 1.0, 1.0);
}