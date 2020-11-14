------------------------------------------------------------------------------------------------------------
HyperspaceMadness Mega Bezel Shader Readme
------------------------------------------------------------------------------------------------------------


----------------------------------------
------------What does it do?------------
----------------------------------------

    - Adds an auto-generated bezel around the screen with reflection
    - Enable easier use of bezels and more "natural" presentation
    - Ease of use for screen scaling and automatic aspect ratio with existing shaders
    - Provide a consistent set of enhanced features wrapped around the core crt shaders



----------------------------------------
------------How does it work?-----------
----------------------------------------

  -In general there is a background image which fills the screen, then the game screen is drawn scaled down with an automatically generated bezel image drawn around the screen. 
  -The bezel and frame you see around the screen auto generated and not part of the background image
  -Most things can be changed to your taste with adjustment of the parameters, so try them out!



----------------------------------------
------------Installation----------------
----------------------------------------

    - If you have previous versions of the Mega Bezel installed:
        - Delete shaders/shaders_slang/bezel/shaders/HyperspaceMadness
        - Delete all hsm presets from shaders/shaders_slang/bezel
        - Inside the .zip is a shaders folder, drop this shaders folder directly over your existing one and everything will go into the right place
    - Set video driver to Vulcan (It will run in GLCore but seems 2x faster in Vulcan)
    - Set video aspect ratio to your monitor aspect ratio, e.g. 16:9
    - Set integer scale to OFF
    - Load a preset in the shaders menu, Mega Bezel shaders are found in shaders_slang/bezel



----------------------------------------
------------Choosing a Preset-----------
----------------------------------------

    Presets are named/sorted by performance
        The most flexible (and most resource hungry) are at the top starting with index 0
        As the name's index number increases the presets get faster and less flexible
    Currently all presets will include all the mega bezel settings except for SCREENSCALE-ONLY which has a subset of parameters

    - Group 0 BASE - Most flexible shader presets, one preset for each different CRT Shader (Includes MDAPT, ScaleFX & GTU)
    - Group 1 GLASS - Glass presets which show a blurry reflection in the area around the screen
    - Group 2 ALT - Same as group 0 but have different parameter values
    - Group 3 SIMPLIFIED - Same as Base except extra passes before the CRT pass removed (Includes MDAPT, ScaleFX & GTU)
    - Group 4 Reflection-Only - Meant to be used with retroarch's standard overlay feature. Removes the frame and other images applied
    - Group 5 SCREENSCALE-ONLY - Only includes the screen scaling and screen effects like fake scanlines



----------------------------------------
----------  Troubleshooting  -----------
----------------------------------------

    In general if you have difficulties loading the shader try loading it with teh imageviewer core
        Steps
            -Add the imageviewer core to retroarch with the online updater
            -Open an image with this core
            -Load the shader
            -If the shader loads correctly then the shader is working.

    When using the shader in imageviewer works, but it doesn’t work when using a core, it is possibly related to the core, or the graphics card being overwhelmed by resource usage with both the core demands and the shader demands

    If you still have difficulties loading the shader with a specific core update the core
    If you still have difficulties download a new separate version of retroarch and try it there. Sometimes problems lurk in some random config file somewhere which are very hard to track down

    To see errors coming from retroarch you need to set up your logging settings:
        Logging - Logging Verbosity - ON
            Frontend Logging - 1(Info)
            Log to File - Off 
        These settings will cause a log window to come up when you launch, and you should see any retroarch errors



-----------------------------------------------------------------------------------------------------------------------------------
-----  Parameter Descriptions  ----------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------

_____[ HSM MEGA BEZEL  V.20XX-XX-XX-X ]____________________

[ DEBUG ]  Debug ON - set to 1 to turn Debug On


_____[ FLIP & ROTATE ]_________________________________________

[ VERTICAL FLIP ]  Flip Vertical - For 3D Cores --- Some 3D cores flip the viewport, this flips it back

[ ROTATE ]  Rotate CRT Tube --- Turns the tube 90 degrees counter counter-clockwise


_____[ ASPECT RATIO ]__________________________________________

[ ASPECT ]  Orientation --- Should the aspect be horizontal or vertical?
            0 - Auto - Chooses vertical vs horizontal based on the core resolution
            1 - Horizontal, uses horizontal aspect
            2 - Vertical, uses vertical aspect

[ASPECT]  Type --- Choose type of aspect ratio
            0 - Auto - Choose aspect ratio based on educated guesses about the core resolution
            1 - Explicit - Use the aspect ratio from the [ASPECT]  Explicit Aspect Ratio parameter
            2 - 4:3 (Almost all arcade games are 4:3)
            3 - 3:2
            4 - 16:9
            5 - PAR (The aspect ratio of the pixel resolution)
            6 - Full (The screen will scale to the full viewport)

[ASPECT]  Explicit Aspect Ratio --- Ratio used when [Aspect] Type is set to Explicit or if Auto is chosen and no matching resolution can be found


------ [SCALING] -------------------------------------------------------------------------------------------

[SCALING]  Int Scale Mode
            0 - Off, Use Non-Integer Scale
            1 - ShortAxis Integer Scale On - for the viewport (monitor) in landscape mode this is the vertical axis
                If the screen/tube aspect ratio is vertical then integer scale is used for both horizontal and vertical axes
            2 - Integer Scale on both axes

[SCALING]  Int Scale Multiple Offset --- Adjusts the size of the screen by increasing the multiple of the core resolution (on both axes) when using integer scale, to make the screen larger or smaller

[SCALING]  Int Scale Multiple Offset Long Axis --- Adds an additional multiple offset but for only the long axis, with a horizontal aspect ratio this is the horizontal axis

[SCALING]  Int Scale Border Min Height % --- The amount of vertical screen space reserved for the area around the screen when using integer scale

[SCALING]  Non-Integer Scale % --- If integer scale isn't used, this sets the vertical size of the vertical percentage of the full viewport

[SCALING]  Snap To Int-Scale Tolerance --- Snaps the non-integer scale to the closest integer scale within the tolerance 
                                            This allows you to set an approximate size for the screen and have it snap to an integer scale but not if it would be too much different

[ POSITION ]  Position X --- Moves the screen/tube sideways

[ POSITION ]  Position Y --- Moves the screen/tube up and down

------ [CROPPING] -------------------------------------------------------------------------------------------
    Cropping allows you to hide edges of the game image which were never meant to be seen 
    Negative values add empty space at the edges of the tube

[CROPPING]  Crop Overscan Top

[CROPPING]  Crop Overscan Bottom

[CROPPING]  Crop Overscan Left

[CROPPING]  Crop Overscan Right


------ [SCANLINES & SAMPLING] -------------------------------------------------------------------------------------------

[SCANLINE DIRECTION]  Guest & Easymode
            0 - Auto --- Chooses horizontal or vertical scanline direction based on aspect ratio
            1 - Horizontal scanlines
            2 - Vertical scanlines


------ [CORE RES SAMPLING] -------------------------------------------------------------------------------------------
    Adjusting core res sampling changes how the CRT percieves the core resolution
    e.g. If you use a core with 4X internal resolution you can set core res sampling to 0.25 it will appear if it was at 1x resolution
    To use ScaleFX to smooth the shapes in the core image you will need to set the core res sampling higher than 1, 
    otherwise you will not see the increased smoothing coming from ScaleFX

[CORE RES SAMPLING]  Scanline Dir --- Adjust the sampling in direction of the scanlines, 
                                        e.g. if the scanlines are horizontal adjust sampling along the horizontal axis

[CORE RES SAMPLING]  Opposite Dir --- Adjust the sampling in direction opposite of the scanlines, 
                                        e.g. if the scanlines are horizontal adjust sampling along the vertical axis

[INTERLACE]  Trigger Res --- Resolution where the shader should switch into its interlace or high res content mode.


------ [SPLIT SCREEN] -------------------------------------------------------------------------------------------
    Split Screen is for those platforms or games with multiple separate screens, like Nintendo DS, 3DS, or Punchout arcade 

[SPLIT SCREEN]  Split Thickness - Distance between screens when using split screen

[SPLIT SCREEN]  Center Fill --- Different methods to fill in the space between the screens
            0 - None --- Fill the area between the screens with the  
            1 - Bezel --- Draw 2 Bezels, a separate bezel for each sub-screen
            2 - Reflect --- In the empty space between the used parts of the screen do a reflection effects
            3 - Blend --- Blend the image from one screen into the other as we get closer to the center between both screens
            4 - Fade --- Mirror the image at the center edge of the screen, and fade toward the center
            5 - Blend and Fade --- Blend the image at the center edges together then blend towards black at the center


------ [CURVATURE] -------------------------------------------------------------------------------------------
    Applies tube curvature

[CURVATURE MODE]
        0 - 2D --- Simplest and fastest curvature
        1 - 3D Sphere --- Geometric projection from the surface of a sphere to the viewport - Same as CRT-Royale
        2 - 3D Sphere with adjusted corner mapping --- Very similar to #1
        3 - 3D Cylindrical Mapping --- Vertically flat curvature like a Trinitron, e.g. PVM or BVM

[2D CURVATURE]  2D Curvature on Long Axis - Curvature multiple on long axis, for a horizontal aspect ratio this is the horizontal axis

[2D CURVATURE]  2D Curvature on Short Axis - Curvature multiple on short axis, for a horizontal aspect ratio this is the vertical axis

[3D CURVATURE]  Radius - Radius for the sphere the 3D projection is done on, values from 1-4 then to be useful

[3D CURVATURE]  View Distance - This is the distance of the virtual camera from the Sphere

[3D CURVATURE]  Tilt Angle Y - Vertical Tilt, with split screen this will tilt both screens towards or away from the center


------ [POSITION] -------------------------------------------------------------------------------------------

[POSITION]  Position Offset X - Moves the entire screen and frame left and right

[POSITION]  Position Offset Y - Moves the entire screen and frame up and down


------ [COLOR] -------------------------------------------------------------------------------------------
    Color correction, almost all affect core image before it gets to the crt shader

[COLOR]  CRT Profile - Overall color adjustment to match particular standards or example crts
        -1 - No adjustment
        0 - SRGB (Standard color space for computer monitors)
        1 - BVM
        2 - P22 (P22 common phosphor coloring)
        3 - SMPTE-C - North american color standards in the 80s?
        4 - Philips Monitor color
        5 - Trinitron Monitor
        6 - LUT colors from Torridgristle

[COLOR]  Color Space
        0 - SRGB
        1 - DCI
        2 - Adobe
        3 - Rec. 2020

[COLOR]  Luminance - Used to brightens or darken the image

[COLOR]  Black Level - 
        Positive values make darks darker
        Negative values make blacks more gray
        By default it has a small negative value which makes black just a tiny bit gray which creates very slight scanlines in the black areas of the image

[COLOR]  Negative Crop Brightness - This is the brightness of the empty areas which have been revealed at the edges of the tube when negative cropping is used
        This allows the negative crop area to match the brightness of the black areas of the crt image (which are no longer black because of a negative black level)

[COLOR]  CRT Gamma - Gamma applied to the final CRT image


[PHOSPHOR PERSISTENCE]  Amount - Adds light trails behind moving objects
        Positive values give an after image the same color as what was there before
        Negative values give a bluish after image


------ [SCREEN FX] -------------------------------------------------------------------------------------------
    Screen-fx features affect the game screen area (illuminated part of the tube) and are applied after the crt shader 

[SCREEN FX]  Screen Corner Radius --- the roundness of the corner of the tube area
                                        The bezel corner radius follows this, and will match it by default

[SCREEN FX]  Screen Edge Sharpness --- Blends the edge of the game screen image to black, lower values will fade the edge

[SCREEN FX]  Screen Vignette --- Fade out the game screen as we move away from the center of the screen

[SCREEN FX]  Fake 240p Scanline Opacity --- Opacity of scanlines added on top of the crt image. 
                                            These scanlines are not tied to the core image resolution


------ [TUBE] -------------------------------------------------------------------------------------------
    The tube is the area from the inner edge of the bezel inward

[TUBE]  Black Edge Thickness --- Distance between the illuminated game screen and the inner edge of the bezel
                                Set this to 0 or less to remove the black edge

[TUBE]  Curvature Scale --- By default the bezel matches the tube curvature, this adjusts the bezel curvature on top of this basic curvature
                            If you set this to 0 the bezel inner edge would have no curvature

[TUBE]  Tube Glass Image Opacity --- Adds a static reflection on top of the tube 
                                    This comes from an image, the path for the image is set in the preset

[TUBE]  Tube Edge Shadow --- Adds a shadow from the bezel onto the tube
                            This will appear on top of the game screen when the black edge thicknss 0 or less


------ [BG IMAGE] -------------------------------------------------------------------------------------------

[BG IMAGE]  Vignette Opacity --- Adds vignette darkening on top of the background image


------ [BEZEL & FRAME COLOR] -------------------------------------------------------------------------------------------

[BEZEL & FRAME COLOR]  Color Hue --- The color of the bezel, e.g. yellow, blue etc

[BEZEL & FRAME COLOR]  Color Saturation --- How strong the color is

[BEZEL & FRAME COLOR]  Color Value/Brightness --- How bright the color is

[BEZEL & FRAME COLOR]  Blend Color with BG Image --- Blends the color with the background image

[BEZEL & FRAME COLOR]  Noise --- Adds noise into the color of the frame, bezel & highlight


------ [BEZEL] -------------------------------------------------------------------------------------------

[BEZEL]  Opacity --- Opacity of the bezel 0 hides the bezel

[BEZEL]  Width --- Width of area between the inner edge of the bezel and the inner edge of the frame on the sides of the tube

[BEZEL]  Height --- Height of area between the inner edge of the bezel and the inner edge of the frame on the top and bottom of the tube

[BEZEL]  Inner Corner Radius Scale --- Roundness of the corner on the inside edge of the bezel

[BEZEL]  Outer Corner Radius Scale --- Roundness of the corner on the outside edge of the bezel / inner edge of the frame

[BEZEL]  Inner Edge Thickness --- Thickness the small strip on the inner edge of the bezel, used to catch highlights from the screen reflection

[BEZEL]  Brightness --- Brightness adjustment of the color of the bezel

[BEZEL]  Highlight --- How much static highlight in the middle of the sides and top of the bezel

[BEZEL]  Bezel & BG Gamma Adjust --- Gamma adjustment to brighten or darken the bezel and background


------ [FRAME] -------------------------------------------------------------------------------------------

[FRAME]   Opacity --- Opacity of the frame 0 hides the frame

[FRAME]   Thickness --- Thickness or width of the frame

[FRAME]   Outer Corner Radius --- Roundness of the outer corner of the frame

[FRAME]   Pos Y Offset --- Vertical offset of the frame relative to the tube

[FRAME]   Shadow Opacity --- Strength of shadow from the frame

[FRAME]   Shadow Width --- How far the shadow extends from the edges of the frame


------ [REFLECTION BLUR] -------------------------------------------------------------------------------------------
    Blur applied on the reflection which gets stronger as it gets farther away from the tube  

[REFLECTION BLUR]  Num Samples --- Blur Samples

[REFLECTION BLUR]  Min --- Minimum Blur, the amount of blur at the inside of the bezel

[REFLECTION BLUR]  Max --- Opacity of the frame 0 hides the frame


------ [REFLECTION NOISE] -------------------------------------------------------------------------------------------
    Scattering of the reflection rays, gives the effect of surface roughness

[REFLECTION NOISE]   Amount --- This is the amount that the scattered effect is mixed with the simple blurred reflection

[REFLECTION NOISE]   Samples --- Number of scatter samples, more samples means a smoother effect

[REFLECTION NOISE]   Sample Distance --- How far away the scatter samples are taken, higher valu gives a rougher effect


------ [REFLECTION GLOBAL] -------------------------------------------------------------------------------------------

[REFLECTION GLOBAL]  Global Amount --- How much overall reflection, 0 means no reflection

[REFLECTION GLOBAL]  Global Gamma Adjust --- Gamma adjustment on the reflection


------ [REFLECTION AMOUNT] -------------------------------------------------------------------------------------------

[REFLECTION AMOUNT]  Inner Edge Amount

[REFLECTION AMOUNT]  Inner Edge Fullscreen Glow

[REFLECTION AMOUNT]  Direct Reflection

[REFLECTION AMOUNT]  Diffused Reflection

[REFLECTION AMOUNT]  FullScreen Glow

[REFLECTION AMOUNT]  FullScreen Glow Gamma


------ [REFLECTION AMOUNT] -------------------------------------------------------------------------------------------

[REFLECTION FADE]  Fade Amount

[REFLECTION FADE]  Radial Fade Width

[REFLECTION FADE]  Radial Fade Height

[REFLECTION FADE]  Lateral Outer Fade Position

[REFLECTION FADE]  Lateral Outer Fade Distance


------ [REFLECTION CORNER FADE] -------------------------------------------------------------------------------------------

[REFLECTION CORNER FADE]  Corner Fade

[REFLECTION CORNER FADE]  Corner Fade Distance

[REFLECTION CORNER FADE]  Corner Inner Spread

[REFLECTION CORNER FADE]  Corner Outer Spread


------ [REFLECTION CORNER FADE] -------------------------------------------------------------------------------------------

[REFLECTION CORNER ROTATION]  Offset Top

[REFLECTION CORNER ROTATION]  Offset Bottom


------ [TOP IMAGE LAYER] -------------------------------------------------------------------------------------------

[TOP IMAGE LAYER]  Opacity

[TOP IMAGE LAYER]  Blend Mode - Normal, Add, Mult, Under...

[TOP IMAGE LAYER]  Mask - ALL, Tube, Bezel+, Frame+, Frame, BG


-------------More to Come---------------

-------------------------------------------------------------------
------How to Integrate mega-screen-scale into a crt shader------------
----------------------------------------

You will need to integrate the screen scaling in your crt so it can share the same screen scaling as the other shaders

- In the crt shader you need to add the include like this:

	#include "hsm-globals-and-screen-scale-params.inc"


- In the vertex main function you need to scale and move the initial screen coordinate, E.G.

	void main()
	{
		gl_Position = global.MVP * Position;
		vTexCoord = TexCoord;

		// Add the following line
		vTexCoord = HSM_GetScreenVTexCoord(vTexCoord);
	}


- Use the curvature function from hsm-mega-bezel-include.inc to add curvature

	vec2 curved_coord = HSM_GetCurvedCoord(vTexCoord, 1);


- Use screen scale to multiply OutputSize wherever it is used

	screenScale =  HSM_GetScreenScale();
	float sample_offset = (global.SourceSize.y * global.OutputSize.w * screenScale.y) * 0.5;


- Use crop overscan to adjust the sampling of the image to sample the cropped range

	texcoord  = HSM_GetCropOverscanCoord(texcoord, SourceSize.xy);