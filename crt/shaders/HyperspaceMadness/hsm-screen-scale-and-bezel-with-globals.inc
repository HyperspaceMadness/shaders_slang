/*   
hsm-screen-scale-and-bezel-with-globals.inc

Globals for screen scale and bezel
*/

layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
    vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	vec4 FinalViewportSize;
	uint FrameCount;

	float hmss_mega_screen_scale_on;
	float hmss_screen_scale_debug;
	
	float hmss_rotate_crt_image;
	float hmss_aspect_ratio_mode;
	float hmss_screen_aspect_ratio;
	float hmss_integer_scale_mode;
	float hmss_non_integer_scale;
    float hmss_int_scale_multiple_offset;
	float hmss_int_scale_border_min_height;

	float hmss_scanline_direction;
	float hmss_core_res_mult;
	float HMSS_INTERLACE_TRIGGER_RES;

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
	float HMSS_CURVATURE_POST_SCALE_X;
	float HMSS_CURVATURE_POST_SCALE_Y;
	
	float hmss_screenfx_corner_radius;
	float hmss_screenfx_edge_sharpness;
	float hmss_screenfx_vignette;

	float hmss_color_crt_profile;
	float hmss_color_space;
	float hmss_color_lut_colors_on;
	float hmss_color_black_level;
	// float hmss_color_pre_crt_gamma_adjust;
	float hmss_color_negative_crop_brightness;
	float hmss_color_luminance;
	float hmss_color_temperature;
	float hmss_color_saturation;
	float hmss_color_crt_gamma;

	float hmss_phosphor_persistence;

	float hmss_screenfx_fake_scanline_opacity;

	float hmss_tube_black_edge_thickness;
	float hmss_tube_black_edge_curvature_scale;

	float hmbz_tube_glass_image_opacity;
	float hmbz_tube_edge_shadow;

	// Image Bezel
	float hmbz_background_image_opacity;
	float hmbz_background_image_scale_mode;
	float hmbz_background_image_aspect_ratio;
	float hmbz_background_image_tube_height;
	float hmbz_background_image_vignette_opacity;


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
	float hmbz_bezel_noise;

	// Generated Frame
	float hmbz_frame_opacity;
	float hmbz_frame_thickness;
	float hmbz_frame_outer_corner_radius;
	float hmbz_frame_pos_y_offset;
	float hmbz_frame_shadow_opacity;
	float hmbz_frame_shadow_width;
	
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
	float hbr_corner_inner_spread;
	float hbr_corner_outer_spread;
	float hbr_corner_fade_distance;

	float hbr_noise_amount;
	float hbr_noise_samples;
	float hbr_noise_sample_distance;
	float hbr_corner_spread_falloff;

	float htl_top_image_opacity;
	float htl_top_image_blend_mode;
	float htl_top_image_mask_mode;
	
	float hmss_bezel_gamma;
} global;

#include "hsm-screen-scale-params-functions.inc"
#include "hsm-bezel-params.inc"