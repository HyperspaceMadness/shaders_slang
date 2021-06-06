// Edited 2020-10-24-11:02

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//
//    Image Compositing Pass Parameters Start
//
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
//    NIGHT LIGHTING IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_NIGHT_LIGHTING_TITLE "[ NIGHT LIGHTING ]:" 0 0 0.01 0.01

#pragma parameter HSM_NIGHT_OPACITY             "          Opacity"  0 0 100 1
float HSM_NIGHT_OPACITY = global.HSM_NIGHT_OPACITY / 100;

#pragma parameter HSM_NIGHT_SCALE             "          Scale"  100 10 1000 1
float HSM_NIGHT_SCALE = global.HSM_NIGHT_SCALE / 100;

#pragma parameter HSM_NIGHT_MIRROR_HORZ         "          Mirror Horizontal"  0 0 1 1
float HSM_NIGHT_MIRROR_HORZ = global.HSM_NIGHT_MIRROR_HORZ;

#pragma parameter HSM_NIGHT_SATURATION          "          Saturation"  100 0 300 1
float HSM_NIGHT_SATURATION = global.HSM_NIGHT_SATURATION / 100;

#pragma parameter HSM_NIGHT_HUE                 "          Hue"  0 -180 180 1
float HSM_NIGHT_HUE = global.HSM_NIGHT_HUE / 360;

#pragma parameter HSM_NIGHT_VALUE               "          Value"  100 0 400 1
float HSM_NIGHT_VALUE = global.HSM_NIGHT_VALUE / 100;

#pragma parameter HSM_NIGHT_DITHERING_SAMPLES   "          Dithering Noise Samples (Reduces Banding)" 0 0 10 1
float HSM_NIGHT_DITHERING_SAMPLES = global.HSM_NIGHT_DITHERING_SAMPLES;


//---------------------------------------------------------------------------------------------------
//    IMAGES GAMMA
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_STATIC_GAMMA_TITLE        "[ IMAGE LAYER GAMMA ]:" 0 0 0.01 0.01

#pragma parameter HSM_STATIC_LAYERS_GAMMA		"          Image Layers Gamma Adjust" 1 0.01 5 0.01
float HSM_STATIC_LAYERS_GAMMA = global.HSM_STATIC_LAYERS_GAMMA;


//---------------------------------------------------------------------------------------------------
//    IMAGE LAYERING START
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_ADVANCED_LAYERING_TITLE     "[ ADVANCED IMAGE LAYERS ]:" 0 0 0.01 0.01


#pragma parameter HSM_LAYER_ORDER_TITLE			  "[ LAYER ORDER ]:" 0 0 0.01 0.01

#pragma parameter HSM_BG_LAYER_ORDER              "          Background Image"  0 0 12 1
float HSM_BG_LAYER_ORDER = global.HSM_BG_LAYER_ORDER;

#pragma parameter HSM_VIEWPORT_VIGNETTE_LAYER_ORDER "          Viewport Vignette"  1 0 12 1
float HSM_VIEWPORT_VIGNETTE_LAYER_ORDER = global.HSM_VIEWPORT_VIGNETTE_LAYER_ORDER;

#pragma parameter HSM_CRT_LAYER_ORDER             "          CRT Screen"  3 0 12 1
float HSM_CRT_LAYER_ORDER = global.HSM_CRT_LAYER_ORDER;

#pragma parameter HSM_BZL_IMG_LAYER_ORDER         "          Bezel Image"  4 0 12 1
float HSM_BZL_IMG_LAYER_ORDER = global.HSM_BZL_IMG_LAYER_ORDER;

#pragma parameter HSM_BZL_LAYER_ORDER             "          Bezel (Generated)"  5 0 12 1
float HSM_BZL_LAYER_ORDER = global.HSM_BZL_LAYER_ORDER;

#pragma parameter HSM_FRM_LAYER_ORDER             "          Frame (Generated)"  6 0 12 1
float HSM_FRM_LAYER_ORDER = global.HSM_FRM_LAYER_ORDER;

#pragma parameter HSM_CAB_GLASS_LAYER_ORDER       "          Cabinet Glass Image"  7 0 12 1
float HSM_CAB_GLASS_LAYER_ORDER = global.HSM_CAB_GLASS_LAYER_ORDER;

#pragma parameter HSM_DECAL_LAYER_ORDER           "          Decal Image"  8 0 12 1
float HSM_DECAL_LAYER_ORDER = global.HSM_DECAL_LAYER_ORDER;

#pragma parameter HSM_REFLECT_LAYER_ORDER         "          Reflection (Generated)"  9 0 12 1
float HSM_REFLECT_LAYER_ORDER = global.HSM_REFLECT_LAYER_ORDER;

#pragma parameter HSM_LED_LAYER_ORDER             "          LED Image"  10 0 12 1
float HSM_LED_LAYER_ORDER = global.HSM_LED_LAYER_ORDER;

#pragma parameter HSM_TOP_LAYER_ORDER             "          Top Image"  12 0 12 1
float HSM_TOP_LAYER_ORDER = global.HSM_TOP_LAYER_ORDER;


//---------------------------------------------------------------------------------------------------
//    CutOut in Image Layers
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CUTOUT_TITLE			    "[ CUTOUT ]:" 0 0 0.01 0.01

#pragma parameter HSM_CUTOUT_SCALE_MODE         "          Scale Mode - Full | Tube | Bzl | BG | Bzl Img | Decal"  0 0 5 1
float HSM_CUTOUT_SCALE_MODE = global.HSM_CUTOUT_SCALE_MODE;

#pragma parameter HSM_CUTOUT_SCALE 				"          Scale" 100 -100 200 0.1
float HSM_CUTOUT_SCALE = global.HSM_CUTOUT_SCALE / 100;

#pragma parameter HSM_CUTOUT_SCALE_X 		    "          Scale X" 100 -100 200 0.1
float HSM_CUTOUT_SCALE_X = global.HSM_CUTOUT_SCALE_X / 100;

#pragma parameter HSM_CUTOUT_POS_X 		        "          Position XY" 0 -100 200 0.05
float HSM_CUTOUT_POS_X = global.HSM_CUTOUT_POS_X / -100;

#pragma parameter HSM_CUTOUT_POS_Y 		        "          Position Y" 0 -100 200 0.05
float HSM_CUTOUT_POS_Y = global.HSM_CUTOUT_POS_Y / 100;

#pragma parameter HSM_CUTOUT_CORNER_RADIUS 		"          Corner Radius - Def 0" 0 0 70 1
float HSM_CUTOUT_CORNER_RADIUS = global.HSM_CUTOUT_CORNER_RADIUS;


//---------------------------------------------------------------------------------------------------
//    MASK DEBUG
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_MASK_DEBUG_TITLE			"[ MASK DEBUG ]:" 0 0 0.01 0.01

#pragma parameter HSM_LAYERING_DEBUG_MASK_MODE    "    Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" -1 -2 8 1
float HSM_LAYERING_DEBUG_MASK_MODE = global.HSM_LAYERING_DEBUG_MASK_MODE;


//---------------------------------------------------------------------------------------------------
//    BG IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BACKGROUND_TITLE			"[ BACKGROUND LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_BG_OPACITY                  "          Opacity" 100 0 100 1
float HSM_BG_OPACITY = global.HSM_BG_OPACITY / 100;

#pragma parameter HSM_BG_BLEND_MODE               "          Blend Mode - OFF | NORMAL | ADD | MULTIPLY"  1 -1 2 1
float HSM_BG_BLEND_MODE = global.HSM_BG_BLEND_MODE;

#pragma parameter HSM_BG_SOURCE_MATTE_TYPE        "          Source Matte Color - Black | White | None"  0 0 2 1
float HSM_BG_SOURCE_MATTE_TYPE = global.HSM_BG_SOURCE_MATTE_TYPE;

#pragma parameter HSM_BG_MASK_MODE                "    Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 0 0 8 1
float HSM_BG_MASK_MODE = global.HSM_BG_MASK_MODE;

#pragma parameter HSM_BG_CUTOUT_MODE              "          Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_BG_CUTOUT_MODE = global.HSM_BG_CUTOUT_MODE;

#pragma parameter HSM_BG_DUALSCREEN_VIS_MODE      "          Dual Screen Visibility - BOTH | SCREEN 1 | Screen 2" 0 0 2 1
float HSM_BG_DUALSCREEN_VIS_MODE = global.HSM_BG_DUALSCREEN_VIS_MODE;

#pragma parameter HSM_BG_BRIGHTNESS               "          Brightness" 100 0 600 0.5
float HSM_BG_BRIGHTNESS = global.HSM_BG_BRIGHTNESS / 100;

#pragma parameter HSM_BG_APPLY_ADJUSTMENT         "          Apply NightLight & Static Gamma (0 for Backdrop)"  1 0 1 1
float HSM_BG_APPLY_ADJUSTMENT = global.HSM_BG_APPLY_ADJUSTMENT;

#pragma parameter HSM_BG_TEXTURE_ASPECT_MODE      "         Texture Aspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_BG_TEXTURE_ASPECT_MODE = global.HSM_BG_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_BG_EXPLICIT_TEXTURE_ASPECT  "          Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_BG_EXPLICIT_TEXTURE_ASPECT = global.HSM_BG_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_BG_SCALE_MODE               "          Scale Mode - FullScreen | Tube | Bezel" 0 0 2 1
float HSM_BG_SCALE_MODE = global.HSM_BG_SCALE_MODE;

#pragma parameter HSM_BG_SCALE_KEEP_ASPECT        "          Keep Aspect"  1 0 1 1
float HSM_BG_SCALE_KEEP_ASPECT = global.HSM_BG_SCALE_KEEP_ASPECT;

#pragma parameter HSM_BG_SCALE                    "          Scale" 100 0 1000 0.1
float HSM_BG_SCALE = global.HSM_BG_SCALE / 100;

#pragma parameter HSM_BG_SCALE_X                  "          Scale X" 100 0 1000 0.1
float HSM_BG_SCALE_X = global.HSM_BG_SCALE_X / 100;

#pragma parameter HSM_BG_POS_X                    "          Position X"  0 -1000 1000 0.05
float HSM_BG_POS_X = global.HSM_BG_POS_X / -100;

#pragma parameter HSM_BG_POS_Y                    "          Position Y"  0 -1000 1000 0.05
float HSM_BG_POS_Y = global.HSM_BG_POS_Y / 100;

#pragma parameter HSM_BG_MIRROR_WRAP              "          Mirror Wrap" 1 0 1 1
float HSM_BG_MIRROR_WRAP = global.HSM_BG_MIRROR_WRAP;

// TODO Add DUAL Screen where to show Image

//---------------------------------------------------------------------------------------------------
//    VIEWPORT VIGNETTE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_VIEWPORT_VIGNETTE_TITLE		"[ VIEWPORT VIGNETTE LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_VIEWPORT_VIGNETTE_OPACITY     "          Opacity" 0 0 100 2
float HSM_VIEWPORT_VIGNETTE_OPACITY = global.HSM_VIEWPORT_VIGNETTE_OPACITY / 100;

#pragma parameter HSM_VIEWPORT_VIGNETTE_MASK_MODE   "Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 5 0 8 1
float HSM_VIEWPORT_VIGNETTE_MASK_MODE = global.HSM_VIEWPORT_VIGNETTE_MASK_MODE;

#pragma parameter HSM_VIEWPORT_VIGNETTE_CUTOUT_MODE  "          Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_VIEWPORT_VIGNETTE_CUTOUT_MODE = global.HSM_VIEWPORT_VIGNETTE_CUTOUT_MODE;

#pragma parameter HSM_VIEWPORT_VIGNETTE_SCALE_MODE   "          Scale Mode- Full | BG | Tube | Bzl | Decal | TopImg" 0 0 5 1
float HSM_VIEWPORT_VIGNETTE_SCALE_MODE = global.HSM_VIEWPORT_VIGNETTE_SCALE_MODE;

#pragma parameter HSM_VIEWPORT_VIGNETTE_SCALE        "          Scale" 100 0 1000 0.1
float HSM_VIEWPORT_VIGNETTE_SCALE = global.HSM_VIEWPORT_VIGNETTE_SCALE / 100;

#pragma parameter HSM_VIEWPORT_VIGNETTE_SCALE_X      "          Scale X" 100 0 1000 0.1
float HSM_VIEWPORT_VIGNETTE_SCALE_X = global.HSM_VIEWPORT_VIGNETTE_SCALE_X / 100;

#pragma parameter HSM_VIEWPORT_VIGNETTE_POS_X        "          Position X"  0 -1000 1000 0.05
float HSM_VIEWPORT_VIGNETTE_POS_X = global.HSM_VIEWPORT_VIGNETTE_POS_X / -100;

#pragma parameter HSM_VIEWPORT_VIGNETTE_POS_Y        "          Position Y"  0 -1000 1000 0.05
float HSM_VIEWPORT_VIGNETTE_POS_Y = global.HSM_VIEWPORT_VIGNETTE_POS_Y / 100;

//---------------------------------------------------------------------------------------------------
//    CRT Layer
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CRT_TITLE			             "[ CRT SCREEN LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_CRT_SCREEN_BLEND_MODE          "          Blend Mode - OFF | NORMAL | ADD (Backdrop) | MULT" 1 0 3 1
float HSM_CRT_SCREEN_BLEND_MODE = global.HSM_CRT_SCREEN_BLEND_MODE;


//---------------------------------------------------------------------------------------------------
//    BEZEL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BZL_IMG_TITLE			            "[ BEZEL IMAGE LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_BZL_IMG_OPACITY                   "          Opacity" 100 0 100 1
float HSM_BZL_IMG_OPACITY = global.HSM_BZL_IMG_OPACITY / 100;

#pragma parameter HSM_BZL_IMG_HUE                       "          Hue Offset" 0 0 360 1
float HSM_BZL_IMG_HUE = global.HSM_BZL_IMG_HUE / 360;

#pragma parameter HSM_BZL_IMG_SATURATION                "          Saturation" 100 0 200 1
float HSM_BZL_IMG_SATURATION = global.HSM_BZL_IMG_SATURATION / 100;

#pragma parameter HSM_BZL_IMG_BRIGHTNESS                "          Brightness" 100 0 200 1
float HSM_BZL_IMG_BRIGHTNESS = global.HSM_BZL_IMG_BRIGHTNESS / 100;

#pragma parameter HSM_BZL_IMG_BLEND_MODE                "          Blend Mode -  OFF | NORMAL | ADD | MULTIPLY"  1 0 3 1
float HSM_BZL_IMG_BLEND_MODE = global.HSM_BZL_IMG_BLEND_MODE;

#pragma parameter HSM_BZL_SOURCE_MATTE_TYPE             "          Source Matte Color - Black | White | None"  0 0 2 1
float HSM_BZL_SOURCE_MATTE_TYPE = global.HSM_BZL_SOURCE_MATTE_TYPE;

#pragma parameter HSM_BZL_IMG_MASK_MODE                 "    Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 4 0 8 1
float HSM_BZL_IMG_MASK_MODE = global.HSM_BZL_IMG_MASK_MODE;

#pragma parameter HSM_BZL_IMG_CUTOUT_MODE               "          Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_BZL_IMG_CUTOUT_MODE = global.HSM_BZL_IMG_CUTOUT_MODE;

#pragma parameter HSM_BZL_DUALSCREEN_VIS_MODE      "          Dual Screen Visibility - BOTH | SCREEN 1 | Screen 2" 0 0 2 1
float HSM_BZL_DUALSCREEN_VIS_MODE = global.HSM_BZL_DUALSCREEN_VIS_MODE;

#pragma parameter HSM_BZL_IMG_TEXTURE_ASPECT_MODE       "         Texture Aspect - Full | Expl.| 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_BZL_IMG_TEXTURE_ASPECT_MODE = global.HSM_BZL_IMG_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_BZL_IMG_EXPLICIT_TEXTURE_ASPECT   "          Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_BZL_IMG_EXPLICIT_TEXTURE_ASPECT = global.HSM_BZL_IMG_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_BZL_IMG_SCALE_MODE                "          Scale Mode - FullScreen | Tube | Bezel | BG"  1 0 3 1
float HSM_BZL_IMG_SCALE_MODE = global.HSM_BZL_IMG_SCALE_MODE;

#pragma parameter HSM_BZL_IMG_SCALE_KEEP_ASPECT         "          Keep Aspect"  1 0 1 1
float HSM_BZL_IMG_SCALE_KEEP_ASPECT = global.HSM_BZL_IMG_SCALE_KEEP_ASPECT;

#pragma parameter HSM_BZL_IMG_SCALE                     "          Scale" 100 0 1000 0.1
float HSM_BZL_IMG_SCALE = global.HSM_BZL_IMG_SCALE / 100;

#pragma parameter HSM_BZL_IMG_SCALE_X                   "          Scale X" 100 0 1000 0.1
float HSM_BZL_IMG_SCALE_X = global.HSM_BZL_IMG_SCALE_X / 100;

#pragma parameter HSM_BZL_IMG_POS_X                     "          Position X"  0 -1000 1000 0.05
float HSM_BZL_IMG_POS_X = global.HSM_BZL_IMG_POS_X / -100;

#pragma parameter HSM_BZL_IMG_POS_Y                     "          Position Y"  0 -1000 1000 0.05
float HSM_BZL_IMG_POS_Y = global.HSM_BZL_IMG_POS_Y / 100;

#pragma parameter HSM_BZL_IMG_USE_CURVATURE             "          Use Curvature"  0 0 1 1
float HSM_BZL_IMG_USE_CURVATURE = global.HSM_BZL_IMG_USE_CURVATURE;


//---------------------------------------------------------------------------------------------------
//    CAB GLS IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_CAB_GLASS_TITLE			            "[ CABINET OR CABINET GLASS LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_CAB_GLASS_OPACITY                     "          Opacity" 100 0 100 1
float HSM_CAB_GLASS_OPACITY = global.HSM_CAB_GLASS_OPACITY / 100;

#pragma parameter HSM_CAB_GLASS_BRIGHTNESS                  "          Brightness" 100 0 400 1
float HSM_CAB_GLASS_BRIGHTNESS = global.HSM_CAB_GLASS_BRIGHTNESS / 100;

#pragma parameter HSM_CAB_GLASS_BLEND_MODE                  "          Blend Mode - OFF | NORMAL | ADD | MULTIPLY"  1 0 3 1
float HSM_CAB_GLASS_BLEND_MODE = global.HSM_CAB_GLASS_BLEND_MODE;

#pragma parameter HSM_CAB_GLASS_SOURCE_MATTE_TYPE           "          Source Matte Color - Black | White | None"  0 0 2 1
float HSM_CAB_GLASS_SOURCE_MATTE_TYPE = global.HSM_CAB_GLASS_SOURCE_MATTE_TYPE;

#pragma parameter HSM_CAB_GLASS_MASK_MODE                   "    Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG" 0 0 8 1
float HSM_CAB_GLASS_MASK_MODE = global.HSM_CAB_GLASS_MASK_MODE;

#pragma parameter HSM_CAB_GLASS_CUTOUT_MODE                 "          Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_CAB_GLASS_CUTOUT_MODE = global.HSM_CAB_GLASS_CUTOUT_MODE;

#pragma parameter HSM_CAB_GLASS_DUALSCREEN_VIS_MODE      "          Dual Screen Visibility - BOTH | SCREEN 1 | Screen 2" 0 0 2 1
float HSM_CAB_GLASS_DUALSCREEN_VIS_MODE = global.HSM_CAB_GLASS_DUALSCREEN_VIS_MODE;

#pragma parameter HSM_CAB_GLASS_TEXTURE_ASPECT_MODE         "          TexturAspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_CAB_GLASS_TEXTURE_ASPECT_MODE = global.HSM_CAB_GLASS_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_CAB_GLASS_EXPLICIT_TEXTURE_ASPECT     "          Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_CAB_GLASS_EXPLICIT_TEXTURE_ASPECT = global.HSM_CAB_GLASS_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_CAB_GLASS_SCALE_MODE                  "          Scale Mode- Full | BG | Tube | Bzl | Decal | TopImg" 0 0 5 1
float HSM_CAB_GLASS_SCALE_MODE = global.HSM_CAB_GLASS_SCALE_MODE;

#pragma parameter HSM_CAB_GLASS_SCALE_KEEP_ASPECT           "          Keep Aspect"  1 0 1 1
float HSM_CAB_GLASS_SCALE_KEEP_ASPECT = global.HSM_CAB_GLASS_SCALE_KEEP_ASPECT;

#pragma parameter HSM_CAB_GLASS_SCALE                       "          Scale" 100 10 500 0.1
float HSM_CAB_GLASS_SCALE = global.HSM_CAB_GLASS_SCALE / 100;

#pragma parameter HSM_CAB_GLASS_SCALE_X                     "          Scale X" 100 0 500 0.1
float HSM_CAB_GLASS_SCALE_X = global.HSM_CAB_GLASS_SCALE_X / 100;

#pragma parameter HSM_CAB_GLASS_POS_X                       "          Position X"  0 -1000 1000 0.05
float HSM_CAB_GLASS_POS_X = global.HSM_CAB_GLASS_POS_X / -100;

#pragma parameter HSM_CAB_GLASS_POS_Y                       "          Position Y"  0 -1000 1000 0.05
float HSM_CAB_GLASS_POS_Y = global.HSM_CAB_GLASS_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    DECAL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_DECAL_TITLE			            "[ DECAL LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_DECAL_OPACITY                     "          Opacity"  100 0 100 5
float HSM_DECAL_OPACITY = global.HSM_DECAL_OPACITY / 100;

#pragma parameter HSM_DECAL_BLEND_MODE                  "          Blend Mode -  OFF | NORMAL | ADD | MULTIPLY"  1 0 3 1
float HSM_DECAL_BLEND_MODE = global.HSM_DECAL_BLEND_MODE;

#pragma parameter HSM_DECAL_SOURCE_MATTE_TYPE           "          Source Matte Color - Black | White | None"  0 0 2 1
float HSM_DECAL_SOURCE_MATTE_TYPE = global.HSM_DECAL_SOURCE_MATTE_TYPE;

#pragma parameter HSM_DECAL_MASK_MODE                   "    Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG"   0 0 8 1
float HSM_DECAL_MASK_MODE = global.HSM_DECAL_MASK_MODE;

#pragma parameter HSM_DECAL_CUTOUT_MODE                 "          Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_DECAL_CUTOUT_MODE = global.HSM_DECAL_CUTOUT_MODE;

#pragma parameter HSM_DECAL_DUALSCREEN_VIS_MODE      "          Dual Screen Visibility - BOTH | SCREEN 1 | Screen 2" 0 0 2 1
float HSM_DECAL_DUALSCREEN_VIS_MODE = global.HSM_DECAL_DUALSCREEN_VIS_MODE;

#pragma parameter HSM_DECAL_TEXTURE_ASPECT_MODE         "         TextureAspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_DECAL_TEXTURE_ASPECT_MODE = global.HSM_DECAL_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_DECAL_EXPLICIT_TEXTURE_ASPECT     "          Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_DECAL_EXPLICIT_TEXTURE_ASPECT = global.HSM_DECAL_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_DECAL_SCALE_MODE                  "          Scale Mode - Full | Tube | Bezel | BG | Bzl Img"  2 0 4 1
float HSM_DECAL_SCALE_MODE = global.HSM_DECAL_SCALE_MODE;

#pragma parameter HSM_DECAL_SCALE_KEEP_ASPECT           "          Scale Keep Aspect"  1 0 1 1
float HSM_DECAL_SCALE_KEEP_ASPECT = global.HSM_DECAL_SCALE_KEEP_ASPECT;

#pragma parameter HSM_DECAL_SCALE                       "          Scale"  100 50 500 0.1
float HSM_DECAL_SCALE = global.HSM_DECAL_SCALE / 100;

#pragma parameter HSM_DECAL_SCALE_X                     "          Scale X"  100 50 500 0.1
float HSM_DECAL_SCALE_X = global.HSM_DECAL_SCALE_X / 100;

#pragma parameter HSM_DECAL_POS_X                       "          Position X"  0 -1000 1000 0.05
float HSM_DECAL_POS_X = global.HSM_DECAL_POS_X / -100;

#pragma parameter HSM_DECAL_POS_Y                       "          Position Y"  0 -1000 1000 0.05
float HSM_DECAL_POS_Y = global.HSM_DECAL_POS_Y / 100;

//---------------------------------------------------------------------------------------------------
//    LED IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_LED_TITLE			                "[ LED LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_LED_OPACITY                       "          Opacity"  100 0 100 1
float HSM_LED_OPACITY = global.HSM_LED_OPACITY / 100;

#pragma parameter HSM_LED_BLEND_MODE                    "          Blend Mode - OFF | NORMAL | ADD | MULTIPLY"  2 0 3 1
float HSM_LED_BLEND_MODE = global.HSM_LED_BLEND_MODE;

#pragma parameter HSM_LED_SOURCE_MATTE_TYPE             "          Source Matte Color - Black | White | None"  0 0 2 1
float HSM_LED_SOURCE_MATTE_TYPE = global.HSM_LED_SOURCE_MATTE_TYPE;

#pragma parameter HSM_LED_MASK_MODE                     "    Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG"   8 0 8 1
float HSM_LED_MASK_MODE = global.HSM_LED_MASK_MODE;

#pragma parameter HSM_LED_CUTOUT_MODE                   "          Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_LED_CUTOUT_MODE = global.HSM_LED_CUTOUT_MODE;

#pragma parameter HSM_LED_DUALSCREEN_VIS_MODE      "          Dual Screen Visibility - BOTH | SCREEN 1 | Screen 2" 0 0 2 1
float HSM_LED_DUALSCREEN_VIS_MODE = global.HSM_LED_DUALSCREEN_VIS_MODE;

#pragma parameter HSM_LED_TEXTURE_ASPECT_MODE           "         Texture Aspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_LED_TEXTURE_ASPECT_MODE = global.HSM_LED_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_LED_EXPLICIT_TEXTURE_ASPECT       "          Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_LED_EXPLICIT_TEXTURE_ASPECT = global.HSM_LED_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_LED_SCALE_MODE                    "        Scale Mode - Full | Tube | Bezel | BG | Bzl Img | Decal"  0 0 5 1
float HSM_LED_SCALE_MODE = global.HSM_LED_SCALE_MODE;

#pragma parameter HSM_LED_SCALE_KEEP_ASPECT             "          Scale Keep Aspect"  1 0 1 1
float HSM_LED_SCALE_KEEP_ASPECT = global.HSM_LED_SCALE_KEEP_ASPECT;

#pragma parameter HSM_LED_SCALE                         "          Scale" 100 0 1000 0.1
float HSM_LED_SCALE = global.HSM_LED_SCALE / 100;

#pragma parameter HSM_LED_SCALE_X                       "          Scale X" 100 0 1000 0.1
float HSM_LED_SCALE_X = global.HSM_LED_SCALE_X / 100;

#pragma parameter HSM_LED_POS_X                         "          Position X"  0 -1000 1000 0.05
float HSM_LED_POS_X = global.HSM_LED_POS_X / -100;

#pragma parameter HSM_LED_POS_Y                         "          Position Y"  0 -1000 1000 0.05
float HSM_LED_POS_Y = global.HSM_LED_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    TOP IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_TOP_TITLE			                "[ TOP EXTRA LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_TOP_OPACITY                       "          Opacity"  100 0 100 0.1
float HSM_TOP_OPACITY = global.HSM_TOP_OPACITY / 100;

#pragma parameter HSM_TOP_BLEND_MODE                    "          Blend Mode - OFF | NORMAL | ADD | MULTIPLY"  1 0 3 1
float HSM_TOP_BLEND_MODE = global.HSM_TOP_BLEND_MODE;

#pragma parameter HSM_TOP_SOURCE_MATTE_TYPE             "          Source Matte Color - Black | White | None"  0 0 2 1
float HSM_TOP_SOURCE_MATTE_TYPE = global.HSM_TOP_SOURCE_MATTE_TYPE;

#pragma parameter HSM_TOP_MASK_MODE                     "    Mask - ALL | Scrn | Tube | Bz- | Bz | Bz+ | Frm | Frm+ | BG"   0 0 8 1
float HSM_TOP_MASK_MODE = global.HSM_TOP_MASK_MODE;

#pragma parameter HSM_TOP_CUTOUT_MODE                   "          Cutout Mask - OFF | ON | Invert" 0 0 2 1
float HSM_TOP_CUTOUT_MODE = global.HSM_TOP_CUTOUT_MODE;

#pragma parameter HSM_TOP_DUALSCREEN_VIS_MODE      "          Dual Screen Visibility - BOTH | SCREEN 1 | Screen 2" 0 0 2 1
float HSM_TOP_DUALSCREEN_VIS_MODE = global.HSM_TOP_DUALSCREEN_VIS_MODE;

#pragma parameter HSM_TOP_TEXTURE_ASPECT_MODE           "         Texture Aspect- Full | Expl. | 4:3 | 3:4 | 16:9 | 9:16" 0 0 5 1
float HSM_TOP_TEXTURE_ASPECT_MODE = global.HSM_TOP_TEXTURE_ASPECT_MODE;

#pragma parameter HSM_TOP_EXPLICIT_TEXTURE_ASPECT       "          Explicit Texture Aspect" 1.33333 0.01 3 0.01
float HSM_TOP_EXPLICIT_TEXTURE_ASPECT = global.HSM_TOP_EXPLICIT_TEXTURE_ASPECT;

#pragma parameter HSM_TOP_SCALE_MODE                    "        Scale Mode - Full | Tube | Bezel | BG | Bzl Img | Decal"  0 0 5 1
float HSM_TOP_SCALE_MODE = global.HSM_TOP_SCALE_MODE;

#pragma parameter HSM_TOP_SCALE_KEEP_ASPECT             "          Scale Keep Aspect"  1 0 1 1
float HSM_TOP_SCALE_KEEP_ASPECT = global.HSM_TOP_SCALE_KEEP_ASPECT;

#pragma parameter HSM_TOP_SCALE                         "          Scale" 100 0 1000 0.1
float HSM_TOP_SCALE = global.HSM_TOP_SCALE / 100;

#pragma parameter HSM_TOP_SCALE_X                       "          Scale X" 100 0 1000 0.1
float HSM_TOP_SCALE_X = global.HSM_TOP_SCALE_X / 100;

#pragma parameter HSM_TOP_POS_X                         "          Position X"  0 -1000 1000 0.05
float HSM_TOP_POS_X = global.HSM_TOP_POS_X / -100;

#pragma parameter HSM_TOP_POS_Y                         "          Position Y"  0 -1000 1000 0.05
float HSM_TOP_POS_Y = global.HSM_TOP_POS_Y / 100;

#pragma parameter HSM_TOP_MIRROR_WRAP                   "          Mirror Wrap" 1 0 1 1
float HSM_TOP_MIRROR_WRAP = global.HSM_TOP_MIRROR_WRAP;

