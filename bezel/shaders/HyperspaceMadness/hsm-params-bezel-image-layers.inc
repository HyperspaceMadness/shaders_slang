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
#pragma parameter HSM_IMAGE_LAYERING_TITLE "_____[ IMAGE LAYERING ]________________________________________" 0 0 0 0

//---------------------------------------------------------------------------------------------------
//    STATIC ELEMENT GAMMA
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_STATIC_LAYERS_GAMMA				"[ STATIC LAYERS GAMMA ]  Gamma Adjust" 1 0.01 5 0.01
float HSM_STATIC_LAYERS_GAMMA = global.HSM_STATIC_LAYERS_GAMMA;


//---------------------------------------------------------------------------------------------------
//    NIGHT LIGHTING IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_NIGHT_LIGHTING_TITLE "_____[ NIGHT LIGHTING ]________________________________________" 0 0 0 0

#pragma parameter HSM_NIGHT_OPACITY       "[ NIGHT LIGHTING ]  Opacity"  0 0 100 1
float HSM_NIGHT_OPACITY = global.HSM_NIGHT_OPACITY / 100;

#pragma parameter HSM_NIGHT_MIRROR_HORZ       "[ NIGHT LIGHTING ]  Mirror H"  0 0 1 1
float HSM_NIGHT_MIRROR_HORZ = global.HSM_NIGHT_MIRROR_HORZ;

#pragma parameter HSM_NIGHT_SATURATION    "[ NIGHT LIGHTING ]  Saturation"  100 0 300 1
float HSM_NIGHT_SATURATION = global.HSM_NIGHT_SATURATION / 100;

#pragma parameter HSM_NIGHT_HUE    "[ NIGHT LIGHTING ]  Hue"  0 -180 180 1
float HSM_NIGHT_HUE = global.HSM_NIGHT_HUE / 360;

#pragma parameter HSM_NIGHT_VALUE    "[ NIGHT LIGHTING ]  Value"  100 0 400 1
float HSM_NIGHT_VALUE = global.HSM_NIGHT_VALUE / 100;

#pragma parameter HSM_NIGHT_DITHERING_SAMPLES  "[ NIGHT LIGHTING ]  Dithering Noise Samples (Reduces Banding)" 0 0 10 1
float HSM_NIGHT_DITHERING_SAMPLES = global.HSM_NIGHT_DITHERING_SAMPLES;


#pragma parameter HSM_LAYER_ORDER_TITLE			"_____[ LAYER ORDER ]___________________________________________" 0 0 0 0

#pragma parameter HSM_BG_LAYER_ORDER              "[ LAYER ORDER ]  BG Image"  4 0 44 1
float HSM_BG_LAYER_ORDER = global.HSM_BG_LAYER_ORDER;

#pragma parameter HSM_VIEWPORT_VIGNETTE_LAYER_ORDER "[ LAYER ORDER ]  Viewport Vignette"  8 0 44 1
float HSM_VIEWPORT_VIGNETTE_LAYER_ORDER = global.HSM_VIEWPORT_VIGNETTE_LAYER_ORDER;

#pragma parameter HSM_CRT_LAYER_ORDER             "[ LAYER ORDER ]  CRT Screen"  12 0 44 1
float HSM_CRT_LAYER_ORDER = global.HSM_CRT_LAYER_ORDER;

#pragma parameter HSM_BZL_IMG_LAYER_ORDER         "[ LAYER ORDER ]  Bezel Image"  16 0 44 1
float HSM_BZL_IMG_LAYER_ORDER = global.HSM_BZL_IMG_LAYER_ORDER;

#pragma parameter HSM_BZL_LAYER_ORDER             "[ LAYER ORDER ]  Bezel (Generated)"  20 0 44 1
float HSM_BZL_LAYER_ORDER = global.HSM_BZL_LAYER_ORDER;

#pragma parameter HSM_FRM_LAYER_ORDER             "[ LAYER ORDER ]  Frame (Generated)"  24 0 44 1
float HSM_FRM_LAYER_ORDER = global.HSM_FRM_LAYER_ORDER;

#pragma parameter HSM_CAB_GLASS_LAYER_ORDER       "[ LAYER ORDER ]  Cabinet Glass Image"  28 0 44 1
float HSM_CAB_GLASS_LAYER_ORDER = global.HSM_CAB_GLASS_LAYER_ORDER;

#pragma parameter HSM_DECAL_LAYER_ORDER           "[ LAYER ORDER ]  Decal Image"  32 0 44 1
float HSM_DECAL_LAYER_ORDER = global.HSM_DECAL_LAYER_ORDER;

#pragma parameter HSM_REFLECT_LAYER_ORDER      "[ LAYER ORDER ]  Reflection (Generated)"  36 0 44 1
float HSM_REFLECT_LAYER_ORDER = global.HSM_REFLECT_LAYER_ORDER;

#pragma parameter HSM_LED_LAYER_ORDER             "[ LAYER ORDER ]  LED Image"  40 0 44 1
float HSM_LED_LAYER_ORDER = global.HSM_LED_LAYER_ORDER;

#pragma parameter HSM_TOP_LAYER_ORDER             "[ LAYER ORDER ]  Top Image"  44 0 44 1
float HSM_TOP_LAYER_ORDER = global.HSM_TOP_LAYER_ORDER;


//---------------------------------------------------------------------------------------------------
//    CutOut in Image Layers
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CUTOUT_TITLE			"_____[ CUTOUT ]________________________________________________" 0 0 0 0

#pragma parameter HSM_CUTOUT_SCALE_MODE           "[CUTOUT] Scale Mode - Full | Tube | Bzl | BG | Bzl Img | Decal"  0 0 5 1
float HSM_CUTOUT_SCALE_MODE = global.HSM_CUTOUT_SCALE_MODE;

#pragma parameter HSM_CUTOUT_SCALE 				"[ CUTOUT ]  Scale" 100 -100 200 0.1
float HSM_CUTOUT_SCALE = global.HSM_CUTOUT_SCALE / 100;

#pragma parameter HSM_CUTOUT_SCALE_X 		    "[ CUTOUT ]  Scale X" 100 -100 200 0.1
float HSM_CUTOUT_SCALE_X = global.HSM_CUTOUT_SCALE_X / 100;

#pragma parameter HSM_CUTOUT_POS_Y 		        "[ CUTOUT ] Position Y" 0 -100 200 0.1
float HSM_CUTOUT_POS_Y = global.HSM_CUTOUT_POS_Y / 100;

#pragma parameter HSM_CUTOUT_CORNER_RADIUS 		"[ CUTOUT ]  Corner Radius - Def 0" 0 0 70 1
float HSM_CUTOUT_CORNER_RADIUS = global.HSM_CUTOUT_CORNER_RADIUS;


//---------------------------------------------------------------------------------------------------
//    MASK DEBUG
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_MASK_DEBUG_TITLE			"_____[ MASK DEBUG ]____________________________________________" 0 0 0 0

#pragma parameter HSM_LAYERING_DEBUG_MASK_MODE    "Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" -1 -2 8 1
float HSM_LAYERING_DEBUG_MASK_MODE = global.HSM_LAYERING_DEBUG_MASK_MODE;


//---------------------------------------------------------------------------------------------------
//    BG IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BACKGROUND_TITLE			"_____[ BACKGROUND ]____________________________________________" 0 0 0 0

#pragma parameter HSM_BG_OPACITY                  "[ BG ]  Opacity" 100 0 100 1
float HSM_BG_OPACITY = global.HSM_BG_OPACITY / 100;

#pragma parameter HSM_BG_BLEND_MODE               "[ BG ]  Blend Mode - Off | Normal | Add | Multiply"  1 -1 2 1
float HSM_BG_BLEND_MODE = global.HSM_BG_BLEND_MODE;

#pragma parameter HSM_BG_MASK_MODE                "Mask - ALL | Screen | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 0 0 8 1
float HSM_BG_MASK_MODE = global.HSM_BG_MASK_MODE;

#pragma parameter HSM_BG_CUTOUT_MODE              "[ BG ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_BG_CUTOUT_MODE = global.HSM_BG_CUTOUT_MODE;

#pragma parameter HSM_BG_BRIGHTNESS               "[ BG ]  Brightness" 100 0 600 0.5
float HSM_BG_BRIGHTNESS = global.HSM_BG_BRIGHTNESS / 100;

#pragma parameter HSM_BG_APPLY_ADJUSTMENT         "[ BG ] Apply NightLight & Static Gamma (0 for Backdrop)"  1 0 1 1
float HSM_BG_APPLY_ADJUSTMENT = global.HSM_BG_APPLY_ADJUSTMENT;

#pragma parameter HSM_BG_TEXTURE_ASPECT_MODE      "[ BG ] Texture Aspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_BG_TEXTURE_ASPECT_MODE = global.HSM_BG_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_BG_EXPLICIT_TEXTURE_ASPECT  "[ BG ]  Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_BG_EXPLICIT_TEXTURE_ASPECT = global.HSM_BG_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_BG_SCALE_MODE               "[ BG ]  Scale Mode - FullScreen | Tube | Bezel" 0 0 2 1
float HSM_BG_SCALE_MODE = global.HSM_BG_SCALE_MODE;

#pragma parameter HSM_BG_SCALE_KEEP_ASPECT        "[ BG ]  Keep Aspect"  1 0 1 1
float HSM_BG_SCALE_KEEP_ASPECT = global.HSM_BG_SCALE_KEEP_ASPECT;

#pragma parameter HSM_BG_SCALE                    "[ BG ]  Scale" 100 0 1000 0.1
float HSM_BG_SCALE = global.HSM_BG_SCALE / 100;

#pragma parameter HSM_BG_SCALE_X                  "[ BG ]  Scale X" 100 0 1000 0.1
float HSM_BG_SCALE_X = global.HSM_BG_SCALE_X / 100;

#pragma parameter HSM_BG_POS_Y                    "[ BG ]  Position Y"  0 -100 100 0.1
float HSM_BG_POS_Y = global.HSM_BG_POS_Y / 100;

#pragma parameter HSM_BG_MIRROR_WRAP              "[ BG ]  Mirror Wrap" 1 0 1 1
float HSM_BG_MIRROR_WRAP = global.HSM_BG_MIRROR_WRAP;

//---------------------------------------------------------------------------------------------------
//    VIEWPORT VIGNETTE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_VIEWPORT_VIGNETTE_TITLE			    "_____[ VIEWPORT VIGNETTE ]_____________________________________" 0 0 0 0

#pragma parameter HSM_VIEWPORT_VIGNETTE_OPACITY            "[ VIGNETTE ]  Opacity" 50 0 100 2
float HSM_VIEWPORT_VIGNETTE_OPACITY = global.HSM_VIEWPORT_VIGNETTE_OPACITY / 100;

#pragma parameter HSM_VIEWPORT_VIGNETTE_MASK_MODE          "Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 5 0 8 1
float HSM_VIEWPORT_VIGNETTE_MASK_MODE = global.HSM_VIEWPORT_VIGNETTE_MASK_MODE;

#pragma parameter HSM_VIEWPORT_VIGNETTE_CUTOUT_MODE        "[ VIGNETTE ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_VIEWPORT_VIGNETTE_CUTOUT_MODE = global.HSM_VIEWPORT_VIGNETTE_CUTOUT_MODE;

#pragma parameter HSM_VIEWPORT_VIGNETTE_SCALE_MODE         "[ VIGNETT ] Scale Mode- Full | BG | Tube | Bzl | Decal | TopImg" 0 0 5 1
float HSM_VIEWPORT_VIGNETTE_SCALE_MODE = global.HSM_VIEWPORT_VIGNETTE_SCALE_MODE;

#pragma parameter HSM_VIEWPORT_VIGNETTE_SCALE                 "[ VIGNETTE ]  Scale" 100 0 1000 0.1
float HSM_VIEWPORT_VIGNETTE_SCALE = global.HSM_VIEWPORT_VIGNETTE_SCALE / 100;

#pragma parameter HSM_VIEWPORT_VIGNETTE_SCALE_X               "[ VIGNETTE ]  Scale X" 100 0 1000 0.1
float HSM_VIEWPORT_VIGNETTE_SCALE_X = global.HSM_VIEWPORT_VIGNETTE_SCALE_X / 100;

#pragma parameter HSM_VIEWPORT_VIGNETTE_POS_Y                 "[ VIGNETTE ]  Position Y"  0 -100 100 0.1
float HSM_VIEWPORT_VIGNETTE_POS_Y = global.HSM_VIEWPORT_VIGNETTE_POS_Y / 100;

//---------------------------------------------------------------------------------------------------
//    CRT Layer
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CRT_TITLE			"_____[ CRT SCREEN LAYER ]______________________________________" 0 0 0 0

#pragma parameter HSM_CRT_SCREEN_BLEND_MODE  "[ CRT SCREEN ]  Blend Mode - Off | Normal | Add (Backdrop)" 1 0 3 1
float HSM_CRT_SCREEN_BLEND_MODE = global.HSM_CRT_SCREEN_BLEND_MODE;


//---------------------------------------------------------------------------------------------------
//    BEZEL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BZL_IMG_TITLE			       "_____[ BEZEL IMAGE LAYER ]_____________________________________" 0 0 0 0

#pragma parameter HSM_BZL_IMG_OPACITY               "[ BEZEL IMG ]  Opacity" 0 0 100 1
float HSM_BZL_IMG_OPACITY = global.HSM_BZL_IMG_OPACITY / 100;

#pragma parameter HSM_BZL_IMG_HUE                   "[ BEZEL IMG ]  Hue Offset" 0 0 360 1
float HSM_BZL_IMG_HUE = global.HSM_BZL_IMG_HUE / 360;

#pragma parameter HSM_BZL_IMG_SATURATION            "[ BEZEL IMG ]  Saturation" 100 0 200 1
float HSM_BZL_IMG_SATURATION = global.HSM_BZL_IMG_SATURATION / 100;

#pragma parameter HSM_BZL_IMG_BRIGHTNESS            "[ BEZEL IMG ]  Brightness" 100 0 200 1
float HSM_BZL_IMG_BRIGHTNESS = global.HSM_BZL_IMG_BRIGHTNESS / 100;

#pragma parameter HSM_BZL_IMG_BLEND_MODE            "[ BEZEL IMG ]  Blend Mode -  Off | Normal | Add | Multiply"  1 0 3 1
float HSM_BZL_IMG_BLEND_MODE = global.HSM_BZL_IMG_BLEND_MODE;

#pragma parameter HSM_BZL_IMG_MASK_MODE             "Mask - ALL | Screen | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 4 0 8 1
float HSM_BZL_IMG_MASK_MODE = global.HSM_BZL_IMG_MASK_MODE;

#pragma parameter HSM_BZL_IMG_CUTOUT_MODE           "[ BEZEL IMG ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_BZL_IMG_CUTOUT_MODE = global.HSM_BZL_IMG_CUTOUT_MODE;

#pragma parameter HSM_BZL_IMG_TEXTURE_ASPECT_MODE      "[ BEZEL IMG] TexturAspct- Full | Expl.| 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_BZL_IMG_TEXTURE_ASPECT_MODE = global.HSM_BZL_IMG_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_BZL_IMG_EXPLICIT_TEXTURE_ASPECT  "[ BEZEL IMG ]  Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_BZL_IMG_EXPLICIT_TEXTURE_ASPECT = global.HSM_BZL_IMG_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_BZL_IMG_SCALE_MODE            "[ BEZEL IMG ]  Scale Mode - FullScreen | Tube | Bezel | BG"  1 0 3 1
float HSM_BZL_IMG_SCALE_MODE = global.HSM_BZL_IMG_SCALE_MODE;

#pragma parameter HSM_BZL_IMG_SCALE_KEEP_ASPECT      "[ BEZEL IMG ]  Keep Aspect"  1 0 1 1
float HSM_BZL_IMG_SCALE_KEEP_ASPECT = global.HSM_BZL_IMG_SCALE_KEEP_ASPECT;

#pragma parameter HSM_BZL_IMG_SCALE                 "[ BEZEL IMG ]  Scale" 100 0 1000 0.1
float HSM_BZL_IMG_SCALE = global.HSM_BZL_IMG_SCALE / 100;

#pragma parameter HSM_BZL_IMG_SCALE_X               "[ BEZEL IMG ]  Scale X" 100 0 1000 0.1
float HSM_BZL_IMG_SCALE_X = global.HSM_BZL_IMG_SCALE_X / 100;

#pragma parameter HSM_BZL_IMG_POS_Y                 "[ BEZEL IMG ]  Position Y"  0 -100 100 0.1
float HSM_BZL_IMG_POS_Y = global.HSM_BZL_IMG_POS_Y / 100;

#pragma parameter HSM_BZL_IMG_USE_CURVATURE          "[ BEZEL IMG ]  Use Curvature"  0 0 1 1
float HSM_BZL_IMG_USE_CURVATURE = global.HSM_BZL_IMG_USE_CURVATURE;


//---------------------------------------------------------------------------------------------------
//    CAB GLS IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CAB_GLASS_TITLE			"_____[ CABINET OR CABINET GLASS ]______________________________" 0 0 0 0

#pragma parameter HSM_CAB_GLASS_OPACITY           "[ CAB GLS ]  Opacity" 0 0 100 1
float HSM_CAB_GLASS_OPACITY = global.HSM_CAB_GLASS_OPACITY / 100;

#pragma parameter HSM_CAB_GLASS_BRIGHTNESS        "[ CAB GLS ]  Brightness" 100 0 400 1
float HSM_CAB_GLASS_BRIGHTNESS = global.HSM_CAB_GLASS_BRIGHTNESS / 100;

#pragma parameter HSM_CAB_GLASS_BLEND_MODE        "[ CAB GLS ]  Blend Mode - Off | Normal | Add | Multiply"  1 0 3 1
float HSM_CAB_GLASS_BLEND_MODE = global.HSM_CAB_GLASS_BLEND_MODE;

#pragma parameter HSM_CAB_GLASS_MASK_MODE         "Mask - ALL | Screen | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 0 0 8 1
float HSM_CAB_GLASS_MASK_MODE = global.HSM_CAB_GLASS_MASK_MODE;

#pragma parameter HSM_CAB_GLASS_CUTOUT_MODE       "[ CAB GLS ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_CAB_GLASS_CUTOUT_MODE = global.HSM_CAB_GLASS_CUTOUT_MODE;

#pragma parameter HSM_CAB_GLASS_TEXTURE_ASPECT_MODE  "[ CAB GLS] TexturAspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_CAB_GLASS_TEXTURE_ASPECT_MODE = global.HSM_CAB_GLASS_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_CAB_GLASS_EXPLICIT_TEXTURE_ASPECT  "[ CAB GLS ]  Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_CAB_GLASS_EXPLICIT_TEXTURE_ASPECT = global.HSM_CAB_GLASS_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_CAB_GLASS_SCALE_MODE        "[ CAB GLS ] Scale Mode- Full | BG | Tube | Bzl | Decal | TopImg" 0 0 5 1
float HSM_CAB_GLASS_SCALE_MODE = global.HSM_CAB_GLASS_SCALE_MODE;

#pragma parameter HSM_CAB_GLASS_SCALE_KEEP_ASPECT "[ CAB GLS ]  Keep Aspect"  1 0 1 1
float HSM_CAB_GLASS_SCALE_KEEP_ASPECT = global.HSM_CAB_GLASS_SCALE_KEEP_ASPECT;

#pragma parameter HSM_CAB_GLASS_SCALE             "[ CAB GLS ]  Scale" 100 10 500 1
float HSM_CAB_GLASS_SCALE = global.HSM_CAB_GLASS_SCALE / 100;

#pragma parameter HSM_CAB_GLASS_SCALE_X             "[ CAB GLS ]  Scale X" 100 0 500 1
float HSM_CAB_GLASS_SCALE_X = global.HSM_CAB_GLASS_SCALE_X / 100;

#pragma parameter HSM_CAB_GLASS_POS_Y             "[ CAB GLS ]  Position Y"  0 -100 100 0.1
float HSM_CAB_GLASS_POS_Y = global.HSM_CAB_GLASS_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    DECAL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_DECAL_TITLE			       "_____[ DECAL LAYER ]___________________________________________" 0 0 0 0

#pragma parameter HSM_DECAL_OPACITY               "[ DECAL ]  Opacity"  0 0 100 5
float HSM_DECAL_OPACITY = global.HSM_DECAL_OPACITY / 100;

#pragma parameter HSM_DECAL_BLEND_MODE            "[ DECAL ]  Blend Mode -  Off | Normal | Add | Multiply"  1 0 3 1
float HSM_DECAL_BLEND_MODE = global.HSM_DECAL_BLEND_MODE;

#pragma parameter HSM_DECAL_MASK_MODE             "Mask - ALL | Screen | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG"   0 0 8 1
float HSM_DECAL_MASK_MODE = global.HSM_DECAL_MASK_MODE;

#pragma parameter HSM_DECAL_CUTOUT_MODE            "[ DECAL ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_DECAL_CUTOUT_MODE = global.HSM_DECAL_CUTOUT_MODE;

#pragma parameter HSM_DECAL_TEXTURE_ASPECT_MODE  "[ DECAL ] TextureAspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_DECAL_TEXTURE_ASPECT_MODE = global.HSM_DECAL_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_DECAL_EXPLICIT_TEXTURE_ASPECT  "[ DECAL ]  Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_DECAL_EXPLICIT_TEXTURE_ASPECT = global.HSM_DECAL_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_DECAL_SCALE_MODE            "[ DECAL ]  Scale Mode - Full | Tube | Bezel | BG | Bzl Img"  2 0 4 1
float HSM_DECAL_SCALE_MODE = global.HSM_DECAL_SCALE_MODE;

#pragma parameter HSM_DECAL_SCALE_KEEP_ASPECT     "[ DECAL ]  Scale Keep Aspect"  1 0 1 1
float HSM_DECAL_SCALE_KEEP_ASPECT = global.HSM_DECAL_SCALE_KEEP_ASPECT;

#pragma parameter HSM_DECAL_SCALE                 "[ DECAL ]  Scale"  100 50 500 0.1
float HSM_DECAL_SCALE = global.HSM_DECAL_SCALE / 100;

#pragma parameter HSM_DECAL_SCALE_X                "[ DECAL ]  Scale X"  100 50 500 0.1
float HSM_DECAL_SCALE_X = global.HSM_DECAL_SCALE_X / 100;

#pragma parameter HSM_DECAL_POS_Y                 "[ DECAL ]  Position Y"  0 -100 100 0.1
float HSM_DECAL_POS_Y = global.HSM_DECAL_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    LED IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_LED_TITLE			       "_____[ LED LAYER ]_____________________________________________" 0 0 0 0

#pragma parameter HSM_LED_OPACITY                 "[ LED ]  Opacity"  0 0 100 1
float HSM_LED_OPACITY = global.HSM_LED_OPACITY / 100;

#pragma parameter HSM_LED_BLEND_MODE              "[ LED ]  Blend Mode - Off | Normal | Add | Multiply"  2 0 3 1
float HSM_LED_BLEND_MODE = global.HSM_LED_BLEND_MODE;

#pragma parameter HSM_LED_MASK_MODE               "Mask - ALL | Screen | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG"   8 0 8 1
float HSM_LED_MASK_MODE = global.HSM_LED_MASK_MODE;

#pragma parameter HSM_LED_CUTOUT_MODE             "[ LED ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_LED_CUTOUT_MODE = global.HSM_LED_CUTOUT_MODE;

#pragma parameter HSM_LED_TEXTURE_ASPECT_MODE  "[ LED ] Texture Aspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_LED_TEXTURE_ASPECT_MODE = global.HSM_LED_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_LED_EXPLICIT_TEXTURE_ASPECT  "[ LED ]  Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_LED_EXPLICIT_TEXTURE_ASPECT = global.HSM_LED_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_LED_SCALE_MODE              "[ LED ] Scale Mode - Full | Tube | Bezel | BG | Bzl Img | Decal"  0 0 5 1
float HSM_LED_SCALE_MODE = global.HSM_LED_SCALE_MODE;

#pragma parameter HSM_LED_SCALE_KEEP_ASPECT       "[ LED ]  Scale Keep Aspect"  1 0 1 1
float HSM_LED_SCALE_KEEP_ASPECT = global.HSM_LED_SCALE_KEEP_ASPECT;

#pragma parameter HSM_LED_SCALE                   "[ LED ]  Scale" 100 0 1000 0.1
float HSM_LED_SCALE = global.HSM_LED_SCALE / 100;

#pragma parameter HSM_LED_SCALE_X                 "[ LED ]  Scale X" 100 0 1000 0.1
float HSM_LED_SCALE_X = global.HSM_LED_SCALE_X / 100;

#pragma parameter HSM_LED_POS_Y                   "[ LED ]  Position Y"  0 -100 100 0.1
float HSM_LED_POS_Y = global.HSM_LED_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    TOP IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_TOP_TITLE			       "_____[ TOP EXTRA LAYER ]_______________________________________" 0 0 0 0

#pragma parameter HSM_TOP_OPACITY                 "[ TOP ]  Opacity"  0 0 100 0.1
float HSM_TOP_OPACITY = global.HSM_TOP_OPACITY / 100;

#pragma parameter HSM_TOP_BLEND_MODE              "[ TOP ]  Blend Mode - Off | Normal | Add | Multiply"  1 0 3 1
float HSM_TOP_BLEND_MODE = global.HSM_TOP_BLEND_MODE;

#pragma parameter HSM_TOP_MASK_MODE               "Mask - ALL | Screen | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG"   0 0 8 1
float HSM_TOP_MASK_MODE = global.HSM_TOP_MASK_MODE;

#pragma parameter HSM_TOP_CUTOUT_MODE             "[ TOP ]  Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_TOP_CUTOUT_MODE = global.HSM_TOP_CUTOUT_MODE;

#pragma parameter HSM_TOP_TEXTURE_ASPECT_MODE  "[ TOP ] Texture Aspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_TOP_TEXTURE_ASPECT_MODE = global.HSM_TOP_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_TOP_EXPLICIT_TEXTURE_ASPECT  "[ TOP ]  Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_TOP_EXPLICIT_TEXTURE_ASPECT = global.HSM_TOP_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_TOP_SCALE_MODE              "[ TOP ] Scale Mode - Full | Tube | Bezel | BG | Bzl Img | Decal"  0 0 5 1
float HSM_TOP_SCALE_MODE = global.HSM_TOP_SCALE_MODE;

#pragma parameter HSM_TOP_SCALE_KEEP_ASPECT       "[ TOP ]  Scale Keep Aspect"  1 0 1 1
float HSM_TOP_SCALE_KEEP_ASPECT = global.HSM_TOP_SCALE_KEEP_ASPECT;

#pragma parameter HSM_TOP_SCALE                   "[ TOP ]  Scale" 100 0 1000 0.1
float HSM_TOP_SCALE = global.HSM_TOP_SCALE / 100;

#pragma parameter HSM_TOP_SCALE_X                 "[ TOP ]  Scale X" 100 0 1000 0.1
float HSM_TOP_SCALE_X = global.HSM_TOP_SCALE_X / 100;

#pragma parameter HSM_TOP_POS_Y                   "[ TOP ]  Position Y"  0 -100 100 0.1
float HSM_TOP_POS_Y = global.HSM_TOP_POS_Y / 100;

#pragma parameter HSM_TOP_MIRROR_WRAP             "[ TOP ]  Mirror Wrap" 1 0 1 1
float HSM_TOP_MIRROR_WRAP = global.HSM_TOP_MIRROR_WRAP;

