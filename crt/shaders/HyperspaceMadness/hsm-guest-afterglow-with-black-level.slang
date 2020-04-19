#version 450

/*
   Phosphor Afterglow Shader - Reduced number of parameters by HyperspaceMadness
   
   Copyright (C) 2018 guest(r) - guest.r@gmail.com

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
   float hag_afterglow_amount;
   // float hag_afterglow_persistence;
   // float hag_afterglow_saturation;
} params;

//#include "hsm-mega-bezel-params.inc"
// Get the black level from here
#include "hsm-mega-screen-scale.inc"

const float hag_afterglow_persistence = 0.5;
const float hag_afterglow_saturation = 0.1;

#define COMPAT_TEXTURE(c,d) texture(c,d)

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
layout(set = 0, binding = 3) uniform sampler2D OriginalHistory1;
layout(set = 0, binding = 4) uniform sampler2D OriginalHistory2;
layout(set = 0, binding = 5) uniform sampler2D OriginalHistory3;
layout(set = 0, binding = 6) uniform sampler2D OriginalHistory4;
layout(set = 0, binding = 7) uniform sampler2D OriginalHistory5;
layout(set = 0, binding = 8) uniform sampler2D OriginalHistory6;

#define Prev1Texture OriginalHistory1
#define Prev2Texture OriginalHistory2
#define Prev3Texture OriginalHistory3
#define Prev4Texture OriginalHistory4
#define Prev5Texture OriginalHistory5
#define Prev6Texture OriginalHistory6

#define TEX0 vTexCoord

#define eps 1e-3

vec3 afterglow(float number)
{
	return vec3(params.hag_afterglow_amount) * exp2(-vec3(hag_afterglow_persistence) * vec3(number * number));
}

void main()
{
   vec3 rgb_color = COMPAT_TEXTURE(Source, TEX0.xy).rgb;

   if (params.hag_afterglow_amount != 0)
   {
      vec3 glow = vec3(0);
      glow += COMPAT_TEXTURE(Prev1Texture, TEX0.xy).rgb * afterglow(1.0);
      glow += COMPAT_TEXTURE(Prev2Texture, TEX0.xy).rgb * afterglow(2.0);
      glow += COMPAT_TEXTURE(Prev3Texture, TEX0.xy).rgb * afterglow(3.0);
      glow += COMPAT_TEXTURE(Prev4Texture, TEX0.xy).rgb * afterglow(4.0);
      glow += COMPAT_TEXTURE(Prev5Texture, TEX0.xy).rgb * afterglow(5.0);
      glow += COMPAT_TEXTURE(Prev6Texture, TEX0.xy).rgb * afterglow(6.0);

      glow = normalize(pow(glow + vec3(eps), vec3(hag_afterglow_saturation))) * length(glow);		
      
      float glow_over_threshold = (rgb_color.r + rgb_color.g + rgb_color.b) > 7.0 / 255.0 ? 0 : 1;
      
      rgb_color += glow_over_threshold * glow;
   }
   // Apply Black level adjustment and the rgb_color is not linearized
   FragColor =  HMSS_ApplyBlackLevelGammaLuminance(vec4(rgb_color,1), 0);
}