/*   
hsm-mega-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

//#define TELMO_TEST

#include "hsm-helper-functions.inc"
//#include "hsm-royale-geometry-functions.inc"

// Screen Scale Required Parameters
#pragma parameter hmss_mega_screen_scale_on				"___HSM MEGA BEZEL__ V.2020-04-05 -SCREEN SCALE ON" 0 0 1 1
#pragma parameter hmss_screen_scale_debug				"[SCREEN SCALE]  Screen Scale Debug" 0 0 1 1
#pragma parameter hmss_screen_scale_only             	"[SCREEN SCALE]  Screen Scale Only (No Bezel in Preset)" 0 0 1 1

#pragma parameter hmss_rotate_crt_image					"[SCALING]  Rotate CRT Image"  0 0 1 1
//#pragma parameter hmss_flip_screen_vertical			"[SCALING]  Flip Screen Vertical"  0 0 1 1
#pragma parameter hmss_aspect_ratio_mode 				"[SCALING]  Aspect Ratio Mode (0:Auto, 1:Horizontal, 2:Vert)"  0 0 2 1
#pragma parameter hmss_screen_aspect_ratio				"[SCALING]  Screen Aspect Ratio"  1.3333 0 3 0.002

#pragma parameter hmss_integer_scale_mode 				"[SCALING]  Integer Scale Mode - 0:Off, 1-ShortAxis, 2-BothAxes" 0 0 2 1
// Non integer scale is set to 82.97 so that cores which output 224px will have integer scale by default
// This is 8x integer scale at 3840x2160 and 6x integer scale at 1920x1080
#pragma parameter hmss_non_integer_scale 				"[SCALING]  Non-Integer Scale %" 82.97 1 200 0.2
#pragma parameter hmss_int_scale_multiple_offset 		"[SCALING]  Int Scale Multiple Offset" 0 -20 20 1
#pragma parameter hmss_int_scale_border_min_height 		"[SCALING]  Int Scale Border Min Height %" 5.5 -20 20 0.5

#pragma parameter hmss_scanline_direction 				"[SCANLINES]  Scanline Dir Guest-Venom (0:Auto, 1:Horiz, 2:Vert)"  0 0 2 1

#pragma parameter hmss_position_offset_x 				"[POSITION]  Position Offset X" 0 -100 100 0.1
#pragma parameter hmss_position_offset_y 				"[POSITION]  Position Offset Y" 0 -100 100 0.1

#pragma parameter hmss_crop_overscan_top 				"[CROPPING]  Crop Overscan Top" 0 -256 256 1
#pragma parameter hmss_crop_overscan_bottom 			"[CROPPING]  Crop Overscan Bottom" 0 -256 256 1
#pragma parameter hmss_crop_overscan_left 				"[CROPPING]  Crop Overscan Left" 0 -256 256 1
#pragma parameter hmss_crop_overscan_right 				"[CROPPING]  Crop Overscan Right" 0 -256 256 1

//#pragma parameter hmss_curvature_type 					"[CURVATURE]  Curvature Mode (0:2D 1-3:Geom)" 0 0 3
#pragma parameter hmss_curvature_on_long_axis 			"[CURVATURE]  Curvature on Long Axis (default 3)" 0 0 12.5 0.2
#pragma parameter hmss_curvature_on_short_axis 			"[CURVATURE]  Curvature on Short Axis (default 4)" 0 0 12.5 0.2

#pragma parameter hmss_corner_radius 					"[SCREEN EDGE]  Screen Corner Radius (Default 10)" 0 0 70 1
#pragma parameter hmss_screen_edge_sharpness 			"[SCREEN EDGE]  Screen Edge Sharpness" 0.4 0 1 0.01
#pragma parameter hmss_tube_black_edge_thickness 		"[SCREEN EDGE]  Tube Black Edge Thickness" 1.2 -2 8 0.05

#pragma parameter hmss_pre_crt_black_level 				"[COLOR]  Pre-CRT Black Level" 0 -30 30 0.05-
#pragma parameter hmss_pre_crt_gamma					"[COLOR]  Pre-CRT Gamma" 1 0.01 2 0.01
#pragma parameter hmss_pre_crt_luminance				"[COLOR]  Pre-CRT Luminance" 1 0 2 0.01
#pragma parameter hmss_post_crt_gamma					"[COLOR]  Post-CRT Gamma" 1 0.01 2 0.01
#pragma parameter hmss_negative_crop_brightness			"[COLOR]  Negative Crop Brightness" 0 0 20 0.02

#pragma parameter hag_afterglow_amount                  "[AFTERGLOW]  Amount"        0.07 0.0 1.0 0.01
#pragma parameter hag_afterglow_persistence             "[AFTERGLOW]  Persistence"   0.05 0.0 1.0 0.01
#pragma parameter hag_afterglow_saturation              "[AFTERGLOW]  Saturation"    0.10 0.0 1.0 0.01

// #pragma parameter hmss_reflection_mirror_stretch 		"[REFLECTION]  Mirror Stretch" 1.1 0.1 5 0.02
// #pragma parameter hmss_reflection_mirror_offset 		"[REFLECTION]  Mirror Offset" -2 -100 100 0.1
// Screen Scale Required Parameters End

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

float HMSS_GetIsCroppedOriginalSizeVertical()
{
	vec2 cropped_original_size = HMSS_GetCroppedOriginalSize();
	float cropped_aspect_ratio = cropped_original_size.x/cropped_original_size.y;
	return cropped_aspect_ratio < 1 ? 1 : 0;
}

float HMSS_GetScreenAspectRatio()
{
	float horizontal_aspect_ratio = global.hmss_screen_aspect_ratio;
	float vertical_aspect_ratio = 1.0 / global.hmss_screen_aspect_ratio;
	
	float auto_screen_aspect_ratio = HMSS_GetIsCroppedOriginalSizeVertical() > 0.5 ? vertical_aspect_ratio : horizontal_aspect_ratio;
	return global.hmss_aspect_ratio_mode < 1 ? auto_screen_aspect_ratio : (global.hmss_aspect_ratio_mode < 2 ? horizontal_aspect_ratio : vertical_aspect_ratio);
}

float HMSS_GetFinalViewportAspectRatio()
{
	return global.FinalViewportSize.x / global.FinalViewportSize.y;
}

float HMSS_GetUseVerticalScanlines()
{
	float auto_use_vert_scanlines = HMSS_GetScreenAspectRatio() < 1 ? 1 : 0;
	return global.hmss_scanline_direction < 1 ? auto_use_vert_scanlines : (global.hmss_scanline_direction < 2 ? 0 : 1);
}

float HMSS_GetScreenInverseAspectRatio()
{
	float horizontal_aspect_ratio = global.hmss_screen_aspect_ratio;
	float vertical_aspect_ratio = 1.0 / global.hmss_screen_aspect_ratio;

	float auto_screen_aspect_ratio = HMSS_GetIsCroppedOriginalSizeVertical() > 0.5 ? vertical_aspect_ratio : horizontal_aspect_ratio;
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
		float aspect_ratio = HMSS_GetScreenAspectRatio();
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

vec2 HMSS_GetLongShortAxisCurvatureValues()
{
	return vec2(global.hmss_curvature_on_long_axis / 100, global.hmss_curvature_on_short_axis / 100);
}

vec2 HMSS_GetCurvatureValues()
{
	vec2 curvature_values = HMSS_GetScreenAspectRatio() < 1 ? vec2(global.hmss_curvature_on_short_axis / 100, global.hmss_curvature_on_long_axis / 100 ) 
														: vec2(global.hmss_curvature_on_long_axis / 100, global.hmss_curvature_on_short_axis / 100 );
	return curvature_values;
}

// Torridgristle's curvature
vec2 HMSS_GetCurvedCoord(vec2 in_coord, float curvature_multiplier)
{
	vec2 ctr_coord = in_coord - 0.5;
	vec2 curvature_values = HMSS_GetCurvatureValues();
	vec2 distortion = curvature_values * curvature_multiplier * 15.0;
	vec2 ctr_curved_coord = in_coord * 2.0 - 1.0;
	float curved_coord_distance = sqrt(ctr_curved_coord.x * ctr_curved_coord.x + ctr_curved_coord.y * ctr_curved_coord.y);
	ctr_curved_coord = ctr_curved_coord / curved_coord_distance;
	ctr_curved_coord = ctr_curved_coord * (1.0 - pow(vec2(1.0 - (curved_coord_distance / 1.4142135623730950488016887242097)), (1.0 / (1.0 + distortion * 0.2))));
	ctr_curved_coord = ctr_curved_coord / clamp(1.0 - pow(vec2(0.29289321881345247559915563789515), (1.0 / (vec2(1.0) + distortion * 0.2))), 0.0001, 10);
	ctr_curved_coord = ctr_curved_coord * 0.5;

	return clamp(ctr_curved_coord, -1, 1) + 0.5;
}

// TODO to get a better blend at the corners we need to guess the offset from the curved corner will be then blend using this
vec2 HMSS_GetWrappedCurvedCoord(vec2 in_coord, float curvature_multiplier)
{
	float aspect_ratio = HMSS_GetScreenAspectRatio();
	vec2 ctr_coord = in_coord - 0.5;
	vec2 ctr_screen_edge_coord = clamp(ctr_coord, -0.5, 0.5);
	vec2 vector_outside = ctr_coord - ctr_screen_edge_coord;

	vec2 ctr_coord_0_1 = ctr_coord * 2.0;
	float curved_coord_distance = sqrt(ctr_coord_0_1.x * ctr_coord_0_1.x + ctr_coord_0_1.y * ctr_coord_0_1.y);
	vec2 ctr_mirror_coord = ctr_coord;

	// Only curve the coordinate if the coordinate is inside the sphere where the coordinate space is continuous
	float max_curved_range = 1.41;
	if (curved_coord_distance < max_curved_range)
	{
		ctr_mirror_coord = HMSS_GetCurvedCoord(in_coord, curvature_multiplier) - 0.5;

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

			ctr_mirror_coord = blend_to_uncurved * ctr_coord + (1 - blend_to_uncurved) * ctr_mirror_coord;
		}
	}
	if (abs(ctr_mirror_coord.x) > 0.5)
	{
		ctr_mirror_coord.x = ctr_mirror_coord.x - 2 * sign(ctr_mirror_coord.x) * (abs(ctr_mirror_coord.x) - 0.5);
	}
	if (abs(ctr_mirror_coord.y) > 0.5)
	{
		ctr_mirror_coord.y = ctr_mirror_coord.y - 2 * sign(ctr_mirror_coord.y) * (abs(ctr_mirror_coord.y) - 0.5);
	}

	return (ctr_mirror_coord + 0.5);

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

// Borrowed from cgwg's crt-geom, under GPL
float HMSS_GetCornerMask(vec2 in_coord, float corner_radius, float edge_sharpness)
// returns 0.0 - 1.0 value used for masking the corner so it looks round
{
	vec2 new_coord = min(in_coord, vec2(1.0) - in_coord) * vec2(HMSS_GetFinalViewportAspectRatio() / HMSS_GetScreenAspectRatio(), 1);
	vec2 corner_distance = vec2(max(corner_radius / 1000.0, max((1.0 - global.hmss_screen_edge_sharpness * edge_sharpness) * 0.01, 0.002)));
	new_coord = (corner_distance - min(new_coord, corner_distance));
	float distance = sqrt(dot(new_coord, new_coord));

	return clamp((corner_distance.x - distance) * (edge_sharpness * 500 + 100), 0.0, 1.0);
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

vec4 HMSS_ApplyBlackLevelGammaLuminance(vec4 in_color, float color_is_linear)
{
	if (color_is_linear == 0)
	{
		in_color = HHLP_Linearize(in_color);
	}

	vec3 rgb_color = in_color.rgb;
	// Black Level Adjustment
	rgb_color -= vec3(global.hmss_pre_crt_black_level / 100);
	rgb_color *= vec3(1.0) / vec3(1.0 - global.hmss_pre_crt_black_level / 100);

	// Gamma
	rgb_color = pow(rgb_color, 1.0 / vec3(global.hmss_pre_crt_gamma));

	// Luminance
	rgb_color = clamp(HMSS_HSVtoRGB(HMSS_RGBtoHSV(clamp(rgb_color, 0, 1)) * vec3(1, 1, global.hmss_pre_crt_luminance)), 0.0, 1.0);

	vec4 out_color = vec4(rgb_color, 1);

	if (color_is_linear == 0)
	{
		out_color = HHLP_Delinearize(out_color);
	}

	return out_color;
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

	#ifdef TELMO_TEST
		if (HMSS_IsInNegativeCropArea(sample_coord) == 1)
		{
			return vec4(global.hmss_negative_crop_brightness / 100, global.hmss_negative_crop_brightness / 100, global.hmss_negative_crop_brightness / 100, 1);
		}
		else
		{
			return texture(in_sampler, sample_coord);
		}
	#else
		vec4 sampled_color = texture(in_sampler, sample_coord);
		vec4 negative_crop_color = vec4(global.hmss_negative_crop_brightness / 100, global.hmss_negative_crop_brightness / 100, global.hmss_negative_crop_brightness / 100, 1);

		float negative_crop = HMSS_IsInNegativeCropArea(sample_coord);

		return negative_crop * negative_crop_color + (1 - negative_crop) * sampled_color;
	#endif
}