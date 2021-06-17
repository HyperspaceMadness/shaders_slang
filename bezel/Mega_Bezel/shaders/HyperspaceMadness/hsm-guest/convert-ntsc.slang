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
	vec3 col = texture(Source, vTexCoord).rgb;
	vec3 orig = texture(PrePass0, vTexCoord).rgb;
	vec3 res = plant(col, max(max(orig.r, orig.g), orig.b));
	vec3 res1 = min(res, col);
	
	res1 = clamp(mix(orig, sqrt(col*orig), 5.0), plant(0.5*(res1+res1*res1), max(max(res1.r, res1.g), res1.b)), min(max(col,orig),res));
	
	FragColor = vec4(res1, 1.0);
}