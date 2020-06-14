#type vertex
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoords;
layout(location = 2) in vec3 inNormal;

uniform mat4 uViewProjection;
uniform mat4 uModel;

void main()
{
	gl_Position = uViewProjection * uModel * vec4(inPosition, 1.0);
}
#type fragment
#version 330 core

layout(location = 0) out vec4 outColor;

void main()
{
	outColor = vec4(0.0, 1.0, 0.0, 1.0);
}