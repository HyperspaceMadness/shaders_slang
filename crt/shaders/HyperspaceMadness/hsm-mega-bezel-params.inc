#pragma parameter hag_afterglow_amount                  "[AFTERGLOW]  Amount"        0.07 0.0 1.0 0.01
#pragma parameter hag_afterglow_persistence             "[AFTERGLOW]  Persistence"   0.05 0.0 1.0 0.01
#pragma parameter hag_afterglow_saturation              "[AFTERGLOW]  Saturation"    0.10 0.0 1.0 0.01

#pragma parameter hmbz_bezel_color_hue					"[BEZEL & FRAME]  Color Hue" 0 0 360 0.5
#pragma parameter hmbz_bezel_color_saturation			"[BEZEL & FRAME]  Color Saturation" 0 0 100 1
#pragma parameter hmbz_bezel_color_value				"[BEZEL & FRAME]  Color Value (Brightness)" 9 0 100 0.2
#pragma parameter hmbz_bezel_color_blend_with_image		"[BEZEL & FRAME]  Blend Color with Image" 0 0 1 0.05

#pragma parameter hmbz_bezel_opacity 					"[BEZEL]  Opacity" 1 0 1 0.05
#pragma parameter hmbz_bezel_width 						"[BEZEL]  Width" 6.5 -10 200 0.1
#pragma parameter hmbz_bezel_height 					"[BEZEL]  Height" 5 -10 200 0.1
#pragma parameter hmbz_bezel_inner_curvature_scale 		"[BEZEL]  Inner Curvature" 1 0 4 0.1
#pragma parameter hmbz_bezel_inner_corner_radius_scale	"[BEZEL]  Inner Corner Radius Scale" 0.5 0 10 0.1
#pragma parameter hmbz_bezel_outer_corner_radius_scale 	"[BEZEL]  Outer Corner Radius Scale" 1 0 10 0.1
#pragma parameter hmbz_bezel_inner_edge_thickness		"[BEZEL]  Inner Edge Thickness" 0.5 0 5 0.1
#pragma parameter hmbz_bezel_brightness 				"[BEZEL]  Brightness" 60 0 300 2
#pragma parameter hmbz_bezel_highlight 					"[BEZEL]  Highlight" 2 0 100 0.2
#pragma parameter hmbz_bezel_noise 						"[BEZEL]  Noise" 30 0 100 1

#pragma parameter hmbz_bezel_corner_highlight_inner_spread 	 "[BEZEL]  Corner Highlight Inner Spread" 100 0 500 10
#pragma parameter hmbz_bezel_corner_highlight_outer_spread 	 "[BEZEL]  Corner Highlight Outer Spread" 100 0 500 10
#pragma parameter hmbz_bezel_corner_highlight_spread_falloff "[BEZEL]  Corner Highlight Spread Falloff"  50 1 200 1

#pragma parameter hmbz_frame_opacity 					"[FRAME]  Opacity" 1 0 1 0.05
#pragma parameter hmbz_frame_brightness 				"[FRAME]   Brightness" 100 0 300 2
#pragma parameter hmbz_frame_thickness 					"[FRAME]   Thickness" 8 0 200 0.2
#pragma parameter hmbz_frame_outer_corner_radius 		"[FRAME]   Outer Corner Radius" 5 0 10 0.05
#pragma parameter hmbz_frame_inner_edge_thickness		"[FRAME]   Inner Edge Thickness" 2 0 50 0.05
#pragma parameter hmbz_frame_pos_y_offset 				"[FRAME]   Pos Y Offset" 0 -25 25 0.05

#pragma parameter hmbz_frame_shadow_opacity				"[FRAME]   Shadow Opacity" 1 0 3 0.01
#pragma parameter hmbz_frame_shadow_width				"[FRAME]   Shadow Width" 10 0 50 0.1

#pragma parameter hmbz_vignette_shadow_opacity			"[FRAME]  Vignette Opacity" 0.8 0 2 0.02

// Bezel Parameters
#pragma parameter hmbz_image_bezel_opacity 				"[IMAGE BEZEL]  Opacity" 1 0 1 0.05
#pragma parameter hmbz_image_bezel_brightness 			"[IMAGE BEZEL]  Brightness" 1 0.5 3 0.01
#pragma parameter hmbz_image_bezel_scale_mode 			"[IMAGE BEZEL]  Scale Mode - 0:Auto 1:Fullscreen 2:Fit Height" 2 0 2 1
#pragma parameter hmbz_image_bezel_aspect_ratio 		"[IMAGE BEZEL]  Aspect Ratio" 1.77 0.25 4 0.01
// Visual height of the tube in the texture (Only used in Image Mode 0)
#pragma parameter hmbz_image_bezel_tube_height     		"[IMAGE BEZEL]  Tube Height (in Texture)" 69 10 150.0 0.1
#pragma parameter hmbz_image_bezel_cut_out_inside_frame "[IMAGE BEZEL]  Cut Out Inside Frame" 1 0 1 1

// Blur
#pragma parameter hbl_blur_num_samples 					"[REFLECTION BLUR]  Num Samples - 0 for OFF" 20 0 40 1
#pragma parameter hbl_blur_min 							"[REFLECTION BLUR]  Min" 	0 0 1 0.01
#pragma parameter hbl_blur_max 							"[REFLECTION BLUR]  Max" 	0.95 0 1 0.01

// Reflection Noise
#pragma parameter hbr_noise_amount 						"[REFLECTION NOISE]  Amount" 0.5 0 1 0.1
#pragma parameter hbr_noise_samples 					"[REFLECTION NOISE]   Samples (0 for OFF)" 1 0 20 1
#pragma parameter hbr_noise_sample_distance 			"[REFLECTION NOISE]   Sample Distance" 0.20 0 1 0.01
#pragma parameter hbr_noise_falloff 					"[REFLECTION NOISE]   Falloff" 0.3 0 1 0.01

// Reflection Parameters
#pragma parameter hbr_global_amount 					"[REFLECTION]  Global Amount" 0.4 0 3 0.02
#pragma parameter hbr_global_gamma_adjust 				"[REFLECTION]  Main Gamma Adjust" 1.2 0.25 3 0.05

#pragma parameter hbr_inner_edge_reflection 			"[REFLECTION]  Inner Edge Reflection" 0.7 0 3 0.02
#pragma parameter hbr_direct_reflection 				"[REFLECTION]  Direct Reflection" 1 0 3 0.02
#pragma parameter hbr_diffused_reflection 				"[REFLECTION]  Diffused Reflection" 0.5 0 3 0.02
#pragma parameter hbr_fullscreen_glow 					"[REFLECTION]  FullScreen Glow" 75 0 600 0.5
#pragma parameter hbr_fullscreen_glow_gamma 			"[REFLECTION]  FullScreen Glow Gamma" 3 0 5 0.02

#pragma parameter hbr_fade_amount 						"[REFLECTION]  Fade Amount" 1 0 1 0.05
#pragma parameter hbr_radial_fade_speed 				"[REFLECTION]  Radial Fade Speed"  100 1 200 1
#pragma parameter hbr_radial_fade_width 				"[REFLECTION]  Radial Fade Width" 70 0 300 1
#pragma parameter hbr_radial_fade_height 				"[REFLECTION]  Radial Fade Height" 100 0 300 1

#pragma parameter hbr_lateral_outer_fade_position 		"[REFLECTION]  Lateral Outer Fade Position" -18 -100 100 0.5
#pragma parameter hbr_lateral_outer_fade_distance 		"[REFLECTION]  Lateral Outer Fade Distance" 20 1 50 0.5

#pragma parameter hbr_corner_fade 						"[REFLECTION]  Corner Fade" 10 1 100 0.5
#pragma parameter hbr_corner_fade_distance 				"[REFLECTION]  Corner Fade Distance" 100 1 100 1

#pragma parameter hbr_reflection_mask_mode 				"[REFLECTION]  Reflection Mask Mode(0:None, 1-In Frame)" 1 0 2 1
