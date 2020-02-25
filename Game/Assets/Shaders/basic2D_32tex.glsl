#type vertex
#version 330 core

layout(location = 0) in vec2  inPosition;
layout(location = 1) in vec2  inTextureCoords;
layout(location = 2) in vec4  inColor;
layout(location = 3) in float inTextureID;

out vec2	 vTextureCoords;
out vec4	 vColor;
flat out int vTextureID;

void main()
{
	gl_Position    = vec4(inPosition, 0.0, 1.0);
	vTextureCoords = inTextureCoords;
	vColor		   = inColor;
	vTextureID	   = int(inTextureID);
}
#type fragment
#version 330 core

layout(location = 0) out vec4 outColor;

in vec2		vTextureCoords;
in vec4		vColor;
flat in int vTextureID;

uniform sampler2D uTextures[32];

void main()
{
	vec4 texture_color = texture(uTextures[vTextureID], vTextureCoords);
	outColor = texture_color * vColor;
}