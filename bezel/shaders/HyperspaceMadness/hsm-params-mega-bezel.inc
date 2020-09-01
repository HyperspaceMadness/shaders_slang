// Tube Glass & Shadow
#pragma parameter HBZ_TUBE_GLASS_IMAGE_OPACITY         "[TUBE]  Tube Glass Highlight Opacity (Image)" 1.4 0.01 200 0.05
float HBZ_TUBE_GLASS_IMAGE_OPACITY = global.HBZ_TUBE_GLASS_IMAGE_OPACITY / 100;

#pragma parameter HBZ_TUBE_GLASS_IMAGE_SCALE         "[TUBE]  Tube Glass Highlight Scale" 1.05 0.1 5 0.01
float HBZ_TUBE_GLASS_IMAGE_SCALE = global.HBZ_TUBE_GLASS_IMAGE_SCALE;

#pragma parameter HBZ_TUBE_EDGE_SHADOW                 "[TUBE]  Tube Edge Shadow" 0.7 0 2 0.05
float HBZ_TUBE_EDGE_SHADOW = global.HBZ_TUBE_EDGE_SHADOW;



// Bezel & Frame Color
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



#pragma parameter HBZ_BEZEL_TITLE "------[BEZEL - MEGA BEZEL]-------------------------------------" 0 0 0 1

// Bezel
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



// Frame
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



#pragma parameter HBZ_IMAGE_TITLE "------[IMAGE LAYERS - MEGA BEZEL]--------------------------" 0 0 0 1

// Background
// #pragma parameter HBZ_BACKGROUND_IMAGE_OPACITY 		"[BG IMAGE]  Opacity" 1 0 1 0.05
#ifndef HBZ_BACKGROUND_IMAGE_OPACITY
    #define HBZ_BACKGROUND_IMAGE_OPACITY 1
#endif

// #pragma parameter HBZ_BACKGROUND_IMAGE_SCALE_MODE 		"[BG IMAGE]  Scale Mode - Auto, Fullscreen, Fit Height" 1 0 2 1
#ifndef HBZ_BACKGROUND_IMAGE_SCALE_MODE
    #define HBZ_BACKGROUND_IMAGE_SCALE_MODE 1
#endif

// #pragma parameter HBZ_BACKGROUND_IMAGE_ASPECT_RATIO 	"[BG IMAGE]  Aspect Ratio" 1.77 0.25 4 0.01
#ifndef HBZ_BACKGROUND_IMAGE_ASPECT_RATIO
    #define HBZ_BACKGROUND_IMAGE_ASPECT_RATIO 1.77
#endif

// Visual height of the tube in the texture (Only used in Scale Mode 0)
// #pragma parameter HBZ_IMAGE_LAYER_HORZ_VIEWPORT_TUBE_HEIGHT      "[BG IMAGE]  Tube Height in Texture (Scale Mode 0)" 69 10 150.0 0.1
#ifndef HBZ_IMAGE_LAYER_HORZ_VIEWPORT_TUBE_HEIGHT
    #define HBZ_IMAGE_LAYER_HORZ_VIEWPORT_TUBE_HEIGHT 0.8297
#endif

#define HBZ_IMAGE_LAYER_VERT_VIEWPORT_TUBE_HEIGHT 0.8297


//---------------------------------------------------------------------------------------------------
//    BACKGROUND IMAGE
//---------------------------------------------------------------------------------------------------

#pragma parameter HBZ_BACKGROUND_IMAGE_VIGNETTE_OPACITY "[IMAGE LAYER]  Background Vignette Opacity" 0.5 0 2 0.02
float HBZ_BACKGROUND_IMAGE_VIGNETTE_OPACITY = global.HBZ_BACKGROUND_IMAGE_VIGNETTE_OPACITY;

#pragma parameter HBZ_BACKGROUND_IMAGE_BRIGHTNESS       "[IMAGE LAYER]  Background Brightness" 1 0 2 0.02
float HBZ_BACKGROUND_IMAGE_BRIGHTNESS = global.HBZ_BACKGROUND_IMAGE_BRIGHTNESS;

#pragma parameter HBZ_BACKGROUND_IMAGE_USE_AS_BACKGROUND  "[IMAGE LAYER]  Background Use as Backdrop (No Bezel)" 0 0 1 1
float HBZ_BACKGROUND_IMAGE_USE_AS_BACKGROUND = global.HBZ_BACKGROUND_IMAGE_USE_AS_BACKGROUND;

#pragma parameter HBZ_BACKGROUND_IMAGE_SCALE_WITH_TUBE       "[IMAGE LAYER]  Bezel Scale With Tube" 0 0 1 1
float HBZ_BACKGROUND_IMAGE_SCALE_WITH_TUBE = global.HBZ_BACKGROUND_IMAGE_SCALE_WITH_TUBE;

#pragma parameter HBZ_BACKGROUND_IMAGE_SCALE                 "[IMAGE LAYER]  Bezel Scale" 100 0 1000 0.1
float HBZ_BACKGROUND_IMAGE_SCALE = global.HBZ_BACKGROUND_IMAGE_SCALE / 100;

#pragma parameter HBZ_BACKGROUND_IMAGE_POS_Y                 "[IMAGE LAYER]  Bezel Position Y" 0 -100 100 0.1
float HBZ_BACKGROUND_IMAGE_POS_Y = global.HBZ_BACKGROUND_IMAGE_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    BEZEL IMAGE
//---------------------------------------------------------------------------------------------------

#pragma parameter HBZ_BEZEL_IMAGE_ON                    "[IMAGE LAYER]  Bezel ON" 0 0 1 1
float HBZ_BEZEL_IMAGE_ON = global.HBZ_BEZEL_IMAGE_ON;

#pragma parameter HBZ_BEZEL_IMAGE_SCALE_WITH_TUBE       "[IMAGE LAYER]  Bezel Scale With Tube" 0 0 1 1
float HBZ_BEZEL_IMAGE_SCALE_WITH_TUBE = global.HBZ_BEZEL_IMAGE_SCALE_WITH_TUBE;

#pragma parameter HBZ_BEZEL_IMAGE_SCALE                 "[IMAGE LAYER]  Bezel Scale" 100 0 1000 0.1
float HBZ_BEZEL_IMAGE_SCALE = global.HBZ_BEZEL_IMAGE_SCALE / 100;

#pragma parameter HBZ_BEZEL_IMAGE_POS_Y                 "[IMAGE LAYER]  Bezel Position Y" 0 -100 100 0.1
float HBZ_BEZEL_IMAGE_POS_Y = global.HBZ_BEZEL_IMAGE_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    FRAME DECAL IMAGE
//---------------------------------------------------------------------------------------------------

#pragma parameter HBZ_FRAME_DECAL_IMAGE_OPACITY         "[IMAGE LAYER]  Frame Decal Opacity"  0 0 100 5
float HBZ_FRAME_DECAL_IMAGE_OPACITY = global.HBZ_FRAME_DECAL_IMAGE_OPACITY / 100;

#pragma parameter HBZ_FRAME_DECAL_IMAGE_SCALE           "[IMAGE LAYER]  Frame Decal Scale"  100 50 150 0.1
float HBZ_FRAME_DECAL_IMAGE_SCALE = global.HBZ_FRAME_DECAL_IMAGE_SCALE / 100;

#pragma parameter HBZ_FRAME_DECAL_IMAGE_POS_Y           "[IMAGE LAYER]  Frame Decal Position Y"  0 -100 100 0.1
float HBZ_FRAME_DECAL_IMAGE_POS_Y = global.HBZ_FRAME_DECAL_IMAGE_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    NIGHT LIGHTING IMAGE
//---------------------------------------------------------------------------------------------------

#pragma parameter HBZ_NIGHTLIGHTING_IMAGE_OPACITY       "[IMAGE LAYER]  Night Lighting Opacity"  0 0 100 1
float HBZ_NIGHTLIGHTING_IMAGE_OPACITY = global.HBZ_NIGHTLIGHTING_IMAGE_OPACITY / 100;


//---------------------------------------------------------------------------------------------------
//    LED IMAGE
//---------------------------------------------------------------------------------------------------

#pragma parameter HBZ_LED_IMAGE_OPACITY                 "[IMAGE LAYER]  LED Image Opacity"  0 0 100 1
float HBZ_LED_IMAGE_OPACITY = global.HBZ_LED_IMAGE_OPACITY / 100;


//---------------------------------------------------------------------------------------------------
//    TOP IMAGE
//---------------------------------------------------------------------------------------------------

#pragma parameter HTI_TOP_IMAGE_OPACITY                 "[IMAGE LAYER]  Top Opacity"  0 0 100 0.1
float HTI_TOP_IMAGE_OPACITY = global.HTI_TOP_IMAGE_OPACITY / 100;

#pragma parameter HTI_TOP_IMAGE_BLEND_MODE              "[IMAGE LAYER]  Top Blend Mode - Normal, Add, Mult, Under..."  0 0 5 1
float HTI_TOP_IMAGE_BLEND_MODE = global.HTI_TOP_IMAGE_BLEND_MODE;

#pragma parameter HTI_TOP_IMAGE_MASK_MODE               "[IMAGE LAYER]  Top Mask - ALL, Tube, Bezel+, Frame+, Frame, BG"  0 0 5 1
float HTI_TOP_IMAGE_MASK_MODE = global.HTI_TOP_IMAGE_MASK_MODE;


#pragma parameter HBZ_BEZEL_GAMMA				        "[STATIC ELEMENTS GAMMA]  Gamma Adjust" 1 0.01 5 0.01
float HBZ_BEZEL_GAMMA = global.HBZ_BEZEL_GAMMA;



#pragma parameter HBZ_REFLECTION_TITLE "------[REFLECTION BLURRING - MEGA BEZEL]-----------------------" 0 0 0 1

// Reflection Blur
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



#pragma parameter HBZ_REFLECTIONFADE_TITLE "------[REFLECTION FADING - MEGA BEZEL]-------------------------" 0 0 0 1

// Reflection
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




/////////////// CONSTANT TUNING SETTINGS ///////////////

#ifndef HBR_CORNER_SPREAD_FALLOFF
    #define HBR_CORNER_SPREAD_FALLOFF 100
#endif

#ifndef HBZ_GLASS_INNER_EDGE_SOFTNESS
    #define HBZ_GLASS_INNER_EDGE_SOFTNESS 0.3
#endif