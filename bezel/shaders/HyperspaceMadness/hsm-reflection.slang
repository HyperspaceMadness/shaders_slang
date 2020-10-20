#version 450

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

/////////////// Helper Functions ///////////////

float TUBE_MASK = 0;

float SCREEN_ASPECT = HSS_GetScreenAspect();
vec2 SCREEN_SCALE = HSS_GetScreenScale(SCREEN_ASPECT);

//TODO remove this and replace with simpler calls
float GetFade(float current_position, float corner_position, float fade_distance)
{
	return smoothstep(corner_position + fade_distance / 2, corner_position - fade_distance / 2, current_position);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma stage vertex

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 3) out vec2 SCREEN_COORD;
layout(location = 6) out vec2 VIEWPORT_COORD;

//////////////////////////////////////////////////////////////////////////////////////////////////
void main()
{
	gl_Position = global.MVP * Position;
	vec2 vTexCoord = TexCoord;

	if (HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL > 0.5)
		vTexCoord.y =  1 - vTexCoord.y;

	SCREEN_COORD = HSS_GetScreenVTexCoord(vTexCoord, SCREEN_SCALE);

	VIEWPORT_COORD = vTexCoord * 1.0001;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma stage fragment

layout(location = 3) in vec2 SCREEN_COORD;
layout(location = 6) in vec2 VIEWPORT_COORD;

layout(location = 0) out vec4 FragColor;

// Pass Framebuffer Textures
layout(set = 0, binding = 1) uniform sampler2D BR_MappingPass;

layout(set = 0, binding = 2) uniform sampler2D BR_CRTPass;

layout(set = 0, binding = 5) uniform sampler2D TubeHighlightImage;
layout(set = 0, binding = 6) uniform sampler2D ColoredGelImage;

layout(set = 0, binding = 7) uniform sampler2D BR_MirrorBlurredPass;
layout(set = 0, binding = 8) uniform sampler2D BR_MirrorReflectionDiffusedPass;
layout(set = 0, binding = 9) uniform sampler2D BR_MirrorFullscreenGlowPass;
layout(set = 0, binding = 10) uniform sampler2D AvgLumPass;

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

	// Shrink the mask by 0.001 to clip off outer edge
	float screen_mask = HSS_GetCornerMask(((screen_curved_coord - 0.5) * 1.001) + 0.5, SCREEN_ASPECT, HSS_SCREEN_CORNER_RADIUS, HSS_SCREEN_EDGE_SHARPNESS);

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
	float outside_ratio_warped = clamp(length(outermap_warped_outside_screen_vector) / outermap_range, 0, 1);
	vec2 outermap_screen_corner_ctr_coord = vec2(0.5, -0.5);

	// Get a coordinate offset so it is centered around the corner
	vec2 outermap_coord_warped_ctr_at_screen_corner = abs(outermap_warped_coord_ctr) - vec2(0.5);

	//----------------------------------------------------
	//  Calculate Corner Highlight Mask
	//----------------------------------------------------
	const float pi = 3.1415;

	// Get amount to shift the point at the outer corner to match the overall position offset
	vec2 pos_shift_offset = vec2(0, HBZ_BEZEL_OUTER_POS_Y_OFFSET / 100) * SCREEN_SCALE.y / outermap_scale;
	pos_shift_offset *= outermap_coord.y > 0.5 ? 1 : -1;

	// Get the direction vector from the inner corner of the bezel pointing at the outer corner 
	vec2 corner_crease_dir = (outermap_screen_corner_ctr_coord + pos_shift_offset) / vec2(HBZ_BEZEL_HEIGHT / 100 + 1, HBZ_BEZEL_WIDTH + 1) - (outermap_screen_corner_ctr_coord) ;
	corner_crease_dir *= vec2(SCREEN_ASPECT, 1);

	float aspect_corner_length_scale_offset = SCREEN_ASPECT > 1 ? 0.9 : 1.5;
	float corner_crease_length = length(corner_crease_dir * aspect_corner_length_scale_offset);

	// A hack to adjust the angle offset, because without it the corner angle isn't pointing exactly at the corner
	// This offset is the opposite direction for vertical and horizontal aspect ratio
	float corner_rotation_offset = (SCREEN_COORD.y < 0.5) ? -HBR_CORNER_ROTATION_OFFSET_TOP : -HBR_CORNER_ROTATION_OFFSET_BOTTOM;

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

	float corner_fade_width_inner = HBR_CORNER_INNER_SPREAD / 100 * (SCREEN_SCALE.x + SCREEN_SCALE.y) * HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREEN_CORNER_RADIUS / 10 / 250 * 1.2;
	float corner_fade_width_outer = HBR_CORNER_OUTER_SPREAD / 100 * (SCREEN_SCALE.x + SCREEN_SCALE.y) * HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE * HSS_SCREEN_CORNER_RADIUS / 10 / 250 * 1.6;
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

	float outside_tube_mask_wider = 1 - HSS_GetCornerMask(tube_warped_coord_ctr * 0.996 + 0.5, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREEN_CORNER_RADIUS, 0.9);
	float tube_shadow_mask = HSS_GetCornerMask(tube_warped_coord_ctr + 0.5, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREEN_CORNER_RADIUS, 0);
	float tube_edge_shadow_mult = HBZ_BEZEL_INNER_EDGE_SHADOW * (tube_shadow_mask) + (1 - HBZ_BEZEL_INNER_EDGE_SHADOW);

	crt_image_linear.rgb *= tube_edge_shadow_mult * (1 - outside_tube_mask_wider);
	crt_image_linear.a = (1 - outside_tube_mask_wider);

	float edge_highlight_mask  = 0;

	float hmbz_bezel_highlight_edge = 0.9;
	float hmbz_bezel_highlight_top = 0.2;
	float hmbz_bezel_highlight_bottom = 0.3;
	float hmbz_bezel_highlight_sides = 0.2;

	float hmbz_bezel_highlight_falloff_speed = 0.5;
	float hmbz_bezel_highlight_width = 0.25;

	float hmbz_bezel_edge_highlight_width = 0.8;
	if (HGL_GLASSBORDER_ON == 1)
		hmbz_bezel_edge_highlight_width = 0.55;

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

	//----------------------------------------------------
	// Reflection
	//----------------------------------------------------
	vec4 reflected_color = vec4(0);
	vec4 edge_reflected_color = vec4(0);
	vec4 glass_border_edge_color = vec4(0);
	vec4 edge_fullscreen_glow = vec4(0);
	if (HBR_GLOBAL_AMOUNT > 0)
	{
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


		// Put all the fades together into one mask
		float final_fade_mask = clamp(HBR_FADE_AMOUNT * combined_fade_mask, 0, 1) + 1 - HBR_FADE_AMOUNT;

		float stoichaic_blur_samples = HBR_NOISE_SAMPLES;
		float noise_falloff = 0.3;
		float stoichaic_blur_max = HHLP_QuadraticBezier(outside_ratio_warped, vec2(0, noise_falloff)) * 3;
		float stoichaic_blur_amount = HBR_NOISE_SAMPLE_DISTANCE;

		vec4 fullscreen_blurred_sampled_color = HSS_GetStoichaicBlurredSample(BR_MirrorFullscreenGlowPass, VIEWPORT_COORD.xy, stoichaic_blur_samples, (1 - corner_mask) * stoichaic_blur_max * 3, stoichaic_blur_amount);

		vec4 corner_reflection_color = fullscreen_blurred_sampled_color;
		
		vec4 fullscreen_glow_color = pow(fullscreen_blurred_sampled_color, vec4(HBR_FULLSCREEN_GLOW_GAMMA));
		
		vec4 diffused_reflection_color = texture(BR_MirrorReflectionDiffusedPass, VIEWPORT_COORD.xy);
		vec4 diffused_reflection_scatter_color = HSS_GetStoichaicBlurredSample(BR_MirrorReflectionDiffusedPass, VIEWPORT_COORD.xy, stoichaic_blur_samples, stoichaic_blur_max, stoichaic_blur_amount);
		vec4 diffused_reflection_blended_color = mix(diffused_reflection_color, diffused_reflection_scatter_color, HBR_NOISE_AMOUNT);

		vec4 blurred_reflection_scatter_color = HSS_GetStoichaicBlurredSample(BR_MirrorBlurredPass, VIEWPORT_COORD.xy, stoichaic_blur_samples, stoichaic_blur_max, stoichaic_blur_amount);
		vec4 blurred_reflection_blended_color = mix(blurred_reflection_color, blurred_reflection_scatter_color, HBR_NOISE_AMOUNT);

		// Add Fullscreen Glow
		float lateral_fade_outer_mask_for_glow = (lateral_fade_mask - 1) * 0.8 + 1;

		//Combine diffused and undiffused reflection
		
		vec4 bezel_reflected_color = (HBR_DIRECT_REFLECTION * blurred_reflection_blended_color + HBR_DIFFUSED_REFLECTION * diffused_reflection_blended_color) * final_fade_mask;

		// Add Reflection from corners which is sampled from the fullscreen glow
		bezel_reflected_color += HBR_CORNER_FADE * corner_reflection_color * corner_fade_mask;

		// Add Fullscreen Glow
		bezel_reflected_color += HBR_FULLSCREEN_GLOW / 100 * 1.5 * fullscreen_glow_color * radial_inner_fade_mask * lateral_fade_outer_mask_for_glow;

		// Add Bezel and Edge reflection together
		edge_reflected_color = 1.25 * HBR_INNER_EDGE_REFLECTION * (blurred_reflection_color + 0.50 * diffused_reflection_color);
		float reflection_area_mask = outside_tube_mask;


		float vignette_shadow_mask = 0;
		vignette_shadow_mask += 0.75 * HHLP_QuadraticBezier(1 - HSS_GetVignetteFactor(VIEWPORT_COORD, HLY_BG_IMAGE_VIGNETTE_OPACITY), vec2(1, 0.5));
		vignette_shadow_mask += 0.5 * HLY_BG_IMAGE_VIGNETTE_OPACITY * HHLP_QuadraticBezier(smoothstep(outside_ratio_warped, 0, 0.1), vec2(1, 0.5));

		// Edge Reflection
		if (HGL_GLASSBORDER_ON == 1)
		{
			reflected_color += (1 - vignette_shadow_mask) * bezel_reflected_color;
			reflection_area_mask *= outside_tube_mask_wider;
			reflected_color += edge_mask * edge_reflected_color;
		}
		else
		{
			reflected_color += (1 - edge_mask) * bezel_reflected_color;
			reflected_color += edge_mask * (edge_reflected_color + HHLP_EasePowerIn(corner_mask, 1) * corner_reflection_color);
		}

		reflected_color = HBR_GLOBAL_AMOUNT * pow(reflected_color, vec4(HBR_GLOBAL_GAMMA_ADJUST));
		
		// Mask reflection to only appear inside the bezel
		reflected_color = clamp(reflected_color, 0, 1) * clamp(reflection_area_mask, 0, 1);

		if (HGL_GLASSBORDER_ON == 1)
		{
			glass_border_edge_color = HBR_GLOBAL_AMOUNT * pow(edge_reflected_color, vec4(HBR_GLOBAL_GAMMA_ADJUST));
			reflected_color = mix(reflected_color, glass_border_edge_color, edge_mask * outside_tube_mask);
		}
		// Edge Full Screen Glow
		// Add Small amount of static glow on the edge (So when the screen is dark there is some highlight) as well as dynamic light
		edge_fullscreen_glow = HBR_INNER_EDGE_FULLSCREEN_GLOW * edge_highlight_mask * outside_tube_mask * (vec4(0.005) 
									+ (avg_lum_mult  + 0.5) * (2 * fullscreen_glow_color + vec4(0.01)));
		
		// Add Diffused reflection on top of the glass inner edge
		if (HGL_GLASSBORDER_ON == 1)
			edge_fullscreen_glow += HBR_INNER_EDGE_FULLSCREEN_GLOW * 0.5 * edge_highlight_mask * outside_tube_mask * diffused_reflection_color;

		reflected_color += clamp(edge_fullscreen_glow, 0, 1);
		reflected_color.a = 1;

		// vec4 frag_color_linear = vec4(0);
		// if (VIEWPORT_COORD.x < 0.5 && VIEWPORT_COORD.y < 0.5)
		// frag_color_linear = edge_highlight_mask * vec4(1);
		// if (VIEWPORT_COORD.x > 0.5 && VIEWPORT_COORD.y < 0.5)
		// frag_color_linear = edge_fullscreen_glow;
		// // if (VIEWPORT_COORD.x < 0.5 && VIEWPORT_COORD.y > 0.5)
		// // frag_color_linear = glass_border_edge_color * edge_mask * outside_tube_mask + edge_fullscreen_glow;
		// // if (VIEWPORT_COORD.x > 0.5 && VIEWPORT_COORD.y > 0.5)
		// // frag_color_linear = glass_border_edge_color * edge_mask * outside_tube_mask;

		// FragColor = HSS_ApplyGamma(clamp(frag_color_linear, 0, 1), HSS_DEFAULT_SRGB_GAMMA);
		// return;
	}

    // CRT
	// if (HBR_REFLECTION_IS_LAST_PASS == 1)
	crt_image_linear *= screen_mask;

    vec4 frag_color_linear = crt_image_linear;
    
	float black_edge_mask = TUBE_MASK * (1 - screen_mask);

	// Add a Colored Gel image on top of the screen, this is what colors games like space invaders or battlezone
	if (HSS_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT > 0)
	{
		vec4 gel_image = texture(ColoredGelImage, tube_coord_warped);
		gel_image = HSS_Linearize(gel_image, HSS_DEFAULT_SRGB_GAMMA);

		if (HSS_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT > 0)
			frag_color_linear += black_edge_mask * gel_image * gel_image.a * HSS_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT;
	}

	// TUBE HIGHLIGHT
    if (HSS_TUBE_HIGHLIGHT_IMAGE_OPACITY > 0)
    {
		vec2 tube_highlight_coord = (tube_coord_warped - 0.5) / HSS_TUBE_HIGHLIGHT_IMAGE_SCALE + 0.5;
        // vec4 tube_highlight_image = texture(TubeHighlightImage, tube_highlight_coord);

		// // Dithering for the glass reflection if needed to reduce banding
		// float blur_max_size = 1;
		// float blur_amount = 0.2;
		// vec4 tube_highlight_image = HSS_GetStoichaicBlurredSample(TubeHighlightImage, tube_highlight_coord, HSS_TUBE_HIGHLIGHT_IMAGE_DITHERING_SAMPLES, blur_max_size, blur_amount);
		
		vec4 tube_highlight_image = texture(TubeHighlightImage, tube_highlight_coord);
		tube_highlight_image = HSS_Linearize(tube_highlight_image, HSS_DEFAULT_SRGB_GAMMA);

        // Since the tube highlight has already been applied in the crt pass and we've already masked it to the screen
		// We just need to add the tube highlight on the black screen area
		frag_color_linear += black_edge_mask * HSS_TUBE_HIGHLIGHT_IMAGE_OPACITY * tube_highlight_image * tube_highlight_image.a;
	}



    // frag_color_linear +=  (1 - screen_mask) * vec4(0.8, 0, 0, 1);

	// frag_color_linear += tube_highlight_image;


    // // REFLECTION
	// if (HGL_GLASSBORDER_ON == 1)
	// 	frag_color_linear = mix(frag_color_linear, reflected_color, screen_mask);
	// else
	// 	frag_color_linear += reflected_color;

	frag_color_linear += reflected_color;

	// Convert from linear to gamma space values
	if (HBR_REFLECTION_IS_LAST_PASS == 1)
		FragColor = HSS_ApplyGamma(clamp(frag_color_linear, 0, 1), HSS_DEFAULT_SRGB_GAMMA);
	else
		FragColor = frag_color_linear;
	
}