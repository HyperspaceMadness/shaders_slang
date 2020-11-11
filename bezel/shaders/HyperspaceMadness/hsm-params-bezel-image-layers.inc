// Edited 2020-10-24-11:02

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
#pragma parameter H_IMAGE_LAYERING_TITLE "_____[ IMAGE LAYERING ]________________________________________" 0 0 0 0

//---------------------------------------------------------------------------------------------------
//    STATIC ELEMENT GAMMA
//---------------------------------------------------------------------------------------------------
#pragma parameter H_STATIC_LAYERS_GAMMA				"[ STATIC LAYERS GAMMA ]  Gamma Adjust" 1 0.01 5 0.01
float H_STATIC_LAYERS_GAMMA = global.H_STATIC_LAYERS_GAMMA;


//---------------------------------------------------------------------------------------------------
//    NIGHT LIGHTING IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_NIGHT_LIGHTING_TITLE "_____[ NIGHT LIGHTING ]________________________________________" 0 0 0 0

#pragma parameter H_NIGHT_OPACITY       "[ NIGHT LIGHTING ]  Opacity"  0 0 100 1
float H_NIGHT_OPACITY = global.H_NIGHT_OPACITY / 100;

#pragma parameter H_NIGHT_MIRROR_HORZ       "[ NIGHT LIGHTING ]  Mirror H"  0 0 1 1
float H_NIGHT_MIRROR_HORZ = global.H_NIGHT_MIRROR_HORZ;

#pragma parameter H_NIGHT_SATURATION    "[ NIGHT LIGHTING ]  Saturation"  100 0 300 1
float H_NIGHT_SATURATION = global.H_NIGHT_SATURATION / 100;

#pragma parameter H_NIGHT_HUE    "[ NIGHT LIGHTING ]  Hue"  0 -180 180 1
float H_NIGHT_HUE = global.H_NIGHT_HUE / 360;

#pragma parameter H_NIGHT_VALUE    "[ NIGHT LIGHTING ]  Value"  100 0 400 1
float H_NIGHT_VALUE = global.H_NIGHT_VALUE / 100;

#pragma parameter H_NIGHT_DITHERING_SAMPLES  "[ NIGHT LIGHTING ]  Dithering Noise Samples (Reduces Banding)" 0 0 10 1
float H_NIGHT_DITHERING_SAMPLES = global.H_NIGHT_DITHERING_SAMPLES;


#pragma parameter H_LAYER_ORDER_TITLE			"_____[ LAYER ORDER ]___________________________________________" 0 0 0 0

#pragma parameter H_BG_LAYER_ORDER              "[ LAYER ORDER ]  BG Image"  2 0 22 1
float H_BG_LAYER_ORDER = global.H_BG_LAYER_ORDER;

#pragma parameter H_CRT_LAYER_ORDER             "[ LAYER ORDER ]  CRT Screen"  4 0 22 1
float H_CRT_LAYER_ORDER = global.H_CRT_LAYER_ORDER;

#pragma parameter H_BZL_IMG_LAYER_ORDER         "[ LAYER ORDER ]  Bezel Image"  6 0 22 1
float H_BZL_IMG_LAYER_ORDER = global.H_BZL_IMG_LAYER_ORDER;

#pragma parameter H_BZL_LAYER_ORDER             "[ LAYER ORDER ]  Bezel (Generated)"  8 0 22 1
float H_BZL_LAYER_ORDER = global.H_BZL_LAYER_ORDER;

#pragma parameter H_FRM_LAYER_ORDER             "[ LAYER ORDER ]  Frame (Generated)"  10 0 22 1
float H_FRM_LAYER_ORDER = global.H_FRM_LAYER_ORDER;

#pragma parameter H_CAB_GLASS_LAYER_ORDER       "[ LAYER ORDER ]  Cabinet Glass Image"  12 0 22 1
float H_CAB_GLASS_LAYER_ORDER = global.H_CAB_GLASS_LAYER_ORDER;

#pragma parameter H_DECAL_LAYER_ORDER           "[ LAYER ORDER ]  Decal Image"  14 0 22 1
float H_DECAL_LAYER_ORDER = global.H_DECAL_LAYER_ORDER;

#pragma parameter H_REFLECTION_LAYER_ORDER      "[ LAYER ORDER ]  Reflection (Generated)"  16 0 22 1
float H_REFLECTION_LAYER_ORDER = global.H_REFLECTION_LAYER_ORDER;

#pragma parameter H_LED_LAYER_ORDER             "[ LAYER ORDER ]  LED Image"  18 0 22 1
float H_LED_LAYER_ORDER = global.H_LED_LAYER_ORDER;

#pragma parameter H_TOP_LAYER_ORDER             "[ LAYER ORDER ]  Top Image"  20 0 22 1
float H_TOP_LAYER_ORDER = global.H_TOP_LAYER_ORDER;


//---------------------------------------------------------------------------------------------------
//    CutOut in Image Layers
//---------------------------------------------------------------------------------------------------
#pragma parameter H_CUTOUT_TITLE			"_____[ CUTOUT ]________________________________________________" 0 0 0 0

#pragma parameter H_CUTOUT_SCALE_MODE           "[CUTOUT] Scale Mode - Full | Tube | Bzl | BG | Bzl Img | Decal"  0 0 5 1
float H_CUTOUT_SCALE_MODE = global.H_CUTOUT_SCALE_MODE;

#pragma parameter H_CUTOUT_SCALE 				"[ CUTOUT ]  Scale" 100 -100 200 0.1
float H_CUTOUT_SCALE = global.H_CUTOUT_SCALE / 100;

#pragma parameter H_CUTOUT_SCALE_X 		        "[ CUTOUT ]  Scale X" 100 -100 200 0.1
float H_CUTOUT_SCALE_X = global.H_CUTOUT_SCALE_X / 100;

#pragma parameter H_CUTOUT_POS_Y 		        "[ CUTOUT ] Position Y" 0 -100 200 0.1
float H_CUTOUT_POS_Y = global.H_CUTOUT_POS_Y / 100;

#pragma parameter H_CUTOUT_CORNER_RADIUS 		"[ CUTOUT ]  Corner Radius - Def 0" 0 0 70 1
float H_CUTOUT_CORNER_RADIUS = global.H_CUTOUT_CORNER_RADIUS;


//---------------------------------------------------------------------------------------------------
//    MASK DEBUG
//---------------------------------------------------------------------------------------------------
#pragma parameter H_LAYERING_DEBUG_MASK_MODE    "[ DEBUG ]  Mask - ALL | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" -1 -2 7 1
float H_LAYERING_DEBUG_MASK_MODE = global.H_LAYERING_DEBUG_MASK_MODE;


//---------------------------------------------------------------------------------------------------
//    BG IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_BACKGROUND_TITLE			"_____[ BACKGROUND ]____________________________________________" 0 0 0 0

#pragma parameter H_BG_OPACITY               "[ BG ]  Opacity" 100 0 100 1
float H_BG_OPACITY = global.H_BG_OPACITY / 100;

#pragma parameter H_BG_BLEND_MODE               "[ BG ]  Blend Mode - Off | Normal | Add | Multiply"  1 -1 2 1
float H_BG_BLEND_MODE = global.H_BG_BLEND_MODE;

#pragma parameter H_BG_MASK_MODE                "[ BG ]  Mask - ALL | Tube | Bz- | Bz | Bz+ | Fram | Fram+ | BG" 0 0 7 1
float H_BG_MASK_MODE = global.H_BG_MASK_MODE;

#pragma parameter H_BG_CUTOUT_MODE              "[ BG ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float H_BG_CUTOUT_MODE = global.H_BG_CUTOUT_MODE;

#pragma parameter H_BG_BRIGHTNESS               "[ BG ]  Brightness" 100 0 600 0.5
float H_BG_BRIGHTNESS = global.H_BG_BRIGHTNESS / 100;

#pragma parameter H_BG_VIGNETTE_OPACITY         "[ BG ]  Vignette Opacity" 50 0 100 2
float H_BG_VIGNETTE_OPACITY = global.H_BG_VIGNETTE_OPACITY / 100;

#pragma parameter H_BG_APPLY_ADJUSTMENT         "[ BG ] Apply NightLight & Static Gamma (0 for Backdrop)"  1 0 1 1
float H_BG_APPLY_ADJUSTMENT = global.H_BG_APPLY_ADJUSTMENT;

#pragma parameter H_BG_SCALE_MODE               "[ BG ]  Scale Mode - FullScreen | Tube | Bezel" 0 0 2 1
float H_BG_SCALE_MODE = global.H_BG_SCALE_MODE;

#pragma parameter H_BG_SCALE_KEEP_ASPECT        "[ BG ]  Keep Aspect"  1 0 1 1
float H_BG_SCALE_KEEP_ASPECT = global.H_BG_SCALE_KEEP_ASPECT;

#pragma parameter H_BG_SCALE                    "[ BG ]  Scale" 100 0 1000 0.1
float H_BG_SCALE = global.H_BG_SCALE / 100;

#pragma parameter H_BG_SCALE_X                  "[ BG ]  Scale X" 100 0 1000 0.1
float H_BG_SCALE_X = global.H_BG_SCALE_X / 100;

#pragma parameter H_BG_POS_Y                    "[ BG ]  Position Y" 0 -100 100 0.1
float H_BG_POS_Y = global.H_BG_POS_Y / 100;

#pragma parameter H_BG_MIRROR_WRAP              "[ BG ]  Mirror Wrap" 1 0 1 1
float H_BG_MIRROR_WRAP = global.H_BG_MIRROR_WRAP;


//---------------------------------------------------------------------------------------------------
//    CRT Layer
//---------------------------------------------------------------------------------------------------
#pragma parameter H_CRT_TITLE			"_____[ CRT SCREEN LAYER ]______________________________________" 0 0 0 0

#pragma parameter H_CRT_SCREEN_BLEND_MODE  "[ CRT SCREEN ]  Blend Mode - Off | Normal | Add (Backdrop)" 1 0 3 1
float H_CRT_SCREEN_BLEND_MODE = global.H_CRT_SCREEN_BLEND_MODE;


//---------------------------------------------------------------------------------------------------
//    BEZEL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_BZL_IMG_TITLE			       "_____[ BEZEL IMAGE LAYER ]_____________________________________" 0 0 0 0

#pragma parameter H_BZL_IMG_OPACITY               "[ BEZEL IMG ]  Opacity" 0 0 100 1
float H_BZL_IMG_OPACITY = global.H_BZL_IMG_OPACITY / 100;

#pragma parameter H_BZL_IMG_HUE                   "[ BEZEL IMG ]  Hue Offset" 0 0 360 1
float H_BZL_IMG_HUE = global.H_BZL_IMG_HUE / 360;

#pragma parameter H_BZL_IMG_SATURATION            "[ BEZEL IMG ]  Saturation" 100 0 200 1
float H_BZL_IMG_SATURATION = global.H_BZL_IMG_SATURATION / 100;

#pragma parameter H_BZL_IMG_BRIGHTNESS            "[ BEZEL IMG ]  Brightness" 100 0 200 1
float H_BZL_IMG_BRIGHTNESS = global.H_BZL_IMG_BRIGHTNESS / 100;

#pragma parameter H_BZL_IMG_BLEND_MODE            "[ BEZEL IMG ]  Blend Mode -  Off | Normal | Add | Multiply"  1 0 3 1
float H_BZL_IMG_BLEND_MODE = global.H_BZL_IMG_BLEND_MODE;

#pragma parameter H_BZL_IMG_MASK_MODE             "[BEZEL IMG] Mask- ALL | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 3 0 7 1
float H_BZL_IMG_MASK_MODE = global.H_BZL_IMG_MASK_MODE;

#pragma parameter H_BZL_IMG_CUTOUT_MODE           "[ BEZEL IMG ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float H_BZL_IMG_CUTOUT_MODE = global.H_BZL_IMG_CUTOUT_MODE;

#pragma parameter H_BZL_IMG_SCALE_MODE            "[ BEZEL IMG ]  Scale Mode - FullScreen | Tube | Bezel | BG"  1 0 3 1
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
//    CAB GLASS IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_CAB_GLASS_TITLE			"_____[ CABINET OR CABINET GLASS ]______________________________" 0 0 0 0

#pragma parameter H_CAB_GLASS_OPACITY           "[ CAB GLASS ]  Opacity" 0 0 100 1
float H_CAB_GLASS_OPACITY = global.H_CAB_GLASS_OPACITY / 100;

#pragma parameter H_CAB_GLASS_BRIGHTNESS        "[ CAB GLASS ]  Brightness" 100 0 400 1
float H_CAB_GLASS_BRIGHTNESS = global.H_CAB_GLASS_BRIGHTNESS / 100;

#pragma parameter H_CAB_GLASS_BLEND_MODE        "[ CAB GLASS ]  Blend Mode - Off | Normal | Add | Multiply"  1 0 3 1
float H_CAB_GLASS_BLEND_MODE = global.H_CAB_GLASS_BLEND_MODE;

#pragma parameter H_CAB_GLASS_MASK_MODE         "[CAB GLASS] Mask- ALL | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 0 0 7 1
float H_CAB_GLASS_MASK_MODE = global.H_CAB_GLASS_MASK_MODE;

#pragma parameter H_CAB_GLASS_CUTOUT_MODE       "[ CAB GLASS ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float H_CAB_GLASS_CUTOUT_MODE = global.H_CAB_GLASS_CUTOUT_MODE;

#pragma parameter H_CAB_GLASS_SCALE_MODE        "[CAB GLASS] Scale Mode- Full | BG | Tube | Bzl | Decal | TopImg" 0 0 5 1
float H_CAB_GLASS_SCALE_MODE = global.H_CAB_GLASS_SCALE_MODE;

#pragma parameter H_CAB_GLASS_SCALE_KEEP_ASPECT "[ CAB GLASS ]  Keep Aspect"  1 0 1 1
float H_CAB_GLASS_SCALE_KEEP_ASPECT = global.H_CAB_GLASS_SCALE_KEEP_ASPECT;

#pragma parameter H_CAB_GLASS_SCALE             "[ CAB GLASS ]  Scale" 100 10 500 1
float H_CAB_GLASS_SCALE = global.H_CAB_GLASS_SCALE / 100;

#pragma parameter H_CAB_GLASS_SCALE_X             "[ CAB GLASS ]  Scale X" 100 10 500 1
float H_CAB_GLASS_SCALE_X = global.H_CAB_GLASS_SCALE_X / 100;

#pragma parameter H_CAB_GLASS_POS_Y             "[ CAB GLASS ]  Position Y" 0 10 500 1
float H_CAB_GLASS_POS_Y = global.H_CAB_GLASS_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    DECAL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_DECAL_TITLE			       "_____[ DECAL LAYER ]___________________________________________" 0 0 0 0

#pragma parameter H_DECAL_OPACITY               "[ DECAL ]  Opacity"  0 0 100 5
float H_DECAL_OPACITY = global.H_DECAL_OPACITY / 100;

#pragma parameter H_DECAL_BLEND_MODE            "[ DECAL ]  Blend Mode -  Off | Normal | Add | Multiply"  1 0 3 1
float H_DECAL_BLEND_MODE = global.H_DECAL_BLEND_MODE;

#pragma parameter H_DECAL_MASK_MODE             "[ DECAL ] Mask- ALL | Tube | Bz- | Bz | Bz+ | Fram | Fram+ | BG"   0 0 7 1
float H_DECAL_MASK_MODE = global.H_DECAL_MASK_MODE;

#pragma parameter H_DECAL_CUTOUT_MODE            "[ DECAL ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float H_DECAL_CUTOUT_MODE = global.H_DECAL_CUTOUT_MODE;

#pragma parameter H_DECAL_SCALE_MODE            "[ DECAL ]  Scale Mode - Full | Tube | Bezel | BG | Bzl Img"  2 0 4 1
float H_DECAL_SCALE_MODE = global.H_DECAL_SCALE_MODE;

#pragma parameter H_DECAL_SCALE_KEEP_ASPECT     "[ DECAL ]  Scale Keep Aspect"  1 0 1 1
float H_DECAL_SCALE_KEEP_ASPECT = global.H_DECAL_SCALE_KEEP_ASPECT;

#pragma parameter H_DECAL_SCALE                 "[ DECAL ]  Scale"  100 50 500 0.1
float H_DECAL_SCALE = global.H_DECAL_SCALE / 100;

#pragma parameter H_DECAL_SCALE_X                "[ DECAL ]  Scale X"  100 50 500 0.1
float H_DECAL_SCALE_X = global.H_DECAL_SCALE_X / 100;

#pragma parameter H_DECAL_POS_Y                 "[ DECAL ]  Position Y"  0 -100 100 0.1
float H_DECAL_POS_Y = global.H_DECAL_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    LED IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_LED_TITLE			       "_____[ LED LAYER ]_____________________________________________" 0 0 0 0

#pragma parameter H_LED_OPACITY                 "[ LED ]  Opacity"  0 0 100 1
float H_LED_OPACITY = global.H_LED_OPACITY / 100;

#pragma parameter H_LED_BLEND_MODE              "[ LED ]  Blend Mode - Off | Normal | Add | Multiply"  2 0 3 1
float H_LED_BLEND_MODE = global.H_LED_BLEND_MODE;

#pragma parameter H_LED_MASK_MODE               "[ LED ]  Mask - ALL | Tube | Bz- | Bz | Bz+ | Fram | Fram+ | BG"   7 0 7 1
float H_LED_MASK_MODE = global.H_LED_MASK_MODE;

#pragma parameter H_LED_CUTOUT_MODE             "[ LED ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float H_LED_CUTOUT_MODE = global.H_LED_CUTOUT_MODE;

#pragma parameter H_LED_SCALE_MODE              "[ LED ] Scale Mode - Full | Tube | Bezel | BG | Bzl Img | Decal"  0 0 5 1
float H_LED_SCALE_MODE = global.H_LED_SCALE_MODE;

#pragma parameter H_LED_SCALE_KEEP_ASPECT       "[ LED ]  Scale Keep Aspect"  1 0 1 1
float H_LED_SCALE_KEEP_ASPECT = global.H_LED_SCALE_KEEP_ASPECT;

#pragma parameter H_LED_SCALE                   "[ LED ]  Scale" 100 0 1000 0.1
float H_LED_SCALE = global.H_LED_SCALE / 100;

#pragma parameter H_LED_SCALE_X                 "[ LED ]  Scale X" 100 0 1000 0.1
float H_LED_SCALE_X = global.H_LED_SCALE_X / 100;

#pragma parameter H_LED_POS_Y                   "[ LED ]  Position Y"  0 -100 100 0.1
float H_LED_POS_Y = global.H_LED_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    TOP IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter H_TOP_TITLE			       "_____[ TOP EXTRA LAYER ]_______________________________________" 0 0 0 0

#pragma parameter H_TOP_OPACITY                 "[ TOP ]  Opacity"  0 0 100 0.1
float H_TOP_OPACITY = global.H_TOP_OPACITY / 100;

#pragma parameter H_TOP_BLEND_MODE              "[ TOP ]  Blend Mode - Off | Normal | Add | Multiply"  1 0 3 1
float H_TOP_BLEND_MODE = global.H_TOP_BLEND_MODE;

#pragma parameter H_TOP_MASK_MODE               "[ TOP ]  Mask - ALL | Tube | Bz- | Bz | Bz+ | Fram | Fram+ | BG"   0 0 7 1
float H_TOP_MASK_MODE = global.H_TOP_MASK_MODE;

#pragma parameter H_TOP_CUTOUT_MODE             "[ TOP ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float H_TOP_CUTOUT_MODE = global.H_TOP_CUTOUT_MODE;

#pragma parameter H_TOP_SCALE_MODE              "[ TOP ] Scale Mode - Full | Tube | Bezel | BG | Bzl Img | Decal"  0 0 5 1
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

