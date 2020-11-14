#version 450

layout(push_constant) uniform Push
{
	vec4 SourceSize;
	vec4 OriginalSize;
	vec4 FinalViewportSize;
	vec4 OutputSize;
	uint FrameCount;
   float SIZEV;
   float GLOW_FALLOFF_V;
} params;

// Higher value, more centered glow.
// Lower values might need more taps.
// Parameter lines go here:
#pragma parameter SIZEV "V. Glow Radius" 4.0 1.0 12.0 0.5 
#define SIZEV params.SIZEV
#pragma parameter GLOW_FALLOFF_V "Vertical Glow Grade" 0.30 0.00 1.0 0.1 
#define GLOW_FALLOFF_V params.GLOW_FALLOFF_V

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

void main()
{
	vec3 color = vec3(0.0);
	float y = (params.OriginalSize.x/params.OriginalSize.y)*0.25*SIZEV/1200.0;
	vec2 y1 = vec2(0.0, y);
	vec2 dy = y1;
	
	float w1 = mix(0.218818, 0.121647, GLOW_FALLOFF_V);
	float w3 = mix(0.188264, 0.116229, GLOW_FALLOFF_V);
	float w5 = mix(0.119895, 0.101380, GLOW_FALLOFF_V);
	float w7 = mix(0.056512, 0.080725, GLOW_FALLOFF_V);
	float w9 = mix(0.019711, 0.058680, GLOW_FALLOFF_V);
	float w11 = mix(0.005086, 0.038940, GLOW_FALLOFF_V);
	float w13 = mix(0.000971, 0.023590, GLOW_FALLOFF_V);
	float w15 = mix(0.000137, 0.013046, GLOW_FALLOFF_V);
	float w17 = mix(0.000014, 0.006586, GLOW_FALLOFF_V);
	float w2 = 0.5*(w1 + w3);
	float w4 = 0.5*(w3 + w5);
	float w6 = 0.5*(w5 + w7);
	float w8 = 0.5*(w7 + w9);
	float w10 = 0.5*(w9 + w11);
	float w12 = 0.5*(w11 + w13);
	float w14 = 0.5*(w13 + w15);
	float w16 = 0.5*(w15 + w17);
	
	float w = 1.0/(1.5*(w1+w17)+3.0*(w3+w5+w7+w9+w11+w13+w15));
	
	color += COMPAT_TEXTURE(Source, vTexCoord).rgb * w1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w2; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w3; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w4; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w5; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w6; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w7; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w8; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w9; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w10; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w11; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w12; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w13; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w14; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w15; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w16; dy+=y1;
	color += (COMPAT_TEXTURE(Source, vTexCoord + dy).rgb + COMPAT_TEXTURE(Source, vTexCoord - dy).rgb) * w17;
	
	FragColor = vec4(color * w, 1.0);
}