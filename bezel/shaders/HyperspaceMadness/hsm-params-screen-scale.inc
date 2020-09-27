/*   
hsm-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

// Screen Scale Required Parameters
#pragma parameter HSS_MEGA_BEZEL_TITLE					"------[  HSM MEGA BEZEL  ALPHA.2020-09-27-0  ]-----------------" 0 0 0 0

#pragma parameter HSS_MEGA_BEZEL_DEBUG					"[DEBUG]  Debug ON" 0 0 1 1
float HSS_MEGA_BEZEL_DEBUG = global.HSS_MEGA_BEZEL_DEBUG;

//---------------------------------------------------------------------------------------------------
//    FLIP & ROTATE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSS_FLIP_TITLE "------[FLIP & ROTATE - MEGA BEZEL]-----------------------------" 0 0 0 1

#pragma parameter HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL	"[VERTICAL FLIP]  Flip Viewport Vertical - For Some 3D Cores"  0 0 1 1
float HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL = global.HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL;

#pragma parameter HSS_ROTATE_CORE_IMAGE					"[ROTATE]  Rotate CRT Tube"  0 0 1 1
float HSS_ROTATE_CORE_IMAGE = global.HSS_ROTATE_CORE_IMAGE;


//---------------------------------------------------------------------------------------------------
//    ASPECT RATIO
//---------------------------------------------------------------------------------------------------
#pragma parameter HSS_ASPECT_TITLE "------[ASPECT RATIO - MEGA BEZEL]------------------------------" 0 0 0 1

#pragma parameter HSS_ASPECT_RATIO_ORIENTATION 			"[ASPECT]  Orientation - Auto, Horizontal, Vertical"  0 0 2 1
float HSS_ASPECT_RATIO_ORIENTATION = global.HSS_ASPECT_RATIO_ORIENTATION;

#pragma parameter HSS_ASPECT_RATIO_MODE 				"[ASPECT]  Type - 0-Auto, 1-Explicit, 4:3, 3:2, 16:9, PAR, Full"  0 0 6 1
float HSS_ASPECT_RATIO_MODE = global.HSS_ASPECT_RATIO_MODE;

#pragma parameter HSS_ASPECT_RATIO_EXPLICIT				"[ASPECT]  Explicit Aspect Ratio (Also Auto Ratio Fallback)"  1.3333 0 3 0.002
float HSS_ASPECT_RATIO_EXPLICIT = global.HSS_ASPECT_RATIO_EXPLICIT;


//---------------------------------------------------------------------------------------------------
//    SCALING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSS_SCALING_TITLE "------[SCALING - MEGA BEZEL]-----------------------------------" 0 0 0 1

#pragma parameter HSS_INT_SCALE_MODE 					"[SCALING]  Int Scale Mode - OFF, ShortAxis, BothAxes" 0 0 2 1
#define HSS_INT_SCALE_MODE global.HSS_INT_SCALE_MODE

#pragma parameter HSS_INT_SCALE_MULTIPLE_OFFSET 		"[SCALING]  Int Scale Multiple Offset" 0 -20 20 1
#define HSS_INT_SCALE_MULTIPLE_OFFSET global.HSS_INT_SCALE_MULTIPLE_OFFSET

#pragma parameter HSS_INT_SCALE_MULTIPLE_OFFSET_LONG 	"[SCALING]  Int Scale Multiple Offset Long Axis" 0 -20 20 1
#define HSS_INT_SCALE_MULTIPLE_OFFSET_LONG global.HSS_INT_SCALE_MULTIPLE_OFFSET_LONG

#pragma parameter HSS_INT_SCALE_BORDER_MIN_HEIGHT 		"[SCALING]  Int Scale Border Min Height %" 5.5 -20 20 0.5
float HSS_INT_SCALE_BORDER_MIN_HEIGHT = global.HSS_INT_SCALE_BORDER_MIN_HEIGHT;

// Non integer scale is set to 82.97 so that cores which output 224px will have integer scale by default
// This is 8x integer scale at 3840x2160 and 6x integer scale at 1920x1080
#pragma parameter HSS_NON_INTEGER_SCALE 				"[SCALING]  Non-Integer Scale %" 82.97 1 200 0.2
float HSS_NON_INTEGER_SCALE = global.HSS_NON_INTEGER_SCALE;

#pragma parameter HSS_SNAP_TO_INT_SCALE_TOLERANCE 		"[SCALING]  Snap To Int-Scale Tolerance - Suggested 0.1" 0 0 3 0.01
float HSS_SNAP_TO_INT_SCALE_TOLERANCE = global.HSS_SNAP_TO_INT_SCALE_TOLERANCE;

#pragma parameter HSS_POSITION_OFFSET_X 				"[POSITION]  Position Offset X" 0 -100 100 0.1
float HSS_POSITION_OFFSET_X = global.HSS_POSITION_OFFSET_X / 100;

#pragma parameter HSS_POSITION_OFFSET_Y 				"[POSITION]  Position Offset Y" 0 -100 100 0.1
float HSS_POSITION_OFFSET_Y = -1 * global.HSS_POSITION_OFFSET_Y / 100;


//---------------------------------------------------------------------------------------------------
//    CROPPING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSS_CROPPING_TITLE "------[CROPPING - MEGA BEZEL]----------------------------------" 0 0 0 1

#pragma parameter HSS_CROP_OVERSCAN_TOP 				"[CROPPING]  Crop Overscan Top" 0 -256 256 1
float HSS_CROP_OVERSCAN_TOP = global.HSS_CROP_OVERSCAN_TOP;

#pragma parameter HSS_CROP_OVERSCAN_BOTTOM 				"[CROPPING]  Crop Overscan Bottom" 0 -256 256 1
float HSS_CROP_OVERSCAN_BOTTOM = global.HSS_CROP_OVERSCAN_BOTTOM;

#pragma parameter HSS_CROP_OVERSCAN_LEFT 				"[CROPPING]  Crop Overscan Left" 0 -256 256 1
float HSS_CROP_OVERSCAN_LEFT = global.HSS_CROP_OVERSCAN_LEFT;

#pragma parameter HSS_CROP_OVERSCAN_RIGHT 				"[CROPPING]  Crop Overscan Right" 0 -256 256 1
float HSS_CROP_OVERSCAN_RIGHT = global.HSS_CROP_OVERSCAN_RIGHT;


//---------------------------------------------------------------------------------------------------
//    SCANLINES & SAMPLING
//---------------------------------------------------------------------------------------------------
#pragma parameter HSS_SCANLINES_TITLE "------[SCANLINES & SAMPLING - MEGA BEZEL]----------------------" 0 0 0 1

#pragma parameter HSS_SCANLINE_DIRECTION 				"[SCANLINE DIRECTION]  Guest & Easymode - Auto, Horiz, Vert"  0 0 2 1
float HSS_SCANLINE_DIRECTION = global.HSS_SCANLINE_DIRECTION;

#pragma parameter HSS_CORE_RES_SAMPLING_MULT_SCANLINE_DIR			"[CORE RES SAMPLING]  Scanline Dir"  1 0.25 16 0.25
float HSS_CORE_RES_SAMPLING_MULT_SCANLINE_DIR = global.HSS_CORE_RES_SAMPLING_MULT_SCANLINE_DIR;

#pragma parameter HSS_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR			"[CORE RES SAMPLING]  Opposite Dir"  1 0.25 16 0.25
float HSS_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR = global.HSS_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR;

#pragma parameter HSS_INTERLACE_TRIGGER_RES 			"[INTERLACE]  Trigger Res (Also Fake Scanlines)" 600.0 0.0 2000.0 25.0
#define HSS_INTERLACE_TRIGGER_RES global.HSS_INTERLACE_TRIGGER_RES


//---------------------------------------------------------------------------------------------------
//    SPLIT SCREEN
//---------------------------------------------------------------------------------------------------
#pragma parameter HBZ_SPLITSCREEN_TITLE "------[SPLIT SCREEN - MEGA BEZEL]------------------------------" 0 0 0 1

#pragma parameter HSS_SPLIT_SCREEN_AMOUNT				"[SPLIT SCREEN]  Split Thickness - SPLIT SCREEN PRESET ONLY" 0 0 256 2
float HSS_SPLIT_SCREEN_AMOUNT = global.HSS_SPLIT_SCREEN_AMOUNT;

// TODO add Split Position, also auto set position, catches for 3DS

#pragma parameter HSS_SPLIT_SCREEN_CENTER_FILL_MODE		"[SPLIT SCREEN]  Center Fill - 1:Bezel 2:Reflect 3:Blend 4:Fade" 0 0 6 1
float HSS_SPLIT_SCREEN_CENTER_FILL_MODE = global.HSS_SPLIT_SCREEN_CENTER_FILL_MODE;


//---------------------------------------------------------------------------------------------------
//    CURVATURE
//---------------------------------------------------------------------------------------------------
#pragma parameter HBZ_CURVATURE_TITLE "------[CURVATURE - MEGA BEZEL]---------------------------------" 0 0 0 1

#pragma parameter HSS_CURVATURE_MODE 					"[CURVATURE MODE]  0:2D 1-2:3D Sphere, 3:3D Cylinder" 0 0 3 1
float HSS_CURVATURE_MODE = global.HSS_CURVATURE_MODE;

#pragma parameter HSS_CURVATURE_2D_SCALE_LONG_AXIS 		"[2D CURVATURE]  2D Curvature on Long Axis - Def 1" 1 0 4 0.05
#define HSS_CURVATURE_2D_SCALE_LONG_AXIS global.HSS_CURVATURE_2D_SCALE_LONG_AXIS

#pragma parameter HSS_CURVATURE_2D_SCALE_SHORT_AXIS 	"[2D CURVATURE]  2D Curvature on Short Axis - Def 1" 1 0 4 0.05
#define HSS_CURVATURE_2D_SCALE_SHORT_AXIS global.HSS_CURVATURE_2D_SCALE_SHORT_AXIS

#pragma parameter HSS_CURVATURE_3D_RADIUS 				"[3D CURVATURE]  Radius" 2 0.16 1024 0.01
float HSS_CURVATURE_3D_RADIUS = global.HSS_CURVATURE_3D_RADIUS;

#pragma parameter HSS_CURVATURE_3D_VIEW_DIST 			"[3D CURVATURE]  View Distance - Def 1.5" 1.5 0.5 1024 0.05
float HSS_CURVATURE_3D_VIEW_DIST = global.HSS_CURVATURE_3D_VIEW_DIST;

#pragma parameter HSS_CURVATURE_3D_TILT_ANGLE_X 		"[3D CURVATURE]  Tilt Angle X" 0 -1.5 1.5 0.01
float HSS_CURVATURE_3D_TILT_ANGLE_X = global.HSS_CURVATURE_3D_TILT_ANGLE_X;

#pragma parameter HSS_CURVATURE_3D_TILT_ANGLE_Y 		"[3D CURVATURE]  Tilt Angle Y" 0 -1.5 1.5 0.01
float HSS_CURVATURE_3D_TILT_ANGLE_Y = global.HSS_CURVATURE_3D_TILT_ANGLE_Y;


//---------------------------------------------------------------------------------------------------
//    COLOR & SCREEN FX
//---------------------------------------------------------------------------------------------------
#pragma parameter HBZ_COLOR_TITLE "------[COLOR & SCREEN FX - MEGA BEZEL]-------------------------" 0 0 0 1

#pragma parameter HSS_COLOR_BLACK_LEVEL 				"[COLOR]  Black Level - Def -0.04" -0.04 -1 1 0.01
#define HSS_COLOR_BLACK_LEVEL global.HSS_COLOR_BLACK_LEVEL

#pragma parameter HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS	"[COLOR]  Negative Crop Brightness - Def 1.8" 1.8 0 100 0.2
#define HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS global.HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS

#pragma parameter HSS_COLOR_CRT_GAMMA   				"[COLOR]  CRT Gamma - Def 2.3" 2.2 0.1 5 0.05
#define HSS_COLOR_CRT_GAMMA global.HSS_COLOR_CRT_GAMMA

#pragma parameter HSS_PHOSPHOR_PERSISTENCE             "[PHOSPHOR PERSISTENCE]  Amount - Pos:Neutral, Neg:Blue" 0 -1 1 0.05
#define HSS_PHOSPHOR_PERSISTENCE global.HSS_PHOSPHOR_PERSISTENCE

#pragma parameter HSS_SCREENFX_CORNER_RADIUS 			"[SCREEN FX]  Screen Corner Radius - Def 10" 10 0 70 1
#define HSS_SCREENFX_CORNER_RADIUS global.HSS_SCREENFX_CORNER_RADIUS

#pragma parameter HSS_SCREENFX_EDGE_SHARPNESS 			"[SCREEN FX]  Screen Edge Sharpness - Def 0.4" 0.4 0 1 0.01
#define HSS_SCREENFX_EDGE_SHARPNESS global.HSS_SCREENFX_EDGE_SHARPNESS

#pragma parameter HSS_SCREENFX_VIGNETTE                "[SCREEN FX]  Screen Vignette" 0 0 1 0.01
#define HSS_SCREENFX_VIGNETTE global.HSS_SCREENFX_VIGNETTE

#pragma parameter HSS_SCREENFX_FAKE_SCANLINE_OPACITY 	"[SCREEN FX]  Fake 240p Scanline Opacity - Def 0.7" 0.7 0 1 0.05
#define HSS_SCREENFX_FAKE_SCANLINE_OPACITY global.HSS_SCREENFX_FAKE_SCANLINE_OPACITY

// #pragma parameter HSS_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 	"[SCREEN FX]  Fake 240p Scanline Brightness Cutoff - Def 3" 3 0 10 0.05
#ifndef HSS_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF
	#define HSS_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 3
#endif


//---------------------------------------------------------------------------------------------------
//    GLASS BORDER
//---------------------------------------------------------------------------------------------------
#pragma parameter HGL_GLASSBORDER_TITLE "------[GLASS BORDER - MEGA BEZEL]------------------------------" 0 0 0 0

#pragma parameter HGL_GLASSBORDER_ON       "[GLASS BORDER]  ON" 0 0 1 1
float HGL_GLASSBORDER_ON = global.HGL_GLASSBORDER_ON;


//---------------------------------------------------------------------------------------------------
//    TUBE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSS_TUBE_TITLE "------[TUBE - MEGA BEZEL]--------------------------------------" 0 0 0 1

#pragma parameter HSS_TUBE_BLACK_EDGE_THICKNESS 		"[TUBE]  Black Edge Thickness - Def 1" 1 -2 8 0.05
#define HSS_TUBE_BLACK_EDGE_THICKNESS global.HSS_TUBE_BLACK_EDGE_THICKNESS

// TODO this black edge curvature isn't doing anything anymore
#pragma parameter HSS_TUBE_CURVATURE_SCALE 	"[TUBE]  Curvature Scale" 1 0 20 0.1
#define HSS_TUBE_CURVATURE_SCALE global.HSS_TUBE_CURVATURE_SCALE

#ifndef HSS_SCREENFX_SCANLINE_RES
	#define HSS_SCREENFX_SCANLINE_RES 240
#endif

#ifndef HSS_DEFAULT_CRT_GAMMA
	#define HSS_DEFAULT_CRT_GAMMA 2.4
#endif

#ifndef HSS_DEFAULT_SRGB_GAMMA
	#define HSS_DEFAULT_SRGB_GAMMA 2.2
#endif


