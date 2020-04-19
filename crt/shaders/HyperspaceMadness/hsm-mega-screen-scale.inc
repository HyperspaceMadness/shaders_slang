/*   
hsm-mega-screen-scale

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Include file which has supporting functions to do a managed scaling of the visible screen/tube within the full framebuffer image
	-Developed to support scaling across multiple shaders needed for the Mega Bezel Reflection shader chain so that the scale of the 
		screen and effects around the screen can be synchronized
	-Useful for placement and scale of the screen when working with overlay images
	-Supports automatically switching to vertical aspect ratio for TATE/Vertical games when the core aspect ratio is vertical

	-Retroarch Video Settings:
		-Aspect Ratio should be set to the monitor aspect ratio
		-Integer Scale should be set to OFF

	- Thanks to Torridgristle for his curvature function!
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

	float hmss_pre_crt_black_level;
	float hmss_pre_crt_gamma;
	float hmss_post_crt_gamma;

	float hmss_negative_crop_brightness;
} global;

#include "hsm-mega-screen-scale-params-functions.inc"