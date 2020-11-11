#version 450

/*
   CRT - Guest - Dr. Venom
   
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
   
*/

layout(push_constant) uniform Push
{
	float TATE, IOS, OS, BLOOM, brightboost, brightboost1, gsl, scanline1, scanline2, beam_min, beam_max, beam_size,
      h_sharp, s_sharp, csize, bsize, warpX, warpY, glow, shadowMask, masksize, vertmask,
      slotmask, slotwidth, double_slot, mcut, maskDark, maskLight, CGWG, gamma_out, spike, inter;
} params;

layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
	vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	uint FrameCount;
	float bloom;
	float interm;
	float scans;
	float slotms;
	float decon;
} global;

#pragma parameter glow "Glow Strength" 0.06 0.0 1.0 0.01
#define glow         params.glow     // Glow Strength
#pragma parameter bloom "Bloom Strength" 0.0 0.0 2.0 0.1
#define bloom         global.bloom     // bloom effect
#pragma parameter TATE "TATE Mode" 0.0 0.0 1.0 1.0
#define TATE         params.TATE     // Screen orientation
#pragma parameter IOS "Smart Integer Scaling: 1.0:Y, 2.0:'X'+Y" 0.0 0.0 2.0 1.0
#define IOS          params.IOS     // Smart Integer Scaling
#pragma parameter OS "R. Bloom Overscan Mode" 1.0 0.0 2.0 1.0
#define OS           params.OS     // Do overscan
#pragma parameter BLOOM "Raster bloom %" 0.0 0.0 20.0 1.0
#define BLOOM        params.BLOOM     // Bloom overscan percentage
#pragma parameter brightboost "Bright Boost Dark Pixels" 1.30 0.50 4.00 0.05
#define brightboost  params.brightboost     // adjust brightness
#pragma parameter brightboost1 "Bright Boost Bright Pixels" 1.15 0.50 3.00 0.05
#define brightboost1  params.brightboost1     // adjust brightness
#pragma parameter gsl "Scanline Type" 0.0 0.0 2.0 1.0
#define gsl          params.gsl      // Alternate scanlines
#pragma parameter scanline1 "Scanline beam shape low" 6.0 1.0 20.0 0.5
#define scanline1    params.scanline1      // scanline param, vertical sharpness
#pragma parameter scanline2 "Scanline beam shape high" 8.0 3.0 40.0 1.0 
#define scanline2    params.scanline2      // scanline param, vertical sharpness
#pragma parameter beam_min "Scanline shape dark pixels" 1.30 0.5 2.5 0.05
#define beam_min     params.beam_min     // dark area beam min - narrow
#pragma parameter beam_max "Scanline shape bright pixels" 1.05 0.5 2.5 0.05
#define beam_max     params.beam_max     // bright area beam max - wide
#pragma parameter beam_size "Increased bright scanline beam" 0.60 0.0 1.0 0.05
#define beam_size    params.beam_size     // increased max. beam size
#pragma parameter decon "Horizontal Color Deconvergence" 0.0 -1.0 1.0 0.1
#define decon        global.decon     // Horizontal deconvergence colors
#pragma parameter vertmask "Scanline Color Deconvergence" 0.0 -1.0 1.0 0.1
#define vertmask     params.vertmask     // Scanline deconvergence colors
#pragma parameter scans "Scanline 1&2 Saturation" 0.7 0.0 1.0 0.05
#define scans        global.scans     // scanline saturation
#pragma parameter spike "Scanline Spike Removal" 1.0 0.0 2.0 0.10
#define spike params.spike
#pragma parameter h_sharp "Horizontal sharpness" 5.20 0.20 15.0 0.20
#define h_sharp      params.h_sharp     // pixel sharpness
#pragma parameter s_sharp "Substractive sharpness (1.0 recommended for 'cubic effect')" 0.50 0.0 1.9 0.10
#define s_sharp      params.s_sharp     // substractive sharpness
#pragma parameter csize "Corner size" 0.0 0.0 0.07 0.01
#define csize        params.csize     // corner size
#pragma parameter bsize "Border smoothness" 600.0 100.0 600.0 25.0
#define bsize        params.bsize     // border smoothness
#pragma parameter warpX "CurvatureX (default 0.03)" 0.0 0.0 0.125 0.01
#define warpX        params.warpX     // Curvature X
#pragma parameter warpY "CurvatureY (default 0.04)" 0.0 0.0 0.125 0.01
#define warpY        params.warpY     // Curvature Y
#pragma parameter shadowMask "CRT Mask: 0:CGWG, 1-4:Lottes, 5-6:'Trinitron'" 0.0 -1.0 7.0 1.0
#define shadowMask   params.shadowMask     // Mask Style
#pragma parameter masksize "CRT Mask Size (2.0 is nice in 4k)" 1.0 1.0 2.0 1.0
#define masksize     params.masksize     // Mask Size
#pragma parameter maskDark "Lottes maskDark" 0.5 0.0 2.0 0.05
#define maskDark     params.maskDark     // Dark "Phosphor"
#pragma parameter maskLight "Lottes maskLight" 1.5 0.0 2.0 0.05
#define maskLight    params.maskLight     // Light "Phosphor"
#pragma parameter CGWG "Mask 0,5,6,7 Mask Str." 0.3 -0.5 1.0 0.05
#define CGWG         params.CGWG     // CGWG Mask Strength
#pragma parameter mcut "Mask 5-7 Low Strength" 1.20 0.0 2.0 0.05
#define mcut         params.mcut     // Mask 5-7 cutoff
#pragma parameter slotmask "Slot Mask Strength" 0.0 0.0 1.0 0.05
#define slotmask     params.slotmask     // Slot Mask ON/OFF
#pragma parameter slotwidth "Slot Mask Width" 2.0 1.0 6.0 0.5
#define slotwidth    params.slotwidth     // Slot Mask Width
#pragma parameter double_slot "Slot Mask Height: 2x1 or 4x1" 1.0 1.0 2.0 1.0
#define double_slot  params.double_slot     // Slot Mask Height
#pragma parameter slotms "Slot Mask Size" 1.0 1.0 2.0 1.0
#define slotms  global.slotms     // Slot Mask Size
#pragma parameter inter "Interlace Trigger Resolution :" 400.0 0.0 800.0 25.0
#define inter         params.inter     // interlace resolution
#pragma parameter interm "Interlace Mode (0.0 = OFF):" 1.0 0.0 3.0 1.0
#define interm         global.interm     // interlace mode 
#pragma parameter gamma_out "Gamma out" 2.4 1.0 3.5 0.05
#define gamma_out    params.gamma_out     // output gamma


#define COMPAT_TEXTURE(c,d) texture(c,d)
#define TEX0 vTexCoord

#define SourceSize global.OriginalSize
#define OutputSize global.OutputSize
#define gl_FragCoord (vTexCoord * OutputSize.xy)

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord * 1.00001;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D ScanPass;
layout(set = 0, binding = 3) uniform sampler2D LinearizePass;
layout(set = 0, binding = 4) uniform sampler2D AvgLumPass;
layout(set = 0, binding = 5) uniform sampler2D GlowPass;

#define Texture ScanPass
#define PassPrev5Texture AvgLumPass
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
	return mix(vec3(mx), res, scans);		
}    

vec3 sw2(vec3 x, vec3 color, float scanline)
{
	float mx = max(max(color.r, color.g),color.b);
	vec3 tmp = mix(vec3(2.5*beam_min),vec3(beam_max), color);
	tmp = mix(vec3(beam_max), tmp, pow(abs(x), color+0.3));
	vec3 ex = x*tmp;
	vec3 res = exp2(-scanline*ex*ex)/(0.6 + 0.4*mx);
	mx = max(max(res.r,res.g),res.b);
	return mix(vec3(mx), res, scans);	
} 

// Shadow mask (1-4 from PD CRT Lottes shader).

vec3 Mask(vec2 pos, vec3 c)
{
	pos = floor(pos/masksize);
	vec3 mask = vec3(maskDark, maskDark, maskDark);
	vec3 one = vec3(1.0);
	float mx = max(max(c.r,c.g),c.b);
	float dark_compensate = max( clamp( mix (mcut, CGWG, mx),0.0, 1.0) - 0.4, 0.0) + 1.0;
	
	// No mask
	if (shadowMask == -1.0)
	{
		mask = vec3(1.0);
	}       
	
	// Phosphor.
	else if (shadowMask == 0.0)
	{
		float mc = 1.0 - max(CGWG, 0.0);
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
		mask = clamp(mix( mix(one, mask, mcut), mix(one, mask, CGWG), mx), 0.0, 1.0) * dark_compensate;
	}    

	// Trinitron mask 6
	else if (shadowMask == 6.0)
	{
		mask = vec3(0.0);
		pos.x = fract(pos.x/3.0);
		if      (pos.x < 0.333) mask.r = 1.0;
		else if (pos.x < 0.666) mask.g = 1.0;
		else                    mask.b = 1.0;
		mask = clamp(mix( mix(one, mask, mcut), mix(one, mask, CGWG), mx), 0.0, 1.0) * dark_compensate;
	}
	
	// BW Trinitron mask 7
	else if (shadowMask == 7.0)
	{
		float maskTmp = clamp(mix( mix(1.0, 0.0, mcut), mix(1.0, 0.0, CGWG), mx), 0.0, 1.0);
		mask = vec3(maskTmp);
		pos.x = fract(pos.x/2.0);
		if  (pos.x < 0.5) mask = vec3(1.0);
	}    
	
	return mask * dark_compensate;
} 

float SlotMask(vec2 pos, vec3 c)
{
	if (slotmask == 0.0) return 1.0;
	
	pos = floor(pos/slotms);
	float mx = pow(max(max(c.r,c.g),c.b),1.33);
	float mlen = slotwidth*2.0;
	float px = fract(pos.x/mlen);
	float py = floor(fract(pos.y/(2.0*double_slot))*2.0*double_slot);
	float slot_dark = 1.0 - slotmask;
	float slot = 1.0;
	if (py == 0.0 && px <  0.5) slot = slot_dark; else
	if (py == double_slot && px >= 0.5) slot = slot_dark;		
	
	return slot;
}   
 
// Distortion of scanlines, and end of screen alpha (PD Lottes Curvature)
vec2 Warp(vec2 pos)
{
	pos  = pos*2.0-1.0;    
	pos *= vec2(1.0 + (pos.y*pos.y)*warpX, 1.0 + (pos.x*pos.x)*warpY);
	return pos*0.5 + 0.5;
} 

vec2 Overscan(vec2 pos, float dx, float dy){
	pos=pos*2.0-1.0;    
	pos*=vec2(dx,dy);
	return pos*0.5+0.5;
} 


// Borrowed from cgwg's crt-geom, under GPL

float corner(vec2 coord)
{
	coord = (coord - vec2(0.5)) * 1.0 + vec2(0.5);
	coord = min(coord, vec2(1.0)-coord) * vec2(1.0, OutputSize.y/OutputSize.x);
	vec2 cdist = vec2(max(csize, max((1.0-smoothstep(100.0,600.0,bsize))*0.01,0.002)));
	coord = (cdist - min(coord,cdist));
	float dist = sqrt(dot(coord,coord));
	return clamp((cdist.x-dist)*bsize,0.0, 1.0);
}

vec3 declip(vec3 c, float b)
{
	float m = max(max(c.r,c.g),c.b);
	if (m > b) c = c*b/m;
	return c;
}

void main()
{
	float lum = COMPAT_TEXTURE(PassPrev5Texture, vec2(0.1,0.1)).a;

	// Calculating texel coordinates
   
	vec2 texcoord = TEX0.xy;
	if (IOS > 0.0){
		vec2 ofactor = OutputSize.xy/SourceSize.xy;
		vec2 intfactor = round(ofactor);
		vec2 diff = ofactor/intfactor;
		float scan = mix(diff.y, diff.x, TATE);
		texcoord = Overscan(texcoord, scan, scan);
		if (IOS == 1.0) texcoord = mix(vec2(TEX0.x, texcoord.y), vec2(texcoord.x, TEX0.y), TATE);
	}
   
	float factor  = 1.00 + (1.0-0.5*OS)*BLOOM/100.0 - lum*BLOOM/100.0;
	texcoord  = Overscan(texcoord, factor, factor);
	vec2 pos  = Warp(texcoord);
	vec2 pos0 = Warp(TEX0.xy);
   
	vec2 coffset = vec2(0.5, 0.5);
	bool interb = (interm > 0.5 && interm < 2.5 && inter <= mix(SourceSize.y, SourceSize.x, TATE));
	bool notate  = (TATE < 0.5);
	
	if (interb) coffset = ((notate) ? vec2(0.5,0.0) : vec2(0.0, 0.5));
	
	vec2 ps = SourceSize.zw;
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
	
	float zero = exp2(-h_sharp);   
	
	float sharp1 = (s_sharp > 1.0) ? (1.0 + 0.5*fract(s_sharp)) : s_sharp;
	sharp1 = sharp1 * zero;
	
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
	float twl2 = max(wl2 - sharp1, mix(0.0,mix(-0.10, 0.0001, sqrt(fpx)),float(s_sharp > 0.05)));
	float twl1 = max(wl1 - sharp1, 0.0);
	float twr1 = max(wr1 - sharp1, 0.0);	
	float twr2 = max(wr2 - sharp1, mix(0.0,mix(-0.10, 0.0001, sqrt(fp1)),float(s_sharp > 0.05)));
	float twr3 = max(wr3 - sharp1, 0.0);
	
	float wtt = 1.0/(twl3+twl2+twl1+twr1+twr2+twr3);
	float wt  = 1.0/(wl2+wl1+wr1+wr2);
	bool sharp = (s_sharp > 0.05);
	
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

	float dfx = pow(fpx, fp1);
	float df1 = pow(fp1, fpx);

	float clow = 1.0 - pow(abs(decon),0.6);
	float chigh = 1.0 + abs(decon);

	vec3 dcolor1 = vec3(clow, chigh, clow);
	vec3 dcolor2 = vec3(chigh, clow, chigh);

	if (decon < 0.0) { dcolor1 = dcolor1.rgg; dcolor2 = dcolor2.rgg; }

	vec3 d1 = abs(l1 - r1); float c1 = pow(max((max(max(d1.r,d1.g),d1.b)-0.15)/0.85,0.0),0.33);
	l1 *= mix(vec3(1.0), dcolor1, dfx*c1);
	r1 *= mix(vec3(1.0), dcolor2, df1*c1);
	
	d1 = abs(l2 - l1); c1 = pow(max((max(max(d1.r,d1.g),d1.b)-0.15)/0.85,0.0),0.33);
	l2 *= mix(vec3(1.0), dcolor1,    c1);

	d1 = abs(r2 - r1); c1 = pow(max((max(max(d1.r,d1.g),d1.b)-0.15)/0.85,0.0),0.33);
	r2 *= mix(vec3(1.0), dcolor2,    c1);
	
	vec3 color1 = (l3*twl3 + l2*twl2 + l1*twl1 + r1*twr1 + r2*twr2 + r3*twr3)*wtt;
	
	vec3 colmin = min(min(l1,r1), min(l2,r2));
	vec3 colmax = max(max(l1,r1), max(l2,r2));
	
	if (sharp) color1 = clamp(color1, colmin, colmax);
	
	vec3 gtmp = vec3(gamma_out*0.1); 
	vec3 scolor1 = color1;
	
	scolor1 = (sl2*wl2 + sl1*wl1 + sr1*wr1 + sr2*wr2)*wt;
	scolor1 = pow(scolor1, gtmp);	vec3 mcolor1 = scolor1;
	scolor1 = mix(color1, scolor1, spike);
	
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

	d1 = abs(l1 - r1); c1 = pow(max((max(max(d1.r,d1.g),d1.b)-0.15)/0.85,0.0),0.33);
	l1 *= mix(vec3(1.0), dcolor1, dfx*c1);
	r1 *= mix(vec3(1.0), dcolor2, df1*c1);
	
	d1 = abs(l2 - l1); c1 = pow(max((max(max(d1.r,d1.g),d1.b)-0.15)/0.85,0.0),0.33);
	l2 *= mix(vec3(1.0), dcolor1,    c1);

	d1 = abs(r2 - r1); c1 = pow(max((max(max(d1.r,d1.g),d1.b)-0.15)/0.85,0.0),0.33);
	r2 *= mix(vec3(1.0), dcolor2,    c1);

	vec3 color2 = (l3*twl3 + l2*twl2 + l1*twl1 + r1*twr1 + r2*twr2 + r3*twr3)*wtt;
	
	colmin = min(min(l1,r1), min(l2,r2));
	colmax = max(max(l1,r1), max(l2,r2));
	
	if (sharp) color2 = clamp(color2, colmin, colmax);

	vec3 scolor2 = color2;
	
	scolor2 = (sl2*wl2 + sl1*wl1 + sr1*wr1 + sr2*wr2)*wt;
	scolor2 = pow(scolor2, gtmp);	vec3 mcolor2 = scolor2;
	scolor2 = mix(color2, scolor2, spike);
	
	vec3 color0 = color1;

	if (interb)
	{
		pC4-= 2.*offy;
	
		l3 = COMPAT_TEXTURE(PassPrev4Texture, pC4 -off2).xyz;
		l2 = COMPAT_TEXTURE(PassPrev4Texture, pC4 -offx).xyz;
		l1 = COMPAT_TEXTURE(PassPrev4Texture, pC4      ).xyz;
		r1 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +offx).xyz;
		r2 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +off2).xyz;
		r3 = COMPAT_TEXTURE(PassPrev4Texture, pC4 +offx+off2).xyz;

		d1 = abs(l1 - r1); c1 = pow(max((max(max(d1.r,d1.g),d1.b)-0.15)/0.85,0.0),0.33);
		l1 *= mix(vec3(1.0), dcolor1, dfx*c1);
		r1 *= mix(vec3(1.0), dcolor2, df1*c1);
	
		d1 = abs(l2 - l1); c1 = pow(max((max(max(d1.r,d1.g),d1.b)-0.15)/0.85,0.0),0.33);
		l2 *= mix(vec3(1.0), dcolor1,    c1);

		d1 = abs(r2 - r1); c1 = pow(max((max(max(d1.r,d1.g),d1.b)-0.15)/0.85,0.0),0.33);
		r2 *= mix(vec3(1.0), dcolor2,    c1);
	
		color0 = (l3*twl3 + l2*twl2 + l1*twl1 + r1*twr1 + r2*twr2 + r3*twr3)*wtt;
	
		colmin = min(min(l1,r1), min(l2,r2));
		colmax = max(max(l1,r1), max(l2,r2));
	
		if (sharp) color0 = clamp(color0, colmin, colmax);
	}
	
	// calculating scanlines
	
	vec3 one = vec3(1.0);
	
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

	vec3 f1 = vec3(f); 
	vec3 f2 = vec3(1.0-f);
	
	if (gsl == 0.0) { w1 = sw0(f1,cref1,shape1); w2 = sw0(f2,cref2,shape2);} else
	if (gsl == 1.0) { w1 = sw1(f1,cref1,shape1); w2 = sw1(f2,cref2,shape2);} else
	if (gsl == 2.0) { w1 = sw2(f1,cref1,shape1); w2 = sw2(f2,cref2,shape2);}

	vec3 cd1 = one; vec3 cd2 = one; float vm = pow(abs(vertmask), 0.4);
	
	float v_high = 1.0 + 0.25*abs(vertmask);
	float v_low  = 1.0 - vm;
	
	if (vertmask < 0.0) 
	{
		cd1 = min(mix(one, vec3(v_high, v_low, v_low), 1.5*pow(f+0.075, 1.0-f)), 1.0);
		cd2 = min(mix(one, vec3(v_low, v_high, v_high), 1.5*pow(1.075-f, f)), 1.0);
	}
	else
	{
		cd1 = min(mix(one, vec3(v_high, v_low, v_high), 1.5*pow(f+0.075, 1.0-f)), 1.0);
		cd2 = min(mix(one, vec3(v_low, v_high, v_low), 1.5*pow(1.075-f, f)), 1.0);
	}
	
	vec3 color = color1*w1*cd1 + color2*w2*cd2;
	
	color = min(color, 1.0);
	
	if (interm > 0.5 && inter <= mix(SourceSize.y, SourceSize.x, TATE)) 
	{
		if (interm < 2.5)
		{
			float line_no  = floor(mod(mix(  OGL2Pos.y,  OGL2Pos.x, TATE),2.0));		
			float frame_no = floor(mod(float(global.FrameCount),2.0));
			float ii = (interm > 1.5) ? 0.5 : abs(line_no-frame_no);
			
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
	vec3 cmask = one;
	
	float smask = (notate) ? SlotMask(gl_FragCoord.xy * 1.000001,tmp) : SlotMask(gl_FragCoord.yx * 1.000001,tmp);
	color = color*smask;	
	
	cmask*= (notate) ? Mask(gl_FragCoord.xy * 1.000001,mcolor) :
		Mask(gl_FragCoord.yx * 1.000001,mcolor);
	
	color = color*cmask;
	
	color = min(color,1.0);
	cmask = min(cmask*smask, 1.0);
	
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
	if (interm < 0.5 || inter > mix(SourceSize.y, SourceSize.x, TATE)) color = declip(color, pow(w3,0.6));	
	color = min(color, mix(cmask,one,0.6));

	color = color + glow*Bloom/3.0;
		
	color = pow(color, vec3(1.0/gamma_out));
	
	FragColor = vec4(color*corner(pos0), 1.0);
}
