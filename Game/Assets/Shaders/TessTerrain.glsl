#type vertex
#version 430

layout (location = 0) in vec2 inPosition;

out vec2 vMapCoord;

uniform mat4      uGlobal;
uniform mat4      uLocal;
uniform vec3      uCameraPosition;
uniform vec2      uIndex;
uniform vec2      uLocation;
uniform float     uGap;
uniform float     uScaleY;
uniform int       uLod;
uniform int       uLodMorphingArea[8];
uniform sampler2D uHeightMap;

//float MorphLatitude(vec2 position)
//{
//	vec2 frac = position - uLocation;
//	
//	float morph = (uIndex.x == 0 ? frac.x : - frac.x) + (uIndex.y == 0 ? - frac.y : frac.y);
//	if (uIndex.x == 0)
//		morph -= uGap;
//	if (uIndex.y == 0)
//		morph += uGap;
//	if (morph > 0)
//	{
//		if (uIndex.y == 0)
//		{
//			return morph;
//		}
//		else
//		{
//			return -morph;
//		}
//	}	
//	return 0;
//}
//
//float MorphLongitude(vec2 position)
//{
//	vec2 frac = position - uLocation;
//	
//	float morph = (uIndex.x == 0 ? - frac.x : frac.x) + (uIndex.y == 0 ? frac.y : - frac.y);
//	if (uIndex.x == 0)
//		morph += uGap;
//	if (uIndex.y == 0)
//		morph -= uGap;
//	if (morph > 0)
//	{
//		if (uIndex.x == 0)
//		{
//			return -morph;
//		}
//		else
//		{
//			return morph;
//		}
//	}	
//	return 0;
//}
//
//vec2 Morph(vec2 local_position, int morphing_area)
//{
//	vec2 morph = vec2(0);
//	
//	vec2 fix_point_latitude = vec2(
//		(uIndex.x == 0 ? uGap : 0)
//	  , (uIndex.y == 0 ? 0    : uGap)
//	);
//	vec2 fix_point_longitude = vec2(
//		(uIndex.x == 0 ? 0    : uGap)
//	  , (uIndex.y == 0 ? uGap : 0)
//	);
//	
//	float planar_factor = 0;
//	planar_factor = (uCameraPosition.y > abs(uScaleY) ?  1 : uCameraPosition.y / abs(uScaleY));
//	
//	float distance_latitude  = length(uCameraPosition - (uGlobal * vec4(fix_point_latitude.x , planar_factor, fix_point_latitude.y , 1)).xyz);
//	float distance_longitude = length(uCameraPosition - (uGlobal * vec4(fix_point_longitude.x, planar_factor, fix_point_longitude.y, 1)).xyz);
//	
//	if (distance_latitude < morphing_area)
//		morph.x = MorphLatitude(local_position);
//	if (distance_longitude < morphing_area)
//		morph.y = MorphLongitude(local_position);
//
//	return morph;
//}

float MorphLatitude(vec2 position) {
	
	vec2 frac = position - uLocation;
	
	if (uIndex == vec2(0,0)){
		float morph = frac.x - frac.y;
		if (morph > 0)
			return morph;
	}
	if (uIndex == vec2(1,0)){
		float morph = uGap - frac.x - frac.y;
		if (morph > 0)
			return morph;
	}
	if (uIndex == vec2(0,1)){
		float morph = frac.x + frac.y - uGap;
		if (morph > 0)
			return -morph;
	}
	if (uIndex == vec2(1,1)){
		float morph = frac.y - frac.x;
		if (morph > 0)
			return -morph;
	}
	return 0;
}

float MorphLongitude(vec2 position) {
	
	vec2 frac = position - uLocation;
	
	if (uIndex == vec2(0,0)){
		float morph = frac.y - frac.x;
		if (morph > 0)
			return -morph;
	}
	if (uIndex == vec2(1,0)){
		float morph = frac.y - (uGap - frac.x);
		if (morph > 0)
			return morph;
	}
	if (uIndex == vec2(0,1)){
		float morph = uGap - frac.y - frac.x;
		if (morph > 0)
			return -morph;
	}
	if (uIndex == vec2(1,1)){
		float morph = frac.x - frac.y;
		if (morph > 0)
			return morph;
	}
	return 0;
}

vec2 Morph(vec2 local_position, int morph_area){
	
	vec2 morphing = vec2(0,0);
	
	vec2 fixPointLatitude = vec2(0,0);
	vec2 fixPointLongitude = vec2(0,0);
	float distLatitude;
	float distLongitude;
	
	if (uIndex == vec2(0,0)) {
		fixPointLatitude = uLocation + vec2(uGap,0);
		fixPointLongitude = uLocation + vec2(0,uGap);
	}
	else if (uIndex == vec2(1,0)) {
		fixPointLatitude = uLocation;
		fixPointLongitude = uLocation + vec2(uGap,uGap);
	}
	else if (uIndex == vec2(0,1)) {
		fixPointLatitude = uLocation + vec2(uGap,uGap);
		fixPointLongitude = uLocation;
	}
	else if (uIndex == vec2(1,1)) {
		fixPointLatitude = uLocation + vec2(0,uGap);
		fixPointLongitude = uLocation + vec2(uGap,0);
	}
	
	float planarFactor = 0;
	if (uCameraPosition.y > abs(uScaleY))
		planarFactor = 1;
	else
		planarFactor = uCameraPosition.y/ abs(uScaleY);
		
	distLatitude = length(uCameraPosition - (uGlobal * 
					vec4(fixPointLatitude.x,planarFactor,fixPointLatitude.y,1)).xyz);
	distLongitude = length(uCameraPosition - (uGlobal * 
					vec4(fixPointLongitude.x,planarFactor,fixPointLongitude.y,1)).xyz);
					
	if (distLatitude > morph_area)
		morphing.x = MorphLatitude(local_position.xy);
	if (distLongitude > morph_area)
		morphing.y = MorphLongitude(local_position.xy);
		
	return morphing;
}

void main()
{				
	vec2 local_position = (uLocal * vec4(inPosition.x, 0, inPosition.y, 1)).xz;
	
	if (uLod > 0)
		local_position += Morph(local_position, uLodMorphingArea[uLod - 1]); 
					
	float height = texture(uHeightMap, local_position).r;

	vMapCoord	= local_position;
	gl_Position = uGlobal * vec4(local_position.x, height, local_position.y, 1);
}
#type tesselation control
#version 430

layout(vertices = 16) out;

in vec2 vMapCoord[];

out vec2 tcMapCoord[];

const int AB = 2;
const int BC = 3;
const int CD = 0;
const int DA = 1;

uniform int   uTesselationFactor;
uniform float uTesselationSlope;
uniform float uTesselationShift;
uniform vec3  uCameraPosition;
	
float LodFactor(float dist)
{
	return max(0.0, uTesselationFactor / pow(dist, uTesselationSlope) + uTesselationShift);
}

void main()
{
	if(gl_InvocationID == 0)
	{
			vec3 abMid = vec3(gl_in[0].gl_Position  + gl_in[3].gl_Position ) / 2.0;		
			vec3 bcMid = vec3(gl_in[3].gl_Position  + gl_in[15].gl_Position) / 2.0;		
			vec3 cdMid = vec3(gl_in[15].gl_Position + gl_in[12].gl_Position) / 2.0;		
			vec3 daMid = vec3(gl_in[12].gl_Position + gl_in[0].gl_Position ) / 2.0;		

			float distanceAB = distance(abMid, uCameraPosition);
			float distanceBC = distance(bcMid, uCameraPosition);
			float distanceCD = distance(cdMid, uCameraPosition);
			float distanceDA = distance(daMid, uCameraPosition);

			gl_TessLevelOuter[AB] = mix(1, gl_MaxTessGenLevel, LodFactor(distanceAB));
			gl_TessLevelOuter[BC] = mix(1, gl_MaxTessGenLevel, LodFactor(distanceBC));
			gl_TessLevelOuter[CD] = mix(1, gl_MaxTessGenLevel, LodFactor(distanceCD));
			gl_TessLevelOuter[DA] = mix(1, gl_MaxTessGenLevel, LodFactor(distanceDA));
	
			gl_TessLevelInner[0] = (gl_TessLevelOuter[BC] + gl_TessLevelOuter[DA]) / 4;
			gl_TessLevelInner[1] = (gl_TessLevelOuter[AB] + gl_TessLevelOuter[CD]) / 4;
	}
	
	tcMapCoord[gl_InvocationID] = vMapCoord[gl_InvocationID];

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
#type tesselation evaluation
#version 430

layout(quads, fractional_odd_spacing, cw) in;

in vec2 tcMapCoord[];

out vec2 teMapCoord;

uniform sampler2D uHeightMap;
uniform float     uScaleY;

void main(){

    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
	
	// world position
	vec4 position =
	((1 - u) * (1 - v) * gl_in[12].gl_Position +
	u * (1 - v) * gl_in[0].gl_Position +
	u * v * gl_in[3].gl_Position +
	(1 - u) * v * gl_in[15].gl_Position);
	
	teMapCoord = 	
	((1 - u) * (1 - v) * tcMapCoord[12] +
	u * (1 - v)		   * tcMapCoord[0]  +
	u * v			   * tcMapCoord[3]  +
	(1 - u) * v		   * tcMapCoord[15]);

	position.y = texture(uHeightMap, teMapCoord).r * uScaleY;

	gl_Position = position;
}
#type geometry
#version 430

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

struct Material
{
	sampler2D diffuse;
	sampler2D normal;
	sampler2D displacement;
	vec2 scale;
};

in vec2 teMapCoord[];

out vec2 gMapCoord;
out vec3 gPosition;
out vec3 gTangent;

uniform mat4 uViewProjection;
uniform sampler2D uNormalMap;
uniform sampler2D uSplatMap;
uniform vec3 uCameraPosition;
uniform Material uMaterials[3];
uniform int uTBNRange;

vec3 tangent;
vec3 displacement[3];

void CalculateTangent()
{
	vec3 v0 = gl_in[0].gl_Position.xyz; 
	vec3 v1 = gl_in[1].gl_Position.xyz; 
	vec3 v2 = gl_in[2].gl_Position.xyz; 

	vec3 e1 = v1 - v0;
	vec3 e2 = v2 - v0;

	vec2 uv0 = teMapCoord[0];
	vec2 uv1 = teMapCoord[1];
	vec2 uv2 = teMapCoord[2];

	vec2 deltaUV1 = uv1 - uv0;
	vec2 deltaUV2 = uv2 - uv0;

	float r = 1.0 / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

	tangent = normalize((e1 * deltaUV2.y - e2 * deltaUV1.y) * r);
}


void main()
{
	for (int i = 0; i < 3; ++i)
	{
		displacement[i] = vec3(0);
	}

	float dist = (distance(gl_in[0].gl_Position.xyz, uCameraPosition)
				+ distance(gl_in[1].gl_Position.xyz, uCameraPosition)
				+ distance(gl_in[2].gl_Position.xyz, uCameraPosition)) / 3;
	if (dist < uTBNRange)
	{
		CalculateTangent();

		for (int i = 0; i < gl_in.length(); ++i)
		{
			displacement[i].y = 1;

			float height = gl_in[i].gl_Position.y;
			vec3 normal  = normalize(texture(uNormalMap, teMapCoord[i]).rbg);
			
			vec4 blend_value = texture(uSplatMap, teMapCoord[i]);

			float[4] material_alpha = float[](blend_value.r, blend_value.g, blend_value.b, blend_value.a);

			float scale = 0;
			for (int j = 0; j < 3; ++j)
			{
				scale += texture(uMaterials[j].displacement, teMapCoord[i] * uMaterials[j].scale.x).r
						 * uMaterials[j].scale.y
						 * material_alpha[j];
			}

			float attenuation = clamp(- distance(gl_in[i].gl_Position.xyz, uCameraPosition) / (uTBNRange - 50) + 1, 0.0, 1.0);
			scale *= attenuation;

			displacement[i] *= scale;
		}
	}

	for (int i = 0; i < gl_in.length(); ++i)
	{
		vec4 world_position = gl_in[i].gl_Position + vec4(displacement[i], 0.0);
		gl_Position = uViewProjection * world_position;
		gMapCoord = teMapCoord[i];
		gPosition = world_position.xyz;
		gTangent  = tangent;
		EmitVertex();
	}
	
	EndPrimitive();

}
#type fragment
#version 430

layout(location = 0) out vec4 outColor;

struct Material
{
	sampler2D diffuse;
	sampler2D normal;
	sampler2D displacement;
	vec2 scale;
};

in vec2 gMapCoord;
in vec3 gPosition;
in vec3 gTangent;

uniform sampler2D uNormalMap;
uniform sampler2D uSplatMap;
uniform Material uMaterials[3];
uniform int uTBNRange;
uniform vec3 uCameraPosition;

// TEMPORARY
const vec3  cLightDirection = vec3(0.1, -1.0, 0.1);
const float cIntensity = 1.2;

float diffuse(vec3 direction, vec3 normal, float intensity)
{
	return max(0.04, dot(normal, -direction) * intensity);
}

void main()
{
	float dist   = distance(uCameraPosition, gPosition);
	float height = gPosition.y;

	vec3 normal = normalize(texture(uNormalMap, gMapCoord).rbg);

	vec4 blend_value = texture(uSplatMap, gMapCoord);

	float[4] material_alpha = float[](blend_value.r, blend_value.g, blend_value.b, blend_value.a);

	if (dist < uTBNRange - 50)
	{
		float attenuation = clamp(- dist / (uTBNRange - 50) + 1.0, 0.0, 1.0);
	
		vec3 bitangent = normalize(cross(gTangent, normal));
		mat3 TBN = mat3(gTangent, normal, bitangent);

		vec3 bump_normal = vec3(0);
		for (int i = 0; i < 3; ++i)
		{
			bump_normal += (2 * (texture(uMaterials[i].normal, gMapCoord * uMaterials[i].scale.x).rbg) - 1) * material_alpha[i];
		}

		bump_normal = normalize(bump_normal);

		bump_normal.xz *= attenuation;

		normal = normalize(TBN * bump_normal);
	}

	vec3 fragment_color = vec3(0);

	for (int i = 0; i < 3; ++i)
	{
		fragment_color += texture(uMaterials[i].diffuse, gMapCoord * uMaterials[i].scale.x).rgb * material_alpha[i];
	}

	float diffuse = diffuse(cLightDirection, normal, cIntensity);

	fragment_color *= diffuse;

	outColor = vec4(fragment_color, 1.0);
}