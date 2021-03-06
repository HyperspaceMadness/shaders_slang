/*   
hsm-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

// Screen Scale Required Parameters
#pragma parameter HSM_MEGA_BEZEL_TITLE								"[ --- HSM MEGA BEZEL 0.9.018 2021-06-19 --- ]" 0 0 0.01 0.01

#pragma parameter HSM_RESOLUTION_DEBUG_ON							"          Show Resolution Info" 0 0 1 1
float HSM_RESOLUTION_DEBUG_ON = global.HSM_RESOLUTION_DEBUG_ON;

//---------------------------------------------------------------------------------------------------
//    FLIP & ROTATE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_FLIP_ROTATE_TITLE								"[ FLIP & ROTATE ]:" 0 0 0.01 0.01

#pragma parameter HSM_FLIP_VIEWPORT_VERTICAL						"          Flip Viewport Vertical"  0 0 1 1
float HSM_FLIP_VIEWPORT_VERTICAL = global.HSM_FLIP_VIEWPORT_VERTICAL;

#pragma parameter HSM_FLIP_CORE_VERTICAL							"          Flip Core Image Vertical"  0 0 1 1
float HSM_FLIP_CORE_VERTICAL = global.HSM_FLIP_CORE_VERTICAL;

#pragma parameter HSM_FLIP_CORE_HORIZONTAL							"          Flip Core Image Horizontal"  0 0 1 1
float HSM_FLIP_CORE_HORIZONTAL = global.HSM_FLIP_CORE_HORIZONTAL;

#pragma parameter HSM_ROTATE_CORE_IMAGE								"          Rotate CRT Tube"  0 0 1 1
float HSM_ROTATE_CORE_IMAGE = global.HSM_ROTATE_CORE_IMAGE;


//---------------------------------------------------------------------------------------------------
//    ASPECT RATIO
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_ASPECT_RATIO_TITLE							"[ ASPECT RATIO ]:" 0 0 0.01 0.01

#pragma parameter HSM_ASPECT_RATIO_ORIENTATION 						"          Orientation - Auto | Horizontal | Vertical"  0 0 2 1
float HSM_ASPECT_RATIO_ORIENTATION = global.HSM_ASPECT_RATIO_ORIENTATION;

#pragma parameter HSM_ASPECT_RATIO_MODE 							"         Type - Auto | Explicit | 4:3 | 3:2 | 16:9 | PAR | Full"  0 0 6 1
float HSM_ASPECT_RATIO_MODE = global.HSM_ASPECT_RATIO_MODE;

#pragma parameter HSM_ASPECT_RATIO_EXPLICIT							"          Explicit Aspect Ratio (Also Auto Ratio Fallback)"  1.3333 0 3 0.002
float HSM_ASPECT_RATIO_EXPLICIT = global.HSM_ASPECT_RATIO_EXPLICIT;


//---------------------------------------------------------------------------------------------------
//    SCALING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCALING_TITLE									"[ SCALING ]:" 0 0 0.01 0.01

#pragma parameter HSM_INT_SCALE_MODE 								"          Int Scale Mode - OFF | ShortAxis | BothAxes" 0 0 2 1
#define HSM_INT_SCALE_MODE global.HSM_INT_SCALE_MODE

#pragma parameter HSM_INT_SCALE_MULTIPLE_OFFSET 					"          Int Scale Multiple Offset" 0 -20 20 1
#define HSM_INT_SCALE_MULTIPLE_OFFSET global.HSM_INT_SCALE_MULTIPLE_OFFSET

#pragma parameter HSM_INT_SCALE_MULTIPLE_OFFSET_LONG 				"          Int Scale Multiple Offset on Long Axis" 0 -20 20 1
#define HSM_INT_SCALE_MULTIPLE_OFFSET_LONG global.HSM_INT_SCALE_MULTIPLE_OFFSET_LONG

#pragma parameter HSM_INT_SCALE_BORDER_MIN_HEIGHT 					"          Int Scale Border Min Height %" 5.5 -20 20 0.5
float HSM_INT_SCALE_BORDER_MIN_HEIGHT = global.HSM_INT_SCALE_BORDER_MIN_HEIGHT;

// Non integer scale is set to 82.97 so that cores which output 224px will have integer scale by default
// This is 8x integer scale at 3840x2160 and 6x integer scale at 1920x1080
#pragma parameter HSM_NON_INTEGER_SCALE 							"          Non-Integer Scale %" 82.97 1 200 0.2
float HSM_NON_INTEGER_SCALE = global.HSM_NON_INTEGER_SCALE;

//---------------------------------------------------------------------------------------------------
//    Extended Scale
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCREEN_EXTENDED_SCALE_TITLE					"[ EXTENDED SCALING ]:" 0 0 0.01 0.01

#pragma parameter USE_IMAGE_FOR_PLACEMENT 							"          Use Image For Placement (Scale & Y Pos)" 0 0 1 1
float USE_IMAGE_FOR_PLACEMENT = global.USE_IMAGE_FOR_PLACEMENT;

#pragma parameter HSM_NON_INTEGER_SCALE_OFFSET 						"          Non-Integer Scale Offset" 100 5 400 0.1
float HSM_NON_INTEGER_SCALE_OFFSET = global.HSM_NON_INTEGER_SCALE_OFFSET / 100;

#pragma parameter HSM_SNAP_TO_INT_SCALE_TOLERANCE 					"          Snap To Int-Scale Tolerance - Suggested 0.1" 0 0 3 0.01
float HSM_SNAP_TO_INT_SCALE_TOLERANCE = global.HSM_SNAP_TO_INT_SCALE_TOLERANCE;

//---------------------------------------------------------------------------------------------------
//    Position
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCREEN_POSITION_TITLE							"[ POSITION OFFSET ]:" 0 0 0.01 0.01

#pragma parameter HSM_SCREEN_POSITION_X 							"          Position X" 0 -1000 1000 1
float HSM_SCREEN_POSITION_X = global.HSM_SCREEN_POSITION_X / 1000;

#pragma parameter HSM_SCREEN_POSITION_Y 							"          Position Y" 0 -1000 1000 1
float HSM_SCREEN_POSITION_Y = -1 * global.HSM_SCREEN_POSITION_Y / 1000;


//---------------------------------------------------------------------------------------------------
//    CROPPING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CROPPING_TITLE								"[ CROPPING ]:" 0 0 0.01 0.01

#pragma parameter HSM_CROP_MODE 									"          Crop Mode  -  OFF | CROP BLACK ONLY | CROP ANY" 2 0 2 1
float HSM_CROP_MODE = global.HSM_CROP_MODE;

#pragma parameter HSM_CROP_PERCENT_ZOOM								"          Crop Zoom %" 0 0 100 0.5
float HSM_CROP_PERCENT_ZOOM = global.HSM_CROP_PERCENT_ZOOM / 100;

#pragma parameter HSM_CROP_PERCENT_TOP 								"          Crop Top %" 0 0 100 0.1
float HSM_CROP_PERCENT_TOP = global.HSM_CROP_PERCENT_TOP / 100 + HSM_CROP_PERCENT_ZOOM;

#pragma parameter HSM_CROP_PERCENT_BOTTOM 							"          Crop Bottom %" 0 0 100 0.1
float HSM_CROP_PERCENT_BOTTOM = global.HSM_CROP_PERCENT_BOTTOM / 100 + HSM_CROP_PERCENT_ZOOM;

#pragma parameter HSM_CROP_PERCENT_LEFT 							"          Crop Left %" 0 0 100 0.1
float HSM_CROP_PERCENT_LEFT = global.HSM_CROP_PERCENT_LEFT / 100 + HSM_CROP_PERCENT_ZOOM;

#pragma parameter HSM_CROP_PERCENT_RIGHT 							"          Crop Right %" 0 0 100 0.1
float HSM_CROP_PERCENT_RIGHT = global.HSM_CROP_PERCENT_RIGHT / 100 + HSM_CROP_PERCENT_ZOOM;

#pragma parameter HSM_CROP_BLACK_THRESHOLD 							"          Black Threshold for 'CROP BLACK ONLY'" 0 0 100 1
float HSM_CROP_BLACK_THRESHOLD = global.HSM_CROP_BLACK_THRESHOLD / 100;


//---------------------------------------------------------------------------------------------------
//    SCANLINES
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCANLINE_TITLE								"[ SCANLINE DIRECTION ]:" 0 0 0.01 0.01

#pragma parameter HSM_SCANLINE_DIRECTION 							"          Scanline Direction - Auto | Horiz | Vert"  0 0 2 1
float HSM_SCANLINE_DIRECTION = global.HSM_SCANLINE_DIRECTION;


//---------------------------------------------------------------------------------------------------
//    CORE RES SAMPLING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SAMPLING_TITLE								"[ CORE RES SAMPLING]:" 0 0 0.01 0.01

#pragma parameter HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR			"          Scanline Dir Multiplier (X-Prescale for H Scanline)"  100 50 1600 50
float HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR = global.HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR / 100;

#pragma parameter HSM_DOWNSAMPLE_BLUR_SCANLINE_DIR 					"          Scanline Dir Downsample Blur" 0 0 200 10
float HSM_DOWNSAMPLE_BLUR_SCANLINE_DIR = global.HSM_DOWNSAMPLE_BLUR_SCANLINE_DIR / 100;

#pragma parameter HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR			"          Opposite Dir Multiplier (Y Downsample for H Scanline)"  100 25 1600 25
float HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR = global.HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR / 100;

#pragma parameter HSM_DOWNSAMPLE_BLUR_OPPOSITE_DIR 					"          Opposite Dir Downsample Blur" 0 0 200 10
float HSM_DOWNSAMPLE_BLUR_OPPOSITE_DIR = global.HSM_DOWNSAMPLE_BLUR_OPPOSITE_DIR / 100;

//---------------------------------------------------------------------------------------------------
//    INTERLACING
//---------------------------------------------------------------------------------------------------

#pragma parameter HSM_INTERLACE_TITLE								"[ INTERLACING From Guest.r :) ]:" 0 0 0.01 0.01

#pragma parameter HSM_INTERLACE_TRIGGER_RES 						"          Interlacing and Fake Scanlines Trigger Res" 600 100 2000 25
#define HSM_INTERLACE_TRIGGER_RES global.HSM_INTERLACE_TRIGGER_RES

#pragma parameter HSM_INTERLACE_MODE 								"         Interlacing Mode: OFF | Normal 1-3 | Interpolation 4-5" 4 0.0 5.0 1.0
#define HSM_INTERLACE_MODE global.HSM_INTERLACE_MODE

#pragma parameter HSM_INTERLACE_EFFECT_SMOOTHNESS_INTERS 					"          Interlacing Effect Smoothness" 0 0 100 10
#define HSM_INTERLACE_EFFECT_SMOOTHNESS_INTERS global.HSM_INTERLACE_EFFECT_SMOOTHNESS_INTERS / 200

#pragma parameter HSM_INTERLACE_SCANLINE_EFFECT 					"          Interlacing Scanline Effect" 20 0 100 5
#define HSM_INTERLACE_SCANLINE_EFFECT global.HSM_INTERLACE_SCANLINE_EFFECT / 100

#pragma parameter GDV_INTERLACE_SCANLINE_SATURATION 				"          Interlacing (Scanline) Saturation" 40 0 100 5
#define GDV_INTERLACE_SCANLINE_SATURATION global.GDV_INTERLACE_SCANLINE_SATURATION / 100


//---------------------------------------------------------------------------------------------------
//    FAKE SCANLINES
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_FAKE_SCANLINE_TITLE							"[ FAKE SCANLINES ]" 0 0 0.01 0.01

#pragma parameter HSM_FAKE_SCANLINE_OPACITY 						"          Opacity - Def 70" 0 0 100 5
#define HSM_FAKE_SCANLINE_OPACITY global.HSM_FAKE_SCANLINE_OPACITY / 100

#pragma parameter HSM_FAKE_SCANLINE_RES 							"          Scan Resolution" 240 0 480 8
#define HSM_FAKE_SCANLINE_RES global.HSM_FAKE_SCANLINE_RES

#pragma parameter HSM_FAKE_SCANLINE_INT_SCALE 						"          Int Scale Scanlines" 1 0 1 1
#define HSM_FAKE_SCANLINE_INT_SCALE global.HSM_FAKE_SCANLINE_INT_SCALE

#pragma parameter HSM_FAKE_SCANLINE_ROLL 							"          Rolling Scanline" 0 -100 100 5
#define HSM_FAKE_SCANLINE_ROLL global.HSM_FAKE_SCANLINE_ROLL / 100

// #pragma parameter HSM_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 	"[ SCREEN FX ]  Fake 240p Scanline Brightness Cutoff - Def 3" 3 0 10 0.05
#ifndef HSM_FAKE_SCANLINE_BRIGHTNESS_CUTOFF
	#define HSM_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 3
#endif


//---------------------------------------------------------------------------------------------------
//    DUAL SCREEN
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_DUALSCREEN_TITLE								"[ DUAL SCREEN ]:" 0 0 0.01 0.01

#pragma parameter HSM_DUALSCREEN_MODE								"          Dual Screen Mode - OFF | VERTICAL | HORIZONTAL" 0 0 2 1
float HSM_DUALSCREEN_MODE = global.HSM_DUALSCREEN_MODE;

#pragma parameter HSM_DUALSCREEN_CORE_IMAGE_SPLIT_MODE				"          Core Image Split Mode  - AUTO | VERTICAL | HORIZONTAL" 1 0 2 1
float HSM_DUALSCREEN_CORE_IMAGE_SPLIT_MODE = global.HSM_DUALSCREEN_CORE_IMAGE_SPLIT_MODE;

#pragma parameter HSM_DUALSCREEN_CORE_IMAGE_SWAP_SCREENS			"          Core Image Swap Screen Content" 0 0 1 1
float HSM_DUALSCREEN_CORE_IMAGE_SWAP_SCREENS = global.HSM_DUALSCREEN_CORE_IMAGE_SWAP_SCREENS;

#pragma parameter HSM_DUALSCREEN_CORE_IMAGE_SPLIT_OFFSET			"          Core Image Split Offset" 0 -128 128 1
float HSM_DUALSCREEN_CORE_IMAGE_SPLIT_OFFSET = global.HSM_DUALSCREEN_CORE_IMAGE_SPLIT_OFFSET;

#pragma parameter HSM_DUALSCREEN_2ND_SCREEN_SIDES_CROP				"          Crop % from Edges of 2nd Screen" 0 0 100 0.1
float HSM_DUALSCREEN_2ND_SCREEN_SIDES_CROP = global.HSM_DUALSCREEN_2ND_SCREEN_SIDES_CROP / 100;

#pragma parameter HSM_DUALSCREEN_VIEWPORT_SPLIT_LOCATION			"          Viewport Split Offset" 0 -500 500 1
float HSM_DUALSCREEN_VIEWPORT_SPLIT_LOCATION = global.HSM_DUALSCREEN_VIEWPORT_SPLIT_LOCATION / 1000;

#pragma parameter HSM_DUALSCREEN_SHIFT_POSITION_WITH_SCALE			"          Scale Screens from Center of Split" 1 0 1 1
float HSM_DUALSCREEN_SHIFT_POSITION_WITH_SCALE = global.HSM_DUALSCREEN_SHIFT_POSITION_WITH_SCALE;

#pragma parameter HSM_DUALSCREEN_POSITION_OFFSET_BETWEEN_SCREENS	"          Position Offset Between Screens" 0 -250 250 0.2
float HSM_DUALSCREEN_POSITION_OFFSET_BETWEEN_SCREENS = global.HSM_DUALSCREEN_POSITION_OFFSET_BETWEEN_SCREENS / 1000;

#pragma parameter HSM_DUALSCREEN_2ND_SCREEN_ASPECT_RATIO_MODE		"        2nd Screen Aspect Ratio Mode - Same as 1st Screen | PAR" 0 0 1 1
float HSM_DUALSCREEN_2ND_SCREEN_ASPECT_RATIO_MODE = global.HSM_DUALSCREEN_2ND_SCREEN_ASPECT_RATIO_MODE;

#pragma parameter HSM_DUALSCREEN_2ND_SCREEN_INDEPENDENT_SCALE		"          2nd Screen Use Independent Scale" 0 0 1 1
float HSM_DUALSCREEN_2ND_SCREEN_INDEPENDENT_SCALE = global.HSM_DUALSCREEN_2ND_SCREEN_INDEPENDENT_SCALE;

#pragma parameter HSM_DUALSCREEN_2ND_SCREEN_SCALE_OFFSET			"          2nd Screen Scale Offset" 100 1 500 0.5
float HSM_DUALSCREEN_2ND_SCREEN_SCALE_OFFSET = global.HSM_DUALSCREEN_2ND_SCREEN_SCALE_OFFSET / 100;

#pragma parameter HSM_DUALSCREEN_2ND_SCREEN_POS_X					"          2nd Screen Pos X" 0 -500 500 1
float HSM_DUALSCREEN_2ND_SCREEN_POS_X = global.HSM_DUALSCREEN_2ND_SCREEN_POS_X / 1000;

#pragma parameter HSM_DUALSCREEN_2ND_SCREEN_POS_Y					"          2nd Screen Pos Y" 0 -500 500 1
float HSM_DUALSCREEN_2ND_SCREEN_POS_Y = global.HSM_DUALSCREEN_2ND_SCREEN_POS_Y / 1000;


//---------------------------------------------------------------------------------------------------
//    CURVATURE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CURVATURE_TITLE								"[ CURVATURE ]:" 0 0 0.01 0.01

#pragma parameter HSM_CURVATURE_MODE 								"          Curvature Mode  -1:OFF 0:2D 1-2:3D Sphere, 3:3D Cyl" 0 -1 3 1
float HSM_CURVATURE_MODE = global.HSM_CURVATURE_MODE;

#pragma parameter HSM_CURVATURE_2D_SCALE_LONG_AXIS 					"          2D Curvature on Long Axis" 100 5 400 5
#define HSM_CURVATURE_2D_SCALE_LONG_AXIS global.HSM_CURVATURE_2D_SCALE_LONG_AXIS / 100

#pragma parameter HSM_CURVATURE_2D_SCALE_SHORT_AXIS 				"          2D Curvature on Short Axis" 100 5 400 5
#define HSM_CURVATURE_2D_SCALE_SHORT_AXIS global.HSM_CURVATURE_2D_SCALE_SHORT_AXIS / 100

#pragma parameter HSM_CURVATURE_3D_RADIUS 							"          3D Radius" 200 16 102400 1
float HSM_CURVATURE_3D_RADIUS = global.HSM_CURVATURE_3D_RADIUS / 100;

#pragma parameter HSM_CURVATURE_3D_VIEW_DIST 						"          3D View Distance - Def 150" 150 50 102400 5
float HSM_CURVATURE_3D_VIEW_DIST = global.HSM_CURVATURE_3D_VIEW_DIST / 100;

#pragma parameter HSM_CURVATURE_3D_TILT_ANGLE_X 					"          3D Tilt Angle X" 0 -120 120 1
float HSM_CURVATURE_3D_TILT_ANGLE_X = global.HSM_CURVATURE_3D_TILT_ANGLE_X / 100;

#pragma parameter HSM_CURVATURE_3D_TILT_ANGLE_Y 					"          3D Tilt Angle Y" 0 -120 120 1
float HSM_CURVATURE_3D_TILT_ANGLE_Y = global.HSM_CURVATURE_3D_TILT_ANGLE_Y / 100;


//---------------------------------------------------------------------------------------------------
//    ANTI-FLICKER
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_ANTI_FLICKER_TITLE							"[ ANTI-FLICKER ]:" 0 0 0.01 0.01

#pragma parameter HSM_ANTI_FLICKER_ON 								"          Anti-Flicker ON" 0 0 1 1
#define HSM_ANTI_FLICKER_ON global.HSM_ANTI_FLICKER_ON

#pragma parameter HSM_ANTI_FLICKER_THRESHOLD 						"          Luma Difference Threshold" 25 0 100 5
#define HSM_ANTI_FLICKER_THRESHOLD global.HSM_ANTI_FLICKER_THRESHOLD / 100


//---------------------------------------------------------------------------------------------------
//    CRT vs ORIGINAL A/B TESTING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CRTRAWABTEST_TITLE							"[ CRT vs ORIGINAL A/B COMPARE ]:" 0 0 0.01 0.01

#pragma parameter HSM_CRT_ORIGINAL_AB_COMPARE_ON   					"          Compare ON" 0 0 1 1
float HSM_CRT_ORIGINAL_AB_COMPARE_ON = global.HSM_CRT_ORIGINAL_AB_COMPARE_ON;

#pragma parameter HSM_CRT_ORIGINAL_AB_COMPARE_SPLIT_POSITION   		"          Splitscreen Position" 50 0 100 0.2
float HSM_CRT_ORIGINAL_AB_COMPARE_SPLIT_POSITION = global.HSM_CRT_ORIGINAL_AB_COMPARE_SPLIT_POSITION / 100;


//---------------------------------------------------------------------------------------------------
//    Black Level
//---------------------------------------------------------------------------------------------------
// #pragma parameter HSM_COLOR_AND_PERSISTENCE_TITLE				"[ SCANLINES ON BLACK ]:" 0 0 0.01 0.01

// #pragma parameter HSM_COLOR_BLACK_LEVEL 							"          Black Level - Def -4" -4 -100 100 1
// #define HSM_COLOR_BLACK_LEVEL global.HSM_COLOR_BLACK_LEVEL / 100

// Not in use because negative cropping is disabled
// #pragma parameter HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS				"          Negative Crop Brightness - Def 1.8" 1.8 0 100 0.2
// #define HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS global.HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS

// Guest Color Profiles
// [COLOR]  CRT Profile - Overall color adjustment to match particular standards or example crts
//         -1 - No adjustment
//         0 - SRGB (Standard color space for computer monitors)
//         1 - BVM
//         2 - P22 (P22 common phosphor coloring)
//         3 - SMPTE-C - North american color standards in the 80s?
//         4 - Philips Monitor color
//         5 - Trinitron Monitor
//         6 - LUT colors from Torridgristle

// [COLOR]  Color Space
//         0 - SRGB
//         1 - DCI
//         2 - Adobe
//         3 - Rec. 2020

#pragma parameter HSM_BRIGHTNESS_GAMMA_TITLE						"[ CRT BRIGHTNESS & GAMMA ]:" 0 0 0.01 0.01

#pragma parameter HSM_GAMMA_IN_LINEARIZE   							"          Gamma In (Gamma to Linear Space Decode) Def 2.4" 2.4 0.1 5 0.05
#define HSM_GAMMA_IN_LINEARIZE global.HSM_GAMMA_IN_LINEARIZE

#pragma parameter HSM_GAMMA_OUT_CRT   								"          CRT Gamma Out (Linear to Gamma Space Encode) Def 2.4" 2.4 0.1 5 0.05
#define HSM_GAMMA_OUT_CRT global.HSM_GAMMA_OUT_CRT

#pragma parameter HSM_POST_CRT_BRIGHTNESS  							"          CRT Brightness" 100 1 500 1
#define HSM_POST_CRT_BRIGHTNESS global.HSM_POST_CRT_BRIGHTNESS / 100

// #pragma parameter HSM_SCREEN_VIGNETTE_TITLE							"[ SCREEN VIGNETTE ]:" 0 0 0.01 0.01

// #pragma parameter HSM_SCREEN_VIGNETTE                				"          Screen Vignette Opacity" 0 0 100 1
// #define HSM_SCREEN_VIGNETTE global.HSM_SCREEN_VIGNETTE / 200


#pragma parameter HSM_REFLECTIONAPPEARANCE_TITLE					"[ REFLECTION TRANSFORM ]:" 0 0 0.01 0.01

// #pragma parameter HSM_SCREEN_VIGNETTE_IN_REFLECTION     			"          Screen Vignette Opacity in Reflection" 100 0 100 1
// float HSM_SCREEN_VIGNETTE_IN_REFLECTION = global.HSM_SCREEN_VIGNETTE_IN_REFLECTION / 100;

#pragma parameter HSM_SCREEN_REFLECTION_SCALE     					"          Screen Reflection Scale" 100 1 300 1
float HSM_SCREEN_REFLECTION_SCALE = global.HSM_SCREEN_REFLECTION_SCALE / 100;

#pragma parameter HSM_SCREEN_REFLECTION_POS_X     					"          Screen Reflection Pos X" 0 -100 100 1
float HSM_SCREEN_REFLECTION_POS_X = global.HSM_SCREEN_REFLECTION_POS_X / 600;

#pragma parameter HSM_SCREEN_REFLECTION_POS_Y     					"          Screen Reflection Pos Y" 0 -100 100 1
float HSM_SCREEN_REFLECTION_POS_Y = global.HSM_SCREEN_REFLECTION_POS_Y / 600;


//---------------------------------------------------------------------------------------------------
//    TUBE IMAGES
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_TUBE_IMAGES_TITLE								"[ COLORED GEL IMAGE ]:" 0 0 0.01 0.01

#pragma parameter HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT  		"          Colored Gel Multiply Amount" 0 0 100 1
float HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT = global.HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT / 100;

#pragma parameter HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT  		"          Colored Gel Additive Amount" 0 0 100 0.05
float HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT = global.HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT / 100;

#pragma parameter HSM_TUBE_COLORED_GEL_IMAGE_NORMAL_AMOUNT  		"          Colored Gel Normal Amount" 0 0 100 1
float HSM_TUBE_COLORED_GEL_IMAGE_NORMAL_AMOUNT = global.HSM_TUBE_COLORED_GEL_IMAGE_NORMAL_AMOUNT / 100;


//---------------------------------------------------------------------------------------------------
//    TUBE IMAGES
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_TUBE_STATIC_REFLECTION_IMAGE_TITLE			"[ TUBE STATIC REFLECTION IMAGE ]:" 0 0 0.01 0.01

#pragma parameter HSM_TUBE_STATIC_REFLECTION_IMAGE_OPACITY  		"          Tube Static Reflection Opacity" 0 0 100 0.1
float HSM_TUBE_STATIC_REFLECTION_IMAGE_OPACITY = global.HSM_TUBE_STATIC_REFLECTION_IMAGE_OPACITY / 100;

#pragma parameter HSM_TUBE_STATIC_REFLECTION_IMAGE_SCALE  			"          Tube Static Reflection Scale" 110 0 1000 1
float HSM_TUBE_STATIC_REFLECTION_IMAGE_SCALE = global.HSM_TUBE_STATIC_REFLECTION_IMAGE_SCALE / 100;

// #pragma parameter HSM_TUBE_STATIC_REFLECTION_IMAGE_DITHERING_SAMPLES  "[ TUBE IMAGES ]   Tube Static Reflection Noise Samples (Reduces Banding)" 0 0 10 1
// float HSM_TUBE_STATIC_REFLECTION_IMAGE_DITHERING_SAMPLES = global.HSM_TUBE_STATIC_REFLECTION_IMAGE_DITHERING_SAMPLES;


//---------------------------------------------------------------------------------------------------
//    SCREEN BLACK EDGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCREEN_EDGE_TITLE								"[ SCREEN BLACK EDGE ]:" 0 0 0.01 0.01

#pragma parameter HSM_SCREEN_CORNER_RADIUS 							"          Black Edge Corner Radius - Def 10" 10 4 500 2
#define HSM_SCREEN_CORNER_RADIUS global.HSM_SCREEN_CORNER_RADIUS

#pragma parameter HSM_SCREEN_EDGE_SHARPNESS 						"          Black Edge Sharpness - Def 40" 40 0 90 1
#define HSM_SCREEN_EDGE_SHARPNESS global.HSM_SCREEN_EDGE_SHARPNESS / 100

#pragma parameter HSM_TUBE_BLACK_EDGE_CURVATURE_SCALE 				"          Black Edge Curvature Scale Multiplier" 100 100 8000 10
#define HSM_TUBE_BLACK_EDGE_CURVATURE_SCALE global.HSM_TUBE_BLACK_EDGE_CURVATURE_SCALE / 100

#pragma parameter HSM_TUBE_BLACK_EDGE_THICKNESS 					"          Black Edge Thickness" 100 -800 800 5
#define HSM_TUBE_BLACK_EDGE_THICKNESS global.HSM_TUBE_BLACK_EDGE_THICKNESS / 100


//---------------------------------------------------------------------------------------------------
//    Bezel Independent Scale
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BEZEL_INDEPENDENT_TITLE						"[ BEZEL INDEPENDENT SCALE & CURVATURE ]:" 0 0 0.01 0.01

#pragma parameter HSM_BZL_USE_INDEPENDENT_SCALE 					"          Use Independent Scale" 0 0 1 1
#define HSM_BZL_USE_INDEPENDENT_SCALE global.HSM_BZL_USE_INDEPENDENT_SCALE

#pragma parameter HSM_BZL_INDEPENDENT_SCALE 						"          Independent Scale (When scale from image is not used)" 82.97 1 200 0.1
#define HSM_BZL_INDEPENDENT_SCALE global.HSM_BZL_INDEPENDENT_SCALE / 100

#pragma parameter HSM_BZL_USE_INDEPENDENT_CURVATURE 				"          Use Independent Curvature" 0 0 1 1
#define HSM_BZL_USE_INDEPENDENT_CURVATURE global.HSM_BZL_USE_INDEPENDENT_CURVATURE

#pragma parameter HSM_BZL_INDEPENDENT_CURVATURE_SCALE_LONG_AXIS 	"          Independent Curvature X" 100 0 400 5
#define HSM_BZL_INDEPENDENT_CURVATURE_SCALE_LONG_AXIS global.HSM_BZL_INDEPENDENT_CURVATURE_SCALE_LONG_AXIS / 100

#pragma parameter HSM_BZL_INDEPENDENT_CURVATURE_SCALE_SHORT_AXIS 	"          Independent Curvature Y" 100 0 400 5
#define HSM_BZL_INDEPENDENT_CURVATURE_SCALE_SHORT_AXIS global.HSM_BZL_INDEPENDENT_CURVATURE_SCALE_SHORT_AXIS / 100


//---------------------------------------------------------------------------------------------------
//    Bezel General
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BEZEL_GENERAL_TITLE							"[ BEZEL GENERAL ]:" 0 0 0.01 0.01 

#pragma parameter HSM_BZL_SCALE_OFFSET 								"          Scale Offset" 100 1 200 0.1
#define HSM_BZL_SCALE_OFFSET global.HSM_BZL_SCALE_OFFSET / 100

#pragma parameter HSM_BZL_INNER_CURVATURE_SCALE 					"          Inner Curvature Scale Multiplier" 100 0 8000 10
#define HSM_BZL_INNER_CURVATURE_SCALE global.HSM_BZL_INNER_CURVATURE_SCALE / 100

#pragma parameter HSM_BZL_INNER_CORNER_RADIUS_SCALE	    			"          Inner Corner Radius Scale - Def 50" 50 0 8000 1
float HSM_BZL_INNER_CORNER_RADIUS_SCALE = global.HSM_BZL_INNER_CORNER_RADIUS_SCALE / 100;

#ifndef HSM_FAKE_SCANLINE_RES
	#define HSM_FAKE_SCANLINE_RES 240
#endif

#ifndef HSM_DEFAULT_CRT_GAMMA
	#define HSM_DEFAULT_CRT_GAMMA 2.4
#endif

#ifndef HSM_DEFAULT_SRGB_GAMMA
	#define HSM_DEFAULT_SRGB_GAMMA 2.2
#endif


