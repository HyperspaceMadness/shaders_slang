#version 450

/*
   Vertical Downsampling Shader (for even scanlines)
   
   Copyright (C) 2019-2020 guest(r) - guest.r@gmail.com
   
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
	float steps, srange;
} params;

#pragma parameter steps "Scanline Smoothing Interpolation Steps" 4.0 1.0 12.0 1.0
#pragma parameter srange "Scanline Smoothing Sampling Range" 0.75 0.05 2.5 0.05 

#define steps params.steps
#define srange params.srange

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
   vTexCoord = TexCoord*1.00001;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D Source;


void main()
{
	float shrink = texture(Source, vec2(0.1)).a;
	vec2 tex = vTexCoord;
	tex.y = tex.y*shrink;
	vec3 color = texture(Source, tex).rgb;
	
	float obuffer = params.FinalViewportSize.y/params.SourceSize.y;
	
	if (shrink > obuffer + 0.02)
	{	
		color = vec3(0.0);
		float ratio = (shrink/obuffer)*srange;
		float dy = 1.0/params.SourceSize.y;
		float wsum = 0.0;
		float dif = ratio/steps;
	
		for (float i = -ratio; i <= ratio; i = i + dif)
		{
			color += texture(Source, tex + vec2(0.0, dy * i)).rgb;
			wsum = wsum + 1.0;
		}
	
		color = color / wsum; 	
	}
	
	FragColor = vec4(color,1.0);
}