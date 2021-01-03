/*   
hsm-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

// Screen Scale Required Parameters
#pragma parameter HSM_MEGA_BEZEL_TITLE					"[ --- HSM MEGA BEZEL  ALPHA.2020-12-15-0 --- ]_________________" 0 0 0 0

#pragma parameter HSM_RESOLUTION_DEBUG_ON				"      Show Resolution Info" 0 0 1 1
float HSM_RESOLUTION_DEBUG_ON = global.HSM_RESOLUTION_DEBUG_ON;

//---------------------------------------------------------------------------------------------------
//    FLIP & ROTATE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_FLIP_ROTATE_TITLE					"[ FLIP & ROTATE ]______________________________________________" 0 0 0 0

#pragma parameter HSM_FLIP_VIEWPORT_VERTICAL			"      Flip Viewport Vertical"  0 0 1 1
float HSM_FLIP_VIEWPORT_VERTICAL = global.HSM_FLIP_VIEWPORT_VERTICAL;

#pragma parameter HSM_FLIP_CORE_VERTICAL				"      Flip Core Image Vertical"  0 0 1 1
float HSM_FLIP_CORE_VERTICAL = global.HSM_FLIP_CORE_VERTICAL;

#pragma parameter HSM_ROTATE_CORE_IMAGE					"      Rotate CRT Tube"  0 0 1 1
float HSM_ROTATE_CORE_IMAGE = global.HSM_ROTATE_CORE_IMAGE;


//---------------------------------------------------------------------------------------------------
//    ASPECT RATIO
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_ASPECT_RATIO_TITLE					"[ ASPECT RATIO ]_______________________________________________" 0 0 0 0

#pragma parameter HSM_ASPECT_RATIO_ORIENTATION 				"      Orientation - Auto | Horizontal | Vertical"  0 0 2 1
float HSM_ASPECT_RATIO_ORIENTATION = global.HSM_ASPECT_RATIO_ORIENTATION;

#pragma parameter HSM_ASPECT_RATIO_MODE 					"      Type - Auto | Explicit | 4:3 | 3:2 | 16:9 | PAR | Full"  0 0 6 1
float HSM_ASPECT_RATIO_MODE = global.HSM_ASPECT_RATIO_MODE;

#pragma parameter HSM_ASPECT_RATIO_EXPLICIT					"      Explicit Aspect Ratio (Also Auto Ratio Fallback)"  1.3333 0 3 0.002
float HSM_ASPECT_RATIO_EXPLICIT = global.HSM_ASPECT_RATIO_EXPLICIT;


//---------------------------------------------------------------------------------------------------
//    SCALING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCALING_TITLE						"[ SCALING ]____________________________________________________" 0 0 0 0

#pragma parameter HSM_INT_SCALE_MODE 					"      Int Scale Mode - OFF | ShortAxis | BothAxes" 0 0 2 1
#define HSM_INT_SCALE_MODE global.HSM_INT_SCALE_MODE

#pragma parameter HSM_INT_SCALE_MULTIPLE_OFFSET 		"      Int Scale Multiple Offset" 0 -20 20 1
#define HSM_INT_SCALE_MULTIPLE_OFFSET global.HSM_INT_SCALE_MULTIPLE_OFFSET

#pragma parameter HSM_INT_SCALE_MULTIPLE_OFFSET_LONG 	"      Int Scale Multiple Offset on Long Axis" 0 -20 20 1
#define HSM_INT_SCALE_MULTIPLE_OFFSET_LONG global.HSM_INT_SCALE_MULTIPLE_OFFSET_LONG

#pragma parameter HSM_INT_SCALE_BORDER_MIN_HEIGHT 		"      Int Scale Border Min Height %" 5.5 -20 20 0.5
float HSM_INT_SCALE_BORDER_MIN_HEIGHT = global.HSM_INT_SCALE_BORDER_MIN_HEIGHT;

// Non integer scale is set to 82.97 so that cores which output 224px will have integer scale by default
// This is 8x integer scale at 3840x2160 and 6x integer scale at 1920x1080
#pragma parameter HSM_NON_INTEGER_SCALE 				"      Non-Integer Scale %" 82.97 1 200 0.2
float HSM_NON_INTEGER_SCALE = global.HSM_NON_INTEGER_SCALE;

#pragma parameter HSM_SNAP_TO_INT_SCALE_TOLERANCE 		"      Snap To Int-Scale Tolerance - Suggested 0.1" 0 0 3 0.01
float HSM_SNAP_TO_INT_SCALE_TOLERANCE = global.HSM_SNAP_TO_INT_SCALE_TOLERANCE;


//---------------------------------------------------------------------------------------------------
//    Position
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCREEN_POSITION_TITLE				"[ POSITION ]___________________________________________________" 0 0 0 0

#pragma parameter HSM_SCREEN_POSITION_X 				"      Position X" 0 -100 100 0.1
float HSM_SCREEN_POSITION_X = global.HSM_SCREEN_POSITION_X / 100;

#pragma parameter HSM_SCREEN_POSITION_Y 				"      Position Y" 0 -100 100 0.1
float HSM_SCREEN_POSITION_Y = -1 * global.HSM_SCREEN_POSITION_Y / 100;


//---------------------------------------------------------------------------------------------------
//    CROPPING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CROPPING_TITLE					"[ CROPPING ]___________________________________________________" 0 0 0 0

#pragma parameter HSM_CROP_OVERSCAN_TOP 				"      Crop Overscan Top" 0 -256 256 1
float HSM_CROP_OVERSCAN_TOP = global.HSM_CROP_OVERSCAN_TOP;

#pragma parameter HSM_CROP_OVERSCAN_BOTTOM 				"      Crop Overscan Bottom" 0 -256 256 1
float HSM_CROP_OVERSCAN_BOTTOM = global.HSM_CROP_OVERSCAN_BOTTOM;

#pragma parameter HSM_CROP_OVERSCAN_LEFT 				"      Crop Overscan Left" 0 -256 256 1
float HSM_CROP_OVERSCAN_LEFT = global.HSM_CROP_OVERSCAN_LEFT;

#pragma parameter HSM_CROP_OVERSCAN_RIGHT 				"      Crop Overscan Right" 0 -256 256 1
float HSM_CROP_OVERSCAN_RIGHT = global.HSM_CROP_OVERSCAN_RIGHT;


//---------------------------------------------------------------------------------------------------
//    CORE RES SAMPLING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SAMPLING_TITLE								"[ CORE RES SAMPLING ]__________________________________________" 0 0 0 0

#pragma parameter HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR			"      Scanline Direction Multiplier"  1 0.25 16 0.25
float HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR = global.HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR;

#pragma parameter HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR			"      Opposite Direction Multiplier"  1 0.25 16 0.25
float HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR = global.HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR;


//---------------------------------------------------------------------------------------------------
//    SCANLINES
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCANLINE_TITLE								"[ SCANLINES ]__________________________________________________" 0 0 0 0

#pragma parameter HSM_SCANLINE_DIRECTION 							"      Scanline Direction (GDV & Easymode) - Auto | Horiz | Vert"  0 0 2 1
float HSM_SCANLINE_DIRECTION = global.HSM_SCANLINE_DIRECTION;

#pragma parameter HSM_SCANLINE_INTERLACE_TRIGGER_RES 				"      Interlace and Fake Scanlines Trigger Res" 600.0 0.0 2000.0 25.0
#define HSM_SCANLINE_INTERLACE_TRIGGER_RES global.HSM_SCANLINE_INTERLACE_TRIGGER_RES

#pragma parameter HSM_SCANLINE_FAKE_SCANLINE_OPACITY 				"      Fake Scanline Opacity - Def 0.7" 0.7 0 1 0.05
#define HSM_SCANLINE_FAKE_SCANLINE_OPACITY global.HSM_SCANLINE_FAKE_SCANLINE_OPACITY

// #pragma parameter HSM_SCANLINE_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 	"[ SCREEN FX ]  Fake 240p Scanline Brightness Cutoff - Def 3" 3 0 10 0.05
#ifndef HSM_SCANLINE_FAKE_SCANLINE_BRIGHTNESS_CUTOFF
	#define HSM_SCANLINE_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 3
#endif


// //---------------------------------------------------------------------------------------------------
// //    SPLIT SCREEN
// //---------------------------------------------------------------------------------------------------
// #pragma parameter HSM_SPLITSCREEN_TITLE					"[ SPLIT SCREEN ]_______________________________________________" 0 0 0 0

// #pragma parameter HSM_SPLITSCREEN_ON					"      Split Screen ON - SPLIT SCREEN PRESET ONLY" 0 0 1 1
// float HSM_SPLITSCREEN_ON = global.HSM_SPLITSCREEN_ON;

// #pragma parameter HSM_SPLITSCREEN_AMOUNT				"      Split Thickness - SPLIT SCREEN PRESET ONLY" 0 0 256 2
// float HSM_SPLITSCREEN_AMOUNT = global.HSM_SPLITSCREEN_AMOUNT;

// // TODO add Split Position, also auto set position, catches for 3DS

// #pragma parameter HSM_SPLITSCREEN_CENTER_FILL_MODE		"      Center Fill Mode - 1:Bezel 2:Reflect 3:Blend 4:Fade" 0 0 6 1
// float HSM_SPLITSCREEN_CENTER_FILL_MODE = global.HSM_SPLITSCREEN_CENTER_FILL_MODE;


//---------------------------------------------------------------------------------------------------
//    CURVATURE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CURVATURE_TITLE					"[ CURVATURE ]__________________________________________________" 0 0 0 0

#pragma parameter HSM_CURVATURE_MODE 					"      Curvature Mode  -1:OFF 0:2D 1-2:3D Sphere, 3:3D Cylinder" 0 -1 3 1
float HSM_CURVATURE_MODE = global.HSM_CURVATURE_MODE;

#pragma parameter HSM_CURVATURE_2D_SCALE_LONG_AXIS 		"      2D Curvature on Long Axis - Def 1" 1 0 4 0.05
#define HSM_CURVATURE_2D_SCALE_LONG_AXIS global.HSM_CURVATURE_2D_SCALE_LONG_AXIS

#pragma parameter HSM_CURVATURE_2D_SCALE_SHORT_AXIS 	"      2D Curvature on Short Axis - Def 1" 1 0 4 0.05
#define HSM_CURVATURE_2D_SCALE_SHORT_AXIS global.HSM_CURVATURE_2D_SCALE_SHORT_AXIS

#pragma parameter HSM_CURVATURE_3D_RADIUS 				"      3D Radius" 2 0.16 1024 0.01
float HSM_CURVATURE_3D_RADIUS = global.HSM_CURVATURE_3D_RADIUS;

#pragma parameter HSM_CURVATURE_3D_VIEW_DIST 			"      3D View Distance - Def 1.5" 1.5 0.5 1024 0.05
float HSM_CURVATURE_3D_VIEW_DIST = global.HSM_CURVATURE_3D_VIEW_DIST;

#pragma parameter HSM_CURVATURE_3D_TILT_ANGLE_X 		"      3D Tilt Angle X" 0 -1.5 1.5 0.01
float HSM_CURVATURE_3D_TILT_ANGLE_X = global.HSM_CURVATURE_3D_TILT_ANGLE_X;

#pragma parameter HSM_CURVATURE_3D_TILT_ANGLE_Y 		"      3D Tilt Angle Y" 0 -1.5 1.5 0.01
float HSM_CURVATURE_3D_TILT_ANGLE_Y = global.HSM_CURVATURE_3D_TILT_ANGLE_Y;



//---------------------------------------------------------------------------------------------------
//    INTRO IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_INTRO_IMAGE_TITLE					"[ INTRO IMAGE ]________________________________________________" 0 0 0 0

#pragma parameter HSM_INTRO_IMAGE_BLEND_MODE        	"      Blend Mode - Off | Norm | Add | Mult"  1 0 3 1
#define HSM_INTRO_IMAGE_BLEND_MODE global.HSM_INTRO_IMAGE_BLEND_MODE

#pragma parameter HSM_INTRO_IMAGE_RES_X        			"      Res X"  128 0 640 2
#define HSM_INTRO_IMAGE_RES_X global.HSM_INTRO_IMAGE_RES_X

#pragma parameter HSM_INTRO_IMAGE_RES_Y        			"      Res Y"  128 0 640 2
#define HSM_INTRO_IMAGE_RES_Y global.HSM_INTRO_IMAGE_RES_Y



//---------------------------------------------------------------------------------------------------
//    PHOSPHOR PERSISTENCE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_PERSISTENCE_TITLE					"[ PHOSPHOR PERSISTENCE ]_______________________________________" 0 0 0 0

#pragma parameter HSM_PHOSPHOR_PERSISTENCE          	"      Phosphor Persistence - Positive:Neutral, Negative:Blue" 0 -1 1 0.05
#define HSM_PHOSPHOR_PERSISTENCE global.HSM_PHOSPHOR_PERSISTENCE



//---------------------------------------------------------------------------------------------------
//    COLOR & Persistence
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_COLOR_AND_PERSISTENCE_TITLE		"[ SCANLINES ON BLACK ]_________________________________________" 0 0 0 0

#pragma parameter HSM_COLOR_BLACK_LEVEL 				"      Black Level - Def -0.04" -0.04 -1 1 0.01
#define HSM_COLOR_BLACK_LEVEL global.HSM_COLOR_BLACK_LEVEL

#pragma parameter HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS	"      Negative Crop Brightness - Def 1.8" 1.8 0 100 0.2
#define HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS global.HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS

#pragma parameter HSM_COLOR_TITLE						"[ CRT GAMMA ]__________________________________________________" 0 0 0 0

#pragma parameter HSM_COLOR_CRT_GAMMA   				"      CRT Gamma (Linear to Gamma Space Encode) Def 2.2" 2.2 0.1 5 0.05
#define HSM_COLOR_CRT_GAMMA global.HSM_COLOR_CRT_GAMMA

#pragma parameter HSM_SCREENVIGNETTE_TITLE				"[ SCREEN VIGNETTE ]____________________________________________" 0 0 0 0

#pragma parameter HSM_SCREEN_VIGNETTE                	"      Screen Vignette Opacity" 0 0 1 0.01
#define HSM_SCREEN_VIGNETTE global.HSM_SCREEN_VIGNETTE

#pragma parameter HSM_SCREEN_VIGNETTE_IN_REFLECTION     "      Screen Vignette  Opacity in Reflection" 0 0 1 1
float HSM_SCREEN_VIGNETTE_IN_REFLECTION = global.HSM_SCREEN_VIGNETTE_IN_REFLECTION;



//---------------------------------------------------------------------------------------------------
//    SCREEN EDGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCREEN_EDGE_TITLE					"[ SCREEN EDGE ]________________________________________________" 0 0 0 0

#pragma parameter HSM_SCREEN_CORNER_RADIUS 				"      Corner Radius - Def 10" 10 0 70 1
#define HSM_SCREEN_CORNER_RADIUS global.HSM_SCREEN_CORNER_RADIUS

#pragma parameter HSM_SCREEN_EDGE_SHARPNESS 			"      Edge Sharpness - Def 0.4" 0.4 0 1 0.01
#define HSM_SCREEN_EDGE_SHARPNESS global.HSM_SCREEN_EDGE_SHARPNESS

#pragma parameter HSM_TUBE_BLACK_EDGE_THICKNESS 		"      Black Border Thickness - Def 1" 1 -2 8 0.05
#define HSM_TUBE_BLACK_EDGE_THICKNESS global.HSM_TUBE_BLACK_EDGE_THICKNESS



//---------------------------------------------------------------------------------------------------
//    TUBE IMAGES
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_TUBE_IMAGES_TITLE							"[ TUBE IMAGES ]________________________________________________" 0 0 0 0

#pragma parameter HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT  	"      Colored Gel Multiply Amount" 0 0 100 5
float HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT = global.HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT / 100;

#pragma parameter HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT  	"      Colored Gel Additive Amount" 0 0 100 0.05
float HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT = global.HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT / 100;

#pragma parameter HSM_TUBE_STATIC_REFLECTION_IMAGE_OPACITY  			"      Tube Static Reflection Opacity" 0 0 100 0.1
float HSM_TUBE_STATIC_REFLECTION_IMAGE_OPACITY = global.HSM_TUBE_STATIC_REFLECTION_IMAGE_OPACITY / 100;

#pragma parameter HSM_TUBE_STATIC_REFLECTION_IMAGE_SCALE  				"      Tube Static Reflection Scale" 110 0 1000 1
float HSM_TUBE_STATIC_REFLECTION_IMAGE_SCALE = global.HSM_TUBE_STATIC_REFLECTION_IMAGE_SCALE / 100;

// #pragma parameter HSM_TUBE_STATIC_REFLECTION_IMAGE_DITHERING_SAMPLES  "[ TUBE IMAGES ]   Tube Static Reflection Noise Samples (Reduces Banding)" 0 0 10 1
// float HSM_TUBE_STATIC_REFLECTION_IMAGE_DITHERING_SAMPLES = global.HSM_TUBE_STATIC_REFLECTION_IMAGE_DITHERING_SAMPLES;

#pragma parameter HSM_CRTLASTPASS_TITLE							"[ CRT IS LAST PASS ]___________________________________________" 0 0 0 0

#pragma parameter HSM_CRT_IS_LAST_PASS 							"      CRT is Last Pass" 0 0 1 1
#define HSM_CRT_IS_LAST_PASS global.HSM_CRT_IS_LAST_PASS



//---------------------------------------------------------------------------------------------------
//    Tube / Inner Bezel Curvature
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BEZEL_TITLE								"[ BEZEL ]______________________________________________________" 0 0 0 0

#pragma parameter HSM_BZL_INNER_CURVATURE_SCALE 				"      Inner Curvature Scale" 1 0 20 0.1
#define HSM_BZL_INNER_CURVATURE_SCALE global.HSM_BZL_INNER_CURVATURE_SCALE

#ifndef HSM_SCREENFX_SCANLINE_RES
	#define HSM_SCREENFX_SCANLINE_RES 240
#endif

#ifndef HSM_DEFAULT_CRT_GAMMA
	#define HSM_DEFAULT_CRT_GAMMA 2.4
#endif

#ifndef HSM_DEFAULT_SRGB_GAMMA
	#define HSM_DEFAULT_SRGB_GAMMA 2.2
#endif


