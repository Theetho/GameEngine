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
	v_normal = (u_model * vec4(in_normal, 0.0)).xyz;
	v_fragmentPosition = vec3(u_model * vec4(in_position, 1.0));
	gl_Position = u_MVP * vec4(in_position, 1.0);
}
#type fragment
#version 330 core

struct DirectionalLight
{
	vec3 color;
	vec3 direction;

	float ambient;
	float diffuse;
	float specular;
};

layout(location = 0) out vec4 out_color;

//uniform vec4 u_color;
uniform sampler2D u_texture;
uniform vec3 u_cameraPosition;
uniform DirectionalLight u_light;

in vec2 v_textureCoords;
in vec3 v_normal;
in vec3 v_fragmentPosition;

// -----------------------------------------------------------------------------

vec4 getFinalLightColor()
{	
	vec3 ambientColor = u_light.color * u_light.ambient;

	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(- u_light.direction);
	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseColor = u_light.color * diffuseFactor * u_light.diffuse;

	vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
	vec3 reflection = reflect(- lightDirection, normal);

	float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
	vec3 specularColor = u_light.color * specularFactor * u_light.specular;
	
	return vec4(specularColor + diffuseColor + ambientColor, 1.0);
}

// -----------------------------------------------------------------------------

void main()
{
	vec4 finalLightColor = getFinalLightColor();

	//out_color = u_color * finalLightColor;
	out_color = texture(u_texture, v_textureCoords) * finalLightColor;
}