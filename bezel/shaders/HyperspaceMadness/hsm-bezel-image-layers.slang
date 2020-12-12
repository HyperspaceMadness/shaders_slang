#version 450

/*   
hsm-image-layers

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
#include "hsm-globals-and-all-params.inc"

#define DEFAULT_TUBE_SCALE_V 0.82987
#define DEFAULT_BEZEL_SCALE_V 0.91159

/////////////// DEFINES ///////////////

#define MASK_MODE_ALL 0
#define MASK_MODE_SCREEN 1
#define MASK_MODE_TUBE 2
#define MASK_MODE_INSIDE_BEZEL 3
#define MASK_MODE_BEZEL 4
#define MASK_MODE_OUTSIDE_TUBE 5
#define MASK_MODE_FRAME 6
#define MASK_MODE_OUTSIDE_BEZEL 7
#define MASK_MODE_OUTSIDE_FRAME 8

#define CUTOUT_MODE_OFF 0
#define CUTOUT_MODE_INSIDE 1
#define CUTOUT_MODE_OUTSIDE 1

#define IMAGE_SCALE_MODE_VIEWPORT 0
#define IMAGE_SCALE_MODE_SCREEN 1
#define IMAGE_SCALE_MODE_FRAME 2
#define IMAGE_SCALE_MODE_BG 3
#define IMAGE_SCALE_MODE_BEZELIMAGE 4
#define IMAGE_SCALE_MODE_DECAL 5

#define TEXTURE_ASPECT_MODE_VIEWPORT 0
#define TEXTURE_ASPECT_MODE_EXPLICIT 1
#define TEXTURE_ASPECT_MODE_4_3 2
#define TEXTURE_ASPECT_MODE_3_4 3
#define TEXTURE_ASPECT_MODE_16_9 4
#define TEXTURE_ASPECT_MODE_9_16 5

/////////////// Helper Functions ///////////////

float SCREEN_MASK = 0;
float TUBE_MASK = 0;
float BEZEL_MASK = 0;
float INSIDE_BEZEL_MASK = 0;
float OUTSIDE_TUBE_MASK_FOR_IMAGE = 0;
float FRAME_MASK = 0;
float FRAME_MASK_FOR_IMAGE = 0;
float OUTSIDE_BEZEL_MASK = 0;
float OUTSIDE_FRAME_MASK_FOR_IMAGE = 0;
float OUTSIDE_FRAME_MASK = 0;
float CUTOUT_MASK = 0;

float SCREEN_ASPECT = HSM_GetScreenAspect();
vec2 SCREEN_SCALE = HSM_GetScreenScale(SCREEN_ASPECT);
vec2 TUBE_SCALE = HSM_GetTubeScale(SCREEN_SCALE);
vec2 FRAME_SCALE = vec2(1);
vec2 BACKGROUND_SCALE = vec2(1);

/* Composite one image over top another using the alpha to blend
 * It is expected that the input colors have been already premultiplied
 * which means their rgb has already been multiplied by their alpha */
vec4 PreMultAlphaBlend(vec4 color_under, vec4 color_over)
{
	vec4 out_color = vec4(color_over.rgb + (color_under.rgb * (1 - color_over.a)), clamp(color_under.a + color_over.a, 0, 1));
	return out_color;
}

// Takes a viewport coordinate and gives a new coordinate scaled by the specific scale mode
// Takes into account the default sizes of each scale mode
vec2 GetScaledCoord(vec2 viewport_coord, vec2 background_coord, vec2 screen_coord, vec2 bezel_outside_coord, vec2 bezel_image_coord, vec2 decal_coord, float texture_aspect_mode, float explicit_texture_aspect, vec2 scale_offset, vec2 pos_offset, float scale_mode, float keep_aspect)
{
	if (texture_aspect_mode == TEXTURE_ASPECT_MODE_VIEWPORT)
		explicit_texture_aspect = global.OutputSize.x / global.OutputSize.y;
	if (texture_aspect_mode == TEXTURE_ASPECT_MODE_4_3)
		explicit_texture_aspect = 1.33333;
	if (texture_aspect_mode == TEXTURE_ASPECT_MODE_3_4)
		explicit_texture_aspect = 0.75;
	if (texture_aspect_mode == TEXTURE_ASPECT_MODE_16_9)
		explicit_texture_aspect = 1.7777;
	if (texture_aspect_mode == TEXTURE_ASPECT_MODE_9_16)
		explicit_texture_aspect = 0.5625;

	vec2 destination_scale = vec2(0.5);
	vec2 destination_pos_offset = pos_offset;
	vec2 destination_coord = viewport_coord / 0.5;
	float destination_aspect = 0.2;
	if (scale_mode == IMAGE_SCALE_MODE_VIEWPORT)
	{
		destination_coord = viewport_coord;
		destination_scale = vec2(1, 1);
		destination_aspect = global.OutputSize.x / global.OutputSize.y;
	}
	else if (scale_mode == IMAGE_SCALE_MODE_SCREEN)
	{
		destination_coord = screen_coord;
		destination_scale = vec2(1, 1) * (1 / DEFAULT_TUBE_SCALE_V);
		// destination_pos_offset += vec2(0, HSM_SCREEN_POSITION_Y);
		destination_aspect = (SCREEN_SCALE.x * global.OutputSize.x) / (SCREEN_SCALE.y * global.OutputSize.y);
	}
	else if (scale_mode == IMAGE_SCALE_MODE_FRAME)
	{
		destination_coord = bezel_outside_coord;
		destination_scale = vec2(1, 1) * (1 / DEFAULT_BEZEL_SCALE_V);
		// destination_pos_offset += vec2(0, HSM_SCREEN_POSITION_Y + HSM_BZL_OUTER_POSITION_Y);
		destination_aspect = (FRAME_SCALE.x * global.OutputSize.x) / (FRAME_SCALE.y * global.OutputSize.y);
	}
	else if (scale_mode == IMAGE_SCALE_MODE_BG)
	{
		destination_coord = background_coord;
		destination_scale = vec2(1, 1);
		destination_aspect = global.OutputSize.x / global.OutputSize.y;
	}
	else if (scale_mode == IMAGE_SCALE_MODE_BEZELIMAGE)
	{
		destination_coord = bezel_image_coord;
		destination_scale = vec2(1, 1);
		destination_aspect = global.OutputSize.x / global.OutputSize.y;
	}
	else if (scale_mode == IMAGE_SCALE_MODE_DECAL)
	{
		destination_coord = decal_coord;
		destination_scale = vec2(1, 1);
		destination_aspect = global.OutputSize.x / global.OutputSize.y;
	}

	// Find the aspect difference so the image can be shown without distortion
	// vec2 destination_size = destination_scale * global.OutputSize.xy;
	float aspect_difference = explicit_texture_aspect / destination_aspect;

	destination_scale *= (keep_aspect == 1) ? vec2(aspect_difference, 1) : vec2(1);
	destination_scale *= scale_offset;

	vec2 out_coord = HSM_GetInverseScaledCoord(destination_coord, destination_scale);
	out_coord += vec2(destination_pos_offset.x, destination_pos_offset.y);

	return out_coord;
}

// Return the mask for the specific mode
float GetMask(float mask_mode)
{
	float mask = 	(mask_mode == MASK_MODE_ALL) ? 1 :
					(mask_mode == MASK_MODE_SCREEN) ? SCREEN_MASK :
					(mask_mode == MASK_MODE_TUBE) ? TUBE_MASK :
					(mask_mode == MASK_MODE_INSIDE_BEZEL) ? INSIDE_BEZEL_MASK :
					(mask_mode == MASK_MODE_BEZEL) ? BEZEL_MASK :
					(mask_mode == MASK_MODE_OUTSIDE_TUBE) ? OUTSIDE_TUBE_MASK_FOR_IMAGE :
					(mask_mode == MASK_MODE_FRAME) ? FRAME_MASK :
					(mask_mode == MASK_MODE_OUTSIDE_BEZEL) ? OUTSIDE_BEZEL_MASK :
					(mask_mode == MASK_MODE_OUTSIDE_FRAME) ? OUTSIDE_FRAME_MASK : 0.5;
	return mask;
}

vec4 BlendMultiply(vec4 color_under, vec4 color_over, float opacity)
{
	float final_opacity = color_over.a * opacity;
	return vec4(color_under.rgb * (final_opacity * color_over.rgb + (1 - final_opacity) * vec3(1)), color_under.a);
}

// Assumes Opacity is already encoded in alpha
vec4 BlendModeLayerMix(vec4 color_under, vec4 color_over, float blend_mode, float mask_mode, float cutout_mode, float layer_opacity)
{
	if (blend_mode == 0)
		return color_under;
	
	float cutout_mask = 1;
	if (cutout_mode == CUTOUT_MODE_INSIDE)
		cutout_mask = CUTOUT_MASK;
	if (cutout_mode == CUTOUT_MODE_OUTSIDE)
		cutout_mask = 1 - CUTOUT_MASK;

	if (blend_mode == BLEND_MODE_OFF)
		return color_under;
	
	color_over.a *= layer_opacity * GetMask(mask_mode) * cutout_mask;

	vec4 out_color = vec4(0);

	if (blend_mode == BLEND_MODE_NORMAL)
	{
		color_over.rgb *= color_over.a;
		out_color = PreMultAlphaBlend(color_under, color_over);
	}
	else
	{
		vec4 blend_color = color_under; 
		if (blend_mode == BLEND_MODE_ADD)  	 		blend_color.rgb = color_under.rgb + color_over.rgb ;
		if (blend_mode == BLEND_MODE_MULTIPLY)  	blend_color.rgb = color_under.rgb * color_over.rgb ;

		out_color = vec4(clamp(mix(color_under.rgb, blend_color.rgb, color_over.a), 0, 1), color_under.a);
	}
	return out_color;
}

//TODO remove this and replace with simpler calls
float GetFade(float current_position, float corner_position, float fade_distance)
{
	return smoothstep(corner_position + fade_distance / 2, corner_position - fade_distance / 2, current_position);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma stage vertex

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 0) out vec2 VIEWPORT_WITH_POS_OFFSET_COORD;
layout(location = 3) out vec2 SCREEN_COORD;
layout(location = 6) out vec2 VIEWPORT_COORD;
layout(location = 8) out vec3 BEZEL_FRAME_ORIGINAL_COLOR_RGB;

//////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	gl_Position = global.MVP * Position;
	vec2 vTexCoord = TexCoord;

	if (HSM_FLIP_VIEWPORT_VERTICAL > 0.5)
		vTexCoord.y =  1 - vTexCoord.y;

	VIEWPORT_WITH_POS_OFFSET_COORD = HSM_GetCoordWithPositionOffset(vTexCoord * 1.0001);

	SCREEN_COORD = HSM_GetScreenVTexCoord(vTexCoord, SCREEN_SCALE);

	VIEWPORT_COORD = vTexCoord * 1.0001;

	// Not sure why we need linearize this but it seems to have a smoother range this way
	BEZEL_FRAME_ORIGINAL_COLOR_RGB = HSM_Linearize(vec4(HSM_HSVtoRGB(vec3(HSM_BZL_COLOR_HUE, HSM_BZL_COLOR_SATURATION, HSM_BZL_COLOR_VALUE)), 1), HSM_DEFAULT_SRGB_GAMMA).rgb;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma stage fragment

layout(location = 0) in vec2 VIEWPORT_WITH_POS_OFFSET_COORD;
layout(location = 3) in vec2 SCREEN_COORD;
layout(location = 6) in vec2 VIEWPORT_COORD;
layout(location = 8) in vec3 BEZEL_FRAME_ORIGINAL_COLOR_RGB;

layout(location = 0) out vec4 FragColor;

// Pass Framebuffer Textures
layout(set = 0, binding = 1) uniform sampler2D BR_MappingPass;
layout(set = 0, binding = 2) uniform sampler2D BR_CRTAndReflectionPass;

// Image Textures from disk
layout(set = 0, binding = 3)  uniform sampler2D BackgroundImage;
layout(set = 0, binding = 4)  uniform sampler2D BackgroundVertImage;
layout(set = 0, binding = 5)  uniform sampler2D CabinetGlassImage;
layout(set = 0, binding = 6)  uniform sampler2D BezelImage;
layout(set = 0, binding = 7)  uniform sampler2D BezelVertImage;
layout(set = 0, binding = 8)  uniform sampler2D FrameHighlightImage;
layout(set = 0, binding = 9)  uniform sampler2D DecalImage;
layout(set = 0, binding = 10) uniform sampler2D NightLightingImage;
layout(set = 0, binding = 11) uniform sampler2D LEDImage;
layout(set = 0, binding = 12) uniform sampler2D TopLayerImage;
layout(set = 0, binding = 13) uniform sampler2D TopLayerVertImage;

//////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	//----------------------------------------------------
	// CRT Pass
	//----------------------------------------------------
	// Get the CRT pass and make it in linear space & mask the area outside the screen
	vec4 crt_and_reflection_linear = texture(BR_CRTAndReflectionPass, VIEWPORT_COORD.xy); // HSM_Linearize(texture(BR_CRTAndReflectionPass, VIEWPORT_COORD.xy), HSM_DEFAULT_CRT_GAMMA);
	crt_and_reflection_linear.a = 1;
	vec4 crt_linear = crt_and_reflection_linear;

	// If the reflection was supposed to be the last pass just return the sample for this layer
	if (HSM_REFLECT_IS_LAST_PASS == 1)
	{
		FragColor = crt_and_reflection_linear;
		return;
	}

	vec2 tube_coord_warped = vec2(0, 0);
	float outside_tube_mask = 0;
	float edge_mask = 0;
	HSM_GetCachedCurvedValues(BR_MappingPass, VIEWPORT_COORD.xy, tube_coord_warped, outside_tube_mask, edge_mask);
	TUBE_MASK = 1 - outside_tube_mask;

	vec2 tube_warped_coord_ctr = tube_coord_warped - 0.5;


	vec2 screen_curved_coord = HSM_GetCurvedCoord(SCREEN_COORD, 1, SCREEN_ASPECT);

	float split_pos_1 = 0;
	float split_pos_2 = 0;
	float split_dist = 0;
	float split_axis_is_horizontal = 0;

	if (HSM_SPLITSCREEN_ON == 1)
	{

		HSM_GetSplitInfo(split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

		if (HSM_SPLITSCREEN_CENTER_FILL_MODE == 2)
		{
			float sides_split_fade_mask = 1 - HSM_GetSplitScreenAreaGradient(tube_coord_warped, 1, 0.04);
			crt_linear *= sides_split_fade_mask;
		}
		else
		{
			if (HSM_SPLITSCREEN_CENTER_FILL_MODE == 1)
				// Take the split area and re-map it to 0-1
				screen_curved_coord = HSM_Get0To1CoordFromSplitArea(screen_curved_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

			// If this is the split screen preset and we want to blend the center colors
			if (HSM_SPLITSCREEN_CENTER_FILL_MODE == 3 || HSM_SPLITSCREEN_CENTER_FILL_MODE == 4)
				float split_screen_area_mask = (1 - outside_tube_mask) * HHLP_EasePowerOut(HSM_GetSplitScreenAreaGradient(tube_coord_warped, 0.25, 1.25), 2);

			// If we should fade to black in the center
			if (HSM_SPLITSCREEN_CENTER_FILL_MODE > 3 && HSM_SPLITSCREEN_CENTER_FILL_MODE < 6)
			{
				float split_screen_area_mask = HHLP_EasePowerOut(HSM_GetSplitScreenAreaGradient(tube_coord_warped, 0.1, 1.4), 2);
				
				crt_linear *= 1 - split_screen_area_mask;
			}
		}
	}


	// Shrink the mask by 0.001 to clip off outer edge
	SCREEN_MASK = HSM_GetCornerMask(((screen_curved_coord - 0.5) * 1.001) + 0.5, SCREEN_ASPECT, HSM_SCREEN_CORNER_RADIUS, HSM_SCREEN_EDGE_SHARPNESS);

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
	vec2 outer_bezel_scale = vec2(HSM_BZL_WIDTH / SCREEN_ASPECT + 1, HSM_BZL_HEIGHT / 100 + 1);


	float screen_aspect = SCREEN_ASPECT;
	vec2 frame_pos_offset = vec2(0, HSM_BZL_OUTER_POSITION_Y / 100);

	// Need to put this before screen_scale_diagonal?
	vec2 screen_coord = SCREEN_COORD; //HSM_GetScreenVTexCoord(VIEWPORT_COORD, SCREEN_SCALE);
	vec2 screen_scale = SCREEN_SCALE;
	vec2 sub_screen_scale = SCREEN_SCALE;
	float frame_thickness = HSM_FRM_THICKNESS;

	if (HSM_SPLITSCREEN_ON == 1)
		// If we are using split screen with separate frames
		if (HSM_SPLITSCREEN_CENTER_FILL_MODE == 1)
		{
			outer_bezel_scale = split_axis_is_horizontal * vec2((outer_bezel_scale.x - 1) * 2 + 1, outer_bezel_scale.y) + (1 - split_axis_is_horizontal) * vec2(outer_bezel_scale.x, (outer_bezel_scale.y - 1) * 2 + 1);
			
			// Adjust the direction of position depending on if the screens are left & Right or Top and Bottom
			frame_pos_offset *= HSM_SetSplitAxisCoord(vec2(1,1), HSM_BZL_OUTER_POSITION_Y / 100,  split_axis_is_horizontal);
			
			// If this is the first screen invert the position offset, so the screens slide toward or away from each other 
			float in_first_half = HHLP_IsUnderValue(HSM_GetSplitAxisCoord1D(SCREEN_COORD, split_axis_is_horizontal), 0.5);
			frame_pos_offset *=  in_first_half * 1 + (1 - in_first_half) * -1;
		}

	outer_bezel_scale = (outer_bezel_scale - 1) * screen_scale_diagonal + 1;

	vec2 bezel_outside_coord = SCREEN_COORD + frame_pos_offset;

	// Only run curved coordinates if requested or we are using tilt
	if ((HSM_CURVATURE_MODE > 0) && ((HSM_CURVATURE_3D_TILT_ANGLE_X != 0) || (HSM_CURVATURE_3D_TILT_ANGLE_Y != 0)))
		bezel_outside_coord = HSM_GetCurvedCoord(bezel_outside_coord, 0, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);

	if (HSM_SPLITSCREEN_ON == 1)
		if (HSM_SPLITSCREEN_CENTER_FILL_MODE == 1)
		{
			// If this was on the first screen then flip it back
			bezel_outside_coord = HSM_Get0To1CoordFromSplitArea(bezel_outside_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);
			sub_screen_scale = split_axis_is_horizontal * vec2(split_pos_1 * SCREEN_SCALE.x, SCREEN_SCALE.y) + (1 - split_axis_is_horizontal) * vec2(SCREEN_SCALE.x, (1 - split_pos_2) * SCREEN_SCALE.y);
			frame_thickness *= 2;
		}

	vec2 black_edge_scale_offset = HSM_GetTubeScale(sub_screen_scale) / sub_screen_scale;

	bezel_outside_coord = HSM_GetInverseScaledCoord(bezel_outside_coord, black_edge_scale_offset * outer_bezel_scale) + vec2(0, HSM_BZL_OUTER_POSITION_Y / 100);
	vec2 frame_outside_coord = (bezel_outside_coord + vec2(0, HSM_FRM_OUTER_POS_Y) - 0.5) / vec2((frame_thickness * HSM_FRM_THICKNESS_SCALE_X) / (sub_screen_scale.x / sub_screen_scale.y * output_aspect) + 1, frame_thickness + 1) + 0.5;

	FRAME_SCALE = screen_scale * black_edge_scale_offset * outer_bezel_scale;

	if (HSM_BZL_OUTER_CURVATURE_SCALE > 0)
	{
		bezel_outside_coord = HSM_GetCurvedCoord(bezel_outside_coord, HSM_BZL_OUTER_CURVATURE_SCALE, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);

		if ( HSM_FRM_OUTER_CURVATURE_SCALE > 0)
			frame_outside_coord = HSM_GetCurvedCoord(frame_outside_coord, HSM_BZL_OUTER_CURVATURE_SCALE * HSM_FRM_OUTER_CURVATURE_SCALE, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);
	}

	OUTSIDE_BEZEL_MASK = 1 - HSM_GetCornerMask(bezel_outside_coord, SCREEN_ASPECT, HSM_FRM_INNER_CORNER_RADIUS_SCALE * HSM_BZL_OUTER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0.9);

	//----------------------------------------------------
	//  Calculate Corner Highlight Mask
	//----------------------------------------------------
	const float pi = 3.1415;

	// Get amount to shift the point at the outer corner to match the overall position offset
	vec2 pos_shift_offset = vec2(0, HSM_BZL_OUTER_POSITION_Y / 100) * SCREEN_SCALE.y / outermap_scale;
	pos_shift_offset *= outermap_coord.y > 0.5 ? 1 : -1;

	// Get the direction vector from the inner corner of the bezel pointing at the outer corner 
	vec2 corner_crease_dir = (outermap_screen_corner_ctr_coord + pos_shift_offset) / vec2(HSM_BZL_HEIGHT / 100 + 1, HSM_BZL_WIDTH + 1) - (outermap_screen_corner_ctr_coord) ;
	corner_crease_dir *= vec2(SCREEN_ASPECT, 1);

	float aspect_corner_length_scale_offset = SCREEN_ASPECT > 1 ? 0.9 : 1.5;
	float corner_crease_length = length(corner_crease_dir * aspect_corner_length_scale_offset);

	// A hack to adjust the angle offset, because without it the corner angle isn't pointing exactly at the corner
	// This offset is the opposite direction for vertical and horizontal aspect ratio
	float corner_rotation_offset = (SCREEN_COORD.y < 0.5) ? -HSM_REFLECT_CORNER_ROTATION_OFFSET_TOP : -HSM_REFLECT_CORNER_ROTATION_OFFSET_BOTTOM;

	if (HSM_SPLITSCREEN_CENTER_FILL_MODE == 1)
		corner_rotation_offset += SCREEN_ASPECT < 1 ? 13 : -13; 
	else
		if (HSM_CURVATURE_MODE == 0)
			// If we are using a 3d Curvature no offset is necessary
			corner_rotation_offset += (SCREEN_ASPECT > 1) ? 2 : 3;

	// Convert direction vector to an angle so we can rotate the corner crease direction
	float corner_angle_degrees = atan(corner_crease_dir.y / corner_crease_dir.x) / (2 * pi) * 360;

	corner_angle_degrees += corner_rotation_offset;
	float corner_angle_radians = corner_angle_degrees / 360 * 2 * pi;
	corner_crease_dir = vec2(cos(corner_angle_radians), sin(corner_angle_radians));

	// Get the distance perpendicular to the crease direction so we can use it to fade later
	float distance_from_crease = HHLP_GetDistanceToLine(outermap_coord_warped_ctr_at_screen_corner.x, outermap_coord_warped_ctr_at_screen_corner.y, 1, corner_crease_dir.y / corner_crease_dir.x, 0 );

	float fade_out_to_corner = HHLP_QuadraticBezier(clamp(length(outermap_warped_outside_screen_vector) / (corner_crease_length * 2), 0, 1), vec2(0.5, HSM_REFLECT_CORNER_SPREAD_FALLOFF / 100));

	float corner_fade_width_inner = HSM_REFLECT_CORNER_INNER_SPREAD / 100 * (SCREEN_SCALE.x + SCREEN_SCALE.y) * HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS / 10 / 250 * 1.2;
	float corner_fade_width_outer = HSM_REFLECT_CORNER_OUTER_SPREAD / 100 * (SCREEN_SCALE.x + SCREEN_SCALE.y) * HSM_BZL_OUTER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS / 10 / 250 * 1.6;
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

	float frame_inner_edge_mask = (HSM_FRM_INNER_EDGE_THICKNESS == 0) ? 0 : 1 - HSM_GetCornerMask(	(bezel_outside_coord - 0.5) * (1 + (HSM_FRM_INNER_EDGE_THICKNESS / vec2(SCREEN_ASPECT, 1))) + 0.5, 
																										SCREEN_ASPECT, 
																										HSM_FRM_INNER_CORNER_RADIUS_SCALE * HSM_BZL_OUTER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 
																										0.9);

	float noise_mask = clamp(fract(sin(dot(outermap_warped_coord_ctr + vec2(0.5, 0.5) + 1, vec2(12.9898, 78.233))) * 43758.5453), 0, 1);
	
	float outside_tube_mask_wider = 1 - HSM_GetCornerMask(tube_warped_coord_ctr * 0.996 + 0.5, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0.9);
	float tube_shadow_mask = HSM_GetCornerMask(tube_warped_coord_ctr + 0.5, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0);
	float tube_edge_shadow_mult = HSM_BZL_INNER_EDGE_SHADOW * (tube_shadow_mask) + (1 - HSM_BZL_INNER_EDGE_SHADOW);

	crt_linear.rgb *= tube_edge_shadow_mult * (1 - outside_tube_mask_wider);
	crt_linear.a = (1 - outside_tube_mask_wider);

	vec4 background_color = vec4(0);


	float edge_highlight_mask  = 0;


	vec2 background_coord_no_mirror = VIEWPORT_COORD;
	background_coord_no_mirror = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord, bezel_outside_coord, vec2(0), vec2(0),
									HSM_BG_TEXTURE_ASPECT_MODE, 
									HSM_BG_EXPLICIT_TEXTURE_ASPECT, 
									vec2(HSM_BG_SCALE * HSM_BG_SCALE_X, HSM_BG_SCALE), 
									vec2(0, HSM_BG_POS_Y), 
									HSM_BG_SCALE_MODE, 
									HSM_BG_SCALE_KEEP_ASPECT);

	vec2 background_coord = background_coord_no_mirror;

	if (HSM_BG_MIRROR_WRAP == 1)
		background_coord = HSM_GetMirrorWrapCoord(background_coord);

	if (SCREEN_ASPECT > 1)
		background_color = texture(BackgroundImage, background_coord).rgba;
	else 
		background_color = texture(BackgroundVertImage, background_coord).rgba;

	background_color = HSM_Linearize(background_color, HSM_DEFAULT_SRGB_GAMMA);

	// Premultiply background color
	background_color.rgb *= background_color.a * HSM_BG_BRIGHTNESS;
	BlendModeLayerMix(vec4(0), 
						background_color, 
						BLEND_MODE_NORMAL, 
						HSM_BG_MASK_MODE, 
						0,
						1);



	//----------------------------------------------------
	// Background Image - Applied Underneath Bezel
	//----------------------------------------------------

	// ----------------------------------------------------
	// Generated Bezel - Applied ON TOP of the Background, BELOW the reflection
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

	float hmbz_bezel_edge_highlight_width = 0.8;
	if (HSM_GLASS_BORDER_ON == 1)
		hmbz_bezel_edge_highlight_width = 0.55;
	
	float hmbz_bezel_brightness_frame_inner_edge = 0.014;
	float hmbz_bezel_brightness_frame_outer_edge = 0.0;
	float hmbz_brightness_shadow = 0;
	float hmbz_frame_brightness = 100;

	vec3 base_color = BEZEL_FRAME_ORIGINAL_COLOR_RGB;

	vec3 base_color_with_noise = mix(base_color, 1.5 * base_color * noise_mask, HSM_BZL_NOISE);
	vec3 top_color = hmbz_bezel_brightness_top * HSM_BZL_BRIGHTNESS / 100 * base_color_with_noise;
	vec3 bottom_color = hmbz_bezel_brightness_bottom * HSM_BZL_BRIGHTNESS / 100 * base_color_with_noise;
	vec3 sides_color = hmbz_bezel_brightness_sides * HSM_BZL_BRIGHTNESS / 100 * base_color_with_noise;

	vec3 frame_color = hmbz_frame_brightness / 100 * mix(base_color, 1.5 * base_color * noise_mask, 0.6 * HSM_BZL_NOISE);;
	
	vec3 outside_frame_color = hmbz_brightness_shadow * base_color_with_noise;

	vec3 bezel_diffuse_color = mix(sides_color, top_color, top_mask);
	bezel_diffuse_color = mix(bezel_diffuse_color, bottom_color, bottom_mask);

	float top_center_highlight_mask 	= hmbz_bezel_highlight_top * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));
	float bottom_center_highlight_mask 	= hmbz_bezel_highlight_bottom * bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));
	float sides_highlight_mask 			= hmbz_bezel_highlight_sides * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(outermap_warped_coord_ctr.y)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));

	float edge_top_center_highlight_mask 		= hmbz_bezel_highlight_top * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 0));
	float edge_bottom_center_highlight_mask 	= hmbz_bezel_highlight_bottom * bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 0));
	float edge_sides_highlight_mask 			= hmbz_bezel_highlight_sides * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.y)), vec2(0.8, 0));

	if (HSM_GLASS_BORDER_ON == 1)
	{
		edge_top_center_highlight_mask 		= 0.6 * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 1));
		edge_bottom_center_highlight_mask 	= bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 1));
		edge_sides_highlight_mask 			= 0.7 * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.y)), vec2(0.8, 1));
	}

	edge_highlight_mask 	= hmbz_bezel_highlight_edge * edge_mask * (edge_top_center_highlight_mask + edge_bottom_center_highlight_mask + edge_sides_highlight_mask);

	// Combine all the individual highlights into one mask
	float combined_highlight_mask = (1 + 2.5 * HSM_BZL_NOISE) * (1 - noise_mask * 2.5 * HSM_BZL_NOISE) * (top_center_highlight_mask + bottom_center_highlight_mask + sides_highlight_mask);
	vec3 bezel_color = bezel_diffuse_color + HSM_BZL_HIGHLIGHT / 100 * combined_highlight_mask;
	bezel_color += HSM_BZL_HIGHLIGHT / 100 * edge_highlight_mask;


	// Add the inner edge highlight on top of the bezel color which has it's own highlight
	vec3 frame_inner_edge_color = bezel_color + hmbz_bezel_brightness_frame_inner_edge + HSM_BZL_HIGHLIGHT * 0.1 * hmbz_bezel_brightness_frame_inner_edge;
	bezel_color = mix(bezel_color, frame_inner_edge_color, frame_inner_edge_mask);

	// Get color for the frame area outside of the bezel
	vec2 frame_outside_coord_ctr = frame_outside_coord - 0.5;
	OUTSIDE_FRAME_MASK = 1 - HSM_GetCornerMask(frame_outside_coord_ctr + 0.5, SCREEN_ASPECT, HSM_FRM_OUTER_CORNER_RADIUS, 1);
	OUTSIDE_FRAME_MASK_FOR_IMAGE = 1 - HSM_GetCornerMask(frame_outside_coord_ctr * 0.999 + 0.5, SCREEN_ASPECT, HSM_FRM_OUTER_CORNER_RADIUS, 1);

	float dist_inside_outer_edge = min(0.5 - abs(frame_outside_coord_ctr.x), 0.5 - abs(frame_outside_coord_ctr.y));
	float frame_outer_edge_width = HSM_FRM_OUTER_EDGE_THICKNESS * 0.006;
	vec3 frame_diffuse_color = mix(frame_color, (1 - HSM_FRM_OUTER_EDGE_SHADING) * frame_color, smoothstep(frame_outer_edge_width, 0, dist_inside_outer_edge));
	
	frame_diffuse_color = mix(frame_diffuse_color, outside_frame_color, OUTSIDE_FRAME_MASK);

	// Composite in color from outside the bezel
	vec3 bezel_and_frame_rgb = mix(bezel_color, frame_diffuse_color, OUTSIDE_BEZEL_MASK);

	float frame_edge = 0.495;

	// Get masks on side of frame to multiply together to get a shadow around the frame
	// Get vector from the screen edge outward
	float dist_outside_frame = length(clamp(abs(frame_outside_coord_ctr) - frame_edge, 0, 1) * vec2(SCREEN_ASPECT, 1));

	// Get masks for shadows, from frame as well as sides and top and bottom of viewport
	INSIDE_BEZEL_MASK = 1 - OUTSIDE_BEZEL_MASK;
	BEZEL_MASK = INSIDE_BEZEL_MASK * outside_tube_mask;
	float FRAME_MASK = OUTSIDE_BEZEL_MASK * (1 - OUTSIDE_FRAME_MASK);
	FRAME_MASK_FOR_IMAGE = OUTSIDE_BEZEL_MASK * (1 - OUTSIDE_FRAME_MASK_FOR_IMAGE);

	
	float FRAME_AND_BEZEL_MASK = outside_tube_mask * (1 - OUTSIDE_FRAME_MASK);

	vec4 frame_shadow_layer = vec4(0);
	if (HSM_FRM_OPACITY > 0.001)
		frame_shadow_layer.a = HHLP_QuadraticBezier(smoothstep(HSM_FRM_SHADOW_WIDTH / 100, 0, dist_outside_frame), vec2(1, 0));

	if (HSM_GLASS_BORDER_ON == 1)
		OUTSIDE_TUBE_MASK_FOR_IMAGE = clamp(outside_tube_mask - edge_mask, 0, 1);
	else
		OUTSIDE_TUBE_MASK_FOR_IMAGE = 1 - HSM_GetCornerMask((tube_coord_warped - 0.5) * 1.003 + 0.5, SCREEN_ASPECT, HSM_FRM_OUTER_CORNER_RADIUS, 1);

	//-----------------------------------------------------------------------------------------
	// Night Lighting Image
	//-----------------------------------------------------------------------------------------
	// Add Multiplied Image for Darkening
	// Sample the image and do some color correction
	vec4 night_lighting_image = vec4(0);
	if (HSM_NIGHT_OPACITY > 0)
	{
		vec2 night_lighting_coord = VIEWPORT_COORD;

		if (HSM_NIGHT_MIRROR_HORZ == 1)
			night_lighting_coord.x = (night_lighting_coord.x - 0.5) * -1 + 0.5;

		// Dithering if needed to reduce banding
		float blur_max_size = 1;
		float blur_amount = 0.2;
		
		night_lighting_image = HSM_GetStoichaicBlurredSample(NightLightingImage, night_lighting_coord.xy, HSM_NIGHT_DITHERING_SAMPLES, blur_max_size, blur_amount);
		night_lighting_image = HSM_Linearize(night_lighting_image, HSM_DEFAULT_SRGB_GAMMA);
		
		// Do HSV alterations on the night lighting image
		if (HSM_NIGHT_HUE != 0 || HSM_NIGHT_SATURATION != 1 || HSM_NIGHT_VALUE != 1)
		{
			vec3 night_lighting_image_hsv = HSM_RGBtoHSV(night_lighting_image.rgb);
			night_lighting_image_hsv.x += HSM_NIGHT_HUE;
			night_lighting_image_hsv.y *= HSM_NIGHT_SATURATION;
			night_lighting_image_hsv.z *= HSM_NIGHT_VALUE;
			night_lighting_image = vec4(HSM_HSVtoRGB(night_lighting_image_hsv), night_lighting_image.a);
		}
	}

	//----------------------------------------------------
	// Generated Bezel
	//----------------------------------------------------

	vec4 bezel_layer = vec4(0);
	vec4 frame_layer = vec4(0);

	if (HSM_BZL_OPACITY > 0 || HSM_FRM_OPACITY > 0)
	{
		vec4 bezel_and_frame_rgba = vec4(bezel_and_frame_rgb, 1);
		
		if (HSM_STATIC_LAYERS_GAMMA != 1)
			bezel_and_frame_rgba = HSM_ApplyGamma(bezel_and_frame_rgba, HSM_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HSM_NIGHT_OPACITY > 0)
			if (HSM_BZL_IMG_BLEND_MODE != BLEND_MODE_ADD)
				bezel_and_frame_rgba = BlendMultiply(bezel_and_frame_rgba, night_lighting_image, HSM_NIGHT_OPACITY);

		if (HSM_BZL_OPACITY > 0 )
			if (HSM_FRM_OPACITY > 0)
				bezel_layer = clamp(bezel_and_frame_rgba * FRAME_AND_BEZEL_MASK, 0, 1);
			else
				bezel_layer = clamp(bezel_and_frame_rgba * BEZEL_MASK, 0, 1);


		if (HSM_FRM_OPACITY > 0 )
			frame_layer = clamp(bezel_and_frame_rgba * FRAME_MASK, 0, 1);
	}

	//----------------------------------------------------
	// Bezel Image
	//----------------------------------------------------
	vec4 bezel_image = vec4(0);
	vec2 screen_coord_for_bezel_image = screen_coord;
	
	if (HSM_BZL_IMG_USE_CURVATURE == 1)
		screen_coord_for_bezel_image = screen_curved_coord;
	
	vec2 bezel_image_coord = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord_for_bezel_image, bezel_outside_coord, vec2(0), vec2(0),
											HSM_BZL_IMG_TEXTURE_ASPECT_MODE, 
											HSM_BZL_IMG_EXPLICIT_TEXTURE_ASPECT,
											vec2(HSM_BZL_IMG_SCALE * HSM_BZL_IMG_SCALE_X, HSM_BZL_IMG_SCALE), 
											vec2(0, HSM_BZL_IMG_POS_Y), 
											HSM_BZL_IMG_SCALE_MODE, 
											HSM_BZL_IMG_SCALE_KEEP_ASPECT);
	if (HSM_BZL_IMG_OPACITY > 0)
	{
		bezel_image = SCREEN_ASPECT < 1 ? texture(BezelVertImage, bezel_image_coord):
										  texture(BezelImage,     bezel_image_coord);

		bezel_image = HSM_Linearize(bezel_image, HSM_DEFAULT_SRGB_GAMMA);
		// bezel_image.rgb *= HSM_BZL_IMG_BRIGHTNESS;

		// Do HSV alterations on the night lighting image
		if (HSM_BZL_IMG_HUE != 0 || HSM_BZL_IMG_SATURATION != 1 || HSM_BZL_IMG_BRIGHTNESS != 1)
		{
			vec3 bezel_image_hsv = HSM_RGBtoHSV(bezel_image.rgb);
			bezel_image_hsv.x += HSM_BZL_IMG_HUE;
			bezel_image_hsv.y *= HSM_BZL_IMG_SATURATION;
			bezel_image_hsv.z *= HSM_BZL_IMG_BRIGHTNESS;
			bezel_image = vec4(HSM_HSVtoRGB(bezel_image_hsv), bezel_image.a);
		}

		if (HSM_STATIC_LAYERS_GAMMA != 1)
			bezel_image = HSM_ApplyGamma(bezel_image, HSM_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HSM_NIGHT_OPACITY > 0)
			if (HSM_BZL_IMG_BLEND_MODE != BLEND_MODE_ADD)
				bezel_image = BlendMultiply(bezel_image, night_lighting_image, HSM_NIGHT_OPACITY);

		// Premultiply Alpha
		bezel_image.rgb *= bezel_image.a;
	}

	vec4 reflection_linear = crt_and_reflection_linear;// * outside_tube_mask;

	//----------------------------------------------------
	// Frame Decal Image
	//----------------------------------------------------
	vec4 decal_image = vec4(0);
	vec2 decal_coord = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord, bezel_outside_coord, bezel_image_coord, vec2(0),
										HSM_DECAL_TEXTURE_ASPECT_MODE, 
										HSM_DECAL_EXPLICIT_TEXTURE_ASPECT, 
										vec2(HSM_DECAL_SCALE * HSM_DECAL_SCALE_X, HSM_DECAL_SCALE), 
										vec2(0, HSM_DECAL_POS_Y), 
										HSM_DECAL_SCALE_MODE, 
										HSM_DECAL_SCALE_KEEP_ASPECT);
	if (HSM_DECAL_OPACITY > 0)
	{
		decal_image = texture(DecalImage, decal_coord);
		decal_image = HSM_Linearize(decal_image, HSM_DEFAULT_SRGB_GAMMA);

		// STATIC GAMMA
		if (HSM_STATIC_LAYERS_GAMMA != 1)
			decal_image = HSM_ApplyGamma(decal_image, HSM_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HSM_NIGHT_OPACITY > 0)
			if (HSM_DECAL_BLEND_MODE != BLEND_MODE_ADD)
				decal_image = BlendMultiply(decal_image, night_lighting_image, HSM_NIGHT_OPACITY);

		decal_image.rgb *= decal_image.a;
	}

	vec4 top_image = vec4(0);
	vec2 top_image_coord = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord, bezel_outside_coord, bezel_image_coord, decal_coord,
						HSM_TOP_TEXTURE_ASPECT_MODE, 
						HSM_TOP_EXPLICIT_TEXTURE_ASPECT, 
						vec2(HSM_TOP_SCALE * HSM_TOP_SCALE_X, HSM_TOP_SCALE), 
						vec2(0, HSM_TOP_POS_Y), 
						HSM_TOP_SCALE_MODE, 
						HSM_TOP_SCALE_KEEP_ASPECT);
	if (HSM_TOP_MIRROR_WRAP == 1)
		top_image_coord = HSM_GetMirrorWrapCoord(top_image_coord);
	if (HSM_TOP_OPACITY > 0)
	{
		// Get the top image color and masking values if needed
		top_image = SCREEN_ASPECT < 1 ? texture(TopLayerVertImage, top_image_coord):
										texture(TopLayerImage,     top_image_coord);
		top_image = HSM_Linearize(top_image, HSM_DEFAULT_SRGB_GAMMA);

		// STATIC GAMMA
		if (HSM_STATIC_LAYERS_GAMMA != 1)
			top_image = HSM_ApplyGamma(top_image, HSM_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HSM_NIGHT_OPACITY > 0)
				if (HSM_TOP_BLEND_MODE != BLEND_MODE_ADD)
					top_image = BlendMultiply(top_image, night_lighting_image, HSM_NIGHT_OPACITY);

		top_image.rgb *= top_image.a;
	}
	
	//----------------------------------------------------
	// Cabinet Glass Image
	//----------------------------------------------------
	vec4 cab_glass_image = vec4(0);
	if (HSM_CAB_GLASS_OPACITY > 0)
	{
		vec2 cab_glass_coord = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord, bezel_outside_coord, bezel_image_coord, decal_coord,
						HSM_CAB_GLASS_TEXTURE_ASPECT_MODE, 
						HSM_CAB_GLASS_EXPLICIT_TEXTURE_ASPECT, 
						vec2(HSM_CAB_GLASS_SCALE * HSM_CAB_GLASS_SCALE_X, HSM_CAB_GLASS_SCALE), 
						vec2(0, HSM_CAB_GLASS_POS_Y), 
						HSM_CAB_GLASS_SCALE_MODE, 
						HSM_CAB_GLASS_SCALE_KEEP_ASPECT);

		// Add Scaling
		cab_glass_coord = (cab_glass_coord - 0.5) * 1 / HSM_CAB_GLASS_SCALE + 0.5;

		cab_glass_image = texture(CabinetGlassImage, cab_glass_coord.xy);

		cab_glass_image = HSM_Linearize(cab_glass_image, HSM_DEFAULT_SRGB_GAMMA);
		cab_glass_image.rgb *= HSM_CAB_GLASS_BRIGHTNESS;

		// STATIC GAMMA
		if (HSM_STATIC_LAYERS_GAMMA != 1)
			cab_glass_image = HSM_ApplyGamma(cab_glass_image, HSM_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HSM_NIGHT_OPACITY > 0)
			if (HSM_CAB_GLASS_BLEND_MODE != BLEND_MODE_ADD)
				cab_glass_image = BlendMultiply(cab_glass_image, night_lighting_image, HSM_NIGHT_OPACITY);

		
		// cab_glass_image.rgb *= cab_glass_image.a;
	}

	//-----------------------------------------------------------------------------------------
	// LED Image
	//-----------------------------------------------------------------------------------------
	// Lights - Add small self illuminated lights on top of night image
	vec4 led_image = vec4(0);
	if (HSM_LED_OPACITY > 0)
	{
		vec2 led_coord = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord, bezel_outside_coord, bezel_image_coord, decal_coord,
						HSM_LED_TEXTURE_ASPECT_MODE, 
						HSM_LED_EXPLICIT_TEXTURE_ASPECT, 
						vec2(HSM_LED_SCALE * HSM_LED_SCALE_X, HSM_LED_SCALE), 
						vec2(0, HSM_LED_POS_Y), 
						HSM_LED_SCALE_MODE, 
						HSM_LED_SCALE_KEEP_ASPECT);

		led_image = texture(LEDImage, led_coord);
		led_image = HSM_Linearize(led_image, HSM_DEFAULT_SRGB_GAMMA);

		// STATIC GAMMA
		if (HSM_STATIC_LAYERS_GAMMA != 1)
			led_image = HSM_ApplyGamma(led_image, HSM_STATIC_LAYERS_GAMMA);

		led_image.rgb *= led_image.a;
	}

	//-----------------------------------------------------------------------------------------
	// BACKGROUND
	//-----------------------------------------------------------------------------------------
	if (HSM_BG_APPLY_ADJUSTMENT == 1)
		if (HSM_STATIC_LAYERS_GAMMA != 1)
			background_color = HSM_ApplyGamma(background_color, HSM_STATIC_LAYERS_GAMMA);

	// NIGHT LIGHTING
	if (HSM_BG_APPLY_ADJUSTMENT == 1)
		if (HSM_NIGHT_OPACITY > 0)
			background_color = BlendMultiply(background_color, night_lighting_image, HSM_NIGHT_OPACITY);

	// PREMULTIPLIED ALPHA
	background_color.rgb *= background_color.a;


	//-----------------------------------------------------------------------------------------
	// CUTOUT MASK
	//-----------------------------------------------------------------------------------------
	CUTOUT_MASK = 1;

	// vec2 cutout_coord = (bezel_outside_coord - 0.5) / vec2(HSM_CUTOUT_SCALE / (sub_screen_scale.x / sub_screen_scale.y * output_aspect) + 1, HSM_CUTOUT_SCALE_X + 1) + 0.5 + vec2(0, HSM_CUTOUT_POS_Y);
	
	vec2 cutout_coord = (VIEWPORT_COORD - 0.5) * 2 + 0.5;
	if (HSM_CUTOUT_SCALE_MODE == 1)
		cutout_coord = GetScaledCoord(screen_coord, vec2(0,0), vec2(0,0), vec2(0,0), vec2(0,0), vec2(0,0),
								TEXTURE_ASPECT_MODE_VIEWPORT,
								1,
								vec2(HSM_CUTOUT_SCALE * HSM_CUTOUT_SCALE_X, HSM_CUTOUT_SCALE), 
								vec2(0, HSM_CUTOUT_POS_Y), 
								IMAGE_SCALE_MODE_VIEWPORT, 
								0);
	else if (HSM_CUTOUT_SCALE_MODE == 2)
		cutout_coord = GetScaledCoord(bezel_outside_coord, vec2(0,0), vec2(0,0), vec2(0,0), vec2(0,0), vec2(0,0),
										TEXTURE_ASPECT_MODE_VIEWPORT,
										1,
										vec2(HSM_CUTOUT_SCALE * HSM_CUTOUT_SCALE_X, HSM_CUTOUT_SCALE), 
										vec2(0, HSM_CUTOUT_POS_Y), 
										IMAGE_SCALE_MODE_VIEWPORT, 
										0);
	else
	{
		cutout_coord = (VIEWPORT_COORD - 0.5) / vec2(DEFAULT_BEZEL_SCALE_V * screen_aspect / output_aspect, DEFAULT_BEZEL_SCALE_V) + 0.5;
		cutout_coord = GetScaledCoord(cutout_coord, background_coord_no_mirror, screen_coord_for_bezel_image, bezel_outside_coord, bezel_image_coord, decal_coord,
												TEXTURE_ASPECT_MODE_VIEWPORT,
												1,
												vec2(HSM_CUTOUT_SCALE * HSM_CUTOUT_SCALE_X, HSM_CUTOUT_SCALE), 
												vec2(0, HSM_CUTOUT_POS_Y), 
												HSM_CUTOUT_SCALE_MODE, 
												0);
		if (HSM_CUTOUT_SCALE_MODE > 2)
			cutout_coord = (cutout_coord - 0.5) / vec2(DEFAULT_BEZEL_SCALE_V * screen_aspect / output_aspect, DEFAULT_BEZEL_SCALE_V) + 0.5;

	}

	// vec2 cutout_coord = VIEWPORT_COORD; //(VIEWPORT_COORD - 0.5) * 2 + 0.5;

	if (HSM_CUTOUT_CORNER_RADIUS > 0)
		CUTOUT_MASK = 1 - HSM_GetCornerMask(cutout_coord, SCREEN_ASPECT, HSM_CUTOUT_CORNER_RADIUS, 1);
	else
		CUTOUT_MASK = 1 - HSM_GetCornerMask(cutout_coord, SCREEN_ASPECT, HSM_CUTOUT_CORNER_RADIUS, 1);

	//-----------------------------------------------------------------------------------------
	// Full Viewport Vignette
	//-----------------------------------------------------------------------------------------
	// TODO need to use scaling parameters for this
	vec4 vignette_layer = vec4(0);

	if (HSM_VIEWPORT_VIGNETTE_OPACITY > 0)
	{
		vec2 vignette_coord = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord, bezel_outside_coord, bezel_image_coord, decal_coord,
					TEXTURE_ASPECT_MODE_VIEWPORT, 
					1, 
					vec2(HSM_VIEWPORT_VIGNETTE_SCALE * HSM_VIEWPORT_VIGNETTE_SCALE_X, HSM_VIEWPORT_VIGNETTE_SCALE), 
					vec2(0, HSM_VIEWPORT_VIGNETTE_POS_Y), 
					HSM_VIEWPORT_VIGNETTE_SCALE_MODE, 
					0);

		vignette_layer.a += 0.75 * HHLP_QuadraticBezier(1 - HSM_GetVignetteFactor(vignette_coord, HSM_VIEWPORT_VIGNETTE_OPACITY), vec2(1, 0.5));
	}

	//-----------------------------------------------------------------------------------------
	// COMPOSITE ALL LAYERS
	//-----------------------------------------------------------------------------------------

	vec4 frag_color_linear = vec4(0);

	for(int i=0; i < 45; i++)
	{
		// BACKGROUND
		if (HSM_BG_LAYER_ORDER == i)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													background_color, 
													HSM_BG_BLEND_MODE, 
													HSM_BG_MASK_MODE, 
													HSM_BG_CUTOUT_MODE,
													HSM_BG_OPACITY);

		// VIGNETTE
		if (HSM_VIEWPORT_VIGNETTE_LAYER_ORDER == i)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													vignette_layer, 
													BLEND_MODE_NORMAL, 
													HSM_VIEWPORT_VIGNETTE_MASK_MODE, 
													HSM_VIEWPORT_VIGNETTE_CUTOUT_MODE,
													HSM_VIEWPORT_VIGNETTE_OPACITY);

		// CRT SCREEN
		if (HSM_CRT_LAYER_ORDER == i)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													crt_linear, 
													HSM_CRT_SCREEN_BLEND_MODE, 
													MASK_MODE_ALL, 
													0, 
													1);
		
		// BEZEL IMAGE
		if (HSM_BZL_IMG_LAYER_ORDER == i)
			if (HSM_BZL_IMG_OPACITY > 0)
				frag_color_linear = BlendModeLayerMix(frag_color_linear, 
														bezel_image, 
														HSM_BZL_IMG_BLEND_MODE, 
														HSM_BZL_IMG_MASK_MODE, 
														HSM_BZL_IMG_CUTOUT_MODE, 
														HSM_BZL_IMG_OPACITY);

		// GENERATED BEZEL LAYER
		if (HSM_BZL_LAYER_ORDER == i)
			if (HSM_BZL_OPACITY > 0)
				frag_color_linear = BlendModeLayerMix(frag_color_linear, 
														bezel_layer, 
														HSM_BZL_BLEND_MODE, 
														MASK_MODE_ALL, 
														0, 
														HSM_BZL_OPACITY);

		// ADD SHADOW OUTSIDE FRAME
		if (HSM_FRM_LAYER_ORDER == i)
			if (HSM_FRM_OPACITY > 0)
			{
				if (HSM_FRM_SHADOW_OPACITY > 0)
					frag_color_linear = BlendModeLayerMix(frag_color_linear, 
															frame_shadow_layer, 
															BLEND_MODE_NORMAL, 
															MASK_MODE_OUTSIDE_BEZEL,
															0, 
															HSM_FRM_OPACITY * HSM_FRM_SHADOW_OPACITY);


				// GENERATED FRAME LAYER
				frag_color_linear = BlendModeLayerMix(frag_color_linear, 
														frame_layer, 
														HSM_FRM_BLEND_MODE, 
														MASK_MODE_ALL, 
														0, 
														HSM_FRM_OPACITY);
			}

		// CABINET GLASS
		if (HSM_CAB_GLASS_LAYER_ORDER == i)
			if (HSM_CAB_GLASS_OPACITY > 0)
				frag_color_linear = BlendModeLayerMix(frag_color_linear, 
														cab_glass_image, 
														HSM_CAB_GLASS_BLEND_MODE, 
														HSM_CAB_GLASS_MASK_MODE, 
														HSM_CAB_GLASS_CUTOUT_MODE, 
														HSM_CAB_GLASS_OPACITY);

		// DECAL IMAGE
		if (HSM_DECAL_LAYER_ORDER == i)
			if (HSM_DECAL_OPACITY > 0)
				frag_color_linear = BlendModeLayerMix(frag_color_linear, 
														decal_image, 
														HSM_DECAL_BLEND_MODE, 
														HSM_DECAL_MASK_MODE, 
														HSM_DECAL_CUTOUT_MODE, 
														HSM_DECAL_OPACITY);

		// LED IMAGE
		if (HSM_LED_LAYER_ORDER == i)
			if (HSM_LED_OPACITY > 0)
				frag_color_linear = BlendModeLayerMix(frag_color_linear, 
														led_image, 
														HSM_LED_BLEND_MODE, 
														HSM_LED_MASK_MODE, 
														HSM_LED_CUTOUT_MODE, 
														HSM_LED_OPACITY);

		// REFLECTION
		if (HSM_REFLECT_LAYER_ORDER == i)
			if (HSM_REFLECT_BLEND_MODE > -1)
				if (HSM_REFLECT_GLOBAL_AMOUNT > 0)
					frag_color_linear = BlendModeLayerMix(frag_color_linear, 
															reflection_linear, 
															HSM_REFLECT_BLEND_MODE, 
															HSM_REFLECT_MASK_MODE, 
															0, 
															1);

		// Top Layer
		if (HSM_TOP_LAYER_ORDER == i)
			if (HSM_TOP_OPACITY > 0)
				frag_color_linear = BlendModeLayerMix(frag_color_linear, 
														top_image, 
														HSM_TOP_BLEND_MODE, 
														HSM_TOP_MASK_MODE, 
														HSM_TOP_CUTOUT_MODE, 
														HSM_TOP_OPACITY);
	}

	//-----------------------------------------------------------------------------------------
	// MASK DEBUG DISPLAY
	//-----------------------------------------------------------------------------------------
	// Show a red overlay on the screen showing the mask for each mask mode
	if (HSM_LAYERING_DEBUG_MASK_MODE != -1)
	{
		float debug_mask = 1;
		if (HSM_LAYERING_DEBUG_MASK_MODE == -2)
			debug_mask = CUTOUT_MASK;
		else
			debug_mask = GetMask(HSM_LAYERING_DEBUG_MASK_MODE);

		frag_color_linear = PreMultAlphaBlend(frag_color_linear, vec4(1, 0, 0, 1) * 0.15 * debug_mask);
		frag_color_linear = PreMultAlphaBlend(frag_color_linear, vec4(0.05, 0.05, 0.05, 1) * 0.15 * (1 - debug_mask));
		frag_color_linear = clamp(frag_color_linear, 0, 1);
	}


	// Convert from linear to gamma space values
	FragColor = HSM_ApplyGamma(clamp(frag_color_linear, 0, 1), HSM_DEFAULT_SRGB_GAMMA);
}


