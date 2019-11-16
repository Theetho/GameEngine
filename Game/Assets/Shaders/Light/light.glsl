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

layout(location = 0) out vec4 out_color;

#define MAX_NUMBER_OF_LIGHT 8

struct Light
{
	int id;

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

uniform vec4 u_color;
//uniform sampler2D u_texture;
uniform vec3 u_cameraPosition;
uniform Light u_lights[MAX_NUMBER_OF_LIGHT];

in vec2 v_textureCoords;
in vec3 v_normal;
in vec3 v_fragmentPosition;

// -----------------------------------------------------------------------------

vec4 CalculateDirectionalLight(Light light)
{	
	vec3 ambientColor = light.color * light.ambient;

	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(- light.direction);
	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseColor = light.color * diffuseFactor * light.diffuse;

	vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
	vec3 reflection = reflect(- lightDirection, normal);

	float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
	vec3 specularColor = light.color * specularFactor * light.specular;
	
	return vec4(specularColor + diffuseColor + ambientColor, 1.0);
}

// -----------------------------------------------------------------------------

vec4 CalculatePointLight(Light light)
{
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(light.position - v_fragmentPosition);
	
	float d = length(lightDirection);
	float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));

	vec3 ambientColor = light.color * light.ambient * attenuation;

	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseColor = light.color * diffuseFactor * light.diffuse * attenuation;

	vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
	vec3 reflection = reflect(-lightDirection, normal);

	float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 128);
	vec3 specularColor = light.color * specularFactor * light.specular * attenuation;

	return vec4(specularColor + diffuseColor + ambientColor, 1.0);
}

// -----------------------------------------------------------------------------

vec4 CalculateSpotLight(Light light)
{
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(light.position - v_fragmentPosition);
	
	float theta = dot(lightDirection, normalize(- light.direction));

	vec3 ambientColor = light.color * light.ambient;
	
	if (theta > light.cutOff)
	{
		float d = length(lightDirection);
		float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));		

		float diffuseFactor = max(dot(normal, lightDirection), 0.0);
		vec3 diffuseColor = light.color * diffuseFactor * light.diffuse * attenuation;
		
		vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
		vec3 reflection = reflect(- lightDirection, normal);
		
		float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
		vec3 specularColor = light.color * specularFactor * light.specular * attenuation;
	
		return vec4(specularColor + diffuseColor + ambientColor, 1.0);
	}
	else
	{
		return vec4(ambientColor, 1.0);
	}
}

// -----------------------------------------------------------------------------

void main()
{
	vec4 finalLightColor = vec4(0.0, 0.0, 0.0, 1.0);

	for (int i = 0; i < MAX_NUMBER_OF_LIGHT; ++i)
	{
		if (u_lights[i].id == 0)
		{
			finalLightColor += CalculateDirectionalLight(u_lights[i]);
		}
		else if (u_lights[i].id == 1)
		{
			finalLightColor += CalculatePointLight(u_lights[i]);
		}
		else if (u_lights[i].id == 2)
		{
			finalLightColor += CalculateSpotLight(u_lights[i]);
		}
	}

	out_color = u_color * finalLightColor;
	//out_color = texture(u_texture, v_textureCoords) * finalLightColor;
}