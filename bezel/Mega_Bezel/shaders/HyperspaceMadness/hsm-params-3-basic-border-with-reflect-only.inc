//---------------------------------------------------------------------------------------------------
//    STANDARD BACKGROUND IMAGE LAYER
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_STANDARD_IMG_TITLE	        "[ STANDARD IMAGE LAYERS ]______________________________________" 0 0 0.01 0.01

#pragma parameter HSM_STANDARD_IMG_ASPECT_RATIO_MODE 	    "      Aspect Ratio - FULL | EXPLICIT | 16:9 | 9:16"  2 0 3 1
float HSM_STANDARD_IMG_ASPECT_RATIO_MODE = global.HSM_STANDARD_IMG_ASPECT_RATIO_MODE;

#pragma parameter HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT 	"      Explicit Aspect Ratio"  1.777 0.01 4 0.01
float HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT = global.HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT;

#pragma parameter HSM_BG_OPACITY 	                        "      Background Image Opacity" 100 0 100 0.1
float HSM_BG_OPACITY = global.HSM_BG_OPACITY / 100;

#pragma parameter HSM_BG_BLEND_MODE 		                "      Background Blend Mode - OFF | NORM | ADD | MULT"  2 0 3 1
float HSM_BG_BLEND_MODE = global.HSM_BG_BLEND_MODE;

#pragma parameter HSM_STANDARD_BG_SHOW_OVER_SCREEN 	        "      Background Show over Screen" 0 0 1 1
float HSM_STANDARD_BG_SHOW_OVER_SCREEN = global.HSM_STANDARD_BG_SHOW_OVER_SCREEN / 100;