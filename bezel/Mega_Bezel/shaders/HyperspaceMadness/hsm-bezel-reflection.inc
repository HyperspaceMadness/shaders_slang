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
#include "hsm-common-functions-bezel.inc"

/////////////// Helper Functions ///////////////

layout(push_constant) uniform Push
{
	vec4 BR_MirrorBlurredPassSize;
	vec4 BR_MirrorReflectionDiffusedPassSize;
	vec4 BR_MirrorFullscreenGlowPassSize;
	
} params;


//TODO remove this and replace with simpler calls
float GetFade(float current_position, float corner_position, float fade_distance)
{
	return smoothstep(corner_position + fade_distance / 2, corner_position - fade_distance / 2, current_position);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma stage vertex

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 6) out vec2 VIEWPORT_COORD;

//////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	gl_Position = global.MVP * Position;
	vec2 vTexCoord = TexCoord;

	if (HSM_FLIP_VIEWPORT_VERTICAL > 0.5)
		vTexCoord.y =  1 - vTexCoord.y;

	VIEWPORT_COORD = vTexCoord * 1.0001;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma stage fragment

layout(location = 6) in vec2 VIEWPORT_COORD;

layout(location = 0) out vec4 FragColor;

// Pass Framebuffer Textures
layout(set = 0, binding = 1) uniform sampler2D InfoCachePass;
layout(set = 0, binding = 2) uniform sampler2D BR_CRTPass;
layout(set = 0, binding = 3) uniform sampler2D BR_MirrorBlurredPass;
layout(set = 0, binding = 4) uniform sampler2D BR_MirrorReflectionDiffusedPass;
layout(set = 0, binding = 5) uniform sampler2D BR_MirrorFullscreenGlowPass;

// Image Textures from Disk
layout(set = 0, binding = 6) uniform sampler2D TubeStaticReflectionImage;
layout(set = 0, binding = 7) uniform sampler2D ColoredGelImage;
layout(set = 0, binding = 8) uniform sampler2D BackgroundImage;
layout(set = 0, binding = 9)  uniform sampler2D BackgroundVertImage;
layout(set = 0, binding = 10) uniform sampler2D ReflectionMaskImage;
layout(set = 0, binding = 11) uniform sampler2D NightLightingImage;
layout(set = 0, binding = 12) uniform sampler2D LEDImage;
layout(set = 0, binding = 13)  uniform sampler2D FrameTextureImage;
layout(set = 0, binding = 14)  uniform sampler2D TopLayerImage;

//////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	HSM_UpdateGlobalScreenValuesFromCache(InfoCachePass, VIEWPORT_COORD);

	vec2 screen_curved_coord = HSM_GetCurvedCoord(SCREEN_COORD, 1, SCREEN_ASPECT);
	
	vec2 tube_curved_coord = HSM_GetTubeCurvedCoord(SCREEN_COORD, 1, SCREEN_SCALE, TUBE_SCALE, SCREEN_ASPECT, 1);
	vec2 tube_curved_coord_ctr = tube_curved_coord - 0.5;
	vec2 edge_mask_coord = tube_curved_coord_ctr * (1 - (HSM_BZL_INNER_EDGE_THICKNESS / vec2(SCREEN_ASPECT, 1))) + 0.5;
	float edge_mask =  HSM_GetCornerMask(edge_mask_coord, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, HSM_BZL_INNER_EDGE_SHARPNESS);

	float outside_tube_mask = 1 - HSM_GetCornerMask(tube_curved_coord, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0.99);
	TUBE_MASK = 1 - outside_tube_mask;

	float avg_lum_mult = smoothstep(0.01, 0.5, pow(AVERAGE_LUMA, 1.3));

	//----------------------------------------------------
	// CRT Pass
	//----------------------------------------------------
	// Get the CRT pass and make it in linear space & mask the area outside the screen
	vec4 crt_linear = HSM_Linearize(texture(BR_CRTPass, VIEWPORT_COORD.xy), HSM_DEFAULT_CRT_GAMMA);
	crt_linear = HSM_ApplyGamma(crt_linear, HSM_DEFAULT_CRT_GAMMA / HSM_DEFAULT_SRGB_GAMMA);

	vec4 blurred_reflection_color = HHLP_GetBilinearTextureSample(BR_MirrorBlurredPass, VIEWPORT_COORD.xy, params.BR_MirrorBlurredPassSize);

	// Shrink the mask by 0.001 to clip off outer edge
	float screen_edge_sharpness = 0.5;
	if (HSM_GLASS_BORDER_ON == 1)
		screen_edge_sharpness = HSM_SCREEN_EDGE_SHARPNESS;
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
	float outermap_scale = 2.3;

	// Get a range width from the outer tube edge to the outer edge of the outermap
	float outermap_range = 0.5 * outermap_scale * 0.7;
	vec2 outermap_screen_size_from_center = vec2(0.5, 0.5);
	vec2 outermap_warped_outside_screen_vector = (tube_curved_coord_ctr - clamp(tube_curved_coord_ctr, -0.490, 0.490)) * vec2(1 / SCREEN_ASPECT, 1);
	float output_aspect = global.OutputSize.x / global.OutputSize.y;
	float outside_ratio_warped = clamp(length(outermap_warped_outside_screen_vector) / outermap_range, 0, 1);
	vec2 outermap_screen_corner_ctr_coord = vec2(0.5, -0.5);

	// Get a coordinate offset so it is centered around the corner
	vec2 outermap_coord_warped_ctr_at_screen_corner = abs(tube_curved_coord_ctr) - vec2(0.5);

	vec2 bezel_outside_coord = vec2(0.5, 0.5);
	vec2 frame_outside_coord = vec2(0.5, 0.5);

	HSM_GetBezelCoords(SCREEN_COORD, SCREEN_SCALE, TUBE_SCALE, SCREEN_ASPECT, bezel_outside_coord, frame_outside_coord);

	FRAME_SCALE = HSM_GetFrameScale(SCREEN_SCALE, TUBE_SCALE, SCREEN_ASPECT);

	float OUTSIDE_BEZEL_MASK = 1 - HSM_GetCornerMask(bezel_outside_coord, SCREEN_ASPECT, HSM_FRM_INNER_CORNER_RADIUS_SCALE * HSM_BZL_OUTER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0.9);

	//----------------------------------------------------
	//  Calculate Corner Highlight Mask
	//----------------------------------------------------
	const float pi = 3.1415;

	// Get amount to shift the point at the outer corner to match the overall position offset
	vec2 pos_shift_offset = vec2(0, HSM_BZL_OUTER_POSITION_Y) * SCREEN_SCALE.y / outermap_scale;
	pos_shift_offset *= tube_curved_coord.y > 0.5 ? 1 : -1;

	// Get the direction vector from the inner corner of the bezel pointing at the outer corner 
	vec2 corner_crease_dir = (outermap_screen_corner_ctr_coord + pos_shift_offset) / vec2(HSM_BZL_HEIGHT + 1, HSM_BZL_WIDTH + 1) - (outermap_screen_corner_ctr_coord) ;
	corner_crease_dir *= vec2(SCREEN_ASPECT, 1);

	float aspect_corner_length_scale_offset = SCREEN_ASPECT > 1 ? 0.9 : 1.5;
	float corner_crease_length = length(corner_crease_dir * aspect_corner_length_scale_offset);

	// A hack to adjust the angle offset, because without it the corner angle isn't pointing exactly at the corner
	// This offset is the opposite direction for vertical and horizontal aspect ratio
	float corner_rotation_offset = (SCREEN_COORD.y < 0.5) ? -HSM_REFLECT_CORNER_ROTATION_OFFSET_TOP : -HSM_REFLECT_CORNER_ROTATION_OFFSET_BOTTOM;

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

	float corner_fade_width_inner = HSM_REFLECT_CORNER_INNER_SPREAD * (SCREEN_SCALE.x + SCREEN_SCALE.y) * HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS / 10 / 250 * 1.2;
	float corner_fade_width_outer = HSM_REFLECT_CORNER_OUTER_SPREAD * (SCREEN_SCALE.x + SCREEN_SCALE.y) * HSM_BZL_OUTER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS / 10 / 250 * 1.6;
	float corner_fade_width = (corner_fade_width_inner + fade_out_to_corner * (corner_fade_width_outer - corner_fade_width_inner));

	// Get a vector perpendicular to the crease that we can shift the crease to blend between bottom/top and sides
	vec2 corner_crease_perp_dir = normalize(vec2(corner_crease_dir.y, corner_crease_dir.x));
	vec2 corner_coord_shifted = outermap_coord_warped_ctr_at_screen_corner - corner_crease_perp_dir * corner_fade_width / 2;
	vec2 corner_crease_dir_shifted = corner_crease_dir - corner_crease_perp_dir * corner_fade_width / 2;

	// Get the distance to this shifted crease
	float distance_from_crease_shifted = HHLP_GetDistanceToLine(corner_coord_shifted.x, corner_coord_shifted.y, 1, corner_crease_dir_shifted.y / corner_crease_dir_shifted.x, 0 );

	float top_half_mask = smoothstep(0.55, 0.5, tube_curved_coord.y);

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
	float outside_tube_mask_wider = 1 - HSM_GetCornerMask(tube_curved_coord_ctr * 0.996 + 0.5, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0.9);
	float tube_shadow_mask = HSM_GetCornerMask(tube_curved_coord_ctr + 0.5, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0);
	float tube_edge_shadow_mult = HSM_BZL_INNER_EDGE_SHADOW * (tube_shadow_mask) + (1 - HSM_BZL_INNER_EDGE_SHADOW);

	crt_linear.rgb *= tube_edge_shadow_mult * (1 - outside_tube_mask_wider);
	crt_linear.a = (1 - outside_tube_mask_wider);


	// Get color for the frame area outside of the bezel
	vec2 frame_outside_coord_ctr = frame_outside_coord - 0.5;
	float SHADOW_OUTSIDE_FRAME_MASK = 1 - HSM_GetCornerMask(frame_outside_coord_ctr * 1.01 + 0.5, SCREEN_ASPECT, HSM_FRM_OUTER_CORNER_RADIUS, 1);
	OUTSIDE_FRAME_MASK = 1 - HSM_GetCornerMask(frame_outside_coord_ctr + 0.5, SCREEN_ASPECT, HSM_FRM_OUTER_CORNER_RADIUS, 1);
	OUTSIDE_FRAME_MASK_FOR_IMAGE = 1 - HSM_GetCornerMask(frame_outside_coord_ctr * 0.999 + 0.5, SCREEN_ASPECT, HSM_FRM_OUTER_CORNER_RADIUS, 1);
	// Get masks for shadows, from frame as well as sides and top and bottom of viewport
	INSIDE_BEZEL_MASK = 1 - OUTSIDE_BEZEL_MASK;
	BEZEL_MASK = INSIDE_BEZEL_MASK * outside_tube_mask;
	FRAME_MASK = OUTSIDE_BEZEL_MASK * (1 - OUTSIDE_FRAME_MASK);
	FRAME_MASK_FOR_IMAGE = OUTSIDE_BEZEL_MASK * (1 - OUTSIDE_FRAME_MASK_FOR_IMAGE);
	float FRAME_AND_BEZEL_MASK = outside_tube_mask * (1 - OUTSIDE_FRAME_MASK);

	// ----------------------------------------------------
	// Generated Bezel
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

	vec3 base_color = HSM_Linearize(vec4(HSM_HSVtoRGB(vec3(HSM_BZL_COLOR_HUE, HSM_BZL_COLOR_SATURATION, HSM_BZL_COLOR_VALUE)), 1), HSM_DEFAULT_SRGB_GAMMA).rgb;
	float noise_mask = clamp(fract(sin(dot(tube_curved_coord_ctr + vec2(0.5, 0.5) + 1, vec2(12.9898, 78.233))) * 43758.5453), 0, 1);
	vec3 base_color_with_noise = mix(base_color, 1.5 * base_color * noise_mask, HSM_BZL_NOISE);
	vec3 top_color = hmbz_bezel_brightness_top * HSM_BZL_BRIGHTNESS * base_color_with_noise;
	vec3 bottom_color = hmbz_bezel_brightness_bottom * HSM_BZL_BRIGHTNESS * base_color_with_noise;
	vec3 sides_color = hmbz_bezel_brightness_sides * HSM_BZL_BRIGHTNESS * base_color_with_noise;

	vec3 frame_color = hmbz_frame_brightness / 100 * mix(base_color, 1.5 * base_color * noise_mask, 0.6 * HSM_BZL_NOISE);;
	
	vec3 outside_frame_color = hmbz_brightness_shadow * base_color_with_noise;

	vec3 bezel_diffuse_color = mix(sides_color, top_color, top_mask);
	bezel_diffuse_color = mix(bezel_diffuse_color, bottom_color, bottom_mask);

	float top_center_highlight_mask 	= hmbz_bezel_highlight_top * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(tube_curved_coord_ctr.x)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));
	float bottom_center_highlight_mask 	= hmbz_bezel_highlight_bottom * bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(tube_curved_coord_ctr.x)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));
	float sides_highlight_mask 			= hmbz_bezel_highlight_sides * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_highlight_width, 0, abs(tube_curved_coord_ctr.y)), vec2(0.5, hmbz_bezel_highlight_falloff_speed));

	float edge_top_center_highlight_mask 		= hmbz_bezel_highlight_top * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(tube_curved_coord_ctr.x)), vec2(0.8, 0));
	float edge_bottom_center_highlight_mask 	= hmbz_bezel_highlight_bottom * bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(tube_curved_coord_ctr.x)), vec2(0.8, 0));
	float edge_sides_highlight_mask 			= hmbz_bezel_highlight_sides * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(tube_curved_coord_ctr.y)), vec2(0.8, 0));

	if (HSM_GLASS_BORDER_ON == 1)
	{
		edge_top_center_highlight_mask 		= 0.6 * top_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(tube_curved_coord_ctr.x)), vec2(0.8, 1));
		edge_bottom_center_highlight_mask 	= bottom_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(tube_curved_coord_ctr.x)), vec2(0.8, 1));
		edge_sides_highlight_mask 			= 0.7 * sides_mask * HHLP_QuadraticBezier(smoothstep(hmbz_bezel_edge_highlight_width, 0, abs(tube_curved_coord_ctr.y)), vec2(0.8, 1));
	}

	float edge_highlight_mask 	= hmbz_bezel_highlight_edge * edge_mask * (edge_top_center_highlight_mask + edge_bottom_center_highlight_mask + edge_sides_highlight_mask);

	// Combine all the individual highlights into one mask
	float combined_highlight_mask = (1 + 2.5 * HSM_BZL_NOISE) * (1 - noise_mask * 2.5 * HSM_BZL_NOISE) * (top_center_highlight_mask + bottom_center_highlight_mask + sides_highlight_mask);
	vec3 bezel_color = bezel_diffuse_color + HSM_BZL_HIGHLIGHT * combined_highlight_mask;
	bezel_color += HSM_BZL_HIGHLIGHT * edge_highlight_mask;


	// Add the inner edge highlight on top of the bezel color which has it's own highlight
	vec3 frame_inner_edge_color = bezel_color + hmbz_bezel_brightness_frame_inner_edge + HSM_BZL_HIGHLIGHT * 10 * hmbz_bezel_brightness_frame_inner_edge;
	bezel_color = mix(bezel_color, frame_inner_edge_color, frame_inner_edge_mask);

	float dist_inside_outer_edge = min(0.5 - abs(frame_outside_coord_ctr.x), 0.5 - abs(frame_outside_coord_ctr.y));
	float frame_outer_edge_width = HSM_FRM_OUTER_EDGE_THICKNESS;
	vec3 frame_diffuse_color = mix(frame_color, (1 - HSM_FRM_OUTER_EDGE_SHADING) * frame_color, smoothstep(frame_outer_edge_width, 0, dist_inside_outer_edge));
	
	if (HSM_FRM_TEXTURE_OPACITY > 0)
	{
		vec4 frame_texture_color = HSM_Linearize(texture(FrameTextureImage, frame_outside_coord), HSM_DEFAULT_SRGB_GAMMA);
		frame_diffuse_color = HSM_BlendModeLayerMix(vec4(frame_diffuse_color, 1), frame_texture_color, HSM_FRM_TEXTURE_BLEND_MODE, HSM_FRM_TEXTURE_OPACITY).rgb;
	}

	frame_diffuse_color = mix(frame_diffuse_color, outside_frame_color, OUTSIDE_FRAME_MASK);

	// Composite in color from outside the bezel
	vec3 bezel_and_frame_rgb = mix(bezel_color, frame_diffuse_color, OUTSIDE_BEZEL_MASK);

	float frame_edge = 0.495;

	// Get masks on side of frame to multiply together to get a shadow around the frame
	// Get vector from the screen edge outward
	float dist_outside_frame = length(clamp(abs(frame_outside_coord_ctr) - frame_edge, 0, 1) * vec2(SCREEN_ASPECT, 1));

	vec4 frame_shadow_layer = vec4(0);
	frame_shadow_layer.a = SHADOW_OUTSIDE_FRAME_MASK * HHLP_QuadraticBezier(smoothstep(HSM_FRM_SHADOW_WIDTH, 0, dist_outside_frame), vec2(1, 0));
	
	//----------------------------------------------------
	// Reflection
	//----------------------------------------------------
	vec4 reflected_color = vec4(0);
	vec4 edge_reflected_color = vec4(0);
	vec4 glass_border_edge_color = vec4(0);
	vec4 edge_fullscreen_glow = vec4(0);
	if (HSM_REFLECT_GLOBAL_AMOUNT > 0)
	{
		// Corner Mask for Specular highlights
		float fade_out_to_corner = smoothstep(0 + HSM_REFLECT_CORNER_FADE_DISTANCE / 2, 0 - HSM_REFLECT_CORNER_FADE_DISTANCE / 2, outside_ratio_warped);
		float corner_fade_mask = (top_corner_mask + bottom_corner_mask) * (HSM_REFLECT_CORNER_FADE) * fade_out_to_corner * 2;

		corner_fade_mask *= 1 - frame_inner_edge_mask;

		// Radial fade - fading away from the edges of the screen
		float radial_fade_speed = 100;
		float radial_fade_sides = 1 - HHLP_QuadraticBezier(clamp((outside_ratio_warped / (HSM_REFLECT_RADIAL_FADE_WIDTH)), 0, 1), vec2(1 - (radial_fade_speed / 100), 1));
		float radial_fade_top_bottom = 1 - HHLP_QuadraticBezier(clamp((outside_ratio_warped / (HSM_REFLECT_RADIAL_FADE_HEIGHT)), 0, 1), vec2(1 - (radial_fade_speed / 100), 1));
		float radial_fade_mask = clamp((1 - sides_mask) * radial_fade_top_bottom
									+ sides_mask * radial_fade_sides, 0, 1);

		float radial_inner_fade_mask = clamp(0.3 + 0.7 * HHLP_QuadraticBezier(smoothstep(0.01, 0.3, outside_ratio_warped / (HSM_REFLECT_RADIAL_FADE_WIDTH)), vec2(0.1, 0.3)), 0, 1);

		// Lateral fade - Fading left to right across the bottom or top to bottom along the sides 
		float distance_ratio = smoothstep(0, 0.075, outside_ratio_warped);
		float lateral_outer_fade_distance = HSM_REFLECT_LATERAL_OUTER_FADE_DISTANCE;
		lateral_outer_fade_distance = 0.5 * lateral_outer_fade_distance + distance_ratio * 0.5 * lateral_outer_fade_distance;
		float lateral_fade_mask = (1 - sides_mask) * GetFade(abs(tube_curved_coord_ctr.x) + (HSM_REFLECT_LATERAL_OUTER_FADE_POSITION) / SCREEN_ASPECT, 
																	outermap_screen_size_from_center.x,
																	outermap_screen_size_from_center.x * lateral_outer_fade_distance)
										+  sides_mask * GetFade(abs(tube_curved_coord_ctr.y) + (HSM_REFLECT_LATERAL_OUTER_FADE_POSITION) / SCREEN_ASPECT, 
																outermap_screen_size_from_center.y, 
																outermap_screen_size_from_center.y * lateral_outer_fade_distance); 

		vec2 screen_coord_ctr = SCREEN_COORD - 0.5;

		float combined_fade_mask = radial_fade_mask * lateral_fade_mask;

		// Put all the fades together into one mask
		float final_fade_mask = clamp(HSM_REFLECT_FADE_AMOUNT * combined_fade_mask, 0, 1) + 1 - HSM_REFLECT_FADE_AMOUNT;

		float stoichaic_blur_samples = HSM_REFLECT_NOISE_SAMPLES;
		float noise_falloff = 0.3;
		float stoichaic_blur_max = HHLP_QuadraticBezier(outside_ratio_warped, vec2(0, noise_falloff)) * 3;
		float stoichaic_blur_amount = HSM_REFLECT_NOISE_SAMPLE_DISTANCE;

		// vec4 fullscreen_blurred_sampled_color = HSM_GetStoichaicBlurredSample(BR_MirrorFullscreenGlowPass, VIEWPORT_COORD.xy, stoichaic_blur_samples, (1 - corner_mask) * stoichaic_blur_max * 3, stoichaic_blur_amount);
		vec4 fullscreen_blurred_sampled_color = HHLP_GetBilinearTextureSample(BR_MirrorFullscreenGlowPass, VIEWPORT_COORD.xy, params.BR_MirrorFullscreenGlowPassSize);

		vec4 corner_reflection_color = fullscreen_blurred_sampled_color;
		
		vec4 fullscreen_glow_color = pow(fullscreen_blurred_sampled_color, vec4(HSM_REFLECT_FULLSCREEN_GLOW_GAMMA));
		
		vec4 diffused_reflection_color = HHLP_GetBilinearTextureSample(BR_MirrorReflectionDiffusedPass, VIEWPORT_COORD.xy, params.BR_MirrorReflectionDiffusedPassSize);
		vec4 diffused_reflection_scatter_color = HSM_GetStoichaicBlurredSample(BR_MirrorReflectionDiffusedPass, VIEWPORT_COORD.xy, stoichaic_blur_samples, stoichaic_blur_max, stoichaic_blur_amount);
		vec4 diffused_reflection_blended_color = mix(diffused_reflection_color, diffused_reflection_scatter_color, HSM_REFLECT_NOISE_AMOUNT);

		vec4 blurred_reflection_scatter_color = HSM_GetStoichaicBlurredSample(BR_MirrorBlurredPass, VIEWPORT_COORD.xy, stoichaic_blur_samples, stoichaic_blur_max, stoichaic_blur_amount);
		vec4 blurred_reflection_blended_color = mix(blurred_reflection_color, blurred_reflection_scatter_color, HSM_REFLECT_NOISE_AMOUNT);

		// Add Fullscreen Glow
		float lateral_fade_outer_mask_for_glow = (lateral_fade_mask - 1) * 0.8 + 1;

		//Combine diffused and undiffused reflection
		
		vec4 bezel_reflected_color = (HSM_REFLECT_DIRECT_AMOUNT * blurred_reflection_blended_color + HSM_REFLECT_DIFFUSED_AMOUNT * diffused_reflection_blended_color) * final_fade_mask;

		// Add Reflection from corners which is sampled from the fullscreen glow
		bezel_reflected_color += HSM_REFLECT_CORNER_FADE * 100 * corner_reflection_color * corner_fade_mask;

		// Add Fullscreen Glow
		bezel_reflected_color += HSM_REFLECT_FULLSCREEN_GLOW * 1.5 * fullscreen_glow_color * radial_inner_fade_mask * lateral_fade_outer_mask_for_glow;

		// Add Bezel and Edge reflection together
		edge_reflected_color = 1.25 * HSM_REFLECT_BEZEL_INNER_EDGE_AMOUNT * (blurred_reflection_color + 0.50 * diffused_reflection_color);
		float reflection_area_mask = outside_tube_mask;

		float vignette_shadow_mask = 0.75 * HHLP_QuadraticBezier(1 - HSM_GetVignetteFactor(VIEWPORT_COORD, HSM_REFLECT_VIGNETTE_AMOUNT), vec2(1, 0.5));
		vignette_shadow_mask += 0.5 * HSM_REFLECT_VIGNETTE_AMOUNT * HHLP_QuadraticBezier(smoothstep(outside_ratio_warped, 0, 0.1), vec2(1, 0.5));

		// Edge Reflection
		if (HSM_GLASS_BORDER_ON == 1)
		{
			reflected_color += (1 - vignette_shadow_mask) * bezel_reflected_color;
			reflection_area_mask *= outside_tube_mask_wider;
		}
		else
		{
			reflected_color += (1 - edge_mask) * bezel_reflected_color;
			reflected_color += edge_mask * (edge_reflected_color + HHLP_EasePowerIn(corner_mask, 1) * corner_reflection_color);
		}

		reflected_color = HSM_REFLECT_GLOBAL_AMOUNT * pow(reflected_color, vec4(HSM_REFLECT_GLOBAL_GAMMA_ADJUST));

		// Mask reflection to only appear inside the bezel
		reflected_color = clamp(reflected_color, 0, 1) * clamp(reflection_area_mask, 0, 1);

		if (HSM_GLASS_BORDER_ON == 1)
		{
			glass_border_edge_color = HSM_REFLECT_GLOBAL_AMOUNT * pow(edge_reflected_color, vec4(HSM_REFLECT_GLOBAL_GAMMA_ADJUST));
			reflected_color = mix(reflected_color, glass_border_edge_color, edge_mask * outside_tube_mask);
		}
		// Edge Full Screen Glow
		// Add Small amount of static glow on the edge (So when the screen is dark there is some highlight) as well as dynamic light
		edge_fullscreen_glow = HSM_REFLECT_BEZEL_INNER_EDGE_FULLSCREEN_GLOW * edge_highlight_mask * outside_tube_mask * (vec4(0.005) 
									+ (avg_lum_mult  + 0.5) * (2 * fullscreen_glow_color + vec4(0.01)));
		
		// Add Diffused reflection on top of the glass inner edge
		if (HSM_GLASS_BORDER_ON == 1)
			edge_fullscreen_glow += HSM_REFLECT_BEZEL_INNER_EDGE_FULLSCREEN_GLOW * 0.5 * edge_highlight_mask * outside_tube_mask * diffused_reflection_color;

		reflected_color += clamp(edge_fullscreen_glow, 0, 1);
		reflected_color.a = 1;

		// Modulate amount of refleciton on frame inner edge
		reflected_color.rgb *= (1 - HSM_REFLECT_FRAME_INNER_EDGE_AMOUNT) * (1 - frame_inner_edge_mask) + HSM_REFLECT_FRAME_INNER_EDGE_AMOUNT;
	}

#ifdef IS_STANDARD_PRESET
	float bezel_mask = HSM_GetCornerMask(bezel_outside_coord, SCREEN_ASPECT, HSM_FRM_INNER_CORNER_RADIUS_SCALE * HSM_BZL_OUTER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0.9);
	reflected_color *= bezel_mask;
#endif

	// Apply the mask image on the reflection, usually used to show the uneven brightness of a bumpy surface
	if (HSM_REFLECT_MASK_IMG_AMOUNT > 0)
		reflected_color *= HSM_REFLECT_MASK_IMG_AMOUNT * texture(ReflectionMaskImage, VIEWPORT_COORD).r + (1 - HSM_REFLECT_MASK_IMG_AMOUNT);

	crt_linear *= SCREEN_MASK * TUBE_MASK;

    vec4 frag_color_linear = crt_linear;
    
	float black_edge_mask = TUBE_MASK * (1 - SCREEN_MASK);

	// Add a Colored Gel image on top of the screen, this is what colors games like space invaders or battlezone
	if (HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT > 0)
	{
		vec4 gel_image = texture(ColoredGelImage, tube_curved_coord);
		gel_image = HSM_Linearize(gel_image, HSM_DEFAULT_SRGB_GAMMA);

		if (HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT > 0)
			frag_color_linear += black_edge_mask * gel_image * gel_image.a * HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT;
	}

	// TUBE HIGHLIGHT
    if (HSM_TUBE_STATIC_REFLECTION_IMAGE_OPACITY > 0)
    {
		vec2 tube_highlight_coord = (tube_curved_coord - 0.5) / HSM_TUBE_STATIC_REFLECTION_IMAGE_SCALE + 0.5;
        // vec4 tube_highlight_image = texture(TubeStaticReflectionImage, tube_highlight_coord);

		// // Dithering for the glass reflection if needed to reduce banding
		// float blur_max_size = 1;
		// float blur_amount = 0.2;
		// vec4 tube_highlight_image = HSM_GetStoichaicBlurredSample(TubeStaticReflectionImage, tube_highlight_coord, HSM_TUBE_STATIC_REFLECTION_IMAGE_DITHERING_SAMPLES, blur_max_size, blur_amount);
		
		vec4 tube_highlight_image = texture(TubeStaticReflectionImage, tube_highlight_coord);
		tube_highlight_image = HSM_Linearize(tube_highlight_image, HSM_DEFAULT_SRGB_GAMMA);

        // Since the tube highlight has already been applied in the crt pass and we've already masked it to the screen
		// We just need to add the tube highlight on the black screen area
		frag_color_linear += black_edge_mask * HSM_TUBE_STATIC_REFLECTION_IMAGE_OPACITY * tube_highlight_image * tube_highlight_image.a;
	}

	// Clamp otherwise we get artifacts (blue overlays of brighter parts of image)
	frag_color_linear = clamp(frag_color_linear, 0, 1);

	vec4 night_lighting_image = texture(NightLightingImage, VIEWPORT_COORD);

	vec2 image_coord = VIEWPORT_COORD;
	float final_viewport_aspect = global.FinalViewportSize.x/global.FinalViewportSize.y;

FragColor = frag_color_linear + reflected_color;

#ifdef IS_STANDARD_PRESET
	// Image Ratio is 16:9
	if (HSM_STANDARD_IMG_ASPECT_RATIO == 1)
		image_coord.x = (VIEWPORT_COORD.x - 0.5) / (1.7777/final_viewport_aspect) + 0.5;

	// Image Ratio is 9:16
	if (HSM_STANDARD_IMG_ASPECT_RATIO == 2)
		image_coord.x = (VIEWPORT_COORD.x - 0.5) / (0.5625/final_viewport_aspect) + 0.5;

	vec4 bg_layer = vec4(0);
	if (SCREEN_ASPECT > 1) 
		bg_layer = texture(BackgroundImage, image_coord);
	else
		bg_layer = texture(BackgroundVertImage, image_coord);

	bg_layer = HSM_Linearize(bg_layer, HSM_DEFAULT_SRGB_GAMMA);

	vec4 led_layer = texture(LEDImage, image_coord);
	led_layer = HSM_Linearize(led_layer, HSM_DEFAULT_SRGB_GAMMA);

	vec4 top_layer = texture(TopLayerImage, image_coord);
	top_layer = HSM_Linearize(top_layer, HSM_DEFAULT_SRGB_GAMMA);

	if (HSM_STATIC_LAYERS_GAMMA != 1)
	{
		bg_layer = HSM_ApplyGamma(bg_layer, HSM_STATIC_LAYERS_GAMMA);
		led_layer = HSM_ApplyGamma(led_layer, HSM_STATIC_LAYERS_GAMMA);
		top_layer = HSM_ApplyGamma(top_layer, HSM_STATIC_LAYERS_GAMMA);
	}

	if (HSM_STANDARD_BG_SHOW_OVER_SCREEN == 0)
	{
		if (HSM_GLASS_BORDER_ON == 1)
			bg_layer.a *= outside_tube_mask_wider * (1 - edge_mask);
		else
			bg_layer *= outside_tube_mask;
	}

	if (HSM_NIGHT_OPACITY > 0)
	{
		bg_layer = mix(bg_layer, bg_layer * night_lighting_image, HSM_NIGHT_OPACITY);
		top_layer = mix(top_layer, top_layer * night_lighting_image, HSM_NIGHT_OPACITY);
	}

	if (HSM_STANDARD_BG_SHOW_OVER_SCREEN == 0)
		bg_layer *= outside_tube_mask_wider;

	vec4 bezel_layer = vec4(0);
	vec4 frame_layer = vec4(0);
	if (HSM_BZL_OPACITY > 0 || HSM_FRM_OPACITY > 0)
	{
		vec4 bezel_and_frame_rgba = vec4(bezel_and_frame_rgb, 1);
		
		if (HSM_STATIC_LAYERS_GAMMA != 1)
			bezel_and_frame_rgba = HSM_ApplyGamma(bezel_and_frame_rgba, HSM_STATIC_LAYERS_GAMMA);

		// NIGHT LIGHTING
		if (HSM_NIGHT_OPACITY > 0)
			bezel_and_frame_rgba = HSM_BlendMultiply(bezel_and_frame_rgba, night_lighting_image, HSM_NIGHT_OPACITY);

		// Mask out the area outside the frame
		bezel_layer = bezel_and_frame_rgba * (1 - OUTSIDE_FRAME_MASK);
		// Layer this on top of the shadow
		bezel_layer = HSM_BlendModeLayerMix(frame_shadow_layer * HSM_FRM_SHADOW_OPACITY, bezel_layer, BLEND_MODE_NORMAL, 1);
		// Adjust the masks for the transparency of each portion, Bezel and from the frame outwards
		bezel_layer = clamp(bezel_layer * (BEZEL_MASK * HSM_BZL_OPACITY + OUTSIDE_BEZEL_MASK * HSM_FRM_OPACITY), 0, 1);
	}

	// vec4 vignette_layer = vec4(0);
	// if (HSM_VIEWPORT_VIGNETTE_OPACITY > 0)
	// {
	// 	vignette_layer.a += 0.75 * HHLP_QuadraticBezier(1 - HSM_GetVignetteFactor(VIEWPORT_COORD, HSM_VIEWPORT_VIGNETTE_OPACITY), vec2(1, 0.5)) * OUTSIDE_BEZEL_MASK;
	// }

	frag_color_linear = HSM_BlendModeLayerMix(frag_color_linear, bg_layer, HSM_BG_BLEND_MODE, HSM_BG_OPACITY);
	// frag_color_linear = HSM_BlendModeLayerMix(frag_color_linear, vignette_layer, BLEND_MODE_NORMAL, 1);
	frag_color_linear = HSM_BlendModeLayerMix(frag_color_linear, led_layer, HSM_LED_BLEND_MODE, HSM_LED_OPACITY);
	frag_color_linear = HSM_BlendModeLayerMix(frag_color_linear, bezel_layer, BLEND_MODE_NORMAL, 1);
	frag_color_linear += reflected_color;
	frag_color_linear = HSM_BlendModeLayerMix(frag_color_linear, top_layer, HSM_TOP_BLEND_MODE, HSM_TOP_OPACITY);

	FragColor = HSM_ApplyGamma(clamp(frag_color_linear, 0, 1), HSM_DEFAULT_SRGB_GAMMA);
#endif

#ifdef IS_GLASS_PRESET
	vec4 bg_layer = texture(BackgroundImage, image_coord);
	bg_layer = HSM_Linearize(bg_layer, HSM_DEFAULT_SRGB_GAMMA);

	// if (HSM_GLASS_BORDER_ON == 1)
		bg_layer.a *= outside_tube_mask_wider * (1 - edge_mask);
	// else
	// 	bg_layer *= outside_tube_mask;

	frag_color_linear = HSM_BlendModeLayerMix(frag_color_linear, bg_layer, HSM_BG_BLEND_MODE, HSM_BG_OPACITY);
	frag_color_linear += reflected_color;
	FragColor = HSM_ApplyGamma(clamp(frag_color_linear, 0, 1), HSM_DEFAULT_SRGB_GAMMA);
#endif

	// Markup to Draw Found Top and Bottom of tube area in the image
	// // Need to add this above layout(set = 0, binding = 14) uniform sampler2D ScreenPlacementImage;
	// float num_samples = 60;
	// float screen_top_y_pos = 1;
	// float screen_bottom_y_pos = 0;

	// for (int i=0; i < num_samples; i++)
	// {
	// 	float y_pos = i * 1 / num_samples;
	// 	float image_alpha = texture(ScreenPlacementImage, vec2(0.5, y_pos)).a;
	// 	if (image_alpha < 0.5)
	// 	{
	// 		screen_top_y_pos = min(screen_top_y_pos, y_pos);
	// 		screen_bottom_y_pos = max(screen_bottom_y_pos, y_pos);
	// 	}
		
	// }

	// if (VIEWPORT_COORD.y < screen_top_y_pos + 0.001 && VIEWPORT_COORD.y > screen_top_y_pos - 0.001)
	// 	FragColor = vec4(1, 0, 0, 1);

	// if (VIEWPORT_COORD.y < screen_bottom_y_pos + 0.001 && VIEWPORT_COORD.y > screen_bottom_y_pos - 0.001)
	// 	FragColor = vec4(0, 1, 0, 1);

}