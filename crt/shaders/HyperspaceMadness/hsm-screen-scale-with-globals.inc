/*   
hsm-screen-scale-with-globals.inc

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
} global;

#include "hsm-screen-scale-params-functions.inc"