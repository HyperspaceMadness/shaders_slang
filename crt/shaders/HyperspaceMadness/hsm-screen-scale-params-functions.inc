/*   
hsm-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

// Screen Scale Required Parameters
#pragma parameter hmss_mega_screen_scale_on				"___HSM MEGA BEZEL__ V.2020-05-17-0 -SCREEN SCALE ON" 1 0 1 1
#pragma parameter hmss_screen_scale_debug				"[SCREEN SCALE]  Screen Scale Debug" 0 0 1 1

#pragma parameter hmss_rotate_crt_image					"[SCALING]  Rotate CRT Image"  0 0 1 1
//#pragma parameter hmss_flip_screen_vertical			"[SCALING]  Flip Screen Vertical"  0 0 1 1
#pragma parameter hmss_aspect_ratio_mode 				"[SCALING]  Aspect Ratio Mode - Auto, Horizontal, Vertical"  0 0 2 1
#pragma parameter hmss_screen_aspect_ratio				"[SCALING]  Screen Aspect Ratio"  1.3333 0 3 0.002

#pragma parameter hmss_integer_scale_mode 				"[SCALING]  Integer Scale Mode - OFF, ShortAxis, BothAxes" 0 0 2 1
// Non integer scale is set to 82.97 so that cores which output 224px will have integer scale by default
// This is 8x integer scale at 3840x2160 and 6x integer scale at 1920x1080
#pragma parameter hmss_non_integer_scale 				"[SCALING]  Non-Integer Scale %" 82.97 1 200 0.2
#pragma parameter hmss_int_scale_multiple_offset 		"[SCALING]  Int Scale Multiple Offset" 0 -20 20 1
#pragma parameter hmss_int_scale_border_min_height 		"[SCALING]  Int Scale Border Min Height %" 5.5 -20 20 0.5

#pragma parameter hmss_scanline_direction 				"[SCANLINES]  Scanline Dir Guest-Venom - Auto, Horiz, Vert"  0 0 2 1

#pragma parameter hmss_position_offset_x 				"[POSITION]  Position Offset X" 0 -100 100 0.1
#pragma parameter hmss_position_offset_y 				"[POSITION]  Position Offset Y" 0 -100 100 0.1

#pragma parameter hmss_crop_overscan_top 				"[CROPPING]  Crop Overscan Top" 0 -256 256 1
#pragma parameter hmss_crop_overscan_bottom 			"[CROPPING]  Crop Overscan Bottom" 0 -256 256 1
#pragma parameter hmss_crop_overscan_left 				"[CROPPING]  Crop Overscan Left" 0 -256 256 1
#pragma parameter hmss_crop_overscan_right 				"[CROPPING]  Crop Overscan Right" 0 -256 256 1

#pragma parameter hmss_curvature_mode 					"[CURVATURE MODE]  Curvature Mode - 0:2D 1-2:3D Sphere, 3:3D Cyl" 0 0 3 1
#pragma parameter hmss_curvature_3D_radius 				"[CURVATURE 3D]  3D Radius" 2 0.16 1024 0.01
#pragma parameter hmss_curvature_3D_view_dist 			"[CURVATURE 3D]  3D View Distance" 2 0.5 1024 0.05
#pragma parameter hmss_curvature_3D_tilt_angle_x 		"[CURVATURE 3D]  3D Tilt Angle X" 0 -3.1415 3.1415 0.01745
#pragma parameter hmss_curvature_3D_tilt_angle_y 		"[CURVATURE 3D]  3D Tilt Angle Y" 0 -3.1415 3.1415 0.01745
#pragma parameter hmss_curvature_2D_long_axis 			"[CURVATURE 2D]  2D/Extra3D Curvature on Long Axis - Def 2" 2 0 100 0.2
#pragma parameter hmss_curvature_2D_short_axis 			"[CURVATURE 2D]  2D/Extra3D Curvature on Short Axis - Def 3" 3 0 100 0.2
#pragma parameter hmss_curvature_post_scale_x 			"[CURVATURE POST SCALE]  Scale X" 100 70 130 0.2
#pragma parameter hmss_curvature_post_scale_y 			"[CURVATURE POST SCALE]  Scale Y" 100 70 130 0.2

#pragma parameter hmss_screen_corner_radius 			"[SCREEN EDGE]  Screen Corner Radius - Default 10" 0 0 70 1
#pragma parameter hmss_screen_edge_sharpness 			"[SCREEN EDGE]  Screen Edge Sharpness" 0.4 0 1 0.01
#pragma parameter hmss_screen_vignette                  "[SCREEN EDGE]  Screen Vignette" 0 0 1 0.01

#pragma parameter hmss_color_lut_colors_on 				"[COLOR]  LUT Colors ON (No Royale)" 1 0 1 1
#pragma parameter hmss_color_black_level 				"[COLOR]  Black Level" 0 -30 30 0.05-
#pragma parameter hmss_color_luminance   				"[COLOR]  Luminance" 100 0 400 5
#pragma parameter hmss_color_pre_crt_gamma_adjust		"[COLOR]  Gamma Adjust" 1 0.01 8 0.01
#pragma parameter hmss_color_temperature   				"[COLOR]  Temperature" -50 -100.0 100.0 5.0
#pragma parameter hmss_color_saturation    				"[COLOR]  Saturation" 1.0 0.0 2.0 0.05
#pragma parameter hmss_color_negative_crop_brightness	"[COLOR]  Negative Crop Brightness" 0 0 20 0.02
#pragma parameter hmss_color_crt_gamma   				"[COLOR]  CRT Gamma" 2.2 0.1 5 0.05

#pragma parameter hmss_phosphor_persistence             "[PHOSPHOR]  Persistence - Pos:Blue, Neg:Neutral" 0 -1 1 0.05

#pragma parameter hmss_res_independent_scanline_size 	"[RES INDEPENDENT SCANLINES] Size - 0:OFF" 0 0 32 1

#pragma parameter hmss_tube_black_edge_thickness 		"[TUBE]  Black Edge Thickness" 1.2 -2 8 0.05
#pragma parameter hmss_tube_black_edge_curvature_scale 	"[TUBE]  Black Edge Curvature Scale" 1 0 4 0.1


const float HMSS_DEFAULT_GAMMA = 2.2;

// Macros.
#define FIX(c) max(abs(c), 1e-5)
#define PI 3.141592653589

#include "hsm-helper-functions.inc"
#include "hsm-royale-geometry-functions.inc"

vec2 HMSS_GetRotatedOriginalSize()
{
	if (global.hmss_rotate_crt_image == 1 || global.hmss_rotate_crt_image == 3)
	{
		return global.OriginalSize.yx;
	}
	else
	{
		return global.OriginalSize.xy;
	}
}

vec2 HMSS_GetCroppedSize(vec2 in_size){
	if (global.hmss_mega_screen_scale_on == 0)
	{
		return in_size;
	}
	else
	{
		return vec2(in_size.x - global.hmss_crop_overscan_right - global.hmss_crop_overscan_left,
					in_size.y - global.hmss_crop_overscan_top + global.hmss_crop_overscan_bottom);
	}
}

vec2 HMSS_GetCroppedOriginalSize()
{
	return HMSS_GetCroppedSize(HMSS_GetRotatedOriginalSize());
}

float HMSS_GetIsOriginalSizeVertical()
{
	vec2 rotated_original_size = HMSS_GetRotatedOriginalSize();
	float aspect_ratio = rotated_original_size.x/rotated_original_size.y;
	return aspect_ratio < 1 ? 1 : 0;
}

float HMSS_GetScreenAspect()
{
	float horizontal_aspect_ratio = global.hmss_screen_aspect_ratio;
	float vertical_aspect_ratio = 1.0 / global.hmss_screen_aspect_ratio;
	
	float auto_screen_aspect_ratio = HMSS_GetIsOriginalSizeVertical() > 0.5 ? vertical_aspect_ratio : horizontal_aspect_ratio;
	return global.hmss_aspect_ratio_mode < 1 ? auto_screen_aspect_ratio : (global.hmss_aspect_ratio_mode < 2 ? horizontal_aspect_ratio : vertical_aspect_ratio);
}

float HMSS_GetFinalViewportAspectRatio()
{
	return global.FinalViewportSize.x / global.FinalViewportSize.y;
}

float HMSS_GetUseVerticalScanlines()
{
	float auto_use_vert_scanlines = HMSS_GetScreenAspect() < 1 ? 1 : 0;
	return global.hmss_scanline_direction < 1 ? auto_use_vert_scanlines : (global.hmss_scanline_direction < 2 ? 0 : 1);
}

float HMSS_GetScreenInverseAspectRatio()
{
	float horizontal_aspect_ratio = global.hmss_screen_aspect_ratio;
	float vertical_aspect_ratio = 1.0 / global.hmss_screen_aspect_ratio;

	float auto_screen_aspect_ratio = HMSS_GetIsOriginalSizeVertical() > 0.5 ? vertical_aspect_ratio : horizontal_aspect_ratio;
	return global.hmss_aspect_ratio_mode < 1 ? auto_screen_aspect_ratio : (global.hmss_aspect_ratio_mode < 2 ? horizontal_aspect_ratio : vertical_aspect_ratio);
}

// Example Usage:
// vec2 screenScale = HMSS_GetScreenScale();
// vTexCoord = HMSS_GetInverseScaledCoord(TexCoord, screenScale);

vec2 HMSS_GetScreenScale()
{
	if (global.hmss_mega_screen_scale_on == 0)
	{
		return vec2(1.0, 1.0);
	}
	else
	{
		float output_aspect_ratio = HMSS_GetFinalViewportAspectRatio();
		float aspect_ratio = HMSS_GetScreenAspect();
		float inverse_aspect_ratio = 1.0 / aspect_ratio;

		// Get Original size with cropping applied as this affects the integer scale
		vec2 cropped_original_size = HMSS_GetCroppedOriginalSize();

		// If we are using non-integer scale return
		if (global.hmss_integer_scale_mode == 0)
		{
			return vec2(aspect_ratio / output_aspect_ratio, 1) * global.hmss_non_integer_scale / 100;
		}

		// Get the maximum height that the integer scale needs to fit into
		float viewport_res_y_without_border = global.FinalViewportSize.y - 2 * (global.hmss_int_scale_border_min_height / 100) * global.FinalViewportSize.y;
		
		float integer_scale_multiple_vert = clamp(floor(viewport_res_y_without_border / cropped_original_size.y) + global.hmss_int_scale_multiple_offset, 1, 100);
		float integer_scale_vert = integer_scale_multiple_vert * cropped_original_size.y / global.FinalViewportSize.y;

		// Get the horizontal scale from the vertical scale and aspect ratio
		float integer_scale_horz_from_aspect = aspect_ratio / output_aspect_ratio * integer_scale_vert;

		// Get the scale as a multiple of the original x-size
		float integer_scale_multiple_horz = integer_scale_horz_from_aspect * global.FinalViewportSize.x / cropped_original_size.x;

		// If we are using vertical scanlines or integer scale is set to both directions make the horizontal multiple an integer
		if (HMSS_GetUseVerticalScanlines() == 1 || global.hmss_integer_scale_mode == 2)
		{
			integer_scale_multiple_horz = round(integer_scale_multiple_horz);
		}

		float integer_scale_horz = integer_scale_multiple_horz * cropped_original_size.x / global.FinalViewportSize.x;

		return vec2(integer_scale_horz, integer_scale_vert);
	}
}

vec2 HMSS_GetScreenSize()
{
	vec2 viewport_size = global.FinalViewportSize.xy * HMSS_GetScreenScale();
	// Round this so we get proper integers
	viewport_size = vec2(round(viewport_size.x), round(viewport_size.y));
	return viewport_size;
}

// Returns Diagonal Screen scale relative to the viewport height
float HMSS_GetScreenDiagonalScale()
{
	vec2 screen_scale = HMSS_GetScreenScale();
	float screen_scale_x_compensated = screen_scale.x / (global.FinalViewportSize.x/global.FinalViewportSize.y);
	return sqrt(screen_scale_x_compensated * screen_scale_x_compensated + screen_scale.y * screen_scale.y);
}

vec2 HMSS_GetIntegerScaleMult()
{
	float epsilon = 0.002;
	vec2 integer_scale = HMSS_GetScreenSize() / HMSS_GetCroppedOriginalSize();
	integer_scale = vec2(fract(integer_scale.x + 0.001) < epsilon ? round(integer_scale.x) : integer_scale.x,
						 fract(integer_scale.y + 0.001) < epsilon ? round(integer_scale.y) : integer_scale.y);
	return integer_scale;
}

vec2 HMSS_GetScreenScaleWithEdgeHeight(float edge_height)
// Edge Height is a 0 to 1 percentage of the screen height
{
	float output_aspect_ratio = global.FinalViewportSize.x / global.FinalViewportSize.y;
	
	vec2 screen_scale = HMSS_GetScreenScale();
	float aspect_ratio = screen_scale.x / screen_scale.y;

	vec2 edge_width_height_as_scale = vec2(0, 0);
	edge_width_height_as_scale.x = 1 + (edge_height / screen_scale.y) / aspect_ratio / output_aspect_ratio;
	edge_width_height_as_scale.y = 1 + edge_height / screen_scale.y;

	return screen_scale * edge_width_height_as_scale;
}

// Same as the HMSS_GetScreenScale, but adds the width of the black edge
// Used for scaling the overlay outside the black edge
vec2 HMSS_GetTubeScale()
{
	return HMSS_GetScreenScaleWithEdgeHeight(global.hmss_tube_black_edge_thickness / 100.0);
}

vec2 HMSS_GetInverseScaledCoord(vec2 in_coord, vec2 in_scale)
{
	vec2 middle = vec2(0.49999, 0.49999);
	vec2 diff = in_coord.xy - middle;
	vec2 screen_inverse_scale = 1.0 / in_scale;
	vec2 scaled_coord = middle + diff * screen_inverse_scale;

	return scaled_coord;
}

vec2 HMSS_GetPositionOffset()
{
	if (global.hmss_mega_screen_scale_on == 0)
	{
		return vec2(0, 0);
	}
	else
	{
		float output_aspect_ratio = global.FinalViewportSize.x / global.FinalViewportSize.y;
		return vec2(global.hmss_position_offset_x / 100 / output_aspect_ratio, -global.hmss_position_offset_y / 100);
	}
}

vec2 HMSS_GetCoordWithPositionOffset(vec2 in_coord)
{
	if (global.hmss_mega_screen_scale_on == 0)
	{
		return in_coord;
	}
	else
	{
		return in_coord - HMSS_GetPositionOffset();
	}
}

vec2 HMSS_GetVTexCoordWithArgs(vec2 in_coord, vec2 in_scale, vec2 position_offset)
{
	return HMSS_GetInverseScaledCoord(HMSS_GetCoordWithPositionOffset(in_coord), in_scale);
}

vec2 HMSS_GetScreenVTexCoord(vec2 in_coord)
{
	return HMSS_GetVTexCoordWithArgs(in_coord, HMSS_GetScreenScale(), HMSS_GetPositionOffset());
}

vec2 HMSS_GetTubeVTexCoord(vec2 in_coord)
{
	return HMSS_GetVTexCoordWithArgs(in_coord, HMSS_GetTubeScale(), HMSS_GetPositionOffset());
}

vec2 HMSS_GetLongShortAxisCurvatureValues()
{
	return vec2(global.hmss_curvature_2D_long_axis / 100, global.hmss_curvature_2D_short_axis / 100);
}

vec2 HMSS_GetCurvatureValues()
{
	vec2 curvature_values = HMSS_GetScreenAspect() < 1 ? vec2(global.hmss_curvature_2D_short_axis / 100, global.hmss_curvature_2D_long_axis / 100 ) 
														: vec2(global.hmss_curvature_2D_long_axis / 100, global.hmss_curvature_2D_short_axis / 100 );
	return curvature_values;
}

// float Geom_Intersect(vec2 in_coord , vec2 sinangle, vec2 cosangle, float in_radius)
// {
//   float A = dot(in_coord, in_coord) + d.x * d.x;
//   float B = 2.0 * (in_radius * (dot(in_coord, sinangle) - d.x * cosangle.x * cosangle.y) - d.x * d.x);
//   float C = d.x * d.x + 2.0 * in_radius * d.x * cosangle.x * cosangle.y;
//   return (-B-sqrt(B * B - 4.0 * A * C)) / (2.0 * A);
// }

// vec2 Geom_Backward_Transform(vec2 in_coord, vec2 sinangle, vec2 cosangle, float in_radius)
// {
//   float c = Geom_Intersect(in_coord, sinangle, cosangle, in_radius);
//   vec2 pt = vec2(c) * in_coord;
//   pt -= vec2(-in_radius) * sinangle;
//   pt /= vec2(in_radius);
//   vec2 tang = sinangle / cosangle;
//   vec2 poc = pt / cosangle;
//   float A = dot(tang, tang) + 1.0;
//   float B = -2.0 * dot(poc, tang);
//   float C = dot(poc,poc)-1.0;
//   float a = (-B + sqrt(B * B - 4.0 * A * C)) / (2.0 * A);
//   vec2 uv = (pt - a * sinangle) / cosangle;
//   float r = FIX(in_radius * acos(a));
//   return uv * r / sin(r / in_radius);
// }

// vec2 Geom_Transform(vec2 coord, vec3 stretch, vec2 sinangle, vec2 cosangle, float in_radius, vec2 in_aspect)
// {
//   coord = (coord-vec2(0.5)) * in_aspect.xy * stretch.z + stretch.xy;
//   return (Geom_Backward_Transform(coord, sinangle, cosangle, in_radius) / in_aspect.xy + vec2(0.5));
// }

// vec2 HMSS_GetGeomCurvedCoord(vec2 in_coord, float tilt_x, float tilt_y)
// {
// 	vec2 ang = vec2(tilt_x, tilt_y);
// 	float v_sinangle = sin(ang);
// 	float v_cosangle = cos(ang);
// 	float v_stretch = maxscale(v_sinangle, v_cosangle);
// 	vec2 curved_coord = Geom_Transform(in_coord, v_stretch, v_sinangle, v_cosangle);

// 	return curved_coord;
// }

vec2 HMSS_GetCrtPiCurvedCoord(vec2 in_coord, vec2 in_curvature)
{
	// Barrel distortion shrinks the display area a bit, this will allow us to counteract that.
	in_curvature *= 5;
	vec2 barrelScale = 1.0 - (0.23 * in_curvature);
    in_coord -= vec2(0.5);
    float rsq = in_coord.x * in_coord.x + in_coord.y * in_coord.y;
    in_coord += in_coord * (in_curvature * rsq);
    in_coord *= barrelScale;
	in_coord += vec2(0.5);
    // if (abs(in_coord.x) >= 0.5 || abs(in_coord.y) >= 0.5)
    //     in_coord = vec2(-1.0);     // If out of bounds, return an invalid value.
    // else
    // {
    //     in_coord += vec2(0.5);
    // }

    return in_coord;
}

vec2 HMSS_GetTorridGristleCurvedCoord(vec2 in_coord, vec2 curvature_values)
{
	vec2 ctr_coord = in_coord - 0.5;
	vec2 distortion = curvature_values * 15.0;
	vec2 ctr_coord_0_1 = in_coord * 2.0 - 1.0;
	vec2 ctr_curved_coord = ctr_coord_0_1;
	float curved_coord_distance = sqrt(ctr_curved_coord.x * ctr_curved_coord.x + ctr_curved_coord.y * ctr_curved_coord.y);
	ctr_curved_coord = ctr_curved_coord / curved_coord_distance;
	ctr_curved_coord = ctr_curved_coord * (1.0 - pow(vec2(1.0 - (curved_coord_distance / 1.4142135623730950488016887242097)), (1.0 / (1.0 + distortion * 0.2))));
	ctr_curved_coord = ctr_curved_coord / clamp(1.0 - pow(vec2(0.29289321881345247559915563789515), (1.0 / (vec2(1.0) + distortion * 0.2))), 0.0001, 10);
	ctr_curved_coord = ctr_curved_coord * 0.5;

	float max_curved_range = 1.41;
	if (curved_coord_distance < max_curved_range)
	{
		if (abs(ctr_coord_0_1.x) > 1 || abs(ctr_coord_0_1.y) > 1)
		{
			float length_inside = length(clamp(abs(ctr_coord_0_1), 0, 1));
			float length_outside = curved_coord_distance - length_inside;
			float outside_range = max_curved_range - length_inside;
			float outside_ratio = length_outside / outside_range;
			
			// vec2 normalized_vec = abs(normalize(ctr_coord_0_1));
			// float pi = 3.1415;
			// float corner_angle_degrees = atan(normalized_vec.y / normalized_vec.x) / (2 * pi) * 360;
			//float corner_mask = smoothstep(40, 43, corner_angle_degrees);

			float blend_to_uncurved = HHLP_EasePowerInOut(outside_ratio, 2);

			ctr_curved_coord = blend_to_uncurved * ctr_coord + (1 - blend_to_uncurved) * ctr_curved_coord;
		}
	}
	else
		ctr_curved_coord = in_coord - 0.5;

	return ctr_curved_coord + 0.5;
}

// Torridgristle's curvature
vec2 HMSS_Get2DCurvedCoord(vec2 in_coord, float curvature_multiplier)
{
	// vec2 curvature_values = curvature_multiplier * HMSS_GetCurvatureValues();
	// return HMSS_GetTorridGristleCurvedCoord(in_coord, curvature_values);
	vec2 curvature_values = HMSS_GetCurvatureValues();
	return HMSS_GetCrtPiCurvedCoord(in_coord, curvature_values);
}

// // Used to get the circular area where the 2D curved coordinates are valid
// // Takes an uncurved coordinate
// float HMSS_Get2DInsideRangeMask(vec2 in_coord)
// {
// 	vec2 ctr_coord = in_coord - 0.5;
// 	vec2 ctr_coord_0_1 = in_coord * 2.0 - 1.0;
// 	vec2 ctr_curved_coord = ctr_coord_0_1;
// 	float curved_coord_distance = sqrt(ctr_curved_coord.x * ctr_curved_coord.x + ctr_curved_coord.y * ctr_curved_coord.y);
// 	float max_curved_range = 1.40;

// 	return 1 - clamp((curved_coord_distance - max_curved_range) * 10000, 0, 1);
// }

vec2 HMSS_GetPostCurvatureScaledCoord(vec2 in_curved_coord)
{
	return (in_curved_coord - 0.5) / vec2(global.hmss_curvature_post_scale_x / 100, global.hmss_curvature_post_scale_y / 100) + 0.5;
}

vec2 HMSS_GetCurvedCoord(vec2 in_coord, float curvature_multiplier)
{
	vec2 curved_coord = vec2(0, 0);
	if (global.hmss_curvature_mode > 0.5)
	{
		float epsilon = 0.001;
		float geom_radius_with_mult = global.hmss_curvature_3D_radius * (1 / (curvature_multiplier + epsilon));
        float screen_aspect = HMSS_GetScreenAspect();
        vec2 extra_curvature_mult = HMSS_GetCurvatureValues() / 2 * 50 + 1;
		mat2x2 pixel_to_video_uv;
		curved_coord = HRG_GetGeomCurvedCoord(	in_coord, 
												global.hmss_curvature_mode, 
												geom_radius_with_mult,
												global.hmss_curvature_3D_view_dist,
												global.hmss_curvature_3D_tilt_angle_x,
												global.hmss_curvature_3D_tilt_angle_y,
												screen_aspect,
												extra_curvature_mult,
												global.SourceSize.xy,
												global.OutputSize.xy,
												pixel_to_video_uv);
	}
	else
	{
		curved_coord = HMSS_Get2DCurvedCoord(in_coord, curvature_multiplier);
	}

	return HMSS_GetPostCurvatureScaledCoord(curved_coord);
}

vec2 HMSS_GetMirrorWrappedCoord(vec2 in_coord)
{
	in_coord = mod(in_coord, 2);
	vec2 ctr_mirror_coord = in_coord - 0.5;

	float mirror_x = clamp(clamp(abs(ctr_mirror_coord.x) - 0.5, 0, 1) * 100000, 0, 1);
	float mirror_y = clamp(clamp(abs(ctr_mirror_coord.y) - 0.5, 0, 1) * 100000, 0, 1);

	ctr_mirror_coord.x = ctr_mirror_coord.x - mirror_x * 2 * sign(ctr_mirror_coord.x) * (abs(ctr_mirror_coord.x) - 0.5);
	ctr_mirror_coord.y = ctr_mirror_coord.y - mirror_y * 2 * sign(ctr_mirror_coord.y) * (abs(ctr_mirror_coord.y) - 0.5);

	return ctr_mirror_coord + 0.5;
}

// TODO to get a better blend at the corners we need to guess the offset from the curved corner will be then blend using this
vec2 HMSS_GetWrappedCurvedCoord(vec2 in_coord, float curvature_multiplier)
{
	return HMSS_GetMirrorWrappedCoord(HMSS_GetCurvedCoord(in_coord, curvature_multiplier));

	// Old version of reflection coord which is actually goes straight out from the side instead of being curved
	// if (curved_coord_distance > 1.41)
	// {
	// 	if (abs(ctr_coord.x) > 0.5)
	// 	{
	// 		ctr_mirror_coord.x = ctr_screen_edge_coord.x - global.hmss_reflection_mirror_stretch * vector_outside.x + sign(ctr_screen_edge_coord.x) * global.hmss_reflection_mirror_offset / aspect_ratio / 100;
	// 	}
	// 	if (abs(ctr_coord.y) > 0.5)
	// 	{
	// 		ctr_mirror_coord.y = ctr_screen_edge_coord.y - global.hmss_reflection_mirror_stretch * vector_outside.y + sign(ctr_screen_edge_coord.x) * global.hmss_reflection_mirror_offset / 100;
	// 	}
		
	// 	return ctr_mirror_coord + 0.5;
	// }

	// vec2 ctr_curved_coord = HMSS_GetCurvedCoord(in_coord, curvature_multiplier) - 0.5;
	// vec2 ctr_blended_coord = ctr_curved_coord;

	// // TODO need to repeat edge when we are in the black edge area
	// 	if ((abs(ctr_curved_coord.x) > 0.5 && abs(ctr_curved_coord.y) > 0.5))
	// 	{
	// 		return ctr_mirror_coord + 0.5;
	// 	}

	// 	if (abs(ctr_curved_coord.x) + global.hmss_tube_black_edge_thickness / 100 / aspect_ratio > 0.5)
	// 	{
	// 		vec2 ctr_curved_screen_edge_coord = HMSS_GetCurvedCoord(vec2(ctr_screen_edge_coord.x, ctr_coord.y) + 0.5, curvature_multiplier) - 0.5;
	// 		float curved_offset = ctr_curved_screen_edge_coord.x - ctr_screen_edge_coord.x;
	// 		ctr_mirror_coord.x = ctr_screen_edge_coord.x - global.hmss_reflection_mirror_stretch * vector_outside.x - 2 * curved_offset + sign(ctr_screen_edge_coord.x) * (2 * global.hmss_tube_black_edge_thickness + global.hmss_reflection_mirror_offset) / 100 / aspect_ratio;
	// 		ctr_mirror_coord.x = clamp(ctr_mirror_coord.x, -0.49999, 0.49999);
	// 	}
	// 	if (abs(ctr_curved_coord.y) + global.hmss_tube_black_edge_thickness / 100 > 0.5)
	// 	{
	// 		vec2 ctr_curved_screen_edge_coord = HMSS_GetCurvedCoord(vec2(ctr_coord.x, ctr_screen_edge_coord.y) + 0.5, curvature_multiplier) - 0.5;
	// 		float curved_offset = ctr_curved_screen_edge_coord.y - ctr_screen_edge_coord.y;
	// 		ctr_mirror_coord.y = ctr_screen_edge_coord.y - global.hmss_reflection_mirror_stretch * vector_outside.y - 2 * curved_offset + sign(ctr_screen_edge_coord.y) * (2 * global.hmss_tube_black_edge_thickness + global.hmss_reflection_mirror_offset) / 100;
	// 		ctr_mirror_coord.y = clamp(ctr_mirror_coord.y, -0.49999, 0.49999);
	// 	}
	// 	if (abs(ctr_curved_coord.x) > 0.5 || abs(ctr_curved_coord.y) > 0.5)
	// 	{
	// 		ctr_blended_coord = HMSS_GetCurvedCoord(ctr_mirror_coord + 0.5, curvature_multiplier) - 0.5;
	// 	}
	// 	if (abs(ctr_curved_coord.x) > 0.5 && abs(ctr_curved_coord.y) > 0.5)
	// 	{
	// 		ctr_blended_coord = ctr_mirror_coord + 0.5;
	// 	}
	
	//return ctr_blended_coord + 0.5;
}

// Returns curved coordinates for the coordinate supplied
// Cached coordinate comes from the mapping pass texture supplied
// x & y are the curved tube coordinates
vec4 HMSS_GetCachedCurvedValues(sampler2D in_mapping_pass, vec2 in_coord, inout vec2 out_curved_coord, inout float outside_tube_mask, inout float edge_mask)
{
	//return HMSS_GetCurvedCoord(HMSS_GetTubeVTexCoord(in_coord), 1);
	vec4 texture_sample = texture(in_mapping_pass, in_coord);
	out_curved_coord = texture_sample.xy;
	outside_tube_mask = texture_sample.z;
	edge_mask = texture_sample.w;
	return texture_sample;
}

// Borrowed from cgwg's crt-geom, under GPL
float HMSS_GetCornerMask(vec2 in_coord, float corner_radius, float edge_sharpness)
// returns 0.0 - 1.0 value used for masking the corner so it looks round
{
	//(0.5 - abs(in_coord - 0.5)) * 2
	vec2 new_coord = min(in_coord, vec2(1.0) - in_coord) * vec2(HMSS_GetScreenAspect(), 1);
	vec2 corner_distance = vec2(max(corner_radius / 1000.0, (1.0 - global.hmss_screen_edge_sharpness * edge_sharpness) * 0.01));
	new_coord = (corner_distance - min(new_coord, corner_distance));
	float distance = sqrt(dot(new_coord, new_coord));

	return clamp((corner_distance.x - distance) * (edge_sharpness * 500 + 100), 0.0, 1.0);
}


vec3 HMSS_RGBtoHSV(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = c.g < c.b ? vec4(c.bg, K.wz) : vec4(c.gb, K.xy);
    vec4 q = c.r < p.x ? vec4(p.xyw, c.r) : vec4(c.r, p.yzx);

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 HMSS_HSVtoRGB(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec4 HMSS_ApplyGamma(vec4 in_color, float in_gamma)
{
	vec3 out_color = pow(in_color.rgb, vec3(1 / in_gamma));
	return vec4(out_color, in_color.a);
}

vec4 HMSS_Linearize(vec4 in_color)
{
	return HMSS_ApplyGamma(in_color, 1 / HMSS_DEFAULT_GAMMA);
}

vec4 HMSS_Delinearize(vec4 in_color)
{
	return HMSS_ApplyGamma(in_color, HMSS_DEFAULT_GAMMA);
}

vec4 HMSS_ApplyBlackLevelGammaLuma(vec4 in_color, float color_is_linear)
{
	// If there is no black level or gamma adjustment return without any adjustment
	if (global.hmss_color_black_level == 0 && global.hmss_color_pre_crt_gamma_adjust == 1)
	{
		return in_color;
	}
	
	vec4 out_color = in_color;

	// Linearize if color isn't linear
	if (color_is_linear == 0)
	{
		out_color = HMSS_Linearize(out_color);
	}

	// Black Level
	out_color -= vec4(global.hmss_color_black_level / 100);
	out_color *= vec4(1.0) / vec4(1.0 - global.hmss_color_black_level / 100);

	// Lumanence
	out_color *= global.hmss_color_luminance / 100;

	// Gamma
	out_color = HMSS_ApplyGamma(out_color, global.hmss_color_pre_crt_gamma_adjust);

	// If color isn't linear put default gamma back on
	if (color_is_linear == 0)
	{
		out_color = HMSS_Delinearize(out_color);
	}

	out_color.w = in_color.w;

	return clamp(out_color, 0, 1);
}

vec2 HMSS_RotateCoordinate(vec2 in_coord, float counterclockwise_turns)
{
	vec2 ctr_coord = in_coord - 0.5;
	// if (counterclockwise_turns == 1)
	// {
		ctr_coord = (1 - counterclockwise_turns) * ctr_coord + counterclockwise_turns * vec2(-ctr_coord.y, ctr_coord.x);
	// }
	// if (counterclockwise_turns == 2)
	// {
	// 	ctr_coord = vec2(-ctr_coord.x, -ctr_coord.y);
	// }
	// if (counterclockwise_turns == 3)
	// {
	// 	ctr_coord = vec2(ctr_coord.y, -ctr_coord.x);
	// }
	return ctr_coord + 0.5;
}

vec2 HMSS_GetCropOverscanCoord(vec2 in_coord){
	vec2 rotated_original_size = HMSS_GetRotatedOriginalSize();
	float ratio_crop_right = global.hmss_crop_overscan_right / rotated_original_size.x;
	float ratio_crop_left = global.hmss_crop_overscan_left / rotated_original_size.x;
	float ratio_crop_top = global.hmss_crop_overscan_top / rotated_original_size.y;
	float ratio_crop_bottom = global.hmss_crop_overscan_bottom / rotated_original_size.y;

	float cropped_range_x = (1.0 - ratio_crop_right) - (0.0 + ratio_crop_left);
	float cropped_range_y = (1.0 - ratio_crop_bottom) - (0.0 + ratio_crop_top);
	vec2 crop_coord = vec2(ratio_crop_left + in_coord.x * cropped_range_x, 
							ratio_crop_top + in_coord.y * cropped_range_y);
	crop_coord = HMSS_RotateCoordinate(crop_coord, global.hmss_rotate_crt_image);
	return crop_coord;
}

vec2 HMSS_GetMirrorWrapCoord(vec2 in_coord)
{
	vec2 ctr_coord = in_coord - 0.5;
	vec2 ctr_mirror_coord = vec2(0,0);

	float x_is_outside = clamp((clamp(abs(ctr_coord.x), 0.5, 1) - 0.5) * 100000, 0, 1);
	ctr_mirror_coord.x = (1 - x_is_outside) * ctr_coord.x + 
						x_is_outside * (ctr_coord.x - 2 * sign(ctr_coord.x) * (abs(ctr_coord.x) - 0.5));

	float y_is_outside = clamp((clamp(abs(ctr_coord.y), 0.5, 1) - 0.5) * 100000, 0, 1);
	ctr_mirror_coord.y = (1 - y_is_outside) * ctr_coord.y + 
						y_is_outside * (ctr_coord.y - 2 * sign(ctr_coord.y) * (abs(ctr_coord.y) - 0.5));

	return ctr_mirror_coord + 0.5;
}

// Check to see if we are in the negative crop area
float HMSS_IsInNegativeCropArea(vec2 in_coord)
{
	float result = abs(clamp(global.hmss_crop_overscan_top, -1, 0) * clamp(in_coord.y, -1, 0)) * 100000 +
				   abs(clamp(global.hmss_crop_overscan_bottom, -1, 0) * (clamp(in_coord.y, 1, 2) - 1)) * 100000 +
				   abs(clamp(global.hmss_crop_overscan_left, -1, 0) * clamp(in_coord.x, -1, 0)) * 100000 +
				   abs(clamp(global.hmss_crop_overscan_right, -1, 0) * (clamp(in_coord.x, 1, 2) - 1)) * 100000;
	return clamp(result, 0, 1);
}

// Texture Sampler function which implements cropping the source image
vec4 HMSS_COMPAT_TEXTURE(sampler2D in_sampler, vec2 in_coord)
{
	vec2 ctr_coord = in_coord - 0.5;
	ctr_coord = clamp(ctr_coord, -0.49999, 0.49999);

	vec2 sample_coord = HMSS_GetCropOverscanCoord(ctr_coord + 0.5);
	vec4 sampled_color = texture(in_sampler, sample_coord);
	vec4 negative_crop_color = vec4(global.hmss_color_negative_crop_brightness / 100, global.hmss_color_negative_crop_brightness / 100, global.hmss_color_negative_crop_brightness / 100, 1);

	float negative_crop = HMSS_IsInNegativeCropArea(sample_coord);

	return negative_crop * negative_crop_color + (1 - negative_crop) * sampled_color;
}

vec4 HMSS_ApplyPhosphorPersistence(vec4 in_color, sampler2D in_feedback_pass, vec2 in_coord)
{
	if (global.hmss_phosphor_persistence == 0) return in_color;

	vec3 Phosphor = global.hmss_phosphor_persistence > 0 ? vec3(0.5, 0.6, 0.8) : vec3(0.5, 0.5, 0.5);

	float delta_time = 5 - 5 * HHLP_EasePowerOut(abs(global.hmss_phosphor_persistence), 2) + 0.1;
	vec4 prev_color = texture(in_feedback_pass, in_coord);
	prev_color.r *= pow(Phosphor.r, delta_time);
	prev_color.g *= pow(Phosphor.g, delta_time);
	prev_color.b *= pow(Phosphor.b, delta_time);

	vec4 out_color = in_color;
	out_color.r = max(prev_color.r, out_color.r);
	out_color.g = max(prev_color.g, out_color.g);
	out_color.b = max(prev_color.b, out_color.b);

	return out_color;
}

// Matrices
const mat3 D65_to_XYZ = mat3 (
           0.4306190,  0.2220379,  0.0201853,
           0.3415419,  0.7066384,  0.1295504,
           0.1783091,  0.0713236,  0.9390944);

const mat3 XYZ_to_D65 = mat3 (
           3.0628971, -0.9692660,  0.0678775,
          -1.3931791,  1.8760108, -0.2288548,
          -0.4757517,  0.0415560,  1.0693490);
		   
const mat3 D50_to_XYZ = mat3 (
           0.4552773,  0.2323025,  0.0145457,
           0.3675500,  0.7077956,  0.1049154,
           0.1413926,  0.0599019,  0.7057489);
		   
const mat3 XYZ_to_D50 = mat3 (
           2.9603944, -0.9787684,  0.0844874,
          -1.4678519,  1.9161415, -0.2545973,
          -0.4685105,  0.0334540,  1.4216174);

// Borrowed from Guest's Guest-Venom d65-d50
vec4 HMSS_ApplyColorTemperature_D65_D50(vec4 in_color)
{
	vec3 color = in_color.rgb;
   
   	color = normalize(pow(color + 1e-4, vec3(global.hmss_color_saturation)))*length(color);
   
	float p = 2.4;
	
	color = pow(color, vec3(p));
	
	vec3 warmer = D50_to_XYZ*color;
	warmer = XYZ_to_D65*warmer;
	
	vec3 cooler = D65_to_XYZ*color;
	cooler = XYZ_to_D50*cooler;
	
	float m = abs(global.hmss_color_temperature)/100.0;
	
	vec3 comp = (global.hmss_color_temperature < 0.0) ? cooler : warmer;
	
	color = mix(color, comp, m);

	color = pow(color, vec3(1.0/p));	
	
	return vec4(color, 1.0);
}

float HMSS_GetVignetteFactor(vec2 coord, float amount)
{
	float orig_mamehlsl_amount = amount;
	vec2 ctr_coord = coord - 0.5;

	float vignette_length = length(ctr_coord * vec2(0.5 * global.OutputSize.x/global.OutputSize.y + 0.5, 1));
	float vignette_blur = (orig_mamehlsl_amount * 0.75) + 0.25;

	// 0.5 full screen fitting circle
	float vignette_radius = 1.0 - (orig_mamehlsl_amount * 0.25);
	float vignette = smoothstep(vignette_radius, vignette_radius - vignette_blur, vignette_length);

	float vignette_multiplier = smoothstep(0, 0.05, amount);
	return 1 - vignette_multiplier + vignette * vignette_multiplier;
}

float HMSS_GetScreenVignetteFactor(vec2 coord, float amount)
{
	coord = (coord - 0.5) * 0.999 + 0.5;
    coord *=  1.0 - coord.yx;
    
    float vignette = coord.x * coord.y * 20; // multiply with sth for intensity
    
    vignette = pow(vignette, amount * 3); // change pow for modifying the extend of the  vignette
	float vignette_multiplier = smoothstep(0, 0.05, amount);
	if (amount < 0.01) return 1;
	else return vignette;
}

// Torridgristle - ScanlineSimple pass - Public domain
vec4 HMSS_AddResIndependentScanlines(vec4 in_color, vec2 in_coord)
{
	if (global.hmss_res_independent_scanline_size < 0.5) return in_color;

	float scanline_size = global.OutputSize.y > 1800 ? 2 * global.hmss_res_independent_scanline_size : global.hmss_res_independent_scanline_size;

	float pi = 3.141592654;
	vec2 screen_size = global.OutputSize.xy * HMSS_GetScreenScale();

	float Scanline = mod(in_coord.y * screen_size.y, scanline_size) / scanline_size;
	Scanline = 1 - abs(Scanline - 0.5) * 2.;
	Scanline = 1 - pow(1 - Scanline, 2);

	return in_color * Scanline;
}

vec4 HMSS_GetPostCrtPreppedColor(vec2 screen_curved_coord, vec4 in_color, float encoded_input_gamma, float output_with_gamma)
{
	vec4 out_color = in_color;
	
	// Put the color in linear space by correcting for the encoded gamma
	if (encoded_input_gamma != 1)
	{
		out_color = HMSS_ApplyGamma(in_color, encoded_input_gamma);
	}

	vec2 mirrored_screen_coord = HMSS_GetMirrorWrappedCoord(screen_curved_coord);
	float vignette_factor = HMSS_GetScreenVignetteFactor(mirrored_screen_coord, global.hmss_screen_vignette);
	
	// TODO Screen Edge Sharpness should be applied here instead of in the mega bezel shader
	HMSS_GetCornerMask(screen_curved_coord, global.hmss_screen_corner_radius, global.hmss_screen_edge_sharpness);

	// If this is called from the glass preset we don't want the vignette to affect mirrored area
	#ifdef GLASS_PRESET
		float screen_mask = HMSS_GetCornerMask((screen_curved_coord - 0.5) * 0.999 + 0.5, global.hmss_screen_corner_radius, 0.9);
		vignette_factor = 1 - ((1 - vignette_factor) * screen_mask);
	#endif

	// If we are not using this with the bezel we want
	#ifdef MASK_OUTSIDE_SCREEN
		float screen_mask = HMSS_GetCornerMask((screen_curved_coord - 0.5) * 0.999 + 0.5, global.hmss_screen_corner_radius, 0.9);
		vignette_factor = vignette_factor * screen_mask;
	#endif

	out_color = HMSS_AddResIndependentScanlines(out_color, screen_curved_coord);

	out_color *= vignette_factor;

	// Apply the final Gamma
	if (output_with_gamma > 0.5)
	{
		out_color = HMSS_ApplyGamma(out_color, global.hmss_color_crt_gamma);
	}

	return out_color;
}