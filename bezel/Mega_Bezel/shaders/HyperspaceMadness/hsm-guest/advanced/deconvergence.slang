#version 450

/*
   CRT - Guest - Advanced - Deconvergence pass + noise
   
   Copyright (C) 2021 guest(r) - guest.r@gmail.com
   
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
	vec4 OutputSize;
	uint FrameCount;
    float deconr;
	float TATE;
	float decons;
	float addnoise;
	float shadowMask;
	float masksize;
	float deconrr;
	float deconrg;
	float deconrb;
	float deconrry;
	float deconrgy;
	float deconrby;	
	float deconsmooth;
} params;

#pragma parameter TATE "          TATE Mode" 0.0 0.0 1.0 1.0
#define TATE         params.TATE     // Screen orientation

#pragma parameter bogus_hdeconvergence "[ HORIZONTAL/VERTICAL DECONVERGENCE ]: " 0.0 0.0 1.0 1.0

#pragma parameter deconrr "          Horizontal Deconvergence Red Range" 0.0 -7.0 7.0 0.5

#pragma parameter deconrg "          Horizontal Deconvergence Green Range" 0.0 -7.0 7.0 0.5

#pragma parameter deconrb "          Horizontal Deconvergence Blue Range" 0.0 -7.0 7.0 0.5

#pragma parameter deconrry "          Vertical Deconvergence Red Range" 0.0 -7.0 7.0 0.5

#pragma parameter deconrgy "          Vertical Deconvergence Green Range" 0.0 -7.0 7.0 0.5

#pragma parameter deconrby "          Vertical Deconvergence Blue Range" 0.0 -7.0 7.0 0.5
 
#pragma parameter decons "          Deconvergence Strength" 0.5 0.0 2.0 0.05
#define decons        params.decons     // Horizontal deconvergence colors strength

#pragma parameter deconsmooth "          Deconvergence Smoothing" 0.0 0.0 1.0 0.25

#pragma parameter addnoise "          Add Noise" 0.0 -1.0 1.0 0.05
#define addnoise       params.addnoise    // Switch colors left/right

#pragma parameter shadowMask "          CRT Mask: 0:CGWG, 1-4:Lottes, 5-7:'Trinitron'" 0.0 -1.0 8.0 1.0
#define shadowMask   params.shadowMask     // Mask Style

#pragma parameter masksize "          CRT Mask Size (2.0 is nice in 4k)" 1.0 1.0 4.0 1.0
#define masksize     params.masksize     // Mask Size

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


const float masksizes[10] = float[10](2.0, 2.0, 3.0, 3.0, 3.0, 3.0, 2.0, 3.0, 2.0, 4.0);

vec3 plant (vec3 tar, float r)
{
	float t = max(max(tar.r,tar.g),tar.b) + 0.00001;
	return tar * r / t;
}

// noise function:
// Dedicated to the public domain.
// If you want a real license, you may consider this MIT/BSD/CC0/WTFPL-licensed (take your pick).
// Adapted from ChuckNorris - shadertoy: https://www.shadertoy.com/view/XtK3Dz

vec3 noise(vec3 v){
    if (addnoise < 0.0) v.z = -addnoise; else v.z = v.z/6000.0;
	// ensure reasonable range
    v = fract(v) + fract(v*1e4) + fract(v*1e-4);
    // seed
    v += vec3(0.12345, 0.6789, 0.314159);
    // more iterations => more random
    v = fract(v*dot(v, v)*123.456);
    v = fract(v*dot(v, v)*123.456);
    return v;
}

void main()
{
	
	vec3 color = COMPAT_TEXTURE(Source, vTexCoord).rgb;
	vec3 result = color;
	
	if ((abs(params.deconrr) + abs(params.deconrg) + abs(params.deconrb)) > 0.25)
	{	
		float step = masksizes[int(shadowMask)+1]*masksize;
		step*= (TATE < 0.5) ? (params.OutputSize.z) : (params.OutputSize.w);
		float stepy = (TATE < 0.5) ? (params.OutputSize.w) : (params.OutputSize.z);
		
		vec2 dx = (TATE < 0.5) ? vec2(step, 0.0) :  vec2(0.0, step);
		vec2 dy = (TATE > 0.5) ? vec2(stepy, 0.0) :  vec2(0.0, stepy);		

		vec2 rc = params.deconrr * dx + params.deconrry*dy;
		vec2 gc = params.deconrg * dx + params.deconrgy*dy;
		vec2 bc = params.deconrb * dx + params.deconrby*dy;		

		dx = (dx+dy) * params.deconsmooth;
		
		float r1 = COMPAT_TEXTURE(Source, vTexCoord + rc    ).r;
		float g1 = COMPAT_TEXTURE(Source, vTexCoord + gc    ).g;
		float b1 = COMPAT_TEXTURE(Source, vTexCoord + bc    ).b;

		float r2 = COMPAT_TEXTURE(Source, vTexCoord + rc -dx).r;
		float g2 = COMPAT_TEXTURE(Source, vTexCoord + gc -dx).g;
		float b2 = COMPAT_TEXTURE(Source, vTexCoord + bc -dx).b;

		float r3 = COMPAT_TEXTURE(Source, vTexCoord + rc +dx).r;
		float g3 = COMPAT_TEXTURE(Source, vTexCoord + gc +dx).g;
		float b3 = COMPAT_TEXTURE(Source, vTexCoord + bc +dx).b;

		vec3 result1 = vec3(r1,g1,b1);
		vec3 result2 = vec3(r2,g2,b2);
		vec3 result3 = vec3(r3,g3,b3);
		
		result = clamp(mix(color, (result1+result2+result3)/3.0, decons), 0.0, 1.0);

		float mc = max(max(color.r,color.g),color.b);		
		float mr = max(max(result.r,result.g),result.b);
		result = plant(result, clamp(mix(mc,mr,0.7*mc+0.3), 0.5*mc, 1.0));
	}
	
	result = mix(result, noise(vec3(params.OutputSize.xy * vTexCoord, float(params.FrameCount))), 0.2*abs(addnoise));
	
	float corner = COMPAT_TEXTURE(Source, vTexCoord).a;	
	
	FragColor = vec4(result*corner, 1.0);
}