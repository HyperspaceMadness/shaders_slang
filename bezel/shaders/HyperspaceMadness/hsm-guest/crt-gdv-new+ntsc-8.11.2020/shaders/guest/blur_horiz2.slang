#version 450

layout(push_constant) uniform Push
{
	vec4 LinearizePassSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	uint FrameCount;
   float SIZEH;
   float GLOW_FALLOFF_H;
} params;

// Higher value, more centered glow.
// Lower values might need more taps.

#pragma parameter SIZEH "H. Glow Radius" 4.0 1.0 12.0 0.5 
#define SIZEH params.SIZEH

#pragma parameter GLOW_FALLOFF_H "Horizontal Glow Grade" 0.30 0.00 1.0 0.1 
#define GLOW_FALLOFF_H params.GLOW_FALLOFF_H

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
layout(set = 0, binding = 2) uniform sampler2D LinearizePass;

#define COMPAT_TEXTURE(c,d) texture(c,d)
#define LinearizePassSize params.LinearizePassSize

void main()
{
	vec3 color = vec3(0.0);
	float x = 0.25*SIZEH/1200.0;
	vec2 x1 = vec2(x, 0.0);
	vec2 dx = x1;

	float w1 = mix(0.218818, 0.121647, GLOW_FALLOFF_H);
	float w3 = mix(0.188264, 0.116229, GLOW_FALLOFF_H);
	float w5 = mix(0.119895, 0.101380, GLOW_FALLOFF_H);
	float w7 = mix(0.056512, 0.080725, GLOW_FALLOFF_H);
	float w9 = mix(0.019711, 0.058680, GLOW_FALLOFF_H);
	float w11 = mix(0.005086, 0.038940, GLOW_FALLOFF_H);
	float w13 = mix(0.000971, 0.023590, GLOW_FALLOFF_H);
	float w15 = mix(0.000137, 0.013046, GLOW_FALLOFF_H);
	float w17 = mix(0.000014, 0.006586, GLOW_FALLOFF_H);
	float w2 = 0.5*(w1 + w3);
	float w4 = 0.5*(w3 + w5);
	float w6 = 0.5*(w5 + w7);
	float w8 = 0.5*(w7 + w9);
	float w10 = 0.5*(w9 + w11);
	float w12 = 0.5*(w11 + w13);
	float w14 = 0.5*(w13 + w15);
	float w16 = 0.5*(w15 + w17);
	
	float w = 1.0/(1.5*(w1+w17)+3.0*(w3+w5+w7+w9+w11+w13+w15));
	
	color += COMPAT_TEXTURE(LinearizePass, vTexCoord).rgb * w1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w2; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w3; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w4; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w5; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w6; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w7; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w8; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w9; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w10; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w11; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w12; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w13; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w14; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w15; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w16; dx+=x1;
	color += (COMPAT_TEXTURE(LinearizePass, vTexCoord + dx).rgb + COMPAT_TEXTURE(LinearizePass, vTexCoord - dx).rgb) * w17;
	
	FragColor = vec4(color * w, 1.0);
}