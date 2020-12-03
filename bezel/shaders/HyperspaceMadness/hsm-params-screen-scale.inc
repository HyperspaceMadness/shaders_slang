/*   
hsm-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

// Screen Scale Required Parameters
#pragma parameter HSM_MEGA_BEZEL_TITLE					"_____[ HSM MEGA BEZEL  ALPHA.2020-11-15-0 ]____________________" 0 0 0 0

#pragma parameter HSM_RESOLUTION_DEBUG_ON					"[ DEBUG ]  Show Resolution Info" 0 0 1 1
float HSM_RESOLUTION_DEBUG_ON = global.HSM_RESOLUTION_DEBUG_ON;

//---------------------------------------------------------------------------------------------------
//    FLIP & ROTATE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_FLIP_ROTATE_TITLE					"_____[ FLIP & ROTATE ]_________________________________________" 0 0 0 0

#pragma parameter HSM_FLIP_VIEWPORT_AND_CORE_VERTICAL	"[ VERTICAL FLIP ]  Flip Vertical - For 3D Cores"  0 0 1 1
float HSM_FLIP_VIEWPORT_AND_CORE_VERTICAL = global.HSM_FLIP_VIEWPORT_AND_CORE_VERTICAL;

#pragma parameter HSM_ROTATE_CORE_IMAGE					"[ ROTATE ]  Rotate CRT Tube"  0 0 1 1
float HSM_ROTATE_CORE_IMAGE = global.HSM_ROTATE_CORE_IMAGE;


//---------------------------------------------------------------------------------------------------
//    ASPECT RATIO
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_ASPECT_RATIO_TITLE					"_____[ ASPECT RATIO ]__________________________________________" 0 0 0 0

#pragma parameter HSM_ASPECT_RATIO_ORIENTATION 			"[ ASPECT ]  Orientation - Auto | Horizontal | Vertical"  0 0 2 1
float HSM_ASPECT_RATIO_ORIENTATION = global.HSM_ASPECT_RATIO_ORIENTATION;

#pragma parameter HSM_ASPECT_RATIO_MODE 					"[ASPECT] Type - Auto | Explicit | 4:3 | 3:2 | 16:9 | PAR | Full"  0 0 6 1
float HSM_ASPECT_RATIO_MODE = global.HSM_ASPECT_RATIO_MODE;

#pragma parameter HSM_ASPECT_RATIO_EXPLICIT				"[ ASPECT ]  Explicit Aspect Ratio (Also Auto Ratio Fallback)"  1.3333 0 3 0.002
float HSM_ASPECT_RATIO_EXPLICIT = global.HSM_ASPECT_RATIO_EXPLICIT;


//---------------------------------------------------------------------------------------------------
//    SCALING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCALING_TITLE					"_____[ SCALING ]_______________________________________________" 0 0 0 0

#pragma parameter HSM_INT_SCALE_MODE 					"[ SCALING ]  Int Scale Mode - OFF | ShortAxis | BothAxes" 0 0 2 1
#define HSM_INT_SCALE_MODE global.HSM_INT_SCALE_MODE

#pragma parameter HSM_INT_SCALE_MULTIPLE_OFFSET 		"[ SCALING ]  Int Scale Multiple Offset" 0 -20 20 1
#define HSM_INT_SCALE_MULTIPLE_OFFSET global.HSM_INT_SCALE_MULTIPLE_OFFSET

#pragma parameter HSM_INT_SCALE_MULTIPLE_OFFSET_LONG 	"[ SCALING ]  Int Scale Multiple Offset on Long Axis" 0 -20 20 1
#define HSM_INT_SCALE_MULTIPLE_OFFSET_LONG global.HSM_INT_SCALE_MULTIPLE_OFFSET_LONG

#pragma parameter HSM_INT_SCALE_BORDER_MIN_HEIGHT 	"[ SCALING ]  Int Scale Border Min Height %" 5.5 -20 20 0.5
float HSM_INT_SCALE_BORDER_MIN_HEIGHT = global.HSM_INT_SCALE_BORDER_MIN_HEIGHT;

// Non integer scale is set to 82.97 so that cores which output 224px will have integer scale by default
// This is 8x integer scale at 3840x2160 and 6x integer scale at 1920x1080
#pragma parameter HSM_NON_INTEGER_SCALE 				"[ SCALING ]  Non-Integer Scale %" 82.97 1 200 0.2
float HSM_NON_INTEGER_SCALE = global.HSM_NON_INTEGER_SCALE;

#pragma parameter HSM_SNAP_TO_INT_SCALE_TOLERANCE 		"[ SCALING ]  Snap To Int-Scale Tolerance - Suggested 0.1" 0 0 3 0.01
float HSM_SNAP_TO_INT_SCALE_TOLERANCE = global.HSM_SNAP_TO_INT_SCALE_TOLERANCE;


//---------------------------------------------------------------------------------------------------
//    Position
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCREEN_POSITION_TITLE					"_____[ POSITION ]______________________________________________" 0 0 0 0

#pragma parameter HSM_SCREEN_POSITION_X 				"[ POSITION ]  Position X" 0 -100 100 0.1
float HSM_SCREEN_POSITION_X = global.HSM_SCREEN_POSITION_X / 100;

#pragma parameter HSM_SCREEN_POSITION_Y 				"[ POSITION ]  Position Y" 0 -100 100 0.1
float HSM_SCREEN_POSITION_Y = -1 * global.HSM_SCREEN_POSITION_Y / 100;


//---------------------------------------------------------------------------------------------------
//    CROPPING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CROPPING_TITLE					"_____[ CROPPING ]______________________________________________" 0 0 0 0

#pragma parameter HSM_CROP_OVERSCAN_TOP 				"[ CROPPING ]  Crop Overscan Top" 0 -256 256 1
float HSM_CROP_OVERSCAN_TOP = global.HSM_CROP_OVERSCAN_TOP;

#pragma parameter HSM_CROP_OVERSCAN_BOTTOM 				"[ CROPPING ]  Crop Overscan Bottom" 0 -256 256 1
float HSM_CROP_OVERSCAN_BOTTOM = global.HSM_CROP_OVERSCAN_BOTTOM;

#pragma parameter HSM_CROP_OVERSCAN_LEFT 				"[ CROPPING ]  Crop Overscan Left" 0 -256 256 1
float HSM_CROP_OVERSCAN_LEFT = global.HSM_CROP_OVERSCAN_LEFT;

#pragma parameter HSM_CROP_OVERSCAN_RIGHT 				"[ CROPPING ]  Crop Overscan Right" 0 -256 256 1
float HSM_CROP_OVERSCAN_RIGHT = global.HSM_CROP_OVERSCAN_RIGHT;


//---------------------------------------------------------------------------------------------------
//    CORE RES SAMPLING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SAMPLING_TITLE								"_____[ CORE RES SAMPLING ]_____________________________________" 0 0 0 0

#pragma parameter HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR			"[ CORE RES SAMPLING ]  Scanline Dir"  1 0.25 16 0.25
float HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR = global.HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR;

#pragma parameter HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR			"[ CORE RES SAMPLING ]  Opposite Dir"  1 0.25 16 0.25
float HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR = global.HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR;


//---------------------------------------------------------------------------------------------------
//    SCANLINES
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCANLINE_TITLE								"_____[ SCANLINES ]_____________________________________________" 0 0 0 0

#pragma parameter HSM_SCANLINE_DIRECTION 							"[ SCANLINE DIRECTION ]  Guest & Easymode - Auto | Horiz | Vert"  0 0 2 1
float HSM_SCANLINE_DIRECTION = global.HSM_SCANLINE_DIRECTION;

#pragma parameter HSM_SCANLINE_INTERLACE_TRIGGER_RES 						"[ INTERLACE AND FAKE SCANLINES ]  Trigger Res" 600.0 0.0 2000.0 25.0
#define HSM_SCANLINE_INTERLACE_TRIGGER_RES global.HSM_SCANLINE_INTERLACE_TRIGGER_RES

#pragma parameter HSM_SCANLINE_FAKE_SCANLINE_OPACITY 				"[ FAKE SCANLINES ]  Scanline Opacity - Def 0.7" 0.7 0 1 0.05
#define HSM_SCANLINE_FAKE_SCANLINE_OPACITY global.HSM_SCANLINE_FAKE_SCANLINE_OPACITY

// #pragma parameter HSM_SCANLINE_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 	"[ SCREEN FX ]  Fake 240p Scanline Brightness Cutoff - Def 3" 3 0 10 0.05
#ifndef HSM_SCANLINE_FAKE_SCANLINE_BRIGHTNESS_CUTOFF
	#define HSM_SCANLINE_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 3
#endif


//---------------------------------------------------------------------------------------------------
//    SPLIT SCREEN
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SPLITSCREEN_TITLE					"_____[ SPLIT SCREEN ]__________________________________________" 0 0 0 0

#pragma parameter HSM_SPLITSCREEN_ON					"[ SPLIT SCREEN ]  Split ON - SPLIT SCREEN PRESET ONLY" 0 0 1 1
float HSM_SPLITSCREEN_ON = global.HSM_SPLITSCREEN_ON;

#pragma parameter HSM_SPLITSCREEN_AMOUNT				"[ SPLIT SCREEN ]  Split Thickness - SPLIT SCREEN PRESET ONLY" 0 0 256 2
float HSM_SPLITSCREEN_AMOUNT = global.HSM_SPLITSCREEN_AMOUNT;

// TODO add Split Position, also auto set position, catches for 3DS

#pragma parameter HSM_SPLITSCREEN_CENTER_FILL_MODE		"[ SPLIT SCREEN ] Center Fill - 1:Bezel 2:Reflect 3:Blend 4:Fade" 0 0 6 1
float HSM_SPLITSCREEN_CENTER_FILL_MODE = global.HSM_SPLITSCREEN_CENTER_FILL_MODE;


//---------------------------------------------------------------------------------------------------
//    CURVATURE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CURVATURE_TITLE					"_____[ CURVATURE ]_____________________________________________" 0 0 0 0

#pragma parameter HSM_CURVATURE_MODE 					"[ CURVATURE MODE ]  -1:OFF 0:2D 1-2:3D Sphere, 3:3D Cylinder" 0 -1 3 1
float HSM_CURVATURE_MODE = global.HSM_CURVATURE_MODE;

#pragma parameter HSM_CURVATURE_2D_SCALE_LONG_AXIS 	"[ 2D CURVATURE ]  2D Curvature on Long Axis - Def 1" 1 0 4 0.05
#define HSM_CURVATURE_2D_SCALE_LONG_AXIS global.HSM_CURVATURE_2D_SCALE_LONG_AXIS

#pragma parameter HSM_CURVATURE_2D_SCALE_SHORT_AXIS 	"[ 2D CURVATURE ]  2D Curvature on Short Axis - Def 1" 1 0 4 0.05
#define HSM_CURVATURE_2D_SCALE_SHORT_AXIS global.HSM_CURVATURE_2D_SCALE_SHORT_AXIS

#pragma parameter HSM_CURVATURE_3D_RADIUS 			"[ 3D CURVATURE ]  Radius" 2 0.16 1024 0.01
float HSM_CURVATURE_3D_RADIUS = global.HSM_CURVATURE_3D_RADIUS;

#pragma parameter HSM_CURVATURE_3D_VIEW_DIST 			"[ 3D CURVATURE ]  View Distance - Def 1.5" 1.5 0.5 1024 0.05
float HSM_CURVATURE_3D_VIEW_DIST = global.HSM_CURVATURE_3D_VIEW_DIST;

#pragma parameter HSM_CURVATURE_3D_TILT_ANGLE_X 		"[ 3D CURVATURE ]  Tilt Angle X" 0 -1.5 1.5 0.01
float HSM_CURVATURE_3D_TILT_ANGLE_X = global.HSM_CURVATURE_3D_TILT_ANGLE_X;

#pragma parameter HSM_CURVATURE_3D_TILT_ANGLE_Y 		"[ 3D CURVATURE ]  Tilt Angle Y" 0 -1.5 1.5 0.01
float HSM_CURVATURE_3D_TILT_ANGLE_Y = global.HSM_CURVATURE_3D_TILT_ANGLE_Y;


//---------------------------------------------------------------------------------------------------
//    PHOSPHOR PERSISTENCE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_PERSISTENCE_TITLE								"_____[ PHOSPHOR PERSISTENCE ]__________________________________" 0 0 0 0

#pragma parameter HSM_PHOSPHOR_PERSISTENCE          "[ PHOSPHOR PERSISTENCE ]  Amount - Pos:Neutral, Neg:Blue" 0 -1 1 0.05
#define HSM_PHOSPHOR_PERSISTENCE global.HSM_PHOSPHOR_PERSISTENCE



//---------------------------------------------------------------------------------------------------
//    COLOR & Persistence
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_COLOR_AND_PERSISTENCE_TITLE		"_____[ COLOR ]___________________________________" 0 0 0 0

#pragma parameter HSM_COLOR_BLACK_LEVEL 				"[ SCANLINES ON BLACK ]  Black Level - Def -0.04" -0.04 -1 1 0.01
#define HSM_COLOR_BLACK_LEVEL global.HSM_COLOR_BLACK_LEVEL

#pragma parameter HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS	"[ SCANLINES ON BLACK ]  Negative Crop Brightness - Def 1.8" 1.8 0 100 0.2
#define HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS global.HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS

#pragma parameter HSM_COLOR_CRT_GAMMA   				"[ GAMMA ]  CRT Gamma (Linear to Gamma Space Encode) Def 2.2" 2.2 0.1 5 0.05
#define HSM_COLOR_CRT_GAMMA global.HSM_COLOR_CRT_GAMMA

#pragma parameter HSM_SCREEN_VIGNETTE                	"[ SCREEN VIGNETTE ]  Opacity" 0 0 1 0.01
#define HSM_SCREEN_VIGNETTE global.HSM_SCREEN_VIGNETTE

#pragma parameter HSM_SCREEN_VIGNETTE_IN_REFLECTION     "[ SCREEN VIGNETTE ]  Opacity in Reflection" 0 0 1 1
float HSM_SCREEN_VIGNETTE_IN_REFLECTION = global.HSM_SCREEN_VIGNETTE_IN_REFLECTION;

//---------------------------------------------------------------------------------------------------
//    SCREEN EDGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SCREEN_EDGE_TITLE		"_____[ SCREEN EDGE ]___________________________________________" 0 0 0 0

#pragma parameter HSM_SCREEN_CORNER_RADIUS 			"[ SCREEN EDGE ]  Corner Radius - Def 10" 10 0 70 1
#define HSM_SCREEN_CORNER_RADIUS global.HSM_SCREEN_CORNER_RADIUS

#pragma parameter HSM_SCREEN_EDGE_SHARPNESS 			"[ SCREEN EDGE ]  Edge Sharpness - Def 0.4" 0.4 0 1 0.01
#define HSM_SCREEN_EDGE_SHARPNESS global.HSM_SCREEN_EDGE_SHARPNESS

#pragma parameter HSM_TUBE_BLACK_EDGE_THICKNESS 		"[ SCREEN EDGE ]  Black Border Thickness - Def 1" 1 -2 8 0.05
#define HSM_TUBE_BLACK_EDGE_THICKNESS global.HSM_TUBE_BLACK_EDGE_THICKNESS




//---------------------------------------------------------------------------------------------------
//    TUBE IMAGES
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_TUBE_IMAGES_TITLE		"_____[ TUBE IMAGES ]___________________________________________" 0 0 0 0

#pragma parameter HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT  "[ TUBE IMAGES ]   Colored Gel Multiply Amount" 0 0 100 5
float HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT = global.HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT / 100;

#pragma parameter HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT  "[ TUBE IMAGES ]   Colored Gel Additive Amount" 0 0 100 0.05
float HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT = global.HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT / 100;

#pragma parameter HSM_TUBE_HIGHLIGHT_IMAGE_OPACITY  "[ TUBE IMAGES ]   Tube Highlight Opacity" 1.4 0 100 0.1
float HSM_TUBE_HIGHLIGHT_IMAGE_OPACITY = global.HSM_TUBE_HIGHLIGHT_IMAGE_OPACITY / 100;

#pragma parameter HSM_TUBE_HIGHLIGHT_IMAGE_SCALE  "[ TUBE IMAGES ]   Tube Highlight Scale" 110 0 1000 1
float HSM_TUBE_HIGHLIGHT_IMAGE_SCALE = global.HSM_TUBE_HIGHLIGHT_IMAGE_SCALE / 100;

// #pragma parameter HSM_TUBE_HIGHLIGHT_IMAGE_DITHERING_SAMPLES  "[ TUBE IMAGES ]   Tube Highlight Noise Samples (Reduces Banding)" 0 0 10 1
// float HSM_TUBE_HIGHLIGHT_IMAGE_DITHERING_SAMPLES = global.HSM_TUBE_HIGHLIGHT_IMAGE_DITHERING_SAMPLES;

#pragma parameter HSM_CRT_IS_LAST_PASS 		"[ SCREEN EDGE ]  CRT is Last Pass" 0 0 1 1
#define HSM_CRT_IS_LAST_PASS global.HSM_CRT_IS_LAST_PASS

//---------------------------------------------------------------------------------------------------
//    Tube / Inner Bezel Curvature
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BEZEL_TITLE		"_____[ BEZEL ]_________________________________________________" 0 0 0 0

#pragma parameter HSM_BZL_INNER_CURVATURE_SCALE 	"[ BEZEL ]  Inner Curvature Scale" 1 0 20 0.1
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

