#version 460 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

out vec4 v_color;

uniform mat4 u_VP;

void main()
{
	gl_Position = u_VP * vec4(in_position, 1.0);
	v_color = in_color;
}