/*   
hsm-mega-bezel-reflection

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Adds a reflection effect around the screen to imitate the reflection on the bezel of a real CRT
	-Must be used with a crt shader which integrates the hsm-mega-bezel-include.inc scaling so 
		the crt screen and reflection scale and position are synchronized

	-Retroarch Video Settings:
		-Aspect Ratio should be set to the monitor aspect ratio
		-Integer Scale should be set to OFF

Thanks to:
	Hunkerk who sparked this idea with his Bezel Reflection Test  
	Everyone on the libretro forum for helpful suggestions
*/

/////////////// IMPORTS ///////////////
#include "hsm-screen-scale-and-bezel-with-globals.inc"

/////////////// DEFINES ///////////////
#define BLEND_MODE_NORMAL 0
#define BLEND_MODE_ADD 1
#define BLEND_MODE_MULTIPLY 2
#define BLEND_MODE_NORMAL_UNDER 3
#define BLEND_MODE_ADD_UNDER 4
#define BLEND_MODE_MULTIPLY_UNDER 5

#define MASK_MODE_ALL 0
#define MASK_MODE_TUBE 1
#define MASK_MODE_OUTSIDE_TUBE 2
#define MASK_MODE_FRAME 3
#define MASK_MODE_OUTSIDE_BEZEL 4
#define MASK_MODE_OUTSIDE_FRAME 5

/////////////// Helper Functions ///////////////

// Assumes Opacity is already encoded in alpha
vec4 BlendModeLayerMix(vec4 in_color_under, vec4 in_color_over, float in_blend_mode)
{
	vec4 blend_color = in_color_over;

	if (in_blend_mode == BLEND_MODE_ADD)  	 			blend_color = in_color_under + in_color_over;
	else if (in_blend_mode == BLEND_MODE_MULTIPLY)  	blend_color = in_color_under * in_color_over;

	return clamp(mix(in_color_under, blend_color, in_color_over.a), 0, 1);
}

vec2 GetImageLayerCoord(vec2 viewport_coord, vec2 position_offset, vec2 tube_scale)
{
	float output_aspect = global.OutputSize.x / global.OutputSize.y;
	float aspect_difference = HBZ_BACKGROUND_IMAGE_ASPECT_RATIO / output_aspect;
	vec2 fit_height_scale = vec2(aspect_difference, 1);

	// If the texture is supposed to be fit to the screen
	if (HBZ_BACKGROUND_IMAGE_SCALE_MODE == 1)
		return viewport_coord;

	// If the texture is supposed to fit vertically
	if (HBZ_BACKGROUND_IMAGE_SCALE_MODE == 2)
		return (viewport_coord - 0.5) / fit_height_scale + 0.5;

	// Otherwise use Auto Scaling with Position offset
	else
	{
		// If using auto scale mode and apply the position adjustment from mega screen scale
		vec2 screen_height_match_scale =  fit_height_scale * tube_scale.y / (HBZ_BACKGROUND_IMAGE_TUBE_HEIGHT / 100);
		vec2 scale = screen_height_match_scale;
		return HSS_GetInverseScaledCoord(HSS_GetCoordWithPositionOffset(viewport_coord), scale);
	}
}

float clamp_0_1(float in_value)
{
	return clamp(in_value, 0, 1);
}

float GetFade(float current_position, float corner_position, float fade_distance)
{
	return smoothstep(corner_position + fade_distance / 2, corner_position - fade_distance / 2, current_position);
}

void srand(vec2 a, out float r)
{
	r = sin(dot(a, vec2(1233.224, 1743.335)));
}

float rand(inout float r)
{
	r = fract(3712.65 * r + 0.61432);
	return (r - 0.5) * 2.0;
}

vec4 GetStoichaicBlurredSample(sampler2D in_sampler, vec2 in_coord, float num_samples, float max_blur_size, float blur_ratio)
{
	if (num_samples == 0 || max_blur_size == 0 || blur_ratio == 0)
	{
		return texture(in_sampler, in_coord);
	}

	// Common value for max_blur_size is about 40
	float p = blur_ratio * max_blur_size / global.SourceSize.y;
	vec4 blurred_color = vec4(0.0);
	float radius;
	srand(in_coord, radius);
	vec2 radius_vector;
	
	for(int i=0; i < num_samples; i++)
	{
		radius_vector.x = rand(radius);
		radius_vector.y = rand(radius);
		vec2 sample_coord = in_coord + radius_vector * p;

		// sample_coord = HSS_GetMirrorWrappedCoord(sample_coord);
		sample_coord = clamp(sample_coord, 0.04, 0.96);
		// if (abs(sample_coord.y - 0.5) > 0.5) blurred_color += vec4(1, 0, 0, 0);

		blurred_color += texture(in_sampler, sample_coord) / num_samples;
	}

	return blurred_color;
}

float SCREEN_ASPECT = HSS_GetScreenAspect();
vec2 SCREEN_SCALE = HSS_GetScreenScale(SCREEN_ASPECT);
vec2 TUBE_SCALE = HSS_GetTubeScale(SCREEN_SCALE);

//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma stage vertex

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 0) out vec2 VIEWPORT_WITH_POS_OFFSET_COORD;
layout(location = 3) out vec2 SCREEN_COORD;
layout(location = 6) out vec2 VIEWPORT_COORD;
layout(location = 7) out vec2 IMAGE_LAYER_COORD;
layout(location = 8) out vec3 BEZEL_FRAME_ORIGINAL_COLOR_RGB;

//////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	gl_Position = global.MVP * Position;
	vec2 vTexCoord = TexCoord;

	if (HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL > 0.5)
		vTexCoord.y =  1 - vTexCoord.y;

	VIEWPORT_WITH_POS_OFFSET_COORD = HSS_GetCoordWithPositionOffset(vTexCoord * 1.0001);

	SCREEN_COORD = HSS_GetScreenVTexCoord(vTexCoord, SCREEN_SCALE);

	VIEWPORT_COORD = vTexCoord * 1.0001;
	IMAGE_LAYER_COORD = GetImageLayerCoord(VIEWPORT_COORD, HSS_GetPositionOffset(), TUBE_SCALE);

	// Not sure why we need linearize this but it seems to have a smoother range this way
	BEZEL_FRAME_ORIGINAL_COLOR_RGB = HSS_Linearize(vec4(HSS_HSVtoRGB(vec3(HBZ_BEZEL_COLOR_HUE / 360, HBZ_BEZEL_COLOR_SATURATION / 100, HBZ_BEZEL_COLOR_VALUE / 100)), 1), HSS_DEFAULT_SRGB_GAMMA).rgb;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma stage fragment

layout(location = 0) in vec2 VIEWPORT_WITH_POS_OFFSET_COORD;
layout(location = 3) in vec2 SCREEN_COORD;
layout(location = 6) in vec2 VIEWPORT_COORD;
layout(location = 7) in vec2 IMAGE_LAYER_COORD;
layout(location = 8) in vec3 BEZEL_FRAME_ORIGINAL_COLOR_RGB;

layout(location = 0) out vec4 FragColor;

// Pass Framebuffer Textures
layout(set = 0, binding = 2) uniform sampler2D BR_MappingPass;
layout(set = 0, binding = 3) uniform sampler2D BR_CRTPass;
layout(set = 0, binding = 5) uniform sampler2D BR_MirrorBlurredPass;
layout(set = 0, binding = 6) uniform sampler2D BR_MirrorReflectionDiffusedPass;
layout(set = 0, binding = 7) uniform sampler2D BR_MirrorFullscreenGlowPass;

// Image Textures from disk
layout(set = 0, binding = 8) uniform sampler2D AvgLumPass;
layout(set = 0, binding = 9) uniform sampler2D TubeGlassImage;
#ifndef REFLECTION_ONLY_PRESET
	layout(set = 0, binding = 10)  uniform sampler2D BackgroundImage;
	layout(set = 0, binding = 11)  uniform sampler2D BackgroundVertImage;
	layout(set = 0, binding = 12) uniform sampler2D TopLayerImage;
	layout(set = 0, binding = 13) uniform sampler2D TopLayerVertImage;
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	vec2 tube_coord_warped = vec2(0, 0);
	float outside_tube_mask = 0;
	float edge_mask = 0;
	HSS_GetCachedCurvedValues(BR_MappingPass, VIEWPORT_COORD.xy, tube_coord_warped, outside_tube_mask, edge_mask);
	float tube_mask = 1 - outside_tube_mask;

	vec2 tube_warped_coord_ctr = tube_coord_warped - 0.5;

	float avg_lum_mult = smoothstep(0.01, 0.5, pow(texture(AvgLumPass, VIEWPORT_COORD).a, 1.3));

	//----------------------------------------------------
	// CRT Pass
	//----------------------------------------------------
	// Get the CRT pass and make it in linear space & mask the area outside the screen
	vec4 crt_image_linear = HSS_Linearize(texture(BR_CRTPass, VIEWPORT_COORD.xy), HSS_DEFAULT_CRT_GAMMA);
	crt_image_linear = HSS_ApplyGamma(crt_image_linear, HSS_DEFAULT_CRT_GAMMA / HSS_DEFAULT_SRGB_GAMMA);

	vec4 blurred_reflection_color = texture(BR_MirrorBlurredPass, VIEWPORT_COORD.xy);

	vec2 screen_curved_coord = HSS_GetCurvedCoord(SCREEN_COORD, 1, SCREEN_ASPECT);

	#ifdef HSM_SPLIT_SCREEN_PRESET
		float split_pos_1 = 0;
		float split_pos_2 = 0;
		float split_dist = 0;
		float split_axis_is_horizontal = 0;
		HSS_GetSplitInfo(split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

		if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 2)
		{
			float sides_split_fade_mask = 1 - HSS_GetSplitScreenAreaGradient(tube_coord_warped, 1, 0.04);
			crt_image_linear *= sides_split_fade_mask;
		}
		else
		{
			if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
			{
				// Take the split area and re-map it to 0-1
				screen_curved_coord = HSS_Get0To1CoordFromSplitArea(screen_curved_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);
			}
					// If this is the split screen preset and we want to blend the center colors
			if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 3 || HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 4)
			{
				float split_screen_area_mask = (1 - outside_tube_mask) * HHLP_EasePowerOut(HSS_GetSplitScreenAreaGradient(tube_coord_warped, 0.25, 1.25), 2);
				
				crt_image_linear = mix(crt_image_linear, blurred_reflection_color, split_screen_area_mask);
			}

			// If we should fade to black in the center
			if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE > 3 && HSS_SPLIT_SCREEN_CENTER_FILL_MODE < 6)
			{
				float split_screen_area_mask = HHLP_EasePowerOut(HSS_GetSplitScreenAreaGradient(tube_coord_warped, 0.1, 1.4), 2);
				
				crt_image_linear *= 1 - split_screen_area_mask;
			}
		}
	#endif

	// Shrink the mask by 0.001 to clip off outer edge
	float screen_mask = HSS_GetCornerMask(((screen_curved_coord - 0.5) * 1.001) + 0.5, SCREEN_ASPECT, HSS_SCREENFX_CORNER_RADIUS, HSS_SCREENFX_EDGE_SHARPNESS);
	crt_image_linear *= screen_mask;

	//----------------------------------------------------
	//  Calculate Outside mapping Coords
	//----------------------------------------------------

	/* This first big chunk is to get a mapping of the space outside of the screen which is continuous
	This is more complicated than you would expect because since we are using curved coordinates 
	there are discontinuities outside the normal screen corners, e.g. where x > 1 and y > 1
	So instead of trying to use the coordinates from the screen/tube we use a larger space 
	and subtract the screen space to see how far we are outside of the sreen
	*/

	// Additional scale to be applied to the tube scale to create an expanded mapping area 
	vec2 outermap_scale = vec2(1, 1) * (1.3 + 1);

	// Get a range width from the outer tube edge to the outer edge of the outermap
	float outermap_range = 0.5 * (outermap_scale.y) * 0.7;
	vec2 outermap_warped_coord_ctr = tube_warped_coord_ctr;
	vec2 outermap_coord = tube_warped_coord_ctr + 0.5;
	vec2 outermap_screen_size_from_center = vec2(0.5, 0.5);
	vec2 outermap_warped_outside_screen_vector = (outermap_warped_coord_ctr - clamp(outermap_warped_coord_ctr, -0.490, 0.490)) * vec2(1 / SCREEN_ASPECT, 1);
	float output_aspect = global.OutputSize.x / global.OutputSize.y;
	float outside_ratio_warped = clamp(length(outermap_warped_outside_screen_vector) / outermap_range, 0, 1);
	vec2 outermap_screen_corner_ctr_coord = vec2(0.5, -0.5);

	// Get a coordinate offset so it is centered around the corner
	vec2 outermap_coord_warped_ctr_at_screen_corner = abs(outermap_warped_coord_ctr) - vec2(0.5);


	float screen_scale_diagonal = sqrt(SCREEN_SCALE.y * SCREEN_SCALE.y + (SCREEN_SCALE.y * SCREEN_ASPECT) * (SCREEN_SCALE.y * SCREEN_ASPECT));

	// TODO need to correct for screen aspect of sub screen
	vec2 outer_bezel_scale = vec2(HBZ_BEZEL_WIDTH / 100 / SCREEN_ASPECT + 1, HBZ_BEZEL_HEIGHT / 100 + 1);


	float screen_aspect = SCREEN_ASPECT;
	vec2 frame_pos_offset = vec2(0, HBZ_FRAME_POS_Y_OFFSET / 100);

	// Need to put this before screen_scale_diagonal?
	vec2 screen_coord = HSS_GetScreenVTexCoord(VIEWPORT_COORD, SCREEN_SCALE);
	vec2 screen_scale = SCREEN_SCALE;
	vec2 sub_screen_scale = SCREEN_SCALE;
	float frame_thickness = HBZ_FRAME_THICKNESS / 100;

	#ifdef HSM_SPLIT_SCREEN_PRESET
		// If we are using split screen with separate frames
		if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
		{
			outer_bezel_scale = split_axis_is_horizontal * vec2((outer_bezel_scale.x - 1) * 2 + 1, outer_bezel_scale.y) + (1 - split_axis_is_horizontal) * vec2(outer_bezel_scale.x, (outer_bezel_scale.y - 1) * 2 + 1);
			
			// Adjust the direction of position depending on if the screens are left & Right or Top and Bottom
			frame_pos_offset *= HSS_SetSplitAxisCoord(vec2(1,1), HBZ_FRAME_POS_Y_OFFSET / 100,  split_axis_is_horizontal);
			
			// If this is the first screen invert the position offset, so the screens slide toward or away from each other 
			float in_first_half = HHLP_IsUnderValue(HSS_GetSplitAxisCoord1D(SCREEN_COORD, split_axis_is_horizontal), 0.5);
			frame_pos_offset *=  in_first_half * 1 + (1 - in_first_half) * -1;
		}
	#endif

	outer_bezel_scale = (outer_bezel_scale - 1) * screen_scale_diagonal + 1;

	vec2 bezel_outside_coord = SCREEN_COORD + frame_pos_offset;

	// Only run curved coordinates if we need to because of tilt
	if ((HSS_CURVATURE_MODE > 0) && ((HSS_CURVATURE_3D_TILT_ANGLE_X != 0) || (HSS_CURVATURE_3D_TILT_ANGLE_Y != 0)))
	{
		bezel_outside_coord = HSS_GetCurvedCoord(bezel_outside_coord, 0, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);
	}

	#ifdef HSM_SPLIT_SCREEN_PRESET
		if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
		{
			// If this was on the first screen then flip it back
			bezel_outside_coord = HSS_Get0To1CoordFromSplitArea(bezel_outside_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);
			sub_screen_scale = split_axis_is_horizontal * vec2(split_pos_1 * SCREEN_SCALE.x, SCREEN_SCALE.y) + (1 - split_axis_is_horizontal) * vec2(SCREEN_SCALE.x, (1 - split_pos_2) * SCREEN_SCALE.y);
			frame_thickness *= 2;
		}
	#endif

	vec2 black_edge_scale_offset = HSS_GetTubeScale(sub_screen_scale) / sub_screen_scale;

	bezel_outside_coord = HSS_GetInverseScaledCoord(bezel_outside_coord, black_edge_scale_offset * outer_bezel_scale) + vec2(0, HBZ_FRAME_POS_Y_OFFSET / 100);

	float outside_bezel_mask = 1 - HSS_GetCornerMask(bezel_outside_coord, SCREEN_ASPECT,  HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 0.9);

	vec2 frame_outside_coord = (bezel_outside_coord - 0.5) / vec2(frame_thickness/ (sub_screen_scale.x / sub_screen_scale.y * output_aspect) + 1, frame_thickness + 1) + 0.5;

	// vec2 frame_scale = vec2(HBZ_BEZEL_WIDTH / 100 / SCREEN_ASPECT + 1, HBZ_BEZEL_HEIGHT / 100 + 1);
	// frame_scale = (outer_bezel_scale - 1) * screen_scale_diagonal + 1;

	// vec2 frame_base_coord = HSS_GetInverseScaledCoord(VIEWPORT_WITH_POS_OFFSET_COORD, frame_scale * TUBE_SCALE) + frame_pos_offset;
	// vec2 frame_outside_coord = (frame_base_coord - 0.5) / vec2(HBZ_FRAME_THICKNESS / 100 / SCREEN_ASPECT + 1, HBZ_FRAME_THICKNESS / 100 + 1) + 0.5;// If no tilt we don't need curved coordinateRAME_THICKNESS / 100 + 1) + 0.5;

	// if ((HSS_CURVATURE_MODE > 0) && ((HSS_CURVATURE_3D_TILT_ANGLE_X != 0) || (HSS_CURVATURE_3D_TILT_ANGLE_Y != 0)))
	// {
	// 	frame_outside_coord = HSS_GetCurvedCoord(frame_outside_coord, 0, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);
	// }

	//----------------------------------------------------
	//  Calculate Corner Highlight Mask
	//----------------------------------------------------
	const float pi = 3.1415;
	float corner_highlight_pos_y_offset = 0;

	// Still need to shift the highlight vertically
	//+ vec2(0, corner_highlight_pos_y_offset / 100)

	// Get amount to shift the point at the outer corner to match the overall position offset
	vec2 pos_shift_offset = vec2(0, HBZ_FRAME_POS_Y_OFFSET / 100) * SCREEN_SCALE.y / outermap_scale;
	pos_shift_offset *= outermap_coord.y > 0.5 ? 1 : -1;

	// Get the direction vector from the inner corner of the bezel pointing at the outer corner 
	vec2 corner_crease_dir = (outermap_screen_corner_ctr_coord + pos_shift_offset) / vec2(HBZ_BEZEL_HEIGHT / 100 + 1, HBZ_BEZEL_WIDTH / 100 + 1) - (outermap_screen_corner_ctr_coord + vec2(0, corner_highlight_pos_y_offset / 100)) ;
	corner_crease_dir *= vec2(SCREEN_ASPECT, 1);

	float aspect_corner_length_scale_offset = SCREEN_ASPECT > 1 ? 0.9 : 1.5;
	float corner_crease_length = length(corner_crease_dir * aspect_corner_length_scale_offset);

	// A hack to adjust the angle offset, because without it the corner angle isn't pointing exactly at the corner
	// This offset is the opposite direction for vertical and horizontal aspect ratio
	float corner_rotation_offset = (SCREEN_COORD.y < 0.5) ? -HBR_CORNER_ROTATION_OFFSET_TOP : -HBR_CORNER_ROTATION_OFFSET_BOTTOM;

	if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
	{
		corner_rotation_offset += 13;
	}
	else
	{
		if (HSS_CURVATURE_MODE == 0)
		{
			// If we are using a 3d Curvature no offset is necessary
			corner_rotation_offset += (SCREEN_ASPECT > 1) ? 2 : 3;
		}
	}

	// Convert direction vector to an angle so we can rotate the corner crease direction
	float corner_angle_degrees = atan(corner_crease_dir.y / corner_crease_dir.x) / (2 * pi) * 360;

	corner_angle_degrees += corner_rotation_offset;
	float corner_angle_radians = corner_angle_degrees / 360 * 2 * pi;
	corner_crease_dir = vec2(cos(corner_angle_radians), sin(corner_angle_radians));

	// Get the distance perpendicular to the crease direction so we can use it to fade later
	float distance_from_crease = HHLP_GetDistanceToLine(outermap_coord_warped_ctr_at_screen_corner.x, outermap_coord_warped_ctr_at_screen_corner.y, 1, corner_crease_dir.y / corner_crease_dir.x, 0 );

	float fade_out_to_corner = HHLP_QuadraticBezier(clamp(length(outermap_warped_outside_screen_vector) / (corner_crease_length * 2), 0, 1), vec2(0.5, HBR_CORNER_SPREAD_FALLOFF / 100));

	float corner_fade_width_inner = HBR_CORNER_INNER_SPREAD / 100 * (SCREEN_SCALE.x + SCREEN_SCALE.y) * HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS / 10 / 250 * 1.2;
	float corner_fade_width_outer = HBR_CORNER_OUTER_SPREAD / 100 * (SCREEN_SCALE.x + SCREEN_SCALE.y) * HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS / 10 / 250 * 1.6;
	float corner_fade_width = (corner_fade_width_inner + fade_out_to_corner * (corner_fade_width_outer - corner_fade_width_inner));

	// Get a vector perpendicular to the crease that we can shift the crease to blend between bottom/top and sides
	vec2 corner_crease_perp_dir = normalize(vec2(corner_crease_dir.y, corner_crease_dir.x));
	vec2 corner_coord_shifted = outermap_coord_warped_ctr_at_screen_corner - corner_crease_perp_dir * corner_fade_width / 2;
	vec2 corner_crease_dir_shifted = corner_crease_dir - corner_crease_perp_dir * corner_fade_width / 2;

	// Get the distance to this shifted crease
	float distance_from_crease_shifted = HHLP_GetDistanceToLine(corner_coord_shifted.x, corner_coord_shifted.y, 1, corner_crease_dir_shifted.y / corner_crease_dir_shifted.x, 0 );

	float top_half_mask = smoothstep(0.55, 0.5, outermap_coord.y);

	// Get a mask which transitions between sides and top/bottom at the corner crease  
	float top_bottom_vs_sides_mask = dot(normalize(corner_coord_shifted), normalize(corner_crease_dir_shifted)) > 0 ? 1 - smoothstep(0, corner_fade_width / 2, distance_from_crease_shifted) : 1;

	// Masks isolating specific parts
	float sides_mask = 1 - top_bottom_vs_sides_mask;
	float top_mask = top_half_mask * top_bottom_vs_sides_mask;
	float bottom_mask = (1 -top_half_mask) * top_bottom_vs_sides_mask;

	float corner_mask = smoothstep(corner_fade_width / 2, 0, distance_from_crease);

	float top_corner_mask = corner_mask * top_half_mask;
	float bottom_corner_mask = corner_mask * (1 - top_half_mask);

	float frame_inner_edge_mask = (HBZ_FRAME_INNER_EDGE_THICKNESS == 0) ? 0 : 1 - HSS_GetCornerMask(	(bezel_outside_coord - 0.5) * (1 + (HBZ_FRAME_INNER_EDGE_THICKNESS / 1000 / vec2(SCREEN_ASPECT, 1))) + 0.5, 
																										SCREEN_ASPECT, 
																										HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 
																										0.9);

	float noise_mask = clamp(fract(sin(dot(outermap_warped_coord_ctr + vec2(0.5, 0.5) + 1, vec2(12.9898, 78.233))) * 43758.5453), 0, 1);
	
	float tube_shadow_mask = HSS_GetCornerMask(tube_warped_coord_ctr + 0.5, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 0);
	float tube_edge_shadow_mult = HBZ_TUBE_EDGE_SHADOW * (tube_shadow_mask) + (1 - HBZ_TUBE_EDGE_SHADOW);
	crt_image_linear *= tube_edge_shadow_mult;

	//----------------------------------------------------
	// Tube Glass Image
	//----------------------------------------------------
	if (HBZ_TUBE_GLASS_IMAGE_OPACITY > 0)
	{
		vec4 tube_glass_color = HSS_Linearize(texture(TubeGlassImage, tube_warped_coord_ctr * 0.97 * 1 / HBZ_TUBE_GLASS_IMAGE_SCALE + 0.5), HSS_DEFAULT_SRGB_GAMMA);
		tube_glass_color.a *= (HBZ_TUBE_GLASS_IMAGE_OPACITY / 100) * tube_mask;
		crt_image_linear = BlendModeLayerMix(crt_image_linear, tube_glass_color, BLEND_MODE_ADD);
	}

	vec2 tiled_image_coord = mod(IMAGE_LAYER_COORD, 1);
	vec4 background_color = vec4(0);

	#ifndef REFLECTION_ONLY_PRESET
		if (SCREEN_ASPECT > 1)
		{
			background_color = texture(BackgroundImage, tiled_image_coord).rgba;
		}
		else 
		{
			background_color = texture(BackgroundVertImage, tiled_image_coord).rgba;
		}
		background_color = HSS_Linearize(background_color, HSS_DEFAULT_SRGB_GAMMA);


		float outside_tube_mask_wider = 1 - HSS_GetCornerMask(tube_warped_coord_ctr * 0.996 + 0.5, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 0.9);
		background_color *= HBZ_BACKGROUND_IMAGE_OPACITY * background_color.a * outside_tube_mask_wider;

		float vignette_shadow_mask = 0;
		vignette_shadow_mask += 0.75 * HHLP_QuadraticBezier(1 - HSS_GetVignetteFactor(VIEWPORT_COORD, HBZ_BACKGROUND_IMAGE_VIGNETTE_OPACITY), vec2(1, 0.5));
		vignette_shadow_mask += 0.5 * HBZ_BACKGROUND_IMAGE_VIGNETTE_OPACITY * HHLP_QuadraticBezier(smoothstep(outside_ratio_warped, 0, 0.1), vec2(1, 0.5));
		
		//----------------------------------------------------
		// Background Image - Applied Underneath Bezel
		//----------------------------------------------------

		// Add Background
		vec4 shaded_background_color = background_color;
		if (HBZ_BACKGROUND_IMAGE_VIGNETTE_OPACITY > 0)
		{
			shaded_background_color = mix(background_color, vec4(0, 0, 0, 1), vignette_shadow_mask);
		}
	#endif
	// ----------------------------------------------------
	// Generated Bezel - Applied ON TOP of the Image Bezel, BELOW the reflection
	// ----------------------------------------------------

	/* This first bit is to get a mapping of the space outside of the screen which is continuous
	This is more complicated than you would expect because since we are using curved coordinates 
	there are discontinuities outside the normal screen corners, e.g. where x > 1 and y > 1
	So instead of trying to use the coordinates from the screen/tube we use a larger space 
	and subtract the screen space to see how far we are outside of the sreen
	*/
	
	float hmbz_bezel_brightness_top = 0.5;
	float hmbz_bezel_brightness_sides = 1;
	float hmbz_bezel_brightness_bottom = 2;

	float hmbz_bezel_highlight_edge = 0.9;
	float hmbz_bezel_highlight_top = 0.2;
	float hmbz_bezel_highlight_bottom = 0.3;
	float hmbz_bezel_highlight_sides = 0.2;
	
	float hmbz_bezel_highlight_falloff_speed = 0.5;
	float hmbz_bezel_highlight_width = 0.25;

	#ifdef GLASS_PRESET
		float hmbz_bezel_edge_highlight_width = 0.55;
	#else
		float hmbz_bezel_edge_highlight_width = 0.8;
	#endif
	
	float hmbz_bezel_brightness_frame_inner_edge = 0.014;
	float hmbz_bezel_brightness_frame_outer_edge = 0.5;
	float hmbz_brightness_shadow = 0;
	float hmbz_frame_brightness = 100;

	vec3 base_color = mix(BEZEL_FRAME_ORIGINAL_COLOR_RGB, background_color.rgb, HBZ_BEZEL_COLOR_BLEND_WITH_IMAGE);

	vec3 base_color_with_noise = mix(base_color, 1.5 * base_color * noise_mask, HBZ_BEZEL_NOISE / 100);
	vec3 top_color = hmbz_bezel_brightness_top * HBZ_BEZEL_BRIGHTNESS / 100 * base_color_with_noise;
	vec3 bottom_color = hmbz_bezel_brightness_bottom * HBZ_BEZEL_BRIGHTNESS / 100 * base_color_with_noise;
	vec3 sides_color = hmbz_bezel_brightness_sides * HBZ_BEZEL_BRIGHTNESS / 100 * base_color_with_noise;

	vec3 frame_color = hmbz_frame_brightness / 100 * mix(base_color, 1.5 * base_color * noise_mask, 0.6 * HBZ_BEZEL_NOISE / 100);;
	
	#ifndef REFLECTION_ONLY_PRESET
		vec3 frame_outer_edge_color = hmbz_bezel_brightness_frame_outer_edge * base_color_with_noise; //TODO When Highlight is off frame inner edge is very dark
		vec3 outside_frame_color = hmbz_brightness_shadow * base_color_with_noise;
	#endif

	vec3 bezel_diffuse_color = mix(sides_color, top_color, top_mask);
	bezel_diffuse_color = mix(bezel_diffuse_color, bottom_color, bottom_mask);


	float top_center_highlight_mask 	= hmbz_bezel_highlight_top * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));
	float bottom_center_highlight_mask 	= hmbz_bezel_highlight_bottom * bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));
	float sides_highlight_mask 			= hmbz_bezel_highlight_sides * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(outermap_warped_coord_ctr.y)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));

	float edge_top_center_highlight_mask 		= hmbz_bezel_highlight_top * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 0));
	float edge_bottom_center_highlight_mask 	= hmbz_bezel_highlight_bottom * bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 0));
	float edge_sides_highlight_mask 			= hmbz_bezel_highlight_sides * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.y)), vec2(0.8, 0));

	#ifdef GLASS_PRESET
		edge_top_center_highlight_mask 		= 0.6 * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 1));
		edge_bottom_center_highlight_mask 	= bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 1));
		edge_sides_highlight_mask 			= 0.7 * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.y)), vec2(0.8, 1));
	#endif

	float edge_highlight_mask 	= hmbz_bezel_highlight_edge * edge_mask * (edge_top_center_highlight_mask + edge_bottom_center_highlight_mask + edge_sides_highlight_mask);

	// Combine all the individual highlights into one mask
	//(1 + HBZ_BEZEL_NOISE) * (1 - noise_mask * HBZ_BEZEL_NOISE) * 
	float combined_highlight_mask = (1 + 2.5 * HBZ_BEZEL_NOISE / 100) * (1 - noise_mask * 2.5 * HBZ_BEZEL_NOISE / 100) * (top_center_highlight_mask + bottom_center_highlight_mask + sides_highlight_mask);
	vec3 bezel_color = bezel_diffuse_color + HBZ_BEZEL_HIGHLIGHT / 100 * combined_highlight_mask;
	bezel_color += HBZ_BEZEL_HIGHLIGHT / 100 * edge_highlight_mask;
	
	#ifndef REFLECTION_ONLY_PRESET
		// Add the inner edge highlight on top of the bezel color which has it's own highlight
		vec3 frame_inner_edge_color = bezel_color + hmbz_bezel_brightness_frame_inner_edge + HBZ_BEZEL_HIGHLIGHT * 0.1 * hmbz_bezel_brightness_frame_inner_edge;
		bezel_color = mix(bezel_color, frame_inner_edge_color, frame_inner_edge_mask);

		// Get color for the frame area outside of the bezel
		vec2 frame_outside_coord_ctr = frame_outside_coord - 0.5;
		float outside_frame_mask = 1 - HSS_GetCornerMask(frame_outside_coord_ctr + 0.5, SCREEN_ASPECT, HBZ_FRAME_OUTER_CORNER_RADIUS, 1);
		float outside_frame_mask_for_top_image = 1 - HSS_GetCornerMask(frame_outside_coord_ctr * 0.999 + 0.5, SCREEN_ASPECT, HBZ_FRAME_OUTER_CORNER_RADIUS, 1);

		float dist_inside_outer_edge = min(0.5 - abs(frame_outside_coord_ctr.x), 0.5 - abs(frame_outside_coord_ctr.y));
		float frame_outer_edge_width = 0.006;
		vec3 frame_diffuse_color = mix(frame_color, frame_outer_edge_color, smoothstep(frame_outer_edge_width, 0, dist_inside_outer_edge));
		
		frame_diffuse_color = mix(frame_diffuse_color, outside_frame_color, outside_frame_mask);

		// Composite in color from outside the bezel
		vec3 bezel_and_frame_color = mix(bezel_color, frame_diffuse_color, outside_bezel_mask);
		vec4 bezel_and_frame_color_v4 = clamp(vec4(bezel_and_frame_color.x, bezel_and_frame_color.y, bezel_and_frame_color.z, 1), 0, 1);

		float frame_edge = 0.495;

		// Get masks on side of frame to multiply together to get a shadow around the frame
		// Get vector from the screen edge outward
		float dist_outside_frame = length(clamp(abs(frame_outside_coord_ctr) - frame_edge, 0, 1) * vec2(SCREEN_ASPECT, 1));
		float frame_shadow_mask_0 = HHLP_QuadraticBezier(smoothstep(HBZ_FRAME_SHADOW_WIDTH / 100, 0, dist_outside_frame), vec2(1, 0));

		// Get masks for shadows, from frame as well as sides and top and bottom of viewport
		float bezel_mask = (1 - outside_bezel_mask) * outside_tube_mask;
		float frame_mask = outside_bezel_mask * (1 - outside_frame_mask);
		float frame_mask_for_top_image = outside_bezel_mask * (1 - outside_frame_mask_for_top_image);
		float frame_shadow_mask = outside_frame_mask * frame_shadow_mask_0;

		// Get 
		float combined_bezel_frame_mask =  0;
		
		if (HBZ_BEZEL_OPACITY > 0.001)
		{
			combined_bezel_frame_mask += HBZ_BEZEL_OPACITY * bezel_mask;
		}
		if (HBZ_FRAME_OPACITY > 0.001)
		{
			combined_bezel_frame_mask += HBZ_FRAME_OPACITY * frame_mask;
			combined_bezel_frame_mask += HBZ_FRAME_OPACITY * HBZ_FRAME_SHADOW_OPACITY * frame_shadow_mask;
		}
		combined_bezel_frame_mask = clamp(combined_bezel_frame_mask, 0, 1) * outside_tube_mask;

		vec4 bezel_frame_bg_color = mix(shaded_background_color, bezel_and_frame_color_v4, combined_bezel_frame_mask);
		bezel_frame_bg_color = HSS_ApplyGamma(bezel_frame_bg_color, HBZ_BEZEL_GAMMA);

		// Add Bezel, Frame & Shadow color to the screen color
		vec4 frag_color_linear = mix(crt_image_linear, bezel_frame_bg_color, outside_tube_mask);
	#else
		vec4 frag_color_linear = mix(crt_image_linear, vec4(bezel_color, 1), outside_tube_mask);
	#endif

	#ifndef REFLECTION_ONLY_PRESET
		// Get the top image color and masking values if needed
		vec4 top_image = vec4(0);
		if (HTI_TOP_IMAGE_OPACITY > 0)
		{
			top_image = SCREEN_ASPECT < 1 ? texture(TopLayerVertImage, IMAGE_LAYER_COORD):
														texture(TopLayerImage,     IMAGE_LAYER_COORD);
			top_image = HSS_Linearize(top_image, HSS_DEFAULT_SRGB_GAMMA);

			// Get Mask for Top Layer Image
			#ifdef GLASS_PRESET
				float outside_tube_mask_for_top_image = clamp(outside_tube_mask - edge_mask, 0, 1);
			#else
				float outside_tube_mask_for_top_image = 1 - HSS_GetCornerMask((tube_coord_warped - 0.5) * 1.003 + 0.5, SCREEN_ASPECT, HBZ_FRAME_OUTER_CORNER_RADIUS, 1);
			#endif

			float top_image_mask = 1;
			top_image_mask = 	(HTI_TOP_IMAGE_MASK_MODE == MASK_MODE_ALL) ? 1 :
								(HTI_TOP_IMAGE_MASK_MODE == MASK_MODE_TUBE) ? tube_mask :
								(HTI_TOP_IMAGE_MASK_MODE == MASK_MODE_OUTSIDE_TUBE) ? outside_tube_mask_for_top_image :
								(HTI_TOP_IMAGE_MASK_MODE == MASK_MODE_FRAME) ? frame_mask_for_top_image :
								(HTI_TOP_IMAGE_MASK_MODE == MASK_MODE_OUTSIDE_BEZEL) ? outside_bezel_mask :
								(HTI_TOP_IMAGE_MASK_MODE == MASK_MODE_OUTSIDE_FRAME) ? outside_frame_mask_for_top_image : 1;

			// Apply masks and opacity to overlay image alpha
			top_image.a *= HTI_TOP_IMAGE_OPACITY / 100 * top_image_mask;
		}

		// Add the top image now if the blending needs to be applied under the reflection 
		if (HTI_TOP_IMAGE_OPACITY > 0 && HTI_TOP_IMAGE_BLEND_MODE > 2)
		{
			// Do blend mode layer mix
			frag_color_linear = BlendModeLayerMix(frag_color_linear, top_image, mod(HTI_TOP_IMAGE_BLEND_MODE, 3));
		}
	#endif

	//----------------------------------------------------
	// Reflection - Applied ON TOP of the Bezel
	//----------------------------------------------------
	vec4 reflected_color = vec4(0);
	if (HBR_GLOBAL_AMOUNT != 0)
	{
		
		#ifdef HSM_SPLIT_SCREEN_PRESET
			if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
			{
				HBR_RADIAL_FADE_WIDTH *= 1;
				HBR_RADIAL_FADE_HEIGHT *= 1;
			}
		#endif
		// Corner Mask for Specular highlights
		float fade_out_to_corner = smoothstep(0 + HBR_CORNER_FADE_DISTANCE / 100 / 2, 0 - HBR_CORNER_FADE_DISTANCE / 100 / 2, outside_ratio_warped);
		float corner_fade_mask = (top_corner_mask + bottom_corner_mask) * (HBR_CORNER_FADE / 100) * fade_out_to_corner * 2;

		// Radial fade - fading away from the edges of the screen
		float radial_fade_speed = 100;
		float radial_fade_sides = 1 - HHLP_QuadraticBezier(clamp_0_1(outside_ratio_warped / (HBR_RADIAL_FADE_WIDTH / 500)), vec2(1 - (radial_fade_speed / 100), 1));
		float radial_fade_top_bottom = 1 - HHLP_QuadraticBezier(clamp_0_1(outside_ratio_warped / (HBR_RADIAL_FADE_HEIGHT / 500)), vec2(1 - (radial_fade_speed / 100), 1));
		float radial_fade_mask = clamp_0_1((1 - sides_mask) * radial_fade_top_bottom
									+ sides_mask * radial_fade_sides);

		float radial_inner_fade_mask = clamp_0_1(0.3 + 0.7 * HHLP_QuadraticBezier(smoothstep(0.01, 0.3, outside_ratio_warped / (HBR_RADIAL_FADE_WIDTH / 500)), vec2(0.1, 0.3)));

		// Lateral fade - Fading left to right across the bottom or top to bottom along the sides 
		float distance_ratio = smoothstep(0, 0.075, outside_ratio_warped);
		float lateral_outer_fade_distance = HBR_LATERAL_OUTER_FADE_DISTANCE / 100;
		lateral_outer_fade_distance = 0.5 * lateral_outer_fade_distance + distance_ratio * 0.5 * lateral_outer_fade_distance;
		float lateral_fade_mask = (1 - sides_mask) * GetFade(abs(outermap_warped_coord_ctr.x) + (HBR_LATERAL_OUTER_FADE_POSITION / -1000) / SCREEN_ASPECT, 
																	outermap_screen_size_from_center.x,
																	outermap_screen_size_from_center.x * lateral_outer_fade_distance)
										+  sides_mask * GetFade(abs(outermap_warped_coord_ctr.y) + (HBR_LATERAL_OUTER_FADE_POSITION / -1000) / SCREEN_ASPECT, 
																outermap_screen_size_from_center.y, 
																outermap_screen_size_from_center.y * lateral_outer_fade_distance); 

		vec2 screen_coord_ctr = SCREEN_COORD - 0.5;

		// float edge_lateral_fade_mask = (1 - sides_mask) * smoothstep(0.5, 0.5 - 0.07 / SCREEN_ASPECT, abs(screen_coord_ctr.x))
		// 								+  sides_mask * smoothstep(0.5, 0.43, abs(screen_coord_ctr.y));

		// float lateral_fade_center_mask = (1 - sides_mask) * clamp_0_1(GetFade(abs(outermap_warped_coord_ctr.x), 0, 0.5))
		// 										+ sides_mask * clamp_0_1(GetFade(abs(outermap_warped_coord_ctr.y), 0, 0.5));

		float combined_fade_mask = radial_fade_mask * lateral_fade_mask;

		#ifdef HSM_SPLIT_SCREEN_PRESET
			if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 2)
			{
				// Add the split reflection area to the outside tube mask area
				float split_reflection_area_mask = HSS_GetSplitScreenAreaGradient(tube_coord_warped, 0.9, 0.04);
				outside_tube_mask = clamp(outside_tube_mask + screen_mask * split_reflection_area_mask, 0, 1);
				
				// Get a mask to fade out the sides and bezel inner edge around the split area
				float sides_split_fade_mask = 1 - HSS_GetSplitScreenAreaGradient(tube_coord_warped, 0.7, 1.5);
				combined_fade_mask *= sides_split_fade_mask;
				edge_mask *= sides_split_fade_mask;

				float fade_to_tube_edge = 1 - smoothstep(0.30, 0.6, abs(tube_coord_warped.x - 0.5));
				float split_fade_mask = screen_mask * (1 - HHLP_EasePowerOut(HSS_GetSplitScreenAreaGradient(tube_coord_warped, 0, 1.1), 1.5)) * fade_to_tube_edge;
				combined_fade_mask += split_fade_mask;
			}
			if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 4 || HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 5)
			{
				// Get a mask to fade out the sides and edges in and around the split area
				float sides_split_fade_mask = 1 - HSS_GetSplitScreenAreaGradient(tube_coord_warped, 0.2, 1.5);
				combined_fade_mask *= sides_split_fade_mask;
				edge_mask *= sides_split_fade_mask;
			}
		#endif

		// Put all the fades together into one mask
		float final_fade_mask = clamp_0_1(HBR_FADE_AMOUNT * combined_fade_mask) + 1 - HBR_FADE_AMOUNT;

		float stoichaic_blur_samples = HBR_NOISE_SAMPLES;
		float noise_falloff = 0.3;
		float stoichaic_blur_max = HHLP_QuadraticBezier(outside_ratio_warped, vec2(0, noise_falloff)) * 3;
		float stoichaic_blur_amount = HBR_NOISE_SAMPLE_DISTANCE;

		vec4 fullscreen_blurred_sampled_color = GetStoichaicBlurredSample(BR_MirrorFullscreenGlowPass, VIEWPORT_COORD.xy, stoichaic_blur_samples, (1 - corner_mask) * stoichaic_blur_max * 3, stoichaic_blur_amount);

		vec4 corner_reflection_color = fullscreen_blurred_sampled_color;
		
		vec4 fullscreen_glow_color = pow(fullscreen_blurred_sampled_color, vec4(HBR_FULLSCREEN_GLOW_GAMMA));
		
		vec4 diffused_reflection_color = texture(BR_MirrorReflectionDiffusedPass, VIEWPORT_COORD.xy);
		vec4 diffused_reflection_scatter_color = GetStoichaicBlurredSample(BR_MirrorReflectionDiffusedPass, VIEWPORT_COORD.xy, stoichaic_blur_samples, stoichaic_blur_max, stoichaic_blur_amount);
		vec4 diffused_reflection_blended_color = mix(diffused_reflection_color, diffused_reflection_scatter_color, HBR_NOISE_AMOUNT);

		vec4 blurred_reflection_scatter_color = GetStoichaicBlurredSample(BR_MirrorBlurredPass, VIEWPORT_COORD.xy, stoichaic_blur_samples, stoichaic_blur_max, stoichaic_blur_amount);
		vec4 blurred_reflection_blended_color = mix(blurred_reflection_color, blurred_reflection_scatter_color, HBR_NOISE_AMOUNT);

		// Add Fullscreen Glow
		float lateral_fade_outer_mask_for_glow = (lateral_fade_mask - 1) * 0.8 + 1;

		//Combine diffused and undiffused reflection
		
		vec4 bezel_reflected_color = (HBR_DIRECT_REFLECTION * blurred_reflection_blended_color + HBR_DIFFUSED_REFLECTION * diffused_reflection_blended_color) * final_fade_mask;

		//Screen transfer mode 1 - (1 - diffused_reflection_color) * (1 - blurred_reflection_color);

		// Add Reflection from corners which is sampled from the fullscreen glow
		bezel_reflected_color += HBR_CORNER_FADE * corner_reflection_color * corner_fade_mask;

		// Add Fullscreen Glow
		bezel_reflected_color += HBR_FULLSCREEN_GLOW / 100 * 1.5 * fullscreen_glow_color * radial_inner_fade_mask * lateral_fade_outer_mask_for_glow;

		// Add Bezel and Edge reflection together
		vec4 edge_reflected_color = 1.25 * HBR_INNER_EDGE_REFLECTION * (blurred_reflection_color + 0.50 * diffused_reflection_color);
		float reflection_area_mask = (1 - outside_bezel_mask) * outside_tube_mask;

		// Edge Reflection
		#ifdef GLASS_PRESET
			reflected_color += (1 - vignette_shadow_mask) * bezel_reflected_color;
			reflection_area_mask *= outside_tube_mask_wider;
		#else
			reflected_color += (1 - edge_mask) * bezel_reflected_color;
			reflected_color += edge_mask * (edge_reflected_color + HHLP_EasePowerIn(corner_mask, 1) * corner_reflection_color);
		#endif

		reflected_color = HBR_GLOBAL_AMOUNT * pow(reflected_color, vec4(HBR_GLOBAL_GAMMA_ADJUST));
		
		// Mask reflection to only appear inside the bezel
		reflected_color = clamp(reflected_color, 0, 1) * clamp(reflection_area_mask, 0, 1);

		// Add reflection_color with mask
		frag_color_linear += reflected_color;

		#ifdef GLASS_PRESET
			vec4 edge_color = HBR_GLOBAL_AMOUNT * pow(edge_reflected_color, vec4(HBR_GLOBAL_GAMMA_ADJUST));
			frag_color_linear = mix(frag_color_linear, edge_color, edge_mask * outside_tube_mask);
		#endif

		// Edge Full Screen Glow
		// Add Small amount of static glow on the edge (So when the screen is dark there is some highlight) as well as dynamic light
		vec4 edge_fullscreen_glow = HBR_INNER_EDGE_FULLSCREEN_GLOW * edge_highlight_mask * outside_tube_mask * (vec4(0.005) + (avg_lum_mult  + 0.5) * (2 * fullscreen_glow_color + vec4(0.01)));
		
		// Add Diffused reflection on top of the glass inner edge
		#ifdef GLASS_PRESET
			edge_fullscreen_glow += HBR_INNER_EDGE_FULLSCREEN_GLOW * 0.5 * edge_highlight_mask * outside_tube_mask * diffused_reflection_color;
		#endif

		frag_color_linear += clamp(edge_fullscreen_glow, 0, 1);
	}

	#ifndef REFLECTION_ONLY_PRESET
		// Add the top image now if the blending needs to be applied on top of the reflection 
		if (HTI_TOP_IMAGE_OPACITY > 0 && HTI_TOP_IMAGE_BLEND_MODE < 3)
		{
			// Do blend mode layer mix
			frag_color_linear = BlendModeLayerMix(frag_color_linear, top_image, HTI_TOP_IMAGE_BLEND_MODE);
		}
	#endif

	FragColor = HSS_ApplyGamma(clamp(frag_color_linear, 0, 1), HSS_DEFAULT_SRGB_GAMMA);
}