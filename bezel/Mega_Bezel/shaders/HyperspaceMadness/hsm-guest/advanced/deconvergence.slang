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

#include "../../hsm-globals-and-screen-scale-params.inc"

layout(push_constant) uniform Push
{
	vec4 OutputSize;
	uint FrameCount;
    float deconr;
	float TATE;
	float GDV_DECONVERGENCE_STRENGTH;
	float GDV_NOISE_AMOUNT;
	float GDV_MASK_TYPE;
	float GDV_MASK_SIZE;
	float GDV_DECONVERGENCE_H_RANGE_RED;
	float GDV_DECONVERGENCE_H_RANGE_GREEN;
	float GDV_DECONVERGENCE_H_RANGE_BLUE;
	float GDV_DECONVERGENCE_V_RANGE_RED;
	float GDV_DECONVERGENCE_V_RANGE_GREEN;
	float GDV_DECONVERGENCE_V_RANGE_BLUE;	
	float GDV_DECONVERGENCE_SMOOTHING;
} params;

// #pragma parameter TATE "          TATE Mode" 0.0 0.0 1.0 1.0
// #define TATE         params.TATE     // Screen orientation

#pragma parameter GDV_DECONVERGENCE_TITLE "[ HORIZONTAL/VERTICAL DECONVERGENCE ]: " 0.0 0.0 1.0 1.0

#pragma parameter GDV_DECONVERGENCE_H_RANGE_RED "          Horizontal Deconvergence Red Range" 0.0 -7.0 7.0 0.25

#pragma parameter GDV_DECONVERGENCE_H_RANGE_GREEN "          Horizontal Deconvergence Green Range" 0.0 -7.0 7.0 0.25

#pragma parameter GDV_DECONVERGENCE_H_RANGE_BLUE "          Horizontal Deconvergence Blue Range" 0.0 -7.0 7.0 0.25

#pragma parameter GDV_DECONVERGENCE_V_RANGE_RED "          Vertical Deconvergence Red Range" 0.0 -7.0 7.0 0.25

#pragma parameter GDV_DECONVERGENCE_V_RANGE_GREEN "          Vertical Deconvergence Green Range" 0.0 -7.0 7.0 0.25

#pragma parameter GDV_DECONVERGENCE_V_RANGE_BLUE "          Vertical Deconvergence Blue Range" 0.0 -7.0 7.0 0.25
 
#pragma parameter GDV_DECONVERGENCE_STRENGTH "          Deconvergence Strength" 0.5 0.0 2.0 0.05
#define GDV_DECONVERGENCE_STRENGTH        params.GDV_DECONVERGENCE_STRENGTH     // Horizontal deconvergence colors strength

#pragma parameter GDV_DECONVERGENCE_SMOOTHING "          Deconvergence Smoothing" 0.0 0.0 1.0 0.10

#pragma parameter GDV_NOISE_AMOUNT "          Add Noise" 0.0 -1.0 1.0 0.05
#define GDV_NOISE_AMOUNT       params.GDV_NOISE_AMOUNT    // Switch colors left/right

#pragma parameter GDV_MASK_TYPE "          CRT Mask: 0:CGWG, 1-4:Lottes, 5-7:'Trinitron'" 0.0 -1.0 8.0 1.0
#define shadowMask   params.GDV_MASK_TYPE     // Mask Style

#pragma parameter GDV_MASK_SIZE "          CRT Mask Size - 0:Auto | 1:2K | 2:4k" 0 1 4 1
#define masksize     params.GDV_MASK_SIZE     // Mask Size

/*
layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
	vec2 FinalViewportSize;
} global;
*/

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
layout(set = 0, binding = 1) uniform sampler2D InfoCachePass;
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
    if (GDV_NOISE_AMOUNT < 0.0) v.z = -GDV_NOISE_AMOUNT; else v.z = v.z/6000.0;
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
	HSM_UpdateGlobalScreenValuesFromCache(InfoCachePass, vTexCoord);
	float TATE = USE_VERTICAL_SCANLINES;

	vec3 color = COMPAT_TEXTURE(Source, vTexCoord).rgb;
	vec3 result = color;
	
	if ((abs(params.GDV_DECONVERGENCE_H_RANGE_RED) + abs(params.GDV_DECONVERGENCE_H_RANGE_GREEN) + abs(params.GDV_DECONVERGENCE_H_RANGE_BLUE) + abs(params.GDV_DECONVERGENCE_V_RANGE_RED) + abs(params.GDV_DECONVERGENCE_V_RANGE_GREEN) + abs(params.GDV_DECONVERGENCE_V_RANGE_BLUE)) > 0.20)
	{	
		/* HSM Removed
		float step = masksizes[int(shadowMask)+1]*masksize;
		*/

		// HSM ADDED
		float final_mask_size = masksize;
		// If using automatic Mask Size
		if (masksize < 0.5)
			final_mask_size = (global.FinalViewportSize.x + global.FinalViewportSize.y) / 3 > 1900 ? 2 : 1;
		float step = masksizes[int(shadowMask)+1]*final_mask_size;

		step*= (TATE < 0.5) ? (params.OutputSize.z) : (params.OutputSize.w);
		float stepy = (TATE < 0.5) ? (params.OutputSize.w) : (params.OutputSize.z);
		
		vec2 dx = (TATE < 0.5) ? vec2(step, 0.0) :  vec2(0.0, step);
		vec2 dy = (TATE > 0.5) ? vec2(stepy, 0.0) :  vec2(0.0, stepy);		

		vec2 rc = params.GDV_DECONVERGENCE_H_RANGE_RED * dx + params.GDV_DECONVERGENCE_V_RANGE_RED*dy;
		vec2 gc = params.GDV_DECONVERGENCE_H_RANGE_GREEN * dx + params.GDV_DECONVERGENCE_V_RANGE_GREEN*dy;
		vec2 bc = params.GDV_DECONVERGENCE_H_RANGE_BLUE * dx + params.GDV_DECONVERGENCE_V_RANGE_BLUE*dy;		

		dx = (dx+dy) * params.GDV_DECONVERGENCE_SMOOTHING;
		
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
		
		result = clamp(mix(color, (result1+result2+result3)/3.0, GDV_DECONVERGENCE_STRENGTH), 0.0, 1.0);

		float mc = max(max(color.r,color.g),color.b);		
		float mr = max(max(result.r,result.g),result.b);
		result = plant(result, clamp(mix(mc,mr,0.7*mc+0.3), 0.5*mc, 1.0));
	}
	
	result = mix(result, noise(vec3(params.OutputSize.xy * vTexCoord, float(params.FrameCount))), 0.2*abs(GDV_NOISE_AMOUNT));
	
	float corner = COMPAT_TEXTURE(Source, vTexCoord).a;	
	
	FragColor = vec4(result*corner, 1.0);
}