#type vertex
#version 330 core

layout(location = 0) in vec2 inPosition;

uniform mat4 uModel;

out vec2 vTextureCoords;

void main()
{
	gl_Position = uModel * vec4(inPosition, 0.0, 1.0);
	vTextureCoords = vec2((inPosition.x + 1.0) / 2.0, 1 - (inPosition.y + 1.0) / 2.0);
}
#type fragment
#version 330 core

layout(location = 0) out vec4 outColor;

in vec2 vTextureCoords;

uniform sampler2D uTexture;

void main()
{
	outColor = texture(uTexture, vTextureCoords);
}