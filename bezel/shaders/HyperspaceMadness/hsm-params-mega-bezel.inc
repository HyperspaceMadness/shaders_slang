


//---------------------------------------------------------------------------------------------------
// Bezel & Frame Color
//---------------------------------------------------------------------------------------------------
#pragma parameter HBZ_BEZEL_AND_FRAME_TITLE "------[BEZEL & FRAME COLORING - MEGA BEZEL]--------------------" 0 0 0 1

#pragma parameter HBZ_BEZEL_COLOR_HUE					"[BEZEL & FRAME COLOR]  Color Hue" 0 0 360 0.5
float HBZ_BEZEL_COLOR_HUE = global.HBZ_BEZEL_COLOR_HUE / 360;

#pragma parameter HBZ_BEZEL_COLOR_SATURATION			"[BEZEL & FRAME COLOR]  Color Saturation" 0 0 100 1
float HBZ_BEZEL_COLOR_SATURATION = global.HBZ_BEZEL_COLOR_SATURATION / 100;

#pragma parameter HBZ_BEZEL_COLOR_VALUE				"[BEZEL & FRAME COLOR]  Color Value/Brightness - Def 10" 10 0 100 0.2
float HBZ_BEZEL_COLOR_VALUE = global.HBZ_BEZEL_COLOR_VALUE / 100;

#pragma parameter HBZ_BEZEL_COLOR_BLEND_WITH_IMAGE		"[BEZEL & FRAME COLOR]  Blend Color with Image" 0 0 1 0.05
float HBZ_BEZEL_COLOR_BLEND_WITH_IMAGE = global.HBZ_BEZEL_COLOR_BLEND_WITH_IMAGE;

#pragma parameter HBZ_BEZEL_NOISE 						"[BEZEL & FRAME COLOR]  Noise - Def 30" 30 0 100 1
float HBZ_BEZEL_NOISE = global.HBZ_BEZEL_NOISE / 100;


//---------------------------------------------------------------------------------------------------
// Bezel
//---------------------------------------------------------------------------------------------------
#pragma parameter HBZ_BEZEL_TITLE "------[BEZEL - MEGA BEZEL]-------------------------------------" 0 0 0 1

#pragma parameter HBZ_BEZEL_OPACITY 					"[BEZEL]  Opacity" 1 0 1 0.05
float HBZ_BEZEL_OPACITY = global.HBZ_BEZEL_OPACITY;

#pragma parameter HBZ_BEZEL_WIDTH 						"[BEZEL]  Width - Def 7.5" 7.5 -10 200 0.1
float HBZ_BEZEL_WIDTH = global.HBZ_BEZEL_WIDTH / 100;

#pragma parameter HBZ_BEZEL_HEIGHT 					    "[BEZEL]  Height - Def 6" 6 -10 200 0.1
float HBZ_BEZEL_HEIGHT = global.HBZ_BEZEL_HEIGHT;

#pragma parameter HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE	"[BEZEL]  Inner Corner Radius Scale - Def 0.5" 0.5 0 10 0.1
float HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE = global.HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE;

#pragma parameter HBZ_BEZEL_INNER_EDGE_THICKNESS		"[BEZEL]  Inner Edge Thickness - Def 0.5" 0.5 0 5 0.1
float HBZ_BEZEL_INNER_EDGE_THICKNESS = global.HBZ_BEZEL_INNER_EDGE_THICKNESS  / 100;

#pragma parameter HSS_BEZEL_OUTER_CURVATURE_SCALE 		"[BEZEL]   Outer Curvature Scale" 0 0 5 0.05
float HSS_BEZEL_OUTER_CURVATURE_SCALE = global.HSS_BEZEL_OUTER_CURVATURE_SCALE;

#pragma parameter HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE 	"[BEZEL]  Outer Corner Radius Scale - Def 1" 1 0 10 0.1
float HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE = global.HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE;

#pragma parameter HBZ_BEZEL_BRIGHTNESS 				"[BEZEL]  Brightness - Def 30" 30 0 300 2
float HBZ_BEZEL_BRIGHTNESS = global.HBZ_BEZEL_BRIGHTNESS;

#pragma parameter HBZ_BEZEL_HIGHLIGHT 					"[BEZEL]  Highlight" 1 0 100 0.2
float HBZ_BEZEL_HIGHLIGHT = global.HBZ_BEZEL_HIGHLIGHT;


//---------------------------------------------------------------------------------------------------
// Frame
//---------------------------------------------------------------------------------------------------
#pragma parameter HBZ_FRAME_TITLE "------[FRAME - MEGA BEZEL]-----------------------------" 0 0 0 1

#pragma parameter HBZ_FRAME_OPACITY 					"[FRAME]   Opacity" 1 0 1 0.05
float HBZ_FRAME_OPACITY = global.HBZ_FRAME_OPACITY;

#pragma parameter HBZ_FRAME_THICKNESS 					"[FRAME]   Thickness" 7 0 200 0.2
float HBZ_FRAME_THICKNESS = global.HBZ_FRAME_THICKNESS;

#pragma parameter HBZ_FRAME_INNER_EDGE_THICKNESS 		"[FRAME]   Inner Edge Thickness" 1 0 50 0.05
float HBZ_FRAME_INNER_EDGE_THICKNESS = global.HBZ_FRAME_INNER_EDGE_THICKNESS / 1000;

#pragma parameter HBZ_FRAME_INNER_CORNER_RADIUS_SCALE 		"[FRAME]   Inner Corner Radius Scale" 1 0 50 0.05
float HBZ_FRAME_INNER_CORNER_RADIUS_SCALE = global.HBZ_FRAME_INNER_CORNER_RADIUS_SCALE;

#pragma parameter HSS_FRAME_OUTER_CURVATURE_SCALE 		"[FRAME]   Outer Curvature Scale" 0 0 5 0.05
float HSS_FRAME_OUTER_CURVATURE_SCALE = global.HSS_FRAME_OUTER_CURVATURE_SCALE;

#pragma parameter HBZ_FRAME_OUTER_CORNER_RADIUS 		"[FRAME]   Outer Corner Radius" 5 0 70 0.05
float HBZ_FRAME_OUTER_CORNER_RADIUS = global.HBZ_FRAME_OUTER_CORNER_RADIUS;

#pragma parameter HBZ_FRAME_OUTER_EDGE_THICKNESS 		"[FRAME]   Outer Edge Thickness" 1 0 100 0.1
float HBZ_FRAME_OUTER_EDGE_THICKNESS = global.HBZ_FRAME_OUTER_EDGE_THICKNESS;

#pragma parameter HBZ_FRAME_OUTER_EDGE_SHADING 		    "[FRAME]   Outer Edge Shading" 0.5 0 1 0.05
float HBZ_FRAME_OUTER_EDGE_SHADING = global.HBZ_FRAME_OUTER_EDGE_SHADING;

#pragma parameter HBZ_FRAME_POS_Y_OFFSET 				"[FRAME]   Pos Y Offset" 0 -25 25 0.05
float HBZ_FRAME_POS_Y_OFFSET = global.HBZ_FRAME_POS_Y_OFFSET;

#pragma parameter HBZ_FRAME_SHADOW_OPACITY				"[FRAME]   Shadow Opacity" 1 0 3 0.01
float HBZ_FRAME_SHADOW_OPACITY = global.HBZ_FRAME_SHADOW_OPACITY;

#pragma parameter HBZ_FRAME_SHADOW_WIDTH				"[FRAME]   Shadow Width" 10 0 50 0.1
float HBZ_FRAME_SHADOW_WIDTH = global.HBZ_FRAME_SHADOW_WIDTH;


//---------------------------------------------------------------------------------------------------
// Reflection Blur
//---------------------------------------------------------------------------------------------------

#pragma parameter HBZ_REFLECTION_TITLE "------[REFLECTION BLURRING - MEGA BEZEL]-----------------------" 0 0 0 1

#pragma parameter HBR_BLUR_NUM_SAMPLES 					"[REFLECTION BLUR]  Num Samples - 0 for OFF" 20 0 40 1
float HBR_BLUR_NUM_SAMPLES = global.HBR_BLUR_NUM_SAMPLES;

#pragma parameter HBR_BLUR_MIN 							"[REFLECTION BLUR]  Min" 	0 0 1 0.01
float HBR_BLUR_MIN = global.HBR_BLUR_MIN;

#pragma parameter HBR_BLUR_MAX 							"[REFLECTION BLUR]  Max" 	0.95 0 1 0.01
float HBR_BLUR_MAX = global.HBR_BLUR_MAX;

// Reflection Noise
#pragma parameter HBR_NOISE_AMOUNT 						"[REFLECTION NOISE]   Amount" 0.5 0 1 0.1
float HBR_NOISE_AMOUNT = global.HBR_NOISE_AMOUNT;

#pragma parameter HBR_NOISE_SAMPLES 					"[REFLECTION NOISE]   Samples (0 for OFF)" 1 0 20 1
float HBR_NOISE_SAMPLES = global.HBR_NOISE_SAMPLES;

#pragma parameter HBR_NOISE_SAMPLE_DISTANCE 			"[REFLECTION NOISE]   Sample Distance" 0.20 0 1 0.01
float HBR_NOISE_SAMPLE_DISTANCE = global.HBR_NOISE_SAMPLE_DISTANCE;


//---------------------------------------------------------------------------------------------------
// Reflection Fading
//---------------------------------------------------------------------------------------------------
#pragma parameter HBZ_REFLECTIONFADE_TITLE "------[REFLECTION FADING - MEGA BEZEL]-------------------------" 0 0 0 1

#pragma parameter HBR_GLOBAL_AMOUNT 					"[REFLECTION GLOBAL]  Global Amount" 0.4 0 3 0.02
float HBR_GLOBAL_AMOUNT = global.HBR_GLOBAL_AMOUNT;

#pragma parameter HBR_GLOBAL_GAMMA_ADJUST 				"[REFLECTION GLOBAL]  Global Gamma Adjust" 1.2 0.25 3 0.05
float HBR_GLOBAL_GAMMA_ADJUST = global.HBR_GLOBAL_GAMMA_ADJUST;

#pragma parameter HBR_INNER_EDGE_REFLECTION 			"[REFLECTION AMOUNT]  Inner Edge Amount" 0.7 0 3 0.02
float HBR_INNER_EDGE_REFLECTION = global.HBR_INNER_EDGE_REFLECTION;

#pragma parameter HBR_INNER_EDGE_FULLSCREEN_GLOW 		"[REFLECTION AMOUNT]  Inner Edge Fullscreen Glow" 0.4 0 10 0.02
float HBR_INNER_EDGE_FULLSCREEN_GLOW = global.HBR_INNER_EDGE_FULLSCREEN_GLOW;

#pragma parameter HBR_DIRECT_REFLECTION 				"[REFLECTION AMOUNT]  Direct Reflection" 1.5 0 3 0.02
float HBR_DIRECT_REFLECTION = global.HBR_DIRECT_REFLECTION;

#pragma parameter HBR_DIFFUSED_REFLECTION 				"[REFLECTION AMOUNT]  Diffused Reflection" 0.5 0 3 0.02
float HBR_DIFFUSED_REFLECTION = global.HBR_DIFFUSED_REFLECTION;

#pragma parameter HBR_FULLSCREEN_GLOW 					"[REFLECTION AMOUNT]  FullScreen Glow" 75 0 600 0.5
float HBR_FULLSCREEN_GLOW = global.HBR_FULLSCREEN_GLOW;

#pragma parameter HBR_FULLSCREEN_GLOW_GAMMA 			"[REFLECTION AMOUNT]  FullScreen Glow Gamma" 3 0 5 0.02
float HBR_FULLSCREEN_GLOW_GAMMA = global.HBR_FULLSCREEN_GLOW_GAMMA;

#pragma parameter HBR_FADE_AMOUNT 						"[REFLECTION FADE]  Fade Amount" 1 0 1 0.05
float HBR_FADE_AMOUNT = global.HBR_FADE_AMOUNT;

#pragma parameter HBR_RADIAL_FADE_WIDTH 				"[REFLECTION FADE]  Radial Fade Width" 100 0 1000 1
float HBR_RADIAL_FADE_WIDTH = global.HBR_RADIAL_FADE_WIDTH;

#pragma parameter HBR_RADIAL_FADE_HEIGHT 				"[REFLECTION FADE]  Radial Fade Height" 100 0 1000 1
float HBR_RADIAL_FADE_HEIGHT = global.HBR_RADIAL_FADE_HEIGHT;

#pragma parameter HBR_LATERAL_OUTER_FADE_POSITION 		"[REFLECTION FADE]  Lateral Outer Fade Position" -18 -500 500 0.5
float HBR_LATERAL_OUTER_FADE_POSITION = global.HBR_LATERAL_OUTER_FADE_POSITION;

#pragma parameter HBR_LATERAL_OUTER_FADE_DISTANCE 		"[REFLECTION FADE]  Lateral Outer Fade Distance" 20 1 400 0.5
float HBR_LATERAL_OUTER_FADE_DISTANCE = global.HBR_LATERAL_OUTER_FADE_DISTANCE;

#pragma parameter HBR_CORNER_FADE 						"[REFLECTION CORNER FADE]  Corner Fade" 10 1 100 0.5
float HBR_CORNER_FADE = global.HBR_CORNER_FADE;

#pragma parameter HBR_CORNER_FADE_DISTANCE 				"[REFLECTION CORNER FADE]  Corner Fade Distance" 100 1 100 1
float HBR_CORNER_FADE_DISTANCE = global.HBR_CORNER_FADE_DISTANCE;

#pragma parameter HBR_CORNER_INNER_SPREAD 	            "[REFLECTION CORNER FADE]  Corner Inner Spread" 500 0 1000 10
float HBR_CORNER_INNER_SPREAD = global.HBR_CORNER_INNER_SPREAD;

#pragma parameter HBR_CORNER_OUTER_SPREAD 	            "[REFLECTION CORNER FADE]  Corner Outer Spread" 160 0 1000 10
float HBR_CORNER_OUTER_SPREAD = global.HBR_CORNER_OUTER_SPREAD;

#pragma parameter HBR_CORNER_ROTATION_OFFSET_TOP 	    "[REFLECTION CORNER ROTATION]  Offset Top" 0 -90 90 0.5
float HBR_CORNER_ROTATION_OFFSET_TOP = global.HBR_CORNER_ROTATION_OFFSET_TOP;

#pragma parameter HBR_CORNER_ROTATION_OFFSET_BOTTOM 	"[REFLECTION CORNER ROTATION]  Offset Bottom" 0 -90 90 0.5
float HBR_CORNER_ROTATION_OFFSET_BOTTOM = global.HBR_CORNER_ROTATION_OFFSET_BOTTOM;

// #pragma parameter HBR_CORNER_SPREAD_FALLOFF             "[REFLECTION CORNER FADE]  Corner Spread Falloff"  50 1 200 1
// float HBR_CORNER_SPREAD_FALLOFF = global.HBR_CORNER_SPREAD_FALLOFF;


//---------------------------------------------------------------------------------------------------
// IMAGE LAYERS
//---------------------------------------------------------------------------------------------------

// Visual height of the tube in the texture (Only used in Scale Mode 0)
// #pragma parameter HLY_IMAGE_LAYER_HORZ_VIEWPORT_TUBE_HEIGHT      "[BG IMAGE]  Tube Height in Texture (Scale Mode 0)" 69 10 150.0 0.1
#ifndef HLY_IMAGE_LAYER_HORZ_VIEWPORT_TUBE_HEIGHT
    #define HLY_IMAGE_LAYER_HORZ_VIEWPORT_TUBE_HEIGHT 0.8297
#endif

#define HLY_IMAGE_LAYER_VERT_VIEWPORT_TUBE_HEIGHT 0.8297


//---------------------------------------------------------------------------------------------------
//    BG IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_BG_IMAGE_TITLE "------[BACKGROUND IMAGE LAYER - MEGA BEZEL]--------------------" 0 0 0 0

#pragma parameter HLY_BG_IMAGE_BRIGHTNESS "[BG IMAGE]  Brightness" 100 0 600 0.1
float HLY_BG_IMAGE_BRIGHTNESS = global.HLY_BG_IMAGE_BRIGHTNESS / 100;

#pragma parameter HLY_BG_IMAGE_VIGNETTE_OPACITY "[BG IMAGE]  Vignette Opacity" 50 0 100 2
float HLY_BG_IMAGE_VIGNETTE_OPACITY = global.HLY_BG_IMAGE_VIGNETTE_OPACITY / 100;

#pragma parameter HLY_BG_IMAGE_SCALE_MODE       "[BG IMAGE]  Scale Mode - 0:FullScreen, 1:Tube, 2:Bezel" 0 0 2 1
float HLY_BG_IMAGE_SCALE_MODE = global.HLY_BG_IMAGE_SCALE_MODE;

#pragma parameter HLY_BG_IMAGE_SCALE_KEEP_ASPECT      "[BG IMAGE]  Keep Aspect"  1 0 1 1
float HLY_BG_IMAGE_SCALE_KEEP_ASPECT = global.HLY_BG_IMAGE_SCALE_KEEP_ASPECT;

#pragma parameter HLY_BG_IMAGE_SCALE            "[BG IMAGE]  Scale" 100 0 1000 0.1
float HLY_BG_IMAGE_SCALE = global.HLY_BG_IMAGE_SCALE / 100;

#pragma parameter HLY_BG_IMAGE_SCALE_X            "[BG IMAGE]  Scale X" 100 0 1000 0.1
float HLY_BG_IMAGE_SCALE_X = global.HLY_BG_IMAGE_SCALE_X / 100;

#pragma parameter HLY_BG_IMAGE_POS_Y            "[BG IMAGE]  Position Y" 0 -100 100 0.1
float HLY_BG_IMAGE_POS_Y = global.HLY_BG_IMAGE_POS_Y / 100;

#pragma parameter HLY_BG_IMAGE_MIRROR_WRAP      "[BG IMAGE]  Mirror Wrap" 1 0 1 1
float HLY_BG_IMAGE_MIRROR_WRAP = global.HLY_BG_IMAGE_MIRROR_WRAP;


//---------------------------------------------------------------------------------------------------
//    CRT Layer
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_CRT_SCREEN_TITLE "------[CRT SCREEN LAYER - MEGA BEZEL]--------------------" 0 0 0 0

#pragma parameter HLY_CRT_SCREEN_BLEND_MODE  "[CRT SCREEN]  Blend Mode 0:Normal, 1:Add (Backdrop)" 0 0 1 1
float HLY_CRT_SCREEN_BLEND_MODE = global.HLY_CRT_SCREEN_BLEND_MODE;


//---------------------------------------------------------------------------------------------------
//    TUBE REFLECTION IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_TUBE_REFLECTION_IMAGE_TITLE "------[TUBE REFLECTION IMAGE LAYER - MEGA BEZEL]---------------" 0 0 0 0

#pragma parameter HLY_TUBE_REFLECTION_IMAGE_OPACITY         "[TUBE REFLECTION IMAGE]  Opacity" 1.4 0 100 0.05
float HLY_TUBE_REFLECTION_IMAGE_OPACITY = global.HLY_TUBE_REFLECTION_IMAGE_OPACITY / 100;

#pragma parameter HLY_TUBE_REFLECTION_IMAGE_SCALE           "[TUBE REFLECTION IMAGE]  Scale" 105 10 500 1
float HLY_TUBE_REFLECTION_IMAGE_SCALE = global.HLY_TUBE_REFLECTION_IMAGE_SCALE / 100;

#pragma parameter HLY_TUBE_EDGE_SHADOW                      "[TUBE EDGE SHADOW]  Opacity of Shadow from Bezel" 70 0 200 5
float HLY_TUBE_EDGE_SHADOW = global.HLY_TUBE_EDGE_SHADOW / 100;


//---------------------------------------------------------------------------------------------------
//    BEZEL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_BEZEL_IMAGE_TITLE "------[BEZEL/GEL IMAGE LAYER - MEGA BEZEL]---------------------" 0 0 0 0

#pragma parameter HLY_BEZEL_IMAGE_OPACITY               "[BEZEL IMAGE]  Opacity" 0 0 100 1
float HLY_BEZEL_IMAGE_OPACITY = global.HLY_BEZEL_IMAGE_OPACITY / 100;

#pragma parameter HLY_BEZEL_IMAGE_BLEND_MODE            "[BEZEL IMAGE]  Blend Mode - 0:Normal, 1:Add, 2:Multiply"  0 0 2 1
float HLY_BEZEL_IMAGE_BLEND_MODE = global.HLY_BEZEL_IMAGE_BLEND_MODE;

#pragma parameter HLY_BEZEL_IMAGE_MASK_MODE             "[BEZEL IMAGE]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG" 2 0 7 1
float HLY_BEZEL_IMAGE_MASK_MODE = global.HLY_BEZEL_IMAGE_MASK_MODE;

#pragma parameter HLY_BEZEL_IMAGE_DEPTH_ORDER            "[BEZEL IMAGE]  Depth Order - Under Frame, Over Frame"  0 0 1 1
float HLY_BEZEL_IMAGE_DEPTH_ORDER = global.HLY_BEZEL_IMAGE_DEPTH_ORDER;

#pragma parameter HLY_BEZEL_IMAGE_SCALE_MODE            "[BEZEL IMAGE]  Scale Mode - 0:FullScreen, 1:Tube, 2:Bezel, 3:BG"  1 0 3 1
float HLY_BEZEL_IMAGE_SCALE_MODE = global.HLY_BEZEL_IMAGE_SCALE_MODE;

#pragma parameter HLY_BEZEL_IMAGE_SCALE_KEEP_ASPECT      "[BEZEL IMAGE]  Keep Aspect"  1 0 1 1
float HLY_BEZEL_IMAGE_SCALE_KEEP_ASPECT = global.HLY_BEZEL_IMAGE_SCALE_KEEP_ASPECT;

#pragma parameter HLY_BEZEL_IMAGE_SCALE                 "[BEZEL IMAGE]  Scale" 100 0 1000 0.1
float HLY_BEZEL_IMAGE_SCALE = global.HLY_BEZEL_IMAGE_SCALE / 100;

#pragma parameter HLY_BEZEL_IMAGE_SCALE_X               "[BEZEL IMAGE]  Scale X" 100 0 1000 0.1
float HLY_BEZEL_IMAGE_SCALE_X = global.HLY_BEZEL_IMAGE_SCALE_X / 100;

#pragma parameter HLY_BEZEL_IMAGE_POS_Y                 "[BEZEL IMAGE]  Position Y" 0 -100 100 0.1
float HLY_BEZEL_IMAGE_POS_Y = global.HLY_BEZEL_IMAGE_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    GENERATED BEZEL & FRAME
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_GENERATED_BEZEL_TITLE             "------[GENERATED BEZEL & FRAME - MEGA BEZEL]-------------------" 0 0 0 0

#pragma parameter HLY_GENERATED_BEZEL_OPACITY           "[GENERATED BEZEL & FRAME]  Opacity" 100 0 100 5
float HLY_GENERATED_BEZEL_OPACITY = global.HLY_GENERATED_BEZEL_OPACITY / 100;


//---------------------------------------------------------------------------------------------------
//    DECAL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_DECAL_IMAGE_TITLE "------[DECAL IMAGE LAYER - MEGA BEZEL]-------------------------" 0 0 0 0

#pragma parameter HLY_DECAL_IMAGE_OPACITY               "[DECAL IMAGE]  Opacity"  0 0 100 5
float HLY_DECAL_IMAGE_OPACITY = global.HLY_DECAL_IMAGE_OPACITY / 100;

#pragma parameter HLY_DECAL_IMAGE_BLEND_MODE            "[DECAL IMAGE]  Blend Mode - 0:Normal, 1:Add, 2:Multiply"  0 0 2 1
float HLY_DECAL_IMAGE_BLEND_MODE = global.HLY_DECAL_IMAGE_BLEND_MODE;

#pragma parameter HLY_DECAL_IMAGE_MASK_MODE             "[DECAL IMAGE]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   0 0 7 1
float HLY_DECAL_IMAGE_MASK_MODE = global.HLY_DECAL_IMAGE_MASK_MODE;

#pragma parameter HLY_DECAL_IMAGE_SCALE_MODE            "[DECAL IMAGE]  Scale Mode - 0:FullScreen, 1:Tube, 2:Bezel, 3:BG"  2 0 3 1
float HLY_DECAL_IMAGE_SCALE_MODE = global.HLY_DECAL_IMAGE_SCALE_MODE;

#pragma parameter HLY_DECAL_IMAGE_SCALE_KEEP_ASPECT     "[DECAL IMAGE]  Scale Keep Aspect"  1 0 1 1
float HLY_DECAL_IMAGE_SCALE_KEEP_ASPECT = global.HLY_DECAL_IMAGE_SCALE_KEEP_ASPECT;

#pragma parameter HLY_DECAL_IMAGE_SCALE                 "[DECAL IMAGE]  Scale"  100 50 500 0.1
float HLY_DECAL_IMAGE_SCALE = global.HLY_DECAL_IMAGE_SCALE / 100;

#pragma parameter HLY_DECAL_IMAGE_SCALE_X                 "[DECAL IMAGE]  Scale X"  100 50 500 0.1
float HLY_DECAL_IMAGE_SCALE_X = global.HLY_DECAL_IMAGE_SCALE_X / 100;

#pragma parameter HLY_DECAL_IMAGE_POS_Y                 "[DECAL IMAGE]  Position Y"  0 -100 100 0.1
float HLY_DECAL_IMAGE_POS_Y = global.HLY_DECAL_IMAGE_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    NIGHT LIGHTING IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_NIGHTLIGHTING_IMAGE_TITLE "------[NIGHT LIGHTING IMAGE LAYER - MEGA BEZEL]----------------" 0 0 0 0

#pragma parameter HLY_NIGHTLIGHTING_IMAGE_OPACITY       "[NIGHT LIGHTING IMAGE]  Opacity"  0 0 100 1
float HLY_NIGHTLIGHTING_IMAGE_OPACITY = global.HLY_NIGHTLIGHTING_IMAGE_OPACITY / 100;

#pragma parameter HLY_NIGHTLIGHTING_IMAGE_SATURATION    "[NIGHT LIGHTING IMAGE]  Saturation"  100 0 200 1
float HLY_NIGHTLIGHTING_IMAGE_SATURATION = global.HLY_NIGHTLIGHTING_IMAGE_SATURATION / 100;


//---------------------------------------------------------------------------------------------------
//    REFLECTION IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_REFLECTION_LAYER_TITLE "------[REFLECTION LAYER - MEGA BEZEL]-------------------------" 0 0 0 0

#pragma parameter HLY_REFLECTION_BLEND_MODE             "[REFLECTION]  Blend Mode - 0:Normal, 1:Add"  1 0 1 1
float HLY_REFLECTION_BLEND_MODE = global.HLY_REFLECTION_BLEND_MODE;

#pragma parameter HLY_REFLECTION_MASK_MODE              "[REFLECTION]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   3 0 7 1
float HLY_REFLECTION_MASK_MODE = global.HLY_REFLECTION_MASK_MODE;

//---------------------------------------------------------------------------------------------------
//    LED IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_LED_IMAGE_TITLE "------[LED IMAGE LAYER - MEGA BEZEL]---------------------------" 0 0 0 0

#pragma parameter HLY_LED_IMAGE_OPACITY                 "[LED IMAGE]  Image Opacity"  0 0 100 1
float HLY_LED_IMAGE_OPACITY = global.HLY_LED_IMAGE_OPACITY / 100;

#pragma parameter HLY_LED_IMAGE_MASK_MODE               "[LED IMAGE]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   7 0 7 1
float HLY_LED_IMAGE_MASK_MODE = global.HLY_LED_IMAGE_MASK_MODE;

#pragma parameter HLY_LED_IMAGE_SCALE_MODE              "[LED IMAGE]  Scale Mode - 0:Full Screen 1:BG"  1 0 1 1
float HLY_LED_IMAGE_SCALE_MODE = global.HLY_LED_IMAGE_SCALE_MODE;


//---------------------------------------------------------------------------------------------------
//    TOP IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_TOP_IMAGE_TITLE "------[TOP IMAGE LAYER - MEGA BEZEL]---------------------------" 0 0 0 0

#pragma parameter HLY_TOP_IMAGE_OPACITY                 "[TOP IMAGE]  Opacity"  0 0 100 0.1
float HLY_TOP_IMAGE_OPACITY = global.HLY_TOP_IMAGE_OPACITY / 100;

#pragma parameter HLY_TOP_IMAGE_BLEND_MODE              "[TOP IMAGE]  Blend Mode - Normal, Add, Mult"  0 0 2 1
float HLY_TOP_IMAGE_BLEND_MODE = global.HLY_TOP_IMAGE_BLEND_MODE;

#pragma parameter HLY_TOP_IMAGE_MASK_MODE               "[TOP IMAGE]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   0 0 7 1
float HLY_TOP_IMAGE_MASK_MODE = global.HLY_TOP_IMAGE_MASK_MODE;

#pragma parameter HLY_TOP_IMAGE_DEPTH_ORDER             "[TOP IMAGE]  Depth Order - 0:Under Frame 1:Top"  1 0 1 1
float HLY_TOP_IMAGE_DEPTH_ORDER = global.HLY_TOP_IMAGE_DEPTH_ORDER;

#pragma parameter HLY_TOP_IMAGE_SCALE_MODE              "[TOP IMAGE]  Scale Mode - 0:FullScreen, 1:Tube, 2:Bezel, 3:BG"  3 0 3 1
float HLY_TOP_IMAGE_SCALE_MODE = global.HLY_TOP_IMAGE_SCALE_MODE;

#pragma parameter HLY_TOP_IMAGE_SCALE_KEEP_ASPECT     "[TOP IMAGE]  Scale Keep Aspect"  1 0 1 1
float HLY_TOP_IMAGE_SCALE_KEEP_ASPECT = global.HLY_TOP_IMAGE_SCALE_KEEP_ASPECT;

#pragma parameter HLY_TOP_IMAGE_SCALE                   "[TOP IMAGE]  Scale" 100 0 1000 0.1
float HLY_TOP_IMAGE_SCALE = global.HLY_TOP_IMAGE_SCALE / 100;

#pragma parameter HLY_TOP_IMAGE_SCALE_X                 "[TOP IMAGE]  Scale X" 100 0 1000 0.1
float HLY_TOP_IMAGE_SCALE_X = global.HLY_TOP_IMAGE_SCALE_X / 100;

#pragma parameter HLY_TOP_IMAGE_POS_Y             "[TOP IMAGE]  Position Y"  0 -100 100 0.1
float HLY_TOP_IMAGE_POS_Y = global.HLY_TOP_IMAGE_POS_Y / 100;

#pragma parameter HLY_TOP_IMAGE_APPLY_NIGHT_LIGHTING    "[TOP IMAGE]  Apply Night Lighting to Top Image"  1 0 1 1
float HLY_TOP_IMAGE_APPLY_NIGHT_LIGHTING = global.HLY_TOP_IMAGE_APPLY_NIGHT_LIGHTING;

#pragma parameter HLY_TOP_IMAGE_MIRROR_WRAP      "[TOP IMAGE]  Mirror Wrap" 1 0 1 1
float HLY_TOP_IMAGE_MIRROR_WRAP = global.HLY_TOP_IMAGE_MIRROR_WRAP;

//---------------------------------------------------------------------------------------------------
//    STATIC ELEMENT GAMMA
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_STATIC_ELEMENTS_GAMMA				"[STATIC ELEMENTS GAMMA]  Gamma Adjust" 1 0.01 5 0.01
float HLY_STATIC_ELEMENTS_GAMMA = global.HLY_STATIC_ELEMENTS_GAMMA;


//---------------------------------------------------------------------------------------------------
//    LAYERING DEBUG
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_LAYERING_DEBUG_TITLE "------[LAYERING DEBUG - MEGA BEZEL]----------------------------" 0 0 0 0

#pragma parameter HLY_LAYERING_DEBUG_MASK_MODE    "[DEBUG]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG" -1 -1 7 1
float HLY_LAYERING_DEBUG_MASK_MODE = global.HLY_LAYERING_DEBUG_MASK_MODE;



/////////////// CONSTANT TUNING SETTINGS ///////////////

#ifndef HBR_CORNER_SPREAD_FALLOFF
    #define HBR_CORNER_SPREAD_FALLOFF 100
#endif

#ifndef HBZ_GLASS_INNER_EDGE_SOFTNESS
    #define HBZ_GLASS_INNER_EDGE_SOFTNESS 0.3
#endif