#type compute
#version 460

layout (local_size_x = 16, local_size_y = 16) in;

layout (binding = 0, rgba32f) uniform writeonly image2D outNormalMap;

uniform int		  uResolution;
uniform float	  uStrength;
uniform sampler2D uHeightMap;

void main(void)
{
	// z0 -- z1 -- z2
	// |	 |     |
	// z3 -- h  -- z4
	// |     |     |
	// z5 -- z6 -- z7
	
	ivec2 x		  = ivec2(gl_GlobalInvocationID.xy);
	vec2 texture_coords = gl_GlobalInvocationID.xy / float(uResolution);
	
	float texel_size = 1.0 / uResolution;
	
	float z0 = texture(uHeightMap, texture_coords + vec2(- texel_size, - texel_size)).r;
	float z1 = texture(uHeightMap, texture_coords + vec2(  0		 , - texel_size)).r;
	float z2 = texture(uHeightMap, texture_coords + vec2(  texel_size, - texel_size)).r;
	float z3 = texture(uHeightMap, texture_coords + vec2(- texel_size,   0		   )).r;
	float z4 = texture(uHeightMap, texture_coords + vec2(  texel_size,   0		   )).r;
	float z5 = texture(uHeightMap, texture_coords + vec2(- texel_size,   texel_size)).r;
	float z6 = texture(uHeightMap, texture_coords + vec2(  0		 ,   texel_size)).r;
	float z7 = texture(uHeightMap, texture_coords + vec2(  texel_size,   texel_size)).r;
	 
	vec3 normal;
	
	// Sobel Filter
	normal.z = 1.0 / uStrength;
	normal.x = z0 + 2 * z3 + z5 - z2 - 2 * z4 - z7;
	normal.y = z0 + 2 * z1 + z2 - z5 - 2 * z6 - z7;
	
	imageStore(outNormalMap, x, vec4(normalize(normal),1));
}