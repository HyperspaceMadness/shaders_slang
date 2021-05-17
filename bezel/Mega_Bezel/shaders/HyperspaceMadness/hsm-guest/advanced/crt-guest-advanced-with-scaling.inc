/*
   CRT - Guest - Advanced
   
   Copyright (C) 2018-2021 guest(r) - guest.r@gmail.com

   Incorporates many good ideas and suggestions from Dr. Venom.
   I would also like give thanks to many Libretro forums members for continuous feedback, suggestions and caring about the shader.
   
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
	float GDV_BRIGHT_BOOST_DARK_PIXELS;
	float GDV_BRIGHT_BOOST_BRIGHT_PIXELS;
	float GDV_GLOW_STRENGTH;
	float GDV_BLOOM_STRENGTH;
	float GDV_HALATION_STRENGTH;

	float GDV_SCANLINE_TYPE;
	float GDV_SCANLINE_SHAPE_CENTER;
	float GDV_SCANLINE_SHAPE_EDGES;
	float GDV_SCANLINE_BEAM_SIZE_DARK_MIN;
	float GDV_SCANLINE_BEAM_SIZE_MAX_BRIGHT;
	float GDV_SCANLINE_BEAM_SIZE;
	float GDV_SCANLINE_SATURATION;

    float GDV_HORIZONTAL_SHARPNESS;
	float GDV_SUBTRACTIVE_SHARPNESS;
	float GDV_SMART_EDGES_STRENGTH;
	float GDV_SMART_EDGES_STRENGTH_LIMIT;
	float GDV_SMART_EDGES_SMOOTHING_THRESHOLD;

	float GDV_MASK_TYPE;
	float GDV_MASK_SIZE;
	float GDV_MASK_GAMMA;
	float GDV_MASK_TRINITRON_STRENGTH;
	float GDV_MASK_LOTTES_DARK;
	float GDV_MASK_LOTTES_LIGHT;
	float GDV_MASK_0_5_TO_8_STRENGTH;
	float GDV_KEEP_MASK_WITH_CLIPPING;
	float GDV_SCANLINE_COLOR_DECONVERGENCE;
    float GDV_SLOTMASK_STRENGTH;
	float GDV_SLOTMASK_SIZE;
	float GDV_SLOTMASK_WIDTH;
	float GDV_SLOTMASK_HEIGHT;
	float GDV_SCANLINE_SPIKE_REMOVAL;
	// float scansub;
	float GDV_GAMMA_CORRECT;
} params;


#pragma parameter GDV_BRIGHTNESS_TITLE 				"[ BRIGHTNESS SETTINGS ]:" 0.0 0.0 1.0 1.0

#pragma parameter GDV_GLOW_STRENGTH 				"          Glow Strength" 0.08 0.0 2.0 0.01
#define glow         params.GDV_GLOW_STRENGTH     // Glow Strength

#pragma parameter GDV_BLOOM_STRENGTH 				"          Bloom Strength" 0.0 0.0 2.0 0.05
#define bloom         params.GDV_BLOOM_STRENGTH     // bloom effect

#pragma parameter GDV_HALATION_STRENGTH 			"          Halation Strength" 0.0 0.0 2.0 0.025
#define halation         params.GDV_HALATION_STRENGTH     // halation effect

#pragma parameter GDV_GAMMA_CORRECT 							"          Gamma correct" 1.0 0.50 2.0 0.02
#define gamma_c   params.GDV_GAMMA_CORRECT     // adjust brightness

#pragma parameter GDV_BRIGHT_BOOST_DARK_PIXELS 		"          Bright Boost Dark Pixels" 1.40 0.25 10.0 0.05
#define brightboost  params.GDV_BRIGHT_BOOST_DARK_PIXELS     // adjust brightness

#pragma parameter GDV_BRIGHT_BOOST_BRIGHT_PIXELS 	"          Bright Boost Bright Pixels" 1.10 0.25 3.00 0.025
#define brightboost1  params.GDV_BRIGHT_BOOST_BRIGHT_PIXELS     // adjust brightness


#pragma parameter GDV_SCANLINE_TITLE 				"[ SCANLINE OPTIONS ]: " 0.0 0.0 1.0 1.0

#pragma parameter GDV_SCANLINE_TYPE 				"          Scanline Type" 0.0 -1.0 2.0 1.0
#define gsl          params.GDV_SCANLINE_TYPE      // Alternate scanlines

#pragma parameter GDV_SCANLINE_SHAPE_CENTER 		"          Scanline Beam Shape Center" 6.0 0.0 20.0 0.5
#define scanline1    params.GDV_SCANLINE_SHAPE_CENTER      // scanline param, vertical sharpness

#pragma parameter GDV_SCANLINE_SHAPE_EDGES 			"          Scanline Beam Shape Edges" 8.0 3.0 40.0 1.0 
#define scanline2    params.GDV_SCANLINE_SHAPE_EDGES      // scanline param, vertical sharpness

#pragma parameter GDV_SCANLINE_BEAM_SIZE_DARK_MIN 	"          Scanline Shape Dark Pixels (Higher = Thinner)" 1.30 0.25 3.5 0.05
#define beam_min     params.GDV_SCANLINE_BEAM_SIZE_DARK_MIN     // dark area beam min - narrow

#pragma parameter GDV_SCANLINE_BEAM_SIZE_MAX_BRIGHT "          Scanline Shape Bright Pixels (Higher = Thicker)" 1.00 0.4 2.5 0.05
#define beam_max     params.GDV_SCANLINE_BEAM_SIZE_MAX_BRIGHT     // bright area beam max - wide

#pragma parameter GDV_SCANLINE_BEAM_SIZE   			"          Scanline Increased Bright Beam" 0.60 0.0 1.0 0.05
#define beam_size    params.GDV_SCANLINE_BEAM_SIZE     // increased max. beam size

#pragma parameter GDV_SCANLINE_COLOR_DECONVERGENCE 	"          Scanline Color Deconvergence" 0.0 -1.0 1.0 0.1
#define vertmask     params.GDV_SCANLINE_COLOR_DECONVERGENCE     // Scanline deconvergence colors

#pragma parameter GDV_SCANLINE_SATURATION 			"          Scanline Saturation" 0.60 0.0 1.0 0.05
#define scans        params.GDV_SCANLINE_SATURATION     // scanline saturation

// Scanline darken 'edges' effect - need to uncomment it.
	
// #pragma parameter scansub "          Scanline darken 'edges'" 0.0 0.0 0.30 0.005
// #define scansub      params.scansub   // scanline substraction

#pragma parameter GDV_SCANLINE_SPIKE_REMOVAL 		"          Spike Removal" 1.0 0.0 2.0 0.10
#define spike params.GDV_SCANLINE_SPIKE_REMOVAL


#pragma parameter GDV_FILTERING_TITLE 				"[ FILTERING OPTIONS ]: " 0.0 0.0 1.0 1.0

#pragma parameter GDV_HORIZONTAL_SHARPNESS 			"          Horizontal Sharpness" 5.20 0.20 15.0 0.20
#define h_sharp      params.GDV_HORIZONTAL_SHARPNESS     // pixel sharpness

#pragma parameter GDV_SUBTRACTIVE_SHARPNESS 		"          Subtractive Sharpness (1.0 recommended)" 0.50 0.0 1.5 0.10
#define s_sharp      params.GDV_SUBTRACTIVE_SHARPNESS     // substractive sharpness

#pragma parameter GDV_SMART_EDGES_STRENGTH 			"          Smart Edges Effect Strength" 0.0 0.0 20.0 0.25
#define smart_ei      params.GDV_SMART_EDGES_STRENGTH     // smart edge handling

#pragma parameter GDV_SMART_EDGES_STRENGTH_LIMIT 	"          Smart Edges Effect Strength Limit" 2.0 1.0 12.0 0.1
#define ei_limit      params.GDV_SMART_EDGES_STRENGTH_LIMIT     // smart edge handling

#pragma parameter GDV_SMART_EDGES_SMOOTHING_THRESHOLD     "          Smart Edges Smoothing Threshold" 0.20 0.0 1.0 0.01
#define sth        params.GDV_SMART_EDGES_SMOOTHING_THRESHOLD

// #pragma parameter bogus_screen 						"[ SCREEN OPTIONS ]: " 0.0 0.0 1.0 1.0

// #pragma parameter intres "          Internal Resolution Y: 224p/240p, 1.5...y-dowsample" 0.0 0.0 6.0 0.5 // Joint parameter with linearize pass, values must match

// #pragma parameter TATE "          TATE Mode" 0.0 0.0 1.0 1.0
// #define TATE         params.TATE     // Screen orientation
// #define TATE         0     // Screen orientation

// #pragma parameter IOS "          Integer Scaling: Odd:Y, Even:'X'+Y" 0.0 0.0 4.0 1.0
// #define IOS          params.IOS     // Smart Integer Scaling

// #pragma parameter OS "          R. Bloom Overscan Mode" 1.0 0.0 2.0 1.0
// #define OS           params.OS     // Do overscan

// #pragma parameter BLOOM "          Raster bloom %" 0.0 0.0 20.0 1.0
// #define BLOOM        params.BLOOM     // Bloom overscan percentage

// #pragma parameter csize "          Corner size" 0.0 0.0 0.25 0.01
// #define csize        params.csize     // corner size

// #pragma parameter bsize "          Border smoothness" 600.0 100.0 700.0 10.0
// #define bsize        params.bsize     // border smoothness

// #pragma parameter warpX "          CurvatureX (default 0.03)" 0.0 0.0 0.125 0.01
// #define warpX        params.warpX     // Curvature X

// #pragma parameter warpY "          CurvatureY (default 0.04)" 0.0 0.0 0.125 0.01
// #define warpY        params.warpY     // Curvature Y

// #pragma parameter overscanY "          Overscan Y original pixels" 0.0 -50.0 50.0 1.0
// #define overscanY        params.overscanY     // OverscanY pixels

// #pragma parameter prescalex "          Prescale-X Factor (for xBR...pre-shader)" 1.0 1.0 4.0 1.0
// #define prescalex        params.prescalex     // prescale-x factor

#pragma parameter GDV_CRT_MASK_TITLE 						"[ CRT MASK OPTIONS ]: " 0.0 0.0 1.0 1.0

#pragma parameter GDV_MASK_TYPE 							"          CRT Mask: 0:CGWG, 1-4:Lottes, 5-7:'Trinitron'" 0.0 -1.0 8.0 1.0
#define shadowMask   params.GDV_MASK_TYPE     // Mask Style

#pragma parameter GDV_MASK_0_5_TO_8_STRENGTH 				"          Mask Strength (0, 5-8)" 0.3 -0.5 1.0 0.05
#define maskstr         params.GDV_MASK_0_5_TO_8_STRENGTH      // CGWG Mask Strength

#pragma parameter GDV_MASK_SIZE 							"          CRT Mask Size - 0:Auto | 1:2K | 2:4k" 0 1 4 1
#define masksize     params.GDV_MASK_SIZE     // Mask Size

#pragma parameter GDV_MASK_LOTTES_DARK 						"          Lottes maskDark" 0.5 0.0 2.0 0.05
#define maskDark     params.GDV_MASK_LOTTES_DARK     // Dark "Phosphor"

#pragma parameter GDV_MASK_LOTTES_LIGHT 					"          Lottes maskLight" 1.5 0.0 2.0 0.05
#define maskLight    params.GDV_MASK_LOTTES_LIGHT     // Light "Phosphor"

#pragma parameter GDV_MASK_TRINITRON_STRENGTH 				"          Mask 5-7 Trinitron Low Strength" 1.10 0.0 2.0 0.05
#define mcut         params.GDV_MASK_TRINITRON_STRENGTH      // Mask 5-7 cutoff

#pragma parameter GDV_MASK_GAMMA 							"          Mask Gamma" 2.40 1.0 5.0 0.05
#define mask_gamma   params.GDV_MASK_GAMMA     // Mask application gamma

#pragma parameter GDV_SLOTMASK_STRENGTH 					"          Slot Mask Strength" 0.0 0.0 1.0 0.05
#define slotmask     params.GDV_SLOTMASK_STRENGTH     // Slot Mask ON/OFF

#pragma parameter GDV_SLOTMASK_WIDTH 						"          Slot Mask Width" 2.0 1.0 6.0 0.5
#define slotwidth    params.GDV_SLOTMASK_WIDTH     // Slot Mask Width

#pragma parameter GDV_SLOTMASK_HEIGHT 						"          Slot Mask Height: 2x1 or 4x1" 1.0 1.0 2.0 1.0
#define double_slot  params.GDV_SLOTMASK_HEIGHT     // Slot Mask Height

#pragma parameter GDV_SLOTMASK_SIZE 						"          Slot Mask Size - 0:Auto | 1:2K | 2:4k" 0 1 4 1
#define slotms  params.GDV_SLOTMASK_SIZE     // Slot Mask Size

#pragma parameter GDV_KEEP_MASK_WITH_CLIPPING 				"          Keep Mask effect with clipping" 0.50 0.0 1.0 0.05
#define mclip  params.GDV_KEEP_MASK_WITH_CLIPPING     // Slot Mask Size

// #pragma parameter gamma_out "Gamma out" 2.4 1.0 5.0 0.05
#define gamma_out    HSM_GAMMA_OUT_CRT     // output gamma

// #pragma parameter HSM_INTERLACE_EFFECT_SMOOTHNESS "          Interlacing Effect Smoothness" 0.0 0.0 0.5 0.05 // Joint parameter with linearize pass, values must match
#define inters  HSM_INTERLACE_EFFECT_SMOOTHNESS     // interlacing effect smoothing

// HSM Removed
// #define COMPAT_TEXTURE(c,d) texture(c,d)
// HSM Added
#define COMPAT_TEXTURE(c,d) HSM_GetCroppedTexSample(c,d)
// End Addition

#define TEX0 vTexCoord

#define OutputSize global.OutputSize
#define gl_FragCoord (vTexCoord * OutputSize.xy)

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord * 1.000001;
   
	if (HSM_FLIP_VIEWPORT_VERTICAL == 1)
		vTexCoord.y = 1 - vTexCoord.y;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;

// HSM Added
layout(set = 0, binding = 1) uniform sampler2D InfoCachePass;
layout(set = 0, binding = 2) uniform sampler2D IntroPass;
layout(set = 0, binding = 3) uniform sampler2D ColoredGelImage;
layout(set = 0, binding = 4) uniform sampler2D TubeStaticReflectionImage;
layout(set = 0, binding = 5) uniform sampler2D BackgroundImage;
layout(set = 0, binding = 6)  uniform sampler2D BackgroundVertImage;

layout(set = 0, binding = 7) uniform sampler2D LinearizePass;
layout(set = 0, binding = 8) uniform sampler2D AvgLumPass;
layout(set = 0, binding = 9) uniform sampler2D GlowPass;
layout(set = 0, binding = 10) uniform sampler2D BloomPass;

/* HSM Removed - Seemingly only used for vignette
layout(set = 0, binding = 11) uniform sampler2D PrePass;
*/

#define eps 1e-10 

float st(float x)
{
	return exp2(-10.0*x*x);
} 
   
float sw0(float x, float color, float scanline)
{
	float tmp = mix(beam_min, beam_max, color);
	float ex = x*tmp;
	ex = (gsl > -0.5) ? ex*ex : mix(ex*ex, ex*ex*ex, 0.4);
	return exp2(-scanline*ex);
} 

float sw1(float x, float color, float scanline)
{	
	x = mix (x, beam_min*x, max(x-0.4*color,0.0));
	float tmp = mix(1.2*beam_min, beam_max, color);
	float ex = x*tmp;
	return exp2(-scanline*ex*ex);
}    

float sw2(float x, float color, float scanline)
{
	float tmp = mix(2.5*beam_min, beam_max, color);
	tmp = mix(beam_max, tmp, pow(x, color+0.3));
	float ex = x*tmp;
	return exp2(-scanline*ex*ex);
}  

// Shadow mask (1-4 from PD CRT Lottes shader).

vec3 Mask(vec2 pos, float mx)
{
	// HSM Added
	float final_mask_size = masksize;
	// If using automatic Mask Size
	if (masksize < 0.5)
	{
		final_mask_size = (global.FinalViewportSize.x + global.FinalViewportSize.y) / 3 > 1900 ? 2 : 1;
	}
	pos = floor(pos/final_mask_size);
	// End HSM Added

	// HSM Removed
	// pos = floor(pos/masksize);
	vec3 mask = vec3(maskDark, maskDark, maskDark);
	vec3 one = vec3(1.0);
	float dark_compensate  = mix(max( clamp( mix (mcut, maskstr, mx),0.0, 1.0) - 0.3, 0.0) + 1.0, 1.0, mx);
	float mc = 1.0 - max(maskstr, 0.0);	
	
	// No mask
	if (shadowMask == -1.0)
	{
		mask = vec3(1.0);
	}       
	
	// Phosphor.
	else if (shadowMask == 0.0)
	{
		pos.x = fract(pos.x*0.5);
		if (pos.x < 0.5) { mask.r = 1.0; mask.g = mc; mask.b = 1.0; }
		else { mask.r = mc; mask.g = 1.0; mask.b = mc; }
	}    
   
	// Very compressed TV style shadow mask.
	else if (shadowMask == 1.0)
	{
		float line = maskLight;
		float odd  = 0.0;

		if (fract(pos.x/6.0) < 0.5)
			odd = 1.0;
		if (fract((pos.y + odd)/2.0) < 0.5)
			line = maskDark;

		pos.x = fract(pos.x/3.0);
    
		if      (pos.x < 0.333) mask.r = maskLight;
		else if (pos.x < 0.666) mask.g = maskLight;
		else                    mask.b = maskLight;
		
		mask*=line;  
	} 

	// Aperture-grille.
	else if (shadowMask == 2.0)
	{
		pos.x = fract(pos.x/3.0);

		if      (pos.x < 0.333) mask.r = maskLight;
		else if (pos.x < 0.666) mask.g = maskLight;
		else                    mask.b = maskLight;
	} 

	// Stretched VGA style shadow mask (same as prior shaders).
	else if (shadowMask == 3.0)
	{
		pos.x += pos.y*3.0;
		pos.x  = fract(pos.x/6.0);

		if      (pos.x < 0.333) mask.r = maskLight;
		else if (pos.x < 0.666) mask.g = maskLight;
		else                    mask.b = maskLight;
	}

	// VGA style shadow mask.
	else if (shadowMask == 4.0)
	{
		pos.xy = floor(pos.xy*vec2(1.0, 0.5));
		pos.x += pos.y*3.0;
		pos.x  = fract(pos.x/6.0);

		if      (pos.x < 0.333) mask.r = maskLight;
		else if (pos.x < 0.666) mask.g = maskLight;
		else                    mask.b = maskLight;
	}
	
	// Trinitron mask 5
	else if (shadowMask == 5.0)
	{
		mask = vec3(0.0);		
		pos.x = fract(pos.x/2.0);
		if  (pos.x < 0.5)
		{	mask.r  = 1.0;
			mask.b  = 1.0;
		}
		else     mask.g = 1.0;
		mask = clamp(mix( mix(one, mask, mcut), mix(one, mask, maskstr), mx), 0.0, 1.0) * dark_compensate;
	}    

	// Trinitron mask 6
	else if (shadowMask == 6.0)
	{
		mask = vec3(0.0);
		pos.x = fract(pos.x/3.0);
		if      (pos.x < 0.333) mask.r = 1.0;
		else if (pos.x < 0.666) mask.g = 1.0;
		else                    mask.b = 1.0;
		mask = clamp(mix( mix(one, mask, mcut), mix(one, mask, maskstr), mx), 0.0, 1.0) * dark_compensate;
	}
	
	// BW Trinitron mask 7
	else if (shadowMask == 7.0)
	{
		float maskTmp = clamp(mix( mix(1.0, 0.0, mcut), mix(1.0, 0.0, maskstr), mx), 0.0, 1.0) * dark_compensate;
		mask = vec3(maskTmp);
		pos.x = fract(pos.x/2.0);
		if  (pos.x < 0.5) mask = vec3(1.0);
	}    

	// 4k mask
	else 
	{
		mask = vec3(mc);
		pos.x = fract(pos.x * 0.25);
		if      (pos.x < 0.2)  mask.r  = 1.0;
		else if (pos.x < 0.4)  mask.rg = 1.0.xx;
		else if (pos.x < 0.7)  mask.gb = 1.0.xx;	
		else                   mask.b  = 1.0;	
	}     
 
	return mask;
}  

float SlotMask(vec2 pos, float m)
{
	if (slotmask == 0.0) return 1.0;
	
	// HSM Added
	float final_mask_size = slotms;
	// If using automatic Mask Size
	if (slotms < 0.5)
	{
		final_mask_size = (global.FinalViewportSize.x + global.FinalViewportSize.y) / 3 > 1900 ? 2 : 1;
	}
	pos = floor(pos/final_mask_size);
	// End HSM Added

	// HSM Removed
	// pos = floor(pos/slotms);

	float mlen = slotwidth*2.0;
	float px = fract(pos.x/mlen);
	float py = floor(fract(pos.y/(2.0*double_slot))*2.0*double_slot);
	float slot_dark = 1.0 - slotmask*(1.0 - 0.125*m);
	float slot = 1.0;
	if (py == 0.0 && px <  0.5) slot = slot_dark; else
	if (py == double_slot && px >= 0.5) slot = slot_dark;		
	
	return slot;
}   
 
// // Distortion of scanlines, and end of screen alpha (PD Lottes Curvature)
// vec2 Warp(vec2 pos)
// {
// 	pos  = pos*2.0-1.0;    
// 	pos *= vec2(1.0 + (pos.y*pos.y)*warpX, 1.0 + (pos.x*pos.x)*warpY);
// 	return pos*0.5 + 0.5;
// } 

vec2 Overscan(vec2 pos, float dx, float dy){
	pos=pos*2.0-1.0;    
	pos*=vec2(dx,dy);
	return pos*0.5+0.5;
} 


// // Borrowed from cgwg's crt-geom, under GPL

// float corner(vec2 coord)
// {
// 	coord = (coord - vec2(0.5)) * 1.0 + vec2(0.5);
// 	coord = min(coord, vec2(1.0)-coord) * vec2(1.0, OutputSize.y/OutputSize.x);
// 	vec2 cdist = vec2(max(csize/3.0, max((1.0-smoothstep(100.0,600.0,bsize))*0.01,0.002)));
// 	coord = (cdist - min(coord,cdist));
// 	float dist = sqrt(dot(coord,coord));
// 	return clamp((cdist.x-dist)*bsize,0.0, 1.0);
// }

vec3 declip(vec3 c, float b)
{
	float m = max(max(c.r,c.g),c.b);
	if (m > b) c = c*b/m;
	return c;
}

vec3 gc(vec3 c)
{
	float mc = max(max(c.r,c.g),c.b);
	float mg = pow(mc, 1.0/gamma_c);
	return c * mg/(mc + eps);  
}

vec3 plant (vec3 tar, float r)
{
	float t = max(max(tar.r,tar.g),tar.b) + 0.00001;
	return tar * r / t;
}

void main()
{
	// HSM Added
	HSM_UpdateGlobalScreenValuesFromCache(InfoCachePass, vTexCoord);

	// HSM Changed
	float TATE = USE_VERTICAL_SCANLINES;

	/* HSM Removed
	vec4 SourceSize = global.OriginalSize * vec4(prescalex, 1.0, 1.0/prescalex, 1.0);
	*/
	
	// HSM Added
	// FragColor = vec4(CROPPED_ROTATED_ORIGINAL_SIZE_WITH_CORE_RES_MULT.y / 256);
	// return;

	vec2 SourceSize = CROPPED_ROTATED_ORIGINAL_SIZE_WITH_CORE_RES_MULT * vec2(HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR, 1.0);

	float lum = COMPAT_TEXTURE(AvgLumPass, vec2(0.5,0.5)).a;
	float gamma_in = 1.0/COMPAT_TEXTURE(LinearizePass, vec2(0.25,0.25)).a;
	float intera = COMPAT_TEXTURE(LinearizePass, vec2(0.75,0.25)).a;
	bool interb  = (intera < 0.75);
	bool notate  = (TATE < 0.5);

	/*
	float SourceY = mix(SourceSize.y, SourceSize.x, TATE);
	float sy = 1.0;
	if (params.intres == 0.5) sy = SourceY/224.0; else
	if (params.intres == 1.0) sy = SourceY/240.0; else
	if (params.intres > 1.25) sy = params.intres;
	if (notate) SourceSize*=vec4(1.0, 1.0/sy, 1.0, sy); else SourceSize*=vec4(1.0/sy, 1.0, sy, 1.0);

	
	// Calculating texel coordinates
	vec2 texcoord = TEX0.xy;
	if (IOS > 0.0){
		vec2 ofactor = OutputSize.xy/SourceSize.xy;
		vec2 intfactor = (IOS < 2.5) ? floor(ofactor) : ceil(ofactor);
		vec2 diff = ofactor/intfactor;
		float scan = mix(diff.y, diff.x, TATE);
		texcoord = Overscan(texcoord, scan, scan);
		if (IOS == 1.0 || IOS == 3.0) texcoord = mix(vec2(TEX0.x, texcoord.y), vec2(texcoord.x, TEX0.y), TATE);
	}
   
	float factor  = 1.00 + (1.0-0.5*OS)*BLOOM/100.0 - lum*BLOOM/100.0;
	texcoord  = Overscan(texcoord, factor, factor);

	texcoord = Overscan(texcoord, 1.0, (SourceSize.y - overscanY)/SourceSize.y);

	vec2 pos  = Warp(texcoord);
	vec2 pos0 = Warp(TEX0.xy);
	*/

	vec2 screen_curved_coord = HSM_GetCurvedCoord(SCREEN_COORD, 1, SCREEN_ASPECT);
	vec2 pos = HSM_GetMirrorWrappedCoord(screen_curved_coord);

	bool smarte  = (smart_ei > 0.0 && notate); // smart edge interpolation on / off

	vec2 coffset = vec2(0.5, 0.5);
	
	// HSM Edited - Was SourceSize.zw
	vec2 ps = 1 / SourceSize.xy;
	vec2 OGL2Pos = pos * SourceSize.xy - coffset;
	vec2 fp = fract(OGL2Pos);
	
	vec2 dx = vec2(ps.x,0.0);
	vec2 dy = vec2(0.0, ps.y);
   
	// Reading the texels
	vec2 x2 = 2.0*dx;
	vec2 y2 = 2.0*dy;

	vec2 offx = dx;
	vec2 off2 = x2;
	vec2 offy = dy;
	float fpx = fp.x;
	if(!notate)
	{
		offx = dy;
		off2 = y2;
		offy = dx;
		fpx = fp.y;
	}
	float  f = (notate) ? fp.y : fp.x;
	
	vec2 pC4 = floor(OGL2Pos) * ps + 0.5*ps; 
	
	/* HSM Removed
	if (interb)  pC4.y = pos.y - inters * SourceSize.w;
	*/

	// HSM Added
	if (interb)  pC4.y = pos.y - inters * (1 / SourceSize.y);
	
	float zero = exp2(-h_sharp);
	float sharp1 = s_sharp * zero;
	
	// HSM Removed
	// float fdivider = min(prescalex, 2.0);
	
	// HSM Added
	float fdivider = min(HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR, 2.0);
	// End Addition

	float wl3 = (2.0 + fpx)/fdivider;
	float wl2 = (1.0 + fpx)/fdivider;
	float wl1 = (      fpx)/fdivider;
	float wr1 = (1.0 - fpx)/fdivider;
	float wr2 = (2.0 - fpx)/fdivider;
	float wr3 = (3.0 - fpx)/fdivider;

	wl3*=wl3; wl3 = exp2(-h_sharp*wl3);
	wl2*=wl2; wl2 = exp2(-h_sharp*wl2);
	wl1*=wl1; wl1 = exp2(-h_sharp*wl1);
	wr1*=wr1; wr1 = exp2(-h_sharp*wr1);
	wr2*=wr2; wr2 = exp2(-h_sharp*wr2);
	wr3*=wr3; wr3 = exp2(-h_sharp*wr3);
	
	float fp1 = 1.-fpx;

	float wnorm = max(wl1, wr1);

	float twl3 = max(wl3 - sharp1, 0.0);
	float twl2 = max(wl2 - sharp1, mix(-0.12, 0.0, 1.0-fp1*fp1)); float swl2 = max(twl2, 0.0);
	float twl1 = max(wl1 - sharp1, 0.0);
	float twr1 = max(wr1 - sharp1, 0.0);
	float twr2 = max(wr2 - sharp1, mix(-0.12, 0.0, 1.0-fpx*fpx)); float swr2 = max(twr2, 0.0);
	float twr3 = max(wr3 - sharp1, 0.0);
	
	bool sharp = (sharp1 > 0.0);

	float rwl3, rwl2, rwr2;

	float rwl1 = twl1;
	float rwr1 = twr1;
	vec3 c1, c2;
	
	if (smarte)
	{
		rwl3 = wl3; rwl2 = wl2;
		rwl1 = wl1; rwr1 = wr1;
		rwr2 = wr2;
		twl3 = 0.0; twr3 = 0.0;
		vec3 t = COMPAT_TEXTURE(AvgLumPass, pC4 - offy).xyz;
		vec3 a = COMPAT_TEXTURE(AvgLumPass, pC4       ).xyz;		
		vec3 b = COMPAT_TEXTURE(AvgLumPass, pC4 + offy).xyz;
		vec3 d = COMPAT_TEXTURE(AvgLumPass, pC4 +dy+dy).xyz;
		c1 = (h_sharp > 2.6) ? a : min(a,(t + a + b)/3.0); c1 = max(c1 - sth, 0.0);
		c2 = (h_sharp > 2.6) ? b : min(b,(a + b + d)/3.0); c2 = max(c2 - sth, 0.0);
	}

	float wts = 1.0/(swl2 + rwl1 + rwr1 + swr2);
	
	vec3 l3, l2, l1, r1, r2, r3, sl2, sl1, sr1, sr2, color1, color2, colmin, colmax;

	l3 = COMPAT_TEXTURE(LinearizePass, pC4 -off2).rgb;
	l2 = COMPAT_TEXTURE(LinearizePass, pC4 -offx).rgb;
	l1 = COMPAT_TEXTURE(LinearizePass, pC4      ).rgb;
	r1 = COMPAT_TEXTURE(LinearizePass, pC4 +offx).rgb;
	r2 = COMPAT_TEXTURE(LinearizePass, pC4 +off2).rgb;
	r3 = COMPAT_TEXTURE(LinearizePass, pC4 +offx+off2).rgb;
	
	sl2 = l2*l2*l2; sl2*=sl2;
	sl1 = l1*l1*l1; sl1*=sl1;
	sr1 = r1*r1*r1; sr1*=sr1;
	sr2 = r2*r2*r2; sr2*=sr2;

	colmin = min(min(l1,r1), min(l2,r2));
	colmax = max(max(l1,r1), max(l2,r2));
	
	if (smarte)
	{	
		float pc = min(1.0 + smart_ei*c1.y, ei_limit);
		float pl = min(1.0 + smart_ei*max(c1.y,c1.x), ei_limit);
		float pr = min(1.0 + smart_ei*max(c1.y,c1.z), ei_limit);
		twl1 = pow(rwl1, pc); twr1 = pow(rwr1, pc);
		twl2 = pow(rwl2, pl); twr2 = pow(rwr2, pr);
		float wmax = max(twl1, twr1);
		float sharp_ei = s_sharp*pow(zero, pc)/wmax;		
		twl2 = max(twl2/wmax - sharp_ei, mix(-0.15, 0.0, 1.0-fp1*fp1));
		twl1 = max(twl1/wmax - sharp_ei, 0.0);
		twr1 = max(twr1/wmax - sharp_ei, 0.0);
		twr2 = max(twr2/wmax - sharp_ei, mix(-0.15, 0.0, 1.0-fpx*fpx));
	}
	color1 = (l3*twl3 + l2*twl2 + l1*twl1 + r1*twr1 + r2*twr2 + r3*twr3)/(twl3+twl2+twl1+twr1+twr2+twr3);

	if (sharp) color1 = clamp(color1, colmin, colmax);

	
	vec3 gtmp = vec3(1.0/6.0); 
	vec3 scolor1 = color1;
	
	scolor1 = (sl2*swl2 + sl1*rwl1 + sr1*rwr1 + sr2*swr2)*wts;
	scolor1 = pow(scolor1, gtmp);	vec3 mcolor1 = scolor1;
	scolor1 = min(mix(color1, scolor1, spike),1.0);

	vec3 scolor2, mcolor2;
	
	/* HSM Removed
	if (interb) pC4.y = pos.y + inters * SourceSize.w; else
	pC4+=offy;
	*/

	// HSM Added
	if (interb) pC4.y = pos.y + inters * (1 /SourceSize.y); else
	pC4+=offy;

	l3 = COMPAT_TEXTURE(LinearizePass, pC4 -off2).rgb;
	l2 = COMPAT_TEXTURE(LinearizePass, pC4 -offx).rgb;
	l1 = COMPAT_TEXTURE(LinearizePass, pC4      ).rgb;
	r1 = COMPAT_TEXTURE(LinearizePass, pC4 +offx).rgb;
	r2 = COMPAT_TEXTURE(LinearizePass, pC4 +off2).rgb;
	r3 = COMPAT_TEXTURE(LinearizePass, pC4 +offx+off2).rgb;
	
	sl2 = l2*l2*l2; sl2*=sl2;
	sl1 = l1*l1*l1; sl1*=sl1;
	sr1 = r1*r1*r1; sr1*=sr1;
	sr2 = r2*r2*r2; sr2*=sr2;

	colmin = min(min(l1,r1), min(l2,r2));
	colmax = max(max(l1,r1), max(l2,r2));
	
	if (smarte)
	{	
		float pc = min(1.0 + smart_ei*c2.y, ei_limit);
		float pl = min(1.0 + smart_ei*max(c2.y,c2.x), ei_limit);
		float pr = min(1.0 + smart_ei*max(c2.y,c2.z), ei_limit);
		twl1 = pow(rwl1, pc); twr1 = pow(rwr1, pc);
		twl2 = pow(rwl2, pl); twr2 = pow(rwr2, pr);
		float wmax = max(twl1, twr1);
		float sharp_ei = s_sharp*pow(zero, pc)/wmax;		
		twl2 = max(twl2/wmax - sharp_ei, mix(-0.15, 0.0, 1.0-fp1*fp1));
		twl1 = max(twl1/wmax - sharp_ei, 0.0);
		twr1 = max(twr1/wmax - sharp_ei, 0.0);
		twr2 = max(twr2/wmax - sharp_ei, mix(-0.15, 0.0, 1.0-fpx*fpx));
	}	
	color2 = (l3*twl3 + l2*twl2 + l1*twl1 + r1*twr1 + r2*twr2 + r3*twr3)/(twl3+twl2+twl1+twr1+twr2+twr3);
	
	if (sharp) color2 = clamp(color2, colmin, colmax);
	
	scolor2 = color2;
	scolor2 = (sl2*swl2 + sl1*rwl1 + sr1*rwr1 + sr2*swr2)*wts;
	scolor2 = pow(scolor2, gtmp);	mcolor2 = scolor2;
	scolor2 = min(mix(color2, scolor2, spike),1.0);
	
	// calculating scanlines

	vec3 ctmp; vec3 mcolor; float w3; vec3 color;
	vec3 one = vec3(1.0);

if (!interb)
{	
	float shape1 = mix(scanline1, scanline2, f);
	float shape2 = mix(scanline1, scanline2, 1.0-f);	
	
	float wt1 = st(f);
	float wt2 = st(1.0-f);

	vec3 color00 = color1*wt1 + color2*wt2;
	vec3 scolor0 = scolor1*wt1 + scolor2*wt2;
	mcolor  = (mcolor1*wt1 + mcolor2*wt2)/(wt1+wt2);
	
	ctmp = color00/(wt1+wt2);
	vec3 sctmp = scolor0/(wt1+wt2);
	
	float wf1, wf2;
	
	vec3 cref1 = mix(sctmp, scolor1, beam_size); float creff1 = max(max(cref1.r,cref1.g),cref1.b);
	vec3 cref2 = mix(sctmp, scolor2, beam_size); float creff2 = max(max(cref2.r,cref2.g),cref2.b);

	float f1 = f; 
	float f2 = 1.0-f;
	
	if (gsl <  0.5) { wf1 = sw0(f1,creff1,shape1); wf2 = sw0(f2,creff2,shape2);} else
	if (gsl == 1.0) { wf1 = sw1(f1,creff1,shape1); wf2 = sw1(f2,creff2,shape2);} else
	if (gsl == 2.0) { wf1 = sw2(f1,creff1,shape1); wf2 = sw2(f2,creff2,shape2);}
	
	if ((wf1 + wf2) > 1.0) { float wtmp = 1.0/(wf1+wf2); wf1*=wtmp; wf2*=wtmp; }

	// Scanline darken 'edges' effect - need to uncomment it.
	
	// float ws1 = max(wf1 - scansub, 0.2*wf1*wf2); wf1 = ws1/(1.0 - wf1 + ws1);
	// float ws2 = max(wf2 - scansub, 0.2*wf2*wf1); wf2 = ws2/(1.0 - wf2 + ws2);
	
	// Scanline saturation application
	
	vec3 w1 = vec3(wf1); vec3 w2 = vec3(wf2);
	
	cref1 = color1 / (max(max(color1.r,color1.g),color1.b) + 0.00001);
	cref2 = color2 / (max(max(color2.r,color2.g),color2.b) + 0.00001);	

	w1 = mix(w1*mix(one, cref1*cref1*cref1, scans), w1, wf1);
	w2 = mix(w2*mix(one, cref2*cref2*cref2, scans), w2, wf2);
	
	vec3 cd1 = one; vec3 cd2 = one; float vm = sqrt(abs(vertmask));
	
	float v_high1 = 1.0 + 0.3*vm;
	float v_high2 = 1.0 + 0.6*vm;	
	float v_low  = 1.0 - vm;
	
	float ds1 = min(pow(2.0*f1 + 0.01, f2), 1.0);
	float ds2 = min(pow(2.0*f2 + 0.01, f1), 1.0);
	
	if (vertmask < 0.0) 
	{
		cd1 = mix(one, vec3(v_high2, v_low, v_low), ds1);
		cd2 = mix(one, vec3(v_low, v_high1, v_high1), ds2);
	}
	else
	{
		cd1 = mix(one, vec3(v_high1, v_low, v_high1), ds1);
		cd2 = mix(one, vec3(v_low, v_high2, v_low), ds2);
	}
	
	color = gc(color1)*w1*cd1 + gc(color2)*w2*cd2;
	
	color = min(color, 1.0);
	w3 = wf1+wf2;
}
	
	if (interb) 
	{
		color = gc(0.5*(color1+color2));
		mcolor = vec3(max(max(color.r,color.g), color.b));		
	}

	float mx = max(max(mcolor.r,mcolor.g),mcolor.b);
	mx = pow(mx, 1.20/gamma_in);
   
	// Apply Mask
	
	vec3 orig1 = color;
	vec3 cmask = one;
	
	vec2 maskcoord = gl_FragCoord.yx * 1.000001;
	if (notate) maskcoord = maskcoord.yx;
	
	float smask = SlotMask(maskcoord, mx);	
	cmask*= Mask(maskcoord, mx);
	
	color = pow(color, vec3(mask_gamma/gamma_in));
	color = color*cmask;
	color = min(color,1.0);
	color = color*smask;
	color = pow(color, vec3(gamma_in/mask_gamma));

	cmask = min(cmask*smask, 1.0);

	if (interb) ctmp = color;
	float colmx = pow( max( max(ctmp.r, ctmp.g), ctmp.b), 1.40/gamma_out);

	float bb = mix(brightboost, brightboost1, colmx);
	if (interb) bb = (abs(intera-0.5)<0.1) ? pow(0.80*bb, 0.65) : pow(bb, 0.70);
	color*=bb;

	vec3  Glow = COMPAT_TEXTURE(GlowPass, pos).rgb;
	vec3  Bloom = COMPAT_TEXTURE(BloomPass, pos).rgb;
	float maxb = COMPAT_TEXTURE(BloomPass, pos).a;

	/* HSM Removed
	float vig  = COMPAT_TEXTURE(PrePass, clamp(pos, 0.0+0.5*global.OriginalSize.zw, 1.0-0.5*global.OriginalSize.zw)).a;
	*/

	vec3 Bloom1 = min(Bloom*(orig1+color), max(0.5*(colmx + orig1 - color),0.0));
	color = color + bloom*Bloom1;

	color = min(color, mix(one, cmask, mclip));
	if (!interb) color = declip(color, pow(w3,0.60));

	Bloom = mix(0.5*(Bloom + Bloom*Bloom), Bloom*Bloom, colmx);	
	color = color + (1.1-0.25*colmx)*(0.75+maxb)*Bloom*(0.75 + 0.70*pow(colmx,0.33333))*mix(1.0,w3,0.5*colmx)*mix(one,cmask,0.35 + 0.4*maxb)*halation;

	Glow = mix(Glow, 0.25*color, 0.7*colmx);
	color = color + 0.5*glow*Glow;
	
	/* HSM Removed
	color = pow(color, vec3(1.0/gamma_out));
	
	FragColor = vec4(color*vig, corner(pos));
	*/

	// Prep and add output gamma
	FragColor = vec4(color, 1);
	FragColor = HSM_GetPostCrtPreppedColor(FragColor, vTexCoord, screen_curved_coord, IntroPass, false, ColoredGelImage, TubeStaticReflectionImage, BackgroundImage, BackgroundVertImage);
	// End Addition
}
