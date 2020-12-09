#version 450

#pragma format R32G32B32A32_SFLOAT

layout(push_constant) uniform Push
{
	vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	uint FrameCount;
	float decon;
	float deconstr;
	float GAMMA_INPUT; 	
} params;

#pragma parameter GAMMA_INPUT "Gamma Input" 2.4 1.0 5.0 0.05
#define GAMMA_INPUT params.GAMMA_INPUT

#pragma parameter bogus_deconvergence "[ HORIZONTAL DECONVERGENCE ]:" 0.0 0.0 1.0 1.0

#pragma parameter decon "          Horizontal Deconvergence Range" 1.0 -8.0 8.0 0.250
#define decon        params.decon     // Horizontal deconvergence range

#pragma parameter deconstr "          Horizontal Deconvergence Strength" 0.0 0.0 1.0 0.05
#define deconstr     params.deconstr  // Horizontal deconvergence strength

#define SourceSize  params.SourceSize

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
   vTexCoord = TexCoord * 1.00001;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D PrePass;

#define COMPAT_TEXTURE(c,d) texture(c,d)

void main()
{
	vec2 dx1 =  vec2(1.0/SourceSize.x, 0.0)*decon;
	vec2 dx2 = -vec2(1.0/SourceSize.x, 0.0)*decon;
	
	vec3  c = COMPAT_TEXTURE(PrePass, vTexCoord).rgb;
	
	float r = COMPAT_TEXTURE(PrePass, vTexCoord + dx1).r;
	float b = COMPAT_TEXTURE(PrePass, vTexCoord + dx2).b;

	vec3 res = c;
	res.rb = mix(c.rb, vec2(r,b), deconstr);

	float gamma_in = 1.0/GAMMA_INPUT;
	
	FragColor = vec4(pow(res, vec3(GAMMA_INPUT)), gamma_in);
}