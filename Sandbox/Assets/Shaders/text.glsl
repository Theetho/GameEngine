#type vertex
#version 330 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTextureCoords;
layout(location = 2) in vec3 inColor;

out vec2 vTextureCoords;
out vec3 vColor;

void main()
{
	gl_Position = vec4(inPosition, 0.0, 1.0);
	vTextureCoords = inTextureCoords;
	vColor = inColor;
}
#type fragment
#version 330 core

layout(location = 0) out vec4 outColor;

in vec2 vTextureCoords;
in vec3 vColor;

uniform sampler2D uFontAtlas;

void main()
{
	vec4 character = texture(uFontAtlas, vTextureCoords);

	// Discard background
	if (character.a < 0.3)
		discard;

	outColor = vec4(vColor * character.aaa, character.a);
}