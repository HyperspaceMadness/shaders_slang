//---------------------------------------------------------------------------------------------------
//    NIGHT LIGHTING IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_NIGHT_LIGHTING_TITLE          "[ NIGHT LIGHTING ]:" 0 0 0.01 0.01

#pragma parameter HSM_NIGHT_OPACITY                 "      Opacity"  0 0 100 1
float HSM_NIGHT_OPACITY = global.HSM_NIGHT_OPACITY / 100;

#pragma parameter HSM_NIGHT_SCALE             "      Scale"  100 10 1000 1
float HSM_NIGHT_SCALE = global.HSM_NIGHT_SCALE / 100;

#pragma parameter HSM_NIGHT_MIRROR_HORZ         "      Mirror Horizontal"  0 0 1 1
float HSM_NIGHT_MIRROR_HORZ = global.HSM_NIGHT_MIRROR_HORZ;


//---------------------------------------------------------------------------------------------------
//    IMAGES GAMMA
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_STATIC_GAMMA_TITLE        "[ IMAGE LAYER GAMMA ]:" 0 0 0.01 0.01

#pragma parameter HSM_STATIC_LAYERS_GAMMA		    "      Image Layers Gamma Adjust" 1 0.01 5 0.01
float HSM_STATIC_LAYERS_GAMMA = global.HSM_STATIC_LAYERS_GAMMA;


//---------------------------------------------------------------------------------------------------
//    STANDARD BACKGROUND IMAGE LAYER
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_STANDARD_IMG_TITLE	        "[ STANDARD IMAGE LAYERS ]:" 0 0 0.01 0.01

#pragma parameter HSM_STANDARD_IMG_ASPECT_RATIO_MODE 	    "      Aspect Ratio - FULL | EXPLICIT | 16:9 | 9:16"  2 0 3 1
float HSM_STANDARD_IMG_ASPECT_RATIO_MODE = global.HSM_STANDARD_IMG_ASPECT_RATIO_MODE;

#pragma parameter HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT    "      Explicit Aspect Ratio"  1.777 0.01 4 0.01
float HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT = global.HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT;


//---------------------------------------------------------------------------------------------------
//    BG IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BACKGROUND_TITLE			    "[ BACKGROUND LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_BG_OPACITY 	                "      Opacity" 100 0 100 0.1
float HSM_BG_OPACITY = global.HSM_BG_OPACITY / 100;

#pragma parameter HSM_BG_BLEND_MODE 		        "      Blend Mode - OFF | NORM | ADD | MULT"  2 0 3 1
float HSM_BG_BLEND_MODE = global.HSM_BG_BLEND_MODE;

#pragma parameter HSM_BG_SOURCE_MATTE_TYPE          "      Source Matte Color - Black | White | None"  0 0 2 1
float HSM_BG_SOURCE_MATTE_TYPE = global.HSM_BG_SOURCE_MATTE_TYPE;

#pragma parameter HSM_VIEWPORT_VIGNETTE_OPACITY     "      Vignette Opacity" 0 0 100 2
float HSM_VIEWPORT_VIGNETTE_OPACITY = global.HSM_VIEWPORT_VIGNETTE_OPACITY / 100;

#pragma parameter HSM_STANDARD_BG_SHOW_OVER_SCREEN 	"      Show over Screen" 0 0 1 1
float HSM_STANDARD_BG_SHOW_OVER_SCREEN = global.HSM_STANDARD_BG_SHOW_OVER_SCREEN;


//---------------------------------------------------------------------------------------------------
//    LED IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_LED_TITLE			            "[ LED LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_LED_OPACITY 	                "      Opacity" 100 0 100 0.1
float HSM_LED_OPACITY = global.HSM_LED_OPACITY / 100;

#pragma parameter HSM_LED_BLEND_MODE 		        "      Blend Mode - OFF | NORM | ADD | MULT"  2 0 3 1
float HSM_LED_BLEND_MODE = global.HSM_LED_BLEND_MODE;

#pragma parameter HSM_LED_SOURCE_MATTE_TYPE         "      Source Matte Color - Black | White | None"  0 0 2 1
float HSM_LED_SOURCE_MATTE_TYPE = global.HSM_LED_SOURCE_MATTE_TYPE;

#pragma parameter HSM_STANDARD_LED_SHOW_OVER_SCREEN "      Show over Screen" 0 0 1 1
float HSM_STANDARD_LED_SHOW_OVER_SCREEN = global.HSM_STANDARD_LED_SHOW_OVER_SCREEN;

//---------------------------------------------------------------------------------------------------
//    DECAL IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_DECAL_TITLE			        "[ DECAL LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_DECAL_OPACITY 	            "      Opacity" 100 0 100 0.1
float HSM_DECAL_OPACITY = global.HSM_DECAL_OPACITY / 100;

#pragma parameter HSM_DECAL_BLEND_MODE 		        "      Blend Mode - OFF | NORM | ADD | MULT"  1 0 3 1
float HSM_DECAL_BLEND_MODE = global.HSM_DECAL_BLEND_MODE;

#pragma parameter HSM_DECAL_SOURCE_MATTE_TYPE       "      Source Matte Color - Black | White | None"  0 0 2 1
float HSM_DECAL_SOURCE_MATTE_TYPE = global.HSM_DECAL_SOURCE_MATTE_TYPE;

#pragma parameter HSM_STANDARD_DECAL_SHOW_UNDER_FRAME "      Decal Show Under Frame"  0 0 1 1
float HSM_STANDARD_DECAL_SHOW_UNDER_FRAME = global.HSM_STANDARD_DECAL_SHOW_UNDER_FRAME;

#pragma parameter HSM_STANDARD_DECAL_SCALE_WITH_FRAME "      Scale With Frame - OFF | ON"  0 0 1 1
float HSM_STANDARD_DECAL_SCALE_WITH_FRAME = global.HSM_STANDARD_DECAL_SCALE_WITH_FRAME;

#pragma parameter HSM_DECAL_SCALE 	                  "      Scale" 100 1 300 0.1
float HSM_DECAL_SCALE = global.HSM_DECAL_SCALE / 100;

#pragma parameter HSM_DECAL_POS_Y                     "      Position Y"  0 -100 100 0.1
float HSM_DECAL_POS_Y = global.HSM_DECAL_POS_Y / 100;


//---------------------------------------------------------------------------------------------------
//    TOP IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_TOP_TITLE			            "[ TOP EXTRA LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_TOP_OPACITY 	                "      Opacity" 100 0 100 0.1
float HSM_TOP_OPACITY = global.HSM_TOP_OPACITY / 100;

#pragma parameter HSM_TOP_BLEND_MODE 		        "      Blend Mode - OFF | NORM | ADD | MULT"  1 0 3 1
float HSM_TOP_BLEND_MODE = global.HSM_TOP_BLEND_MODE;

#pragma parameter HSM_TOP_SOURCE_MATTE_TYPE         "      Source Matte Color - Black | White | None"  0 0 2 1
float HSM_TOP_SOURCE_MATTE_TYPE = global.HSM_TOP_SOURCE_MATTE_TYPE;

#pragma parameter HSM_STANDARD_TOP_SCALE_WITH_FRAME "      Scale With Frame - OFF | ON"  0 0 1 1
float HSM_STANDARD_TOP_SCALE_WITH_FRAME = global.HSM_STANDARD_TOP_SCALE_WITH_FRAME;

#pragma parameter HSM_TOP_SCALE 	                "      Scale" 100 1 300 0.1
float HSM_TOP_SCALE = global.HSM_TOP_SCALE / 100;

#pragma parameter HSM_TOP_POS_Y                     "      Position Y"  0 -100 100 0.1
float HSM_TOP_POS_Y = global.HSM_TOP_POS_Y / 100;