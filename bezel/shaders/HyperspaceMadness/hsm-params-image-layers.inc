//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//
//    Image Compositing Pass Parameters Start
//
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
//    IMAGE LAYERING START
//---------------------------------------------------------------------------------------------------
#pragma parameter H_IMAGE_LAYERING_TITLE "_____[ GRAPHIC ELEMENTS LAYERING ]_____________________________" 0 0 0 0

//---------------------------------------------------------------------------------------------------
//    STATIC ELEMENT GAMMA
//---------------------------------------------------------------------------------------------------
#pragma parameter H_STATIC_LAYERS_GAMMA				"[ STATIC LAYERS GAMMA ]  Gamma Adjust _________________________" 1 0.01 5 0.01
float H_STATIC_LAYERS_GAMMA = global.H_STATIC_LAYERS_GAMMA;

//---------------------------------------------------------------------------------------------------
//    NIGHT LIGHTING IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_NLIGHT_IMG_OPACITY       "[ NIGHT LIGHTING ]  Opacity ___________________________________"  0 0 100 1
float H_NLIGHT_IMG_OPACITY = global.H_NLIGHT_IMG_OPACITY / 100;

#pragma parameter H_NLIGHT_IMG_MIRROR_HORZ       "[ NIGHT LIGHTING ]  Mirror H"  0 0 1 1
float H_NLIGHT_IMG_MIRROR_HORZ = global.H_NLIGHT_IMG_MIRROR_HORZ;

#pragma parameter H_NLIGHT_IMG_SATURATION    "[ NIGHT LIGHTING ]  Saturation"  100 0 300 1
float H_NLIGHT_IMG_SATURATION = global.H_NLIGHT_IMG_SATURATION / 100;

#pragma parameter H_NLIGHT_IMG_HUE    "[ NIGHT LIGHTING ]  Hue"  0 -180 180 1
float H_NLIGHT_IMG_HUE = global.H_NLIGHT_IMG_HUE / 360;

#pragma parameter H_NLIGHT_IMG_VALUE    "[ NIGHT LIGHTING ]  Value"  100 0 400 1
float H_NLIGHT_IMG_VALUE = global.H_NLIGHT_IMG_VALUE / 100;

#pragma parameter H_NLIGHT_IMG_DITHERING_SAMPLES  "[ NIGHTLIGHTING ]  Dithering Noise Samples (Reduces Banding)" 0 0 10 1
float H_NLIGHT_IMG_DITHERING_SAMPLES = global.H_NLIGHT_IMG_DITHERING_SAMPLES;


//---------------------------------------------------------------------------------------------------
//    CutOut in Image Layers
//---------------------------------------------------------------------------------------------------

#pragma parameter H_IMG_CUTOUT_WIDTH 				"[ IMAGE CUTOUT ]  Width - Def 1" 1 -100 200 0.1
float H_IMG_CUTOUT_WIDTH = global.H_IMG_CUTOUT_WIDTH / 100;

#pragma parameter H_IMG_CUTOUT_HEIGHT 				"[ IMAGE CUTOUT ]  Height - Def 1" 1 -100 200 0.1
float H_IMG_CUTOUT_HEIGHT = global.H_IMG_CUTOUT_HEIGHT / 100;

#pragma parameter H_IMG_CUTOUT_CORNER_RADIUS 		"[ IMAGE CUTOUT ]  Corner Radius - Def 0" 0 0 70 1
float H_IMG_CUTOUT_CORNER_RADIUS = global.H_IMG_CUTOUT_CORNER_RADIUS;


//---------------------------------------------------------------------------------------------------
//    LAYERING DEBUG
//---------------------------------------------------------------------------------------------------
#pragma parameter H_LAYERING_DEBUG_MASK_MODE    "[ DEBUG ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG  ___" -1 -1 7 1
float H_LAYERING_DEBUG_MASK_MODE = global.H_LAYERING_DEBUG_MASK_MODE;


//---------------------------------------------------------------------------------------------------
//    BG IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_BG_IMG_BRIGHTNESS "[ BACKGROUND ]  Brightness ____________________________________" 100 0 600 0.5
float H_BG_IMG_BRIGHTNESS = global.H_BG_IMG_BRIGHTNESS / 100;

#pragma parameter H_BG_IMG_VIGNETTE_OPACITY "[ BACKGROUND ]  Vignette Opacity" 50 0 100 2
float H_BG_IMG_VIGNETTE_OPACITY = global.H_BG_IMG_VIGNETTE_OPACITY / 100;

#pragma parameter H_BG_IMG_APPLY_ADJUSTMENT    "[ BACKGROUND ] Apply NightLight & Static Gamma (0 for Backdrop)"  1 0 1 1
float H_BG_IMG_APPLY_ADJUSTMENT = global.H_BG_IMG_APPLY_ADJUSTMENT;

#pragma parameter H_BG_IMG_MASK_MODE   "[ BACKGROUND ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG" 1 0 7 1
float H_BG_IMG_MASK_MODE = global.H_BG_IMG_MASK_MODE;

#pragma parameter H_BG_IMG_SCALE_MODE       "[ BACKGROUND ]  Scale Mode - 0:FullScreen, 1:Tube, 2:Bezel" 0 0 2 1
float H_BG_IMG_SCALE_MODE = global.H_BG_IMG_SCALE_MODE;

#pragma parameter H_BG_IMG_SCALE_KEEP_ASPECT      "[ BACKGROUND ]  Keep Aspect"  1 0 1 1
float H_BG_IMG_SCALE_KEEP_ASPECT = global.H_BG_IMG_SCALE_KEEP_ASPECT;

#pragma parameter H_BG_IMG_SCALE            "[ BACKGROUND ]  Scale" 100 0 1000 0.1
float H_BG_IMG_SCALE = global.H_BG_IMG_SCALE / 100;

#pragma parameter H_BG_IMG_SCALE_X            "[ BACKGROUND ]  Scale X" 100 0 1000 0.1
float H_BG_IMG_SCALE_X = global.H_BG_IMG_SCALE_X / 100;

#pragma parameter H_BG_IMG_POS_Y            "[ BACKGROUND ]  Position Y" 0 -100 100 0.1
float H_BG_IMG_POS_Y = global.H_BG_IMG_POS_Y / 100;

#pragma parameter H_BG_IMG_MIRROR_WRAP      "[ BACKGROUND ]  Mirror Wrap" 1 0 1 1
float H_BG_IMG_MIRROR_WRAP = global.H_BG_IMG_MIRROR_WRAP;


//---------------------------------------------------------------------------------------------------
//    CRT Layer
//---------------------------------------------------------------------------------------------------
#pragma parameter H_CRT_SCREEN_BLEND_MODE  "[ CRT SCREEN ]  Blend Mode -  -1:Off 0:Normal, 1:Add (Backdrop)" 0 -1 1 1
float H_CRT_SCREEN_BLEND_MODE = global.H_CRT_SCREEN_BLEND_MODE;


//---------------------------------------------------------------------------------------------------
//    GLASS IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_CAB_GLS_OPACITY           "[ CAB GLASS ]  Opacity ________________________________________" 0 0 100 0.05
float H_CAB_GLS_OPACITY = global.H_CAB_GLS_OPACITY / 100;

#pragma parameter H_CAB_GLS_BRIGHTNESS        "[ CAB GLASS ]  Brightness" 100 0 200 1
float H_CAB_GLS_BRIGHTNESS = global.H_CAB_GLS_BRIGHTNESS / 100;

#pragma parameter H_CAB_GLS_BLEND_MODE        "[ CAB GLASS ]  Blend Mode  -1:Off 0:Normal, 1:Add, 2:Multiply"  1 -1 2 1
float H_CAB_GLS_BLEND_MODE = global.H_CAB_GLS_BLEND_MODE;

#pragma parameter H_CAB_GLS_MASK_MODE         "[ CAB GLASS ] Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG" 1 0 7 1
float H_CAB_GLS_MASK_MODE = global.H_CAB_GLS_MASK_MODE;

#pragma parameter H_CAB_GLS_CUTOUT_MODE       "[ CAB GLASS ]  Image Cutout Mode - 0:OFF 1:ON 2:Invert" 0 0 2 1
float H_CAB_GLS_CUTOUT_MODE = global.H_CAB_GLS_CUTOUT_MODE;

#pragma parameter H_CAB_GLS_DEPTH_ORDER       "[ CAB GLASS ]  Depth Order - Under Frame, Over LED"  0 0 1 1
float H_CAB_GLS_DEPTH_ORDER = global.H_CAB_GLS_DEPTH_ORDER;

#pragma parameter H_CAB_GLS_SCALE_MODE        "[ CAB GLASS ]  Scale Mode - Full, BG, Tube, Bzl, Decal, TopImg" 2 0 5 1
float H_CAB_GLS_SCALE_MODE = global.H_CAB_GLS_SCALE_MODE;

#pragma parameter H_CAB_GLS_SCALE             "[ CAB GLASS ]  Scale" 120 10 500 1
float H_CAB_GLS_SCALE = global.H_CAB_GLS_SCALE / 100;


//---------------------------------------------------------------------------------------------------
//    BEZEL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_BZL_IMG_OPACITY               "[ BEZEL IMG ]  Opacity ________________________________________" 0 0 100 1
float H_BZL_IMG_OPACITY = global.H_BZL_IMG_OPACITY / 100;

#pragma parameter H_BZL_IMG_HUE                   "[ BEZEL IMG ]  Hue Offset" 0 0 360 1
float H_BZL_IMG_HUE = global.H_BZL_IMG_HUE / 360;

#pragma parameter H_BZL_IMG_SATURATION            "[ BEZEL IMG ]  Saturation" 100 0 200 1
float H_BZL_IMG_SATURATION = global.H_BZL_IMG_SATURATION / 100;

#pragma parameter H_BZL_IMG_BRIGHTNESS            "[ BEZEL IMG ]  Brightness" 100 0 200 1
float H_BZL_IMG_BRIGHTNESS = global.H_BZL_IMG_BRIGHTNESS / 100;

#pragma parameter H_BZL_IMG_BLEND_MODE            "[ BEZEL IMG ]  Blend Mode -  -1:Off 0:Normal, 1:Add, 2:Multiply"  0 -1 2 1
float H_BZL_IMG_BLEND_MODE = global.H_BZL_IMG_BLEND_MODE;

#pragma parameter H_BZL_IMG_MASK_MODE             "[ BEZEL IMG ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG" 3 0 7 1
float H_BZL_IMG_MASK_MODE = global.H_BZL_IMG_MASK_MODE;

#pragma parameter H_BZL_IMG_DEPTH_ORDER            "[ BEZEL IMG ] Depth Order - UnderTube,UnderBzl,UnderFrm,OverFrm"  2 0 3 1
float H_BZL_IMG_DEPTH_ORDER = global.H_BZL_IMG_DEPTH_ORDER;

#pragma parameter H_BZL_IMG_SCALE_MODE            "[ BEZEL IMG ]  Scale Mode - 0:FullScreen, 1:Tube, 2:Bezel, 3:BG"  1 0 3 1
float H_BZL_IMG_SCALE_MODE = global.H_BZL_IMG_SCALE_MODE;

#pragma parameter H_BZL_IMG_SCALE_KEEP_ASPECT      "[ BEZEL IMG ]  Keep Aspect"  1 0 1 1
float H_BZL_IMG_SCALE_KEEP_ASPECT = global.H_BZL_IMG_SCALE_KEEP_ASPECT;

#pragma parameter H_BZL_IMG_SCALE                 "[ BEZEL IMG ]  Scale" 100 0 1000 0.1
float H_BZL_IMG_SCALE = global.H_BZL_IMG_SCALE / 100;

#pragma parameter H_BZL_IMG_SCALE_X               "[ BEZEL IMG ]  Scale X" 100 0 1000 0.1
float H_BZL_IMG_SCALE_X = global.H_BZL_IMG_SCALE_X / 100;

#pragma parameter H_BZL_IMG_POS_Y                 "[ BEZEL IMG ]  Position Y" 0 -100 100 0.1
float H_BZL_IMG_POS_Y = global.H_BZL_IMG_POS_Y / 100;

#pragma parameter H_BZL_IMG_USE_CURVATURE          "[ BEZEL IMG ]  Use Curvature"  0 0 1 1
float H_BZL_IMG_USE_CURVATURE = global.H_BZL_IMG_USE_CURVATURE;


//---------------------------------------------------------------------------------------------------
//    DECAL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_DECAL_OPACITY               "[ DECAL ]  Opacity ____________________________________________"  0 0 100 5
float H_DECAL_OPACITY = global.H_DECAL_OPACITY / 100;

#pragma parameter H_DECAL_BLEND_MODE            "[ DECAL ]  Blend Mode -   -1:Off 0:Normal, 1:Add, 2:Multiply"  0 -1 2 1
float H_DECAL_BLEND_MODE = global.H_DECAL_BLEND_MODE;

#pragma parameter H_DECAL_MASK_MODE             "[ DECAL ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   0 0 7 1
float H_DECAL_MASK_MODE = global.H_DECAL_MASK_MODE;

#pragma parameter H_DECAL_SCALE_MODE            "[ DECAL ]  Scale Mode - Full, Tube, Bezel, BG, BzlImg"  2 0 4 1
float H_DECAL_SCALE_MODE = global.H_DECAL_SCALE_MODE;

#pragma parameter H_DECAL_SCALE_KEEP_ASPECT     "[ DECAL ]  Scale Keep Aspect"  1 0 1 1
float H_DECAL_SCALE_KEEP_ASPECT = global.H_DECAL_SCALE_KEEP_ASPECT;

#pragma parameter H_DECAL_SCALE                 "[ DECAL ]  Scale"  100 50 500 0.1
float H_DECAL_SCALE = global.H_DECAL_SCALE / 100;

#pragma parameter H_DECAL_SCALE_X                 "[ DECAL ]  Scale X"  100 50 500 0.1
float H_DECAL_SCALE_X = global.H_DECAL_SCALE_X / 100;

#pragma parameter H_DECAL_POS_Y                 "[ DECAL ]  Position Y"  0 -100 100 0.1
float H_DECAL_POS_Y = global.H_DECAL_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    LED IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_LED_OPACITY                 "[ LED ]  Opacity ______________________________________________"  0 0 100 1
float H_LED_OPACITY = global.H_LED_OPACITY / 100;

#pragma parameter H_LED_BLEND_MODE              "[ LED ]  Blend Mode -  -1:Off 0:Normal, 1:Add, 2:Multiply"  1 -1 2 1
float H_LED_BLEND_MODE = global.H_LED_BLEND_MODE;

#pragma parameter H_LED_MASK_MODE               "[ LED ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   7 0 7 1
float H_LED_MASK_MODE = global.H_LED_MASK_MODE;

#pragma parameter H_LED_SCALE_MODE              "[ LED ]  Scale Mode - Full, BG, BzlImg, Decal, Top"  1 0 4 1
float H_LED_SCALE_MODE = global.H_LED_SCALE_MODE;


//---------------------------------------------------------------------------------------------------
//    TOP IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_TOP_OPACITY                 "[ TOP ]  Opacity ______________________________________________"  0 0 100 0.1
float H_TOP_OPACITY = global.H_TOP_OPACITY / 100;

#pragma parameter H_TOP_BLEND_MODE              "[ TOP ]  Blend Mode -   -1:Off 0:Normal, 1:Add, 2:Multiply"  0 -1 2 1
float H_TOP_BLEND_MODE = global.H_TOP_BLEND_MODE;

#pragma parameter H_TOP_MASK_MODE               "[ TOP ]  Mask - ALL, Tube, Bz-, Bz, Bz+, Fram, Fram+, BG"   0 0 7 1
float H_TOP_MASK_MODE = global.H_TOP_MASK_MODE;

#pragma parameter H_TOP_CUTOUT_MODE               "[ TOP ]  Image Cutout Mode - 0:OFF 1:ON 2:Invert" 0 0 2 1
float H_TOP_CUTOUT_MODE = global.H_TOP_CUTOUT_MODE;

#pragma parameter H_TOP_DEPTH_ORDER             "[ TOP ]  Depth Order - 0:Under Frame 1:Top"  1 0 1 1
float H_TOP_DEPTH_ORDER = global.H_TOP_DEPTH_ORDER;

#pragma parameter H_TOP_SCALE_MODE              "[ TOP ]  Scale Mode - FullScrn, Tube, Bezel, BG, Bzl Img, Decal"  0 0 5 1
float H_TOP_SCALE_MODE = global.H_TOP_SCALE_MODE;

#pragma parameter H_TOP_SCALE_KEEP_ASPECT       "[ TOP ]  Scale Keep Aspect"  1 0 1 1
float H_TOP_SCALE_KEEP_ASPECT = global.H_TOP_SCALE_KEEP_ASPECT;

#pragma parameter H_TOP_SCALE                   "[ TOP ]  Scale" 100 0 1000 0.1
float H_TOP_SCALE = global.H_TOP_SCALE / 100;

#pragma parameter H_TOP_SCALE_X                 "[ TOP ]  Scale X" 100 0 1000 0.1
float H_TOP_SCALE_X = global.H_TOP_SCALE_X / 100;

#pragma parameter H_TOP_POS_Y                   "[ TOP ]  Position Y"  0 -100 100 0.1
float H_TOP_POS_Y = global.H_TOP_POS_Y / 100;

#pragma parameter H_TOP_MIRROR_WRAP             "[ TOP ]  Mirror Wrap" 1 0 1 1
float H_TOP_MIRROR_WRAP = global.H_TOP_MIRROR_WRAP;
