/*   
hsm-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

// Screen Scale Required Parameters
#pragma parameter H_MEGA_BEZEL_TITLE					"_____[ HSM MEGA BEZEL  ALPHA.2020-10-06-0 ]____________________" 0 0 0 0

#pragma parameter H_MEGA_BEZEL_DEBUG					"[ DEBUG ]  Debug ON" 0 0 1 1
float H_MEGA_BEZEL_DEBUG = global.H_MEGA_BEZEL_DEBUG;

//---------------------------------------------------------------------------------------------------
//    FLIP & ROTATE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_FLIP_VIEWPORT_AND_CORE_VERTICAL	"[ VERTICAL FLIP ]  Flip Vertical - For 3D Cores _______________"  0 0 1 1
float H_FLIP_VIEWPORT_AND_CORE_VERTICAL = global.H_FLIP_VIEWPORT_AND_CORE_VERTICAL;

#pragma parameter H_ROTATE_CORE_IMAGE					"[ ROTATE ]  Rotate CRT Tube"  0 0 1 1
float H_ROTATE_CORE_IMAGE = global.H_ROTATE_CORE_IMAGE;


//---------------------------------------------------------------------------------------------------
//    ASPECT RATIO
//---------------------------------------------------------------------------------------------------
#pragma parameter H_ASPECT_RATIO_ORIENTATION 			"[ ASPECT ]  Orientation - Auto, Horizontal, Vertical __________"  0 0 2 1
float H_ASPECT_RATIO_ORIENTATION = global.H_ASPECT_RATIO_ORIENTATION;

#pragma parameter H_ASPECT_RATIO_MODE 				"[ ASPECT ] Type - 0-Auto, 1-Explicit, 4:3, 3:2, 16:9, PAR, Full"  0 0 6 1
float H_ASPECT_RATIO_MODE = global.H_ASPECT_RATIO_MODE;

#pragma parameter H_ASPECT_RATIO_EXPLICIT				"[ ASPECT ]  Explicit Aspect Ratio (Also Auto Ratio Fallback)"  1.3333 0 3 0.002
float H_ASPECT_RATIO_EXPLICIT = global.H_ASPECT_RATIO_EXPLICIT;


//---------------------------------------------------------------------------------------------------
//    SCALING
//---------------------------------------------------------------------------------------------------
#pragma parameter H_INT_SCALE_MODE 					"[ SCALING ]  Int Scale Mode - OFF, ShortAxis, BothAxes ________" 0 0 2 1
#define H_INT_SCALE_MODE global.H_INT_SCALE_MODE

#pragma parameter H_INT_SCALE_MULTIPLE_OFFSET 		"[ SCALING ]  Int Scale Multiple Offset" 0 -20 20 1
#define H_INT_SCALE_MULTIPLE_OFFSET global.H_INT_SCALE_MULTIPLE_OFFSET

#pragma parameter H_INT_SCALE_MULTIPLE_OFFSET_LONG 	"[ SCALING ]  Int Scale Multiple Offset Long Axis" 0 -20 20 1
#define H_INT_SCALE_MULTIPLE_OFFSET_LONG global.H_INT_SCALE_MULTIPLE_OFFSET_LONG

#pragma parameter H_INT_SCALE_BORDER_MIN_HEIGHT 		"[ SCALING ]  Int Scale Border Min Height %" 5.5 -20 20 0.5
float H_INT_SCALE_BORDER_MIN_HEIGHT = global.H_INT_SCALE_BORDER_MIN_HEIGHT;

// Non integer scale is set to 82.97 so that cores which output 224px will have integer scale by default
// This is 8x integer scale at 3840x2160 and 6x integer scale at 1920x1080
#pragma parameter H_NON_INTEGER_SCALE 				"[ SCALING ]  Non-Integer Scale %" 82.97 1 200 0.2
float H_NON_INTEGER_SCALE = global.H_NON_INTEGER_SCALE;

#pragma parameter H_SNAP_TO_INT_SCALE_TOLERANCE 		"[ SCALING ]  Snap To Int-Scale Tolerance - Suggested 0.1" 0 0 3 0.01
float H_SNAP_TO_INT_SCALE_TOLERANCE = global.H_SNAP_TO_INT_SCALE_TOLERANCE;


//---------------------------------------------------------------------------------------------------
//    CROPPING
//---------------------------------------------------------------------------------------------------
#pragma parameter H_POSITION_OFFSET_X 				"[ POSITION ]  Position Offset X _______________________________" 0 -100 100 0.1
float H_POSITION_OFFSET_X = global.H_POSITION_OFFSET_X / 100;

#pragma parameter H_POSITION_OFFSET_Y 				"[ POSITION ]  Position Offset Y" 0 -100 100 0.1
float H_POSITION_OFFSET_Y = -1 * global.H_POSITION_OFFSET_Y / 100;


//---------------------------------------------------------------------------------------------------
//    CROPPING
//---------------------------------------------------------------------------------------------------
#pragma parameter H_CROP_OVERSCAN_TOP 				"[ CROPPING ]  Crop Overscan Top _______________________________" 0 -256 256 1
float H_CROP_OVERSCAN_TOP = global.H_CROP_OVERSCAN_TOP;

#pragma parameter H_CROP_OVERSCAN_BOTTOM 				"[ CROPPING ]  Crop Overscan Bottom" 0 -256 256 1
float H_CROP_OVERSCAN_BOTTOM = global.H_CROP_OVERSCAN_BOTTOM;

#pragma parameter H_CROP_OVERSCAN_LEFT 				"[ CROPPING ]  Crop Overscan Left" 0 -256 256 1
float H_CROP_OVERSCAN_LEFT = global.H_CROP_OVERSCAN_LEFT;

#pragma parameter H_CROP_OVERSCAN_RIGHT 				"[ CROPPING ]  Crop Overscan Right" 0 -256 256 1
float H_CROP_OVERSCAN_RIGHT = global.H_CROP_OVERSCAN_RIGHT;


//---------------------------------------------------------------------------------------------------
//    SCANLINES & SAMPLING
//---------------------------------------------------------------------------------------------------
#pragma parameter H_SCANLINE_DIRECTION 				"[ SCANLINE DIRECTION ]  Guest & Easymode - Auto, Horiz, Vert __"  0 0 2 1
float H_SCANLINE_DIRECTION = global.H_SCANLINE_DIRECTION;

#pragma parameter H_CORE_RES_SAMPLING_MULT_SCANLINE_DIR			"[ CORE RES SAMPLING ]  Scanline Dir ___________________________"  1 0.25 16 0.25
float H_CORE_RES_SAMPLING_MULT_SCANLINE_DIR = global.H_CORE_RES_SAMPLING_MULT_SCANLINE_DIR;

#pragma parameter H_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR			"[ CORE RES SAMPLING ]  Opposite Dir"  1 0.25 16 0.25
float H_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR = global.H_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR;

#pragma parameter H_INTERLACE_TRIGGER_RES 			"[ INTERLACE ]  Trigger Res (Also Fake Scanlines) ______________" 600.0 0.0 2000.0 25.0
#define H_INTERLACE_TRIGGER_RES global.H_INTERLACE_TRIGGER_RES


//---------------------------------------------------------------------------------------------------
//    SPLIT SCREEN
//---------------------------------------------------------------------------------------------------
#pragma parameter H_SPLIT_SCREEN_ON					"[ SPLIT SCREEN ]  Split ON - SPLIT SCREEN PRESET ONLY _________" 0 0 1 1
float H_SPLIT_SCREEN_ON = global.H_SPLIT_SCREEN_ON;

#pragma parameter H_SPLIT_SCREEN_AMOUNT				"[ SPLIT SCREEN ]  Split Thickness - SPLIT SCREEN PRESET ONLY" 0 0 256 2
float H_SPLIT_SCREEN_AMOUNT = global.H_SPLIT_SCREEN_AMOUNT;

// TODO add Split Position, also auto set position, catches for 3DS

#pragma parameter H_SPLIT_SCREEN_CENTER_FILL_MODE		"[ SPLIT SCREEN ] Center Fill - 1:Bezel 2:Reflect 3:Blend 4:Fade" 0 0 6 1
float H_SPLIT_SCREEN_CENTER_FILL_MODE = global.H_SPLIT_SCREEN_CENTER_FILL_MODE;


//---------------------------------------------------------------------------------------------------
//    CURVATURE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_CURVATURE_MODE 					"[ CURVATURE MODE ]  -1:OFF 0:2D 1-2:3D Sphere, 3:3D Cyl _______" 0 -1 3 1
float H_CURVATURE_MODE = global.H_CURVATURE_MODE;

#pragma parameter H_CURVATURE_2D_SCALE_LONG_AXIS 		"[ 2D CURVATURE ]  2D Curvature on Long Axis - Def 1" 1 0 4 0.05
#define H_CURVATURE_2D_SCALE_LONG_AXIS global.H_CURVATURE_2D_SCALE_LONG_AXIS

#pragma parameter H_CURVATURE_2D_SCALE_SHORT_AXIS 	"[ 2D CURVATURE ]  2D Curvature on Short Axis - Def 1" 1 0 4 0.05
#define H_CURVATURE_2D_SCALE_SHORT_AXIS global.H_CURVATURE_2D_SCALE_SHORT_AXIS

#pragma parameter H_CURVATURE_3D_RADIUS 				"[ 3D CURVATURE ]  Radius" 2 0.16 1024 0.01
float H_CURVATURE_3D_RADIUS = global.H_CURVATURE_3D_RADIUS;

#pragma parameter H_CURVATURE_3D_VIEW_DIST 			"[ 3D CURVATURE ]  View Distance - Def 1.5" 1.5 0.5 1024 0.05
float H_CURVATURE_3D_VIEW_DIST = global.H_CURVATURE_3D_VIEW_DIST;

#pragma parameter H_CURVATURE_3D_TILT_ANGLE_X 		"[ 3D CURVATURE ]  Tilt Angle X" 0 -1.5 1.5 0.01
float H_CURVATURE_3D_TILT_ANGLE_X = global.H_CURVATURE_3D_TILT_ANGLE_X;

#pragma parameter H_CURVATURE_3D_TILT_ANGLE_Y 		"[ 3D CURVATURE ]  Tilt Angle Y" 0 -1.5 1.5 0.01
float H_CURVATURE_3D_TILT_ANGLE_Y = global.H_CURVATURE_3D_TILT_ANGLE_Y;


//---------------------------------------------------------------------------------------------------
//    COLOR & Persistence
//---------------------------------------------------------------------------------------------------
#pragma parameter H_COLOR_BLACK_LEVEL 				"[ SCANLINES ON BLACK ]  Black Level - Def -0.04 _______________" -0.04 -1 1 0.01
#define H_COLOR_BLACK_LEVEL global.H_COLOR_BLACK_LEVEL

#pragma parameter H_COLOR_NEGATIVE_CROP_BRIGHTNESS	"[ SCANLINES ON BLACK ]  Negative Crop Brightness - Def 1.8" 1.8 0 100 0.2
#define H_COLOR_NEGATIVE_CROP_BRIGHTNESS global.H_COLOR_NEGATIVE_CROP_BRIGHTNESS

#pragma parameter HSS_PHOSPHOR_PERSISTENCE             "[ PHOSPHOR PERSISTENCE ]  Amount - Pos:Neutral, Neg:Blue ______" 0 -1 1 0.05
#define HSS_PHOSPHOR_PERSISTENCE global.HSS_PHOSPHOR_PERSISTENCE

#pragma parameter H_COLOR_CRT_GAMMA   				"[ SCREEN FX ]  CRT Gamma (Linear to Gamma Space Encode) Def 2.2" 2.2 0.1 5 0.05
#define H_COLOR_CRT_GAMMA global.H_COLOR_CRT_GAMMA

#pragma parameter H_SCREENFX_VIGNETTE                "[ SCREEN FX ]  Screen Vignette" 0 0 1 0.01
#define H_SCREENFX_VIGNETTE global.H_SCREENFX_VIGNETTE

#pragma parameter H_SCREENFX_FAKE_SCANLINE_OPACITY 	"[ SCREEN FX ]  Fake 240p Scanline Opacity - Def 0.7" 0.7 0 1 0.05
#define H_SCREENFX_FAKE_SCANLINE_OPACITY global.H_SCREENFX_FAKE_SCANLINE_OPACITY

// #pragma parameter H_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 	"[ SCREEN FX ]  Fake 240p Scanline Brightness Cutoff - Def 3" 3 0 10 0.05
#ifndef H_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF
	#define H_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 3
#endif

//---------------------------------------------------------------------------------------------------
//    TUBE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_SCREEN_CORNER_RADIUS 				"[ SCREEN EDGE ]  Corner Radius - Def 10 _______________________" 10 0 70 1
#define H_SCREEN_CORNER_RADIUS global.H_SCREEN_CORNER_RADIUS

#pragma parameter H_SCREEN_EDGE_SHARPNESS 			"[ SCREEN EDGE ]  Edge Sharpness - Def 0.4" 0.4 0 1 0.01
#define H_SCREEN_EDGE_SHARPNESS global.H_SCREEN_EDGE_SHARPNESS

#pragma parameter H_TUBE_BLACK_EDGE_THICKNESS 		"[ SCREEN EDGE ]  Black Border Thickness - Def 1" 1 -2 8 0.05
#define H_TUBE_BLACK_EDGE_THICKNESS global.H_TUBE_BLACK_EDGE_THICKNESS

//---------------------------------------------------------------------------------------------------
//    TUBE IMAGES
//---------------------------------------------------------------------------------------------------

#pragma parameter H_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT  "[ TUBE IMAGES ]   Colored Gel Multiply Amount _________________" 0 0 100 5
float H_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT = global.H_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT / 100;

#pragma parameter H_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT  "[ TUBE IMAGES ]   Colored Gel Additive Amount" 0 0 100 0.05
float H_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT = global.H_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT / 100;

#pragma parameter H_TUBE_HIGHLIGHT_IMAGE_OPACITY  "[ TUBE IMAGES ]   Tube Highlight Opacity" 1.4 0 100 0.1
float H_TUBE_HIGHLIGHT_IMAGE_OPACITY = global.H_TUBE_HIGHLIGHT_IMAGE_OPACITY / 100;

#pragma parameter H_TUBE_HIGHLIGHT_IMAGE_SCALE  "[ TUBE IMAGES ]   Tube Highlight Scale" 110 0 1000 1
float H_TUBE_HIGHLIGHT_IMAGE_SCALE = global.H_TUBE_HIGHLIGHT_IMAGE_SCALE / 100;

// #pragma parameter H_TUBE_HIGHLIGHT_IMAGE_DITHERING_SAMPLES  "[ TUBE IMAGES ]   Tube Highlight Noise Samples (Reduces Banding)" 0 0 10 1
// float H_TUBE_HIGHLIGHT_IMAGE_DITHERING_SAMPLES = global.H_TUBE_HIGHLIGHT_IMAGE_DITHERING_SAMPLES;

// TODO Move dither sampling to Post CRT Prep
// TODO Highlight is being masked to teh screen instead of the tube now

//---------------------------------------------------------------------------------------------------
//    GLASS BORDER
//---------------------------------------------------------------------------------------------------
#pragma parameter HGL_GLASSBORDER_ON       "[ GLASS BORDER ]  ON (Glass Preset Only)" 0 0 1 1
float HGL_GLASSBORDER_ON = global.HGL_GLASSBORDER_ON;


//---------------------------------------------------------------------------------------------------
//    Tube / Inner Bezel Curvature
//---------------------------------------------------------------------------------------------------

#pragma parameter H_TUBE_CURVATURE_SCALE 	"[ BEZEL ]  Inner Curvature Scale ______________________________" 1 0 20 0.1
#define H_TUBE_CURVATURE_SCALE global.H_TUBE_CURVATURE_SCALE

#ifndef H_SCREENFX_SCANLINE_RES
	#define H_SCREENFX_SCANLINE_RES 240
#endif

#ifndef HSS_DEFAULT_CRT_GAMMA
	#define HSS_DEFAULT_CRT_GAMMA 2.4
#endif

#ifndef HSS_DEFAULT_SRGB_GAMMA
	#define HSS_DEFAULT_SRGB_GAMMA 2.2
#endif


