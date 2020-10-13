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
#define BLEND_MODE_OFF -1
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
#define IMAGE_SCALE_MODE_SCREEN 1
#define IMAGE_SCALE_MODE_FRAME 2
#define IMAGE_SCALE_MODE_BG 3
#define IMAGE_SCALE_MODE_BEZELIMAGE 4
#define IMAGE_SCALE_MODE_DECAL 5

/////////////// Helper Functions ///////////////

float TUBE_MASK = 0;
float BEZEL_MASK = 0;
float INSIDE_BEZEL_MASK = 0;
float OUTSIDE_TUBE_MASK_FOR_IMAGE = 0;
float FRAME_MASK = 0;
float FRAME_MASK_FOR_IMAGE = 0;
float OUTSIDE_BEZEL_MASK = 0;
float OUTSIDE_FRAME_MASK_FOR_IMAGE = 0;
float OUTSIDE_FRAME_MASK = 0;

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
vec2 GetScaledCoord(vec2 viewport_coord, vec2 background_coord, vec2 screen_coord, vec2 bezel_outside_coord, vec2 bezel_image_coord, vec2 decal_coord, vec2 scale_offset, vec2 pos_offset, float scale_mode, float keep_aspect)
{
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
		destination_scale = vec2(1, 1) * 1.205;
		// destination_pos_offset += vec2(0, HSS_POSITION_OFFSET_Y);
		destination_aspect = (SCREEN_SCALE.x * global.OutputSize.x) / (SCREEN_SCALE.y * global.OutputSize.y);
	}
	else if (scale_mode == IMAGE_SCALE_MODE_FRAME)
	{
		destination_coord = bezel_outside_coord;
		destination_scale = vec2(1, 1) * 1.09698;
		// destination_pos_offset += vec2(0, HSS_POSITION_OFFSET_Y + HBZ_FRAME_POS_Y_OFFSET);
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
	vec2 destination_size = destination_scale * global.OutputSize.xy;
	float aspect_difference = (global.OutputSize.x / global.OutputSize.y) / destination_aspect;

	destination_scale *= (keep_aspect == 1) ? vec2(aspect_difference, 1) : vec2(1);
	destination_scale *= scale_offset;

	vec2 out_coord = HSS_GetInverseScaledCoord(destination_coord, destination_scale);
	out_coord += vec2(destination_pos_offset.x, destination_pos_offset.y);

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
vec4 BlendModeLayerMix(vec4 color_under, vec4 color_over, float blend_mode, float mask_mode, float layer_opacity)
{
	if (blend_mode == BLEND_MODE_OFF)
		return color_under;
	
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
	return texture(in_sampler, in_coord);
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
layout(set = 0, binding = 2) uniform sampler2D BR_CRTAndReflectionPass;

// Image Textures from disk
layout(set = 0, binding = 3)  uniform sampler2D BackgroundImage;
layout(set = 0, binding = 4)  uniform sampler2D BackgroundVertImage;
layout(set = 0, binding = 5)  uniform sampler2D GlassImage;
layout(set = 0, binding = 6)  uniform sampler2D BezelImage;
layout(set = 0, binding = 7)  uniform sampler2D BezelVertImage;
layout(set = 0, binding = 8)  uniform sampler2D DecalImage;
layout(set = 0, binding = 9)  uniform sampler2D NightLightingImage;
layout(set = 0, binding = 10) uniform sampler2D LEDImage;
layout(set = 0, binding = 11) uniform sampler2D TopLayerImage;
layout(set = 0, binding = 12) uniform sampler2D TopLayerVertImage;

//////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	vec2 tube_coord_warped = vec2(0, 0);
	float outside_tube_mask = 0;
	float edge_mask = 0;
	HSS_GetCachedCurvedValues(BR_MappingPass, VIEWPORT_COORD.xy, tube_coord_warped, outside_tube_mask, edge_mask);
	TUBE_MASK = 1 - outside_tube_mask;

	vec2 tube_warped_coord_ctr = tube_coord_warped - 0.5;

	//----------------------------------------------------
	// CRT Pass
	//----------------------------------------------------
	// Get the CRT pass and make it in linear space & mask the area outside the screen


	vec4 crt_and_reflection_linear = texture(BR_CRTAndReflectionPass, VIEWPORT_COORD.xy); // HSS_Linearize(texture(BR_CRTAndReflectionPass, VIEWPORT_COORD.xy), HSS_DEFAULT_CRT_GAMMA);
	crt_and_reflection_linear.a = 1;

	vec4 crt_linear = crt_and_reflection_linear;

	vec2 screen_curved_coord = HSS_GetCurvedCoord(SCREEN_COORD, 1, SCREEN_ASPECT);

	float split_pos_1 = 0;
	float split_pos_2 = 0;
	float split_dist = 0;
	float split_axis_is_horizontal = 0;

	if (HSS_SPLIT_SCREEN_ON == 1)
	{

		HSS_GetSplitInfo(split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

		if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 2)
		{
			float sides_split_fade_mask = 1 - HSS_GetSplitScreenAreaGradient(tube_coord_warped, 1, 0.04);
			crt_linear *= sides_split_fade_mask;
		}
		else
		{
			if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
				// Take the split area and re-map it to 0-1
				screen_curved_coord = HSS_Get0To1CoordFromSplitArea(screen_curved_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

			// If this is the split screen preset and we want to blend the center colors
			if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 3 || HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 4)
				float split_screen_area_mask = (1 - outside_tube_mask) * HHLP_EasePowerOut(HSS_GetSplitScreenAreaGradient(tube_coord_warped, 0.25, 1.25), 2);

			// If we should fade to black in the center
			if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE > 3 && HSS_SPLIT_SCREEN_CENTER_FILL_MODE < 6)
			{
				float split_screen_area_mask = HHLP_EasePowerOut(HSS_GetSplitScreenAreaGradient(tube_coord_warped, 0.1, 1.4), 2);
				
				crt_linear *= 1 - split_screen_area_mask;
			}
		}
	}


	// Shrink the mask by 0.001 to clip off outer edge
	float screen_mask = HSS_GetCornerMask(((screen_curved_coord - 0.5) * 1.001) + 0.5, SCREEN_ASPECT, HSS_SCREENFX_CORNER_RADIUS, HSS_SCREENFX_EDGE_SHARPNESS);
	crt_linear *= screen_mask;
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
	vec2 screen_coord = SCREEN_COORD; //HSS_GetScreenVTexCoord(VIEWPORT_COORD, SCREEN_SCALE);
	vec2 screen_scale = SCREEN_SCALE;
	vec2 sub_screen_scale = SCREEN_SCALE;
	float frame_thickness = HBZ_FRAME_THICKNESS / 100;

	if (HSS_SPLIT_SCREEN_ON == 1)
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

	outer_bezel_scale = (outer_bezel_scale - 1) * screen_scale_diagonal + 1;

	vec2 bezel_outside_coord = SCREEN_COORD + frame_pos_offset;

	// Only run curved coordinates if requested or we are using tilt
	if ((HSS_CURVATURE_MODE > 0) && ((HSS_CURVATURE_3D_TILT_ANGLE_X != 0) || (HSS_CURVATURE_3D_TILT_ANGLE_Y != 0)))
		bezel_outside_coord = HSS_GetCurvedCoord(bezel_outside_coord, 0, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);

	if (HSS_SPLIT_SCREEN_ON == 1)
		if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
		{
			// If this was on the first screen then flip it back
			bezel_outside_coord = HSS_Get0To1CoordFromSplitArea(bezel_outside_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);
			sub_screen_scale = split_axis_is_horizontal * vec2(split_pos_1 * SCREEN_SCALE.x, SCREEN_SCALE.y) + (1 - split_axis_is_horizontal) * vec2(SCREEN_SCALE.x, (1 - split_pos_2) * SCREEN_SCALE.y);
			frame_thickness *= 2;
		}

	vec2 black_edge_scale_offset = HSS_GetTubeScale(sub_screen_scale) / sub_screen_scale;

	bezel_outside_coord = HSS_GetInverseScaledCoord(bezel_outside_coord, black_edge_scale_offset * outer_bezel_scale) + vec2(0, HBZ_FRAME_POS_Y_OFFSET / 100);
	vec2 frame_outside_coord = (bezel_outside_coord - 0.5) / vec2(frame_thickness/ (sub_screen_scale.x / sub_screen_scale.y * output_aspect) + 1, frame_thickness + 1) + 0.5;

	FRAME_SCALE = screen_scale * black_edge_scale_offset * outer_bezel_scale;

	if (HSS_BEZEL_OUTER_CURVATURE_SCALE > 0)
	{
		bezel_outside_coord = HSS_GetCurvedCoord(bezel_outside_coord, HSS_BEZEL_OUTER_CURVATURE_SCALE, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);

		if ( HSS_FRAME_OUTER_CURVATURE_SCALE > 0)
			frame_outside_coord = HSS_GetCurvedCoord(frame_outside_coord, HSS_BEZEL_OUTER_CURVATURE_SCALE * HSS_FRAME_OUTER_CURVATURE_SCALE, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y);
	}

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
		if (HSS_CURVATURE_MODE == 0)
			// If we are using a 3d Curvature no offset is necessary
			corner_rotation_offset += (SCREEN_ASPECT > 1) ? 2 : 3;

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
	float tube_edge_shadow_mult = HBZ_TUBE_EDGE_SHADOW * (tube_shadow_mask) + (1 - HBZ_TUBE_EDGE_SHADOW);

	crt_linear.rgb *= tube_edge_shadow_mult * (1 - outside_tube_mask_wider);
	crt_linear.a = (1 - outside_tube_mask_wider);

	vec4 background_color = vec4(0);

	float vignette_shadow_mask = 0;
	float edge_highlight_mask  = 0;


	vec2 background_coord_no_mirror = VIEWPORT_COORD;
	background_coord_no_mirror = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord, bezel_outside_coord, vec2(0), vec2(0),
									vec2(HLY_BG_IMAGE_SCALE * HLY_BG_IMAGE_SCALE_X, HLY_BG_IMAGE_SCALE), 
									vec2(0, HLY_BG_IMAGE_POS_Y), 
									HLY_BG_IMAGE_SCALE_MODE, 
									HLY_BG_IMAGE_SCALE_KEEP_ASPECT);

	vec2 background_coord = background_coord_no_mirror;

	if (HLY_BG_IMAGE_MIRROR_WRAP == 1)
		background_coord = HSS_GetMirrorWrapCoord(background_coord);

	if (SCREEN_ASPECT > 1)
		background_color = texture(BackgroundImage, background_coord).rgba;
	else 
		background_color = texture(BackgroundVertImage, background_coord).rgba;

	background_color = HSS_Linearize(background_color, HSS_DEFAULT_SRGB_GAMMA);

	// Premultiply background color
	background_color.rgb *= background_color.a * HLY_BG_IMAGE_BRIGHTNESS;
	BlendModeLayerMix(vec4(0), 
						background_color, 
						BLEND_MODE_NORMAL, 
						HLY_BG_IMAGE_MASK_MODE, 
						1);

	// if (HLY_CRT_SCREEN_BLEND_MODE == 0)
	// 	background_color *= outside_tube_mask_wider;


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

	edge_highlight_mask 	= hmbz_bezel_highlight_edge * edge_mask * (edge_top_center_highlight_mask + edge_bottom_center_highlight_mask + edge_sides_highlight_mask);

	// Combine all the individual highlights into one mask
	float combined_highlight_mask = (1 + 2.5 * HBZ_BEZEL_NOISE) * (1 - noise_mask * 2.5 * HBZ_BEZEL_NOISE) * (top_center_highlight_mask + bottom_center_highlight_mask + sides_highlight_mask);
	vec3 bezel_color = bezel_diffuse_color + HBZ_BEZEL_HIGHLIGHT / 100 * combined_highlight_mask;
	bezel_color += HBZ_BEZEL_HIGHLIGHT / 100 * edge_highlight_mask;


	// Add the inner edge highlight on top of the bezel color which has it's own highlight
	vec3 frame_inner_edge_color = bezel_color + hmbz_bezel_brightness_frame_inner_edge + HBZ_BEZEL_HIGHLIGHT * 0.1 * hmbz_bezel_brightness_frame_inner_edge;
	bezel_color = mix(bezel_color, frame_inner_edge_color, frame_inner_edge_mask);

	// Get color for the frame area outside of the bezel
	vec2 frame_outside_coord_ctr = frame_outside_coord - 0.5;
	OUTSIDE_FRAME_MASK = 1 - HSS_GetCornerMask(frame_outside_coord_ctr + 0.5, SCREEN_ASPECT, HBZ_FRAME_OUTER_CORNER_RADIUS, 1);
	OUTSIDE_FRAME_MASK_FOR_IMAGE = 1 - HSS_GetCornerMask(frame_outside_coord_ctr * 0.999 + 0.5, SCREEN_ASPECT, HBZ_FRAME_OUTER_CORNER_RADIUS, 1);

	float dist_inside_outer_edge = min(0.5 - abs(frame_outside_coord_ctr.x), 0.5 - abs(frame_outside_coord_ctr.y));
	float frame_outer_edge_width = HBZ_FRAME_OUTER_EDGE_THICKNESS * 0.006;
	vec3 frame_diffuse_color = mix(frame_color, (1 - HBZ_FRAME_OUTER_EDGE_SHADING) * frame_color, smoothstep(frame_outer_edge_width, 0, dist_inside_outer_edge));
	
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

	// Get 
	float combined_bezel_frame_mask =  0;
	
	if (HLY_BEZEL_OPACITY > 0.001)
		combined_bezel_frame_mask += HLY_BEZEL_OPACITY * BEZEL_MASK;

	vec4 frame_shadow_layer = vec4(0);
	if (HLY_FRAME_OPACITY > 0.001)
		frame_shadow_layer.a = HHLP_QuadraticBezier(smoothstep(HBZ_FRAME_SHADOW_WIDTH / 100, 0, dist_outside_frame), vec2(1, 0));

	if (HGL_GLASSBORDER_ON == 1)
		OUTSIDE_TUBE_MASK_FOR_IMAGE = clamp(outside_tube_mask - edge_mask, 0, 1);
	else
		OUTSIDE_TUBE_MASK_FOR_IMAGE = 1 - HSS_GetCornerMask((tube_coord_warped - 0.5) * 1.003 + 0.5, SCREEN_ASPECT, HBZ_FRAME_OUTER_CORNER_RADIUS, 1);

	//-----------------------------------------------------------------------------------------
	// Night Lighting Image
	//-----------------------------------------------------------------------------------------
	// Add Multiplied Image for Darkening
	// Sample the image and do some color correction
	vec4 night_lighting_image = vec4(0);
	if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
	{
		vec2 night_lighting_coord = VIEWPORT_COORD;

		if (HLY_NIGHTLIGHTING_IMAGE_MIRROR_HORZ == 1)
			night_lighting_coord.x = (night_lighting_coord.x - 0.5) * -1 + 0.5;

		// Dithering if needed to reduce banding
		float blur_max_size = 1;
		float blur_amount = 0.2;
		
		night_lighting_image = GetStoichaicBlurredSample(NightLightingImage, night_lighting_coord.xy, HLY_NIGHTLIGHTING_IMAGE_DITHERING_SAMPLES, blur_max_size, blur_amount);
		night_lighting_image = HSS_Linearize(night_lighting_image, HSS_DEFAULT_SRGB_GAMMA);
		
		// Do HSV alterations on the night lighting image
		if (HLY_NIGHTLIGHTING_IMAGE_HUE != 0 || HLY_NIGHTLIGHTING_IMAGE_SATURATION != 1 || HLY_NIGHTLIGHTING_IMAGE_VALUE != 1)
		{
			vec3 night_lighting_image_hsv = HSS_RGBtoHSV(night_lighting_image.rgb);
			night_lighting_image_hsv.x += HLY_NIGHTLIGHTING_IMAGE_HUE;
			night_lighting_image_hsv.y *= HLY_NIGHTLIGHTING_IMAGE_SATURATION;
			night_lighting_image_hsv.z *= HLY_NIGHTLIGHTING_IMAGE_VALUE;
			night_lighting_image = vec4(HSS_HSVtoRGB(night_lighting_image_hsv), night_lighting_image.a);
		}
	}

	//----------------------------------------------------
	// Background
	//----------------------------------------------------
	// Add Vignette to Background
	if (HLY_BG_IMAGE_VIGNETTE_OPACITY > 0)
	{
		background_color.rgb = mix(background_color.rgb, vec3(0), vignette_shadow_mask);
		background_color = PreMultAlphaBlend(vec4(0, 0, 0, 1), background_color);
	}

	//----------------------------------------------------
	// Generated Bezel
	//----------------------------------------------------

	vec4 bezel_layer = vec4(0);
	vec4 frame_layer = vec4(0);

	if (HLY_BEZEL_OPACITY > 0 || HLY_FRAME_OPACITY > 0)
	{
		vec4 bezel_and_frame_rgba = vec4(bezel_and_frame_rgb, 1);
		
		if (HLY_STATIC_LAYERS_GAMMA != 1)
			bezel_and_frame_rgba = HSS_ApplyGamma(bezel_and_frame_rgba, HLY_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
			if (HLY_BEZEL_IMAGE_BLEND_MODE != 1)
				bezel_and_frame_rgba = BlendMultiply(bezel_and_frame_rgba, night_lighting_image, HLY_NIGHTLIGHTING_IMAGE_OPACITY);

		if (HLY_BEZEL_OPACITY > 0 )
			bezel_layer = clamp(bezel_and_frame_rgba * BEZEL_MASK, 0, 1);

		if (HLY_FRAME_OPACITY > 0 )
			frame_layer = clamp(bezel_and_frame_rgba * FRAME_MASK, 0, 1);
	}

	//----------------------------------------------------
	// Bezel Image
	//----------------------------------------------------
	vec4 bezel_image = vec4(0);
	vec2 screen_coord_for_bezel_image = screen_coord;
	
	if (HLY_BEZEL_IMAGE_USE_CURVATURE == 1)
		screen_coord_for_bezel_image = screen_curved_coord;
	
	vec2 bezel_image_coord = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord_for_bezel_image, bezel_outside_coord, vec2(0), vec2(0),
											vec2(HLY_BEZEL_IMAGE_SCALE * HLY_BEZEL_IMAGE_SCALE_X, HLY_BEZEL_IMAGE_SCALE), 
											vec2(0, HLY_BEZEL_IMAGE_POS_Y), 
											HLY_BEZEL_IMAGE_SCALE_MODE, 
											HLY_BEZEL_IMAGE_SCALE_KEEP_ASPECT);
	if (HLY_BEZEL_IMAGE_OPACITY > 0)
	{
		bezel_image = SCREEN_ASPECT < 1 ? texture(BezelVertImage, bezel_image_coord):
										  texture(BezelImage,     bezel_image_coord);

		bezel_image = HSS_Linearize(bezel_image, HSS_DEFAULT_SRGB_GAMMA);
		bezel_image.rgb *= HLY_BEZEL_IMAGE_BRIGHTNESS;

		if (HLY_STATIC_LAYERS_GAMMA != 1)
			bezel_image = HSS_ApplyGamma(bezel_image, HLY_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
			if (HLY_BEZEL_IMAGE_BLEND_MODE != 1)
				bezel_image = BlendMultiply(bezel_image, night_lighting_image, HLY_NIGHTLIGHTING_IMAGE_OPACITY);

		// Premultiply Alpha
		bezel_image.rgb *= bezel_image.a;
	}

	vec4 reflection_linear = crt_and_reflection_linear * outside_tube_mask;

	//----------------------------------------------------
	// Frame Decal Image
	//----------------------------------------------------
	vec4 decal_image = vec4(0);
	vec2 decal_coord = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord, bezel_outside_coord, bezel_image_coord, vec2(0),
										vec2(HLY_DECAL_IMAGE_SCALE * HLY_DECAL_IMAGE_SCALE_X, HLY_DECAL_IMAGE_SCALE), 
										vec2(0, HLY_DECAL_IMAGE_POS_Y), 
										HLY_DECAL_IMAGE_SCALE_MODE, 
										HLY_DECAL_IMAGE_SCALE_KEEP_ASPECT);
	if (HLY_DECAL_IMAGE_OPACITY > 0)
	{
		decal_image = texture(DecalImage, decal_coord);
		decal_image = HSS_Linearize(decal_image, HSS_DEFAULT_SRGB_GAMMA);

		// STATIC GAMMA
		if (HLY_STATIC_LAYERS_GAMMA != 1)
			decal_image = HSS_ApplyGamma(decal_image, HLY_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
			if (HLY_DECAL_IMAGE_BLEND_MODE != 1)
				decal_image = BlendMultiply(decal_image, night_lighting_image, HLY_NIGHTLIGHTING_IMAGE_OPACITY);

		decal_image.rgb *= decal_image.a;
	}

	vec4 top_image = vec4(0);
	vec2 top_image_coord = GetScaledCoord(VIEWPORT_COORD, background_coord_no_mirror, screen_coord, bezel_outside_coord, bezel_image_coord, decal_coord,
						vec2(HLY_TOP_IMAGE_SCALE * HLY_TOP_IMAGE_SCALE_X, HLY_TOP_IMAGE_SCALE), 
						vec2(0, HLY_TOP_IMAGE_POS_Y), 
						HLY_TOP_IMAGE_SCALE_MODE, 
						HLY_TOP_IMAGE_SCALE_KEEP_ASPECT);
	if (HLY_TOP_IMAGE_MIRROR_WRAP == 1)
		top_image_coord = HSS_GetMirrorWrapCoord(top_image_coord);
	if (HLY_TOP_IMAGE_OPACITY > 0)
	{
		// Get the top image color and masking values if needed
		top_image = SCREEN_ASPECT < 1 ? texture(TopLayerVertImage, top_image_coord):
										texture(TopLayerImage,     top_image_coord);
		top_image = HSS_Linearize(top_image, HSS_DEFAULT_SRGB_GAMMA);

		// STATIC GAMMA
		if (HLY_STATIC_LAYERS_GAMMA != 1)
			top_image = HSS_ApplyGamma(top_image, HLY_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
			if (HLY_TOP_IMAGE_APPLY_NIGHT_LIGHTING == 1)
				if (HLY_TOP_IMAGE_BLEND_MODE != 1)
					top_image = BlendMultiply(top_image, night_lighting_image, HLY_NIGHTLIGHTING_IMAGE_OPACITY);

		top_image.rgb *= top_image.a;
	}
	
	//----------------------------------------------------
	// Tube Glass Image
	//----------------------------------------------------
	vec4 glass_image = vec4(0);
	if (HLY_GLASS_IMAGE_OPACITY > 0)
	{
		vec2 glass_coord = VIEWPORT_COORD * 2;

		if (HLY_GLASS_IMAGE_SCALE_MODE == 0)
			glass_coord = VIEWPORT_COORD;
		else if (HLY_GLASS_IMAGE_SCALE_MODE == 1)
			glass_coord = background_coord_no_mirror;
		else if (HLY_GLASS_IMAGE_SCALE_MODE == 2)
			glass_coord = tube_warped_coord_ctr * 0.97 + 0.5;
		else if (HLY_GLASS_IMAGE_SCALE_MODE == 3)
			glass_coord = bezel_image_coord;
		else if (HLY_GLASS_IMAGE_SCALE_MODE == 4)
			glass_coord = decal_coord;
		else if (HLY_GLASS_IMAGE_SCALE_MODE == 5)
			glass_coord = top_image_coord;

		// Add Scaling
		glass_coord = (glass_coord - 0.5) * 1 / HLY_GLASS_IMAGE_SCALE + 0.5;

		// Dithering for the glass reflection if needed to reduce banding
		float blur_max_size = 1;
		float blur_amount = 0.2;
		
		glass_image = GetStoichaicBlurredSample(GlassImage, glass_coord.xy, HLY_GLASS_IMAGE_DITHERING_SAMPLES, blur_max_size, blur_amount);
		glass_image = HSS_Linearize(glass_image, HSS_DEFAULT_SRGB_GAMMA);

		// STATIC GAMMA
		if (HLY_STATIC_LAYERS_GAMMA != 1)
			glass_image = HSS_ApplyGamma(glass_image, HLY_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
			if (HLY_GLASS_IMAGE_BLEND_MODE != 1)
				glass_image = BlendMultiply(glass_image, night_lighting_image, HLY_NIGHTLIGHTING_IMAGE_OPACITY);

		glass_image.rgb *= glass_image.a;
	}

	//-----------------------------------------------------------------------------------------
	// LED Image
	//-----------------------------------------------------------------------------------------
	// Lights - Add small self illuminated lights on top of night image
	vec4 led_image = vec4(0);
	if (HLY_LED_IMAGE_OPACITY > 0)
	{
		//0:Full Screen 1:BG 2:BEZEL 3:Top Image
		
		vec2 led_coord = VIEWPORT_COORD * 2;

		if (HLY_LED_IMAGE_SCALE_MODE == 0)
			led_coord = VIEWPORT_COORD;
		else if (HLY_LED_IMAGE_SCALE_MODE == 1)
			led_coord = background_coord_no_mirror;
		else if (HLY_LED_IMAGE_SCALE_MODE == 2)
			led_coord = bezel_image_coord;
		else if (HLY_LED_IMAGE_SCALE_MODE == 3)
			led_coord = decal_coord;
		else if (HLY_LED_IMAGE_SCALE_MODE == 4)
			led_coord = top_image_coord;

		led_image = texture(LEDImage, led_coord);
		led_image = HSS_Linearize(led_image, HSS_DEFAULT_SRGB_GAMMA);

		// STATIC GAMMA
		if (HLY_STATIC_LAYERS_GAMMA != 1)
			glass_image = HSS_ApplyGamma(glass_image, HLY_STATIC_LAYERS_GAMMA);

		led_image.rgb *= led_image.a;
	}

	//-----------------------------------------------------------------------------------------
	// BACKGROUND
	//-----------------------------------------------------------------------------------------
	if (HLY_BG_IMAGE_APPLY_NIGHT_LIGHTING_AND_STATIC_GAMMA == 1)
		if (HLY_STATIC_LAYERS_GAMMA != 1)
			background_color = HSS_ApplyGamma(background_color, HLY_STATIC_LAYERS_GAMMA);

	// NIGHT LIGHTING
	if (HLY_BG_IMAGE_APPLY_NIGHT_LIGHTING_AND_STATIC_GAMMA == 1)
		if (HLY_NIGHTLIGHTING_IMAGE_OPACITY > 0)
			background_color = BlendMultiply(background_color, night_lighting_image, HLY_NIGHTLIGHTING_IMAGE_OPACITY);

	// PREMULTIPLIED ALPHA
	background_color.rgb *= background_color.a;


	//-----------------------------------------------------------------------------------------
	// COMPOSITE ALL LAYERS
	//-----------------------------------------------------------------------------------------

	vec4 frag_color_linear = background_color;

	// BEZEL IMAGE UNDER GENERATED BEZEL
	if (HLY_BEZEL_IMAGE_OPACITY > 0)
		if (HLY_BEZEL_IMAGE_DEPTH_ORDER == 0)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													bezel_image, 
													HLY_BEZEL_IMAGE_BLEND_MODE, 
													HLY_BEZEL_IMAGE_MASK_MODE, 
													HLY_BEZEL_IMAGE_OPACITY);

	// ADD CRT
	frag_color_linear = BlendModeLayerMix(frag_color_linear, 
											crt_linear, 
											HLY_CRT_SCREEN_BLEND_MODE, 
											MASK_MODE_ALL, 
											1);
	

	// ADD GLASS REFLECTION
	if (HLY_GLASS_IMAGE_OPACITY > 0)
		if (HLY_GLASS_IMAGE_DEPTH_ORDER == 0)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													glass_image, 
													HLY_GLASS_IMAGE_BLEND_MODE, 
													HLY_GLASS_IMAGE_MASK_MODE, 
													HLY_GLASS_IMAGE_OPACITY);

	// BEZEL IMAGE UNDER GENERATED BEZEL
	if (HLY_BEZEL_IMAGE_OPACITY > 0)
		if (HLY_BEZEL_IMAGE_DEPTH_ORDER == 1)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													bezel_image, 
													HLY_BEZEL_IMAGE_BLEND_MODE, 
													HLY_BEZEL_IMAGE_MASK_MODE, 
													HLY_BEZEL_IMAGE_OPACITY);

	// ADD TOP IMAGE under the bezel for Depth Order 0
	// This acts as sort of an additional background image and goes under the frame shadow
	if (HLY_TOP_IMAGE_OPACITY > 0)
		if (HLY_TOP_IMAGE_DEPTH_ORDER == 0)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													top_image, 
													HLY_TOP_IMAGE_BLEND_MODE, 
													HLY_TOP_IMAGE_MASK_MODE, 
													HLY_TOP_IMAGE_OPACITY);

	// ADD SHADOW OUTSIDE FRAME
	if (HBZ_FRAME_SHADOW_OPACITY > 0 && HLY_FRAME_OPACITY > 0)
		frag_color_linear = BlendModeLayerMix(frag_color_linear, 
												frame_shadow_layer, 
												BLEND_MODE_NORMAL, 
												MASK_MODE_OUTSIDE_BEZEL, 
												HLY_FRAME_OPACITY * HBZ_FRAME_SHADOW_OPACITY);


	// GENERATED BEZEL LAYER
	if (HLY_BEZEL_OPACITY > 0)
		frag_color_linear = BlendModeLayerMix(frag_color_linear, 
												bezel_layer, 
												HLY_BEZEL_BLEND_MODE, 
												MASK_MODE_ALL, 
												HLY_BEZEL_OPACITY);

	// BEZEL IMAGE OVER GENERATED BEZEL
	if (HLY_BEZEL_IMAGE_OPACITY > 0)
		if (HLY_BEZEL_IMAGE_DEPTH_ORDER == 2)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													bezel_image, 
													HLY_BEZEL_IMAGE_BLEND_MODE, 
													HLY_BEZEL_IMAGE_MASK_MODE, 
													HLY_BEZEL_IMAGE_OPACITY);

	// GENERATED FRAME LAYER
	if (HLY_FRAME_OPACITY > 0)
		frag_color_linear = BlendModeLayerMix(frag_color_linear, 
												frame_layer, 
												HLY_FRAME_BLEND_MODE, 
												MASK_MODE_ALL, 
												HLY_FRAME_OPACITY);

	// BEZEL IMAGE OVER GENERATED BEZEL
	if (HLY_BEZEL_IMAGE_OPACITY > 0)
		if (HLY_BEZEL_IMAGE_DEPTH_ORDER == 3)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													bezel_image, 
													HLY_BEZEL_IMAGE_BLEND_MODE, 
													HLY_BEZEL_IMAGE_MASK_MODE, 
													HLY_BEZEL_IMAGE_OPACITY);

	// DECAL IMAGE
	if (HLY_DECAL_IMAGE_OPACITY > 0)
		frag_color_linear = BlendModeLayerMix(frag_color_linear, 
												decal_image, 
												HLY_DECAL_IMAGE_BLEND_MODE, 
												HLY_DECAL_IMAGE_MASK_MODE, 
												HLY_DECAL_IMAGE_OPACITY);

	// LED IMAGE
	if (HLY_LED_IMAGE_OPACITY > 0)
		frag_color_linear = BlendModeLayerMix(frag_color_linear, 
												led_image, 
												HLY_LED_IMAGE_BLEND_MODE, 
												HLY_LED_IMAGE_MASK_MODE, 
												HLY_LED_IMAGE_OPACITY);

	// REFLECTION
	if (HLY_REFLECTION_BLEND_MODE > -1)
		if (HBR_GLOBAL_AMOUNT > 0)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													reflection_linear, 
													HLY_REFLECTION_BLEND_MODE, 
													HLY_REFLECTION_MASK_MODE, 
													1);

	// ADD GLASS REFLECTION
	if (HLY_GLASS_IMAGE_OPACITY > 0)
		if (HLY_GLASS_IMAGE_DEPTH_ORDER == 1)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													glass_image, 
													HLY_GLASS_IMAGE_BLEND_MODE, 
													HLY_GLASS_IMAGE_MASK_MODE, 
													HLY_GLASS_IMAGE_OPACITY);

	// if (HGL_GLASSBORDER_ON == 1 && HBR_GLOBAL_AMOUNT > 0)
	// 	frag_color_linear = mix(frag_color_linear, glass_border_edge_color, edge_mask * outside_tube_mask);

	// frag_color_linear += edge_fullscreen_glow;

	//-----------------------------------------------------------------------------------------
	// Top Combined Layer
	//-----------------------------------------------------------------------------------------
	if (HLY_TOP_IMAGE_OPACITY > 0)
		if (HLY_TOP_IMAGE_DEPTH_ORDER == 1)
			frag_color_linear = BlendModeLayerMix(frag_color_linear, 
													top_image, 
													HLY_TOP_IMAGE_BLEND_MODE, 
													HLY_TOP_IMAGE_MASK_MODE, 
													HLY_TOP_IMAGE_OPACITY);
													
	//-----------------------------------------------------------------------------------------
	// MASK DEBUG DISPLAY
	//-----------------------------------------------------------------------------------------
	// Show a red overlay on the screen showing the mask for each mask mode
	if (HLY_LAYERING_DEBUG_MASK_MODE > -1)
	{
		frag_color_linear = PreMultAlphaBlend(frag_color_linear, vec4(1, 0, 0, 1) * 0.15 * GetMask(HLY_LAYERING_DEBUG_MASK_MODE));
		frag_color_linear = PreMultAlphaBlend(frag_color_linear, vec4(0.05, 0.05, 0.05, 1) * 0.15 * (1 - GetMask(HLY_LAYERING_DEBUG_MASK_MODE)));
		frag_color_linear = clamp(frag_color_linear, 0, 1);
	}

	// Convert from linear to gamma space values
	FragColor = HSS_ApplyGamma(clamp(frag_color_linear, 0, 1), HSS_DEFAULT_SRGB_GAMMA);
}