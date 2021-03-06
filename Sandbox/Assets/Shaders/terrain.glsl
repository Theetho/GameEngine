#type vertex
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoords;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inColor;

out vec2 vTextureCoords;
out vec3 vNormal;
out vec3 vFragmentPosition;
out vec3 vColor;

uniform mat4 uViewProjection;
uniform mat4 uModel;
uniform vec4 uClipingPlane;

void main()
{
	vTextureCoords = inTextureCoords * 40.0f;
	vNormal = (uModel * vec4(inNormal, 0.0)).xyz;
	vFragmentPosition = vec3(uModel * vec4(inPosition, 1.0));
	vColor = inColor;
	vec4 world_position = uModel * vec4(inPosition, 1.0);

	gl_ClipDistance[0] = dot(world_position, uClipingPlane);
	gl_Position = uViewProjection * world_position;
}
#type fragment
#version 330 core

layout(location = 0) out vec4 outColor;

#define MAX_NUMBER_OF_LIGHT	8

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

uniform vec3 uCameraPosition;
uniform Light uLights[MAX_NUMBER_OF_LIGHT];

in vec2 vTextureCoords;
in vec3 vNormal;
in vec3 vFragmentPosition;
in vec3 vColor;

vec4 CalculateDirectionalLight(Light light)
{	
	vec3 normal = normalize(vNormal);
	vec3 lightDirection = normalize(- light.direction);
	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseColor = diffuseFactor * light.color * vColor;
	
	return vec4(diffuseColor, 0.0);
}

// -----------------------------------------------------------------------------

vec4 CalculatePointLight(Light light)
{
	vec3 normal = normalize(vNormal);
	vec3 lightDirection = normalize(light.position - vFragmentPosition);

	float d = length(lightDirection);
	float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));

	float diffuseFactor = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseColor = diffuseFactor * attenuation * light.color * vColor;

	return vec4(diffuseColor, 0.0);
}

// -----------------------------------------------------------------------------

vec4 CalculateSpotLight(Light light)
{
	vec3 normal = normalize(vNormal);
	vec3 lightDirection = normalize(light.position - vFragmentPosition);
	
	float theta = dot(lightDirection, normalize(- light.direction));

	vec3 ambientColor = light.color * 0.1 * vColor;
	
	if (theta > light.cutOff)
	{
		float d = length(lightDirection);
		float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));		

		float diffuseFactor = max(dot(normal, lightDirection), 0.0);
		vec3 diffuseColor = diffuseFactor * attenuation * light.color * vColor;
		
		return vec4(diffuseColor, 0.0);
	}
	else
	{
		return vec4(ambientColor, 0.0);
	}
}

// -----------------------------------------------------------------------------

void main()
{
	vec4 final_light_color = vec4(0.0, 0.0, 0.0, 1.0);

	for (int i = 0; i < MAX_NUMBER_OF_LIGHT; ++i)
	{
		if (uLights[i].id == 1)
		{
			final_light_color += CalculateDirectionalLight(uLights[i]);
		}
		else if (uLights[i].id == 2)
		{
			final_light_color += CalculatePointLight(uLights[i]);
		}
		else if (uLights[i].id == 3)
		{
			final_light_color += CalculateSpotLight(uLights[i]);
		}
	}

	outColor = final_light_color;
}