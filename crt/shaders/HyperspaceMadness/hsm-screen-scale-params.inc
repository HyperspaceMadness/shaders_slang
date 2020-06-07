/*   
hsm-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

// Screen Scale Required Parameters
#pragma parameter HSS_MEGA_BEZEL_DEBUG				"___HSM MEGA BEZEL__ V.2020-06-07-0 - Debug ON" 0 0 1 1
float HSS_MEGA_BEZEL_DEBUG = global.HSS_MEGA_BEZEL_DEBUG;

#pragma parameter HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL	"[VERTICAL FLIP]  Flip Viewport Vertical (For Cores like MUPEN)"  0 0 1 1
float HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL = global.HSS_FLIP_VIEWPORT_AND_CORE_VERTICAL;

#pragma parameter HSS_ROTATE_CORE_IMAGE				"[ROTATE]  Rotate CRT Image"  0 0 1 1
float HSS_ROTATE_CORE_IMAGE = global.HSS_ROTATE_CORE_IMAGE;

#pragma parameter HSS_ASPECT_RATIO_ORIENTATION 		"[ASPECT RATIO]  Orientation - Auto, Horizontal, Vertical"  0 0 2 1
float HSS_ASPECT_RATIO_ORIENTATION = global.HSS_ASPECT_RATIO_ORIENTATION;

#pragma parameter HSS_ASPECT_RATIO_MODE 				"[ASPECT RATIO]  Type - Auto, Explicit, 4:3, 3:2, 16:9, PAR,Full"  0 0 6 1
float HSS_ASPECT_RATIO_MODE = global.HSS_ASPECT_RATIO_MODE;

#pragma parameter HSS_ASPECT_RATIO_EXPLICIT			"[ASPECT]  Explicit Aspect Ratio (Also Auto Ratio Fallback)"  1.3333 0 3 0.002
float HSS_ASPECT_RATIO_EXPLICIT = global.HSS_ASPECT_RATIO_EXPLICIT;

#pragma parameter HSS_INT_SCALE_MODE 					"[SCALING]  Int Scale Mode - OFF, ShortAxis, BothAxes" 0 -1 2 1
#define HSS_INT_SCALE_MODE global.HSS_INT_SCALE_MODE

#pragma parameter HSS_INT_SCALE_MULTIPLE_OFFSET 		"[SCALING]  Int Scale Multiple Offset" 0 -20 20 1
#define HSS_INT_SCALE_MULTIPLE_OFFSET global.HSS_INT_SCALE_MULTIPLE_OFFSET

#pragma parameter HSS_INT_SCALE_MULTIPLE_OFFSET_LONG 	"[SCALING]  Int Scale Multiple Offset Long Axis" 0 -20 20 1
#define HSS_INT_SCALE_MULTIPLE_OFFSET_LONG global.HSS_INT_SCALE_MULTIPLE_OFFSET_LONG

#pragma parameter HSS_INT_SCALE_BORDER_MIN_HEIGHT 		"[SCALING]  Int Scale Border Min Height %" 5.5 -20 20 0.5
float HSS_INT_SCALE_BORDER_MIN_HEIGHT = global.HSS_INT_SCALE_BORDER_MIN_HEIGHT;

// Non integer scale is set to 82.97 so that cores which output 224px will have integer scale by default
// This is 8x integer scale at 3840x2160 and 6x integer scale at 1920x1080
#pragma parameter HSS_NON_INTEGER_SCALE 				"[SCALING]  Non-Integer Scale %" 82.97 1 200 0.2 //At one point it seemed 77.777
float HSS_NON_INTEGER_SCALE = global.HSS_NON_INTEGER_SCALE;

#pragma parameter HSS_SCANLINE_DIRECTION 				"[SCANLINES]  Direction Guest & Easymode - Auto, Horiz, Vert"  0 0 2 1
float HSS_SCANLINE_DIRECTION = global.HSS_SCANLINE_DIRECTION;

#pragma parameter HSS_CORE_RES_SAMPLING_MULT_X			"[SCANLINES]  Core Res Sampling Mult X"  1 0.25 16 0.25
float HSS_CORE_RES_SAMPLING_MULT_X = global.HSS_CORE_RES_SAMPLING_MULT_X;

#pragma parameter HSS_CORE_RES_SAMPLING_MULT_Y			"[SCANLINES]  Core Res Sampling Mult Y"  1 0.25 16 0.25
float HSS_CORE_RES_SAMPLING_MULT_Y = global.HSS_CORE_RES_SAMPLING_MULT_Y;

#pragma parameter HSS_INTERLACE_TRIGGER_RES 			"[SCANLINES]  Interlace Trigger Res (Also Fake Scanlines)" 600.0 0.0 2000.0 25.0
#define HSS_INTERLACE_TRIGGER_RES global.HSS_INTERLACE_TRIGGER_RES

#pragma parameter HSS_POSITION_OFFSET_X 				"[POSITION]  Position Offset X" 0 -100 100 0.1
float HSS_POSITION_OFFSET_X = global.HSS_POSITION_OFFSET_X;

#pragma parameter HSS_POSITION_OFFSET_Y 				"[POSITION]  Position Offset Y" 0 -100 100 0.1
float HSS_POSITION_OFFSET_Y = global.HSS_POSITION_OFFSET_Y;

#pragma parameter HSS_CROP_OVERSCAN_TOP 				"[CROPPING]  Crop Overscan Top" 0 -256 256 1
float HSS_CROP_OVERSCAN_TOP = global.HSS_CROP_OVERSCAN_TOP;

#pragma parameter HSS_CROP_OVERSCAN_BOTTOM 				"[CROPPING]  Crop Overscan Bottom" 0 -256 256 1
float HSS_CROP_OVERSCAN_BOTTOM = global.HSS_CROP_OVERSCAN_BOTTOM;

#pragma parameter HSS_CROP_OVERSCAN_LEFT 				"[CROPPING]  Crop Overscan Left" 0 -256 256 1
float HSS_CROP_OVERSCAN_LEFT = global.HSS_CROP_OVERSCAN_LEFT;

#pragma parameter HSS_CROP_OVERSCAN_RIGHT 				"[CROPPING]  Crop Overscan Right" 0 -256 256 1
float HSS_CROP_OVERSCAN_RIGHT = global.HSS_CROP_OVERSCAN_RIGHT;

#pragma parameter HSS_CURVATURE_MODE 					"[CURVATURE]  Curvature Mode - 0:2D 1-2:3D Sphere, 3:3D Cyl" 0 0 3 1
float HSS_CURVATURE_MODE = global.HSS_CURVATURE_MODE;

#pragma parameter HSS_CURVATURE_3D_RADIUS 				"[CURVATURE]  3D Radius" 2 0.16 1024 0.01
float HSS_CURVATURE_3D_RADIUS = global.HSS_CURVATURE_3D_RADIUS;

#pragma parameter HSS_CURVATURE_3D_VIEW_DIST 			"[CURVATURE]  3D View Distance" 2 0.5 1024 0.05
float HSS_CURVATURE_3D_VIEW_DIST = global.HSS_CURVATURE_3D_VIEW_DIST;

#pragma parameter HSS_CURVATURE_3D_TILT_ANGLE_X 		"[CURVATURE]  3D Tilt Angle X" 0 -3.1415 3.1415 0.01745
float HSS_CURVATURE_3D_TILT_ANGLE_X = global.HSS_CURVATURE_3D_TILT_ANGLE_X;

#pragma parameter HSS_CURVATURE_3D_TILT_ANGLE_Y 		"[CURVATURE]  3D Tilt Angle Y" 0 -3.1415 3.1415 0.01745
float HSS_CURVATURE_3D_TILT_ANGLE_Y = global.HSS_CURVATURE_3D_TILT_ANGLE_Y;

#pragma parameter HSS_CURVATURE_2D_LONG_AXIS 			"[CURVATURE]  2D/Extra3D Curvature on Long Axis - Def 2" 2 0 100 0.2
#define HSS_CURVATURE_2D_LONG_AXIS global.HSS_CURVATURE_2D_LONG_AXIS

#pragma parameter HSS_CURVATURE_2D_SHORT_AXIS 			"[CURVATURE]  2D/Extra3D Curvature on Short Axis - Def 3" 3 0 100 0.2
#define HSS_CURVATURE_2D_SHORT_AXIS global.HSS_CURVATURE_2D_SHORT_AXIS

// #pragma parameter HSS_CURVATURE_POST_SCALE_X 			"[CURVATURE POST SCALE]  Scale X" 100 70 130 0.2
// #pragma parameter HSS_CURVATURE_POST_SCALE_Y 			"[CURVATURE POST SCALE]  Scale Y" 100 70 130 0.2
// #define HSS_CURVATURE_POST_SCALE_X 100
// #define HSS_CURVATURE_POST_SCALE_Y 100

#pragma parameter HSS_COLOR_CRT_PROFILE 				"[COLOR]  CRT Profile: sRGB,BVM,P22,SMPTE-C,Philips,Trinit,LUT" 6 -1 6 1
#define HSS_COLOR_CRT_PROFILE global.HSS_COLOR_CRT_PROFILE

#pragma parameter HSS_COLOR_SPACE 						"[COLOR]  Color Space: sRGB, DCI, Adobe, Rec.2020" 0 0 3 1
#define HSS_COLOR_SPACE global.HSS_COLOR_SPACE

#pragma parameter HSS_COLOR_TEMPERATURE   				"[COLOR]  Temperature - Def -50" -50 -100 100 5
#define HSS_COLOR_TEMPERATURE global.HSS_COLOR_TEMPERATURE

#pragma parameter HSS_COLOR_SATURATION    				"[COLOR]  Saturation" 1.0 0.0 2.0 0.01
#define HSS_COLOR_SATURATION global.HSS_COLOR_SATURATION

#pragma parameter HSS_COLOR_LUMINANCE   				"[COLOR]  Luminance" 100 0 400 1
#define HSS_COLOR_LUMINANCE global.HSS_COLOR_LUMINANCE

#pragma parameter HSS_COLOR_BLACK_LEVEL 				"[COLOR]  Black Level - Def -0.1" -0.1 -30 30 0.01
#define HSS_COLOR_BLACK_LEVEL global.HSS_COLOR_BLACK_LEVEL

#pragma parameter HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS	"[COLOR]  Negative Crop Brightness - Def 0.05" 0.05 0 20 0.01
#define HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS global.HSS_COLOR_NEGATIVE_CROP_BRIGHTNESS

#pragma parameter HSS_COLOR_CRT_GAMMA   				"[COLOR]  CRT Gamma - Def 2.4" 2.4 0.1 5 0.05
#define HSS_COLOR_CRT_GAMMA global.HSS_COLOR_CRT_GAMMA

#pragma parameter HSS_PHOSPHOR_PERSISTENCE             "[PHOSPHOR PERSISTENCE]  Amount - Pos:Blue, Neg:Neutral" 0 -1 1 0.05
#define HSS_PHOSPHOR_PERSISTENCE global.HSS_PHOSPHOR_PERSISTENCE

#pragma parameter HSS_SCREENFX_CORNER_RADIUS 			"[SCREEN FX]  Screen Corner Radius - Def 10" 10 0 70 1
#define HSS_SCREENFX_CORNER_RADIUS global.HSS_SCREENFX_CORNER_RADIUS

#pragma parameter HSS_SCREENFX_EDGE_SHARPNESS 			"[SCREEN FX]  Screen Edge Sharpness - Def 0.4" 0.4 0 1 0.01
#define HSS_SCREENFX_EDGE_SHARPNESS global.HSS_SCREENFX_EDGE_SHARPNESS

#pragma parameter HSS_SCREENFX_VIGNETTE                "[SCREEN FX]  Screen Vignette" 0 0 1 0.01
#define HSS_SCREENFX_VIGNETTE global.HSS_SCREENFX_VIGNETTE

#pragma parameter HSS_SCREENFX_FAKE_SCANLINE_OPACITY 	"[SCREEN FX]  Fake 240p Scanline Opacity - Def 0.7" 0.7 0 1 0.05
#define HSS_SCREENFX_FAKE_SCANLINE_OPACITY global.HSS_SCREENFX_FAKE_SCANLINE_OPACITY

#pragma parameter HSS_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF 	"[SCREEN FX]  Fake 240p Scanline Brightness Cutoff - Def 3" 3 0 10 0.05
#define HSS_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF global.HSS_SCREENFX_FAKE_SCANLINE_BRIGHTNESS_CUTOFF

#pragma parameter HSS_TUBE_BLACK_EDGE_THICKNESS 		"[TUBE]  Black Edge Thickness" 1.2 -2 8 0.05
#define HSS_TUBE_BLACK_EDGE_THICKNESS global.HSS_TUBE_BLACK_EDGE_THICKNESS

// TODO this black edge curvature isn't doing anything anymore
#pragma parameter HSS_TUBE_BLACK_CURVATURE_SCALE 	"[TUBE]  Black Edge Curvature Scale" 1 0 4 0.1
#define HSS_TUBE_BLACK_CURVATURE_SCALE global.HSS_TUBE_BLACK_CURVATURE_SCALE

// #pragma parameter extra_1 	"Extra 1" 1 0 4 0.1
// #pragma parameter extra_2 	"Extra 2" 1 0 4 0.1
// #pragma parameter extra_3 	"Extra 3" 1 0 4 0.1

#define HSS_SCREENFX_SCANLINE_RES 240
#define HSS_DEFAULT_CRT_GAMMA 2.4
#define HSS_DEFAULT_SRGB_GAMMA 2.2
