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
#pragma parameter HSM_BASIC_BG_IMG_TITLE	                    "[ BASIC BACKGROUND IMAGE LAYER ]_______________________________" 0 0 0.01 0.01

#pragma parameter HSM_BG_OPACITY 	                    "      Opacity" 100 0 100 0.1
float HSM_BG_OPACITY = global.HSM_BG_OPACITY / 100;

#pragma parameter HSM_BG_BLEND_MODE 		            "      Blend Mode - Off | Norm | Add | Mult"  2 0 3 1
float HSM_BG_BLEND_MODE = global.HSM_BG_BLEND_MODE;

#pragma parameter HSM_STANDARD_IMG_ASPECT_RATIO 		"      Aspect Ratio - Full | 16:9 | 9:16"  0 0 2 1
float HSM_STANDARD_IMG_ASPECT_RATIO = global.HSM_STANDARD_IMG_ASPECT_RATIO;

#pragma parameter HSM_STANDARD_BG_SHOW_OVER_SCREEN 		"      Show over Screen"  0 0 1 1
float HSM_STANDARD_BG_SHOW_OVER_SCREEN = global.HSM_STANDARD_BG_SHOW_OVER_SCREEN;
