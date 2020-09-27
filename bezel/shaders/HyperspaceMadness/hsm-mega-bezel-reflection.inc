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

#define MASK_MODE_ALL 0
#define MASK_MODE_TUBE 1
#define MASK_MODE_INSIDE_BEZEL 2
#define MASK_MODE_BEZEL 3
#define MASK_MODE_OUTSIDE_TUBE 4
#define MASK_MODE_FRAME 5
#define MASK_MODE_OUTSIDE_BEZEL 6
#define MASK_MODE_OUTSIDE_FRAME 7

#define IMAGE_SCALE_MODE_VIEWPORT 0
#define IMAGE_SCALE_MODE_TUBE 1
#define IMAGE_SCALE_MODE_BEZEL 2
#define IMAGE_SCALE_MODE_BG 3

/////////////// Helper Functions ///////////////

float TUBE_MASK = 0;
float BEZEL_MASK = 0;
float INSIDE_BEZEL_MASK = 0;
float OUTSIDE_TUBE_MASK_FOR_IMAGE = 0;
float FRAME_MASK_FOR_IMAGE = 0;
float OUTSIDE_BEZEL_MASK = 0;
float OUTSIDE_FRAME_MASK_FOR_IMAGE = 0;

float SCREEN_ASPECT = HSS_GetScreenAspect();
vec2 SCREEN_SCALE = HSS_GetScreenScale(SCREEN_ASPECT);
vec2 TUBE_SCALE = HSS_GetTubeScale(SCREEN_SCALE);
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
vec2 GetScaledCoord(vec2 viewport_coord, vec2 scale_offset, vec2 pos_offset, float scale_mode, float keep_aspect)
{
	// vec2 destination_scale = (scale_mode == IMAGE_SCALE_MODE_VIEWPORT) 	? vec2(1, 1) :
	// 						 (scale_mode == IMAGE_SCALE_MODE_TUBE) 		? TUBE_SCALE :
	// 						 (scale_mode == IMAGE_SCALE_MODE_BEZEL) 	? FRAME_SCALE :
	// 						 (scale_mode == IMAGE_SCALE_MODE_BG) 	? BACKGROUND_SCALE :
	// 						 vec2(0.5, 0.5);

	// /* Add a scaling offset to get the image to cover the full viewport 
	//  * when tube & frame are a default size */
	// destination_scale *= (scale_mode == IMAGE_SCALE_MODE_VIEWPORT) 	? 1 :
	// 					(scale_mode == IMAGE_SCALE_MODE_TUBE) 		? 1.1877 :
	// 					(scale_mode == IMAGE_SCALE_MODE_BEZEL) 		? 1.09698 :
	// 					(scale_mode == IMAGE_SCALE_MODE_BG) 		? 1 :
	// 					0.5;

	vec2 destination_scale = vec2(0.5);
	vec2 destination_pos_offset = pos_offset;
	if (scale_mode == IMAGE_SCALE_MODE_VIEWPORT)
	{
		destination_scale = vec2(1, 1);
	}
	else if (scale_mode == IMAGE_SCALE_MODE_TUBE)
	{
		destination_scale = TUBE_SCALE * 1.1877;
		destination_pos_offset += vec2(0, HSS_POSITION_OFFSET_Y);
	}
	else if (scale_mode == IMAGE_SCALE_MODE_BEZEL)
	{
		destination_scale = FRAME_SCALE * 1.09698;
		destination_pos_offset += vec2(0, HSS_POSITION_OFFSET_Y - HBZ_FRAME_POS_Y_OFFSET);
	}
	else if (scale_mode == IMAGE_SCALE_MODE_BG)
	{
		destination_scale = BACKGROUND_SCALE;
		destination_pos_offset += vec2(0, HLY_BG_IMAGE_POS_Y);
	}
	// If no scale mode is matched then this is viewport scale
	else
	{
		destination_scale = vec2(1, 1);
	}

	// Find the aspect difference so the image can be shown without distortion
	vec2 destination_size = destination_scale * global.OutputSize.xy;
	float aspect_difference = (global.OutputSize.x / global.OutputSize.y) / (destination_size.x / destination_size.y);

	destination_scale *= (keep_aspect == 1) ? vec2(aspect_difference, 1) : vec2(1);
	destination_scale *= scale_offset;

	vec2 out_coord = HSS_GetInverseScaledCoord(viewport_coord, destination_scale);
	out_coord += vec2(destination_pos_offset.x, destination_pos_offset.y);

		// vec2 frame_size = FRAME_SCALE * global.OutputSize.xy;
		// float frame_aspect = frame_size.x / frame_size.y;
		// float aspect_difference = output_aspect / frame_aspect;
	// vec2 decal_coord = HSS_GetInverseScaledCoord(VIEWPORT_COORD, 
	// 												1.05989 * FRAME_SCALE * (frame_thickness / 2 + 1) 
	// 												* vec2(HLY_DECAL_IMAGE_SCALE * HLY_DECAL_IMAGE_SCALE_X * aspect_difference, HLY_DECAL_IMAGE_SCALE));
	return out_coord;
}

// Return the mask for the specific mode
float GetMask(float mask_mode)
{
	float mask = 	(mask_mode == MASK_MODE_ALL) ? 1 :
					(mask_mode == MASK_MODE_TUBE) ? TUBE_MASK :
					(mask_mode == MASK_MODE_INSIDE_BEZEL) ? INSIDE_BEZEL_MASK :
					(mask_mode == MASK_MODE_BEZEL) ? BEZEL_MASK :
					(mask_mode == MASK_MODE_OUTSIDE_TUBE) ? OUTSIDE_TUBE_MASK_FOR_IMAGE :
					(mask_mode == MASK_MODE_FRAME) ? FRAME_MASK_FOR_IMAGE :
					(mask_mode == MASK_MODE_OUTSIDE_BEZEL) ? OUTSIDE_BEZEL_MASK :
					(mask_mode == MASK_MODE_OUTSIDE_FRAME) ? OUTSIDE_FRAME_MASK_FOR_IMAGE : 0.5;
	return mask;
}

// Assumes Opacity is already encoded in alpha
vec4 BlendModeLayerMix(vec4 color_under, vec4 color_over, float blend_mode, float mask_mode, float layer_opacity)
{
	color_over.a *= layer_opacity * GetMask(mask_mode);

	vec4 out_color = vec4(0);

	if (blend_mode == BLEND_MODE_NORMAL)
	{
		color_over.rgb *= layer_opacity * GetMask(mask_mode);
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

	if (HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL > 0.5)
		vTexCoord.y =  1 - vTexCoord.y;

	VIEWPORT_WITH_POS_OFFSET_COORD = HSS_GetCoordWithPositionOffset(vTexCoord * 1.0001);

	SCREEN_COORD = HSS_GetScreenVTexCoord(vTexCoord, SCREEN_SCALE);

	VIEWPORT_COORD = vTexCoord * 1.0001;

	// Not sure why we need linearize this but it seems to have a smoother range this way
	BEZEL_FRAME_ORIGINAL_COLOR_RGB = HSS_Linearize(vec4(HSS_HSVtoRGB(vec3(HBZ_BEZEL_COLOR_HUE, HBZ_BEZEL_COLOR_SATURATION, HBZ_BEZEL_COLOR_VALUE)), 1), HSS_DEFAULT_SRGB_GAMMA).rgb;
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

layout(set = 0, binding = 2) uniform sampler2D BR_CRTPass;
layout(set = 0, binding = 3) uniform sampler2D BR_MirrorBlurredPass;
layout(set = 0, binding = 4) uniform sampler2D BR_MirrorReflectionDiffusedPass;
layout(set = 0, binding = 5) uniform sampler2D BR_MirrorFullscreenGlowPass;
layout(set = 0, binding = 6) uniform sampler2D AvgLumPass;
layout(set = 0, binding = 7) uniform sampler2D TubeGlassImage;

// Image Textures from disk

#ifndef REFLECTION_ONLY_PRESET
layout(set = 0, binding = 8)  uniform sampler2D BackgroundImage;
layout(set = 0, binding = 9)  uniform sampler2D BackgroundVertImage;
layout(set = 0, binding = 10) uniform sampler2D BezelImage;
layout(set = 0, binding = 11) uniform sampler2D DecalImage;
layout(set = 0, binding = 12) uniform sampler2D NightLightingImage;
layout(set = 0, binding = 13) uniform sampler2D LEDImage;
layout(set = 0, binding = 14) uniform sampler2D TopLayerImage;
layout(set = 0, binding = 15) uniform sampler2D TopLayerVertImage;
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	vec2 tube_coord_warped = vec2(0, 0);
	float outside_tube_mask = 0;
	float edge_mask = 0;
	HSS_GetCachedCurvedValues(BR_MappingPass, VIEWPORT_COORD.xy, tube_coord_warped, outside_tube_mask, edge_mask);
	TUBE_MASK = 1 - outside_tube_mask;

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
	vec2 outer_bezel_scale = vec2(HBZ_BEZEL_WIDTH / SCREEN_ASPECT + 1, HBZ_BEZEL_HEIGHT / 100 + 1);


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

	// Only run curved coordinates if requested or we are using tilt
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
	vec2 frame_outside_coord = (bezel_outside_coord - 0.5) / vec2(frame_thickness/ (sub_screen_scale.x / sub_screen_scale.y * output_aspect) + 1, frame_thickness + 1) + 0.5;

	FRAME_SCALE = screen_scale * black_edge_scale_offset * outer_bezel_scale;

#ifndef REFLECTION_ONLY_PRESET
	if (HSS_BEZEL_OUTER_CURVATURE_SCALE > 0)
	{
		bezel_outside_coord = HSS_GetCurvedCoord(bezel_outside_coord, HSS_BEZEL_OUTER_CURVATURE_SCALE, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);

		if ( HSS_FRAME_OUTER_CURVATURE_SCALE > 0)
			frame_outside_coord = HSS_GetCurvedCoord(frame_outside_coord, HSS_BEZEL_OUTER_CURVATURE_SCALE * HSS_FRAME_OUTER_CURVATURE_SCALE, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);
	}
#endif

	OUTSIDE_BEZEL_MASK = 1 - HSS_GetCornerMask(bezel_outside_coord, SCREEN_ASPECT, HBZ_FRAME_INNER_CORNER_RADIUS_SCALE * HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 0.9);

	//----------------------------------------------------
	//  Calculate Corner Highlight Mask
	//----------------------------------------------------
	const float pi = 3.1415;

	// Get amount to shift the point at the outer corner to match the overall position offset
	vec2 pos_shift_offset = vec2(0, HBZ_FRAME_POS_Y_OFFSET / 100) * SCREEN_SCALE.y / outermap_scale;
	pos_shift_offset *= outermap_coord.y > 0.5 ? 1 : -1;

	// Get the direction vector from the inner corner of the bezel pointing at the outer corner 
	vec2 corner_crease_dir = (outermap_screen_corner_ctr_coord + pos_shift_offset) / vec2(HBZ_BEZEL_HEIGHT / 100 + 1, HBZ_BEZEL_WIDTH + 1) - (outermap_screen_corner_ctr_coord) ;
	corner_crease_dir *= vec2(SCREEN_ASPECT, 1);

	float aspect_corner_length_scale_offset = SCREEN_ASPECT > 1 ? 0.9 : 1.5;
	float corner_crease_length = length(corner_crease_dir * aspect_corner_length_scale_offset);

	// A hack to adjust the angle offset, because without it the corner angle isn't pointing exactly at the corner
	// This offset is the opposite direction for vertical and horizontal aspect ratio
	float corner_rotation_offset = (SCREEN_COORD.y < 0.5) ? -HBR_CORNER_ROTATION_OFFSET_TOP : -HBR_CORNER_ROTATION_OFFSET_BOTTOM;

	if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
		corner_rotation_offset += SCREEN_ASPECT < 1 ? 13 : -13; 
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

	float frame_inner_edge_mask = (HBZ_FRAME_INNER_EDGE_THICKNESS == 0) ? 0 : 1 - HSS_GetCornerMask(	(bezel_outside_coord - 0.5) * (1 + (HBZ_FRAME_INNER_EDGE_THICKNESS / vec2(SCREEN_ASPECT, 1))) + 0.5, 
																										SCREEN_ASPECT, 
																										HBZ_FRAME_INNER_CORNER_RADIUS_SCALE * HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 
																										0.9);

	float noise_mask = clamp(fract(sin(dot(outermap_warped_coord_ctr + vec2(0.5, 0.5) + 1, vec2(12.9898, 78.233))) * 43758.5453), 0, 1);
	
	float outside_tube_mask_wider = 1 - HSS_GetCornerMask(tube_warped_coord_ctr * 0.996 + 0.5, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 0.9);
	float tube_shadow_mask = HSS_GetCornerMask(tube_warped_coord_ctr + 0.5, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 0);
	float tube_edge_shadow_mult = HLY_TUBE_EDGE_SHADOW * (tube_shadow_mask) + (1 - HLY_TUBE_EDGE_SHADOW);
	crt_image_linear *= tube_edge_shadow_mult;
	crt_image_linear *= (1 - outside_tube_mask_wider);

	vec4 background_color = vec4(0);

	#ifndef REFLECTION_ONLY_PRESET
		vec2 background_coord = GetScaledCoord(VIEWPORT_COORD, 
												vec2(HLY_BG_IMAGE_SCALE * HLY_BG_IMAGE_SCALE_X, HLY_BG_IMAGE_SCALE), 
												vec2(0, HLY_BG_IMAGE_POS_Y), 
												HLY_BG_IMAGE_SCALE_MODE, 
												HLY_BG_IMAGE_SCALE_KEEP_ASPECT);

		
		if (HLY_BG_IMAGE_MIRROR_WRAP == 1)
			background_coord = HSS_GetMirrorWrapCoord(background_coord);

		if (SCREEN_ASPECT > 1)
			background_color = texture(BackgroundImage, background_coord).rgba;
		else 
			background_color = texture(BackgroundVertImage, background_coord).rgba;

		background_color = HSS_Linearize(background_color, HSS_DEFAULT_SRGB_GAMMA)
						   * background_color.a
						   * HLY_BG_IMAGE_BRIGHTNESS;

		if (HLY_CRT_SCREEN_BLEND_MODE == 0)
			background_color *= outside_tube_mask_wider;

		float vignette_shadow_mask = 0;
		vignette_shadow_mask += 0.75 * HHLP_QuadraticBezier(1 - HSS_GetVignetteFactor(VIEWPORT_COORD, HLY_BG_IMAGE_VIGNETTE_OPACITY), vec2(1, 0.5));
		vignette_shadow_mask += 0.5 * HLY_BG_IMAGE_VIGNETTE_OPACITY * HHLP_QuadraticBezier(smoothstep(outside_ratio_warped, 0, 0.1), vec2(1, 0.5));
		
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
		if (HGL_GLASSBORDER_ON == 1)
			hmbz_bezel_edge_highlight_width = 0.55;
		
		float hmbz_bezel_brightness_frame_inner_edge = 0.014;
		float hmbz_bezel_brightness_frame_outer_edge = 0.0;
		float hmbz_brightness_shadow = 0;
		float hmbz_frame_brightness = 100;

		vec3 base_color = mix(BEZEL_FRAME_ORIGINAL_COLOR_RGB, background_color.rgb, HBZ_BEZEL_COLOR_BLEND_WITH_IMAGE);

		vec3 base_color_with_noise = mix(base_color, 1.5 * base_color * noise_mask, HBZ_BEZEL_NOISE);
		vec3 top_color = hmbz_bezel_brightness_top * HBZ_BEZEL_BRIGHTNESS / 100 * base_color_with_noise;
		vec3 bottom_color = hmbz_bezel_brightness_bottom * HBZ_BEZEL_BRIGHTNESS / 100 * base_color_with_noise;
		vec3 sides_color = hmbz_bezel_brightness_sides * HBZ_BEZEL_BRIGHTNESS / 100 * base_color_with_noise;

		vec3 frame_color = hmbz_frame_brightness / 100 * mix(base_color, 1.5 * base_color * noise_mask, 0.6 * HBZ_BEZEL_NOISE);;
		
		vec3 outside_frame_color = hmbz_brightness_shadow * base_color_with_noise;

		vec3 bezel_diffuse_color = mix(sides_color, top_color, top_mask);
		bezel_diffuse_color = mix(bezel_diffuse_color, bottom_color, bottom_mask);


		float top_center_highlight_mask 	= hmbz_bezel_highlight_top * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));
		float bottom_center_highlight_mask 	= hmbz_bezel_highlight_bottom * bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));
		float sides_highlight_mask 			= hmbz_bezel_highlight_sides * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(outermap_warped_coord_ctr.y)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));

		float edge_top_center_highlight_mask 		= hmbz_bezel_highlight_top * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 0));
		float edge_bottom_center_highlight_mask 	= hmbz_bezel_highlight_bottom * bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 0));
		float edge_sides_highlight_mask 			= hmbz_bezel_highlight_sides * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.y)), vec2(0.8, 0));

		if (HGL_GLASSBORDER_ON == 1)
		{
			edge_top_center_highlight_mask 		= 0.6 * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 1));
			edge_bottom_center_highlight_mask 	= bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.x)), vec2(0.8, 1));
			edge_sides_highlight_mask 			= 0.7 * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(outermap_warped_coord_ctr.y)), vec2(0.8, 1));
		}

		float edge_highlight_mask 	= hmbz_bezel_highlight_edge * edge_mask * (edge_top_center_highlight_mask + edge_bottom_center_highlight_mask + edge_sides_highlight_mask);

		// Combine all the individual highlights into one mask
		float combined_highlight_mask = (1 + 2.5 * HBZ_BEZEL_NOISE) * (1 - noise_mask * 2.5 * HBZ_BEZEL_NOISE) * (top_center_highlight_mask + bottom_center_highlight_mask + sides_highlight_mask);
		vec3 bezel_color = bezel_diffuse_color + HBZ_BEZEL_HIGHLIGHT / 100 * combined_highlight_mask;
		bezel_color += HBZ_BEZEL_HIGHLIGHT / 100 * edge_highlight_mask;
	

		// Add the inner edge highlight on top of the bezel color which has it's own highlight
		vec3 frame_inner_edge_color = bezel_color + hmbz_bezel_brightness_frame_inner_edge + HBZ_BEZEL_HIGHLIGHT * 0.1 * hmbz_bezel_brightness_frame_inner_edge;
		bezel_color = mix(bezel_color, frame_inner_edge_color, frame_inner_edge_mask);

		// Get color for the frame area outside of the bezel
		vec2 frame_outside_coord_ctr = frame_outside_coord - 0.5;
		float outside_frame_mask = 1 - HSS_GetCornerMask(frame_outside_coord_ctr + 0.5, SCREEN_ASPECT, HBZ_FRAME_OUTER_CORNER_RADIUS, 1);
		OUTSIDE_FRAME_MASK_FOR_IMAGE = 1 - HSS_GetCornerMask(frame_outside_coord_ctr * 0.999 + 0.5, SCREEN_ASPECT, HBZ_FRAME_OUTER_CORNER_RADIUS, 1);

		float dist_inside_outer_edge = min(0.5 - abs(frame_outside_coord_ctr.x), 0.5 - abs(frame_outside_coord_ctr.y));
		float frame_outer_edge_width = HBZ_FRAME_OUTER_EDGE_THICKNESS * 0.006;
		vec3 frame_diffuse_color = mix(frame_color, (1 - HBZ_FRAME_OUTER_EDGE_SHADING) * frame_color, smoothstep(frame_outer_edge_width, 0, dist_inside_outer_edge));
		
		frame_diffuse_color = mix(frame_diffuse_color, outside_frame_color, outside_frame_mask);

		// Composite in color from outside the bezel
		vec3 bezel_and_frame_color = mix(bezel_color, frame_diffuse_color, OUTSIDE_BEZEL_MASK);

		float frame_edge = 0.495;

		// Get masks on side of frame to multiply together to get a shadow around the frame
		// Get vector from the screen edge outward
		float dist_outside_frame = length(clamp(abs(frame_outside_coord_ctr) - frame_edge, 0, 1) * vec2(SCREEN_ASPECT, 1));

		// Get masks for shadows, from frame as well as sides and top and bottom of viewport
		INSIDE_BEZEL_MASK = 1 - OUTSIDE_BEZEL_MASK;
		BEZEL_MASK = INSIDE_BEZEL_MASK * outside_tube_mask;
		float frame_mask = OUTSIDE_BEZEL_MASK * (1 - outside_frame_mask);
		FRAME_MASK_FOR_IMAGE = OUTSIDE_BEZEL_MASK * (1 - OUTSIDE_FRAME_MASK_FOR_IMAGE);

		// Get 
		float combined_bezel_frame_mask =  0;
		
		if (HBZ_BEZEL_OPACITY > 0.001)
			combined_bezel_frame_mask += HBZ_BEZEL_OPACITY * BEZEL_MASK;

		vec4 frame_shadow_layer = vec4(0);
		if (HBZ_FRAME_OPACITY > 0.001)
		{
			float frame_shadow_mask = HHLP_QuadraticBezier(smoothstep(HBZ_FRAME_SHADOW_WIDTH / 100, 0, dist_outside_frame), vec2(1, 0))
									* outside_frame_mask;

			combined_bezel_frame_mask += HBZ_FRAME_OPACITY * frame_mask;

			frame_shadow_layer.a = frame_shadow_mask;
		}

		combined_bezel_frame_mask = clamp(combined_bezel_frame_mask, 0, 1) * outside_tube_mask;

		// Premultiply the bezel & frame color
		bezel_and_frame_color *= combined_bezel_frame_mask;

		vec4 bezel_and_frame_layer = clamp(vec4(bezel_and_frame_color.x, bezel_and_frame_color.y, bezel_and_frame_color.z, combined_bezel_frame_mask), 0, 1);

	#endif

	//----------------------------------------------------
	// Reflection
	//----------------------------------------------------
	vec4 reflected_color = vec4(0);
	if (HBR_GLOBAL_AMOUNT > 0)
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
		float radial_fade_sides = 1 - HHLP_QuadraticBezier(clamp((outside_ratio_warped / (HBR_RADIAL_FADE_WIDTH / 500)), 0, 1), vec2(1 - (radial_fade_speed / 100), 1));
		float radial_fade_top_bottom = 1 - HHLP_QuadraticBezier(clamp((outside_ratio_warped / (HBR_RADIAL_FADE_HEIGHT / 500)), 0, 1), vec2(1 - (radial_fade_speed / 100), 1));
		float radial_fade_mask = clamp((1 - sides_mask) * radial_fade_top_bottom
									+ sides_mask * radial_fade_sides, 0, 1);

		float radial_inner_fade_mask = clamp(0.3 + 0.7 * HHLP_QuadraticBezier(smoothstep(0.01, 0.3, outside_ratio_warped / (HBR_RADIAL_FADE_WIDTH / 500)), vec2(0.1, 0.3)), 0, 1);

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
		float final_fade_mask = clamp(HBR_FADE_AMOUNT * combined_fade_mask, 0, 1) + 1 - HBR_FADE_AMOUNT;

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
		float reflection_area_mask = outside_tube_mask;

		// Edge Reflection
		if (HGL_GLASSBORDER_ON == 1)
		{
			reflected_color += (1 - vignette_shadow_mask) * bezel_reflected_color;
			reflection_area_mask *= outside_tube_mask_wider;
		}
		else
			reflected_color += (1 - edge_mask) * bezel_reflected_color 
							   + edge_mask * (edge_reflected_color + HHLP_EasePowerIn(corner_mask, 1) * corner_reflection_color);

		reflected_color = HBR_GLOBAL_AMOUNT * pow(reflected_color, vec4(HBR_GLOBAL_GAMMA_ADJUST));
		
		// Mask reflection to only appear inside the bezel
		reflected_color = clamp(reflected_color, 0, 1) * clamp(reflection_area_mask, 0, 1);

		// TODO need to address this glass preset for composite stack rework
		// // Add reflection_color with mask
		// frag_color_linear += reflected_color;

		// 	if (HGL_GLASSBORDER_ON == 1)
		// 	vec4 edge_color = HBR_GLOBAL_AMOUNT * pow(edge_reflected_color, vec4(HBR_GLOBAL_GAMMA_ADJUST));
		// 	frag_color_linear = mix(frag_color_linear, edge_color, edge_mask * outside_tube_mask);

		// Edge Full Screen Glow
		// Add Small amount of static glow on the edge (So when the screen is dark there is some highlight) as well as dynamic light
		vec4 edge_fullscreen_glow = HBR_INNER_EDGE_FULLSCREEN_GLOW * edge_highlight_mask * outside_tube_mask * (vec4(0.005) 
									+ (avg_lum_mult  + 0.5) * (2 * fullscreen_glow_color + vec4(0.01)));
		
		// Add Diffused reflection on top of the glass inner edge
		if (HGL_GLASSBORDER_ON == 1)
			edge_fullscreen_glow += HBR_INNER_EDGE_FULLSCREEN_GLOW * 0.5 * edge_highlight_mask * outside_tube_mask * diffused_reflection_color;

		reflected_color += clamp(edge_fullscreen_glow, 0, 1);
		reflected_color.a = 1;
	}

	//----------------------------------------------------
	// Tube Glass Image
	//----------------------------------------------------
	vec4 tube_reflection_image = vec4(0);
	if (HLY_TUBE_REFLECTION_IMAGE_OPACITY > 0)
	{
		tube_reflection_image = texture(TubeGlassImage, tube_warped_coord_ctr * 0.97 * 1 / HLY_TUBE_REFLECTION_IMAGE_SCALE + 0.5);
		tube_reflection_image = HSS_Linearize(tube_reflection_image, HSS_DEFAULT_SRGB_GAMMA);
	}

#ifndef REFLECTION_ONLY_PRESET

	if (HGL_GLASSBORDER_ON == 1)
		OUTSIDE_TUBE_MASK_FOR_IMAGE = clamp(outside_tube_mask - edge_mask, 0, 1);
	else
		OUTSIDE_TUBE_MASK_FOR_IMAGE = 1 - HSS_GetCornerMask((tube_coord_warped - 0.5) * 1.003 + 0.5, SCREEN_ASPECT, HBZ_FRAME_OUTER_CORNER_RADIUS, 1);

	//----------------------------------------------------
	// Background
	//----------------------------------------------------
	// Add Vignette to Background
	if (HLY_BG_IMAGE_VIGNETTE_OPACITY > 0)
	{
		background_color = mix(background_color, vec4(0, 0, 0, 1), vignette_shadow_mask);
		background_color = PreMultAlphaBlend(vec4(0, 0, 0, 1), background_color);
	}

	//----------------------------------------------------
	// Bezel Image
	//----------------------------------------------------
	vec4 bezel_image = vec4(0);
	if (HLY_BEZEL_IMAGE_OPACITY > 0)
	{
		vec2 bezel_coord = GetScaledCoord(VIEWPORT_COORD, 
							vec2(HLY_BEZEL_IMAGE_SCALE * HLY_BEZEL_IMAGE_SCALE_X, HLY_BEZEL_IMAGE_SCALE), 
							vec2(0, HLY_BEZEL_IMAGE_POS_Y), 
							HLY_BEZEL_IMAGE_SCALE_MODE, 
							HLY_BEZEL_IMAGE_SCALE_KEEP_ASPECT);

		bezel_image = texture(BezelImage, bezel_coord);
		bezel_image = HSS_Linearize(bezel_image, HSS_DEFAULT_SRGB_GAMMA);
	}

	//----------------------------------------------------
	// Frame Decal Image
	//----------------------------------------------------
	vec4 decal_image = vec4(0);
	if (HLY_DECAL_IMAGE_OPACITY > 0)
	{
		vec2 frame_size = FRAME_SCALE * global.OutputSize.xy;
		float frame_aspect = frame_size.x / frame_size.y;
		float aspect_difference = output_aspect / frame_aspect;

		// vec2 decal_coord = HSS_GetInverseScaledCoord(VIEWPORT_COORD, 
		// 											 1.05989 * FRAME_SCALE * (frame_thickness / 2 + 1) 
		// 											 * vec2(HLY_DECAL_IMAGE_SCALE * HLY_DECAL_IMAGE_SCALE_X * aspect_difference, HLY_DECAL_IMAGE_SCALE));
		// decal_coord += vec2(0, HLY_DECAL_IMAGE_POS_Y);

		vec2 decal_coord = GetScaledCoord(VIEWPORT_COORD, 
										  vec2(HLY_DECAL_IMAGE_SCALE * HLY_DECAL_IMAGE_SCALE_X, HLY_DECAL_IMAGE_SCALE), 
										  vec2(0, HLY_DECAL_IMAGE_POS_Y), 
										  HLY_DECAL_IMAGE_SCALE_MODE, 
										  HLY_DECAL_IMAGE_SCALE_KEEP_ASPECT);

		decal_image = texture(DecalImage, decal_coord);
		decal_image = HSS_Linearize(decal_image, HSS_DEFAULT_SRGB_GAMMA);
		decal_image.rgb *= decal_image.a;
	}

	//----------------------------------------------------
	// Top Image
	//----------------------------------------------------
	// TODO - Default Tube Height in horizontal = 0.8297
	
	//----------------------------------------------------
	// Night Lighting Image
	//----------------------------------------------------
	// Add Multiplied Image for Darkening
	vec4 night_lighting_image = vec4(0);
	if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
	{
		night_lighting_image = texture(NightLightingImage, VIEWPORT_COORD);
		night_lighting_image = HSS_Linearize(night_lighting_image, HSS_DEFAULT_SRGB_GAMMA);
		vec3 night_lighting_image_hsv = HSS_RGBtoHSV(night_lighting_image.rgb);
		vec3 hsv_adjust = vec3(1, HLY_NIGHTLIGHTING_IMAGE_SATURATION, 1);

		if (HLY_NIGHTLIGHTING_IMAGE_SATURATION != 1)
			night_lighting_image = vec4(HSS_HSVtoRGB(night_lighting_image_hsv * hsv_adjust), night_lighting_image.a);
	}

	vec4 top_image = vec4(0);
	if (HLY_TOP_IMAGE_OPACITY > 0)
	{
		vec2 top_image_coord = GetScaledCoord(VIEWPORT_COORD, 
							vec2(HLY_TOP_IMAGE_SCALE * HLY_TOP_IMAGE_SCALE_X, HLY_TOP_IMAGE_SCALE), 
							vec2(0, HLY_TOP_IMAGE_POS_Y), 
							HLY_TOP_IMAGE_SCALE_MODE, 
							HLY_TOP_IMAGE_SCALE_KEEP_ASPECT);

		if (HLY_BG_IMAGE_MIRROR_WRAP == 1)
			top_image_coord = HSS_GetMirrorWrapCoord(top_image_coord);

		// Get the top image color and masking values if needed
		top_image = SCREEN_ASPECT < 1 ? texture(TopLayerVertImage, top_image_coord):
										texture(TopLayerImage,     top_image_coord);
		top_image = HSS_Linearize(top_image, HSS_DEFAULT_SRGB_GAMMA);
		top_image.rgb *= top_image.a;
	}
	
	//----------------------------------------------------
	// LED Image
	//----------------------------------------------------
	// Lights - Add small self illuminated lights on top of night image
	vec4 led_image = vec4(0);
	if (HLY_LED_IMAGE_OPACITY > 0)
	{
		vec2 led_coord = HLY_LED_IMAGE_SCALE_MODE == 1 ? background_coord : VIEWPORT_COORD;
		led_image = texture(LEDImage, led_coord);
		led_image = HSS_Linearize(led_image, HSS_DEFAULT_SRGB_GAMMA);
		led_image.rgb *= led_image.a;
	}

	//------------------------------------------------------
	// COMPOSITE LAYERS
	//------------------------------------------------------

	//---------------------------------------------
	// Bottom Combined Layer - All the elements which go under the bezel
	//---------------------------------------------
	vec4 bottom_combined_layer = background_color;

	if (HLY_STATIC_ELEMENTS_GAMMA != 1)
	{
		// GAMMA ADJUST STATIC ELEMENTS
		bottom_combined_layer.rgb /= bottom_combined_layer.a;
		bottom_combined_layer.rgb = mix(bottom_combined_layer.rgb, HSS_ApplyGamma(bottom_combined_layer, HLY_STATIC_ELEMENTS_GAMMA).rgb, 
									OUTSIDE_TUBE_MASK_FOR_IMAGE);
		bottom_combined_layer.rgb *= bottom_combined_layer.a;
	}

	// NIGHT LIGHTING
	if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
		bottom_combined_layer = BlendModeLayerMix(bottom_combined_layer, 
												night_lighting_image, 
												BLEND_MODE_MULTIPLY, 
												MASK_MODE_OUTSIDE_TUBE, 
												HLY_NIGHTLIGHTING_IMAGE_OPACITY);

	// ADD CRT
	bottom_combined_layer = BlendModeLayerMix(bottom_combined_layer, 
												crt_image_linear, 
												HLY_CRT_SCREEN_BLEND_MODE, 
												MASK_MODE_ALL, 
												1);

	// ADD TUBE REFLECTION
	bottom_combined_layer = BlendModeLayerMix(bottom_combined_layer, 
												tube_reflection_image, 
												BLEND_MODE_ADD, 
												MASK_MODE_TUBE, 
												HLY_TUBE_REFLECTION_IMAGE_OPACITY);

	//---------------------------------------------
	// Mid Combined Layer - All the elements which go on top of the tube
	//						These are all affected by the Night Lighting Image
	//---------------------------------------------
	vec4 mid_combined_layer = vec4(0);


	// BEZEL IMAGE UNDER GENERATED BEZEL
	if (HLY_BEZEL_IMAGE_OPACITY > 0)
		if (HLY_BEZEL_IMAGE_DEPTH_ORDER == 0)
			mid_combined_layer = BlendModeLayerMix(mid_combined_layer, 
													bezel_image, 
													HLY_BEZEL_IMAGE_BLEND_MODE, 
													HLY_BEZEL_IMAGE_MASK_MODE, 
													HLY_BEZEL_IMAGE_OPACITY);

	// ADD TOP IMAGE under the bezel for Depth Order 0
	// This acts as sort of an additional background image and goes under the frame shadow
	if (HLY_TOP_IMAGE_OPACITY > 0)
		if (HLY_TOP_IMAGE_DEPTH_ORDER == 0)
			mid_combined_layer = BlendModeLayerMix(mid_combined_layer, 
													top_image, 
													HLY_TOP_IMAGE_BLEND_MODE, 
													HLY_TOP_IMAGE_MASK_MODE, 
													HLY_TOP_IMAGE_OPACITY);

	// ADD SHADOW OUTSIDE FRAME
	if (HBZ_FRAME_SHADOW_OPACITY > 0 && HBZ_FRAME_OPACITY > 0 && HLY_GENERATED_BEZEL_OPACITY > 0)
		mid_combined_layer = BlendModeLayerMix(mid_combined_layer, 
												frame_shadow_layer, 
												BLEND_MODE_NORMAL, 
												MASK_MODE_OUTSIDE_BEZEL, 
												HLY_GENERATED_BEZEL_OPACITY * HBZ_FRAME_OPACITY * HBZ_FRAME_SHADOW_OPACITY);

	// GENERATED BEZEL AND FRAME LAYER 
	bezel_and_frame_layer.rgb *= bezel_and_frame_layer.a;
	if (HLY_GENERATED_BEZEL_OPACITY > 0  && (HBZ_BEZEL_OPACITY > 0 || HBZ_FRAME_OPACITY > 0))
		mid_combined_layer = BlendModeLayerMix(mid_combined_layer, 
												bezel_and_frame_layer, 
												BLEND_MODE_NORMAL, 
												MASK_MODE_ALL, 
												HLY_GENERATED_BEZEL_OPACITY);

	// BEZEL IMAGE OVER GENERATED BEZEL
	if (HLY_BEZEL_IMAGE_OPACITY > 0)
		if (HLY_BEZEL_IMAGE_DEPTH_ORDER == 1)
			mid_combined_layer = BlendModeLayerMix(mid_combined_layer, 
													bezel_image, 
													HLY_BEZEL_IMAGE_BLEND_MODE, 
													HLY_BEZEL_IMAGE_MASK_MODE, 
													HLY_BEZEL_IMAGE_OPACITY);

	// DECAL IMAGE
	if (HLY_DECAL_IMAGE_OPACITY > 0)
		mid_combined_layer = BlendModeLayerMix(mid_combined_layer, 
												decal_image, 
												HLY_DECAL_IMAGE_BLEND_MODE, 
												HLY_DECAL_IMAGE_MASK_MODE, 
												HLY_DECAL_IMAGE_OPACITY);

	// GAMMA ADJUST STATIC ELEMENTS
	if (HLY_STATIC_ELEMENTS_GAMMA != 1)
	{
		mid_combined_layer.rgb /= mid_combined_layer.a;
		mid_combined_layer.rgb = HSS_ApplyGamma(mid_combined_layer, HLY_STATIC_ELEMENTS_GAMMA).rgb;
		mid_combined_layer.rgb *= mid_combined_layer.a;
	}

	// NIGHT LIGHTING
	if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
	{
		mid_combined_layer = BlendModeLayerMix(mid_combined_layer, 
												night_lighting_image, 
												BLEND_MODE_MULTIPLY, 
												MASK_MODE_ALL, 
												HLY_NIGHTLIGHTING_IMAGE_OPACITY);
	}

	//---------------------------------------------
	// Mid Additive Combined Layer
	//---------------------------------------------
	vec4 mid_additive_combined_layer = vec4(0);

	// LED IMAGE
	if (HLY_LED_IMAGE_OPACITY > 0)
		mid_additive_combined_layer = BlendModeLayerMix(mid_additive_combined_layer, 
														led_image, 
														BLEND_MODE_ADD, 
														HLY_LED_IMAGE_MASK_MODE, 
														HLY_LED_IMAGE_OPACITY);

	// REFLECTION
	if (HBR_GLOBAL_AMOUNT > 0)
		mid_additive_combined_layer = BlendModeLayerMix(mid_additive_combined_layer, 
														reflected_color, 
														HLY_REFLECTION_BLEND_MODE, 
														HLY_REFLECTION_MASK_MODE, 
														1);

	// Composite all combined layers
	vec4 frag_color_linear = vec4(0);
	frag_color_linear = PreMultAlphaBlend(bottom_combined_layer, mid_combined_layer);
	frag_color_linear = PreMultAlphaBlend(frag_color_linear, mid_additive_combined_layer);

	//---------------------------------------------
	// Top Combined Layer
	//---------------------------------------------
	if (HLY_TOP_IMAGE_OPACITY > 0)
		if (HLY_TOP_IMAGE_DEPTH_ORDER == 1)
		{
			// If applying the top image with normal blend Mode adjust with Gamma and Night Lighting
			if (HLY_TOP_IMAGE_BLEND_MODE == BLEND_MODE_NORMAL)
			{
				// Gamma Adjust top image
				if (HLY_STATIC_ELEMENTS_GAMMA != 1)
				{
					top_image.rgb /= top_image.a;
					top_image.rgb = HSS_ApplyGamma(top_image, HLY_STATIC_ELEMENTS_GAMMA).rgb;
					top_image.rgb *= top_image.a;
				}

				// Add Night Lighting to Top Image
				if (HLY_TOP_IMAGE_APPLY_NIGHT_LIGHTING == 1)
					top_image = BlendModeLayerMix(top_image, 
													night_lighting_image, 
													BLEND_MODE_MULTIPLY, 
													MASK_MODE_ALL, 
													HLY_NIGHTLIGHTING_IMAGE_OPACITY);
			}

			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													top_image, 
													HLY_TOP_IMAGE_BLEND_MODE, 
													HLY_TOP_IMAGE_MASK_MODE, 
													HLY_TOP_IMAGE_OPACITY);
		}
	
	// Show a red overlay on the screen showing the mask for each mask mode
	if (HLY_LAYERING_DEBUG_MASK_MODE > -1)
	{
		frag_color_linear = PreMultAlphaBlend(frag_color_linear, vec4(1, 0, 0, 1) * 0.15 * GetMask(HLY_LAYERING_DEBUG_MASK_MODE));
		frag_color_linear = PreMultAlphaBlend(frag_color_linear, vec4(0.05, 0.05, 0.05, 1) * 0.15 * (1 - GetMask(HLY_LAYERING_DEBUG_MASK_MODE)));
		frag_color_linear = clamp(frag_color_linear, 0, 1);
	}

#else // If this is a Reflection Only preset
		// CRT
		vec4 frag_color_linear = BlendModeLayerMix(frag_color_linear, crt_image_linear * outside_tube_mask_wider, HLY_CRT_SCREEN_BLEND_MODE, 1);
		// TUBE REFLECTION
		if (HLY_TUBE_REFLECTION_IMAGE_OPACITY > 0)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, tube_reflection_image, MASK_MODE_ADD, HLY_TUBE_REFLECTION_IMAGE_OPACITY);
		// REFLECTION
		frag_color_linear = BlendModeLayerMix(frag_color_linear, reflected_color, BLEND_MODE_ADD, HLY_REFLECTION_MASK_MODE, 1);
#endif

	// Convert from linear to gamma space values
	FragColor = HSS_ApplyGamma(clamp(frag_color_linear, 0, 1), HSS_DEFAULT_SRGB_GAMMA);
}