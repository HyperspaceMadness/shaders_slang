#version 450

layout(push_constant) uniform Push
{
	vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	uint FrameCount;
	float blendMode;
} params;

#pragma parameter blendMode "NTSC Blend Mode (use 2-3 for dithering)" 0.0 0.0 3.0 1.0

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
	if (params.blendMode > 1.5)
	{
		vec3 col0 = texture(Source, vTexCoord - dx).rgb;
		     col1 = texture(Source, vTexCoord     ).rgb;
		     col2 = texture(Source, vTexCoord + dx).rgb;
	
		float k1 = 1.0/(dot(col1 - res, col1 - res) + 0.0001);
		float k2 = 1.0/(dot(col2 - res, col2 - res) + 0.0001);
		float k3 = 1.0/(dot(col0 - res, col0 - res) + 0.0001);
		float k4 = 0.15 * (k1 + k2 + k3);
		k1 = k1 - k4;
		k2 = k2 - k4;
		k3 = k3 - k4;	
		res = (k1 * sqrt(col1) + k2 * sqrt(col2) + k3 * sqrt(col0)) / (k1 + k2 + k3);
		res = res * res;
	}

	FragColor = vec4(res, 1.0);
}