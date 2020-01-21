#type vertex
#version 450 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoords;
layout(location = 2) in vec3 inNormal;

out vec3 vTextureCoords;

uniform mat4 uViewProjection;

void main()
{
	vTextureCoords = inPosition;
	gl_ClipDistance[0] = 10000;
	gl_Position = (uViewProjection * vec4(inPosition, 0.0)).xyww;
}
#type fragment
#version 450 core

layout(location = 0) out vec4 outColor;

uniform samplerCube uSkybox;

in vec3 vTextureCoords;

void main()
{
	outColor = texture(uSkybox, vTextureCoords);
}