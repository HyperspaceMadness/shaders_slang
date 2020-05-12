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

// Uncomment the following if you want to see the Placement Guide
#define ShowPlacementGuide

// Following Prefixes are used to make the parameter names unique to this shader
// hmbz_ prefix (for Bezel)
// hbr_ prefix (for Reflection)

layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
    vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	vec4 FinalViewportSize;
	uint FrameCount;

	// Screen Scale
	float hmss_aspect_ratio_mode;
	float hmss_mega_screen_scale_on;
	float hmss_rotate_crt_image;
	float hmss_screen_aspect_ratio;
	float hmss_scanline_direction;
	float hmss_integer_scale_mode;
	float hmss_non_integer_scale;
    float hmss_int_scale_multiple_offset;
	float hmss_int_scale_border_min_height;
	float hmss_position_offset_x;
	float hmss_position_offset_y;

	float hmss_crop_overscan_top;
	float hmss_crop_overscan_bottom;
	float hmss_crop_overscan_left;
	float hmss_crop_overscan_right;

	float hmss_curvature_mode;
	float hmss_curvature_3D_radius;
	float hmss_curvature_3D_view_dist;
	float hmss_curvature_3D_tilt_angle_x;
	float hmss_curvature_3D_tilt_angle_y;
	float hmss_curvature_2D_long_axis;
	float hmss_curvature_2D_short_axis;
	float hmss_curvature_post_scale_x;
	float hmss_curvature_post_scale_y;
	
	float hmss_corner_radius;
	float hmss_screen_edge_sharpness;
	float hmss_tube_black_edge_thickness;
	float hmss_tube_black_edge_curvature_scale;

	float hmss_negative_crop_brightness;

	float hmss_pre_crt_black_level;
	float hmss_pre_crt_gamma;
	float hmss_post_crt_gamma;

	// Image Bezel
	float hmbz_background_image_opacity;
	float hmbz_background_image_scale_mode;
	float hmbz_background_image_aspect_ratio;
	float hmbz_background_image_tube_height;

	float hmbz_tube_glass_image_opacity;
	float hmbz_tube_vignette;
	float hmbz_tube_edge_shadow;

	// Generated Bezel
	float hmbz_bezel_opacity;
	float hmbz_bezel_color_hue;
	float hmbz_bezel_color_saturation;
	float hmbz_bezel_color_value;
	float hmbz_bezel_color_blend_with_image;
	float hmbz_bezel_brightness;
	float hmbz_bezel_highlight;
	float hmbz_bezel_width;
	float hmbz_bezel_height;
	float hmbz_bezel_inner_edge_thickness;
	float hmbz_bezel_inner_corner_radius_scale;
	float hmbz_bezel_outer_corner_radius_scale;
	float hbr_corner_inner_spread;
	float hbr_corner_outer_spread;
	float hbr_corner_spread_falloff; // TODO Need to keep this?
	float hmbz_bezel_noise;

	// Generated Frame
	float hmbz_frame_opacity;
	// float hmbz_frame_brightness;
	float hmbz_frame_thickness;
	float hmbz_frame_inner_edge_thickness;
	float hmbz_frame_outer_corner_radius;
	float hmbz_frame_pos_y_offset;
	float hmbz_frame_shadow_opacity;
	float hmbz_frame_shadow_width;

	float hmbz_background_image_vignette_opacity;
	
	// Blur Stuff
	float hbl_blur_num_samples;
	float hbl_blur_min;
	float hbl_blur_max;

	// Reflection
	float hbr_global_amount;
	float hbr_global_gamma_adjust;

	float hbr_inner_edge_reflection;
	float hbr_inner_edge_fullscreen_glow;
	float hbr_direct_reflection;
	float hbr_diffused_reflection;
	float hbr_fullscreen_glow;
	float hbr_fullscreen_glow_gamma;

	float hbr_fade_amount;
	float hbr_radial_fade_width;
	float hbr_radial_fade_height;

	float hbr_lateral_outer_fade_position;
	float hbr_lateral_outer_fade_distance;

	float hbr_corner_fade;
	float hbr_corner_fade_distance;

	float hbr_noise_amount;
	float hbr_noise_samples;
	float hbr_noise_sample_distance;
} global;

// Import Screen Scale Functions and parameters
// There still must be an entry in the global structure (^Above^) for all these parameter names to access their values
#include "hsm-mega-screen-scale-params-functions.inc"
#include "hsm-mega-bezel-params.inc"

vec2 HMBZ_GetImageLayerCoord(vec2 viewport_coord, vec2 position_offset)
{
	float output_aspect = global.OutputSize.x / global.OutputSize.y;
	float aspect_difference = global.hmbz_background_image_aspect_ratio / output_aspect;
	vec2 fit_height_scale = vec2(aspect_difference, 1);

	// If the texture is supposed to be fit to the screen
	if (global.hmbz_background_image_scale_mode == 1)
		return viewport_coord;

	// If the texture is supposed to fit vertically
	if (global.hmbz_background_image_scale_mode == 2)
		return (viewport_coord - 0.5) / fit_height_scale + 0.5;

	// Otherwise use Auto Scaling with Position offset
	else
	{
		// If using auto scale mode and apply the position adjustment from mega screen scale
		vec2 tube_scale = HMSS_GetTubeScale();
		vec2 screen_height_match_scale =  fit_height_scale * tube_scale.y / (global.hmbz_background_image_tube_height / 100);
		vec2 scale = screen_height_match_scale;
		return HMSS_GetInverseScaledCoord(HMSS_GetCoordWithPositionOffset(viewport_coord), scale);
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
	r=sin(dot(a,vec2(1233.224,1743.335)));
}

float rand(inout float r)
{
	r=fract(3712.65*r+0.61432);
	return (r-0.5)*2.0;
}

// TODO, blend with original?
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
		blurred_color += texture(in_sampler, sample_coord) / num_samples;
	}

	return blurred_color;
}

#pragma stage vertex

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;
layout(location = 2) out vec2 viewportCoord;
layout(location = 3) out vec2 screenCoord;
layout(location = 5) out vec2 imageLayerCoord;

void main()
{
	gl_Position = global.MVP * Position;
    viewportCoord = TexCoord * 1.0001;
	vTexCoord = HMSS_GetCoordWithPositionOffset(TexCoord * 1.0001);
	screenCoord = HMSS_GetScreenVTexCoord(TexCoord);

	imageLayerCoord = HMBZ_GetImageLayerCoord(viewportCoord, HMSS_GetPositionOffset());
}

#pragma stage fragment



layout(location = 0) in vec2 vTexCoord;
layout(location = 2) in vec2 viewportCoord;
layout(location = 3) in vec2 screenCoord;
layout(location = 5) in vec2 imageLayerCoord;

layout(location = 0) out vec4 FragColor;

// Create a 2D sampler from Source and assign it to the variable name Texture
layout(set = 0, binding = 1) uniform sampler2D Source;
layout(set = 0, binding = 2) uniform sampler2D BR_MappingPass;
layout(set = 0, binding = 3) uniform sampler2D BR_CrtPass;
layout(set = 0, binding = 4) uniform sampler2D BR_MirrorLowResPass;
layout(set = 0, binding = 5) uniform sampler2D BR_MirrorBlurredPass;
layout(set = 0, binding = 6) uniform sampler2D BR_MirrorReflectionDiffusedPass;
layout(set = 0, binding = 7) uniform sampler2D BR_MirrorFullscreenGlowPass;

layout(set = 0, binding = 8)  uniform sampler2D BackgroundImage;
layout(set = 0, binding = 9)  uniform sampler2D BackgroundVertImage;
layout(set = 0, binding = 10) uniform sampler2D TubeGlassImage;
layout(set = 0, binding = 11) uniform sampler2D OverlayImage;
layout(set = 0, binding = 12) uniform sampler2D OverlayVertImage;
layout(set = 0, binding = 13) uniform sampler2D AvgLumPass;

float GetVignetteFactor(vec2 coord, float amount)
{
	vec2 VignetteCoord = coord;

	float VignetteLength = length(VignetteCoord * vec2(0.5 * global.OutputSize.x/global.OutputSize.y + 0.5, 1));
	float VignetteBlur = (amount * 0.75) + 0.25;

	// 0.5 full screen fitting circle
	float VignetteRadius = 1.0 - (amount * 0.25);
	float Vignette = smoothstep(VignetteRadius, VignetteRadius - VignetteBlur, VignetteLength);

	return clamp(Vignette, 0, 1);
}

void main()
{
	// Stuff for debugging
	#ifdef ShowPlacementGuide
		float placement_guide_red_alpha = 0;
		float placement_guide_green_alpha = 0;
		float placement_guide_blue_alpha = 0;
	#endif

	vec2 tube_coord_warped = vec2(0, 0);
	float outside_tube_mask = 0;
	float edge_mask = 0;
	HMSS_GetCachedCurvedValues(BR_MappingPass, viewportCoord.xy, tube_coord_warped, outside_tube_mask, edge_mask);

	vec2 tube_warped_coord_ctr = tube_coord_warped - 0.5;

	//----------------------------------------------------
	// CRT Pass
	//----------------------------------------------------
	// Get the CRT pass and make it in linear space & mask the area outside the screen
	vec4 frag_color_linear = HHLP_Linearize(texture(BR_CrtPass, viewportCoord.xy));
	// Shrink the mask by 0.001 to clip off outer edge
	frag_color_linear *= HMSS_GetCornerMask(((HMSS_GetCurvedCoord(screenCoord, 1) - 0.5) * 1.001) + 0.5, global.hmss_corner_radius, global.hmss_screen_edge_sharpness);

	//----------------------------------------------------
	//  Calculate Outside mapping Coords
	//----------------------------------------------------

	/* This first big chunk is to get a mapping of the space outside of the screen which is continuous
	This is more complicated than you would expect because since we are using curved coordinates 
	there are discontinuities outside the normal screen corners, e.g. where x > 1 and y > 1
	So instead of trying to use the coordinates from the screen/tube we use a larger space 
	and subtract the screen space to see how far we are outside of the sreen
	*/

	// General variables related to the main masks referenced later
	float screen_aspect;
	vec2 outermap_scale;
	vec2 screen_scale;
	vec2 tube_scale;
	vec2 tube_coord;
	vec2 outermap_coord;
	vec2 outermap_warped_coord_ctr;
	vec2 outermap_warped_outside_screen_vector;
	vec2 outermap_screen_size_from_center;
	vec2 outermap_screen_corner_ctr_coord;
	vec2 outermap_coord_warped_ctr_at_screen_corner;
	float outside_ratio_warped;
	vec2 frame_coord_ctr;
	float top_mask;
	float bottom_mask;	
	float sides_mask;
	float top_corner_mask;	
	float bottom_corner_mask;
	// float outside_tube_mask;
	float outside_bezel_mask;
	// float edge_mask;
	float noise_mask;

	// screen_aspect is 1.33 for a standard old-style tube placed horizontally
	screen_aspect = HMSS_GetScreenAspect();

	// Scale of the light generating part of the screen relative to the viewport
	screen_scale = HMSS_GetScreenScale();

	// Scale of tube relative to the viewport
	tube_scale = HMSS_GetTubeScale();

	// Additional scale to be applied to the tube scale to create an expanded mapping area 
	outermap_scale = vec2(1, 1) * (1.3 + 1);

	// Coordinate in the space which includes the entire glass area including the illuminated screen and black line around it 
	tube_coord = HMSS_GetInverseScaledCoord(vTexCoord, tube_scale);

	// Get a range width from the outer tube edge to the outer edge of the outermap
	float outermap_range = 0.5 * (outermap_scale.y) * 0.7;
	outermap_warped_coord_ctr = tube_warped_coord_ctr;
	outermap_coord = tube_warped_coord_ctr + 0.5;
	outermap_screen_size_from_center = vec2(0.5, 0.5);
	outermap_warped_outside_screen_vector = outermap_warped_coord_ctr - clamp(outermap_warped_coord_ctr, -0.490, 0.490);
	outside_ratio_warped = clamp(length(outermap_warped_outside_screen_vector) / outermap_range, 0, 1);
	outermap_screen_corner_ctr_coord = vec2(0.5, -0.5);

	// Get a coordinate offset so it is centered around the corner
	outermap_coord_warped_ctr_at_screen_corner = abs(outermap_warped_coord_ctr) - vec2(0.5);

	float screen_scale_diagonal = sqrt(screen_scale.y * screen_scale.y + (screen_scale.y * screen_aspect) * (screen_scale.y * screen_aspect));

	vec2 outer_bezel_scale = vec2(global.hmbz_bezel_width / 100 / screen_aspect + 1, global.hmbz_bezel_height / 100 + 1);
	outer_bezel_scale = (outer_bezel_scale - 1) * screen_scale_diagonal + 1;
	frame_coord_ctr = HMSS_GetInverseScaledCoord(vTexCoord, outer_bezel_scale * tube_scale) - 0.5 + vec2(0, global.hmbz_frame_pos_y_offset / 100);

	// outside_tube_mask = 1 - HMSS_GetCornerMask(tube_warped_coord_ctr + (0.5, 0.5), global.hmbz_bezel_inner_corner_radius_scale * global.hmss_corner_radius, 0.9);

	outside_bezel_mask = 1 - HMSS_GetCornerMask(frame_coord_ctr + 0.5, global.hmbz_bezel_outer_corner_radius_scale * global.hmss_corner_radius, 0.9);

	
	//----------------------------------------------------
	//  Calculate Corner Highlight Mask
	//----------------------------------------------------
	const float pi = 3.1415;
	float corner_highlight_pos_y_offset = 0;

	// Still need to shift the highlight vertically
	//+ vec2(0, corner_highlight_pos_y_offset / 100)

	// Get amount to shift the point at the outer corner to match the overall position offset
	vec2 pos_shift_offset = vec2(0, global.hmbz_frame_pos_y_offset / 100) * screen_scale.y / outermap_scale;
	pos_shift_offset *= outermap_coord.y > 0.5 ? 1 : -1;

	// Get the direction vector from the inner corner of the bezel pointing at the outer corner 
	vec2 corner_crease_dir = (outermap_screen_corner_ctr_coord + pos_shift_offset) / vec2(global.hmbz_bezel_height / 100 + 1, global.hmbz_bezel_width / 100 + 1) - (outermap_screen_corner_ctr_coord + vec2(0, corner_highlight_pos_y_offset / 100)) ;
	corner_crease_dir *= vec2(screen_aspect, 1);

	float aspect_corner_length_scale_offset = screen_aspect > 1 ? 0.9 : 1.5;
	float corner_crease_length = length(corner_crease_dir * aspect_corner_length_scale_offset);

	// A hack to adjust the angle offset, because without it the corner angle isn't pointing exactly at the corner
	// This offset is the opposite direction for vertical and horizontal aspect ratio
	float aspect_corner_angle_offset = screen_aspect > 1 ? 3 : 4;

	// Convert direction vector to an angle so we can rotate the corner crease direction
	float corner_angle_degrees = atan(corner_crease_dir.y / corner_crease_dir.x) / (2 * pi) * 360;
	corner_angle_degrees += aspect_corner_angle_offset;
	float corner_angle_radians = corner_angle_degrees / 360 * 2 * pi;
	corner_crease_dir = vec2(cos(corner_angle_radians), sin(corner_angle_radians));

	// Get the distance perpendicular to the crease direction so we can use it to fade later
	float distance_from_crease = HHLP_GetDistanceToLine(outermap_coord_warped_ctr_at_screen_corner.x, outermap_coord_warped_ctr_at_screen_corner.y, 1, corner_crease_dir.y / corner_crease_dir.x, 0 );

	float fade_out_to_corner = HHLP_QuadraticBezier(clamp(length(outermap_warped_outside_screen_vector) / (corner_crease_length * 2), 0, 1), vec2(0.5, global.hbr_corner_spread_falloff / 100));

	float corner_fade_width_inner = global.hbr_corner_inner_spread / 100 * (screen_scale.x + screen_scale.y) * global.hmbz_bezel_inner_corner_radius_scale * global.hmss_corner_radius / 10 / 250 * 1.2;
	float corner_fade_width_outer = global.hbr_corner_outer_spread / 100 * (screen_scale.x + screen_scale.y) * global.hmbz_bezel_outer_corner_radius_scale * global.hmss_corner_radius / 10 / 250 * 1.6;
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
	sides_mask = 1 - top_bottom_vs_sides_mask;
	top_mask = top_half_mask * top_bottom_vs_sides_mask;
	bottom_mask = (1 -top_half_mask) * top_bottom_vs_sides_mask;

	float corner_mask = smoothstep(corner_fade_width / 2, 0, distance_from_crease);

	top_corner_mask = corner_mask * top_half_mask;
	bottom_corner_mask = corner_mask * (1 - top_half_mask);

	float frame_inner_edge_mask = (global.hmbz_frame_inner_edge_thickness == 0) ? 0 : 1 - HMSS_GetCornerMask(frame_coord_ctr * (1 + (global.hmbz_frame_inner_edge_thickness / 1000 / vec2(screen_aspect, 1))) + 0.5, global.hmbz_bezel_outer_corner_radius_scale * global.hmss_corner_radius, 0.9);

	noise_mask = clamp(fract(sin(dot(outermap_warped_coord_ctr + vec2(0.5, 0.5) + 1, vec2(12.9898, 78.233))) * 43758.5453), 0, 1);
	
	// vec2 inside_tube_coord = clamp(0.5 - clamp(abs(tube_warped_coord_ctr), vec2(0), vec2(0.5)), 0, 1);
	float tube_shadow_mask = HMSS_GetCornerMask(tube_warped_coord_ctr + 0.5, global.hmbz_bezel_inner_corner_radius_scale * global.hmss_corner_radius, 0); //HHLP_EasePowerOut(smoothstep(global.hmbz_tube_edge_shadow * 0.2, 0.01, dist_inside_tube_edge), 3); //HHLP_QuadraticBezier(smoothstep(1 / 100, 0, dist_inside_tube_edge), vec2(0, 1));
	float tube_edge_shadow_mult = global.hmbz_tube_edge_shadow * (tube_shadow_mask) + (1 - global.hmbz_tube_edge_shadow);
	// #ifdef ShowPlacementGuide
	// 	placement_guide_red_alpha += 0.5*tube_shadow_mask;
	// #endif

	// Add Vignette inside the tube
	frag_color_linear *= GetVignetteFactor(tube_warped_coord_ctr, global.hmbz_tube_vignette);

	frag_color_linear *= tube_edge_shadow_mult;

	vec4 base_image	= frag_color_linear;
	vec2 tiled_image_coord = mod(imageLayerCoord, 1);
	vec4 background_image = vec4(0);
	if (HMSS_GetScreenAspect() > 1)
	{
		background_image = texture(BackgroundImage, tiled_image_coord).rgba;
	}
	else 
	{
		background_image = texture(BackgroundVertImage, tiled_image_coord).rgba;
	}
	background_image = HHLP_Linearize(background_image);

	float vignette_shadow_mask = 0;
	vignette_shadow_mask += 0.75 * HHLP_QuadraticBezier(1 - GetVignetteFactor(viewportCoord - 0.5, global.hmbz_background_image_vignette_opacity), vec2(1, 0.5));
	vignette_shadow_mask += 0.5 * global.hmbz_background_image_vignette_opacity * HHLP_QuadraticBezier(smoothstep(outside_ratio_warped, 0, 0.1), vec2(1, 0.5));
	
	// OLD Vignette Code
	// // Get Mask for the Vignette around the sides and top and bottom of the screen
	// float side_vignette_width = (1 - screen_scale.x);
	// float vignette_shadow_mask = 0.9 * HHLP_QuadraticBezier(smoothstep(side_vignette_width, 0, 0.5 - abs(viewportCoord.x - 0.5)), vec2(1, 0)) +
	// 							0.9 * HHLP_QuadraticBezier(smoothstep(viewportCoord.y > 0.5 ? 0.25 : 0.2, 0, 0.55 - abs(viewportCoord.y - 0.5)), vec2(1, 0));
	// vignette_shadow_mask = clamp(global.hmbz_background_image_vignette_opacity * vignette_shadow_mask, 0, 1);
	
	//----------------------------------------------------
	// Background Image - Applied at the bottom
	//----------------------------------------------------
	// TODO The position adjustment is moving the texture twice as fast as the screen

	float bezel_image_alpha = background_image.a;

	// Add Background
	float outside_tube_mask_wider = 1 - HMSS_GetCornerMask(tube_warped_coord_ctr * 0.996 + 0.5, global.hmbz_bezel_inner_corner_radius_scale * global.hmss_corner_radius, 0.9);

	float clipping_mask = outside_tube_mask_wider * bezel_image_alpha;
	vec4 background_color = global.hmbz_background_image_opacity * background_image;
	if (global.hmbz_background_image_vignette_opacity > 0)
	{
		background_color = mix(background_color, vec4(0, 0, 0, 1), vignette_shadow_mask);
	}

	frag_color_linear	= vec4(mix(tube_edge_shadow_mult * base_image, background_color, clipping_mask));


	//----------------------------------------------------
	// Tube Glass Image
	//----------------------------------------------------
	if (global.hmbz_tube_glass_image_opacity > 0)
	{
		vec4 tube_glass_image = HHLP_Linearize(texture(TubeGlassImage, tube_warped_coord_ctr * 0.97 + 0.5 ).rgba);

		frag_color_linear	= frag_color_linear + (global.hmbz_tube_glass_image_opacity / 100) * tube_glass_image.a * (1 - outside_tube_mask) * tube_glass_image;
	}
	
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
	
	float hmbz_bezel_brightness_frame_inner_edge = 1;
	float hmbz_bezel_brightness_frame_outer_edge = 0.5;
	float hmbz_brightness_shadow = 0;
	float hmbz_frame_brightness = 100;

	vec3 orig_color = HHLP_Linearize(vec4(HMSS_HSVtoRGB(vec3(global.hmbz_bezel_color_hue / 360, global.hmbz_bezel_color_saturation / 100, global.hmbz_bezel_color_value / 100)), 1)).rgb;
	vec3 base_color = mix(orig_color, background_color.rgb, global.hmbz_bezel_color_blend_with_image);

	vec3 base_color_with_noise = mix(base_color, 1.5 * base_color * noise_mask, global.hmbz_bezel_noise / 100);
	vec3 top_color = hmbz_bezel_brightness_top * global.hmbz_bezel_brightness / 100 * base_color_with_noise;
	vec3 bottom_color = hmbz_bezel_brightness_bottom * global.hmbz_bezel_brightness / 100 * base_color_with_noise;
	vec3 sides_color = hmbz_bezel_brightness_sides * global.hmbz_bezel_brightness / 100 * base_color_with_noise;

	vec3 frame_color = hmbz_frame_brightness / 100 * mix(base_color, 1.5 * base_color * noise_mask, 0.6 * global.hmbz_bezel_noise / 100);;
	
	vec3 frame_outer_edge_color = hmbz_bezel_brightness_frame_outer_edge * base_color_with_noise; //TODO When Highlight is off frame inner edge is very dark
	vec3 outside_frame_color = hmbz_brightness_shadow * base_color_with_noise;

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
	//(1 + global.hmbz_bezel_noise) * (1 - noise_mask * global.hmbz_bezel_noise) * 
	float combined_highlight_mask = (1 + 2.5 * global.hmbz_bezel_noise / 100) * (1 - noise_mask * 2.5 * global.hmbz_bezel_noise / 100) * (top_center_highlight_mask + bottom_center_highlight_mask + sides_highlight_mask);
	vec3 bezel_color = bezel_diffuse_color + global.hmbz_bezel_highlight / 100 * combined_highlight_mask;
	bezel_color += global.hmbz_bezel_highlight / 100 * edge_highlight_mask;
	
	// Add the inner edge highlight on top of the bezel color which has it's own highlight
	vec3 frame_inner_edge_color = bezel_color + hmbz_bezel_brightness_frame_inner_edge * bezel_color;
	bezel_color = mix(bezel_color, frame_inner_edge_color, frame_inner_edge_mask);

	// Get color for the frame area outside of the bezel
	vec2 frame_outside_coord_ctr = frame_coord_ctr / vec2(global.hmbz_frame_thickness / 100 / screen_aspect + 1, global.hmbz_frame_thickness / 100 + 1);
	float outside_frame_mask = 1 - HMSS_GetCornerMask(frame_outside_coord_ctr + 0.5, global.hmbz_frame_outer_corner_radius, 1);

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
	float dist_outside_frame = length(clamp(abs(frame_outside_coord_ctr) - frame_edge, 0, 1) * vec2(screen_aspect, 1));
	float frame_shadow_mask_0 = HHLP_QuadraticBezier(smoothstep(global.hmbz_frame_shadow_width / 100, 0, dist_outside_frame), vec2(1, 0));

	// Get masks for shadows, from frame as well as sides and top and bottom of viewport
	float bezel_mask = (1 - outside_bezel_mask) * outside_tube_mask;
	float frame_mask = outside_bezel_mask * (1 - outside_frame_mask);
	float frame_shadow_mask = outside_frame_mask * frame_shadow_mask_0;

	// Get 
	float final_mask =  0;
	
	if (global.hmbz_bezel_opacity > 0.001)
	{
		final_mask += global.hmbz_bezel_opacity * bezel_mask;
	}
	if (global.hmbz_frame_opacity > 0.001)
	{
		final_mask += global.hmbz_frame_opacity * frame_mask;
		final_mask += global.hmbz_frame_opacity * global.hmbz_frame_shadow_opacity * frame_shadow_mask;
	}
	final_mask = clamp(final_mask, 0, 1) * outside_tube_mask;

	// Add Bezel, Frame & Shadow color to the screen color
	frag_color_linear = mix(frag_color_linear, bezel_and_frame_color_v4, final_mask);
	

	//----------------------------------------------------
	// Reflection - Applied ON TOP of the Bezel
	//----------------------------------------------------
	if (global.hbr_global_amount != 0)
	{
		// Corner Mask for Specular highlights
		float fade_out_to_corner = smoothstep(0 + global.hbr_corner_fade_distance / 100 / 2, 0 - global.hbr_corner_fade_distance / 100 / 2, outside_ratio_warped);
		float corner_fade_mask = (top_corner_mask + bottom_corner_mask) * (global.hbr_corner_fade / 100) * fade_out_to_corner * 2;

		// Radial fade - fading away from the edges of the screen
		float radial_fade_speed = 100;
		float radial_fade_sides = 1 - HHLP_QuadraticBezier(clamp_0_1(outside_ratio_warped / (global.hbr_radial_fade_width / 500)), vec2(1 - (radial_fade_speed / 100), 1));
		float radial_fade_top_bottom = 1 - HHLP_QuadraticBezier(clamp_0_1(outside_ratio_warped / (global.hbr_radial_fade_height / 500)), vec2(1 - (radial_fade_speed / 100), 1));
		float radial_fade_mask = clamp_0_1((1 - sides_mask) * radial_fade_top_bottom
									+ sides_mask * radial_fade_sides);

		float radial_inner_fade_mask = clamp_0_1(0.3 + 0.7 * HHLP_QuadraticBezier(smoothstep(0.01, 0.3, outside_ratio_warped / (global.hbr_radial_fade_width / 500)), vec2(0.1, 0.3)));

		// Lateral fade - Fading left to right across the bottom or top to bottom along the sides 
		float lateral_fade_mask = (1 - sides_mask) * GetFade(abs(outermap_warped_coord_ctr.x) + (global.hbr_lateral_outer_fade_position / -1000) / screen_aspect, 
																	outermap_screen_size_from_center.x,
																	outermap_screen_size_from_center.x * (global.hbr_lateral_outer_fade_distance / 100))
										+  sides_mask * GetFade(abs(outermap_warped_coord_ctr.y) + (global.hbr_lateral_outer_fade_position / -1000) / screen_aspect, 
																outermap_screen_size_from_center.y, 
																outermap_screen_size_from_center.y * (global.hbr_lateral_outer_fade_distance / 100)); 

		vec2 screen_coord_ctr = screenCoord - 0.5;
		float edge_lateral_fade_mask = (1 - sides_mask) * smoothstep(0.5, 0.5 - 0.07 / HMSS_GetScreenAspect(), abs(screen_coord_ctr.x))
										+  sides_mask * smoothstep(0.5, 0.43, abs(screen_coord_ctr.y));

		// float lateral_fade_center_mask = (1 - sides_mask) * clamp_0_1(GetFade(abs(outermap_warped_coord_ctr.x), 0, 0.5))
		// 										+ sides_mask * clamp_0_1(GetFade(abs(outermap_warped_coord_ctr.y), 0, 0.5));

		// Put all the fades together into one mask
		float combined_fade_mask = clamp_0_1(global.hbr_fade_amount * (radial_fade_mask * lateral_fade_mask)) + 1 - global.hbr_fade_amount;


		// Because the mirroring of the screen has been done in the mirror-wrap shader we just need to sample the screen
		// Sample the fullscreen glow pass and scale it up so the bright areas always reach the edges
		//vec4 sampled_noise = GetStoichaicBlurredSample(BR_MirrorLowResPass, viewportCoord, 1, 0.4, 1);

		// TODO - When samples fall outside of the screen use a mirror wrapped coord
		float stoichaic_blur_samples = global.hbr_noise_samples;
		float noise_falloff = 0.3;
		float stoichaic_blur_max = HHLP_QuadraticBezier(outside_ratio_warped, vec2(0, noise_falloff)) * 3;
		float stoichaic_blur_amount = global.hbr_noise_sample_distance;

		vec4 fullscreen_blurred_sampled_color = GetStoichaicBlurredSample(BR_MirrorFullscreenGlowPass, viewportCoord.xy, stoichaic_blur_samples, (1 - corner_mask) * stoichaic_blur_max * 3, stoichaic_blur_amount);

		vec4 corner_reflection_color = fullscreen_blurred_sampled_color;
		
		vec4 fullscreen_glow_color = pow(fullscreen_blurred_sampled_color, vec4(global.hbr_fullscreen_glow_gamma));
		
		vec4 diffused_reflection_color = texture(BR_MirrorReflectionDiffusedPass, viewportCoord.xy);
		vec4 diffused_reflection_scatter_color = GetStoichaicBlurredSample(BR_MirrorReflectionDiffusedPass, viewportCoord.xy, stoichaic_blur_samples, stoichaic_blur_max, stoichaic_blur_amount);
		vec4 diffused_reflection_blended_color = mix(diffused_reflection_color, diffused_reflection_scatter_color, global.hbr_noise_amount);

		vec4 blurred_reflection_color = texture(BR_MirrorBlurredPass, viewportCoord.xy);
		vec4 blurred_reflection_scatter_color = GetStoichaicBlurredSample(BR_MirrorBlurredPass, viewportCoord.xy, stoichaic_blur_samples, stoichaic_blur_max, stoichaic_blur_amount);
		vec4 blurred_reflection_blended_color = mix(blurred_reflection_color, blurred_reflection_scatter_color, global.hbr_noise_amount);

		//vec4 unblurred_reflection_color = texture(BR_MirrorLowResPass, viewportCoord.xy);
		//vec4 unblurred_reflection_scatter_color = GetStoichaicBlurredSample(BR_MirrorLowResPass, viewportCoord.xy, stoichaic_blur_samples, stoichaic_blur_max, stoichaic_blur_amount);

		// Add Fullscreen Glow
		float lateral_fade_outer_mask_for_glow = (lateral_fade_mask - 1) * 0.8 + 1;

		//Combine diffused and undiffused reflection
		
		vec4 bezel_reflected_color = (global.hbr_direct_reflection * blurred_reflection_blended_color + global.hbr_diffused_reflection * diffused_reflection_blended_color) * combined_fade_mask;

		//Screen transfer mode 1 - (1 - diffused_reflection_color) * (1 - blurred_reflection_color);

		// Add Reflection from corners which is sampled from the fullscreen glow
		bezel_reflected_color += global.hbr_corner_fade * corner_reflection_color * corner_fade_mask;

		// Add Fullscreen Glow
		bezel_reflected_color += global.hbr_fullscreen_glow / 100 * 1.5 * fullscreen_glow_color * radial_inner_fade_mask * lateral_fade_outer_mask_for_glow;

		// Add Bezel and Edge reflection together

		vec4 reflected_color = vec4(0);
		vec4 edge_reflected_color = 1.25 * global.hbr_inner_edge_reflection * (blurred_reflection_color + 0.50 * diffused_reflection_color);
		float reflection_area_mask = (1 - outside_bezel_mask) * outside_tube_mask;

		// Edge Reflection
		#ifdef GLASS_PRESET
			reflected_color += (1 - vignette_shadow_mask) * bezel_reflected_color;
			reflection_area_mask *= outside_tube_mask_wider;
		#else
			reflected_color += (1 - edge_mask) * bezel_reflected_color;
			reflected_color += edge_mask * (edge_lateral_fade_mask * edge_reflected_color + corner_mask * corner_reflection_color);
		#endif
								
		reflected_color = global.hbr_global_amount * pow(reflected_color, vec4(global.hbr_global_gamma_adjust));
		
		// Mask reflection to only appear inside the bezel
		reflected_color *= reflection_area_mask;

		// Add reflection_color with mask
		frag_color_linear += reflected_color;

		#ifdef GLASS_PRESET
			// vec4 edge_color = bezel_and_frame_color_v4 + global.hbr_global_amount * pow(edge_reflected_color, vec4(global.hbr_global_gamma_adjust));

			vec4 edge_color = global.hbr_global_amount * pow(edge_reflected_color, vec4(global.hbr_global_gamma_adjust));
			frag_color_linear = mix(frag_color_linear, edge_color, edge_mask * outside_tube_mask);
		#endif

		float avg_lum_mult = smoothstep(0.01, 0.5, pow(texture(AvgLumPass, viewportCoord).a, 1.3)) + 0.5 ;
		vec4 edge_fullscreen_glow = global.hbr_inner_edge_fullscreen_glow * edge_highlight_mask * outside_tube_mask * (vec4(0.005) + avg_lum_mult * (2 * fullscreen_glow_color + vec4(0.01)));

		frag_color_linear += edge_fullscreen_glow;
	}
	vec4 overlay_image = vec4(0);

	if (HMSS_GetScreenAspect() > 1)
	{
		overlay_image = texture(OverlayImage, imageLayerCoord).rgba;
	}
	else 
	{
		overlay_image = texture(OverlayVertImage, imageLayerCoord).rgba;
	}
	
	FragColor = mix(clamp(HHLP_Delinearize(frag_color_linear), 0, 1), overlay_image, overlay_image.a);

	// float outside_tube_mask = 1 - HMSS_GetCornerMask(HMSS_GetCurvedCoord(tube_coord, 1) + (0.5, 0.5), global.hmbz_bezel_inner_corner_radius_scale * global.hmss_corner_radius, 0.9);
	// FragColor = vec4(outside_tube_mask);

	// Add the color for the debug Stuff
	#ifdef ShowPlacementGuide
		FragColor += vec4(1, 0, 0, 1) * placement_guide_red_alpha;
		FragColor += vec4(0, 1, 0, 1) * placement_guide_green_alpha;
		FragColor += vec4(0, 0, 1, 1) * placement_guide_blue_alpha;
	#endif	


}