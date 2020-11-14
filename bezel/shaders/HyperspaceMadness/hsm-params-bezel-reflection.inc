//---------------------------------------------------------------------------------------------------
//    BEZEL
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//    GENERATED BEZEL & FRAME
//---------------------------------------------------------------------------------------------------
// #pragma parameter HSM_BZL_TITLE "-----[ GENERATED BEZEL & FRAME ]-------------------------------" 0 0 0 1

#pragma parameter HSM_BZL_OPACITY                     "[ BEZEL ]  Opacity" 100 0 100 5
float HSM_BZL_OPACITY = global.HSM_BZL_OPACITY / 100;

#pragma parameter HSM_BZL_BLEND_MODE                  "[ BEZEL ]  Blend Mode - Off | Normal | Add | Mult"  1 0 3 1
float HSM_BZL_BLEND_MODE = global.HSM_BZL_BLEND_MODE;

#pragma parameter HSM_BZL_WIDTH 						"[ BEZEL ]  Width - Def 7.5" 7.5 -10 200 0.1
float HSM_BZL_WIDTH = global.HSM_BZL_WIDTH / 100;

#pragma parameter HSM_BZL_HEIGHT 					    "[ BEZEL ]  Height - Def 6" 6 -10 200 0.1
float HSM_BZL_HEIGHT = global.HSM_BZL_HEIGHT;

#pragma parameter HSM_BZL_INNER_EDGE_THICKNESS		"[ BEZEL ]  Inner Edge Thickness - Def 0.7" 0.7 0 5 0.1
float HSM_BZL_INNER_EDGE_THICKNESS = global.HSM_BZL_INNER_EDGE_THICKNESS  / 100;

#pragma parameter HSM_BZL_INNER_CORNER_RADIUS_SCALE	"[ BEZEL ]  Inner Corner Radius Scale - Def 0.5" 0.5 0 10 0.1
float HSM_BZL_INNER_CORNER_RADIUS_SCALE = global.HSM_BZL_INNER_CORNER_RADIUS_SCALE;

#pragma parameter HSM_BZL_OUTER_CORNER_RADIUS_SCALE 	"[ BEZEL ]  Outer Corner Radius Scale - Def 1" 1 0 10 0.1
float HSM_BZL_OUTER_CORNER_RADIUS_SCALE = global.HSM_BZL_OUTER_CORNER_RADIUS_SCALE;

#pragma parameter HSM_BZL_OUTER_CURVATURE_SCALE 		"[ BEZEL ]   Outer Curvature Scale" 0 0 5 0.05
float HSM_BZL_OUTER_CURVATURE_SCALE = global.HSM_BZL_OUTER_CURVATURE_SCALE;

#pragma parameter HSM_BZL_OUTER_POSITION_Y 			"[ BEZEL ]   Outer Edge Position Y" 0 -25 25 0.05
float HSM_BZL_OUTER_POSITION_Y = global.HSM_BZL_OUTER_POSITION_Y;

#pragma parameter HSM_BZL_BRIGHTNESS 				    "[ BEZEL ]  Brightness - Def 30" 30 0 300 2
float HSM_BZL_BRIGHTNESS = global.HSM_BZL_BRIGHTNESS;

#pragma parameter HSM_BZL_HIGHLIGHT 					"[ BEZEL ]  Highlight" 1 0 100 0.2
float HSM_BZL_HIGHLIGHT = global.HSM_BZL_HIGHLIGHT;

#pragma parameter HSM_BZL_INNER_EDGE_SHADOW        "[ BEZEL ]  Opacity of Shadow from Bezel on Tube" 70 0 200 5
float HSM_BZL_INNER_EDGE_SHADOW = global.HSM_BZL_INNER_EDGE_SHADOW / 100;


//---------------------------------------------------------------------------------------------------
// Bezel & Frame Color
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BEZEL_FRAME_COLOR_TITLE			"_____[ BEZEL & FRAME COLOR ]___________________________________" 0 0 0 0

#pragma parameter HSM_BZL_COLOR_HUE					"[ BEZEL & FRAME COLOR ]  Color Hue" 0 0 360 1
float HSM_BZL_COLOR_HUE = global.HSM_BZL_COLOR_HUE / 360;

#pragma parameter HSM_BZL_COLOR_SATURATION			"[ BEZEL & FRAME COLOR ]  Color Saturation" 0 0 100 1
float HSM_BZL_COLOR_SATURATION = global.HSM_BZL_COLOR_SATURATION / 100;

#pragma parameter HSM_BZL_COLOR_VALUE				    "[ BEZEL & FRAME COLOR ]  Color Value/Brightness - Def 10" 10 0 100 0.2
float HSM_BZL_COLOR_VALUE = global.HSM_BZL_COLOR_VALUE / 100;

#pragma parameter HSM_BZL_COLOR_BLEND_WITH_IMAGE		"[ BEZEL & FRAME COLOR ]  Blend Color with Image" 0 0 1 0.05
float HSM_BZL_COLOR_BLEND_WITH_IMAGE = global.HSM_BZL_COLOR_BLEND_WITH_IMAGE;

#pragma parameter HSM_BZL_NOISE 						"[ BEZEL & FRAME COLOR ]  Noise - Def 30" 30 0 100 1
float HSM_BZL_NOISE = global.HSM_BZL_NOISE / 100;


//---------------------------------------------------------------------------------------------------
//    FRAME
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_FRAME_TITLE			"_____[ FRAME ]_________________________________________________" 0 0 0 0

#pragma parameter HSM_FRM_OPACITY                     "[ FRAME ]  Opacity" 100 0 100 5
float HSM_FRM_OPACITY = global.HSM_FRM_OPACITY / 100;

#pragma parameter HSM_FRM_BLEND_MODE                  "[ FRAME ]  Blend Mode - Off | Normal | Add | Mult"  1 0 3 1
float HSM_FRM_BLEND_MODE = global.HSM_FRM_BLEND_MODE;

#pragma parameter HSM_FRM_THICKNESS 					"[ FRAME ]  Thickness" 7 0 200 0.2
float HSM_FRM_THICKNESS = global.HSM_FRM_THICKNESS / 100;

#pragma parameter HSM_FRM_INNER_EDGE_THICKNESS 		"[ FRAME ]  Inner Edge Thickness" 1 0 50 0.05
float HSM_FRM_INNER_EDGE_THICKNESS = global.HSM_FRM_INNER_EDGE_THICKNESS / 1000;

#pragma parameter HSM_FRM_INNER_CORNER_RADIUS_SCALE 	"[ FRAME ]  Inner Corner Radius Scale" 1 0 50 0.05
float HSM_FRM_INNER_CORNER_RADIUS_SCALE = global.HSM_FRM_INNER_CORNER_RADIUS_SCALE;

#pragma parameter HSM_FRM_OUTER_CURVATURE_SCALE 		"[ FRAME ]  Outer Curvature Scale" 0 0 5 0.05
float HSM_FRM_OUTER_CURVATURE_SCALE = global.HSM_FRM_OUTER_CURVATURE_SCALE;

#pragma parameter HSM_FRM_OUTER_CORNER_RADIUS 		"[ FRAME ]  Outer Corner Radius" 5 0 70 0.05
float HSM_FRM_OUTER_CORNER_RADIUS = global.HSM_FRM_OUTER_CORNER_RADIUS;

#pragma parameter HSM_FRM_OUTER_EDGE_THICKNESS 		"[ FRAME ]  Outer Edge Thickness" 1 0 100 0.1
float HSM_FRM_OUTER_EDGE_THICKNESS = global.HSM_FRM_OUTER_EDGE_THICKNESS;

#pragma parameter HSM_FRM_OUTER_EDGE_SHADING 		    "[ FRAME ]  Outer Edge Shading" 0.5 0 1 0.05
float HSM_FRM_OUTER_EDGE_SHADING = global.HSM_FRM_OUTER_EDGE_SHADING;

#pragma parameter HSM_FRM_SHADOW_OPACITY	            "[ FRAME ]  Shadow Opacity" 1 0 3 0.01
float HSM_FRM_SHADOW_OPACITY = global.HSM_FRM_SHADOW_OPACITY;

#pragma parameter HSM_FRM_SHADOW_WIDTH                "[ FRAME ]  Shadow Width" 10 0 50 0.1
float HSM_FRM_SHADOW_WIDTH = global.HSM_FRM_SHADOW_WIDTH;


//---------------------------------------------------------------------------------------------------
//    REFLECTION
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_REFLECTION_TITLE			"_____[ REFLECTION ]____________________________________________" 0 0 0 0

#pragma parameter HSM_REFLECT_BLEND_MODE             "[ REFLECTION ]  Blend Mode -  Off | Normal | Add"  2 0 2 1
float HSM_REFLECT_BLEND_MODE = global.HSM_REFLECT_BLEND_MODE;

#pragma parameter HSM_REFLECT_MASK_MODE              "[ REFLECTN] Mask- ALL | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG"   3 0 7 1
float HSM_REFLECT_MASK_MODE = global.HSM_REFLECT_MASK_MODE;

#pragma parameter HSM_REFLECT_GLOBAL_AMOUNT 					  "[ REFLECTION ]  Global Amount" 0.4 0 3 0.02
float HSM_REFLECT_GLOBAL_AMOUNT = global.HSM_REFLECT_GLOBAL_AMOUNT;

#pragma parameter HSM_REFLECT_GLOBAL_GAMMA_ADJUST 			"[ REFLECTION ]  Global Gamma Adjust" 1.2 0.25 3 0.05
float HSM_REFLECT_GLOBAL_GAMMA_ADJUST = global.HSM_REFLECT_GLOBAL_GAMMA_ADJUST;

#pragma parameter HSM_REFLECT_INNER_EDGE_AMOUNT 			"[ REFLECTION ]  Inner Edge Amount" 0.9 0 3 0.02
float HSM_REFLECT_INNER_EDGE_AMOUNT = global.HSM_REFLECT_INNER_EDGE_AMOUNT;

#pragma parameter HSM_REFLECT_INNER_EDGE_FULLSCREEN_GLOW 		"[ REFLECTION ]  Inner Edge Fullscreen Glow" 0.4 0 10 0.02
float HSM_REFLECT_INNER_EDGE_FULLSCREEN_GLOW = global.HSM_REFLECT_INNER_EDGE_FULLSCREEN_GLOW;

#pragma parameter HSM_REFLECT_DIRECT_AMOUNT 				"[ REFLECTION ]  Direct Reflection" 1.5 0 3 0.02
float HSM_REFLECT_DIRECT_AMOUNT = global.HSM_REFLECT_DIRECT_AMOUNT;

#pragma parameter HSM_REFLECT_DIFFUSED_AMOUNT 				"[ REFLECTION ]  Diffused Reflection" 0.5 0 3 0.02
float HSM_REFLECT_DIFFUSED_AMOUNT = global.HSM_REFLECT_DIFFUSED_AMOUNT;

#pragma parameter HSM_REFLECT_FULLSCREEN_GLOW 					"[ REFLECTION ]  FullScreen Glow" 75 0 600 0.5
float HSM_REFLECT_FULLSCREEN_GLOW = global.HSM_REFLECT_FULLSCREEN_GLOW;

#pragma parameter HSM_REFLECT_FULLSCREEN_GLOW_GAMMA 			"[ REFLECTION ]  FullScreen Glow Gamma" 3 0 5 0.02
float HSM_REFLECT_FULLSCREEN_GLOW_GAMMA = global.HSM_REFLECT_FULLSCREEN_GLOW_GAMMA;


//---------------------------------------------------------------------------------------------------
// Reflection Fading
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_REFLECTION_FADE_TITLE			"_____[ REFLECTION FADE ]_______________________________________" 0 0 0 0

#pragma parameter HSM_REFLECT_FADE_AMOUNT 					"[ REFLECTION FADE ]  Fade Amount" 1 0 1 0.05
float HSM_REFLECT_FADE_AMOUNT = global.HSM_REFLECT_FADE_AMOUNT;

#pragma parameter HSM_REFLECT_RADIAL_FADE_WIDTH 				"[ REFLECTION FADE ]  Radial Fade Width" 100 0 1000 1
float HSM_REFLECT_RADIAL_FADE_WIDTH = global.HSM_REFLECT_RADIAL_FADE_WIDTH;

#pragma parameter HSM_REFLECT_RADIAL_FADE_HEIGHT 				"[ REFLECTION FADE ]  Radial Fade Height" 100 0 1000 1
float HSM_REFLECT_RADIAL_FADE_HEIGHT = global.HSM_REFLECT_RADIAL_FADE_HEIGHT;

#pragma parameter HSM_REFLECT_LATERAL_OUTER_FADE_POSITION 		"[ REFLECTION FADE ]  Lateral Outer Fade Position" -18 -500 500 0.5
float HSM_REFLECT_LATERAL_OUTER_FADE_POSITION = global.HSM_REFLECT_LATERAL_OUTER_FADE_POSITION;

#pragma parameter HSM_REFLECT_LATERAL_OUTER_FADE_DISTANCE 		"[ REFLECTION FADE ]  Lateral Outer Fade Distance" 20 1 400 0.5
float HSM_REFLECT_LATERAL_OUTER_FADE_DISTANCE = global.HSM_REFLECT_LATERAL_OUTER_FADE_DISTANCE;


#pragma parameter HSM_REFLECT_CORNER_TITLE			"_____[ REFLECTION CORNER ]_____________________________________" 0 0 0 0

#pragma parameter HSM_REFLECT_CORNER_FADE 						"[ REFLECTION CORNER FADE ]  Corner Fade" 10 1 100 0.5
float HSM_REFLECT_CORNER_FADE = global.HSM_REFLECT_CORNER_FADE;

#pragma parameter HSM_REFLECT_CORNER_FADE_DISTANCE 				"[ REFLECTION CORNER FADE ]  Corner Fade Distance" 100 1 100 1
float HSM_REFLECT_CORNER_FADE_DISTANCE = global.HSM_REFLECT_CORNER_FADE_DISTANCE;

#pragma parameter HSM_REFLECT_CORNER_INNER_SPREAD 	            "[ REFLECTION CORNER FADE ]  Corner Inner Spread" 500 0 1000 10
float HSM_REFLECT_CORNER_INNER_SPREAD = global.HSM_REFLECT_CORNER_INNER_SPREAD;

#pragma parameter HSM_REFLECT_CORNER_OUTER_SPREAD 	            "[ REFLECTION CORNER FADE ]  Corner Outer Spread" 160 0 1000 10
float HSM_REFLECT_CORNER_OUTER_SPREAD = global.HSM_REFLECT_CORNER_OUTER_SPREAD;

#pragma parameter HSM_REFLECT_CORNER_ROTATION_OFFSET_TOP 	    "[ REFLECTION CORNER ROTATION ]  Offset Top" 0 -90 90 0.5
float HSM_REFLECT_CORNER_ROTATION_OFFSET_TOP = global.HSM_REFLECT_CORNER_ROTATION_OFFSET_TOP;

#pragma parameter HSM_REFLECT_CORNER_ROTATION_OFFSET_BOTTOM 	"[ REFLECTION CORNER ROTATION ]  Offset Bottom" 0 -90 90 0.5
float HSM_REFLECT_CORNER_ROTATION_OFFSET_BOTTOM = global.HSM_REFLECT_CORNER_ROTATION_OFFSET_BOTTOM;

// #pragma parameter HSM_REFLECT_CORNER_SPREAD_FALLOFF             "[ REFLECTION CORNER FADE ]  Corner Spread Falloff"  50 1 200 1
// float HSM_REFLECT_CORNER_SPREAD_FALLOFF = global.HSM_REFLECT_CORNER_SPREAD_FALLOFF;

//---------------------------------------------------------------------------------------------------
// Reflection Blur
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_REFLECT_BLUR_TITLE			        "_____[ REFLECTION BLUR & NOISE ]_______________________________" 0 0 0 0

#pragma parameter HSM_REFLECT_BLUR_NUM_SAMPLES 					"[ REFLECTION BLUR ]  Num Samples - 0 for OFF" 12 0 40 1
float HSM_REFLECT_BLUR_NUM_SAMPLES = global.HSM_REFLECT_BLUR_NUM_SAMPLES;

#pragma parameter HSM_REFLECT_BLUR_MIN 							"[ REFLECTION BLUR ]  Min" 	0 0 1 0.01
float HSM_REFLECT_BLUR_MIN = global.HSM_REFLECT_BLUR_MIN;

#pragma parameter HSM_REFLECT_BLUR_MAX 							"[ REFLECTION BLUR ]  Max" 	0.95 0 1 0.01
float HSM_REFLECT_BLUR_MAX = global.HSM_REFLECT_BLUR_MAX;

// Reflection Noise
#pragma parameter HSM_REFLECT_NOISE_AMOUNT 						"[ REFLECTION NOISE ]   Amount" 0.5 0 1 0.1
float HSM_REFLECT_NOISE_AMOUNT = global.HSM_REFLECT_NOISE_AMOUNT;

#pragma parameter HSM_REFLECT_NOISE_SAMPLES 					    "[ REFLECTION NOISE ]   Samples (0 for OFF)" 1 0 20 1
float HSM_REFLECT_NOISE_SAMPLES = global.HSM_REFLECT_NOISE_SAMPLES;

#pragma parameter HSM_REFLECT_NOISE_SAMPLE_DISTANCE 			"[ REFLECTION NOISE ]   Sample Distance" 0.20 0 1 0.01
float HSM_REFLECT_NOISE_SAMPLE_DISTANCE = global.HSM_REFLECT_NOISE_SAMPLE_DISTANCE;


//---------------------------------------------------------------------------------------------------
// Reflection Is Last Pass
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_REFLECT_IS_LAST_PASS "[ REFLECTION IS LAST PASS] Glass and Reflect Only Presets" 0 0 1 1
float HSM_REFLECT_IS_LAST_PASS = global.HSM_REFLECT_IS_LAST_PASS;


/////////////// CONSTANT TUNING SETTINGS ///////////////

#ifndef HSM_REFLECT_CORNER_SPREAD_FALLOFF
    #define HSM_REFLECT_CORNER_SPREAD_FALLOFF 100
#endif

#ifndef HSM_GLASS_INNER_EDGE_SOFTNESS
    #define HSM_GLASS_INNER_EDGE_SOFTNESS 0.3
#endif