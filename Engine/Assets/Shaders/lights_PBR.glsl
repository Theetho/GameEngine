#type vertex
#version 450 core

layout(location = 0) in vec3  inPosition;
layout(location = 1) in vec2  inTextureCoords;
layout(location = 2) in vec3  inNormal;
layout(location = 3) in vec4  inBonesID;
layout(location = 4) in vec4  inWeights;

out vec2 vTextureCoords;
out vec3 vNormal;
out vec3 vFragmentPosition;

const int MAX_BONES = 100;

uniform mat4 uViewProjection;
uniform mat4 uModel;
uniform vec4 uClipingPlane;
uniform mat4 uBones[MAX_BONES];

void main()
{
	mat4 BoneTransform = mat4(0.0f);

	BoneTransform = uBones[int(inBonesID[0])] * inWeights[0];
	BoneTransform	  += uBones[int(inBonesID[1])] * inWeights[1];
	BoneTransform	  += uBones[int(inBonesID[2])] * inWeights[2];
	BoneTransform	  += uBones[int(inBonesID[3])] * inWeights[3];
	
	// No bones or no animation linked
	if (BoneTransform == mat4(0.0f))
		BoneTransform = mat4(1.0f);

	vec4 actualPosition = BoneTransform * vec4(inPosition, 1.0);
	vec3 actualNormal   = (BoneTransform * vec4(inNormal, 1.0)).xyz;

	vTextureCoords = inTextureCoords;
	vNormal = (uModel * vec4(actualNormal, 0.0)).xyz;
	vFragmentPosition = vec3(uModel * actualPosition);

	vec4 world_position = uModel * actualPosition;

	gl_ClipDistance[0] = dot(world_position, uClipingPlane);
	gl_Position = uViewProjection * world_position;
}
#type fragment
#version 450 core

layout(location = 0) out vec4 outColor;

#define MAX_NUMBER_OF_LIGHT	8
#define AMBIENT_OCCLUSION 0.2

struct Light
{
	int id;
	float minDiffuseFactor;

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

uniform vec3 uCameraPosition;
uniform Light uLights[MAX_NUMBER_OF_LIGHT];
uniform Material uMaterial;

in vec2 vTextureCoords;
in vec3 vNormal;
in vec3 vFragmentPosition;

vec4 CalculateDirectionalLight(Light light)
{	
	
	vec3 ambientColor = AMBIENT_OCCLUSION * light.color * texture(uMaterial.texture_am, vTextureCoords).rgb;

	vec3 normal = normalize(vNormal);
	vec3 lightDirection = normalize(- light.direction);
	float diffuseFactor = max(dot(normal, lightDirection), light.minDiffuseFactor);
	vec3 diffuseColor = light.color * diffuseFactor * texture(uMaterial.texture_df, vTextureCoords).rgb;

	vec3 toCameraVector = normalize(uCameraPosition - vFragmentPosition);
	vec3 reflection = reflect(- lightDirection, normal);

	// float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 1);
	// vec3 specularColor = light.color * specularFactor * texture(uMaterial.texture_sp, vTextureCoords).rgb;
	vec3 specularColor = vec3(0.0f);

	return vec4(specularColor + diffuseColor + ambientColor, 0.0);
}

// -----------------------------------------------------------------------------

vec4 CalculatePointLight(Light light)
{
	vec3 normal = normalize(vNormal);
	vec3 lightDirection = normalize(light.position - vFragmentPosition);
	
	vec3 ambientColor = AMBIENT_OCCLUSION * light.color * texture(uMaterial.texture_am, vTextureCoords).rgb;

	float d = length(lightDirection);
	float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));

	float diffuseFactor = max(dot(normal, lightDirection), light.minDiffuseFactor);
	vec3 diffuseColor = light.color * diffuseFactor * attenuation * texture(uMaterial.texture_df, vTextureCoords).rgb;

	vec3 toCameraVector = normalize(uCameraPosition - vFragmentPosition);
	vec3 reflection = reflect(-lightDirection, normal);

	//float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
	//vec3 specularColor = light.color * specularFactor * attenuation * texture(uMaterial.texture_sp, vTextureCoords).rgb;
	vec3 specularColor = vec3(0.0f);

	return vec4(specularColor + diffuseColor + ambientColor, 0.0);
}

// -----------------------------------------------------------------------------

vec4 CalculateSpotLight(Light light)
{
	vec3 normal = normalize(vNormal);
	vec3 lightDirection = normalize(light.position - vFragmentPosition);
	
	float theta = dot(lightDirection, normalize(- light.direction));

	vec3 ambientColor = AMBIENT_OCCLUSION * light.color * texture(uMaterial.texture_am, vTextureCoords).rgb;
	
	if (theta > light.cutOff)
	{
		float d = length(lightDirection);
		float attenuation = 1.0 / (light.constant + light.linear * d + light.quadratic * pow(d, 2));		

		float diffuseFactor = max(dot(normal, lightDirection), light.minDiffuseFactor);
		vec3 diffuseColor = light.color * diffuseFactor * attenuation * texture(uMaterial.texture_df, vTextureCoords).rgb;
		
		vec3 toCameraVector = normalize(uCameraPosition - vFragmentPosition);
		vec3 reflection = reflect(- lightDirection, normal);
		
		// float specularFactor = pow(max(dot(toCameraVector, reflection), 0.0), 64);
		// vec3 specularColor = light.color * specularFactor * attenuation * texture(uMaterial.texture_sp, vTextureCoords).rgb;
		vec3 specularColor = vec3(0.0f);
	
		return vec4(specularColor + diffuseColor + ambientColor, 0.0);
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