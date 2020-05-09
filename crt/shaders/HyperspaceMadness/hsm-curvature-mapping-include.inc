// TODO separate out parameters & global variable binding into their own files
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
	float hmss_screen_vignette;
	float hmss_tube_black_edge_thickness;
	float hmss_tube_black_edge_curvature_scale;

	float hmss_negative_crop_brightness;
	float hmss_phosphor_persistence;

	float hmss_pre_crt_black_level;
	float hmss_pre_crt_gamma;
	float hmss_post_crt_gamma;

	// Image Bezel
	float hmbz_background_image_opacity;
	float hmbz_background_image_scale_mode;
	float hmbz_background_image_aspect_ratio;
	float hmbz_background_image_tube_height;

	float hmbz_tube_glass_image_opacity;
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
	float hmbz_bezel_noise;

	// Generated Frame
	float hmbz_frame_opacity;
	// float hmbz_frame_brightness;
	float hmbz_frame_thickness;
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

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out vec2 screenCoord;
layout(location = 2) out vec2 tubeCoord;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord * 1.0001;
   
   // Coordinate in the space which includes the entire glass area including the illuminated screen and black line around it 
   tubeCoord = HMSS_GetTubeVTexCoord(vTexCoord);
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in vec2 screenCoord;
layout(location = 2) in vec2 tubeCoord;
layout(location = 0) out vec4 FragColor;

void main()
{
	float screen_aspect = HMSS_GetScreenAspect();
	
	vec2 tube_curved_coord = HMSS_GetCurvedCoord(tubeCoord, global.hmss_tube_black_edge_curvature_scale);

	vec2 edge_mask_coord = (tube_curved_coord - 0.5) * (1 - (global.hmbz_bezel_inner_edge_thickness / 100 / vec2(screen_aspect, 1))) + 0.5;
	float edge_sharpness = 0.9;

	// If this is used in the glass preset adjust the smoothness of the edge of the glass 
	#ifdef GLASS_PRESET
		edge_sharpness = HMBZ_GLASS_INNER_EDGE_SOFTNESS;
	#endif

	float outside_tube_mask = 1 - HMSS_GetCornerMask(tube_curved_coord, global.hmbz_bezel_inner_corner_radius_scale * global.hmss_corner_radius, 0.9);

	float edge_mask =  HMSS_GetCornerMask(edge_mask_coord, global.hmbz_bezel_inner_corner_radius_scale * global.hmss_corner_radius, edge_sharpness);

	FragColor = vec4(tube_curved_coord.x, tube_curved_coord.y, outside_tube_mask, edge_mask);
}