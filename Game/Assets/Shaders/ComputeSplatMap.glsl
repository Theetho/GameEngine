#type compute
#version 460

layout (local_size_x = 16, local_size_y = 16) in;

layout (binding = 0, rgba16f) uniform writeonly image2D outSplatMap;

uniform sampler2D uNormalMap;
uniform int uResolution;

void main(void)
{
	ivec2 x = ivec2(gl_GlobalInvocationID.xy);
	vec2 texture_coords = gl_GlobalInvocationID.xy/ float(uResolution);
	
	vec3 normal = normalize(texture(uNormalMap, texture_coords).rgb);
	
	float slope_factor = normal.z;
	
	vec4 blend_values = vec4(0,0,0,0);
	
	if (slope_factor > 0.5){
		blend_values.x = 1.0;
	}
	else if (slope_factor > 0.35){
		blend_values.y = 1.0;
	}
	else {
		blend_values.z = 1.0;
	}
	
	imageStore(outSplatMap, x, blend_values);
}