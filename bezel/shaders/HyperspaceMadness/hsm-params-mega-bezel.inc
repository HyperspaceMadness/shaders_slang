//---------------------------------------------------------------------------------------------------
//    REFLECTION
//---------------------------------------------------------------------------------------------------
#pragma parameter HBR_GLOBAL_AMOUNT 					"[ REFLECTION AMOUNT ]  Global Amount --------------------------" 0.4 0 3 0.02
float HBR_GLOBAL_AMOUNT = global.HBR_GLOBAL_AMOUNT;

#pragma parameter HBR_GLOBAL_GAMMA_ADJUST 				"[ REFLECTION AMOUNT ]  Global Gamma Adjust" 1.2 0.25 3 0.05
float HBR_GLOBAL_GAMMA_ADJUST = global.HBR_GLOBAL_GAMMA_ADJUST;

#pragma parameter HBR_INNER_EDGE_REFLECTION 			"[ REFLECTION AMOUNT ]  Inner Edge Amount" 0.9 0 3 0.02
float HBR_INNER_EDGE_REFLECTION = global.HBR_INNER_EDGE_REFLECTION;

#pragma parameter HBR_INNER_EDGE_FULLSCREEN_GLOW 		"[ REFLECTION AMOUNT ]  Inner Edge Fullscreen Glow" 0.4 0 10 0.02
float HBR_INNER_EDGE_FULLSCREEN_GLOW = global.HBR_INNER_EDGE_FULLSCREEN_GLOW;

#pragma parameter HBR_DIRECT_REFLECTION 				"[ REFLECTION AMOUNT ]  Direct Reflection" 1.5 0 3 0.02
float HBR_DIRECT_REFLECTION = global.HBR_DIRECT_REFLECTION;

#pragma parameter HBR_DIFFUSED_REFLECTION 				"[ REFLECTION AMOUNT ]  Diffused Reflection" 0.5 0 3 0.02
float HBR_DIFFUSED_REFLECTION = global.HBR_DIFFUSED_REFLECTION;

#pragma parameter HBR_FULLSCREEN_GLOW 					"[ REFLECTION AMOUNT ]  FullScreen Glow" 75 0 600 0.5
float HBR_FULLSCREEN_GLOW = global.HBR_FULLSCREEN_GLOW;

#pragma parameter HBR_FULLSCREEN_GLOW_GAMMA 			"[ REFLECTION AMOUNT ]  FullScreen Glow Gamma" 3 0 5 0.02
float HBR_FULLSCREEN_GLOW_GAMMA = global.HBR_FULLSCREEN_GLOW_GAMMA;


//---------------------------------------------------------------------------------------------------
// Reflection Fading
//---------------------------------------------------------------------------------------------------
#pragma parameter HBR_FADE_AMOUNT 						"[ REFLECTION FADE ]  Fade Amount ------------------------------" 1 0 1 0.05
float HBR_FADE_AMOUNT = global.HBR_FADE_AMOUNT;

#pragma parameter HBR_RADIAL_FADE_WIDTH 				"[ REFLECTION FADE ]  Radial Fade Width" 100 0 1000 1
float HBR_RADIAL_FADE_WIDTH = global.HBR_RADIAL_FADE_WIDTH;

#pragma parameter HBR_RADIAL_FADE_HEIGHT 				"[ REFLECTION FADE ]  Radial Fade Height" 100 0 1000 1
float HBR_RADIAL_FADE_HEIGHT = global.HBR_RADIAL_FADE_HEIGHT;

#pragma parameter HBR_LATERAL_OUTER_FADE_POSITION 		"[ REFLECTION FADE ]  Lateral Outer Fade Position" -18 -500 500 0.5
float HBR_LATERAL_OUTER_FADE_POSITION = global.HBR_LATERAL_OUTER_FADE_POSITION;

#pragma parameter HBR_LATERAL_OUTER_FADE_DISTANCE 		"[ REFLECTION FADE ]  Lateral Outer Fade Distance" 20 1 400 0.5
float HBR_LATERAL_OUTER_FADE_DISTANCE = global.HBR_LATERAL_OUTER_FADE_DISTANCE;

#pragma parameter HBR_CORNER_FADE 						"[ REFLECTION CORNER FADE ]  Corner Fade -----------------------" 10 1 100 0.5
float HBR_CORNER_FADE = global.HBR_CORNER_FADE;

#pragma parameter HBR_CORNER_FADE_DISTANCE 				"[ REFLECTION CORNER FADE ]  Corner Fade Distance" 100 1 100 1
float HBR_CORNER_FADE_DISTANCE = global.HBR_CORNER_FADE_DISTANCE;

#pragma parameter HBR_CORNER_INNER_SPREAD 	            "[ REFLECTION CORNER FADE ]  Corner Inner Spread" 500 0 1000 10
float HBR_CORNER_INNER_SPREAD = global.HBR_CORNER_INNER_SPREAD;

#pragma parameter HBR_CORNER_OUTER_SPREAD 	            "[ REFLECTION CORNER FADE ]  Corner Outer Spread" 160 0 1000 10
float HBR_CORNER_OUTER_SPREAD = global.HBR_CORNER_OUTER_SPREAD;

#pragma parameter HBR_CORNER_ROTATION_OFFSET_TOP 	    "[ REFLECTION CORNER ROTATION ]  Offset Top" 0 -90 90 0.5
float HBR_CORNER_ROTATION_OFFSET_TOP = global.HBR_CORNER_ROTATION_OFFSET_TOP;

#pragma parameter HBR_CORNER_ROTATION_OFFSET_BOTTOM 	"[ REFLECTION CORNER ROTATION ]  Offset Bottom" 0 -90 90 0.5
float HBR_CORNER_ROTATION_OFFSET_BOTTOM = global.HBR_CORNER_ROTATION_OFFSET_BOTTOM;

// #pragma parameter HBR_CORNER_SPREAD_FALLOFF             "[ REFLECTION CORNER FADE ]  Corner Spread Falloff"  50 1 200 1
// float HBR_CORNER_SPREAD_FALLOFF = global.HBR_CORNER_SPREAD_FALLOFF;


//---------------------------------------------------------------------------------------------------
// Reflection Blur
//---------------------------------------------------------------------------------------------------
#pragma parameter HBR_BLUR_NUM_SAMPLES 					"[ REFLECTION BLUR ]  Num Samples - 0 for OFF ------------------" 12 0 40 1
float HBR_BLUR_NUM_SAMPLES = global.HBR_BLUR_NUM_SAMPLES;

#pragma parameter HBR_BLUR_MIN 							"[ REFLECTION BLUR ]  Min" 	0 0 1 0.01
float HBR_BLUR_MIN = global.HBR_BLUR_MIN;

#pragma parameter HBR_BLUR_MAX 							"[ REFLECTION BLUR ]  Max" 	0.95 0 1 0.01
float HBR_BLUR_MAX = global.HBR_BLUR_MAX;

// Reflection Noise
#pragma parameter HBR_NOISE_AMOUNT 						"[ REFLECTION NOISE ]   Amount" 0.5 0 1 0.1
float HBR_NOISE_AMOUNT = global.HBR_NOISE_AMOUNT;

#pragma parameter HBR_NOISE_SAMPLES 					"[ REFLECTION NOISE ]   Samples (0 for OFF)" 1 0 20 1
float HBR_NOISE_SAMPLES = global.HBR_NOISE_SAMPLES;

#pragma parameter HBR_NOISE_SAMPLE_DISTANCE 			"[ REFLECTION NOISE ]   Sample Distance" 0.20 0 1 0.01
float HBR_NOISE_SAMPLE_DISTANCE = global.HBR_NOISE_SAMPLE_DISTANCE;


//---------------------------------------------------------------------------------------------------
// Reflection Is Last Pass
//---------------------------------------------------------------------------------------------------
#pragma parameter HBR_REFLECTION_IS_LAST_PASS "[ REFLECTION IS LAST PASS] (For Glass and Reflect Only Presets)" 0 0 1 1
float HBR_REFLECTION_IS_LAST_PASS = global.HBR_REFLECTION_IS_LAST_PASS;


//---------------------------------------------------------------------------------------------------
//    BEZEL
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//    GENERATED BEZEL & FRAME
//---------------------------------------------------------------------------------------------------
// #pragma parameter HBZ_BEZEL_TITLE "-----[ GENERATED BEZEL & FRAME ]-------------------------------" 0 0 0 1

#pragma parameter HLY_BEZEL_OPACITY           "[ BEZEL ]  Opacity --------------------------------------------" 100 0 100 5
float HLY_BEZEL_OPACITY = global.HLY_BEZEL_OPACITY / 100;

#pragma parameter HLY_BEZEL_BLEND_MODE        "[ BEZEL ]  Blend Mode -  -1:Off 0:Normal, 1:Add, 2:Mult"  0 -1 2 1
float HLY_BEZEL_BLEND_MODE = global.HLY_BEZEL_BLEND_MODE;

#pragma parameter HBZ_BEZEL_WIDTH 						"[ BEZEL ]  Width - Def 7.5" 7.5 -10 200 0.1
float HBZ_BEZEL_WIDTH = global.HBZ_BEZEL_WIDTH / 100;

#pragma parameter HBZ_BEZEL_HEIGHT 					    "[ BEZEL ]  Height - Def 6" 6 -10 200 0.1
float HBZ_BEZEL_HEIGHT = global.HBZ_BEZEL_HEIGHT;

#pragma parameter HBZ_BEZEL_INNER_EDGE_THICKNESS		"[ BEZEL ]  Inner Edge Thickness - Def 0.7" 0.7 0 5 0.1
float HBZ_BEZEL_INNER_EDGE_THICKNESS = global.HBZ_BEZEL_INNER_EDGE_THICKNESS  / 100;

#pragma parameter HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE	"[ BEZEL ]  Inner Corner Radius Scale - Def 0.5" 0.5 0 10 0.1
float HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE = global.HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE;

#pragma parameter HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE 	"[ BEZEL ]  Outer Corner Radius Scale - Def 1" 1 0 10 0.1
float HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE = global.HBZ_BEZEL_OUTER_CORNER_RADIUS_SCALE;

#pragma parameter HBZ_BEZEL_OUTER_CURVATURE_SCALE 		"[ BEZEL ]   Outer Curvature Scale" 0 0 5 0.05
float HBZ_BEZEL_OUTER_CURVATURE_SCALE = global.HBZ_BEZEL_OUTER_CURVATURE_SCALE;

#pragma parameter HBZ_BEZEL_OUTER_POS_Y_OFFSET 				"[ BEZEL ]   Outer Edge Pos Y Offset" 0 -25 25 0.05
float HBZ_BEZEL_OUTER_POS_Y_OFFSET = global.HBZ_BEZEL_OUTER_POS_Y_OFFSET;

#pragma parameter HBZ_BEZEL_INNER_EDGE_SHADOW        "[ BEZEL ]  Opacity of Shadow from Bezel on Tube" 70 0 200 5
float HBZ_BEZEL_INNER_EDGE_SHADOW = global.HBZ_BEZEL_INNER_EDGE_SHADOW / 100;


// Params below are not needed for reflection pass

//---------------------------------------------------------------------------------------------------
// Bezel & Frame Color
//---------------------------------------------------------------------------------------------------
#pragma parameter HBZ_BEZEL_COLOR_HUE					"[ BEZEL & FRAME COLOR ]  Color Hue ----------------------------" 0 0 360 1
float HBZ_BEZEL_COLOR_HUE = global.HBZ_BEZEL_COLOR_HUE / 360;

#pragma parameter HBZ_BEZEL_COLOR_SATURATION			"[ BEZEL & FRAME COLOR ]  Color Saturation" 0 0 100 1
float HBZ_BEZEL_COLOR_SATURATION = global.HBZ_BEZEL_COLOR_SATURATION / 100;

#pragma parameter HBZ_BEZEL_COLOR_VALUE				    "[ BEZEL & FRAME COLOR ]  Color Value/Brightness - Def 10" 10 0 100 0.2
float HBZ_BEZEL_COLOR_VALUE = global.HBZ_BEZEL_COLOR_VALUE / 100;

#pragma parameter HBZ_BEZEL_COLOR_BLEND_WITH_IMAGE		"[ BEZEL & FRAME COLOR ]  Blend Color with Image" 0 0 1 0.05
float HBZ_BEZEL_COLOR_BLEND_WITH_IMAGE = global.HBZ_BEZEL_COLOR_BLEND_WITH_IMAGE;

#pragma parameter HBZ_BEZEL_NOISE 						"[ BEZEL & FRAME COLOR ]  Noise - Def 30" 30 0 100 1
float HBZ_BEZEL_NOISE = global.HBZ_BEZEL_NOISE / 100;

#pragma parameter HBZ_BEZEL_BRIGHTNESS 				    "[ BEZEL COLOR ]  Brightness - Def 30 --------------------------" 30 0 300 2
float HBZ_BEZEL_BRIGHTNESS = global.HBZ_BEZEL_BRIGHTNESS;

#pragma parameter HBZ_BEZEL_HIGHLIGHT 					"[ BEZEL COLOR ]  Highlight" 1 0 100 0.2
float HBZ_BEZEL_HIGHLIGHT = global.HBZ_BEZEL_HIGHLIGHT;


//---------------------------------------------------------------------------------------------------
//    FRAME
//---------------------------------------------------------------------------------------------------

#pragma parameter HLY_FRAME_OPACITY                     "[ FRAME ]  Opacity --------------------------------------------" 100 0 100 5
float HLY_FRAME_OPACITY = global.HLY_FRAME_OPACITY / 100;

#pragma parameter HLY_FRAME_BLEND_MODE                  "[ FRAME ]  Blend Mode -  -1:Off 0:Normal, 1:Add, 2:Mult"  0 -1 2 1
float HLY_FRAME_BLEND_MODE = global.HLY_FRAME_BLEND_MODE;

#pragma parameter HBZ_FRAME_THICKNESS 					"[ FRAME ]   Thickness -----------------------------------------" 7 0 200 0.2
float HBZ_FRAME_THICKNESS = global.HBZ_FRAME_THICKNESS;

#pragma parameter HBZ_FRAME_INNER_EDGE_THICKNESS 		"[ FRAME ]   Inner Edge Thickness" 1 0 50 0.05
float HBZ_FRAME_INNER_EDGE_THICKNESS = global.HBZ_FRAME_INNER_EDGE_THICKNESS / 1000;

#pragma parameter HBZ_FRAME_INNER_CORNER_RADIUS_SCALE 	"[ FRAME ]   Inner Corner Radius Scale" 1 0 50 0.05
float HBZ_FRAME_INNER_CORNER_RADIUS_SCALE = global.HBZ_FRAME_INNER_CORNER_RADIUS_SCALE;

#pragma parameter HSS_FRAME_OUTER_CURVATURE_SCALE 		"[ FRAME ]   Outer Curvature Scale" 0 0 5 0.05
float HSS_FRAME_OUTER_CURVATURE_SCALE = global.HSS_FRAME_OUTER_CURVATURE_SCALE;

#pragma parameter HBZ_FRAME_OUTER_CORNER_RADIUS 		"[ FRAME ]   Outer Corner Radius" 5 0 70 0.05
float HBZ_FRAME_OUTER_CORNER_RADIUS = global.HBZ_FRAME_OUTER_CORNER_RADIUS;

#pragma parameter HBZ_FRAME_OUTER_EDGE_THICKNESS 		"[ FRAME ]   Outer Edge Thickness" 1 0 100 0.1
float HBZ_FRAME_OUTER_EDGE_THICKNESS = global.HBZ_FRAME_OUTER_EDGE_THICKNESS;

#pragma parameter HBZ_FRAME_OUTER_EDGE_SHADING 		    "[ FRAME ]   Outer Edge Shading" 0.5 0 1 0.05
float HBZ_FRAME_OUTER_EDGE_SHADING = global.HBZ_FRAME_OUTER_EDGE_SHADING;

#pragma parameter HBZ_FRAME_SHADOW_OPACITY	            "[ FRAME ]   Shadow Opacity" 1 0 3 0.01
float HBZ_FRAME_SHADOW_OPACITY = global.HBZ_FRAME_SHADOW_OPACITY;

#pragma parameter HBZ_FRAME_SHADOW_WIDTH                "[ FRAME ]   Shadow Width" 10 0 50 0.1
float HBZ_FRAME_SHADOW_WIDTH = global.HBZ_FRAME_SHADOW_WIDTH;


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//
//    Image Compositing Pass Parameters Start
//
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------
//    Reflection - Image Compositing Parameters
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_REFLECTION_BLEND_MODE             "[ REFLECTION ]  Blend Mode -   -1:Off 0:Normal, 1:Add ---------"  1 -1 1 1
float HLY_REFLECTION_BLEND_MODE = global.HLY_REFLECTION_BLEND_MODE;

#pragma parameter HLY_REFLECTION_MASK_MODE              "[ REFLECTION ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   3 0 7 1
float HLY_REFLECTION_MASK_MODE = global.HLY_REFLECTION_MASK_MODE;


//---------------------------------------------------------------------------------------------------
//    STATIC ELEMENT GAMMA
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_STATIC_LAYERS_GAMMA				"[ STATIC LAYERS GAMMA ]  Gamma Adjust -------------------------" 1 0.01 5 0.01
float HLY_STATIC_LAYERS_GAMMA = global.HLY_STATIC_LAYERS_GAMMA;

//---------------------------------------------------------------------------------------------------
//    NIGHT LIGHTING IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_NIGHTLIGHTING_IMAGE_OPACITY       "[ NIGHT LIGHTING ]  Opacity -----------------------------------"  0 0 100 1
float HLY_NIGHTLIGHTING_IMAGE_OPACITY = global.HLY_NIGHTLIGHTING_IMAGE_OPACITY / 100;

#pragma parameter HLY_NIGHTLIGHTING_IMAGE_MIRROR_HORZ       "[ NIGHT LIGHTING ]  Mirror H"  0 0 1 1
float HLY_NIGHTLIGHTING_IMAGE_MIRROR_HORZ = global.HLY_NIGHTLIGHTING_IMAGE_MIRROR_HORZ;

#pragma parameter HLY_NIGHTLIGHTING_IMAGE_SATURATION    "[ NIGHT LIGHTING ]  Saturation"  100 0 300 1
float HLY_NIGHTLIGHTING_IMAGE_SATURATION = global.HLY_NIGHTLIGHTING_IMAGE_SATURATION / 100;

#pragma parameter HLY_NIGHTLIGHTING_IMAGE_HUE    "[ NIGHT LIGHTING ]  Hue"  0 -180 180 1
float HLY_NIGHTLIGHTING_IMAGE_HUE = global.HLY_NIGHTLIGHTING_IMAGE_HUE / 360;

#pragma parameter HLY_NIGHTLIGHTING_IMAGE_VALUE    "[ NIGHT LIGHTING ]  Value"  100 0 400 1
float HLY_NIGHTLIGHTING_IMAGE_VALUE = global.HLY_NIGHTLIGHTING_IMAGE_VALUE / 100;

#pragma parameter HLY_NIGHTLIGHTING_IMAGE_DITHERING_SAMPLES  "[ NIGHTLIGHTING ]  Dithering Noise Samples (Reduces Banding)" 0 0 10 1
float HLY_NIGHTLIGHTING_IMAGE_DITHERING_SAMPLES = global.HLY_NIGHTLIGHTING_IMAGE_DITHERING_SAMPLES;


//---------------------------------------------------------------------------------------------------
//    IMAGE LAYERING START
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_IMAGE_LAYERING_TITLE "-----[ GRAPHIC ELEMENTS LAYERING ]-----------------------------" 0 0 0 0

//---------------------------------------------------------------------------------------------------
//    CutOut in Image Layers
//---------------------------------------------------------------------------------------------------

#pragma parameter HLY_IMAGE_CUTOUT_WIDTH 				"[ IMAGE CUTOUT ]  Width - Def 1" 1 -100 200 0.1
float HLY_IMAGE_CUTOUT_WIDTH = global.HLY_IMAGE_CUTOUT_WIDTH / 100;

#pragma parameter HLY_IMAGE_CUTOUT_HEIGHT 				"[ IMAGE CUTOUT ]  Height - Def 1" 1 -100 200 0.1
float HLY_IMAGE_CUTOUT_HEIGHT = global.HLY_IMAGE_CUTOUT_HEIGHT / 100;

#pragma parameter HLY_IMAGE_CUTOUT_CORNER_RADIUS 		"[ IMAGE CUTOUT ]  Corner Radius - Def 0" 0 0 70 1
float HLY_IMAGE_CUTOUT_CORNER_RADIUS = global.HLY_IMAGE_CUTOUT_CORNER_RADIUS;


//---------------------------------------------------------------------------------------------------
//    LAYERING DEBUG
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_LAYERING_DEBUG_MASK_MODE    "[ DEBUG ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG  ---" -1 -1 7 1
float HLY_LAYERING_DEBUG_MASK_MODE = global.HLY_LAYERING_DEBUG_MASK_MODE;



//---------------------------------------------------------------------------------------------------
//    BG IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_BG_IMAGE_BRIGHTNESS "[ BACKGROUND ]  Brightness ------------------------------------" 100 0 600 0.5
float HLY_BG_IMAGE_BRIGHTNESS = global.HLY_BG_IMAGE_BRIGHTNESS / 100;

#pragma parameter HLY_BG_IMAGE_VIGNETTE_OPACITY "[ BACKGROUND ]  Vignette Opacity" 50 0 100 2
float HLY_BG_IMAGE_VIGNETTE_OPACITY = global.HLY_BG_IMAGE_VIGNETTE_OPACITY / 100;

#pragma parameter HLY_BG_IMAGE_APPLY_NIGHT_LIGHTING_AND_STATIC_GAMMA    "[ BACKGROUND ] Apply NightLight & Static Gamma (0 for Backdrop)"  1 0 1 1
float HLY_BG_IMAGE_APPLY_NIGHT_LIGHTING_AND_STATIC_GAMMA = global.HLY_BG_IMAGE_APPLY_NIGHT_LIGHTING_AND_STATIC_GAMMA;

#pragma parameter HLY_BG_IMAGE_MASK_MODE   "[ BACKGROUND ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG" 1 0 7 1
float HLY_BG_IMAGE_MASK_MODE = global.HLY_BG_IMAGE_MASK_MODE;

#pragma parameter HLY_BG_IMAGE_SCALE_MODE       "[ BACKGROUND ]  Scale Mode - 0:FullScreen, 1:Tube, 2:Bezel" 0 0 2 1
float HLY_BG_IMAGE_SCALE_MODE = global.HLY_BG_IMAGE_SCALE_MODE;

#pragma parameter HLY_BG_IMAGE_SCALE_KEEP_ASPECT      "[ BACKGROUND ]  Keep Aspect"  1 0 1 1
float HLY_BG_IMAGE_SCALE_KEEP_ASPECT = global.HLY_BG_IMAGE_SCALE_KEEP_ASPECT;

#pragma parameter HLY_BG_IMAGE_SCALE            "[ BACKGROUND ]  Scale" 100 0 1000 0.1
float HLY_BG_IMAGE_SCALE = global.HLY_BG_IMAGE_SCALE / 100;

#pragma parameter HLY_BG_IMAGE_SCALE_X            "[ BACKGROUND ]  Scale X" 100 0 1000 0.1
float HLY_BG_IMAGE_SCALE_X = global.HLY_BG_IMAGE_SCALE_X / 100;

#pragma parameter HLY_BG_IMAGE_POS_Y            "[ BACKGROUND ]  Position Y" 0 -100 100 0.1
float HLY_BG_IMAGE_POS_Y = global.HLY_BG_IMAGE_POS_Y / 100;

#pragma parameter HLY_BG_IMAGE_MIRROR_WRAP      "[ BACKGROUND ]  Mirror Wrap" 1 0 1 1
float HLY_BG_IMAGE_MIRROR_WRAP = global.HLY_BG_IMAGE_MIRROR_WRAP;


//---------------------------------------------------------------------------------------------------
//    CRT Layer
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_CRT_SCREEN_BLEND_MODE  "[ CRT SCREEN ]  Blend Mode -  -1:Off 0:Normal, 1:Add (Backdrop)" 0 -1 1 1
float HLY_CRT_SCREEN_BLEND_MODE = global.HLY_CRT_SCREEN_BLEND_MODE;


//---------------------------------------------------------------------------------------------------
//    GLASS IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_CABINET_GLASS_IMAGE_OPACITY           "[ CAB GLASS ]  Opacity -----------------------------------" 0 0 100 0.05
float HLY_CABINET_GLASS_IMAGE_OPACITY = global.HLY_CABINET_GLASS_IMAGE_OPACITY / 100;

#pragma parameter HLY_CABINET_GLASS_IMAGE_BRIGHTNESS        "[ CAB GLASS ]  Brightness" 100 0 200 1
float HLY_CABINET_GLASS_IMAGE_BRIGHTNESS = global.HLY_CABINET_GLASS_IMAGE_BRIGHTNESS / 100;

#pragma parameter HLY_CABINET_GLASS_IMAGE_BLEND_MODE        "[ CAB GLASS ]  Blend Mode  -1:Off 0:Normal, 1:Add, 2:Multiply"  1 -1 2 1
float HLY_CABINET_GLASS_IMAGE_BLEND_MODE = global.HLY_CABINET_GLASS_IMAGE_BLEND_MODE;

#pragma parameter HLY_CABINET_GLASS_IMAGE_MASK_MODE         "[ CAB GLASS ] Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG" 1 0 7 1
float HLY_CABINET_GLASS_IMAGE_MASK_MODE = global.HLY_CABINET_GLASS_IMAGE_MASK_MODE;

#pragma parameter HLY_CABINET_GLASS_IMAGE_CUTOUT_MODE       "[ CAB GLASS ]  Image Cutout Mode - 0:OFF 1:ON 2:Invert" 0 0 2 1
float HLY_CABINET_GLASS_IMAGE_CUTOUT_MODE = global.HLY_CABINET_GLASS_IMAGE_CUTOUT_MODE;

#pragma parameter HLY_CABINET_GLASS_IMAGE_DEPTH_ORDER       "[ CAB GLASS ]  Depth Order - Under Frame, Over LED"  0 0 1 1
float HLY_CABINET_GLASS_IMAGE_DEPTH_ORDER = global.HLY_CABINET_GLASS_IMAGE_DEPTH_ORDER;

#pragma parameter HLY_CABINET_GLASS_IMAGE_SCALE_MODE        "[ CAB GLASS ]  Scale Mode - Full, BG, Tube, Bzl, Decal, TopImg" 2 0 5 1
float HLY_CABINET_GLASS_IMAGE_SCALE_MODE = global.HLY_CABINET_GLASS_IMAGE_SCALE_MODE;

#pragma parameter HLY_CABINET_GLASS_IMAGE_SCALE             "[ CAB GLASS ]  Scale" 120 10 500 1
float HLY_CABINET_GLASS_IMAGE_SCALE = global.HLY_CABINET_GLASS_IMAGE_SCALE / 100;

#pragma parameter HLY_CABINET_GLASS_IMAGE_DITHERING_SAMPLES  "[ CAB GLASS ]  Dithering Noise Samples (Reduces Banding)" 0 0 10 1
float HLY_CABINET_GLASS_IMAGE_DITHERING_SAMPLES = global.HLY_CABINET_GLASS_IMAGE_DITHERING_SAMPLES;


//---------------------------------------------------------------------------------------------------
//    BEZEL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_BEZEL_IMAGE_OPACITY               "[ BEZEL IMG ]  Opacity ----------------------------------------" 0 0 100 1
float HLY_BEZEL_IMAGE_OPACITY = global.HLY_BEZEL_IMAGE_OPACITY / 100;

#pragma parameter HLY_BEZEL_IMAGE_HUE                   "[ BEZEL IMG ]  Hue Offset" 0 0 360 1
float HLY_BEZEL_IMAGE_HUE = global.HLY_BEZEL_IMAGE_HUE / 360;

#pragma parameter HLY_BEZEL_IMAGE_SATURATION            "[ BEZEL IMG ]  Saturation" 100 0 200 1
float HLY_BEZEL_IMAGE_SATURATION = global.HLY_BEZEL_IMAGE_SATURATION / 100;

#pragma parameter HLY_BEZEL_IMAGE_BRIGHTNESS            "[ BEZEL IMG ]  Brightness" 100 0 200 1
float HLY_BEZEL_IMAGE_BRIGHTNESS = global.HLY_BEZEL_IMAGE_BRIGHTNESS / 100;

#pragma parameter HLY_BEZEL_IMAGE_BLEND_MODE            "[ BEZEL IMG ]  Blend Mode -  -1:Off 0:Normal, 1:Add, 2:Multiply"  0 -1 2 1
float HLY_BEZEL_IMAGE_BLEND_MODE = global.HLY_BEZEL_IMAGE_BLEND_MODE;

#pragma parameter HLY_BEZEL_IMAGE_MASK_MODE             "[ BEZEL IMG ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG" 3 0 7 1
float HLY_BEZEL_IMAGE_MASK_MODE = global.HLY_BEZEL_IMAGE_MASK_MODE;

#pragma parameter HLY_BEZEL_IMAGE_DEPTH_ORDER            "[ BEZEL IMG ] Depth Order - UnderTube,UnderBzl,UnderFrm,OverFrm"  2 0 3 1
float HLY_BEZEL_IMAGE_DEPTH_ORDER = global.HLY_BEZEL_IMAGE_DEPTH_ORDER;

#pragma parameter HLY_BEZEL_IMAGE_SCALE_MODE            "[ BEZEL IMG ]  Scale Mode - 0:FullScreen, 1:Tube, 2:Bezel, 3:BG"  1 0 3 1
float HLY_BEZEL_IMAGE_SCALE_MODE = global.HLY_BEZEL_IMAGE_SCALE_MODE;

#pragma parameter HLY_BEZEL_IMAGE_SCALE_KEEP_ASPECT      "[ BEZEL IMG ]  Keep Aspect"  1 0 1 1
float HLY_BEZEL_IMAGE_SCALE_KEEP_ASPECT = global.HLY_BEZEL_IMAGE_SCALE_KEEP_ASPECT;

#pragma parameter HLY_BEZEL_IMAGE_SCALE                 "[ BEZEL IMG ]  Scale" 100 0 1000 0.1
float HLY_BEZEL_IMAGE_SCALE = global.HLY_BEZEL_IMAGE_SCALE / 100;

#pragma parameter HLY_BEZEL_IMAGE_SCALE_X               "[ BEZEL IMG ]  Scale X" 100 0 1000 0.1
float HLY_BEZEL_IMAGE_SCALE_X = global.HLY_BEZEL_IMAGE_SCALE_X / 100;

#pragma parameter HLY_BEZEL_IMAGE_POS_Y                 "[ BEZEL IMG ]  Position Y" 0 -100 100 0.1
float HLY_BEZEL_IMAGE_POS_Y = global.HLY_BEZEL_IMAGE_POS_Y / 100;

#pragma parameter HLY_BEZEL_IMAGE_USE_CURVATURE          "[ BEZEL IMG ]  Use Curvature"  0 0 1 1
float HLY_BEZEL_IMAGE_USE_CURVATURE = global.HLY_BEZEL_IMAGE_USE_CURVATURE;


//---------------------------------------------------------------------------------------------------
//    DECAL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_DECAL_IMAGE_OPACITY               "[ DECAL ]  Opacity --------------------------------------------"  0 0 100 5
float HLY_DECAL_IMAGE_OPACITY = global.HLY_DECAL_IMAGE_OPACITY / 100;

#pragma parameter HLY_DECAL_IMAGE_BLEND_MODE            "[ DECAL ]  Blend Mode -   -1:Off 0:Normal, 1:Add, 2:Multiply"  0 -1 2 1
float HLY_DECAL_IMAGE_BLEND_MODE = global.HLY_DECAL_IMAGE_BLEND_MODE;

#pragma parameter HLY_DECAL_IMAGE_MASK_MODE             "[ DECAL ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   0 0 7 1
float HLY_DECAL_IMAGE_MASK_MODE = global.HLY_DECAL_IMAGE_MASK_MODE;

#pragma parameter HLY_DECAL_IMAGE_SCALE_MODE            "[ DECAL ]  Scale Mode - Full, Tube, Bezel, BG, BzlImg"  2 0 4 1
float HLY_DECAL_IMAGE_SCALE_MODE = global.HLY_DECAL_IMAGE_SCALE_MODE;

#pragma parameter HLY_DECAL_IMAGE_SCALE_KEEP_ASPECT     "[ DECAL ]  Scale Keep Aspect"  1 0 1 1
float HLY_DECAL_IMAGE_SCALE_KEEP_ASPECT = global.HLY_DECAL_IMAGE_SCALE_KEEP_ASPECT;

#pragma parameter HLY_DECAL_IMAGE_SCALE                 "[ DECAL ]  Scale"  100 50 500 0.1
float HLY_DECAL_IMAGE_SCALE = global.HLY_DECAL_IMAGE_SCALE / 100;

#pragma parameter HLY_DECAL_IMAGE_SCALE_X                 "[ DECAL ]  Scale X"  100 50 500 0.1
float HLY_DECAL_IMAGE_SCALE_X = global.HLY_DECAL_IMAGE_SCALE_X / 100;

#pragma parameter HLY_DECAL_IMAGE_POS_Y                 "[ DECAL ]  Position Y"  0 -100 100 0.1
float HLY_DECAL_IMAGE_POS_Y = global.HLY_DECAL_IMAGE_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    LED IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_LED_IMAGE_OPACITY                 "[ LED ]  Image Opacity ----------------------------------------"  0 0 100 1
float HLY_LED_IMAGE_OPACITY = global.HLY_LED_IMAGE_OPACITY / 100;

#pragma parameter HLY_LED_IMAGE_BLEND_MODE              "[ LED ]  Blend Mode -  -1:Off 0:Normal, 1:Add, 2:Multiply"  1 -1 2 1
float HLY_LED_IMAGE_BLEND_MODE = global.HLY_LED_IMAGE_BLEND_MODE;

#pragma parameter HLY_LED_IMAGE_MASK_MODE               "[ LED ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   7 0 7 1
float HLY_LED_IMAGE_MASK_MODE = global.HLY_LED_IMAGE_MASK_MODE;

#pragma parameter HLY_LED_IMAGE_SCALE_MODE              "[ LED ]  Scale Mode - Full, BG, BzlImg, Decal, Top"  1 0 4 1
float HLY_LED_IMAGE_SCALE_MODE = global.HLY_LED_IMAGE_SCALE_MODE;


//---------------------------------------------------------------------------------------------------
//    TOP IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HLY_TOP_IMAGE_OPACITY                 "[ TOP ]  Opacity ----------------------------------------------"  0 0 100 0.1
float HLY_TOP_IMAGE_OPACITY = global.HLY_TOP_IMAGE_OPACITY / 100;

#pragma parameter HLY_TOP_IMAGE_BLEND_MODE              "[ TOP ]  Blend Mode -   -1:Off 0:Normal, 1:Add, 2:Multiply"  0 -1 2 1
float HLY_TOP_IMAGE_BLEND_MODE = global.HLY_TOP_IMAGE_BLEND_MODE;

#pragma parameter HLY_TOP_IMAGE_MASK_MODE               "[ TOP ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   0 0 7 1
float HLY_TOP_IMAGE_MASK_MODE = global.HLY_TOP_IMAGE_MASK_MODE;

#pragma parameter HLY_TOP_IMAGE_CUTOUT_MODE               "[ TOP ]  Image Cutout Mode - 0:OFF 1:ON 2:Invert" 0 0 2 1
float HLY_TOP_IMAGE_CUTOUT_MODE = global.HLY_TOP_IMAGE_CUTOUT_MODE;

#pragma parameter HLY_TOP_IMAGE_DEPTH_ORDER             "[ TOP ]  Depth Order - 0:Under Frame 1:Top"  1 0 1 1
float HLY_TOP_IMAGE_DEPTH_ORDER = global.HLY_TOP_IMAGE_DEPTH_ORDER;

#pragma parameter HLY_TOP_IMAGE_SCALE_MODE              "[ TOP ]  Scale Mode - FullScrn, Tube, Bezel, BG, Bzl Img, Decal"  0 0 5 1
float HLY_TOP_IMAGE_SCALE_MODE = global.HLY_TOP_IMAGE_SCALE_MODE;

#pragma parameter HLY_TOP_IMAGE_SCALE_KEEP_ASPECT       "[ TOP ]  Scale Keep Aspect"  1 0 1 1
float HLY_TOP_IMAGE_SCALE_KEEP_ASPECT = global.HLY_TOP_IMAGE_SCALE_KEEP_ASPECT;

#pragma parameter HLY_TOP_IMAGE_SCALE                   "[ TOP ]  Scale" 100 0 1000 0.1
float HLY_TOP_IMAGE_SCALE = global.HLY_TOP_IMAGE_SCALE / 100;

#pragma parameter HLY_TOP_IMAGE_SCALE_X                 "[ TOP ]  Scale X" 100 0 1000 0.1
float HLY_TOP_IMAGE_SCALE_X = global.HLY_TOP_IMAGE_SCALE_X / 100;

#pragma parameter HLY_TOP_IMAGE_POS_Y                   "[ TOP ]  Position Y"  0 -100 100 0.1
float HLY_TOP_IMAGE_POS_Y = global.HLY_TOP_IMAGE_POS_Y / 100;

#pragma parameter HLY_TOP_IMAGE_MIRROR_WRAP             "[ TOP ]  Mirror Wrap" 1 0 1 1
float HLY_TOP_IMAGE_MIRROR_WRAP = global.HLY_TOP_IMAGE_MIRROR_WRAP;





/////////////// CONSTANT TUNING SETTINGS ///////////////

#ifndef HBR_CORNER_SPREAD_FALLOFF
    #define HBR_CORNER_SPREAD_FALLOFF 100
#endif

#ifndef HBZ_GLASS_INNER_EDGE_SOFTNESS
    #define HBZ_GLASS_INNER_EDGE_SOFTNESS 0.3
#endif