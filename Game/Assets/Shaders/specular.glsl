#type vertex
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textureCoords;
layout(location = 2) in vec3 in_normal;

out vec2 v_textureCoords;
out vec3 v_normal;
out vec3 v_fragmentPosition;

uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
	v_textureCoords = in_textureCoords;
	v_normal = (inverse(transpose(u_model)) * vec4(in_normal, 0.0)).xyz;
//	v_normal = in_normal;
	v_fragmentPosition = vec3(u_model * vec4(in_position, 1.0));
	gl_Position = u_MVP * vec4(in_position, 1.0);
}
#type fragment
#version 330 core

struct Light
{
	vec3 color;
	vec3 direction;
};

layout(location = 0) out vec4 out_color;

uniform vec4 u_color;
uniform Light u_light;
uniform float u_ambient;
uniform float u_specular;
uniform vec3 u_cameraPosition;

in vec2 v_textureCoords;
in vec3 v_normal;
in vec3 v_fragmentPosition;

void main()
{
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(- u_light.direction);
	float diffuseFactor = max(dot(normal, lightDirection), u_ambient);
	vec3 diffuseColor = u_light.color * diffuseFactor;

	vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
	vec3 reflection = reflect(lightDirection, normal);

	float specularFactor = pow(dot(toCameraVector, reflection), u_specular);
	vec3 specularColor = u_light.color * specularFactor;

	out_color = u_color * vec4(specularColor + diffuseColor, 1.0);
}