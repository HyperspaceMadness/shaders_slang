//---------------------------------------------------------------------------------------------------
//    BEZEL
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//    GENERATED BEZEL & FRAME
//---------------------------------------------------------------------------------------------------
// #pragma parameter H_BZL_TITLE "-----[ GENERATED BEZEL & FRAME ]-------------------------------" 0 0 0 1

#pragma parameter H_BZL_OPACITY                     "[ BEZEL ]  Opacity" 100 0 100 5
float H_BZL_OPACITY = global.H_BZL_OPACITY / 100;

#pragma parameter H_BZL_BLEND_MODE                  "[ BEZEL ]  Blend Mode - Off | Normal | Add | Mult"  1 0 3 1
float H_BZL_BLEND_MODE = global.H_BZL_BLEND_MODE;

#pragma parameter H_BZL_WIDTH 						"[ BEZEL ]  Width - Def 7.5" 7.5 -10 200 0.1
float H_BZL_WIDTH = global.H_BZL_WIDTH / 100;

#pragma parameter H_BZL_HEIGHT 					    "[ BEZEL ]  Height - Def 6" 6 -10 200 0.1
float H_BZL_HEIGHT = global.H_BZL_HEIGHT;

#pragma parameter H_BZL_INNER_EDGE_THICKNESS		"[ BEZEL ]  Inner Edge Thickness - Def 0.7" 0.7 0 5 0.1
float H_BZL_INNER_EDGE_THICKNESS = global.H_BZL_INNER_EDGE_THICKNESS  / 100;

#pragma parameter H_BZL_INNER_CORNER_RADIUS_SCALE	"[ BEZEL ]  Inner Corner Radius Scale - Def 0.5" 0.5 0 10 0.1
float H_BZL_INNER_CORNER_RADIUS_SCALE = global.H_BZL_INNER_CORNER_RADIUS_SCALE;

#pragma parameter H_BZL_OUTER_CORNER_RADIUS_SCALE 	"[ BEZEL ]  Outer Corner Radius Scale - Def 1" 1 0 10 0.1
float H_BZL_OUTER_CORNER_RADIUS_SCALE = global.H_BZL_OUTER_CORNER_RADIUS_SCALE;

#pragma parameter H_BZL_OUTER_CURVATURE_SCALE 		"[ BEZEL ]   Outer Curvature Scale" 0 0 5 0.05
float H_BZL_OUTER_CURVATURE_SCALE = global.H_BZL_OUTER_CURVATURE_SCALE;

#pragma parameter H_BZL_OUTER_POSITION_Y 			"[ BEZEL ]   Outer Edge Position Y" 0 -25 25 0.05
float H_BZL_OUTER_POSITION_Y = global.H_BZL_OUTER_POSITION_Y;

#pragma parameter H_BZL_BRIGHTNESS 				    "[ BEZEL ]  Brightness - Def 30" 30 0 300 2
float H_BZL_BRIGHTNESS = global.H_BZL_BRIGHTNESS;

#pragma parameter H_BZL_HIGHLIGHT 					"[ BEZEL ]  Highlight" 1 0 100 0.2
float H_BZL_HIGHLIGHT = global.H_BZL_HIGHLIGHT;

#pragma parameter H_BZL_INNER_EDGE_SHADOW        "[ BEZEL ]  Opacity of Shadow from Bezel on Tube" 70 0 200 5
float H_BZL_INNER_EDGE_SHADOW = global.H_BZL_INNER_EDGE_SHADOW / 100;


//---------------------------------------------------------------------------------------------------
// Bezel & Frame Color
//---------------------------------------------------------------------------------------------------
#pragma parameter H_BEZEL_FRAME_COLOR_TITLE			"_____[ BEZEL & FRAME COLOR ]___________________________________" 0 0 0 0

#pragma parameter H_BZL_COLOR_HUE					"[ BEZEL & FRAME COLOR ]  Color Hue" 0 0 360 1
float H_BZL_COLOR_HUE = global.H_BZL_COLOR_HUE / 360;

#pragma parameter H_BZL_COLOR_SATURATION			"[ BEZEL & FRAME COLOR ]  Color Saturation" 0 0 100 1
float H_BZL_COLOR_SATURATION = global.H_BZL_COLOR_SATURATION / 100;

#pragma parameter H_BZL_COLOR_VALUE				    "[ BEZEL & FRAME COLOR ]  Color Value/Brightness - Def 10" 10 0 100 0.2
float H_BZL_COLOR_VALUE = global.H_BZL_COLOR_VALUE / 100;

#pragma parameter H_BZL_COLOR_BLEND_WITH_IMAGE		"[ BEZEL & FRAME COLOR ]  Blend Color with Image" 0 0 1 0.05
float H_BZL_COLOR_BLEND_WITH_IMAGE = global.H_BZL_COLOR_BLEND_WITH_IMAGE;

#pragma parameter H_BZL_NOISE 						"[ BEZEL & FRAME COLOR ]  Noise - Def 30" 30 0 100 1
float H_BZL_NOISE = global.H_BZL_NOISE / 100;


//---------------------------------------------------------------------------------------------------
//    FRAME
//---------------------------------------------------------------------------------------------------
#pragma parameter H_FRAME_TITLE			"_____[ FRAME ]_________________________________________________" 0 0 0 0

#pragma parameter H_FRM_OPACITY                     "[ FRAME ]  Opacity" 100 0 100 5
float H_FRM_OPACITY = global.H_FRM_OPACITY / 100;

#pragma parameter H_FRM_BLEND_MODE                  "[ FRAME ]  Blend Mode - Off | Normal | Add | Mult"  1 0 3 1
float H_FRM_BLEND_MODE = global.H_FRM_BLEND_MODE;

#pragma parameter H_FRM_THICKNESS 					"[ FRAME ]  Thickness" 7 0 200 0.2
float H_FRM_THICKNESS = global.H_FRM_THICKNESS / 100;

#pragma parameter H_FRM_INNER_EDGE_THICKNESS 		"[ FRAME ]  Inner Edge Thickness" 1 0 50 0.05
float H_FRM_INNER_EDGE_THICKNESS = global.H_FRM_INNER_EDGE_THICKNESS / 1000;

#pragma parameter H_FRM_INNER_CORNER_RADIUS_SCALE 	"[ FRAME ]  Inner Corner Radius Scale" 1 0 50 0.05
float H_FRM_INNER_CORNER_RADIUS_SCALE = global.H_FRM_INNER_CORNER_RADIUS_SCALE;

#pragma parameter HSS_FRAME_OUTER_CURVATURE_SCALE 		"[ FRAME ]  Outer Curvature Scale" 0 0 5 0.05
float HSS_FRAME_OUTER_CURVATURE_SCALE = global.HSS_FRAME_OUTER_CURVATURE_SCALE;

#pragma parameter H_FRM_OUTER_CORNER_RADIUS 		"[ FRAME ]  Outer Corner Radius" 5 0 70 0.05
float H_FRM_OUTER_CORNER_RADIUS = global.H_FRM_OUTER_CORNER_RADIUS;

#pragma parameter H_FRM_OUTER_EDGE_THICKNESS 		"[ FRAME ]  Outer Edge Thickness" 1 0 100 0.1
float H_FRM_OUTER_EDGE_THICKNESS = global.H_FRM_OUTER_EDGE_THICKNESS;

#pragma parameter H_FRM_OUTER_EDGE_SHADING 		    "[ FRAME ]  Outer Edge Shading" 0.5 0 1 0.05
float H_FRM_OUTER_EDGE_SHADING = global.H_FRM_OUTER_EDGE_SHADING;

#pragma parameter H_FRM_SHADOW_OPACITY	            "[ FRAME ]  Shadow Opacity" 1 0 3 0.01
float H_FRM_SHADOW_OPACITY = global.H_FRM_SHADOW_OPACITY;

#pragma parameter H_FRM_SHADOW_WIDTH                "[ FRAME ]  Shadow Width" 10 0 50 0.1
float H_FRM_SHADOW_WIDTH = global.H_FRM_SHADOW_WIDTH;


//---------------------------------------------------------------------------------------------------
//    REFLECTION
//---------------------------------------------------------------------------------------------------
#pragma parameter H_REFLECTION_TITLE			"_____[ REFLECTION ]____________________________________________" 0 0 0 0

#pragma parameter H_REFLECTION_BLEND_MODE             "[ REFLECTION ]  Blend Mode -  Off | Normal | Add"  2 0 2 1
float H_REFLECTION_BLEND_MODE = global.H_REFLECTION_BLEND_MODE;

#pragma parameter H_REFLECTION_MASK_MODE              "[REFLECTN] Mask - ALL | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG"   3 0 7 1
float H_REFLECTION_MASK_MODE = global.H_REFLECTION_MASK_MODE;


#pragma parameter H_REFLECTION_AMOUNT_TITLE			      "_____[ REFLECTION AMOUNT  ]____________________________________" 0 0 0 0

#pragma parameter H_GLOBAL_AMOUNT 					  "[ REFLECTION AMOUNT ]  Global Amount" 0.4 0 3 0.02
float H_GLOBAL_AMOUNT = global.H_GLOBAL_AMOUNT;

#pragma parameter H_GLOBAL_GAMMA_ADJUST 			"[ REFLECTION AMOUNT ]  Global Gamma Adjust" 1.2 0.25 3 0.05
float H_GLOBAL_GAMMA_ADJUST = global.H_GLOBAL_GAMMA_ADJUST;

#pragma parameter H_INNER_EDGE_REFLECTION 			"[ REFLECTION AMOUNT ]  Inner Edge Amount" 0.9 0 3 0.02
float H_INNER_EDGE_REFLECTION = global.H_INNER_EDGE_REFLECTION;

#pragma parameter H_INNER_EDGE_FULLSCREEN_GLOW 		"[ REFLECTION AMOUNT ]  Inner Edge Fullscreen Glow" 0.4 0 10 0.02
float H_INNER_EDGE_FULLSCREEN_GLOW = global.H_INNER_EDGE_FULLSCREEN_GLOW;

#pragma parameter H_DIRECT_REFLECTION 				"[ REFLECTION AMOUNT ]  Direct Reflection" 1.5 0 3 0.02
float H_DIRECT_REFLECTION = global.H_DIRECT_REFLECTION;

#pragma parameter H_DIFFUSED_REFLECTION 				"[ REFLECTION AMOUNT ]  Diffused Reflection" 0.5 0 3 0.02
float H_DIFFUSED_REFLECTION = global.H_DIFFUSED_REFLECTION;

#pragma parameter H_FULLSCREEN_GLOW 					"[ REFLECTION AMOUNT ]  FullScreen Glow" 75 0 600 0.5
float H_FULLSCREEN_GLOW = global.H_FULLSCREEN_GLOW;

#pragma parameter H_FULLSCREEN_GLOW_GAMMA 			"[ REFLECTION AMOUNT ]  FullScreen Glow Gamma" 3 0 5 0.02
float H_FULLSCREEN_GLOW_GAMMA = global.H_FULLSCREEN_GLOW_GAMMA;


//---------------------------------------------------------------------------------------------------
// Reflection Fading
//---------------------------------------------------------------------------------------------------
#pragma parameter H_REFLECTION_FADE_TITLE			"_____[ REFLECTION FADE ]_______________________________________" 0 0 0 0

#pragma parameter H_FADE_AMOUNT 					"[ REFLECTION FADE ]  Fade Amount" 1 0 1 0.05
float H_FADE_AMOUNT = global.H_FADE_AMOUNT;

#pragma parameter H_RADIAL_FADE_WIDTH 				"[ REFLECTION FADE ]  Radial Fade Width" 100 0 1000 1
float H_RADIAL_FADE_WIDTH = global.H_RADIAL_FADE_WIDTH;

#pragma parameter H_RADIAL_FADE_HEIGHT 				"[ REFLECTION FADE ]  Radial Fade Height" 100 0 1000 1
float H_RADIAL_FADE_HEIGHT = global.H_RADIAL_FADE_HEIGHT;

#pragma parameter H_LATERAL_OUTER_FADE_POSITION 		"[ REFLECTION FADE ]  Lateral Outer Fade Position" -18 -500 500 0.5
float H_LATERAL_OUTER_FADE_POSITION = global.H_LATERAL_OUTER_FADE_POSITION;

#pragma parameter H_LATERAL_OUTER_FADE_DISTANCE 		"[ REFLECTION FADE ]  Lateral Outer Fade Distance" 20 1 400 0.5
float H_LATERAL_OUTER_FADE_DISTANCE = global.H_LATERAL_OUTER_FADE_DISTANCE;


#pragma parameter H_REFLECTION_CORNER_TITLE			"_____[ REFLECTION CORNER ]_____________________________________" 0 0 0 0

#pragma parameter H_CORNER_FADE 						"[ REFLECTION CORNER FADE ]  Corner Fade" 10 1 100 0.5
float H_CORNER_FADE = global.H_CORNER_FADE;

#pragma parameter H_CORNER_FADE_DISTANCE 				"[ REFLECTION CORNER FADE ]  Corner Fade Distance" 100 1 100 1
float H_CORNER_FADE_DISTANCE = global.H_CORNER_FADE_DISTANCE;

#pragma parameter H_CORNER_INNER_SPREAD 	            "[ REFLECTION CORNER FADE ]  Corner Inner Spread" 500 0 1000 10
float H_CORNER_INNER_SPREAD = global.H_CORNER_INNER_SPREAD;

#pragma parameter H_CORNER_OUTER_SPREAD 	            "[ REFLECTION CORNER FADE ]  Corner Outer Spread" 160 0 1000 10
float H_CORNER_OUTER_SPREAD = global.H_CORNER_OUTER_SPREAD;

#pragma parameter H_CORNER_ROTATION_OFFSET_TOP 	    "[ REFLECTION CORNER ROTATION ]  Offset Top" 0 -90 90 0.5
float H_CORNER_ROTATION_OFFSET_TOP = global.H_CORNER_ROTATION_OFFSET_TOP;

#pragma parameter H_CORNER_ROTATION_OFFSET_BOTTOM 	"[ REFLECTION CORNER ROTATION ]  Offset Bottom" 0 -90 90 0.5
float H_CORNER_ROTATION_OFFSET_BOTTOM = global.H_CORNER_ROTATION_OFFSET_BOTTOM;

// #pragma parameter H_CORNER_SPREAD_FALLOFF             "[ REFLECTION CORNER FADE ]  Corner Spread Falloff"  50 1 200 1
// float H_CORNER_SPREAD_FALLOFF = global.H_CORNER_SPREAD_FALLOFF;

//---------------------------------------------------------------------------------------------------
// Reflection Blur
//---------------------------------------------------------------------------------------------------
#pragma parameter H_REFLECT_BLUR_TITLE			        "_____[ REFLECTION BLUR & NOISE ]_______________________________" 0 0 0 0

#pragma parameter H_BLUR_NUM_SAMPLES 					"[ REFLECTION BLUR ]  Num Samples - 0 for OFF" 12 0 40 1
float H_BLUR_NUM_SAMPLES = global.H_BLUR_NUM_SAMPLES;

#pragma parameter H_BLUR_MIN 							"[ REFLECTION BLUR ]  Min" 	0 0 1 0.01
float H_BLUR_MIN = global.H_BLUR_MIN;

#pragma parameter H_BLUR_MAX 							"[ REFLECTION BLUR ]  Max" 	0.95 0 1 0.01
float H_BLUR_MAX = global.H_BLUR_MAX;

// Reflection Noise
#pragma parameter H_NOISE_AMOUNT 						"[ REFLECTION NOISE ]   Amount" 0.5 0 1 0.1
float H_NOISE_AMOUNT = global.H_NOISE_AMOUNT;

#pragma parameter H_NOISE_SAMPLES 					    "[ REFLECTION NOISE ]   Samples (0 for OFF)" 1 0 20 1
float H_NOISE_SAMPLES = global.H_NOISE_SAMPLES;

#pragma parameter H_NOISE_SAMPLE_DISTANCE 			"[ REFLECTION NOISE ]   Sample Distance" 0.20 0 1 0.01
float H_NOISE_SAMPLE_DISTANCE = global.H_NOISE_SAMPLE_DISTANCE;


//---------------------------------------------------------------------------------------------------
// Reflection Is Last Pass
//---------------------------------------------------------------------------------------------------
#pragma parameter H_REFLECTION_IS_LAST_PASS "[ REFLECTION IS LAST PASS] Glass and Reflect Only Presets" 0 0 1 1
float H_REFLECTION_IS_LAST_PASS = global.H_REFLECTION_IS_LAST_PASS;


/////////////// CONSTANT TUNING SETTINGS ///////////////

#ifndef H_CORNER_SPREAD_FALLOFF
    #define H_CORNER_SPREAD_FALLOFF 100
#endif

#ifndef H_GLASS_INNER_EDGE_SOFTNESS
    #define H_GLASS_INNER_EDGE_SOFTNESS 0.3
#endif