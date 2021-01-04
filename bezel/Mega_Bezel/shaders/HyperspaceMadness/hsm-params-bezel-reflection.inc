//---------------------------------------------------------------------------------------------------
//    BEZEL
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//    GENERATED BEZEL & FRAME
//---------------------------------------------------------------------------------------------------
// #pragma parameter HSM_BZL_TITLE "-----[ GENERATED BEZEL & FRAME ]-------------------------------" 0 0 0 1

#pragma parameter HSM_BZL_OPACITY                       "      Opacity" 100 0 100 5
float HSM_BZL_OPACITY = global.HSM_BZL_OPACITY / 100;

#pragma parameter HSM_BZL_BLEND_MODE                    "      Blend Mode - Off | Normal | Add | Mult"  1 0 3 1
float HSM_BZL_BLEND_MODE = global.HSM_BZL_BLEND_MODE;

#pragma parameter HSM_BZL_WIDTH 						"      Width - Def 7.5" 7.5 -10 200 0.1
float HSM_BZL_WIDTH = global.HSM_BZL_WIDTH / 100;

#pragma parameter HSM_BZL_HEIGHT 					    "      Height - Def 6" 6 -10 200 0.1
float HSM_BZL_HEIGHT = global.HSM_BZL_HEIGHT;

#pragma parameter HSM_BZL_INNER_EDGE_THICKNESS		    "      Inner Edge Thickness - Def 0.7" 0.7 0 5 0.1
float HSM_BZL_INNER_EDGE_THICKNESS = global.HSM_BZL_INNER_EDGE_THICKNESS  / 100;

#pragma parameter HSM_BZL_INNER_CORNER_RADIUS_SCALE	    "      Inner Corner Radius Scale - Def 0.5" 0.5 0 10 0.1
float HSM_BZL_INNER_CORNER_RADIUS_SCALE = global.HSM_BZL_INNER_CORNER_RADIUS_SCALE;

#pragma parameter HSM_BZL_OUTER_CORNER_RADIUS_SCALE 	"      Outer Corner Radius Scale - Def 1" 1 0 10 0.1
float HSM_BZL_OUTER_CORNER_RADIUS_SCALE = global.HSM_BZL_OUTER_CORNER_RADIUS_SCALE;

#pragma parameter HSM_BZL_OUTER_CURVATURE_SCALE 		"      Outer Curvature Scale" 0 0 5 0.05
float HSM_BZL_OUTER_CURVATURE_SCALE = global.HSM_BZL_OUTER_CURVATURE_SCALE;

#pragma parameter HSM_BZL_OUTER_POSITION_Y 			    "      Outer Edge Position Y" 0 -25 25 0.05
float HSM_BZL_OUTER_POSITION_Y = global.HSM_BZL_OUTER_POSITION_Y;

#pragma parameter HSM_BZL_BRIGHTNESS 				    "      Brightness - Def 30" 30 0 300 2
float HSM_BZL_BRIGHTNESS = global.HSM_BZL_BRIGHTNESS;

#pragma parameter HSM_BZL_HIGHLIGHT 					"      Highlight" 1 0 100 0.2
float HSM_BZL_HIGHLIGHT = global.HSM_BZL_HIGHLIGHT;

#pragma parameter HSM_BZL_INNER_EDGE_SHADOW             "      Opacity of Shadow from Bezel on Tube" 70 0 200 5
float HSM_BZL_INNER_EDGE_SHADOW = global.HSM_BZL_INNER_EDGE_SHADOW / 100;


//---------------------------------------------------------------------------------------------------
// Bezel & Frame Color
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BEZEL_FRAME_COLOR_TITLE		"[ BEZEL & FRAME COLOR ]________________________________________" 0 0 1 1

#pragma parameter HSM_BZL_COLOR_HUE					"      Hue" 0 0 360 1
float HSM_BZL_COLOR_HUE = global.HSM_BZL_COLOR_HUE / 360;

#pragma parameter HSM_BZL_COLOR_SATURATION			"      Saturation" 0 0 100 1
float HSM_BZL_COLOR_SATURATION = global.HSM_BZL_COLOR_SATURATION / 100;

#pragma parameter HSM_BZL_COLOR_VALUE				"      Value/Brightness - Def 10" 10 0 100 0.2
float HSM_BZL_COLOR_VALUE = global.HSM_BZL_COLOR_VALUE / 100;

#pragma parameter HSM_BZL_NOISE 					"      Noise - Def 30" 30 0 100 1
float HSM_BZL_NOISE = global.HSM_BZL_NOISE / 100;


//---------------------------------------------------------------------------------------------------
//    FRAME
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_FRAME_TITLE			            "[ FRAME ]______________________________________________________" 0 0 1 1

#pragma parameter HSM_FRM_OPACITY                       "      Opacity" 100 0 100 5
float HSM_FRM_OPACITY = global.HSM_FRM_OPACITY / 100;

#pragma parameter HSM_FRM_BLEND_MODE                    "      Blend Mode - Off | Normal | Add | Mult"  1 0 3 1
float HSM_FRM_BLEND_MODE = global.HSM_FRM_BLEND_MODE;

#pragma parameter HSM_FRM_TEXTURE_OPACITY               "      Texture Overlay Opacity (Highlight)" 1.5 0 100 0.1
float HSM_FRM_TEXTURE_OPACITY = global.HSM_FRM_TEXTURE_OPACITY / 100;

#pragma parameter HSM_FRM_TEXTURE_BLEND_MODE            "      Texture Overlay Blend Mode - Off | Normal | Add | Mult"  2 0 3 1
float HSM_FRM_TEXTURE_BLEND_MODE = global.HSM_FRM_TEXTURE_BLEND_MODE;

#pragma parameter HSM_FRM_INNER_EDGE_THICKNESS 		    "      Inner Edge Thickness" 1 0 50 0.05
float HSM_FRM_INNER_EDGE_THICKNESS = global.HSM_FRM_INNER_EDGE_THICKNESS / 1000;

#pragma parameter HSM_FRM_INNER_CORNER_RADIUS_SCALE 	"      Inner Corner Radius Scale" 1 0 50 0.05
float HSM_FRM_INNER_CORNER_RADIUS_SCALE = global.HSM_FRM_INNER_CORNER_RADIUS_SCALE;

#pragma parameter HSM_FRM_THICKNESS 					"      Thickness" 7 0 200 0.2
float HSM_FRM_THICKNESS = global.HSM_FRM_THICKNESS / 100;

#pragma parameter HSM_FRM_THICKNESS_SCALE_X 			"      Thickness Scale X" 100 0 1000 2
float HSM_FRM_THICKNESS_SCALE_X = global.HSM_FRM_THICKNESS_SCALE_X / 100;

#pragma parameter HSM_FRM_OUTER_POS_Y 			        "      Outer Pos Y" 0 -100 100 0.05
float HSM_FRM_OUTER_POS_Y = global.HSM_FRM_OUTER_POS_Y / 100;

#pragma parameter HSM_FRM_OUTER_CURVATURE_SCALE 		"      Outer Curvature Scale" 0 0 5 0.05
float HSM_FRM_OUTER_CURVATURE_SCALE = global.HSM_FRM_OUTER_CURVATURE_SCALE;

#pragma parameter HSM_FRM_OUTER_CORNER_RADIUS 		    "      Outer Corner Radius" 5 0 70 0.05
float HSM_FRM_OUTER_CORNER_RADIUS = global.HSM_FRM_OUTER_CORNER_RADIUS;

#pragma parameter HSM_FRM_OUTER_EDGE_THICKNESS 		    "      Outer Edge Thickness" 1 0 100 0.1
float HSM_FRM_OUTER_EDGE_THICKNESS = global.HSM_FRM_OUTER_EDGE_THICKNESS;

#pragma parameter HSM_FRM_OUTER_EDGE_SHADING 		    "      Outer Edge Shading" 0.5 0 1 0.05
float HSM_FRM_OUTER_EDGE_SHADING = global.HSM_FRM_OUTER_EDGE_SHADING;

#pragma parameter HSM_FRM_SHADOW_OPACITY	            "      Shadow Opacity" 1 0 3 0.01
float HSM_FRM_SHADOW_OPACITY = global.HSM_FRM_SHADOW_OPACITY;

#pragma parameter HSM_FRM_SHADOW_WIDTH                  "      Shadow Width" 10 0 50 0.1
float HSM_FRM_SHADOW_WIDTH = global.HSM_FRM_SHADOW_WIDTH;



//---------------------------------------------------------------------------------------------------
//    REFLECTION
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_REFLECTION_TITLE			            "[ REFLECTION ]_________________________________________________" 0 0 1 1

#pragma parameter HSM_REFLECT_BLEND_MODE                    "      Blend Mode -  Off | Normal | Add"  2 0 2 1
float HSM_REFLECT_BLEND_MODE = global.HSM_REFLECT_BLEND_MODE;

#pragma parameter HSM_REFLECT_MASK_MODE                     "  Mask - ALL | Screen | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG"   4 0 8 1
float HSM_REFLECT_MASK_MODE = global.HSM_REFLECT_MASK_MODE;

#pragma parameter HSM_REFLECT_GLOBAL_AMOUNT 				"      Global Amount" 0.4 0 3 0.02
float HSM_REFLECT_GLOBAL_AMOUNT = global.HSM_REFLECT_GLOBAL_AMOUNT;

#pragma parameter HSM_REFLECT_GLOBAL_GAMMA_ADJUST 			"      Global Gamma Adjust" 1.2 0.25 3 0.05
float HSM_REFLECT_GLOBAL_GAMMA_ADJUST = global.HSM_REFLECT_GLOBAL_GAMMA_ADJUST;

#pragma parameter HSM_REFLECT_INNER_EDGE_AMOUNT 			"      Inner Edge Amount" 0.9 0 3 0.02
float HSM_REFLECT_INNER_EDGE_AMOUNT = global.HSM_REFLECT_INNER_EDGE_AMOUNT;

#pragma parameter HSM_REFLECT_INNER_EDGE_FULLSCREEN_GLOW 	"      Inner Edge Fullscreen Glow" 0.4 0 10 0.02
float HSM_REFLECT_INNER_EDGE_FULLSCREEN_GLOW = global.HSM_REFLECT_INNER_EDGE_FULLSCREEN_GLOW;

#pragma parameter HSM_REFLECT_DIRECT_AMOUNT 				"      Direct Reflection" 1.5 0 3 0.02
float HSM_REFLECT_DIRECT_AMOUNT = global.HSM_REFLECT_DIRECT_AMOUNT;

#pragma parameter HSM_REFLECT_DIFFUSED_AMOUNT 				"      Diffused Reflection" 0.5 0 3 0.02
float HSM_REFLECT_DIFFUSED_AMOUNT = global.HSM_REFLECT_DIFFUSED_AMOUNT;

#pragma parameter HSM_REFLECT_FULLSCREEN_GLOW 				"      FullScreen Glow" 75 0 600 0.5
float HSM_REFLECT_FULLSCREEN_GLOW = global.HSM_REFLECT_FULLSCREEN_GLOW;

#pragma parameter HSM_REFLECT_FULLSCREEN_GLOW_GAMMA 		"      FullScreen Glow Gamma" 3 0 5 0.02
float HSM_REFLECT_FULLSCREEN_GLOW_GAMMA = global.HSM_REFLECT_FULLSCREEN_GLOW_GAMMA;


//---------------------------------------------------------------------------------------------------
// Reflection Fading
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_REFLECTION_FADE_TITLE			            "[ REFLECTION FADE ]____________________________________________" 0 0 1 1

#pragma parameter HSM_REFLECT_FADE_AMOUNT 					    "      Fade Amount" 1 0 1 0.05
float HSM_REFLECT_FADE_AMOUNT = global.HSM_REFLECT_FADE_AMOUNT;

#pragma parameter HSM_REFLECT_RADIAL_FADE_WIDTH 			    "      Radial Fade Width" 100 0 1000 1
float HSM_REFLECT_RADIAL_FADE_WIDTH = global.HSM_REFLECT_RADIAL_FADE_WIDTH;

#pragma parameter HSM_REFLECT_RADIAL_FADE_HEIGHT 				"      Radial Fade Height" 100 0 1000 1
float HSM_REFLECT_RADIAL_FADE_HEIGHT = global.HSM_REFLECT_RADIAL_FADE_HEIGHT;

#pragma parameter HSM_REFLECT_LATERAL_OUTER_FADE_POSITION 		"      Lateral Outer Fade Position" -18 -500 500 0.5
float HSM_REFLECT_LATERAL_OUTER_FADE_POSITION = global.HSM_REFLECT_LATERAL_OUTER_FADE_POSITION;

#pragma parameter HSM_REFLECT_LATERAL_OUTER_FADE_DISTANCE 		"      Lateral Outer Fade Distance" 20 1 400 0.5
float HSM_REFLECT_LATERAL_OUTER_FADE_DISTANCE = global.HSM_REFLECT_LATERAL_OUTER_FADE_DISTANCE;

#pragma parameter HSM_REFLECT_VIGNETTE_AMOUNT 		            "      Viewport Vignette (For Glass Presets)" 0 0 100 0.5
float HSM_REFLECT_VIGNETTE_AMOUNT = global.HSM_REFLECT_VIGNETTE_AMOUNT / 100;


#pragma parameter HSM_REFLECT_CORNER_TITLE			            "[ REFLECTION CORNER ]__________________________________________" 0 0 1 1

#pragma parameter HSM_REFLECT_CORNER_FADE 						"      Corner Fade" 10 1 100 0.5
float HSM_REFLECT_CORNER_FADE = global.HSM_REFLECT_CORNER_FADE;

#pragma parameter HSM_REFLECT_CORNER_FADE_DISTANCE 				"      Corner Fade Distance" 100 1 100 1
float HSM_REFLECT_CORNER_FADE_DISTANCE = global.HSM_REFLECT_CORNER_FADE_DISTANCE;

#pragma parameter HSM_REFLECT_CORNER_INNER_SPREAD 	            "      Corner Inner Spread" 500 0 1000 10
float HSM_REFLECT_CORNER_INNER_SPREAD = global.HSM_REFLECT_CORNER_INNER_SPREAD;

#pragma parameter HSM_REFLECT_CORNER_OUTER_SPREAD 	            "      Corner Outer Spread" 160 0 1000 10
float HSM_REFLECT_CORNER_OUTER_SPREAD = global.HSM_REFLECT_CORNER_OUTER_SPREAD;

#pragma parameter HSM_REFLECT_CORNER_ROTATION_OFFSET_TOP 	    "      Corner Rotation Offset Top" 0 -90 90 0.5
float HSM_REFLECT_CORNER_ROTATION_OFFSET_TOP = global.HSM_REFLECT_CORNER_ROTATION_OFFSET_TOP;

#pragma parameter HSM_REFLECT_CORNER_ROTATION_OFFSET_BOTTOM 	"      Corner Rotation Offset Bottom" 0 -90 90 0.5
float HSM_REFLECT_CORNER_ROTATION_OFFSET_BOTTOM = global.HSM_REFLECT_CORNER_ROTATION_OFFSET_BOTTOM;

// #pragma parameter HSM_REFLECT_CORNER_SPREAD_FALLOFF             "      Corner Spread Falloff"  50 1 200 1
// float HSM_REFLECT_CORNER_SPREAD_FALLOFF = global.HSM_REFLECT_CORNER_SPREAD_FALLOFF;

//---------------------------------------------------------------------------------------------------
// Reflection Blur
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_REFLECT_BLUR_TITLE			                "[ REFLECTION BLUR ]____________________________________________" 0 0 1 1

#pragma parameter HSM_REFLECT_BLUR_NUM_SAMPLES 					    "      Blur Samples - 0 for OFF" 12 0 40 1
float HSM_REFLECT_BLUR_NUM_SAMPLES = global.HSM_REFLECT_BLUR_NUM_SAMPLES;

#pragma parameter HSM_REFLECT_BLUR_MIN 							    "      Min Blur" 	0 0 1 0.01
float HSM_REFLECT_BLUR_MIN = global.HSM_REFLECT_BLUR_MIN;

#pragma parameter HSM_REFLECT_BLUR_MAX 							    "      Max Blur" 	0.95 0 1 0.01
float HSM_REFLECT_BLUR_MAX = global.HSM_REFLECT_BLUR_MAX;

// Reflection Noise
#pragma parameter HSM_REFLECT_NOISE_TITLE			                "[ REFLECTION NOISE ]___________________________________________" 0 0 1 1

#pragma parameter HSM_REFLECT_NOISE_AMOUNT 						    "      Noise Amount" 0.5 0 1 0.1
float HSM_REFLECT_NOISE_AMOUNT = global.HSM_REFLECT_NOISE_AMOUNT;

#pragma parameter HSM_REFLECT_NOISE_SAMPLES 					    "      Noise Samples (0 for OFF)" 1 0 20 1
float HSM_REFLECT_NOISE_SAMPLES = global.HSM_REFLECT_NOISE_SAMPLES;

#pragma parameter HSM_REFLECT_NOISE_SAMPLE_DISTANCE 			    "      Sample Distance" 0.20 0 1 0.01
float HSM_REFLECT_NOISE_SAMPLE_DISTANCE = global.HSM_REFLECT_NOISE_SAMPLE_DISTANCE;


//---------------------------------------------------------------------------------------------------
//    GLASS BORDER
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_GLASS_BORDER_TITLE			        "[ GLASS BORDER ]_______________________________________________" 0 0 1 1

#pragma parameter HSM_GLASS_BORDER_ON                       "      Glass Border ON (Glass Preset Only)" 0 0 1 1
float HSM_GLASS_BORDER_ON = global.HSM_GLASS_BORDER_ON;


//---------------------------------------------------------------------------------------------------
//    REFLECT ONLY IMAGE LAYER
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_REFLECT_ONLY_IMAGE_TITLE	                    "[ REFLECT ONLY IMAGE LAYER ]___________________________________" 0 0 1 1

#pragma parameter HSM_REFLECT_ONLY_IMG_OPACITY 	                    "      Opacity" 0 0 100 0.1
float HSM_REFLECT_ONLY_IMG_OPACITY = global.HSM_REFLECT_ONLY_IMG_OPACITY / 100;

#pragma parameter HSM_REFLECT_ONLY_IMG_BLEND_MODE 		            "      Blend Mode - Off | Norm | Add | Mult"  2 0 3 1
float HSM_REFLECT_ONLY_IMG_BLEND_MODE = global.HSM_REFLECT_ONLY_IMG_BLEND_MODE;


//---------------------------------------------------------------------------------------------------
// Reflection Is Last Pass
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_REFLECT_LAST_PASS_TITLE			        "[ REFLECTION IS LAST PASS ]____________________________________" 0 0 1 1

#pragma parameter HSM_REFLECT_IS_LAST_PASS "      Reflection is Last Pass (Glass and Reflect Only Presets)" 0 0 1 1
float HSM_REFLECT_IS_LAST_PASS = global.HSM_REFLECT_IS_LAST_PASS;


/////////////// CONSTANT TUNING SETTINGS ///////////////

#ifndef HSM_REFLECT_CORNER_SPREAD_FALLOFF
    #define HSM_REFLECT_CORNER_SPREAD_FALLOFF 100
#endif

#ifndef HSM_GLASS_INNER_EDGE_SOFTNESS
    #define HSM_GLASS_INNER_EDGE_SOFTNESS 0.3
#endif