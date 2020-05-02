------------------------------------------------------------------------------------------------------------
HyperspaceMadness Mega Bezel Reflection Shader Readme - 2020-04-19
------------------------------------------------------------------------------------------------------------

The bezel reflection Shader chain is for adding a bezel and reflection around the screen


------------------------------------------------------------------------------------------------------------
How to use it:
	1. Turn Retroarch Video Settings Aspect Ratio to match your monitor
	2. Turn Retroarch Video Settings Integer Scale OFF
	3. Load the shader preset!


------------------------------------------------------------------------------------------------------------
How the shader chain works:

-Scale of the screen/tube as well as the reflection and other shaders in the chain use a 
	common scaling method and parameters
-The scaling is in the hsm-mega-bezel-include.inc which defines scale and curvature functions 
	and user parameters used by the shaders that need them

	Some of the stuff the mega screen scale does:

	Aspect Ratio
	Automatic switching between horizontal or vertical aspect ratio used by vertical/TATE games
	Integer Scale or Non-Integer scale
	Controls Vertical Scanlines when available in crt shader
	Horizontal Integer scale for vertical scanlines
	Crop Overscan enables cropping which properly affects the integer scale
	Integer scale multiple offset to make the screen smaller or bigger by integer steps


-----------------------------------------------------------------------------------------------------------
Shader chain shaders in order

-BR_CrtPass
	hsm-crt-guest-dr-venom-with-scaling.slang (Or any CRT shader which integrates the mega-screen-scale scaling)
-hsm-blur-scanlines.slang - If necessary turn on to blurs scanlines to avoid moire ringing artifacts
-hsm-blur-outside-screen-horiz.slang - adds blur which is used by the reflection pass
-BR_MirrorBlurredPass
	hsm-blur-outside-screen-vert.slang - adds blur which is used by the reflection pass
-BR_MirrorReflectionDiffusedPass
	blur9x9.slang - Resolution is further reduced and more blur applied
-BR_MirrorFullscreenGlowPass
	blur9x9.slang - Resolution is drastically reduced and more blur applied
-hsm-bmega-bezel-reflection.slang - adds the reflection effect


----------------------------------------------------------------------------------------------------------------
How to Integrate mega-screen-scale into a crt shader

You will need to integrate the screen scaling in your crt so it can share the same screen scaling as the other shaders

- In the crt shader you need to add the include like this:

	#include "hsm-mega-screen-scale.inc"


- In the vertex main function you need to scale and move the initial screen coordinate, E.G.

	void main()
	{
		gl_Position = global.MVP * Position;
		vTexCoord = TexCoord;

		// Add the following line
		vTexCoord = HMSS_GetScreenVTexCoord(vTexCoord);
	}


- Use the curvature function from hsm-mega-bezel-include.inc to add curvature

	vec2 curved_coord = HMSS_GetCurvedCoord(vTexCoord, 1);


- Use screen scale to multiply OutputSize wherever it is used

	screenScale =  HMSS_GetScreenScale();
	float sample_offset = (global.SourceSize.y * global.OutputSize.w * screenScale.y) * 0.5;


- Use crop overscan to adjust the sampling of the image to sample the cropped range

	texcoord  = HMSS_GetCropOverscanCoord(texcoord, SourceSize.xy);