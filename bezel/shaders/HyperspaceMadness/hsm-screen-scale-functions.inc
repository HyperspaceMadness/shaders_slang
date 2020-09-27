/*   
hsm-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

#include "hsm-helper-functions.inc"
#include "hsm-royale-geometry-functions.inc"

vec2 HSS_GetRawOriginalSize()
{
	return global.OriginalSize.xy;
}

vec2 HSS_GetRotatedRawOriginalSize()
{
	return HSS_ROTATE_CORE_IMAGE * global.OriginalSize.yx + (1 - HSS_ROTATE_CORE_IMAGE) * global.OriginalSize.xy;
}

float HSS_GetSplitScreenAmount()
{
	#ifdef HSM_SPLIT_SCREEN_PRESET
		vec2 original_size = global.OriginalSize.xy;
		float is_horizontal = HHLP_IsOverValue(original_size.x / original_size.y, 1);

		// Split screen amount should be smaller when the aspect is horizontal
		return is_horizontal * HSS_SPLIT_SCREEN_AMOUNT / 2 + (1 - is_horizontal) * HSS_SPLIT_SCREEN_AMOUNT;
	#else
		return 0;
	#endif
}

vec2 HSS_GetCroppedSize(vec2 in_size){
	return vec2(in_size.x - HSS_CROP_OVERSCAN_RIGHT - HSS_CROP_OVERSCAN_LEFT,
				in_size.y - HSS_CROP_OVERSCAN_TOP - HSS_CROP_OVERSCAN_BOTTOM);
}

// Get the original size with split area added
vec2 HSS_GetOriginalSize()
{
	vec2 original_size = global.OriginalSize.xy;

	#ifdef HSM_SPLIT_SCREEN_PRESET
		// Positive split amount values are a vertical split
		float is_horizontal = HHLP_IsOverValue(original_size.x / original_size.y, 1);

		float split_screen_amount = HSS_GetSplitScreenAmount();

		original_size.x += is_horizontal * clamp(split_screen_amount, 0, 512);
		original_size.y += (1 - is_horizontal) * clamp(split_screen_amount, 0, 512);
	#endif

	return original_size;
}

vec2 HSS_GetRotatedOriginalSize()
{
	vec2 original_size = HSS_GetOriginalSize();
	return HSS_ROTATE_CORE_IMAGE * original_size.yx + (1 - HSS_ROTATE_CORE_IMAGE) * original_size.xy;
}

vec2 HSS_GetCroppedRotatedOriginalSize()
{
	return HSS_GetCroppedSize(HSS_GetRotatedOriginalSize());
}

float HSS_GetIsOriginalSizeVertical()
{
	vec2 rotated_original_size = HSS_GetRotatedOriginalSize();
	float aspect_ratio = rotated_original_size.x / rotated_original_size.y;
	return aspect_ratio < 1 ? 1 : 0;
}

bool HSS_MatchResolution(vec2 in_res, vec2 match_res)
{
	return (in_res == match_res);
}

// Snap to integer scale if within 10%
float HSS_GetScreenAspect()
{
	float epsilon = 0.002;
	vec2 raw_original_size = HSS_GetRawOriginalSize();
	vec2 rotated_original_size = HSS_GetRotatedOriginalSize();
	float core_aspect_ratio = rotated_original_size.x / rotated_original_size.y;
	float core_aspect_horizontal = (core_aspect_ratio < 1) ? 1 / core_aspect_ratio : core_aspect_ratio;
	float horizontal_aspect = 0;

	vec2 nintendo_gameboy_advance_res = 	vec2(240, 160);
	vec2 nintendo_gameboy_res = 			vec2(160, 144);
	vec2 nintendo_ds_top_bottom_res = 		vec2(256, 384);
	vec2 nintendo_ds_side_by_side_res = 	vec2(512, 192);
	vec2 nintendo_3ds_top_bottom_res = 		vec2(400, 480);
	vec2 nintendo_3ds_side_by_side_res = 	vec2(720, 240);
	vec2 atari_lynx_res = 					vec2(160, 102);
	vec2 atari_2600_res = 					vec2(160, 228);
	vec2 atari_2600_crop_res = 				vec2(152, 228);
	
	if (HSS_ASPECT_RATIO_MODE == 0)
	{
		// If the vertical res is larger than 500 is is probably a modern square pixel resolution
		if (raw_original_size.y > 500) horizontal_aspect = core_aspect_horizontal;
		else if (HSS_MatchResolution(nintendo_gameboy_advance_res, 	raw_original_size)) horizontal_aspect = core_aspect_horizontal;
		else if (HSS_MatchResolution(nintendo_gameboy_res, 			raw_original_size)) horizontal_aspect = core_aspect_horizontal;
		else if (HSS_MatchResolution(nintendo_ds_top_bottom_res, 	raw_original_size)) horizontal_aspect = core_aspect_horizontal;
		else if (HSS_MatchResolution(nintendo_ds_side_by_side_res, 	raw_original_size)) horizontal_aspect = core_aspect_horizontal;
		else if (HSS_MatchResolution(nintendo_3ds_top_bottom_res, 	raw_original_size)) horizontal_aspect = core_aspect_horizontal;
		else if (HSS_MatchResolution(nintendo_3ds_side_by_side_res, raw_original_size)) horizontal_aspect = core_aspect_horizontal;
		else if (HSS_MatchResolution(atari_lynx_res, 				raw_original_size)) horizontal_aspect = core_aspect_horizontal;
		else if (HSS_MatchResolution(atari_2600_res, 				raw_original_size)) horizontal_aspect = 1.333;
		else if (HSS_MatchResolution(atari_2600_crop_res, 			raw_original_size)) horizontal_aspect = 1.333;
		// Fall back to the explicit ratio
		else horizontal_aspect = HSS_ASPECT_RATIO_EXPLICIT;
	}
	else 
		if (HSS_ASPECT_RATIO_MODE == 1) horizontal_aspect = HSS_ASPECT_RATIO_EXPLICIT;
		else if (HSS_ASPECT_RATIO_MODE == 2) horizontal_aspect = 1.3333;
		else if (HSS_ASPECT_RATIO_MODE == 3) horizontal_aspect = 1.5;
		else if (HSS_ASPECT_RATIO_MODE == 4) horizontal_aspect = 1.7777;
		else if (HSS_ASPECT_RATIO_MODE == 5) horizontal_aspect = core_aspect_horizontal;
		else if (HSS_ASPECT_RATIO_MODE == 6) horizontal_aspect = global.FinalViewportSize.x / global.FinalViewportSize.y;
		else horizontal_aspect = 1.333;

	// // Version of the above as straight computation to test performance, but actually reduces performance from 160fps to 150fps
	// // If the vertical res is larger than 500 is is probably a modern square pixel resolution
	// float is_square_pixel_res = 	HHLP_IsOverValue(raw_original_size.y, 500) +
	// 								HHLP_EqualsResolution(nintendo_gameboy_advance_res, raw_original_size) +
	// 								HHLP_EqualsResolution(nintendo_gameboy_res, raw_original_size) +
	// 								HHLP_EqualsResolution(nintendo_ds_top_bottom_res, raw_original_size) +
	// 								HHLP_EqualsResolution(nintendo_ds_side_by_side_res, raw_original_size) +
	// 								HHLP_EqualsResolution(nintendo_3ds_top_bottom_res, raw_original_size) +
	// 								HHLP_EqualsResolution(nintendo_3ds_side_by_side_res, raw_original_size) +
	// 								HHLP_EqualsResolution(atari_lynx_res, raw_original_size);
    //
	// horizontal_aspect = HHLP_EqualsValue(HSS_ASPECT_RATIO_MODE, 0, epsilon) * (is_square_pixel_res * core_aspect_horizontal + 
	// 																			(1 - is_square_pixel_res) * HSS_ASPECT_RATIO_EXPLICIT) +
	// 					HHLP_EqualsValue(HSS_ASPECT_RATIO_MODE, 1, epsilon) * HSS_ASPECT_RATIO_EXPLICIT +
	// 					HHLP_EqualsValue(HSS_ASPECT_RATIO_MODE, 2, epsilon) * 1.3333 +
	// 					HHLP_EqualsValue(HSS_ASPECT_RATIO_MODE, 3, epsilon) * 1.5 +
	// 					HHLP_EqualsValue(HSS_ASPECT_RATIO_MODE, 4, epsilon) * 1.7777 +
	// 					HHLP_EqualsValue(HSS_ASPECT_RATIO_MODE, 5, epsilon) * core_aspect_horizontal +
	// 					HHLP_EqualsValue(HSS_ASPECT_RATIO_MODE, 6, epsilon) * global.FinalViewportSize.x / global.FinalViewportSize.y;

	// Find what the vertical aspect would be, either the current horizontal_aspect (if it's already vertical)
	// Or changing the horizontal aspect to vertical by taking the reciprocal
	float vertical_aspect = 1 / horizontal_aspect;
	float final_orientation = HSS_ASPECT_RATIO_ORIENTATION;

	if (HSS_ASPECT_RATIO_ORIENTATION < 0.5)
	{
		// Catch for Atari 2600 - Stella Emulator which would otherwise show up as a vertical aspect ratio
		if (HSS_MatchResolution(atari_2600_res, raw_original_size) || (HSS_MatchResolution(atari_2600_crop_res, raw_original_size))) final_orientation = 1;
		else
		{
			final_orientation = (HSS_GetIsOriginalSizeVertical() > 0.5) ? 2 : 1;
		}
	}
	
	float final_aspect_ratio = (final_orientation < 1.5) ? horizontal_aspect : vertical_aspect;

	return final_aspect_ratio;
}

float HSS_GetFinalViewportAspectRatio()
{
	return global.FinalViewportSize.x / global.FinalViewportSize.y;
}

float HSS_GetUseVerticalScanlines(float screen_aspect)
{
	float auto_use_vert_scanlines = screen_aspect < 1 ? 1 : 0;
	#ifdef HSM_SPLIT_SCREEN_PRESET
		auto_use_vert_scanlines = 0;
	#endif
	return HSS_SCANLINE_DIRECTION < 1 ? auto_use_vert_scanlines : (HSS_SCANLINE_DIRECTION < 2 ? 0 : 1);
}

vec2 HSS_GetCoreSamplingResMult()
{
	vec2 original_size = HSS_GetRotatedRawOriginalSize();
	float use_vert_scanlines = HSS_GetUseVerticalScanlines(original_size.x/original_size.y);
	vec2 sampling_mult = (1 - use_vert_scanlines) * vec2(HSS_CORE_RES_SAMPLING_MULT_SCANLINE_DIR, HSS_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR) + 
							  use_vert_scanlines *  vec2(HSS_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR, HSS_CORE_RES_SAMPLING_MULT_SCANLINE_DIR);
	return sampling_mult;
}

vec2 HSS_GetRotatedOriginalSizeWithCoreResMult()
{
	vec2 original_size = HSS_GetOriginalSize();
	vec2 sampling_mult = HSS_GetCoreSamplingResMult();

	vec2 sampling_size = vec2(floor(sampling_mult.x * original_size.x), floor(sampling_mult.y * original_size.y));

	return HSS_ROTATE_CORE_IMAGE * sampling_size.yx + (1 - HSS_ROTATE_CORE_IMAGE) * sampling_size.xy;
}

vec2 HSS_GetCroppedRotatedOriginalSizeWithCoreResMult()
{
	return HSS_GetCroppedSize(HSS_GetRotatedOriginalSizeWithCoreResMult());
}

float HSS_GetScreenInverseAspectRatio()
{
	float horizontal_aspect = HSS_ASPECT_RATIO_EXPLICIT;
	float vertical_aspect = 1.0 / HSS_ASPECT_RATIO_EXPLICIT;

	float auto_screen_aspect_ratio = HSS_GetIsOriginalSizeVertical() > 0.5 ? vertical_aspect : horizontal_aspect;
	return HSS_ASPECT_RATIO_ORIENTATION < 1 ? auto_screen_aspect_ratio : (HSS_ASPECT_RATIO_ORIENTATION < 2 ? horizontal_aspect : vertical_aspect);
}

// HSS_SNAP_TO_INT_SCALE_TOLERANCE
vec2 HSS_GetScreenScale(float screen_aspect)
{
	if (HSS_ASPECT_RATIO_MODE > 5.5)
	{
		return vec2(1, 1);
	}
	else
	{
		float output_aspect_ratio = HSS_GetFinalViewportAspectRatio();

		// Get Original size with cropping applied as this affects the integer scale
		vec2 cropped_original_size = HSS_GetCroppedRotatedOriginalSize();

		bool viewport_is_vertical = (global.FinalViewportSize.x < global.FinalViewportSize.y);

		// If we are using non-integer scale return
		float screen_height = HSS_NON_INTEGER_SCALE / 100;
		if (HSS_INT_SCALE_MODE == 0)
		{
			if (viewport_is_vertical || screen_aspect > output_aspect_ratio)
			{
				float diagonal_length = HSS_NON_INTEGER_SCALE / 100 * output_aspect_ratio;
				screen_height = (diagonal_length * 1) / sqrt(screen_aspect * screen_aspect + 1 * 1);
			}

			// If the integer tolerance is greater than zero see if we can snap to the nearest integer multiple
			if (HSS_SNAP_TO_INT_SCALE_TOLERANCE > 0)
			{
				float integer_scale_multiple_vert = screen_height * global.FinalViewportSize.y / cropped_original_size.y;
				float int_scale_remainder = fract(integer_scale_multiple_vert);
				int_scale_remainder = (int_scale_remainder < 1 - int_scale_remainder) ? int_scale_remainder : 1 - int_scale_remainder;
				float remainder_percent_of_screen_height = (int_scale_remainder * cropped_original_size.y) / (screen_height * global.FinalViewportSize.y);
				if (remainder_percent_of_screen_height < HSS_SNAP_TO_INT_SCALE_TOLERANCE)
				{
					integer_scale_multiple_vert = round(integer_scale_multiple_vert);
					screen_height = integer_scale_multiple_vert * cropped_original_size.y / global.FinalViewportSize.y;
				}
			}

			return vec2(screen_aspect / output_aspect_ratio, 1) * screen_height;
		}

		// Get the maximum height that the integer scale needs to fit into
		float viewport_res_y_without_border = global.FinalViewportSize.y - 2 * (HSS_INT_SCALE_BORDER_MIN_HEIGHT / 100) * global.FinalViewportSize.y;
		float viewport_res_x_without_border = global.FinalViewportSize.x - 2 * (HSS_INT_SCALE_BORDER_MIN_HEIGHT / 100) * global.FinalViewportSize.x;

		// If the viewport is taller than it is wide then get the height from the corresponding available width
		if (viewport_is_vertical) viewport_res_y_without_border = viewport_res_x_without_border / screen_aspect;

		// If the screen is too high
		if ((viewport_res_y_without_border * screen_aspect) > global.FinalViewportSize.x)
		{
			viewport_res_y_without_border = (1 - 2 * HSS_INT_SCALE_BORDER_MIN_HEIGHT / 100) * global.FinalViewportSize.x / screen_aspect; 
		}

		float integer_scale_multiple_vert = clamp(floor(viewport_res_y_without_border / cropped_original_size.y) + HSS_INT_SCALE_MULTIPLE_OFFSET, 1, 100);
		float integer_scale_vert = integer_scale_multiple_vert * cropped_original_size.y / global.FinalViewportSize.y;

		// Get the horizontal scale from the vertical scale and aspect ratio
		float integer_scale_horz_from_aspect = screen_aspect / output_aspect_ratio * integer_scale_vert;

		// Get the scale as a multiple of the original x-size
		float integer_scale_multiple_horz = integer_scale_horz_from_aspect * global.FinalViewportSize.x / cropped_original_size.x;

		// If we are using vertical scanlines or integer scale is set to both directions make the horizontal multiple an integer
		float final_int_scale_mode = HSS_INT_SCALE_MODE;
		if (HSS_INT_SCALE_MODE > 0.5)
		{
			if (HSS_GetUseVerticalScanlines(screen_aspect) == 1 || HSS_INT_SCALE_MODE == 2)
			{
				integer_scale_multiple_horz = round(integer_scale_multiple_horz);
				final_int_scale_mode = 2;
			}
		}

		float both_axes = clamp((final_int_scale_mode - 1) * 10000, 0, 1);
		integer_scale_multiple_vert += both_axes * abs(clamp((screen_aspect - 1) * 10000, -1, 0)) * HSS_INT_SCALE_MULTIPLE_OFFSET_LONG;
		integer_scale_multiple_horz += both_axes * abs(clamp((screen_aspect - 1) * 10000,  0, 1)) * HSS_INT_SCALE_MULTIPLE_OFFSET_LONG;

		integer_scale_vert = integer_scale_multiple_vert * cropped_original_size.y / global.FinalViewportSize.y;
		float integer_scale_horz = integer_scale_multiple_horz * cropped_original_size.x / global.FinalViewportSize.x;

		return vec2(integer_scale_horz, integer_scale_vert);
	}
}

vec2 HSS_GetScreenSize(vec2 screen_scale)
{
	vec2 screen_size = global.FinalViewportSize.xy * screen_scale;
	// Round this so we get proper integers
	screen_size = vec2(round(screen_size.x), round(screen_size.y));
	return screen_size;
}

// Returns Diagonal Screen scale relative to the viewport height
float HSS_GetScreenDiagonalScale(vec2 screen_scale)
{
	float screen_scale_x_compensated = screen_scale.x / (global.FinalViewportSize.x/global.FinalViewportSize.y);
	return sqrt(screen_scale_x_compensated * screen_scale_x_compensated + screen_scale.y * screen_scale.y);
}

vec2 HSS_GetIntegerScaleMult(vec2 screen_size)
{
	float epsilon = 0.002;
	vec2 integer_scale = screen_size / HSS_GetCroppedRotatedOriginalSize();
	integer_scale = vec2(fract(integer_scale.x + 0.001) < epsilon ? round(integer_scale.x) : integer_scale.x,
						 fract(integer_scale.y + 0.001) < epsilon ? round(integer_scale.y) : integer_scale.y);
	return integer_scale;
}

vec2 HSS_GetScreenScaleWithEdgeHeight(float edge_height, vec2 screen_scale)
// Edge Height is a 0 to 1 percentage of the screen height
{
	float output_aspect_ratio = global.FinalViewportSize.x / global.FinalViewportSize.y;
	
	float aspect_ratio = screen_scale.x / screen_scale.y;

	vec2 edge_width_height_as_scale = vec2(0, 0);
	edge_width_height_as_scale.x = 1 + (edge_height / screen_scale.y) / aspect_ratio / output_aspect_ratio;
	edge_width_height_as_scale.y = 1 + edge_height / screen_scale.y;

	return screen_scale * edge_width_height_as_scale;
}

vec2 HSS_GetInverseScaledCoord(vec2 in_coord, vec2 in_scale)
{
	vec2 middle = vec2(0.49999, 0.49999);
	vec2 diff = in_coord.xy - middle;
	vec2 screen_inverse_scale = 1.0 / in_scale;
	vec2 scaled_coord = middle + diff * screen_inverse_scale;

	return scaled_coord;
}

vec2 HSS_GetPositionOffset()
{
	float output_aspect_ratio = global.FinalViewportSize.x / global.FinalViewportSize.y;
	vec2 pos_offset = vec2(HSS_POSITION_OFFSET_X / output_aspect_ratio, HSS_POSITION_OFFSET_Y);
	return pos_offset;
}

vec2 HSS_GetCoordWithPositionOffset(vec2 in_coord)
{
	return in_coord - HSS_GetPositionOffset();
}

vec2 HSS_GetVTexCoordWithArgs(vec2 in_coord, vec2 in_scale, vec2 position_offset)
{
	return HSS_GetInverseScaledCoord(HSS_GetCoordWithPositionOffset(in_coord), in_scale);
}

vec2 HSS_GetScreenVTexCoord(vec2 in_coord, vec2 in_screen_scale)
{
	return HSS_GetVTexCoordWithArgs(in_coord, in_screen_scale, HSS_GetPositionOffset());
}

float HSS_GetSplitAxisIsHorizontal()
{
	vec2 original_size = HSS_GetRotatedRawOriginalSize();
	return HHLP_IsOverValue(original_size.x/original_size.y, 1);
}

float HSS_GetSplitAxisCoord1D(vec2 in_coord, float split_axis_is_horizontal)
{
	return split_axis_is_horizontal * in_coord.x + (1 - split_axis_is_horizontal) * in_coord.y;
}

vec2 HSS_SetSplitAxisCoord(vec2 in_coord, float new_coord_1D, float split_axis_is_horizontal)
{
	return split_axis_is_horizontal * vec2(new_coord_1D, in_coord.y) + (1 - split_axis_is_horizontal) * vec2(in_coord.x, new_coord_1D);
}

float HSS_GetSplitInfo(inout float split_pos_1, inout float split_pos_2, inout float split_dist, inout float split_axis_is_horizontal)
{
	split_axis_is_horizontal = HSS_GetSplitAxisIsHorizontal();

	vec2 original_size = HSS_GetRotatedRawOriginalSize();
	vec2 cropped_size = HSS_GetCroppedRotatedOriginalSize();

	float cropped_size_1D = HSS_GetSplitAxisCoord1D(cropped_size, split_axis_is_horizontal);
	float split_screen_amount = HSS_GetSplitScreenAmount();
	float half_orig_size = HSS_GetSplitAxisCoord1D(original_size, split_axis_is_horizontal) * 0.5;
	float edge_crop = split_axis_is_horizontal * HSS_CROP_OVERSCAN_LEFT + (1 - split_axis_is_horizontal) * HSS_CROP_OVERSCAN_TOP;

	split_pos_1 = (edge_crop + half_orig_size) / cropped_size_1D;
	split_pos_2 = (edge_crop + half_orig_size + split_screen_amount) / cropped_size_1D;
	split_dist = split_screen_amount / cropped_size_1D;

	return 1;
}

vec2 HSS_Get0To1CoordFromSplitArea(vec2 in_coord, float split_pos_1, float split_pos_2, float split_dist, float split_axis_is_horizontal)
{
	vec2 original_size = HSS_GetRotatedRawOriginalSize();
	float in_coord_1D = HSS_GetSplitAxisCoord1D(in_coord, split_axis_is_horizontal);

	float adjusted_coord_1D = 	HHLP_IsUnderValue(in_coord_1D, 0.5) * in_coord_1D / split_pos_1 + 
								HHLP_IsOverValue(in_coord_1D, 0.5) * (in_coord_1D - split_pos_2) / (1 - split_pos_2);
							
	return HSS_SetSplitAxisCoord(in_coord, adjusted_coord_1D, split_axis_is_horizontal);
}

vec2 HSS_GetSplitAreaCoordFrom0To1(vec2 zone_test_coord, vec2 in_coord, float split_pos_1, float split_pos_2, float split_dist, float split_axis_is_horizontal)
{
	float zone_test_coord_1D = HSS_GetSplitAxisCoord1D(zone_test_coord, split_axis_is_horizontal);
	float in_coord_1D = HSS_GetSplitAxisCoord1D(in_coord, split_axis_is_horizontal);

	float adjusted_coord_1D = 	HHLP_IsUnderValue(zone_test_coord_1D, 0.5) * in_coord_1D * split_pos_1 + 
								HHLP_IsOverValue(zone_test_coord_1D, 0.5) * (in_coord_1D * (1 - split_pos_2) + split_pos_2);

	return HSS_SetSplitAxisCoord(in_coord, adjusted_coord_1D, split_axis_is_horizontal);
}

vec2 HSS_GetFlippedCoordOnSplitAxis(vec2 in_coord, float split_axis_is_horizontal)
{
	float flipped_coord_1D = -1 * (HSS_GetSplitAxisCoord1D(in_coord, split_axis_is_horizontal) - 0.5) + 0.5;
	return HSS_SetSplitAxisCoord(in_coord, flipped_coord_1D, split_axis_is_horizontal);
}

// Same as the HSS_GetScreenScale, but adds the width of the black edge
// Used for scaling the overlay outside the black edge
vec2 HSS_GetTubeScale(vec2 screen_scale)
{
	return HSS_GetScreenScaleWithEdgeHeight(1.2 * HSS_TUBE_BLACK_EDGE_THICKNESS / 100.0, screen_scale);
}

vec2 HSS_GetCurvatureScales(float screen_aspect)
{
	vec2 curvature_scales = screen_aspect < 1 ? vec2(HSS_CURVATURE_2D_SCALE_SHORT_AXIS, HSS_CURVATURE_2D_SCALE_LONG_AXIS)
											  : vec2(HSS_CURVATURE_2D_SCALE_LONG_AXIS,  HSS_CURVATURE_2D_SCALE_SHORT_AXIS);
	curvature_scales = (clamp(curvature_scales, 1, 5) - 1) + 1;
	return curvature_scales;
}
vec2 HSS_GetCurvatureValues(float screen_aspect)
{
	vec2 curvature_values = screen_aspect < 1 ? vec2(2 * HSS_CURVATURE_2D_SCALE_SHORT_AXIS * 2 / 100, HSS_CURVATURE_2D_SCALE_LONG_AXIS * 3 / 100)
											  : vec2(HSS_CURVATURE_2D_SCALE_LONG_AXIS * 3 / 100, 2 * HSS_CURVATURE_2D_SCALE_SHORT_AXIS * 2 / 100);

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

// vec2 HSS_GetGeomCurvedCoord(vec2 in_coord, float tilt_x, float tilt_y)
// {
// 	vec2 ang = vec2(tilt_x, tilt_y);
// 	float v_sinangle = sin(ang);
// 	float v_cosangle = cos(ang);
// 	float v_stretch = maxscale(v_sinangle, v_cosangle);
// 	vec2 curved_coord = Geom_Transform(in_coord, v_stretch, v_sinangle, v_cosangle);

// 	return curved_coord;
// }

vec2 HSS_GetCrtPiCurvedCoord(vec2 in_coord, vec2 in_curvature)
{
	// Barrel distortion shrinks the display area a bit, this will allow us to counteract that.
	in_curvature *= 5;
	vec2 barrelScale = 1.0 - (0.23 * in_curvature);
    in_coord -= vec2(0.5);
    float rsq = in_coord.x * in_coord.x + in_coord.y * in_coord.y;
    in_coord += in_coord * (in_curvature * rsq);
    in_coord *= barrelScale;
	in_coord += vec2(0.5);
    return in_coord;
}

vec2 HSS_GetTorridGristleCurvedCoord(vec2 in_coord, vec2 curvature_values)
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
vec2 HSS_Get2DCurvedCoord(vec2 in_coord, vec2 curvature_values)
{
	
	return HSS_GetCrtPiCurvedCoord(in_coord, curvature_values);
}

// TODO Use GetSplitInfo instead or recalculating
float HSS_GetSplitScreenAreaGradient(vec2 in_cropped_coord, float center_thickness, float gradient_thickness_mult)
{
	vec2 original_size = HSS_GetRotatedRawOriginalSize();
	vec2 cropped_size = HSS_GetCroppedRotatedOriginalSize();

	vec2 px_coord = in_cropped_coord * cropped_size;

	float is_horizontal = HHLP_IsOverValue(original_size.x / original_size.y, 1);
	float split_screen_amount = HSS_GetSplitScreenAmount();

	float px_pos = is_horizontal * px_coord.x + (1 - is_horizontal) * px_coord.y;
	float half_orig_size = is_horizontal * original_size.x * 0.5 + (1 - is_horizontal) * original_size.y * 0.5;
	float edge_crop = is_horizontal * HSS_CROP_OVERSCAN_LEFT + (1 - is_horizontal) * HSS_CROP_OVERSCAN_TOP;

	float cropped_split_px_pos1 = edge_crop + half_orig_size;
	float cropped_split_px_pos2 = edge_crop + half_orig_size + split_screen_amount;
	float cropped_split_px_pos_middle = edge_crop + half_orig_size + split_screen_amount / 2;

	float dist_from_center = abs(px_pos - cropped_split_px_pos_middle);
	// float center_gradient = smoothstep(dist_from_center, center_thickness * split_screen_amount / 2, center_thickness * split_screen_amount / 2 + gradient_thickness_mult * split_screen_amount / 2 + 0.0001);
	float center_gradient = 1 - smoothstep(	center_thickness * split_screen_amount / 2, 
											center_thickness * split_screen_amount / 2 + gradient_thickness_mult * split_screen_amount / 2 + 0.01, 
											dist_from_center);
	return center_gradient;
}

vec2 HSS_GetCurvedCoord(vec2 in_coord, float curvature_multiplier, float screen_aspect)
{
	float epsilon = 0.002;
	vec2 original_size = HSS_GetRotatedRawOriginalSize();

	vec2 adjusted_coord = in_coord;
	float tilt_angle_y = HSS_CURVATURE_3D_TILT_ANGLE_Y;
	float tilt_angle_x = HSS_CURVATURE_3D_TILT_ANGLE_X;
	float pin_inner_edge = 0;

	// If this is split screen with two bezels we need to scale the subsection of the screen (top or bottom)
	// to the full 0-1 space, do the curvature, then scale back to the subsection of the screen
	#ifdef HSM_SPLIT_SCREEN_PRESET
		float split_pos_1 = 0;
		float split_pos_2 = 0;
		float split_dist = 0;
		float split_axis_is_horizontal = 0;
		HSS_GetSplitInfo(split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

		float in_coord_1D = HSS_GetSplitAxisCoord1D(in_coord, split_axis_is_horizontal);
		float coord_is_on_first_half = HHLP_IsUnderValue(in_coord_1D, 0.5);

		if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
		{
			// If we are using split screen the take the coordinates from each screen and stretch them to 0-1
			adjusted_coord = HSS_Get0To1CoordFromSplitArea(in_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

			// If the coordinate was on the first screen then flip it on the split axis so we get the opposite tilting effect
			adjusted_coord = coord_is_on_first_half * HSS_GetFlippedCoordOnSplitAxis(adjusted_coord, split_axis_is_horizontal) + (1 - coord_is_on_first_half) * adjusted_coord;

			// If the screen is horizontal use the main tilt as tilt x, otherwise it's 0
			tilt_angle_x = split_axis_is_horizontal * HSS_CURVATURE_3D_TILT_ANGLE_Y;

			// If the screen is vertical use the main tilt as tilt x, otherwise it's 0
			tilt_angle_y = (1 - split_axis_is_horizontal) * HSS_CURVATURE_3D_TILT_ANGLE_Y;

			pin_inner_edge = 1;
		}
	#endif

	vec2 curved_coord = vec2(0);
	if (HSS_CURVATURE_MODE > 0.5)
	{
		float geom_radius_with_mult = HSS_CURVATURE_3D_RADIUS;
		if (HSS_CURVATURE_MODE == 1) geom_radius_with_mult -= 0.40;
		if (HSS_CURVATURE_MODE == 3) geom_radius_with_mult -= 1;
		geom_radius_with_mult *= (1 / (curvature_multiplier + epsilon));
        vec2 extra_curvature_mult = HSS_GetCurvatureScales(screen_aspect);
		mat2x2 pixel_to_video_uv;
		
		curved_coord = HRG_GetGeomCurvedCoord(	adjusted_coord, 
												HSS_CURVATURE_MODE, 
												geom_radius_with_mult,
												HSS_CURVATURE_3D_VIEW_DIST,
												tilt_angle_x,
												tilt_angle_y,
												screen_aspect,
												pin_inner_edge,
												global.SourceSize.xy,
												global.OutputSize.xy,
												pixel_to_video_uv);
	}
	else
	{
		vec2 curvature_values = curvature_multiplier * HSS_GetCurvatureValues(screen_aspect);
		curved_coord = HSS_Get2DCurvedCoord(adjusted_coord, curvature_values);
	}

	// If this is split screen we need to scale 0-1 space back to the subsection of the screen
	#ifdef HSM_SPLIT_SCREEN_PRESET
		if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
		{
			// If the coordinate was originally on the first screen then flip it back
			curved_coord = coord_is_on_first_half * HSS_GetFlippedCoordOnSplitAxis(curved_coord, split_axis_is_horizontal) + 
							(1 - coord_is_on_first_half) * curved_coord;

			// If this was processed as split screen scale the 0-1 space back to the split areas
			curved_coord = HSS_GetSplitAreaCoordFrom0To1(in_coord, curved_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);
		}
	#endif

	return curved_coord;
}

vec2 HSS_GetMirrorWrappedCoord(vec2 in_coord)
{
	in_coord = mod(in_coord, 2);
	vec2 ctr_mirror_coord = in_coord - 0.5;

	float mirror_x = clamp(clamp(abs(ctr_mirror_coord.x) - 0.5, 0, 1) * 100000, 0, 1);
	float mirror_y = clamp(clamp(abs(ctr_mirror_coord.y) - 0.5, 0, 1) * 100000, 0, 1);

	ctr_mirror_coord.x = ctr_mirror_coord.x - mirror_x * 2 * sign(ctr_mirror_coord.x) * (abs(ctr_mirror_coord.x) - 0.5);
	ctr_mirror_coord.y = ctr_mirror_coord.y - mirror_y * 2 * sign(ctr_mirror_coord.y) * (abs(ctr_mirror_coord.y) - 0.5);

	return ctr_mirror_coord + 0.5;
}

// Returns curved coordinates for the coordinate supplied
// Cached coordinate comes from the mapping pass texture supplied
// x & y are the curved tube coordinates
vec4 HSS_GetCachedCurvedValues(sampler2D in_mapping_pass, vec2 in_coord, inout vec2 out_curved_coord, inout float outside_tube_mask, inout float edge_mask)
{
	vec4 texture_sample = texture(in_mapping_pass, in_coord);
	out_curved_coord = texture_sample.xy;
	outside_tube_mask = texture_sample.z;
	edge_mask = texture_sample.w;
	return texture_sample;
}

// Borrowed from cgwg's crt-geom, under GPL
float HSS_GetCornerMask(vec2 in_coord, float screen_aspect, float corner_radius, float edge_sharpness)
// returns 0.0 - 1.0 value used for masking the corner so it looks round
{
	//(0.5 - abs(in_coord - 0.5)) * 2
	vec2 new_coord = min(in_coord, vec2(1.0) - in_coord) * vec2(screen_aspect, 1);
	vec2 corner_distance = vec2(max(corner_radius / 1000.0, (1.0 - HSS_SCREENFX_EDGE_SHARPNESS * edge_sharpness) * 0.01));
	new_coord = (corner_distance - min(new_coord, corner_distance));
	float distance = sqrt(dot(new_coord, new_coord));

	return clamp((corner_distance.x - distance) * (edge_sharpness * 500 + 100), 0.0, 1.0);
}

vec3 HSS_RGBtoHSV(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = c.g < c.b ? vec4(c.bg, K.wz) : vec4(c.gb, K.xy);
    vec4 q = c.r < p.x ? vec4(p.xyw, c.r) : vec4(c.r, p.yzx);

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 HSS_HSVtoRGB(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec4 HSS_ApplyGamma(vec4 in_color, float in_gamma)
{
	vec3 out_color = pow(in_color.rgb, vec3(1 / in_gamma));
	return vec4(out_color, in_color.a);
}

// 'Removes' encoded gamma from color to put the color in linear space
vec4 HSS_Linearize(vec4 in_color, float encoded_gamma)
{
	return HSS_ApplyGamma(in_color, 1 / encoded_gamma);
}

// Adds gamma onto color in linear space to get a color with encoded gamma
vec4 HSS_Delinearize(vec4 in_color, float in_gamma)
{
	return HSS_ApplyGamma(in_color, in_gamma);
}

vec4 HSS_ApplyBlackLevel(vec4 in_color, float color_is_linear)
{
	vec4 out_color = in_color;

	// Linearize if color isn't linear
	if (color_is_linear == 0)
	{
		out_color = HSS_Linearize(out_color, HSS_DEFAULT_CRT_GAMMA);
	}

	// Black Level
	out_color -= HSS_COLOR_BLACK_LEVEL / 100;
	out_color *= 1 / vec4(1.0 - HSS_COLOR_BLACK_LEVEL / 100);
	out_color = clamp(out_color, 0, 2);

	// If color isn't linear put default gamma back on
	if (color_is_linear == 0)
	{
		out_color = HSS_Delinearize(out_color, HSS_DEFAULT_CRT_GAMMA);
	}

	out_color.w = in_color.w;

	return clamp(out_color, 0, 1);
}

vec2 HSS_RotateCoordinate(vec2 in_coord, float rotation_on)
{
	vec2 ctr_coord = in_coord - 0.5;
	ctr_coord = (1 - rotation_on) * ctr_coord + rotation_on * vec2(-ctr_coord.y, ctr_coord.x);
	return ctr_coord + 0.5;
}

vec2 HSS_GetMirrorWrapCoord(vec2 in_coord)
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
float HSS_IsInNegativeCropArea(vec2 in_coord)
{
	float result = abs(clamp(HSS_CROP_OVERSCAN_TOP, -1, 0) * clamp(in_coord.y, -1, 0)) * 100000 +
				   abs(clamp(HSS_CROP_OVERSCAN_BOTTOM, -1, 0) * (clamp(in_coord.y, 1, 2) - 1)) * 100000 +
				   abs(clamp(HSS_CROP_OVERSCAN_LEFT, -1, 0) * clamp(in_coord.x, -1, 0)) * 100000 +
				   abs(clamp(HSS_CROP_OVERSCAN_RIGHT, -1, 0) * (clamp(in_coord.x, 1, 2) - 1)) * 100000;
	return clamp(result, 0, 1);
}

// Texture Sampler function which takes a coordinate in the cropped coordinate space
vec4 HSS_GetCroppedTexSample(sampler2D in_sampler, vec2 in_cropped_coord)
{
	vec2 original_size = HSS_GetRotatedRawOriginalSize();
	vec2 cropped_size = HSS_GetCroppedRotatedOriginalSize();

	// Flip the coordinate vertically if desired
	in_cropped_coord.y = HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL * (1 - in_cropped_coord.y) + (1 - HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL) * in_cropped_coord.y;

	vec2 px_coord = in_cropped_coord * cropped_size;

	#ifdef HSM_SPLIT_SCREEN_PRESET
		float is_horizontal = HHLP_IsOverValue(original_size.x/original_size.y, 1);
		float split_screen_amount = HSS_GetSplitScreenAmount();

		float px_pos = is_horizontal * px_coord.x + (1 - is_horizontal) * px_coord.y;
		float half_orig_size = is_horizontal * original_size.x * 0.5 + (1 - is_horizontal) * original_size.y * 0.5;
		float edge_crop = is_horizontal * HSS_CROP_OVERSCAN_LEFT + (1 - is_horizontal) * HSS_CROP_OVERSCAN_TOP;

		float cropped_split_px_pos1 = edge_crop + half_orig_size;
		float cropped_split_px_pos2 = edge_crop + half_orig_size + split_screen_amount;
		float cropped_split_px_pos_middle = edge_crop + half_orig_size + split_screen_amount / 2;

		float in_split_area = HHLP_IsOverValue(px_pos, cropped_split_px_pos1) * HHLP_IsUnderValue(px_pos, cropped_split_px_pos2);
		float in_split_area_first_half = in_split_area * HHLP_IsUnderValue(px_pos, cropped_split_px_pos1 + floor(split_screen_amount / 2) + 1);

		float new_px_pos = 	in_split_area * in_split_area_first_half * (cropped_split_px_pos1 - (px_pos - cropped_split_px_pos1) - 0.5) + 
							in_split_area * (1 - in_split_area_first_half) * (cropped_split_px_pos2 + (cropped_split_px_pos2 - px_pos) - split_screen_amount  + 0.5) + 
							(1 - in_split_area) * (px_pos - clamp(abs(split_screen_amount), 0, 1) * HHLP_IsOverValue(px_pos, cropped_split_px_pos1) * split_screen_amount);

		px_coord = is_horizontal * vec2(new_px_pos, px_coord.y) + (1 - is_horizontal) * vec2(px_coord.x, new_px_pos);
	#endif
		
	vec2 sample_coord = (px_coord + vec2(HSS_CROP_OVERSCAN_LEFT, HSS_CROP_OVERSCAN_TOP)) / original_size;
	sample_coord =  HSS_RotateCoordinate(sample_coord, HSS_ROTATE_CORE_IMAGE);
	
	vec4 out_color = texture(in_sampler, sample_coord);

	vec4 negative_crop_color = vec4(HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS / 10000, HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS / 10000, HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS / 10000, 1);
	
	#ifdef HSM_SPLIT_SCREEN_PRESET
		float use_neg_crop_color = HHLP_EqualsValue(HSS_SPLIT_SCREEN_CENTER_FILL_MODE, 0, 0.1) * in_split_area;
		out_color = use_neg_crop_color * negative_crop_color + (1 - use_neg_crop_color) * out_color;
	#endif

	float negative_crop = HSS_IsInNegativeCropArea(sample_coord);

	out_color = negative_crop * negative_crop_color + (1 - negative_crop) * out_color;

	// #ifdef HSM_SPLIT_SCREEN_BLEND_CENTER_PRESET
	// 	out_color = in_split_area * vec4(0) + (1 - in_split_area) * out_color;
	// #endif

	return out_color;
}

vec4 HSS_ApplyPhosphorPersistence(vec4 in_color, sampler2D in_feedback_pass, vec2 in_coord)
{
	if (HSS_PHOSPHOR_PERSISTENCE == 0) return in_color;

	vec3 Phosphor = HSS_PHOSPHOR_PERSISTENCE < 0 ? vec3(0.5, 0.6, 0.8) : vec3(0.5, 0.5, 0.5);

	float delta_time = 5 - 5 * HHLP_EasePowerOut(abs(HSS_PHOSPHOR_PERSISTENCE), 2) + 0.1;
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

float HSS_GetVignetteFactor(vec2 coord, float amount)
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

float HSS_GetScreenVignetteFactor(vec2 coord, float amount)
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
vec4 HSS_ApplyScanlineMask(vec4 in_color, vec2 in_coord, vec2 screen_scale)
{
	//   Stuff to try implementing
	//   Parameter for simulated line count
    //   Option to try to match a integer division of the core resolution
    //   Option for integer "perfect" scanlines
    //   Offset on scan axis
    //   Curvature Multiplier
    //   Try mame hlsl darkening
    //   Check Lottes tone mapping
    //   Crawl

	vec2 original_size = HSS_GetRotatedOriginalSize();
	float use_vert_scanlines = HSS_GetUseVerticalScanlines(original_size.x / original_size.y);
	vec2 sampling_res = HSS_GetRotatedOriginalSizeWithCoreResMult();
	float scan_axis_pos = use_vert_scanlines * in_coord.x + (1 - use_vert_scanlines) * in_coord.y;
	float scan_axis_res = use_vert_scanlines * sampling_res.x + (1 - use_vert_scanlines) * sampling_res.y;

	if (HSS_SCREENFX_FAKE_SCANLINE_OPACITY < 0.001 || scan_axis_res < HSS_INTERLACE_TRIGGER_RES )
	{
		return in_color;
	}

	float pi = 3.141592654;

	vec2 screen_size = global.OutputSize.xy * screen_scale;
	float scan_axis_screen_scale_res = use_vert_scanlines * screen_size.x + (1 - use_vert_scanlines) * screen_size.y;
	
	float simulated_scanline_res = HSS_SCREENFX_SCANLINE_RES;

	#ifdef HSM_SPLIT_SCREEN_PRESET
		if (use_vert_scanlines == 0 && screen_scale.x / screen_scale.y < 1 )
		{
			simulated_scanline_res = HSS_SCREENFX_SCANLINE_RES * 2;
		}
		if (use_vert_scanlines == 1 && screen_scale.x / screen_scale.y > 1 )
		{
			simulated_scanline_res = HSS_SCREENFX_SCANLINE_RES * 2;
		}
	#endif

	float scanline_size = ceil(scan_axis_screen_scale_res / simulated_scanline_res);

	float scan = mod(scan_axis_pos * scan_axis_screen_scale_res, scanline_size) / scanline_size;

	// Alternate, modulating the scanline width depending on brightness
	//float scanline_mask = HHLP_EasePowerOut(1 - abs(scan - 0.5) * 2, 0.5 + 2 * smoothstep(0.4, 0.9, (in_color.r + in_color.g +  in_color.b) / 3));
	float color_brightness_modulation = HHLP_EasePowerOut(smoothstep(0.4, 0.99, (in_color.r + in_color.g +  in_color.b) / 3), 2);

	float scanline_mask = 1 - abs(scan - 0.5) * 2;
	scanline_mask = pow(1 - scanline_mask, 1);

	float final_scanline_mask = clamp(1 * scanline_mask, 0, 1);

	color_brightness_modulation = HHLP_EasePowerOut(smoothstep(0.4, HSS_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF + 1.5, (in_color.r + in_color.g +  in_color.b) / 3), 2);
	final_scanline_mask = clamp(mix(1, mix(final_scanline_mask, 1, color_brightness_modulation), HSS_SCREENFX_FAKE_SCANLINE_OPACITY), 0, 1);

	vec4 masked_color = in_color;
	masked_color *= 1 + 0.5 * HSS_SCREENFX_FAKE_SCANLINE_OPACITY;
	masked_color = clamp(final_scanline_mask * masked_color, 0, 1);
	masked_color.w = in_color.w;

	// Split Screen for debugging
	// masked_color = scan_opposite_axis_pos > 0.7 ? in_color : masked_color;

	return clamp(masked_color, 0, 1);
}

vec4 HSS_GetPostCrtPreppedColor(vec4 in_color_linear, vec2 screen_curved_coord, vec2 screen_coord, float screen_aspect, vec2 screen_scale)
{
	float screen_mask = HSS_GetCornerMask((screen_curved_coord - 0.5) * 0.999 + 0.5, screen_aspect, HSS_SCREENFX_CORNER_RADIUS, 0.9);

	float screen_edge_mask = HSS_GetCornerMask(screen_curved_coord, screen_aspect, HSS_SCREENFX_CORNER_RADIUS, HSS_SCREENFX_EDGE_SHARPNESS);
	screen_edge_mask = 1 - ((1 - screen_edge_mask) * screen_mask);

	vec4 out_color = in_color_linear;
	out_color *= screen_edge_mask;

	vec2 mirrored_screen_coord = HSS_GetMirrorWrappedCoord(screen_curved_coord);
	float vignette_factor = HSS_GetScreenVignetteFactor(mirrored_screen_coord, HSS_SCREENFX_VIGNETTE);

	// If this is called from the glass preset we don't want the vignette to affect mirrored area
	if (HGL_GLASSBORDER_ON == 1)
		vignette_factor = 1 - ((1 - vignette_factor) * screen_mask);

	out_color *= vignette_factor;

	if (HSS_SCREENFX_SCANLINE_RES > 0.5)
	{
		vec4 scanline_masked_color = HSS_ApplyScanlineMask(out_color, screen_coord, screen_scale);
		
		out_color = mix(out_color, scanline_masked_color, screen_mask);
	}

	// If we are not using this with the bezel we want
	#ifdef MASK_OUTSIDE_SCREEN
		out_color *= screen_mask;
	#endif

	// Apply the final Gamma
	out_color = HSS_Delinearize(out_color, HSS_COLOR_CRT_GAMMA);

	return out_color;
}


