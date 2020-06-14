#type vertex
#version 330 core

layout(location = 0) in vec2 inPosition;

out vec4 vClipSpace;
out vec2 vTextureCoords;
out vec3 vFragmentPosition;

uniform mat4 uViewProjection;
uniform mat4 uModel;

const float cTiling = 3.0;

void main()
{
	vec4 world_position = uModel * vec4(inPosition.x, 0.0, inPosition.y, 1.0);
	vClipSpace = uViewProjection * world_position;

	gl_Position = vClipSpace;
	vTextureCoords  = (inPosition / 2.0 + 0.5) * cTiling;
	vFragmentPosition = world_position.xyz;
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

in vec4 vClipSpace;
in vec2 vTextureCoords;
in vec3 vFragmentPosition;

uniform Light     uLights[MAX_NUMBER_OF_LIGHT];
uniform vec3      uCameraPosition;
uniform sampler2D uRefraction;
uniform sampler2D uReflection;
uniform sampler2D uDUDVMap;
uniform sampler2D uNormalMap;
uniform sampler2D uDepthMap;
uniform float	  uWaveMovement;
uniform float	  uNear;
uniform float	  uFar;

const float cWaveStrength = 0.02;
const float cShininess	  = 64.0;
const float cReflectivity = 0.5;

// -----------------------------------------------------------------------------

vec4 CalculateDirectionalLight(Light light, vec3 normal, vec3 to_camera_vector)
{	
	vec3 reflection = reflect(normalize(light.direction), normal);
	float specularFactor = pow(max(dot(to_camera_vector, reflection), 0.0), cShininess);
	return vec4(specularFactor * light.color * cReflectivity, 0.0);
}

// -----------------------------------------------------------------------------

vec4 CalculatePointLight(Light light, vec3 normal, vec3 to_camera_vector)
{
	vec3 reflection = reflect(normalize(light.direction), normal);
	float specularFactor = pow(max(dot(to_camera_vector, reflection), 0.0), cShininess);
	return vec4(specularFactor * light.color * cReflectivity, 0.0);
}

// -----------------------------------------------------------------------------

vec4 CalculateSpotLight(Light light, vec3 normal, vec3 to_camera_vector)
{
	vec3 light_direction = normalize(light.position - vFragmentPosition);
	
	float theta = dot(light_direction, normalize(- light.direction));

	if (theta > light.cutOff)
	{
		vec3 reflection = reflect(normalize(light.direction), normal);
		float specularFactor = pow(max(dot(to_camera_vector, reflection), 0.0), cShininess);
		
		return vec4(specularFactor * light.color * cReflectivity, 0.0);
	}
	else
	{
		return vec4(0.1, 0.1, 0.1, 1.0);
	}
}

// -----------------------------------------------------------------------------

void main()
{
	vec2 normalized_device_space = (vClipSpace.xy / vClipSpace.w) / 2.0 + 0.5;
	vec2 refract_texture_coords = normalized_device_space;
	vec2 reflect_texture_coords = vec2(normalized_device_space.x, - normalized_device_space.y);

	float depth = texture(uDepthMap, refract_texture_coords).r;
	float floor_distance = 2.0 * uNear * uFar / (uFar + uNear - (2.0 * depth - 1.0) * (uFar - uNear));

	depth = gl_FragCoord.z;
	float water_distance = 2.0 * uNear * uFar / (uFar + uNear - (2.0 * depth - 1.0) * (uFar - uNear));
	float water_depth = floor_distance - water_distance;

	vec2 distorted_texture_coords = texture(uDUDVMap, vec2(vTextureCoords.x + uWaveMovement, vTextureCoords.y)).rg * cWaveStrength;
	distorted_texture_coords      = vTextureCoords + vec2(distorted_texture_coords.x, distorted_texture_coords.y + uWaveMovement);
	vec2 distorsion				  = (texture(uDUDVMap, distorted_texture_coords).rg * 2.0 - 1.0) * cWaveStrength;

	refract_texture_coords += distorsion;
	refract_texture_coords = clamp(refract_texture_coords, 0.001, 0.999);

	reflect_texture_coords += distorsion;
	reflect_texture_coords.x = clamp(reflect_texture_coords.x,  0.001,  0.999);
	reflect_texture_coords.y = clamp(reflect_texture_coords.y, -0.999, -0.001);

	vec4 reflection = texture(uReflection, reflect_texture_coords);
	vec4 refraction = texture(uRefraction, refract_texture_coords);

	vec4 normal_map_color = texture(uNormalMap, distorted_texture_coords);
	vec3 normal = normalize(vec3(normal_map_color.r * 2.0 - 1.0, normal_map_color.b, normal_map_color.g * 2.0 - 1.0));
	

	vec3 to_camera_vector = normalize(uCameraPosition - vFragmentPosition);
	float fresnel = dot(normal, normalize(to_camera_vector));

	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
	for (int i = 0; i < MAX_NUMBER_OF_LIGHT; ++i)
	{
		if (uLights[i].id == 1)
		{
			specular += CalculateDirectionalLight(uLights[i], normal, to_camera_vector);
		}
		else if (uLights[i].id == 2)
		{
			specular += CalculatePointLight(uLights[i], normal, to_camera_vector);
		}
		else if (uLights[i].id == 3)
		{
			specular += CalculateSpotLight(uLights[i], normal, to_camera_vector);
		}
	}

	outColor = mix(reflection, refraction, fresnel);
	outColor += specular * clamp(water_depth / 5.0f, 0.0, 1.0);
	outColor.a = clamp(water_depth / 2.0, 0.0, 1.0);
}