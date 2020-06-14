#type vertex
#version 450 core

layout(location = 0) in vec3 inPosition;

uniform mat4 uViewProjection;

void main()
{
	gl_ClipDistance[0] = 10000;
	gl_Position = (uViewProjection * vec4(inPosition, 0.0)).xyww;
}
#type fragment
#version 450 core

layout(location = 0) out vec4 outColor;

const vec3 cBaseColor = vec3(0.18, 0.27, 0.8);

void main()
{
	outColor.r = -0.00022 * (gl_FragCoord.y - 2800) + cBaseColor.r;
	outColor.g = -0.00025 * (gl_FragCoord.y - 2800) + cBaseColor.g;
	outColor.b = -0.00019 * (gl_FragCoord.y - 2800) + cBaseColor.b;
	outColor.a = 1.0;
}