//---------------------------------------------------------------------------------------------------
//    SIMPLE BACKGROUND IMAGE LAYER
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_SIMPLE_IMG_TITLE	                    "[ SIMPLE IMAGE LAYERS ]________________________________________" 0 0 0.01 0.01

#pragma parameter HSM_SIMPLE_IMG_ASPECT_RATIO 				"      Aspect Ratio - Full | 16:9 | 9:16"  0 0 6 1
float HSM_SIMPLE_IMG_ASPECT_RATIO = global.HSM_SIMPLE_IMG_ASPECT_RATIO;

#pragma parameter HSM_BG_OPACITY 	            "      Background Image Opacity" 100 0 100 0.1
float HSM_BG_OPACITY = global.HSM_BG_OPACITY / 100;

#pragma parameter HSM_BG_BLEND_MODE 		        "      Background Blend Mode - Off | Norm | Add | Mult"  2 0 3 1
float HSM_BG_BLEND_MODE = global.HSM_BG_BLEND_MODE;

#pragma parameter HSM_SIMPLE_BG_IMG_SHOW_OVER_SCREEN 	    "      Show Background over Screen" 0 0 1 1
float HSM_SIMPLE_BG_IMG_SHOW_OVER_SCREEN = global.HSM_SIMPLE_BG_IMG_SHOW_OVER_SCREEN / 100;

#pragma parameter HSM_LED_OPACITY 	            "      LED Image Opacity" 0 0 100 0.1
float HSM_LED_OPACITY = global.HSM_LED_OPACITY / 100;

#pragma parameter HSM_LED_BLEND_MODE 		    "      LED Blend Mode - Off | Norm | Add | Mult"  2 0 3 1
float HSM_LED_BLEND_MODE = global.HSM_LED_BLEND_MODE;

#pragma parameter HSM_TOP_OPACITY 	            "      Top Extra Image Opacity" 0 0 100 0.1
float HSM_TOP_OPACITY = global.HSM_TOP_OPACITY / 100;

#pragma parameter HSM_TOP_BLEND_MODE 		    "      Top Extra Image Blend Mode - Off | Norm | Add | Mult"  1 0 3 1
float HSM_TOP_BLEND_MODE = global.HSM_TOP_BLEND_MODE;

// //---------------------------------------------------------------------------------------------------
// //    VIEWPORT VIGNETTE
// //---------------------------------------------------------------------------------------------------
// #pragma parameter HSM_VIEWPORT_VIGNETTE_TITLE			    "[ VIEWPORT VIGNETTE LAYER ]____________________________________" 0 0 0.01 0.01

// #pragma parameter HSM_VIEWPORT_VIGNETTE_OPACITY            "      Opacity" 50 0 100 2
// float HSM_VIEWPORT_VIGNETTE_OPACITY = global.HSM_VIEWPORT_VIGNETTE_OPACITY / 100;

//---------------------------------------------------------------------------------------------------
//    STATIC ELEMENT GAMMA
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_STATIC_GAMMA_TITLE "[ STATIC IMAGE LAYER GAMMA ]___________________________________" 0 0 0.01 0.01

#pragma parameter HSM_STATIC_LAYERS_GAMMA		    "      Static Layers Gamma Adjust" 1 0.01 5 0.01
float HSM_STATIC_LAYERS_GAMMA = global.HSM_STATIC_LAYERS_GAMMA;


//---------------------------------------------------------------------------------------------------
//    NIGHT LIGHTING IMAGE
//---------------------------------------------------------------------------------------------------
#pragma parameter HSM_NIGHT_LIGHTING_TITLE "[ NIGHT LIGHTING ]_____________________________________________" 0 0 0.01 0.01

#pragma parameter HSM_NIGHT_OPACITY       "      Opacity"  0 0 100 1
float HSM_NIGHT_OPACITY = global.HSM_NIGHT_OPACITY / 100;