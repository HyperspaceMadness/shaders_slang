/*   
hsm-params-basic-border

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

//---------------------------------------------------------------------------------------------------
//    BASIC BACKGROUND IMAGE LAYER
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_BASIC_BG_IMG_TITLE	                    "[ BASIC BACKGROUND IMAGE LAYER ]:" 0 0 0.01 0.01

#pragma parameter HSM_STANDARD_IMG_ASPECT_RATIO_MODE 	"      Aspect Ratio - FULL | EXPLICIT | 16:9 | 9:16"  2 0 3 1
float HSM_STANDARD_IMG_ASPECT_RATIO_MODE = global.HSM_STANDARD_IMG_ASPECT_RATIO_MODE;

#pragma parameter HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT 	"      Explicit Aspect Ratio"  1.777 0.01 4 0.01
float HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT = global.HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT;

#pragma parameter HSM_BG_OPACITY 	                    "      Opacity" 100 0 100 0.1
float HSM_BG_OPACITY = global.HSM_BG_OPACITY / 100;

#pragma parameter HSM_BG_BLEND_MODE 		            "      Blend Mode - OFF | NORM | ADD | MULT"  2 0 3 1
float HSM_BG_BLEND_MODE = global.HSM_BG_BLEND_MODE;

#pragma parameter HSM_STANDARD_BG_SHOW_OVER_SCREEN 		"      Show over Screen"  0 0 1 1
float HSM_STANDARD_BG_SHOW_OVER_SCREEN = global.HSM_STANDARD_BG_SHOW_OVER_SCREEN;
