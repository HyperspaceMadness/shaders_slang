/*
   CRT - Guest - Dr. Venom - Includes changes from HyperspaceMadness to integrate the Mega Bezel
   
   Copyright (C) 2018-2020 guest(r) - guest.r@gmail.com

   Incorporates many good ideas and suggestions from Dr. Venom.
   
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
   
	Addition of hsm-mega-screen-scale by HyperspaceMadness remimcgill@hotmail.com

*/

// HSM Added
#include "../hsm-globals-and-screen-scale-params.inc"
// End Addition

layout(push_constant) uniform Push
{
	// HSM Removed
	// float TATE
	// IOS, 
	// OS, 
	// BLOOM, 

	float GDV_BRIGHT_BOOST_DARK_COLORS; 
	float GDV_BRIGHT_BOOST_BRIGHT_COLORS; 
	float GDV_SCANLINE_TYPE; 
	float GDV_SCANLINE_SHAPE_EDGES_LOW; 
	float GDV_SCANLINE_SHAPE_CENTER_HIGH; 
	float GDV_SCANLINE_DARK_BEAM_SIZE_MIN; 
	float GDV_SCANLINE_BRIGHT_BEAM_SIZE_MAX; 
	float GDV_SCANLINE_OVERGROWN_BRIGHT_BEAM;
	float GDV_SCANLINE_SPIKE_REMOVAL; 

    float GDV_HORIZONTAL_SHARPNESS; 
	float GDV_SUBTRACTIVE_SHARPNESS;

	// HSM Removed
	// csize, 
	// bsize, 
	// warpX, 
	// warpY, 

	// HSM Added
	// moved from global since global is comming from the import of mega screen scale
	float GDV_INTERLACE_MODE;
	float GDV_BLOOM_STRENGTH;
	// End Addition

	float GDV_GLOW_STRENGTH; 
	float GDV_MASK_TYPE; 
	float GDV_MASK_SIZE; 
	float GDV_PVM_LIKE_COLORS;
    float GDV_SLOTMASK_STRENGTH; 
	float GDV_SLOTMASK_WIDTH; 
	float GDV_SLOTMASK_HEIGHT; 
	float GDV_MASK_5_TO_7_CUTOFF; 
	float GDV_MASK_4_TO_6_DARK; 
	float GDV_MASK_4_TO_6_LIGHT; 
	float GDV_MASK_0_7_STRENGTH; 
	// HSM Removed
	// gamma_out,
	// interlace_res,
	float GDV_SCANLINE_1_2_SATURATION;
	float GDV_SLOTMASK_SIZE;
} params;



/* HSM Removed
layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
   vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	uint FrameCount;
	float bloom;
	float interlace_mode;	
	float scans;
	float slotms;
} global;
*/

// HSM Removed
// #pragma parameter TATE "TATE Mode" 0.0 0.0 1.0 1.0
// #define TATE         params.TATE     // Screen orientation
// #pragma parameter IOS "Smart Integer Scaling: 1.0:Y, 2.0:'X'+Y" 0.0 0.0 2.0 1.0
// #define IOS          params.IOS     // Smart Integer Scaling
// #pragma parameter OS "R. Bloom Overscan Mode" 1.0 0.0 2.0 1.0
// #define OS           params.OS     // Do overscan
// #pragma parameter BLOOM "Raster bloom %" 0.0 0.0 20.0 1.0
// #define BLOOM        params.BLOOM     // Bloom overscan percentage

// HSM Added (Moved from the bottom)

#pragma parameter GDV_GLOW_STRENGTH "[ GLOW ]  Glow Strength" 0.02 0.0 0.5 0.01
#define glow         params.GDV_GLOW_STRENGTH     // Glow Strength

// HSM Changed from default of 0 to 0.1
#pragma parameter GDV_BLOOM_STRENGTH "[ GLOW ]  Bloom Strength" 0.1 0 2 0.05
#define bloom          params.GDV_BLOOM_STRENGTH     // bloom effect

#pragma parameter GDV_BRIGHTNESS_TITLE	"_____[ BRIGHTNESS ]____________________________________________" 0 0 0 0

#pragma parameter GDV_BRIGHT_BOOST_DARK_COLORS "[ BRIGHTNESS ]  Boost Dark Colors" 1.40 0.50 4.00 0.05
#define brightboost  params.GDV_BRIGHT_BOOST_DARK_COLORS     // adjust brightness

#pragma parameter GDV_BRIGHT_BOOST_BRIGHT_COLORS "[ BRIGHTNESS ]  Boost Bright Colors" 1.15 0.50 3.00 0.05
#define brightboost1  params.GDV_BRIGHT_BOOST_BRIGHT_COLORS     // adjust brightness

#pragma parameter GDV_SCANLINE_TITLE	"_____[ SCANLINE ]______________________________________________" 0 0 0 0

#pragma parameter GDV_SCANLINE_TYPE "[ SCANLINE ]  Type" 0.0 0.0 2.0 1.0
#define gsl          params.GDV_SCANLINE_TYPE      // Alternate scanlines
// HSM Added (Moved From Bottom)
#pragma parameter GDV_SCANLINE_1_2_SATURATION "[ SCANLINE ]  Type 1 & 2 Saturation" 0.5 0.0 1.0 0.1
#define scans         	params.GDV_SCANLINE_1_2_SATURATION     // scanline saturation

#pragma parameter GDV_SCANLINE_SHAPE_CENTER_HIGH "[ SCANLINE ]  Shape Center (High)" 8.0 5.0 23.0 1.0 
#define scanline2    params.GDV_SCANLINE_SHAPE_CENTER_HIGH      // scanline param, vertical sharpness

#pragma parameter GDV_SCANLINE_SHAPE_EDGES_LOW "[ SCANLINE ]  Shape Edges (Low)" 6.0 1.0 15.0 1.0
#define scanline1    params.GDV_SCANLINE_SHAPE_EDGES_LOW      // scanline param, vertical sharpness

#pragma parameter GDV_SCANLINE_DARK_BEAM_SIZE_MIN "[ SCANLINE ]  Dark Beam Thinness (Higher = Thinner)" 1.35 0.5 2.5 0.05
#define beam_min     params.GDV_SCANLINE_DARK_BEAM_SIZE_MIN     // dark area beam min - narrow

#pragma parameter GDV_SCANLINE_BRIGHT_BEAM_SIZE_MAX "[ SCANLINE ]  Bright Beam Thickness" 1.05 0.5 2.5 0.05
#define beam_max     params.GDV_SCANLINE_BRIGHT_BEAM_SIZE_MAX     // bright area beam max - wide

#pragma parameter GDV_SCANLINE_OVERGROWN_BRIGHT_BEAM "[ SCANLINE ]  Overgrown Bright Beam (Increased Bright Beam)" 0.70 0.0 1.0 0.05
#define beam_size    params.GDV_SCANLINE_OVERGROWN_BRIGHT_BEAM     // increased max. beam size

#pragma parameter GDV_SCANLINE_SPIKE_REMOVAL "[ SCANLINE ]  Spike Removal (E.G. White pixel next to black)" 1.0 0.0 2.0 0.10
#define spike params.GDV_SCANLINE_SPIKE_REMOVAL

#pragma parameter GDV_PVM_LIKE_COLORS 		"[ SCANLINE ]  PVM Like Colors (Vertical Deconvergence) Def 0.08" 0.08 -0.3 0.3 0.02
#define vertmask     params.GDV_PVM_LIKE_COLORS     // Vertical mask

#pragma parameter GDV_SHARPNESS_TITLE	"_____[ SHARPNESS ]_____________________________________________" 0 0 0 0

#pragma parameter GDV_HORIZONTAL_SHARPNESS "[ SHARPNESS ]  Horizontal Sharpness" 5.25 1.0 15.0 0.25
#define h_sharp      params.GDV_HORIZONTAL_SHARPNESS     // pixel sharpness

#pragma parameter GDV_SUBTRACTIVE_SHARPNESS "[ SHARPNESS ]  Subtractive Sharpness (Relative)" 0.40 0.0 1.0 0.10
#define s_sharp      params.GDV_SUBTRACTIVE_SHARPNESS     // subtractive sharpness

// HSM Modified, Turned Interlace Mode Off, some parameters moved from global to params 
#pragma parameter GDV_INTERLACE_MODE "[ INTERLACE MODE AT TRIGGER RES ]  - OFF | ON | Blend | Sharp" 3 0 3 1
#define interlace_mode         params.GDV_INTERLACE_MODE     // interlace mode 

// HSM Removed
// #pragma parameter csize "Corner size" 0.0 0.0 0.07 0.01
// #define csize        params.csize     // corner size
// #pragma parameter bsize "Border smoothness" 600.0 100.0 600.0 25.0
// #define bsize        params.bsize     // border smoothness
// #pragma parameter warpX "CurvatureX (default 0.03)" 0.0 0.0 0.125 0.01
// #define warpX        params.warpX     // Curvature X
// #pragma parameter warpY "CurvatureY (default 0.04)" 0.0 0.0 0.125 0.01
// #define warpY        params.warpY     // Curvature Y

// HSM Removed (Moved to Top)
// #pragma parameter glow "Glow Strength" 0.02 0.0 0.5 0.01
// #define glow         params.glow     // Glow Strength

#pragma parameter GDV_MASK_TITLE	"_____[ MASK ]__________________________________________________" 0 0 0 0

#pragma parameter GDV_MASK_TYPE "[ MASK ]  Type - 0:CGWG, 1-4:Lottes, 5-6:Trinitron" 7 -1 7 1
#define shadowMask   params.GDV_MASK_TYPE     // Mask Style

#pragma parameter GDV_MASK_SIZE "[ MASK ]  Size - 0:Auto, 1:2K, 2:4k" 0 0 2 1
#define masksize     params.GDV_MASK_SIZE     // Mask Size

#pragma parameter GDV_MASK_4_TO_6_DARK "[ MASK ]  4-6 Strength Dark (Lottes & Trinitron)" 0.5 0.0 2.0 0.05
#define maskDark     params.GDV_MASK_4_TO_6_DARK     // Dark "Phosphor"

#pragma parameter GDV_MASK_4_TO_6_LIGHT "[ MASK ]  4-6 Strength Light (Lottes & Trinitron)" 1.5 0.0 2.0 0.05
#define maskLight    params.GDV_MASK_4_TO_6_LIGHT     // Light "Phosphor"

#pragma parameter GDV_MASK_5_TO_7_CUTOFF "[ MASK ]  5-7 Cutoff (Trinitron)" 0.25 0.0 0.5 0.05
#define mcut         params.GDV_MASK_5_TO_7_CUTOFF     // Mask 5-7 cutoff

#pragma parameter GDV_MASK_0_7_STRENGTH "[ MASK ]  0 & 7 Strength (CGWG)" 0.3 0.0 1.0 0.05
#define CGWG         params.GDV_MASK_0_7_STRENGTH     // CGWG Mask Strength

// Slotmask
#pragma parameter GDV_SLOTMASK_TITLE	"_____[ SLOTMASK ]______________________________________________" 0 0 0 0

#pragma parameter GDV_SLOTMASK_STRENGTH "[ SLOTMASK ]  Strength - Def 0" 0 0.0 1.0 0.05
#define slotmask     params.GDV_SLOTMASK_STRENGTH     // Slot Mask ON/OFF

// HSM Modified, parameters moved from global to params 
#pragma parameter GDV_SLOTMASK_SIZE "[ SLOTMASK ]  Size - 0:Auto, 1:2K, 2:4k" 0 0 2 1
#define slotms  	params.GDV_SLOTMASK_SIZE     // Slot Mask Size

#pragma parameter GDV_SLOTMASK_WIDTH "[ SLOTMASK ]  Width" 2.0 1.0 6.0 0.5
#define slotwidth    params.GDV_SLOTMASK_WIDTH     // Slot Mask Width

#pragma parameter GDV_SLOTMASK_HEIGHT "[ SLOTMASK ]  Height: 2x1 or 4x1" 1.0 1.0 2.0 1.0
#define double_slot  params.GDV_SLOTMASK_HEIGHT     // Slot Mask Height


// HSM Removed
// #pragma parameter gamma_out "Gamma out" 2.4 1.0 3.5 0.05
// #define gamma_out    params.gamma_out     // output gamma
// HSM Added
#define gamma_out 2.4

// HSM Removed
// #pragma parameter interlace_res "Interlace Trigger Resolution :" 400.0 0.0 800.0 25.0
// #define interlace_res         params.interlace_res

// HSM Added
#define interlace_res H_SCANLINE_INTERLACE_TRIGGER_RES

// HSM Removed (Moved it to the top)
// #pragma parameter bloom "Bloom Strength" 0.0 0.0 2.0 0.1
// #define bloom          params.bloom     // bloom effect
// #pragma parameter scans "Scanline 1&2 Saturation" 0.5 0.0 1.0 0.1
// #define scans         	params.scans     // scanline saturation

#define COMPAT_TEXTURE(c,d) HSS_GetCroppedTexSample(c,d)
// #define TEX0 vTexCoord
// #define InputSize SourceSize
// #define TextureSize SourceSize

// HSM Removed
// #define SourceSize global.SourceSize
// HSM Added
#define SourceSize CROPPED_ORIGINAL_SIZE
// #define SourceSize HSS_GetCroppedRotatedOriginalSizeWithCoreResMult()
// End Addition

#define OutputSize global.OutputSize
#define gl_FragCoord (vTexCoord * OutputSize.xy)

// Calculate values for fragment stage
vec2 CROPPED_ORIGINAL_SIZE = HSS_GetCroppedRotatedOriginalSizeWithCoreResMult();
float SCREEN_ASPECT = HSS_GetScreenAspect();
vec2 SCREEN_SCALE = HSS_GetScreenScale(SCREEN_ASPECT);
float USE_VERTICAL_SCANLINES = HSS_GetUseVerticalScanlines(SCREEN_ASPECT);


#pragma stage vertex

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 0) out vec2 vTexCoord;
layout(location = 4) out vec2 SCREEN_COORD;

void main()
{
	gl_Position = global.MVP * Position;
	vTexCoord = TexCoord * 1.00001;
	SCREEN_COORD = HSS_GetScreenVTexCoord(vTexCoord, SCREEN_SCALE);
}

#pragma stage fragment

layout(location = 0) in vec2 vTexCoord;
layout(location = 4) in vec2 SCREEN_COORD;

layout(location = 0) out vec4 FragColor;

layout(set = 0, binding = 2) uniform sampler2D Source;
layout(set = 0, binding = 3) uniform sampler2D LinearizePass;

// HSM Removed
// layout(set = 0, binding = 4) uniform sampler2D AvgLumPass;

layout(set = 0, binding = 4) uniform sampler2D GlowPass;

// HSM Added
layout(set = 0, binding = 5) uniform sampler2D ColoredGelImage;
layout(set = 0, binding = 6) uniform sampler2D TubeHighlightImage;

#define Texture Source

// HSM Removed
// #define PassPrev5Texture AvgLumPass

#define PassPrev4Texture LinearizePass
#define PassPrev2Texture GlowPass

#define eps 1e-10 

float st(float x)
{
	return exp2(-10.0*x*x);
} 
   
vec3 sw0(vec3 x, vec3 color, float scanline)
{
	vec3 tmp = mix(vec3(beam_min),vec3(beam_max), color);
	vec3 ex = x*tmp;
	return exp2(-scanline*ex*ex);
} 

vec3 sw1(vec3 x, vec3 color, float scanline)
{	
	float mx = max(max(color.r, color.g),color.b);
	x = mix (x, beam_min*x, max(x-0.4*mx,0.0));
	vec3 tmp = mix(vec3(1.2*beam_min),vec3(beam_max), color);
	vec3 ex = x*tmp;
	float br = clamp(0.8*beam_min - 1.0, 0.2, 0.45);
	vec3 res = exp2(-scanline*ex*ex)/(1.0-br+br*mx);
	mx = max(max(res.r,res.g),res.b);
	float scans1 = scans; if (abs(vertmask) > 0.01) scans1=1.0;
	return mix(vec3(mx), res, scans1);		
}    

vec3 sw2(vec3 x, vec3 color, float scanline)
{
	float mx = max(max(color.r, color.g),color.b);
	vec3 tmp = mix(vec3(2.5*beam_min),vec3(beam_max), color);
	tmp = mix(vec3(beam_max), tmp, pow(abs(x), color+0.3));
	vec3 ex = x*tmp;
	vec3 res = exp2(-scanline*ex*ex)/(0.6 + 0.4*mx);
	mx = max(max(res.r,res.g),res.b);
	float scans1 = scans; if (abs(vertmask) > 0.01) scans1=0.85;	
	return mix(vec3(mx), res, scans1);	
} 

// Shadow mask (1-4 from PD CRT Lottes shader).
vec3 Mask(vec2 pos, vec3 c)
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
	
	// No mask
	if (shadowMask == -1.0)
	{
		mask = vec3(1.0);
	}       
	
	// Phosphor.
	else if (shadowMask == 0.0)
	{
		pos.x = fract(pos.x*0.5);
		float mc = 1.0 - CGWG;
		if (pos.x < 0.5) { mask.r = 1.1; mask.g = mc; mask.b = 1.1; }
		else { mask.r = mc; mask.g = 1.1; mask.b = mc; }
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
	
	// Alternate mask 5
	else if (shadowMask == 5.0)
	{
		float mx = max(max(c.r,c.g),c.b);
		vec3 maskTmp = vec3( min( 1.25*max(mx-mcut,0.0)/(1.0-mcut) ,maskDark + 0.2*(1.0-maskDark)*mx));
		float adj = 0.80*maskLight - 0.5*(0.80*maskLight - 1.0)*mx + 0.75*(1.0-mx);	
		mask = maskTmp;
		pos.x = fract(pos.x/2.0);
		if  (pos.x < 0.5)
		{	mask.r  = adj;
			mask.b  = adj;
		}
		else     mask.g = adj;
	}    

	// Alternate mask 6
	else if (shadowMask == 6.0)
	{
		float mx = max(max(c.r,c.g),c.b);
		vec3 maskTmp = vec3( min( 1.33*max(mx-mcut,0.0)/(1.0-mcut) ,maskDark + 0.225*(1.0-maskDark)*mx));
		float adj = 0.80*maskLight - 0.5*(0.80*maskLight - 1.0)*mx + 0.75*(1.0-mx);
		mask = maskTmp;
		pos.x = fract(pos.x/3.0);
		if      (pos.x < 0.333) mask.r = adj;
		else if (pos.x < 0.666) mask.g = adj;
		else                    mask.b = adj; 
	}
	
	// Alternate mask 7
	else if (shadowMask == 7.0)
	{
		float mc = 1.0 - CGWG;
		float mx = max(max(c.r,c.g),c.b);
		float maskTmp = min(1.6*max(mx-mcut,0.0)/(1.0-mcut) , mc);
		mask = vec3(maskTmp);
		pos.x = fract(pos.x/2.0);
		if  (pos.x < 0.5) mask = vec3(1.0 + 0.6*(1.0-mx));
	}    
	
	return mask;
} 

float SlotMask(vec2 pos, vec3 c)
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

	float mx = pow(max(max(c.r,c.g),c.b),1.33);
	float mlen = slotwidth*2.0;
	float px = fract(pos.x/mlen);
	float py = floor(fract(pos.y/(2.0*double_slot))*2.0*double_slot);
	float slot_dark = mix(1.0-slotmask, 1.0-0.80*slotmask, mx);
	float slot = 1.0 + 0.7*slotmask*(1.0-mx);
	if (py == 0.0 && px <  0.5) slot = slot_dark; else
	if (py == double_slot && px >= 0.5) slot = slot_dark;		
	
	return slot;
}  

/* HSM Removed
// Distortion of scanlines, and end of screen alpha (PD Lottes Curvature)
vec2 Warp(vec2 pos)
{
	pos  = pos*2.0-1.0;    
	pos *= vec2(1.0 + (pos.y*pos.y)*warpX, 1.0 + (pos.x*pos.x)*warpY);
	return pos*0.5 + 0.5;
} 
*/

vec2 Overscan(vec2 pos, float dx, float dy){
	pos=pos*2.0-1.0;    
	pos*=vec2(dx,dy);
	return pos*0.5+0.5;
} 


// Borrowed from cgwg's crt-geom, under GPL
/* HSM Removed
float corner(vec2 coord)
{
	coord *= SourceSize.xy / InputSize.xy;
	coord = (coord - vec2(0.5)) * 1.0 + vec2(0.5);
	coord = min(coord, vec2(1.0)-coord) * vec2(1.0, OutputSize.y/OutputSize.x);
	vec2 cdist = vec2(max(csize, max((1.0-smoothstep(100.0,600.0,bsize))*0.01,0.002)));
	coord = (cdist - min(coord,cdist));
	float dist = sqrt(dot(coord,coord));
	return clamp((cdist.x-dist)*bsize,0.0, 1.0);
}
*/

vec3 declip(vec3 c, float b)
{
	float m = max(max(c.r,c.g),c.b);
	if (m > b) c = c*b/m;
	return c;
}

void main()
{
	/* HSM Removed
	float lum = COMPAT_TEXTURE(PassPrev5Texture, vec2(0.1,0.1)).a;

	// Calculating texel coordinates

		vec2 texcoord = TEX0.xy;
	if (IOS > 0.0){
		vec2 ofactor = OutputSize.xy/InputSize.xy;
		vec2 intfactor = round(ofactor);
		vec2 diff = ofactor/intfactor;
		float scan = mix(diff.y, diff.x, TATE);
		texcoord = Overscan(texcoord*(SourceSize.xy/InputSize.xy), scan, scan)*(InputSize.xy/SourceSize.xy);
		if (IOS == 1.0) texcoord = mix(vec2(TEX0.x, texcoord.y), vec2(texcoord.x, TEX0.y), TATE);
	}

	float factor  = 1.00 + (1.0-0.5*OS)*BLOOM/100.0 - lum*BLOOM/100.0;
	texcoord  = Overscan(texcoord*(SourceSize.xy/InputSize.xy), factor, factor)*(InputSize.xy/SourceSize.xy);
	 vec2 pos  = Warp(texcoord*(TextureSize.xy/InputSize.xy))*(InputSize.xy/TextureSize.xy);
	 vec2 pos0 = Warp(TEX0.xy*(TextureSize.xy/InputSize.xy))*(InputSize.xy/TextureSize.xy);
	*/
	
	// HSM Removed
	float TATE = USE_VERTICAL_SCANLINES;

	vec2 screen_curved_coord = HSS_GetCurvedCoord(SCREEN_COORD, 1, SCREEN_ASPECT);
	vec2 pos = HSS_GetMirrorWrappedCoord(screen_curved_coord);

	vec2 coffset = vec2(0.5, 0.5);
	bool use_interlace = (interlace_mode > 0.5 && interlace_mode < 2.5 && interlace_res <= mix(SourceSize.y, SourceSize.x, TATE));
	bool screen_is_horizontal  = (TATE < 0.5);
	
	if (use_interlace) coffset = (screen_is_horizontal) ? vec2(0.5, 0.0) : vec2(0.0, 0.5);
	
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
	if(!screen_is_horizontal)
	{
		offx = dy;
		off2 = y2;
		offy = dx;
		fpx = fp.y;
	}
	float  f = (screen_is_horizontal) ? fp.y : fp.x;
	
	vec2 pC4 = floor(OGL2Pos) * ps + 0.5*ps;
	
	float zero = exp2(-h_sharp);   
	float sharp1 = s_sharp * zero;
	
	float wl3 = 2.0 + fpx;
	float wl2 = 1.0 + fpx;
	float wl1 =       fpx;
	float wr1 = 1.0 - fpx;
	float wr2 = 2.0 - fpx;
	float wr3 = 3.0 - fpx;

	wl3*=wl3; wl3 = exp2(-h_sharp*wl3);	
	wl2*=wl2; wl2 = exp2(-h_sharp*wl2);
	wl1*=wl1; wl1 = exp2(-h_sharp*wl1);
	wr1*=wr1; wr1 = exp2(-h_sharp*wr1);
	wr2*=wr2; wr2 = exp2(-h_sharp*wr2);
	wr3*=wr3; wr3 = exp2(-h_sharp*wr3);
	
	float fp1 = 1.-fpx;

	float twl3 = max(wl3 - sharp1, 0.0);
	float twl2 = max(wl2 - sharp1, mix(0.0,mix(-0.18, -0.01, fpx),float(s_sharp > 0.05)));
	float twl1 = max(wl1 - sharp1, 0.0);
	float twr1 = max(wr1 - sharp1, 0.0);	
	float twr2 = max(wr2 - sharp1, mix(0.0,mix(-0.18, -0.01, fp1),float(s_sharp > 0.05)));
	float twr3 = max(wr3 - sharp1, 0.0);
	
	float wtt = 1.0/(twl3+twl2+twl1+twr1+twr2+twr3);
	float wt  = 1.0/(wl2+wl1+wr1+wr2);
	bool sharp = (s_sharp > 0.05);
	
	// HSM Comment - Do initial sample with offsets
	vec3 l3 = COMPAT_TEXTURE(PassPrev4Texture, pC4 -off2).xyz;
	vec3 l2 = COMPAT_TEXTURE(PassPrev4Texture, pC4 -offx).xyz;
	vec3 l1 = COMPAT_TEXTURE(PassPrev4Texture, pC4      ).xyz;
	vec3 r1 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +offx).xyz;
	vec3 r2 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +off2).xyz;
	vec3 r3 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +offx+off2).xyz;
	
	vec3 sl2 = COMPAT_TEXTURE(Texture, pC4 -offx).xyz;
	vec3 sl1 = COMPAT_TEXTURE(Texture, pC4      ).xyz;
	vec3 sr1 = COMPAT_TEXTURE(Texture, pC4 +offx).xyz;
	vec3 sr2 = COMPAT_TEXTURE(Texture, pC4 +off2).xyz;
	
	vec3 color1 = (l3*twl3 + l2*twl2 + l1*twl1 + r1*twr1 + r2*twr2 + r3*twr3)*wtt;
	
	vec3 colmin = min(min(l1,r1), min(l2,r2));
	vec3 colmax = max(max(l1,r1), max(l2,r2));
	
	if (sharp) color1 = clamp(color1, colmin, colmax);
	
	vec3 gtmp = vec3(gamma_out*0.1); 
	vec3 scolor1 = color1;
	
	scolor1 = (sl2*wl2 + sl1*wl1 + sr1*wr1 + sr2*wr2)*wt;
	scolor1 = pow(scolor1, gtmp);	vec3 mcolor1 = scolor1;
	scolor1 = mix(color1, scolor1, spike);
	
	// HSM Comment - Add an additional Y offset and sample again
	pC4+=offy;
	
	l3 = COMPAT_TEXTURE(PassPrev4Texture, pC4 -off2).xyz;
	l2 = COMPAT_TEXTURE(PassPrev4Texture, pC4 -offx).xyz;
	l1 = COMPAT_TEXTURE(PassPrev4Texture, pC4      ).xyz;
	r1 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +offx).xyz;
	r2 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +off2).xyz;
	r3 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +offx+off2).xyz;
	
	sl2 = COMPAT_TEXTURE(Texture, pC4 -offx).xyz;
	sl1 = COMPAT_TEXTURE(Texture, pC4      ).xyz;
	sr1 = COMPAT_TEXTURE(Texture, pC4 +offx).xyz;
	sr2 = COMPAT_TEXTURE(Texture, pC4 +off2).xyz;
	
	vec3 color2 = (l3*twl3 + l2*twl2 + l1*twl1 + r1*twr1 + r2*twr2 + r3*twr3)*wtt;
	
	colmin = min(min(l1,r1), min(l2,r2));
	colmax = max(max(l1,r1), max(l2,r2));
	
	if (sharp) color2 = clamp(color2, colmin, colmax);

	vec3 scolor2 = color2;
	
	scolor2 = (sl2*wl2 + sl1*wl1 + sr1*wr1 + sr2*wr2)*wt;
	scolor2 = pow(scolor2, gtmp);	vec3 mcolor2 = scolor2;
	scolor2 = mix(color2, scolor2, spike);
	
	vec3 color0 = color1;

	if (use_interlace)
	{
		// HSM Comment - Add a negative Y offset and sample again
		pC4-= 2.*offy;
	
		l3 = COMPAT_TEXTURE(PassPrev4Texture, pC4 -off2).xyz;
		l2 = COMPAT_TEXTURE(PassPrev4Texture, pC4 -offx).xyz;
		l1 = COMPAT_TEXTURE(PassPrev4Texture, pC4      ).xyz;
		r1 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +offx).xyz;
		r2 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +off2).xyz;
		r3 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +offx+off2).xyz;
	
		color0 = (l3*twl3 + l2*twl2 + l1*twl1 + r1*twr1 + r2*twr2 + r3*twr3)*wtt;
	
		colmin = min(min(l1,r1), min(l2,r2));
		colmax = max(max(l1,r1), max(l2,r2));
	
		if (sharp) color0 = clamp(color0, colmin, colmax);
	}
	
	// calculating scanlines
	
	float shape1 = mix(scanline1, scanline2, f);
	float shape2 = mix(scanline1, scanline2, 1.0-f);	
	
	float wt1 = st(f);
	float wt2 = st(1.0-f);

	vec3 color00 = color1*wt1 + color2*wt2;
	vec3 scolor0 = scolor1*wt1 + scolor2*wt2;
	vec3 mcolor  = (mcolor1*wt1 + mcolor2*wt2)/(wt1+wt2);
	
	vec3 ctmp = color00/(wt1+wt2);
	vec3 sctmp = scolor0/(wt1+wt2);
	
	vec3 tmp = pow(ctmp, vec3(1.0/gamma_out));
	mcolor = clamp(mix(ctmp, mcolor, 1.5),0.0,1.0);
	mcolor = pow(mcolor, vec3(1.4/gamma_out));
	
	vec3 w1,w2 = vec3(0.0);
	
	vec3 cref1 = mix(sctmp, scolor1, beam_size);
	vec3 cref2 = mix(sctmp, scolor2, beam_size);
	
	vec3 shift = vec3(-vertmask, vertmask, -vertmask); if (vertmask < 0.0) shift = shift.grr;

	vec3 f1 = vec3(f); 
	vec3 f2 = vec3(1.0-f);
	
	f1 = max(f1 + shift*0.5*(1.0+f), 0.75*f); 
	f2 = max(f2 - shift*0.5*(2.0-f), 0.75*(1.0-f));
	
	if (gsl == 0.0) { w1 = sw0(f1,cref1,shape1); w2 = sw0(f2,cref2,shape2);} else
	if (gsl == 1.0) { w1 = sw1(f1,cref1,shape1); w2 = sw1(f2,cref2,shape2);} else
	if (gsl == 2.0) { w1 = sw2(f1,cref1,shape1); w2 = sw2(f2,cref2,shape2);}
	
	vec3 color = color1*w1 + color2*w2;
	color = min(color, 1.0);
	
	if (interlace_mode > 0.5 && interlace_res <= mix(SourceSize.y, SourceSize.x, TATE)) 
	{
		if (interlace_mode < 2.5)
		{
			float line_no  = floor(mod(mix(  OGL2Pos.y,  OGL2Pos.x, TATE),2.0));		
			float frame_no = floor(mod(float(global.FrameCount),2.0));
			float ii = (interlace_mode > 1.5) ? 0.5 : abs(line_no-frame_no);
			
			vec3 icolor1 = mix(color1, color0, ii);
			vec3 icolor2 = mix(color1, color2, ii);
			
			color = mix(icolor1, icolor2, f);
			mcolor = sqrt(color); 			
		} 
		else color = mix(color1, color2, f);
	}
	
	ctmp = 0.5*(ctmp+tmp);
	color*=mix(brightboost, brightboost1, max(max(ctmp.r,ctmp.g),ctmp.b));
   
	// Apply Mask
	
	vec3 orig1 = color; float pixbr = max(max(ctmp.r,ctmp.g),ctmp.b); vec3 orig = ctmp; w1 = w1+w2; float w3 = max(max(w1.r,w1.g),w1.b); 
	vec3 cmask = vec3(1.0); vec3 cmask1 = cmask; vec3 one = vec3(1.0);
	
	cmask*= (screen_is_horizontal) ? Mask(gl_FragCoord.xy * 1.000001,mcolor) :
		Mask(gl_FragCoord.yx * 1.000001,mcolor);
	
	color = color*cmask;
	
	color = min(color,1.0);
	
	cmask1 *= (screen_is_horizontal) ? SlotMask(gl_FragCoord.xy * 1.000001,tmp) :
		SlotMask(gl_FragCoord.yx * 1.000001,tmp);		
	
	color = color*cmask1; cmask = cmask*cmask1; cmask = min(cmask, 1.0);
	
	vec3 Bloom = COMPAT_TEXTURE(PassPrev2Texture, pos).xyz;
   
	vec3 Bloom1 = 2.0*Bloom*Bloom;
	Bloom1 = min(Bloom1, 0.75);
	float bmax = max(max(Bloom1.r,Bloom1.g),Bloom1.b);
	float pmax = 0.80;
	Bloom1 = min(Bloom1, pmax*bmax)/pmax;
	
	Bloom1 = mix(min( Bloom1, color), Bloom1, 0.5*(orig1+color));
	
	Bloom1 = bloom*Bloom1;
	
	color = color + Bloom1;
	
	color = min(color, 1.0);
	if (interlace_mode < 0.5 || interlace_res > mix(SourceSize.y, SourceSize.x, TATE)) color = declip(color, pow(w3,0.6));	
	color = min(color, mix(cmask,one,0.6));

	color = color + glow*Bloom;
		
	
	/* HSM Removed
	color = pow(color, vec3(1.0/gamma_out));
	
	FragColor = vec4(color*corner(pos0), 1.0);
	*/

	// HSM Added

	// Add Prep after the CRT image is complete, e.g. Vignette
	FragColor = vec4(color, 1);
	
	// Prep and add output gamma
	FragColor = HSS_GetPostCrtPreppedColor(FragColor, screen_curved_coord, SCREEN_COORD, SCREEN_ASPECT, SCREEN_SCALE, ColoredGelImage, TubeHighlightImage);
	// End Addition
}

// HSM Renamed Params
// interm -> interlace_mode
// inter -> interlace_res
// notate -> screen_is_horizontal
// interb -> use_interlace