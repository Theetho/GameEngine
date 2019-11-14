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
//	v_normal = (transpose(inverse(u_model)) * vec4(in_normal, 0.0)).xyz;
	v_normal = (u_model * vec4(in_normal, 0.0)).xyz;
	v_fragmentPosition = vec3(u_model * vec4(in_position, 1.0));
	gl_Position = u_MVP * vec4(in_position, 1.0);
}
#type fragment
#version 330 core

//struct DirectionalLight
//{
//	vec3 color;
//	vec3 direction;
//
//	float ambient;
//	float diffuse;
//	float specular;
//};

//struct PointLight
//{
//	vec3 color;
//	vec3 position;
//
//	float ambient;
//	float diffuse;
//	float specular;
//
//	float constant;
//	float linear; 
//	float quadratic;
//};

struct SpotLight
{
	vec3 color;
	vec3 position;
	vec3 direction;

	float cutOff;

	float ambient;
	float diffuse;
	float specular;

	float constant;
	float linear; 
	float quadratic;
};

layout(location = 0) out vec4 out_color;

uniform vec4 u_color;
uniform SpotLight u_light;
uniform vec3 u_cameraPosition;

in vec2 v_textureCoords;
in vec3 v_normal;
in vec3 v_fragmentPosition;

//vec4 DirectionalLights(vec3 ambientColor, vec3 diffuseColor, vec3 specularColor)
//{	
//	ambientColor = u_light.color * u_light.ambient;
//
//	vec3 normal = normalize(v_normal);
//	vec3 lightDirection = normalize(- u_light.direction);
//	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
//	diffuseColor = u_light.color * diffuseFactor * u_light.diffuse;
//
//	vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
//	vec3 reflection = reflect(- lightDirection, normal);
//
//	float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
//	specularColor = u_light.color * specularFactor * u_light.specular;
//	
//	return vec4(specularColor + diffuseColor + ambientColor, 1.0);
//}

//vec4 PointLights(vec3 ambientColor, vec3 diffuseColor, vec3 specularColor)
//{
//	vec3 normal = normalize(v_normal);
//	vec3 lightDirection = normalize(u_light.position - v_fragmentPosition);
//	
//	float d = length(lightDirection);
//	float attenuation = 1.0 / (u_light.constant + u_light.linear * d + u_light.quadratic * pow(d, 2));
//
//	ambientColor = u_light.color * u_light.ambient * attenuation;
//
//	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
//	diffuseColor = u_light.color * diffuseFactor * u_light.diffuse * attenuation;
//
//	vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
//	vec3 reflection = reflect(-lightDirection, normal);
//
//	float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 128);
//	specularColor = u_light.color * specularFactor * u_light.specular * attenuation;
//
//	return vec4(specularColor + diffuseColor + ambientColor, 1.0);
//}

vec4 SpotLights(vec3 ambientColor, vec3 diffuseColor, vec3 specularColor)
{
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(u_light.position - v_fragmentPosition);
	
	float theta = dot(lightDirection, normalize(- u_light.direction));

	ambientColor = u_light.color * u_light.ambient;
	
	if (theta > u_light.cutOff)
	{
		float d = length(lightDirection);
		float attenuation = 1.0 / (u_light.constant + u_light.linear * d + u_light.quadratic * pow(d, 2));		

		float diffuseFactor = max(dot(normal, lightDirection), 0.0);
		diffuseColor = u_light.color * diffuseFactor * u_light.diffuse * attenuation;
		
		vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
		vec3 reflection = reflect(- lightDirection, normal);
		
		float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
		specularColor = u_light.color * specularFactor * u_light.specular * attenuation;
	
		return vec4(specularColor + diffuseColor + ambientColor, 1.0);
	}
	else
	{
		return vec4(ambientColor, 1.0);
	}
}

void main()
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	vec4 lightColor = SpotLights(ambientColor, diffuseColor, specularColor);

	out_color = u_color * lightColor;
}