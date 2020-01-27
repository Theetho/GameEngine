#type vertex
#version 430

layout (location = 0) in vec2 inPosition;

uniform mat4 uGlobal;
uniform mat4 uLocal;

void main()
{				
	vec2 local_position = (uLocal * vec4(inPosition.x, 0, inPosition.y, 1)).xz;
					
	gl_Position = uGlobal * vec4(local_position.x, 0, local_position.y, 1);
}
#type tesselation control
#version 430

layout(vertices = 16) out;

const int AB = 2;
const int BC = 3;
const int CD = 0;
const int DA = 1;
	
void main()
{
	if(gl_InvocationID == 0)
	{
			gl_TessLevelOuter[AB] = 1;
			gl_TessLevelOuter[BC] = 1;
			gl_TessLevelOuter[CD] = 1;
			gl_TessLevelOuter[DA] = 1;
	
			gl_TessLevelInner[0] = 1;
			gl_TessLevelInner[1] = 1;	
	}
	
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
#type tesselation evalution
#version 430

layout(quads, fractional_odd_spacing, cw) in;

void main(){

    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
	
	// world position
	vec4 position =
	((1 - u) * (1 - v) * gl_in[12].gl_Position +
	u * (1 - v) * gl_in[0].gl_Position +
	u * v * gl_in[3].gl_Position +
	(1 - u) * v * gl_in[15].gl_Position);
	
	gl_Position = position;
}
#type geometry
#version 430

layout(triangles) in;
layout(line_strip, max_vertices = 4) out;

uniform mat4 uViewProjection;

void main() {
	
	for (int i = 0; i < gl_in.length(); ++i)
	{
		vec4 position = gl_in[i].gl_Position;
		gl_Position = uViewProjection * position;
		EmitVertex();
	}
	
	vec4 position = gl_in[0].gl_Position;
	gl_Position = uViewProjection * position;
    EmitVertex();
	
	EndPrimitive();
}
#type fragment
#version 430

layout(location = 0) out vec4 outColor;

void main()
{
	outColor = vec4(0.01, 1, 0.01, 1.0);
}