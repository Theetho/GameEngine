#type vertex
#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textureCoords;
layout(location = 2) in vec3 in_normal;

out vec3 v_textureCoords;

uniform mat4 u_view_projection;

void main()
{
	v_textureCoords = in_position;
	gl_Position = (u_view_projection * vec4(in_position, 0.0)).xyww;
}
#type fragment
#version 450 core

layout(location = 0) out vec4 out_color;

uniform samplerCube u_skybox;

in vec3 v_textureCoords;

void main()
{
	out_color = texture(u_skybox, v_textureCoords);
}