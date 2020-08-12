#ifndef BIND_SHADER_PARAMS_H
#define BIND_SHADER_PARAMS_H

/////////////////////////////  GPL LICENSE NOTICE  /////////////////////////////

//  crt-royale: A full-featured CRT shader, with cheese.
//  Copyright (C) 2014 TroggleMonkey <trogglemonkey@gmx.com>
//
//  This program is free software; you can redistribute it and/or modify it
//  under the terms of the GNU General Public License as published by the Free
//  Software Foundation; either version 2 of the License, or any later version.
//
//  This program is distributed in the hope that it will be useful, but WITHOUT
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
//  more details.
//
//  You should have received a copy of the GNU General Public License along with
//  this program; if not, write to the Free Software Foundation, Inc., 59 Temple
//  Place, Suite 330, Boston, MA 02111-1307 USA


/////////////////////////////  SETTINGS MANAGEMENT  ////////////////////////////

layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
    vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	vec4 FinalViewportSize;
	uint FrameCount;

	float HSS_MEGA_BEZEL_DEBUG;
	float HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL;
	
	float HSS_ROTATE_CORE_IMAGE;
	float HSS_ASPECT_RATIO_ORIENTATION;
	float HSS_ASPECT_RATIO_MODE;
	float HSS_ASPECT_RATIO_EXPLICIT;
	float HSS_INT_SCALE_MODE;
	float HSS_NON_INTEGER_SCALE;
	float HSS_SNAP_TO_INT_SCALE_TOLERANCE;
    float HSS_INT_SCALE_MULTIPLE_OFFSET;
	float HSS_INT_SCALE_MULTIPLE_OFFSET_LONG;
	float HSS_INT_SCALE_BORDER_MIN_HEIGHT;

	float HSS_SCANLINE_DIRECTION;
	float HSS_CORE_RES_SAMPLING_MULT_SCANLINE_DIR;
	float HSS_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR;
	float HSS_INTERLACE_TRIGGER_RES;
float HSS_SPLIT_SCREEN_AMOUNT;
float HSS_SPLIT_SCREEN_CENTER_FILL_MODE;


	float HSS_POSITION_OFFSET_X;
	float HSS_POSITION_OFFSET_Y;

	float HSS_CROP_OVERSCAN_TOP;
	float HSS_CROP_OVERSCAN_BOTTOM;
	float HSS_CROP_OVERSCAN_LEFT;
	float HSS_CROP_OVERSCAN_RIGHT;

	float HSS_CURVATURE_MODE;
	float HSS_CURVATURE_3D_RADIUS;
	float HSS_CURVATURE_3D_VIEW_DIST;
	float HSS_CURVATURE_3D_TILT_ANGLE_X;
	float HSS_CURVATURE_3D_TILT_ANGLE_Y;
	float HSS_CURVATURE_2D_SCALE_LONG_AXIS;
	float HSS_CURVATURE_2D_SCALE_SHORT_AXIS;
	float HSS_CURVATURE_POST_SCALE_X;
	float HSS_CURVATURE_POST_SCALE_Y;
	
	float HSS_SCREENFX_CORNER_RADIUS;
	float HSS_SCREENFX_EDGE_SHARPNESS;
	float HSS_SCREENFX_VIGNETTE;

	float HSS_COLOR_CRT_PROFILE;
	float HSS_COLOR_SPACE;
	float HSS_COLOR_BLACK_LEVEL;
	// float hmss_color_pre_crt_gamma_adjust;
	float HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS;
	float HSS_COLOR_LUMINANCE;
	float HSS_COLOR_TEMPERATURE;
	float HSS_COLOR_SATURATION;
	float HSS_COLOR_CRT_GAMMA;

	float HSS_PHOSPHOR_PERSISTENCE;

	float HSS_SCREENFX_FAKE_SCANLINE_OPACITY;
	float HSS_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF;

	float HSS_TUBE_BLACK_EDGE_THICKNESS;
	float HSS_TUBE_CURVATURE_SCALE;

	float HBZ_TUBE_GLASS_IMAGE_OPACITY;
	float HBZ_TUBE_GLASS_IMAGE_SCALE;
	float HBZ_TUBE_EDGE_SHADOW;

	// Image Bezel
	float HBZ_BACKGROUND_IMAGE_OPACITY;
	float HBZ_BACKGROUND_IMAGE_SCALE_MODE;
	float HBZ_BACKGROUND_IMAGE_ASPECT_RATIO;
	float HBZ_BACKGROUND_IMAGE_TUBE_HEIGHT;
	float HBZ_BACKGROUND_IMAGE_VIGNETTE_OPACITY;


	// Generated Bezel
	float HBZ_BEZEL_OPACITY;
	float HBZ_BEZEL_COLOR_HUE;
	float HBZ_BEZEL_COLOR_SATURATION;
	float HBZ_BEZEL_COLOR_VALUE;
	float HBZ_BEZEL_COLOR_BLEND_WITH_IMAGE;
	float HBZ_BEZEL_BRIGHTNESS;
	float HBZ_BEZEL_HIGHLIGHT;
	float HBZ_BEZEL_WIDTH;
	float HBZ_BEZEL_HEIGHT;
float HSS_BEZEL_OUTER_CURVATURE_SCALE;
	
	float HBZ_BEZEL_INNER_EDGE_THICKNESS;
	float HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE;
	float HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE;
	float HBZ_BEZEL_NOISE;

	// Generated Frame
	float HBZ_FRAME_OPACITY;
	float HSS_FRAME_OUTER_CURVATURE_SCALE;
float HBZ_FRAME_THICKNESS;
float HBZ_FRAME_INNER_EDGE_THICKNESS;
float HBZ_FRAME_INNER_CORNER_RADIUS_SCALE;
float HBZ_FRAME_OUTER_EDGE_THICKNESS;
float HBZ_FRAME_OUTER_EDGE_SHADING;
	float HBZ_FRAME_OUTER_CORNER_RADIUS;
	float HBZ_FRAME_POS_Y_OFFSET;
	float HBZ_FRAME_SHADOW_OPACITY;
	float HBZ_FRAME_SHADOW_WIDTH;
	
	// Blur Stuff
	float HBR_BLUR_NUM_SAMPLES;
	float HBR_BLUR_MIN;
	float HBR_BLUR_MAX;

	// Reflection
	float HBR_GLOBAL_AMOUNT;
	float HBR_GLOBAL_GAMMA_ADJUST;

	float HBR_INNER_EDGE_REFLECTION;
	float HBR_INNER_EDGE_FULLSCREEN_GLOW;
	float HBR_DIRECT_REFLECTION;
	float HBR_DIFFUSED_REFLECTION;
	float HBR_FULLSCREEN_GLOW;
	float HBR_FULLSCREEN_GLOW_GAMMA;

	float HBR_FADE_AMOUNT;
	float HBR_RADIAL_FADE_WIDTH;
	float HBR_RADIAL_FADE_HEIGHT;

	float HBR_LATERAL_OUTER_FADE_POSITION;
	float HBR_LATERAL_OUTER_FADE_DISTANCE;

	float HBR_CORNER_FADE;
	float HBR_CORNER_INNER_SPREAD;
	float HBR_CORNER_OUTER_SPREAD;
float HBR_CORNER_ROTATION_OFFSET_TOP;
float HBR_CORNER_ROTATION_OFFSET_BOTTOM;
	float HBR_CORNER_FADE_DISTANCE;

	float HBR_NOISE_AMOUNT;
	float HBR_NOISE_SAMPLES;
	float HBR_NOISE_SAMPLE_DISTANCE;
	float HBR_CORNER_SPREAD_FALLOFF;

	float HIL_DECAL_IMAGE_OPACITY;
float HIL_NIGHTMODE_IMAGE_OPACITY;
float HIL_LIGHTS_IMAGE_OPACITY;
float HTI_TOP_IMAGE_OPACITY;
	float HTI_TOP_IMAGE_BLEND_MODE;
	float HTI_TOP_IMAGE_MASK_MODE;
	
	float HBZ_BEZEL_GAMMA;
    
	// HSM Removed
	// float crt_gamma;
	// float lcd_gamma;

	float levels_contrast;
	float halation_weight;
	float diffusion_weight;
	float bloom_underestimate_levels;
	float bloom_excess;
	float beam_min_sigma;
	float beam_max_sigma;
	float beam_spot_power;
	float beam_min_shape;
	float beam_max_shape;
	float beam_shape_power;
	float beam_horiz_filter;
	float beam_horiz_sigma;
	float beam_horiz_linear_rgb_weight;
	float convergence_offset_x_r;
	float convergence_offset_x_g;
	float convergence_offset_x_b;
	float convergence_offset_y_r;
	float convergence_offset_y_g;
	float convergence_offset_y_b;
	float mask_type;
	float mask_sample_mode_desired;
	float mask_num_triads_desired;
	float mask_triad_size_desired;
	float mask_specify_num_triads;
	float aa_subpixel_r_offset_x_runtime;
	float aa_subpixel_r_offset_y_runtime;
	float aa_cubic_c;
	float aa_gauss_sigma;
	float geom_mode_runtime;
	float geom_radius;
	float geom_view_dist;
	float geom_tilt_angle_x;
	float geom_tilt_angle_y;
	float geom_aspect_ratio_x;
	float geom_aspect_ratio_y;
	float geom_overscan_x;
	float geom_overscan_y;
	float border_size;
	float border_darkness;
	float border_compress;
	float interlace_bff;
	float interlace_1080i;
	float interlace_detect_toggle;
} global;

#include "../user-settings.h"
#include "derived-settings-and-constants.h"

//  Override some parameters for gamma-management.h and tex2Dantialias.h:
#define OVERRIDE_DEVICE_GAMMA
static const float gba_gamma = 3.5; //  Irrelevant but necessary to define.
#define ANTIALIAS_OVERRIDE_BASICS
#define ANTIALIAS_OVERRIDE_PARAMETERS

//  Disable runtime shader params if the user doesn't explicitly want them.
//  Static constants will be defined in place of uniforms of the same name.
#ifdef RUNTIME_SHADER_PARAMS_ENABLE    
    #ifndef RUNTIME_SCANLINES_HORIZ_FILTER_COLORSPACE
        static const float beam_horiz_filter = clamp(beam_horiz_filter_static, 0.0, 2.0);
        static const float beam_horiz_linear_rgb_weight = clamp(beam_horiz_linear_rgb_weight_static, 0.0, 1.0);
    #endif
    #ifndef RUNTIME_PHOSPHOR_MASK_MODE_TYPE_SELECT
        static const float mask_type = clamp(mask_type_static, 0.0, 2.0);
    #endif
    #ifndef RUNTIME_ANTIALIAS_WEIGHTS
        static const float aa_cubic_c = aa_cubic_c_static;                              //  Clamp to [0, 4]?
        static const float aa_gauss_sigma = max(FIX_ZERO(0.0), aa_gauss_sigma_static);  //  Clamp to [FIXZERO(0), 1]?
    #endif
#else
	#define HARDCODE_SETTINGS
#endif

//  Bind option names to shader parameter uniforms or static constants.
#ifdef HARDCODE_SETTINGS
    //  Use constants from user-settings.h, and limit ranges appropriately:
    static const float crt_gamma = max(0.0, crt_gamma_static);
    static const float lcd_gamma = max(0.0, lcd_gamma_static);
    static const float levels_contrast = clamp(levels_contrast_static, 0.0, 4.0);
    static const float halation_weight = clamp(halation_weight_static, 0.0, 1.0);
    static const float diffusion_weight = clamp(diffusion_weight_static, 0.0, 1.0);
    static const float bloom_underestimate_levels = max(FIX_ZERO(0.0), bloom_underestimate_levels_static);
    static const float bloom_excess = clamp(bloom_excess_static, 0.0, 1.0);
    static const float beam_min_sigma = max(FIX_ZERO(0.0), beam_min_sigma_static);
    static const float beam_max_sigma = max(beam_min_sigma, beam_max_sigma_static);
    static const float beam_spot_power = max(beam_spot_power_static, 0.0);
    static const float beam_min_shape = max(2.0, beam_min_shape_static);
    static const float beam_max_shape = max(beam_min_shape, beam_max_shape_static);
    static const float beam_shape_power = max(0.0, beam_shape_power_static);
    static const float beam_horiz_filter = clamp(beam_horiz_filter_static, 0.0, 2.0);
    static const float beam_horiz_sigma = max(FIX_ZERO(0.0), beam_horiz_sigma_static);
    static const float beam_horiz_linear_rgb_weight = clamp(beam_horiz_linear_rgb_weight_static, 0.0, 1.0);
    //  Unpack static vector elements to match scalar uniforms:
    static const float convergence_offset_x_r = clamp(convergence_offsets_r_static.x, -4.0, 4.0);
    static const float convergence_offset_x_g = clamp(convergence_offsets_g_static.x, -4.0, 4.0);
    static const float convergence_offset_x_b = clamp(convergence_offsets_b_static.x, -4.0, 4.0);
    static const float convergence_offset_y_r = clamp(convergence_offsets_r_static.y, -4.0, 4.0);
    static const float convergence_offset_y_g = clamp(convergence_offsets_g_static.y, -4.0, 4.0);
    static const float convergence_offset_y_b = clamp(convergence_offsets_b_static.y, -4.0, 4.0);
    static const float mask_type = clamp(mask_type_static, 0.0, 2.0);
    static const float mask_sample_mode_desired = clamp(mask_sample_mode_static, 0.0, 2.0);
    static const float mask_specify_num_triads = clamp(mask_specify_num_triads_static, 0.0, 1.0);
    static const float mask_triad_size_desired = clamp(mask_triad_size_desired_static, 1.0, 18.0);
    static const float mask_num_triads_desired = clamp(mask_num_triads_desired_static, 342.0, 1920.0);
    static const float aa_subpixel_r_offset_x_runtime = clamp(aa_subpixel_r_offset_static.x, -0.5, 0.5);
    static const float aa_subpixel_r_offset_y_runtime = clamp(aa_subpixel_r_offset_static.y, -0.5, 0.5);
    static const float aa_cubic_c = aa_cubic_c_static;                              //  Clamp to [0, 4]?
    static const float aa_gauss_sigma = max(FIX_ZERO(0.0), aa_gauss_sigma_static);  //  Clamp to [FIXZERO(0), 1]?
    static const float geom_mode_runtime = clamp(geom_mode_static, 0.0, 3.0);
    static const float geom_radius = max(1.0/(2.0*pi), geom_radius_static);         //  Clamp to [1/(2*pi), 1024]?
    static const float geom_view_dist = max(0.5, geom_view_dist_static);            //  Clamp to [0.5, 1024]?
    static const float geom_tilt_angle_x = clamp(geom_tilt_angle_static.x, -pi, pi);
    static const float geom_tilt_angle_y = clamp(geom_tilt_angle_static.y, -pi, pi);
    static const float geom_aspect_ratio_x = geom_aspect_ratio_static;              //  Force >= 1?
    static const float geom_aspect_ratio_y = 1.0;
    static const float geom_overscan_x = max(FIX_ZERO(0.0), geom_overscan_static.x);
    static const float geom_overscan_y = max(FIX_ZERO(0.0), geom_overscan_static.y);
    static const float border_size = clamp(border_size_static, 0.0, 0.5);           //  0.5 reaches to image center
    static const float border_darkness = max(0.0, border_darkness_static);
    static const float border_compress = max(1.0, border_compress_static);          //  < 1.0 darkens whole image
	static const float interlace_detect = float(interlace_detect_static);
    static const float interlace_bff = float(interlace_bff_static);
    static const float interlace_1080i = float(interlace_1080i_static);
#else

// HSM Removed
// #pragma parameter crt_gamma "Simulated CRT Gamma" 2.5 1.0 5.0 0.025
//#define crt_gamma global.crt_gamma
// #pragma parameter lcd_gamma "Your Display Gamma" 2.2 1.0 5.0 0.025
//#define lcd_gamma global.lcd_gamma

#define crt_gamma 2.5 //HSS_COLOR_CRT_GAMMA
#define lcd_gamma 2.2 //HSS_COLOR_CRT_GAMMA

// HSM Removed
// #pragma parameter levels_contrast "Contrast" 1.0 0.0 4.0 0.015625
// #define levels_contrast global.levels_contrast

// HSM Added
#define levels_contrast 1

#pragma parameter halation_weight 				"[ROYALE GLOW]  Halation Weight" 0.0 0.0 1.0 0.005
#pragma parameter diffusion_weight 				"[GLOW]  Diffusion Weight" 0.04 0.0 1.0 0.005
#pragma parameter bloom_underestimate_levels 	"[GLOW]  Bloom - Underestimate Levels" 0.8 0.0 5.0 0.01
#define bloom_underestimate_levels global.bloom_underestimate_levels
#pragma parameter bloom_excess 					"[GLOW]  Bloom - Excess" 0.0 0.0 1.0 0.005
#pragma parameter beam_min_sigma 				"[SCANLINE BEAM]  Min Sigma" 0.02 0.005 1.0 0.005
#define beam_min_sigma global.beam_min_sigma
#pragma parameter beam_max_sigma 				"[SCANLINE BEAM]  Max Sigma" 0.3 0.005 1.0 0.005
#define beam_max_sigma global.beam_max_sigma
#pragma parameter beam_spot_power 				"[SCANLINE BEAM]  Spot Power" 0.33 0.01 16.0 0.01
#define beam_spot_power global.beam_spot_power
#pragma parameter beam_min_shape 				"[SCANLINE BEAM]  Min Shape" 2.0 2.0 32.0 0.1
#define beam_min_shape global.beam_min_shape
#pragma parameter beam_max_shape 				"[SCANLINE BEAM]  Max Shape" 4.0 2.0 32.0 0.1
#define beam_max_shape global.beam_max_shape
#pragma parameter beam_shape_power 				"[SCANLINE BEAM]  Shape Power" 0.25 0.01 16.0 0.01
#define beam_shape_power global.beam_shape_power
#pragma parameter beam_horiz_filter 			"[SCANLINE BEAM]  Horiz Filter" 0.0 0.0 2.0 1.0
#define beam_horiz_filter global.beam_horiz_filter
#pragma parameter beam_horiz_sigma 				"[SCANLINE BEAM]  Horiz Sigma" 0.35 0.0 0.67 0.005
#define beam_horiz_sigma global.beam_horiz_sigma
#pragma parameter beam_horiz_linear_rgb_weight 	"[SCANLINE BEAM]  Horiz Linear RGB Weight" 1.0 0.0 1.0 0.01

// HSM Removed Params Due to Parameter Limit
// #pragma parameter convergence_offset_x_r "[ROYALE]  Convergence - Offset X Red" 0.0 -4.0 4.0 0.05
// #define convergence_offset_x_r global.convergence_offset_x_r
// #pragma parameter convergence_offset_x_g "[ROYALE]  Convergence - Offset X Green" 0.0 -4.0 4.0 0.05
// #define convergence_offset_x_g global.convergence_offset_x_g
// #pragma parameter convergence_offset_x_b "[ROYALE]  Convergence - Offset X Blue" 0.0 -4.0 4.0 0.05
// #define convergence_offset_x_b global.convergence_offset_x_b
// #pragma parameter convergence_offset_y_r "[ROYALE]  Convergence - Offset Y Red" 0.0 -2.0 2.0 0.05
// #define convergence_offset_y_r global.convergence_offset_y_r
// #pragma parameter convergence_offset_y_g "[ROYALE]  Convergence - Offset Y Green" 0.0 -2.0 2.0 0.05
// #define convergence_offset_y_g global.convergence_offset_y_g
// #pragma parameter convergence_offset_y_b "[ROYALE]  Convergence - Offset Y Blue" 0.0 -2.0 2.0 0.05
// #define convergence_offset_y_b global.convergence_offset_y_b

// HSM Added
#define convergence_offset_x_r clamp(convergence_offsets_r_static.x, -4.0, 4.0)
#define convergence_offset_x_g clamp(convergence_offsets_g_static.x, -4.0, 4.0)
#define convergence_offset_x_b clamp(convergence_offsets_b_static.x, -4.0, 4.0)
#define convergence_offset_y_r clamp(convergence_offsets_r_static.y, -4.0, 4.0)
#define convergence_offset_y_g clamp(convergence_offsets_g_static.y, -4.0, 4.0)
#define convergence_offset_y_b clamp(convergence_offsets_b_static.y, -4.0, 4.0)

#pragma parameter mask_type "[MASK]  Type - Grille, Slot, Shadow" 1.0 0.0 2.0 1.0
#define mask_type global.mask_type

// HSM Removed
// #pragma parameter mask_sample_mode_desired "Mask - Sample Mode" 0.0 0.0 2.0 1.0   //  Consider blocking mode 2.
// #define mask_sample_mode_desired global.mask_sample_mode_desired

// HSM Added
#define mask_sample_mode_desired 0

#pragma parameter mask_specify_num_triads "[MASK]  Specify Number of Triads" 0.0 0.0 1.0 1.0
#pragma parameter mask_triad_size_desired "[MASK]  Triad Size Desired" 3.0 1.0 18.0 0.125
#pragma parameter mask_num_triads_desired "[MASK]  Number of Triads Desired" 480.0 342.0 1920.0 1.0

// HSM Removed
// #pragma parameter aa_subpixel_r_offset_x_runtime "AA - Subpixel R Offset X" -0.333333333 -0.333333333 0.333333333 0.333333333
// #define aa_subpixel_r_offset_x_runtime global.aa_subpixel_r_offset_x_runtime
// #pragma parameter aa_subpixel_r_offset_y_runtime "AA - Subpixel R Offset Y" 0.0 -0.333333333 0.333333333 0.333333333
// #define aa_subpixel_r_offset_y_runtime global.aa_subpixel_r_offset_y_runtime

// HSM Added
#define aa_subpixel_r_offset_x_runtime -0.333333333
#define aa_subpixel_r_offset_y_runtime 0

#pragma parameter aa_cubic_c 			"[SHARPNESS]  AA - Cubic Sharpness" 0.5 0.0 4.0 0.015625
#define aa_cubic_c global.aa_cubic_c
#pragma parameter aa_gauss_sigma 		"[SHARPNESS]  AA - Gaussian Sigma" 0.5 0.0625 1.0 0.015625
#define aa_gauss_sigma global.aa_gauss_sigma

// HSM Removed
// #pragma parameter geom_mode_runtime "Geometry - Mode" 0.0 0.0 3.0 1.0
// #define geom_mode_runtime global.geom_mode_runtime
// #pragma parameter geom_radius "Geometry - Radius" 2.0 0.16 1024.0 0.05
// #define geom_radius global.geom_radius
// #pragma parameter geom_view_dist "Geometry - View Distance" 2.0 0.5 1024.0 0.1
// #define geom_view_dist global.geom_view_dist
// #pragma parameter geom_tilt_angle_x "Geometry - Tilt Angle X" 0.0 -3.14159265 3.14159265 0.017453292519943295
// #define geom_tilt_angle_x global.geom_tilt_angle_x
// #pragma parameter geom_tilt_angle_y "Geometry - Tilt Angle Y" 0.0 -3.14159265 3.14159265 0.017453292519943295
// #define geom_tilt_angle_y global.geom_tilt_angle_y
// #pragma parameter geom_aspect_ratio_x "Geometry - Aspect Ratio X" 432.0 1.0 512.0 1.0
// #define geom_aspect_ratio_x global.geom_aspect_ratio_x
// #pragma parameter geom_aspect_ratio_y "Geometry - Aspect Ratio Y" 329.0 1.0 512.0 1.0
// #define geom_aspect_ratio_y global.geom_aspect_ratio_y

// HSM Added
#define geom_aspect_ratio_x 432.0
#define geom_aspect_ratio_y 329.0

#pragma parameter geom_overscan_x 	"[OVERSCAN]  Overscan X" 1.0 0.004 4.0 0.001
#define geom_overscan_x global.geom_overscan_x
#pragma parameter geom_overscan_y 	"[OVERSCAN]  Overscan Y" 1.0 0.004 4.0 0.001
#define geom_overscan_y global.geom_overscan_y

#define border_size 0.015
#define border_darkness 2
#define border_compress 2.5

#pragma parameter interlace_detect_toggle 	"[INTERLACING]  Interlace ON" 0 0 1 1
bool interlace_detect = bool(global.interlace_detect_toggle);

// HSM Removed
// #pragma parameter interlace_bff "Interlacing - Bottom Field First" 0.0 0.0 1.0 1.0
// #define interlace_bff interlace_bff
// #pragma parameter interlace_1080i "Interlace - Detect 1080i" 0.0 0.0 1.0 1.0
// #define interlace_1080i global.interlace_1080i

// HSM Added
#define interlace_bff 0
#define interlace_1080i 0

#endif

//  Provide accessors for vector constants that pack scalar uniforms:
inline float2 get_aspect_vector(const float geom_aspect_ratio)
{
    //  Get an aspect ratio vector.  Enforce geom_max_aspect_ratio, and prevent
    //  the absolute scale from affecting the uv-mapping for curvature:
    const float geom_clamped_aspect_ratio =
        min(geom_aspect_ratio, geom_max_aspect_ratio);
    const float2 geom_aspect =
        normalize(float2(geom_clamped_aspect_ratio, 1.0));
    return geom_aspect;
}

inline float2 get_geom_overscan_vector()
{
    return float2(geom_overscan_x, geom_overscan_y);
}

// inline float2 get_geom_tilt_angle_vector()
// {
//     return float2(geom_tilt_angle_x, geom_tilt_angle_y);
// }


inline float3 get_convergence_offsets_x_vector()
{
    return float3(convergence_offset_x_r, convergence_offset_x_g,
        convergence_offset_x_b);
}

inline float3 get_convergence_offsets_y_vector()
{
    return float3(convergence_offset_y_r, convergence_offset_y_g,
        convergence_offset_y_b);
}

inline float2 get_convergence_offsets_r_vector()
{
    return float2(convergence_offset_x_r, convergence_offset_y_r);
}

inline float2 get_convergence_offsets_g_vector()
{
    return float2(convergence_offset_x_g, convergence_offset_y_g);
}

inline float2 get_convergence_offsets_b_vector()
{
    return float2(convergence_offset_x_b, convergence_offset_y_b);
}

inline float2 get_aa_subpixel_r_offset()
{
    #ifdef RUNTIME_ANTIALIAS_WEIGHTS
        #ifdef RUNTIME_ANTIALIAS_SUBPIXEL_OFFSETS
            //  WARNING: THIS IS EXTREMELY EXPENSIVE.
            return float2(aa_subpixel_r_offset_x_runtime,
                aa_subpixel_r_offset_y_runtime);
        #else
            return aa_subpixel_r_offset_static;
        #endif
    #else
        return aa_subpixel_r_offset_static;
    #endif
}

//  Provide accessors settings which still need "cooking:"
inline float get_mask_amplify()
{
    static const float mask_grille_amplify = 1.0/mask_grille_avg_color;
    static const float mask_slot_amplify = 1.0/mask_slot_avg_color;
    static const float mask_shadow_amplify = 1.0/mask_shadow_avg_color;
    return mask_type < 0.5 ? mask_grille_amplify :
        mask_type < 1.5 ? mask_slot_amplify :
        mask_shadow_amplify;
}

inline float get_mask_sample_mode()
{
    #ifdef RUNTIME_PHOSPHOR_MASK_MODE_TYPE_SELECT
        #ifdef PHOSPHOR_MASK_MANUALLY_RESIZE
            return mask_sample_mode_desired;
        #else
            return clamp(mask_sample_mode_desired, 1.0, 2.0);
        #endif
    #else
        #ifdef PHOSPHOR_MASK_MANUALLY_RESIZE
            return mask_sample_mode_static;
        #else
            return clamp(mask_sample_mode_static, 1.0, 2.0);
        #endif
    #endif
}

#endif  //  BIND_SHADER_PARAMS_H
