#version 450

/*
   Gaussian blur - horizontal pass, dynamic range, resizable
   
   Copyright (C) 2020 guest(r) - guest.r@gmail.com

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
   
*/ 

layout(push_constant) uniform Push
{
	vec4 LinearizePassSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	uint FrameCount;
	float glow;
	float SIZEH;
	float SIGMA_H;
} params;

#pragma parameter bogus_glow "[ GLOW ]:" 0.0 0.0 1.0 1.0

#pragma parameter glow "          Strength -- glow" 0.08 -2.0 2.0 0.01
#define glow         params.glow     // Glow Strength

#pragma parameter SIZEH "          Horizontal Radius (Num Samples) -- SIZEH" 6.0 1.0 50.0 1.0 
#define SIZEH params.SIZEH

#pragma parameter SIGMA_H "          Horizontal Sigma ( Spread ) -- SIGMA_H" 1.20 0.20 15.0 0.10
#define SIGMA_H params.SIGMA_H

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

float invsqrsigma = 1.0/(2.0*SIGMA_H*SIGMA_H);

float gaussian(float x)
{
	return exp(-x*x*invsqrsigma);
}

void main()
{
	vec4 SourceSize1 = params.OriginalSize;
	float f = fract(SourceSize1.x * vTexCoord.x);
	f = 0.5 - f;
	vec2 tex = floor(SourceSize1.xy * vTexCoord)*SourceSize1.zw + 0.5*SourceSize1.zw;
	vec3 color = vec3(0.0);
	vec2 dx  = vec2(SourceSize1.z, 0.0);

	float w;
	float wsum = 0.0;
	vec3 pixel;
	float n = -SIZEH;

	do
	{
		pixel  = COMPAT_TEXTURE(LinearizePass, tex + n*dx).rgb;
		w      = gaussian(n+f);
		color  = color + w * pixel;
		wsum   = wsum + w;
		n = n + 1.0;
		
	} while (n <= SIZEH);

	color = color / wsum;
	
	FragColor = vec4(color, 1.0);
}