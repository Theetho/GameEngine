#type vertex
#version 330 core
layout (location = 0) in vec4 inVertex; // <vec2 pos, vec2 tex>

out vec2 vTextureCoords;

uniform mat4 uProjection;

void main()
{
    gl_Position = uProjection * vec4(inVertex.xy, 0.0, 1.0);
    vTextureCoords = inVertex.zw;
}
#type fragment
#version 330 core

in vec2 vTextureCoords;
out vec4 outColor;

uniform sampler2D uText;
uniform vec3 uFontColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uText, vTextureCoords).r);
    outColor = vec4(uFontColor, 1.0) * sampled;
}  