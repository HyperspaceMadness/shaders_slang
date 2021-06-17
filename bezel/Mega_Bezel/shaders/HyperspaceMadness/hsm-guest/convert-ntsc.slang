#version 450

layout(push_constant) uniform Push
{
	vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	uint FrameCount;
} params;

layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
} global;

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D Source;
layout(set = 0, binding = 3) uniform sampler2D PrePass0;

vec3 plant (vec3 tar, float r)
{
	float t = max(max(tar.r,tar.g),tar.b) + 0.00001;
	return tar * r / t;
}

void main()
{
	vec2 dx = vec2(params.SourceSize.z * 0.5, 0.0);

	vec3 col1 = texture(Source, vTexCoord -dx).rgb;
	vec3 col2 = texture(Source, vTexCoord +dx).rgb;	
	vec3 col = max(col1,col2);
	vec3 orig = texture(PrePass0, vTexCoord).rgb;
	vec3 res = normalize(col + 0.00001) * min(length(col), length(orig));
	
	FragColor = vec4(res, 1.0);
}