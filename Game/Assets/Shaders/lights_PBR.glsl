#type vertex
#version 450 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textureCoords;
layout(location = 2) in vec3 in_normal;

out vec2 v_textureCoords;
out vec3 v_normal;
out vec3 v_fragmentPosition;

uniform mat4 u_ModelViewProjection;
uniform mat4 u_model;

void main()
{
	v_textureCoords = in_textureCoords;
	v_normal = (u_model * vec4(in_normal, 0.0)).xyz;
	v_fragmentPosition = vec3(u_model * vec4(in_position, 1.0));
	gl_Position = u_ModelViewProjection * vec4(in_position, 1.0);
}
#type fragment
#version 450 core

layout(location = 0) out vec4 out_color;

#define MAX_NUMBER_OF_LIGHT	8
#define AMBIENT_OCCLUSION 0.2

struct Light
{
	int id;

	vec3 color;
	vec3 position;
	vec3 direction;

	float cutOff;

	float constant;
	float linear; 
	float quadratic;
};

struct Material
{
	sampler2D texture_am;
	sampler2D texture_df;
	sampler2D texture_sp;
	sampler2D texture_nl;
};

uniform vec3 u_cameraPosition;
uniform Light u_lights[MAX_NUMBER_OF_LIGHT];
uniform Material u_material;

in vec2 v_textureCoords;
in vec3 v_normal;
in vec3 v_fragmentPosition;

vec4 CalculateDirectionalLight(Light light)
{	
	
	vec3 ambientColor = AMBIENT_OCCLUSION * light.color * texture(u_material.texture_am, v_textureCoords).rgb;

	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(- light.direction);
	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseColor = light.color * diffuseFactor * texture(u_material.texture_df, v_textureCoords).rgb;

	vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
	vec3 reflection = reflect(- lightDirection, normal);

	float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
	vec3 specularColor = light.color * specularFactor * texture(u_material.texture_sp, v_textureCoords).rgb;
	
	return vec4(specularColor + diffuseColor + ambientColor, 1.0);
}

// -----------------------------------------------------------------------------

vec4 CalculatePointLight(Light light)
{
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(light.position - v_fragmentPosition);
	
	vec3 ambientColor = AMBIENT_OCCLUSION * light.color * texture(u_material.texture_am, v_textureCoords).rgb;

	float d = length(lightDirection);
	float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));

	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseColor = light.color * diffuseFactor * attenuation * texture(u_material.texture_df, v_textureCoords).rgb;

	vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
	vec3 reflection = reflect(-lightDirection, normal);

	float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
	vec3 specularColor = light.color * specularFactor * attenuation * texture(u_material.texture_sp, v_textureCoords).rgb;

	return vec4(specularColor + diffuseColor + ambientColor, 1.0);
}

// -----------------------------------------------------------------------------

vec4 CalculateSpotLight(Light light)
{
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(light.position - v_fragmentPosition);
	
	float theta = dot(lightDirection, normalize(- light.direction));

	vec3 ambientColor = AMBIENT_OCCLUSION * light.color * texture(u_material.texture_am, v_textureCoords).rgb;
	
	if (theta > light.cutOff)
	{
		float d = length(lightDirection);
		float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));		

		float diffuseFactor = max(dot(normal, lightDirection), 0.0);
		vec3 diffuseColor = light.color * diffuseFactor * attenuation * texture(u_material.texture_df, v_textureCoords).rgb;
		
		vec3 toCameraVector = normalize(u_cameraPosition - v_fragmentPosition);
		vec3 reflection = reflect(- lightDirection, normal);
		
		float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
		vec3 specularColor = light.color * specularFactor * attenuation * texture(u_material.texture_sp, v_textureCoords).rgb;
	
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
		if (u_lights[i].id == 1)
		{
			finalLightColor += CalculateDirectionalLight(u_lights[i]);
		}
		else if (u_lights[i].id == 2)
		{
			finalLightColor += CalculatePointLight(u_lights[i]);
		}
		else if (u_lights[i].id == 3)
		{
			finalLightColor += CalculateSpotLight(u_lights[i]);
		}
	}

	out_color = finalLightColor;
}