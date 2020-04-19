// Tube Glass & Shadow
#pragma parameter hmbz_tube_glass_image_opacity         "[TUBE]  Tube Glass Image Opacity (Additive)" 0 0 200 0.2
#pragma parameter hmbz_tube_edge_shadow                 "[TUBE]  Tube Edge Shadow" 0.7 0 2 0.05

// Background
#pragma parameter hmbz_background_image_opacity 		"[BG IMAGE]  Opacity" 1 0 1 0.05
#pragma parameter hmbz_background_image_brightness 		"[BG IMAGE]  Brightness" 1 0.5 3 0.01
#pragma parameter hmbz_background_image_scale_mode 		"[BG IMAGE]  Scale Mode - 0:Auto 1:Fullscreen 2:Fit Height" 2 0 2 1
#pragma parameter hmbz_background_image_aspect_ratio 	"[BG IMAGE]  Aspect Ratio" 1.77 0.25 4 0.01
// Visual height of the tube in the texture (Only used in Scale Mode 0)
#pragma parameter hmbz_background_image_tube_height      "[BG IMAGE]  Tube Height (in Texture)" 69 10 150.0 0.1
#pragma parameter hmbz_background_image_vignette_opacity "[BG IMAGE]  Vignette Opacity" 0.8 0 2 0.02


#pragma parameter hmbz_bezel_color_hue					"[BEZEL & FRAME COLOR]  Color Hue" 0 0 360 0.5
#pragma parameter hmbz_bezel_color_saturation			"[BEZEL & FRAME COLOR]  Color Saturation" 0 0 100 1
#pragma parameter hmbz_bezel_color_value				"[BEZEL & FRAME COLOR]  Color Value (Brightness)" 9 0 100 0.2
#pragma parameter hmbz_bezel_color_blend_with_image		"[BEZEL & FRAME COLOR]  Blend Color with Image" 0 0 1 0.05

// Bezel
#pragma parameter hmbz_bezel_opacity 					"[BEZEL]  Opacity" 1 0 1 0.05
#pragma parameter hmbz_bezel_width 						"[BEZEL]  Width" 6.5 -10 200 0.1
#pragma parameter hmbz_bezel_height 					"[BEZEL]  Height" 5 -10 200 0.1
#pragma parameter hmbz_bezel_inner_corner_radius_scale	"[BEZEL]  Inner Corner Radius Scale" 0.5 0 10 0.1
#pragma parameter hmbz_bezel_outer_corner_radius_scale 	"[BEZEL]  Outer Corner Radius Scale" 1 0 10 0.1
#pragma parameter hmbz_bezel_inner_edge_thickness		"[BEZEL]  Inner Edge Thickness" 0.5 0 5 0.1
#pragma parameter hmbz_bezel_brightness 				"[BEZEL]  Brightness" 60 0 300 2
#pragma parameter hmbz_bezel_highlight 					"[BEZEL]  Highlight" 2 0 100 0.2
#pragma parameter hmbz_bezel_noise 						"[BEZEL]  Noise" 30 0 100 1

// Frame
#pragma parameter hmbz_frame_opacity 					"[FRAME]   Opacity" 1 0 1 0.05
#pragma parameter hmbz_frame_brightness 				"[FRAME]   Brightness" 100 0 300 2
#pragma parameter hmbz_frame_thickness 					"[FRAME]   Thickness" 8 0 200 0.2
#pragma parameter hmbz_frame_outer_corner_radius 		"[FRAME]   Outer Corner Radius" 5 0 70 0.05
#pragma parameter hmbz_frame_inner_edge_thickness		"[FRAME]   Inner Edge Thickness" 2 0 50 0.05
#pragma parameter hmbz_frame_pos_y_offset 				"[FRAME]   Pos Y Offset" 0 -25 25 0.05
#pragma parameter hmbz_frame_shadow_opacity				"[FRAME SHADOW]   Shadow Opacity" 1 0 3 0.01
#pragma parameter hmbz_frame_shadow_width				"[FRAME SHADOW]   Shadow Width" 10 0 50 0.1

// Reflection Blur
#pragma parameter hbl_blur_num_samples 					"[REFLECTION BLUR]  Num Samples - 0 for OFF" 20 0 40 1
#pragma parameter hbl_blur_min 							"[REFLECTION BLUR]  Min" 	0 0 1 0.01
#pragma parameter hbl_blur_max 							"[REFLECTION BLUR]  Max" 	0.95 0 1 0.01

// Reflection Noise
#pragma parameter hbr_noise_amount 						"[REFLECTION NOISE]   Amount" 0.5 0 1 0.1
#pragma parameter hbr_noise_samples 					"[REFLECTION NOISE]   Samples (0 for OFF)" 1 0 20 1
#pragma parameter hbr_noise_sample_distance 			"[REFLECTION NOISE]   Sample Distance" 0.20 0 1 0.01

// Reflection
#pragma parameter hbr_global_amount 					"[REFLECTION GLOBAL]  Global Amount" 0.4 0 3 0.02
#pragma parameter hbr_global_gamma_adjust 				"[REFLECTION GLOBAL]  Global Gamma Adjust" 1.2 0.25 3 0.05

#pragma parameter hbr_inner_edge_reflection 			"[REFLECTION AMOUNT]  Inner Edge" 0.7 0 3 0.02
#pragma parameter hbr_direct_reflection 				"[REFLECTION AMOUNT]  Direct Reflection" 1 0 3 0.02
#pragma parameter hbr_diffused_reflection 				"[REFLECTION AMOUNT]  Diffused Reflection" 0.5 0 3 0.02
#pragma parameter hbr_fullscreen_glow 					"[REFLECTION AMOUNT]  FullScreen Glow" 75 0 600 0.5
#pragma parameter hbr_fullscreen_glow_gamma 			"[REFLECTION AMOUNT]  FullScreen Glow Gamma" 3 0 5 0.02

#pragma parameter hbr_fade_amount 						"[REFLECTION FADE]  Fade Amount" 1 0 1 0.05
#pragma parameter hbr_radial_fade_width 				"[REFLECTION FADE]  Radial Fade Width" 70 0 300 1
#pragma parameter hbr_radial_fade_height 				"[REFLECTION FADE]  Radial Fade Height" 100 0 300 1
#pragma parameter hbr_lateral_outer_fade_position 		"[REFLECTION FADE]  Lateral Outer Fade Position" -18 -100 100 0.5
#pragma parameter hbr_lateral_outer_fade_distance 		"[REFLECTION FADE]  Lateral Outer Fade Distance" 20 1 50 0.5

#pragma parameter hbr_corner_fade 						"[REFLECTION CORNER FADE]  Corner Fade" 10 1 100 0.5
#pragma parameter hbr_corner_fade_distance 				"[REFLECTION CORNER FADE]  Corner Fade Distance" 100 1 100 1
#pragma parameter hbr_corner_inner_spread 	            "[REFLECTION CORNER FADE]  Corner Inner Spread" 100 0 500 10
#pragma parameter hbr_corner_outer_spread 	            "[REFLECTION CORNER FADE]  Corner Outer Spread" 100 0 500 10
#pragma parameter hbr_corner_spread_falloff             "[REFLECTION CORNER FADE]  Corner Spread Falloff"  50 1 200 1
