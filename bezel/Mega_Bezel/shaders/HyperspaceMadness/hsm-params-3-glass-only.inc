/*   
hsm-params-basic-border

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:
	-Parameters to be used by Mega Screen Scale and Mega Bezel
*/

//---------------------------------------------------------------------------------------------------
//    STANDARD BACKGROUND IMAGE LAYER
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_STANDARD_IMG_TITLE	                    "[ STANDARD IMAGE LAYERS ]______________________________________" 0 0 0.01 0.01

#pragma parameter HSM_BG_OPACITY 	            "      Background Image Opacity" 0 0 100 0.1
float HSM_BG_OPACITY = global.HSM_BG_OPACITY / 100;

#pragma parameter HSM_BG_BLEND_MODE 		        "      Background Blend Mode - Off | Norm | Add | Mult"  2 0 3 1
float HSM_BG_BLEND_MODE = global.HSM_BG_BLEND_MODE;