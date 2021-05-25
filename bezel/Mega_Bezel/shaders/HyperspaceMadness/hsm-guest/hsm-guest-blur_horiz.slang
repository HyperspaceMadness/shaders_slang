#version 450

layout(push_constant) uniform Push
{
	vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	uint FrameCount;
   float TAPSH;
   // HSM Removed
   // float GLOW_FALLOFF_H;
   // HSM Added
   float GST_GLOW_GRADE;
} params;

// Higher value, more centered glow.
// Lower values might need more taps.
// HSM Removed
// #pragma parameter TAPSH "H. Glow Radius" 4.0 1.0 10.0 1.0 
// #define TAPSH params.TAPSH
// HSM Added
#define TAPSH 4

// HSM Removed
// #pragma parameter GLOW_FALLOFF_H "Horizontal Glow Grade" 0.30 0.00 1.0 0.01 
// #define GLOW_FALLOFF_H params.GLOW_FALLOFF_H

// HSM Added
#pragma parameter GDV_TITLE 		"______[ --- GUEST-DrVENOM --- ]:" 0 0 0 1

#pragma parameter GDV_GLOW_TITLE 		"[ GLOW ]:" 0 0 0 1
#pragma parameter GST_GLOW_GRADE 	"      Glow Grade" 0.30 0.00 1.0 0.01 
#define GLOW_FALLOFF_H params.GST_GLOW_GRADE

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

#define COMPAT_TEXTURE(c,d) texture(c,d)
#define SourceSize params.SourceSize

#define kernel(x) exp(-GLOW_FALLOFF_H * (x) * (x))

void main()
{
	vec3 col = vec3(0.0);
	float dx = SourceSize.z;

	float k_total = 0.;
	for (float i = -TAPSH; i <= TAPSH; i++)
		{
		float k = kernel(i);
		k_total += k;
		col += k * COMPAT_TEXTURE(Source, vTexCoord + vec2(float(i) * dx, 0.0)).rgb;
		}
   FragColor = vec4(col / k_total, 1.0);
}