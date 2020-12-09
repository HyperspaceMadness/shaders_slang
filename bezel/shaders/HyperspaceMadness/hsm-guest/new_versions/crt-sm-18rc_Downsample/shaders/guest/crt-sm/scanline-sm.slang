#version 450

/*
   Scanline Brightness Pass
   
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
	vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	vec4 FinalViewportSize; 	
	uint FrameCount;
	float smart, stype, scanline1, scanline2, beam_min, beam_max;
} params;

#pragma parameter smart "1:Smart 2:Crop 3:Overscan Y Integer Scaling 4:Smoothing" 4.0 0.0 4.0 1.0     // this parameter must reflect the values in the crt-guest-sm.slang shader or an error will occour
#pragma parameter stype "Scanline Type" 0.0 0.0 2.0 1.0                                    // this parameter must reflect the values in the crt-guest-sm.slang shader or an error will occour
#pragma parameter scanline1 "Scanline Shape Center" 6.0 2.0 20.0 0.5                       // this parameter must reflect the values in the crt-guest-sm.slang shader or an error will occour
#pragma parameter scanline2 "Scanline Shape Edges"  7.0 4.0 20.0 0.5                       // this parameter must reflect the values in the crt-guest-sm.slang shader or an error will occour
#pragma parameter beam_min "Scanline dark" 1.40 0.5 3.0 0.05                               // this parameter must reflect the values in the crt-guest-sm.slang shader or an error will occour
#pragma parameter beam_max "Scanline bright" 1.00 0.5 3.0 0.05                             // this parameter must reflect the values in the crt-guest-sm.slang shader or an error will occour

#define smart params.smart
#define stype params.stype
#define scanline1 params.scanline1
#define scanline2 params.scanline2
#define beam_min params.beam_min
#define beam_max params.beam_max

#define COMPAT_TEXTURE(c,d) texture(c,d)
#define TEX0 vTexCoord

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
layout(set = 0, binding = 3) uniform sampler2D RotPass;	

float sw1(float x, vec3 color, float scan)
{
	vec3 tmp = mix(vec3((2.50 - 1.5*stype)*beam_min),vec3(beam_max), color);
	tmp = mix(vec3(beam_max), tmp, pow(vec3(x), color + 0.30));
	vec3 ex = vec3(x)*tmp;
	vec3 res = exp2(-scan*ex*ex);
	float mx = max(max(res.r,res.g),res.b);
	vec3 w = mix(vec3(mx), res, mix(0.60,0.0,stype));
	float origbr = color.r + color.g + color.b;
	float scanbr = w.r*color.r + w.g*color.g + w.b*color.b;
	if (origbr == 0.0) return max(max(w.r,w.b),w.r);
	return scanbr/origbr;	
}

float sw1_(float x, vec3 color, float scan)
{	
	float mx = max(max(color.r,color.g),color.b);
	float ex = mix((2.5 - 1.5*stype)*beam_min, beam_max, mx);
	ex = mix(beam_max, ex, pow(x, mx + 0.25))*x;
	return exp2(-scan*ex*ex);
}

float sw2(float x, vec3 color, float scan)
{	
	vec3 ex = mix(vec3(2.0*beam_min), vec3(beam_max), color);
	vec3 m = 0.5*ex;
	ex = x*ex; 
	vec3 xx = ex*ex;
	xx = mix(xx, ex*xx, m);
	vec3 res = exp2(-1.25*scan*xx);
	float mx = max(max(res.r,res.g),res.b);
	vec3 w = mix(vec3(mx), res, 0.60);
	float origbr = color.r + color.g + color.b;
	float scanbr = w.r*color.r + w.g*color.g + w.b*color.b;
	if (origbr == 0.0) return max(max(w.r,w.b),w.r);
	return scanbr/origbr;	
}

float sw2_(float x, vec3 color, float scan)
{	
	float mx = max(max(color.r,color.g),color.b);
	float ex = mix(2.0*beam_min, beam_max, mx);
	float m = 0.5*ex;
	x = x*ex; float xx = x*x;
	xx = mix(xx, x*xx, m);
	return exp2(-1.25*scan*xx);
} 

void main()
{
	
	float ratio = texture(RotPass, vec2(0.5,0.1)).a;
	if (vTexCoord.y > ratio) discard;   

	vec4 SourceSize1 = params.SourceSize;
	float vertres = SourceSize1.y*ratio;

	float factor = params.FinalViewportSize.y/vertres;	
	float intfactor1 = floor(1.5*params.FinalViewportSize.y/vertres);

	if (smart == 0.0) factor = factor;
	if (smart == 1.0) factor = round(factor);
	if (smart == 2.0) factor = floor(factor);
	if (smart == 3.0) factor = ceil(factor);	
	if (smart == 4.0) factor = intfactor1; 
	
	vec3 tcolor = texture(Source, vTexCoord - vec2(0.0, SourceSize1.w)).rgb;
	vec3 ccolor = texture(Source, vTexCoord).rgb;
	vec3 bcolor = texture(Source, vTexCoord + vec2(0.0, SourceSize1.w)).rgb;
	vec3 color1, color2 = ccolor;
	
	float dx = 1.0/factor; 
	float f1,f2 = 0.0; 
	float w = 1e-7;
	float w1, w2 = 0.0;
	float counter = 1e-7;
	
	for (float i = 0.5*dx; i < 1.0; i = i + dx)
	{	
		f1 = i;
		f2 = 1.0 - i;
		
		if (f1 > 0.5) color1 = bcolor;
		if (f2 > 0.5) color2 = tcolor;		
		
		float scan1 = mix(scanline1, scanline2, f1);
		float scan2 = mix(scanline1, scanline2, f2);
		
		if (stype < 1.5)
		{
			w1 = sw1(f1, color1, scan1);
			w2 = sw1(f2, color2, scan2);
		}
		else
		{
			w1 = sw2(f1, color1, scan1);
			w2 = sw2(f2, color2, scan2);
		}
		
		color1 = ccolor; color2 = ccolor;
		w+= w1 + w2;
		counter = counter + 1.0;
	}

	w = clamp(w/counter, 0.001, 1.0);
	
	FragColor = vec4(ccolor,w); 
}