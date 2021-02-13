------------------------------------------------------------------------------------------------------------
HyperspaceMadness Mega Bezel Shader Readme
------------------------------------------------------------------------------------------------------------


----------------------------------------
What does it do?
----------------------------------------

  * Adds an auto-generated bezel around the screen with reflection
  * Enable easier use of bezels and more "natural" presentation
  * Ease of use for screen scaling and automatic aspect ratio with existing shaders
  * Provide a consistent set of enhanced features wrapped around the core crt shaders
  * Layering images to add art and visual effects



----------------------------------------
How does it work?
----------------------------------------

  * In general there is a background image which fills the screen, then the scaled down game screen with an automatically generated bezel image is drawn on top. 
  * The bezel and frame you see around the screen auto generated and not part of the background image
  * Additional Images can be layered on top to augment the look
  * Most things can be changed to your taste with adjustment of the parameters, so try them out!



----------------------------------------
Installation
----------------------------------------

  * If you have previous versions of the Mega Bezel installed:
    * Delete shaders/shaders_slang/bezel/shaders/HyperspaceMadness
    * Delete all hsm presets from shaders/shaders_slang/bezel
  * Inside the .zip is a shaders folder, drop this shaders folder directly over your existing one and everything will go into the right place
  * Set video driver to Vulcan or GLCore (Vulcan seems faster)
  * Set video aspect ratio to your monitor aspect ratio, e.g. 16:9
  * Set integer scale to OFF
  * Load a preset in the shaders menu, Mega Bezel shaders are found in shaders_slang/bezel/Mega_Bezel



----------------------------------------
Choosing a Preset
----------------------------------------

Presets are named/sorted by performance
The most flexible and most resource hungry are at the top starting with index 0
As the name's index number increases the presets get faster but less flexible

  * **Group 0 BASE**
    * Most flexible shader presets, one preset for each different CRT Shader 
    * Includes MDAPT, ScaleFX & GTU
    * The Guest-DrVenom preset is considered the default preset
  * **Group 1 GLASS** - Glass presets which show a blurry reflection in the area around the screen 
    * Includes MDAPT, ScaleFX & GTU
    * Does not include the additional Image Layering.
  * **Group 3 SIMPLE**
      * Same as Base except extra passes before the CRT pass removed 
      * No MDAPT, ScaleFX & GTU
      * Includes only a subset of the image layers (Background and Top Extra Layer)
  * **Group 4 REFLECT_ONLY**
    * Image Layering pass has been removed
    * No auto-generated bezel and frame and no image layering
    * Includes an image which can be used for the background/bezel which the reflection will appear on top of
    * When used with an image which was a snapshot from a default mega bezel preset the reflection masking will match the frame
    * Can be used with a standard Retroarch overlay
    * When used with a standard overlay the Retroarch video aspect ratio can be set to something like 4:3 to achieve higher performance

  * **Group 5 SCALING-ONLY**
    * Includes only the screen scaling and screen effects like fake scanlines
    * All passes after CRT pass have been removed

**Presets in Mega_Bezel/Variations**

  * These presets are simple presets referencing one of the presets in the Mega_Bezel folder
  * They reference the original preset then have adjusted parameters or texture paths

----------------------------------------
Troubleshooting
----------------------------------------

 * If you have difficulties loading the shader try loading it with the imageviewer core
    * **Steps**
        * Add the imageviewer core to Retroarch with the online updater
        * Open an image with this core
        * Load the shader
        * If the shader loads correctly then the shader is working.
    
 * When shader works in imageviewer, but doesn’t work when using a core, it is possibly related to the core, or the graphics card being overwhelmed by resource usage with both the core requirements and the shader requirements
   
 * If you still have difficulties loading the shader with a specific core update the core
 * If you still have difficulties download a new separate version of Retroarch and try it there. Sometimes problems lurk in some random config file somewhere which are very hard to track down
   
 * **To see errors** coming from Retroarch you need to set up your logging settings:
    * **Logging - Logging Verbosity - ON**
      * **Frontend Logging - 0(Debug)**
      * **Log to File - Off**
    * These settings will **cause a log window to come up** when you launch, and you should see any Retroarch errors, and shader loading details



-----------------------------------------------------------------------------------------------------------------------------------
Parameter Descriptions
-----------------------------------------------------------------------------------------------------------------------------------

**[ --- HSM MEGA BEZEL  20XX-XX-XX-0 --- ]______________________________________________________________________**

**[ FLIP & ROTATE ]______________________________________________________________________**

​		**Flip Viewport Vertical** --- Some cores flip the viewport (full monitor area), this flips it back

​		**Flip Core Image Vertical** --- Some cores flip the core image, this flips it back

​		**Rotate CRT Tube** --- Turns the tube 90 degrees counter counter-clockwise

**[ ASPECT RATIO ]_______________________________________________________________________**

​		**Orientation** --- Should the aspect be tall or wide? This does not rotate the image.
​					**0 - Auto** - Chooses vertical vs horizontal based on the core resolution
​					**1 - Horizontal** - uses horizontal aspect
​					**2 - Vertical** - uses vertical aspect

​		**Type** --- Choose type of aspect ratio
​        			**0 - Auto** - Choose aspect ratio based on educated guesses about the core resolution
​        			**1 - Explicit** - Use the aspect ratio from the [ASPECT]  Explicit Aspect Ratio parameter
​        			**2 - 4:3** (Almost all arcade games are 4:3)
​        			**3 - 3:2**
​        			**4 - 16:9**
​        			**5 - PAR** (The aspect ratio of the pixel resolution)
​        			**6 - Full** (The screen will scale to the full viewport)

​		**Explicit Aspect Ratio** --- Ratio used when [Aspect] Type is set to Explicit or if Auto is chosen and no matching resolution can be found

**[SCALING]_______________________________________________________________________________________________________**

- **Show Resolution Info**
- **Int Scale Mode**
  - **0 - Off,** Use Non-Integer Scale
  - **1 - ShortAxis Integer Scale On** - for the viewport (monitor) in landscape mode this is the vertical axis, If the screen/tube aspect ratio is vertical then integer scale is used for both horizontal and vertical axes
  - **2 - Integer Scale on both axes**

- **Int Scale Multiple Offset**
  - Adjusts the size of the screen by increasing the multiple of the core resolution (on both axes) when using integer scale, to make the screen larger or smaller
- **Int Scale Multiple Offset Long Axis**
  - Adds an additional multiple offset but for only the long axis, with a horizontal aspect ratio this is the horizontal axis
- **Int Scale Border Min Height %**
  - The amount of vertical screen space reserved for the area around the screen when using integer scale
- **Non-Integer Scale %**
  - If integer scale isn't used, this sets the vertical size of the vertical percentage of the full viewport
- **Snap To Int-Scale Tolerance**
  - Snaps the non-integer scale to the closest integer scale within the tolerance. This allows you to set an approximate size for the screen and have it snap to an integer scale but not if it would be too much different

**[POSITION]____________________________________________________________________________________**

- **Position X** - Moves the entire screen and frame left and right
- **Position Y** - Moves the entire screen and frame up and down

**[CROPPING]____________________________________________________________________________________**
    Cropping allows you to hide edges of the game image which were never meant to be seen 
    Negative values add empty space at the edges of the tube

- **Crop Overscan Top**
- **Crop Overscan Bottom**
- **Crop Overscan Left**
- **Crop Overscan Right**

**[CORE RES SAMPLING]____________________________________________________________________________________**

- Adjusting core res sampling changes how the CRT perceives the core resolution
  e.g. If you use a core with 4X internal resolution you can set core res sampling to 0.25 it will appear if it was at 1x resolution
  To use **ScaleFX** to smooth the shapes in the core image you will need to set the core res sampling higher than 1, otherwise you will not see the increased smoothing coming from ScaleFX

- **Scanline Direction Multiplier**
  - Adjust the sampling in direction of the scanlines
  - E.G. if the scanlines are horizontal adjust sampling along the horizontal axis
- **Opposite Direction Multiplier**
  - Adjust the sampling in direction opposite of the scanlines
  - E.G. if the scanlines are horizontal adjust sampling along the vertical axis

**[ SCANLINES ]____________________________________________________________________________________**

- **Scanline Direction (GDV & Easymode)**
  - **0 - Auto** --- Chooses horizontal or vertical scanline direction based on aspect ratio
  - **1 - Horizontal** scanlines
  - **2 - Vertical** scanlines
- **Interlace and Fake Scanlines Trigger Res**
  - Resolution where the shader should switch into its interlace or high res content mode.
- **Fake Scanline Opacity**
  - Opacity of scanlines added on top of the crt image.
  - These scanlines are not tied to the core image resolution

**[CURVATURE]____________________________________________________________________________________**
    Applies tube curvature

- **CURVATURE MODE**
  - **-1 - Turn Curvature Off**
  - **0 - 2D** - Simplest and fastest curvature
  - **1 - 3D Sphere**  -  Geometric projection from the surface of a sphere to the viewport - Same as CRT-Royale
  - **2 - 3D Sphere with adjusted corner mapping** --- Very similar to #1
  - **3 - 3D Cylindrical Mapping** --- Vertically flat curvature like a Trinitron, e.g. PVM or BVM
- **2D Curvature on Long Axis** - Curvature multiple on long axis, for a horizontal aspect ratio this is the horizontal axis
- **2D Curvature on Short Axis** - Curvature multiple on short axis, for a horizontal aspect ratio this is the vertical axis
- **3D Radius** - Radius for the sphere the 3D projection is done on, values from 1-4 then to be useful
- **3D View Distance** - This is the distance of the virtual camera from the Sphere
- **3D Tilt Angle Y** - Vertical Tilt, with split screen this will tilt both screens towards or away from the center

**[ PHOSPHOR PERSISTENCE ]_______________________________________________________________________**

- **Amount**
  - How long the light trail behind the moving object, affects all colors, 0 is OFF
- **Red Persistence**
- **Green Persistence**
- **Blue Persistence**

**[ SCANLINES ON BLACK ]___________________________________________________________________**

- **Black Level**
  * Positive values make darks darker
  * Negative values make blacks more gray
  * Defaults to -4 so that the black areas are not 100% black so you get very faint scanlines

**[ CRT GAMMA ]__________________________________________________________________________________**

- **CRT Gamma** (Linear to Gamma Space Encode) Def 2.2

**[ SCREEN VIGNETTE ]________________________________________________________________________**

- **Screen Vignette Opacity** --- Fade out the game screen as we move away from the center of the screen

**[ REFLECTION APPEARANCE ]____________________________**__________________________________________

- **Screen Vignette Opacity in Reflection** - How much vignette darkening we will see in the reflection
- **Screen Reflection Scale**
  - Scales the reflection from the center
  - With a larger scale, the image from the screen will appear without mirroring, like the Big Blur preset
- **Screen Reflection Pos X**
  - Shift the reflection left or right
- **Screen Reflection Pos Y**
  - Shift the reflection up or down

**[ SCREEN EDGE ]________________________________________________________________________**

- **Corner Radius** --- the roundness of the corner of the tube area
                                          The bezel corner radius follows this, and will match it by default
- **Edge Sharpness** --- Blends the edge of the game screen image to black, lower values will fade the edge
- **Black Edge Thickness** --- Distance between the illuminated game screen and the inner edge of the bezel
  - Set this to 0 or less to remove the black edge

**[ TUBE IMAGES ]________________________________________________________________________**
    The tube is the area from the inner edge of the bezel inward

- **Colored Gel Multiply Amount** - Image applied like a colored gel in photography
  - Used to make vector games which output black and white colored, E.G Battlezone
- **Colored Gel Additive Amount** - Image applied as a brightening of the tube area
  - Used to add color to the screen as if it was the gel being diffusely lit from outside the monitor
- **Tube Static Reflection Opacity**
  - This is the shine on the tube which imitates reflection from the environment
- **Tube Static Reflection Scale**
  - Scales the tube reflection from the center

**[ CRT IS LAST PASS ]__________________________________________________________________________________________**

- **CRT is Last Pass**
  - Blacks out outside the screen, used for the scaling only presets

**[ INTRO SEQUENCE ]________________________________________________________________________________________________________**
​	Animation sequence which plays when the content starts up, animation times are in frames. The frame rate for most games 60 fps

- **Show Intro**
  - 0 - OFF
  - 1 - When Content Loads
  - 2 - Repeat
- **Speed**
  - Overall speed of the entire intro. 1 is full speed

**[ INTRO LOGO ]________________________________________________________________________________________________________**

- **Logo Blend Mode**
  - 0 - Off
  - 1 - Normal Blending
  - 2 - Additive Blending - Added on as added with a projector
  - 3 - Multiply Blending - Image is applied by darkening the under layer
- **Logo Over Solid Color**
  - 0 - Off - The Logo is layered under the solid color
  - 1 - ON - The Logo is layered over the solid color
- **Logo Height (0 for exact resolution)**
- **Logo Res X**
  - X Resolution of the logo image
- **Logo Res Y**
  - Y Resolution of the logo image
- **Logo Placement **
  - 0 - Middle
  - 1 - Top Left
  - 2 - Top Right
  - 3 - Bottom Left
  - 4 - Bottom Right
- **Logo Wait Before Start Frames**
  - How many frames before it starts to fade in
- **Logo Fade In Frames**
  - How many frames to fade in
- **Logo Hold Frames**
  - How many frames to hold the image at full opacity before the fade out starts
- **Logo Fade Out Frames**
  - How many frames to fade out

**[ INTRO SOLID COLOR ]_____________________________________________________________________________________________________**

- **Solid Color Blend Mode**
  - 0 - Off
  - 1 - Normal Blending
  - 2 - Additive Blending - Added on as added with a projector
  - 3 - Multiply Blending - Image is applied by darkening the under layer
- **Solid Color Hue**
- **Solid Color Saturation**
- **Solid Color Value**
- **Solid Color Hold Frames**
  - How many frames to hold the solid color
- **Solid Color Fade Out Frames**
  - How many frames to fade out

**[ INTRO STATIC NOISE ]____________________________________________________________________________________________________**

- **Static Noise Blend Mode**
  - **0 - Off**
  - **1 - Normal Blending**
  - **2 - Additive Blending** - Added on as added with a projector
  - **3 - Multiply Blending** - Image is applied by darkening the under layer
- **Static Noise Hold Frames**
  - How many frames to hold the static noise
- **Static Noise Fade Out Frames**
  - How many frames to fade out

**[ INTRO SOLID BLACK ]____________________________________________________________________________________________________**

- **Solid Black Hold Frames**
  - How many frames to hold the solid black before the fade out starts
- **Solid Black Fade Out Frames**
  - How many frames to fade out

**[ BEZEL ]_________________________________________________________________________________________________________**

- **Use Independent Scale & Curvature**
  - Allows you to adjust the bezel scale independent of the screen
- **Independent Scale**
  - Base scale for the bezel default is 82.97 which is the same as the default screen size
- **Independent Curvature X**
  - Horizontal curvature for the bezel when in independent mode
- **Independent Curvature Y**
  - Vertical curvature for the bezel when in independent mode
- **Inner Curvature Scale Multiplier**
  - Multiplier the curvature of the inner edge of the bezel
  - Default is 100 which will match the tube curvature
  - Multiplies the curvature in normal and independent mode

- **Opacity**
  - At 100 the bezel is fully visible

- **Blend Mode**
  - **0 - Off**
  - **1 - Normal Blending**
  - **2 - Additive Blending** - Added on as added with a projector
  - **3 - Multiply Blending** - Image is applied by darkening the under layer

- **Width**
  - Thickness of the bezel on the sides of the tube, default is 125

- **Height**
  - Thickness of the bezel on the top and bottom of the tube, default is 100

- **Inner Edge Thickness**
  - Thickness of edge of inner, default 100

- **Inner Edge Sharpness** - Def 90
- **Inner Corner Radius Scale** - Def 50
  - Roundness of the inner corner of the bezel, it is a multiplier of the roundness of the screen corner
  - 100 gives you the same roundness as the screen corner

- **Outer Corner Radius Scale** - Def 100
  - Roundness of the inner corner of the bezel, it is a multiplier of the roundness of the screen corner
  - 100 gives you the same roundness as the screen corner

- **Outer Curvature Scale**
  - Amount of curvature on the outside of the bezel it is a multiplier of the roundness of the screen corner
  - Default is 0 which gives a straight edge of the outside of the bezel

- **Outer Edge Position Y**
  - This moves the outer edge of the bezel and the frame up and down

- **Brightness**
  - Brightness of the bezel, the default is 30 so only 30% brightness

- **Highlight**
  - The highlight or shininess in the middle of the bezel

- **Opacity of Shadow from Bezel on Tube**
  - How much of a darkness from the bezel onto the illuminated screen
  - Only visible when the black ring around the screen is reduced so that the bezel is almost on top of the screen

**[ BEZEL & FRAME COLOR ]___________________________________________________________________________________________________**

- **Hue**
  - The hue or "color" of the bezel and frame E.G. Blue vs Orange
- **Saturation**
  - How saturated or strong the color is
- **Value/Brightness**
  - The brightness of the color, default is 10 which is 10%
- **Noise**
  - Noise or speckles in the color, default is 30

**[ FRAME ]_________________________________________________________________________________________________________**

- **Opacity**
  - Opacity of the frame default is 100 which means it is fully visible
- **Blend Mode** - Default is 1
  - **0 - Off**
  - **1 - Normal Blending**
  - **2 - Additive Blending** - Added on as added with a projector
  - **3 - Multiply Blending** - Applied by darkening what is underneath
- **Texture Overlay Opacity (Highlight)**
  - Opacity of the texture applied on top of base color of the frame
  - The default texture is a white highlight and so adds a highlight effect to the frame giving it a bit more dimension
- **Texture Overlay Blend Mode** - Default is 2 so it is additive
  - **0 - Off**
  - **1 - Normal Blending**
  - **2 - Additive Blending** - Added on as added with a projector
  - **3 - Multiply Blending** - Applied by darkening what is underneath
- **Inner Edge Thickness**
  - Thickness of the inner edge of the frame
- **Inner Corner Radius Scale**
  - Roundness of the inner corner, 
- **Thickness**
  - Base thickness of the frame
- **Thickness Scale X**
  - Adjusts the frame thickness of frame at the left and right
- **Outer Pos Y**
  - Shift the outside of the frame up and down which can make the top of the frame larger than the bottom or vice versa 
- **Outer Curvature Scale**
  - Curvature of the outside of the frame, at 100 it will match the curvature of the inside of the frame
- **Outer Corner Radius**
  - Roundness of the frame outer corner
- **Outer Edge Thickness**
  - Thickness of the shading on the outer edge
- **Outer Edge Shading**
  - Controls the darkness of the shading on the outer edge
- **Shadow Opacity**
  - Controls the darkness of the shadow under and around the frame
- **Shadow Width**
  - Controls how wide the shadow is around the frame

**[ REFLECTION ]________________________________________________________________________________________________________**

- **Blend Mode** - How the reflection is applied to the layer underneath Default is 2
  - **0 - Off** - The layer is not shown
  - **1 - Normal Blending**
  - **2 - Additive Blending** - Applied additively to brighten what's underneath
- **Mask** - Mask the reflection with the area inside the:
  - **0 - ALL** - Whole viewport
  - **1 - Screen** - Illuminated area of the tube
  - **2 - Tube**
  - **2 - Bezel and Inward** - Bezel and inward
  - **3 - Bezel**
  - **4 - Bezel +** - Bezel and outward
  - **5 - Frame**
  - **6 - Frame +** - Frame and outward
  - **7 - Background**  - Outside the frame
- **Global Amount**
  - Overall multiplier on the amount of reflection shown
- **Global Gamma Adjust**
  - Gamma adjustment on the reflection, allows you to reduce the amount of reflection in dark areas, or reduce contrast in the reflections
- **Direct Reflection**
  - Amount of the most detailed reflection shown
- **Diffused Reflection**
  - Amount of a very blurry and diffused reflection shown, helps blend between the main reflection to make a more natural effect
- **FullScreen Glow**
  - Amount of a very diffused reflection shown which mimics lighting from the overall brightness of the screen
- **FullScreen Glow Gamma**
  - Adjust the gamma of the full screen glow, this has the effect of controlling how bright the screen needs to be to see the fullscreen glow effect 
- **Bezel Inner Edge Amount**
  - How much reflection on the small inner edge right at the outside of the tube
- **Bezel Inner Edge Fullscreen Glow**
  - Same as above but a non-directional glow from all over the screen
- **Frame Inner Edge Amount**
- **Frame Inner Edge Sharpness**
  - How soft or sharp the reflection is at the inner edge of the frame

**[ REFLECTION FADE ]___________________________________________________________________________________________________**

- **Fade Amount**
  - At 100 the reflection fades out as it comes away from the screen, at 0 the reflection does not fade and is full strength everywhere  
- **Radial Fade Width**
  - The distance away from the sides of the screen where the reflection to completely fades out
- **Radial Fade Height**
  - The distance away from the top and bottom of the screen where the reflection to completely fades out
- **Lateral Outer Fade Position**
  - When the reflection fades out towards the corners, for example on the bottom bezel the reflection fades out towards the left and right. The position where the fade starts.
- **Lateral Outer Fade Distance**
  - For the lateral fade the distance for it to fade out
- **Viewport Vignette (For Glass Presets)**
  - Adds a vignette over the entire viewport to darken the areas as it goes towards the edges used to darken the reflection in the glass preset

**[ REFLECTION CORNER ]_____________________________________________________________________________________________________**

- **Corner Fade**
  - How much should the corner fade out
- **Corner Fade Distance**
  - The distance from the corner where the reflection fully fades out
- **Corner Inner Spread**
  - How much the inner corner reflection spreads out
- **Corner Outer Spread**
  - How much the outer corner reflection spreads out
- **Corner Rotation Offset Top**
  - Adjust the rotation of the highlight in the top corners
- **Corner Rotation Offset Bottom**
  - Adjust the rotation of the highlight in the bottom corners
- **Corner Spread Falloff**
  - Controls the profile of the falloff, small values make falloff faster near the center. 

**[ REFLECTION BLUR ]___________________________________________________________________________________________________**

- **Blur Samples - 0 for OFF**
  - Default is 12
- **Min Blur**
  - What is the least amount of blur in the reflection this is nearest the screen 
- **Max Blur**
  - The highest amount of blur in the reflection, this is the farther away from the screen

**[ REFLECTION NOISE ]______________________________________________________________________________________________________**

- **Noise Amount**
  - How much noise seen in the reflection, gives the effect of the scattered reflection of a slightly textured surface 
- **Noise Samples (0 for OFF)**
  - How many samples taken for the effect, more samples the smoother the effect, fewer samples makes the surface look more like it has little bumps in it
- **Sample Distance**
  - What is the farthest distance away from the point being drawn where the scattered sample come from

**[ GLASS BORDER ]______________________________________________________________________________________________________**

- **Glass Border ON (Glass Preset Only)**
  - Changes the appearance of the reflection to look like the glass effect

**[ REFLECT ONLY IMAGE LAYER ]__________________________________________________________________________________________________**

- **Opacity**
  - Opacity of the image to be applied
- **Blend Mode** - Default is Additive
  - **0 - Off** - Don't show the layer
  - **1 - Normal Blending**
  - **2 - Additive Blending** - Applied additively to brighten what's underneath
- **Aspect Ratio**
  - **0 - Full** - Use the viewport's aspect ratio
  - **1 - 16:9** - Show the image with a 16:9 aspect ratio
  - **2 - 9:16** - Show the image with a 16:9 aspect ratio
- **Mask Reflection to Bezel**
  - Limit the reflection to only appear inside the bezel area
  - Often used with the reflection only preset to show the reflection inside the bezel area shown in the image

**[ REFLECTION IS LAST PASS ]___________________________________________________________________________________________________**

- **Reflection is Last Pass**
  - Used for glass and reflection only presets
  - When this is on the final gamma correction is applied at the reflection pass

**[ NIGHT LIGHTING ]____________________________________________________________________**

- **Opacity**
  - How much of the night lighting darkening effect is applied
- **Mirror Horizontal**
  - Mirror the night lighting image
- **Saturation**
  - How saturated the night lighting is
- **Hue**
  - Shift the hue of the color of the image
- **Value**
  - How dark or bright the night lighting is
- **Dithering Noise Samples**
  - Reduces Banding

**[ IMAGE LAYERING ]________________________________________________________________________________________________________**

- **Static Layers Gamma Adjust**
  - Adjust the Gamma on all layers to brighten or darken all of them

**[ LAYER ORDER ]___________________________________________________________________________________________________**

Layer order adjusts the order in which the layers are composited or "layered" on top of each other, the index 0 is the bottom or base layer. If two layers are given the same index they fall back to being composited in the order seen here.

- **Background Image**
- **Viewport Vignette**
- **CRT Screen**
- **Bezel Image**
- **Bezel (Generated)**
- **Frame (Generated)**
- **Cabinet Glass Image**
- **Decal Image**
- **Reflection (Generated)**
- **LED Image**
- **Top Image**

**[ CUTOUT ]________________________________________________________________________________________________________**

Used to cut a rectangular area from the layers, for example cutting out the hole in the bezel art

- **Scale Mode**
  - Controls if this layer's scaling follows another layer 
  - **0 - Full** - Scale to the viewport 
  - **1 - Tube** - Follow the Tube Scaling
  - **2 - Bezel** - Follow the Bezel Scaling
  - **3 - Background** - Follow the Background Image Scaling
  - **4 - Bezel Image** - Follow the Bezel Image Scaling
  - **5 - Decal Image** - Follow the Decal Image Scaling
- **Scale**
  - Scales cutout in both directions
- **Scale X**
  - Scales cutout horizontally
- **Position Y**
  - Moves the cutout vertically
- **Corner Radius - Def 0**
  - Rounds the corner of the cutout

**[ MASK DEBUG ]________________________________________________________________________________________________________**

- **Mask** - Show the mask as a semi transparent color for the:
  
  - **-1 - Cut Out**
  - **0 - ALL** - Whole viewport
  - **1 - Screen** - Illuminated area of the tube
  - **2 - Tube**
  - **2 - Bezel and Inward** - Bezel and inward
  - **3 - Bezel**
  - **4 - Bezel +** - Bezel and outward
  - **5 - Frame**
  - **6 - Frame +** - Frame and outward
  - **7 - Background**  - Outside the frame
  
  

## ***Common Layer Parameters***

​	*In the multiple image layers there are many parameters which are repeated from layer to layer, their description is shown here*

- ***Opacity***

  - *Opacity multiplier of the layer being applied. 0 means we will not see the layer because it is fully transparent*

- ***Blend Mode*** *- How the reflection is applied to the layer underneath Default is Additive*

  - ***0 - Off*** *- The layer is not shown*
  - ***1 - Normal Blending***
  - ***2 - Additive Blending*** *- Applied additively to brighten what's underneath*

- ***Source Matte Color***

  - *Controls how the image's is interpreted based on the matte color used when the image was stored (what color the image is blended with in the transparent area).* 
  - *Used to remove white fringing on the edges around transparent areas.*
  - ***0 - Black***
    - *The color in the transparent area was black*. Technically this is called Premultiplied alpha. 
  - ***1 - White***
    - *The color in the transparent area was white, Use this if you see white fringing on the edges of the transparency where there should be none.*
  - ***2 - None***
    - *The image was not blended with any matte color, the only transparency info is in the alpha channel*

- **Mask** - Mask the layer with the area inside the:

  - ***0 - ALL*** *- Whole viewport*
  - ***1 - Screen*** *- Illuminated area of the tube*
  - ***2 - Tube***
  - ***2 - Bezel and Inward*** *- Bezel and inward*
  - ***3 - Bezel***
  - ***4 - Bezel +*** *- Bezel and outward*
  - ***5 - Frame***
  - ***6 - Frame +*** *- Frame and outward*
  - ***7 - Background***  *- Outside the frame*

- ***Cutout Mask***

  - ***0 - OFF*** *- Don't cut out any area of the layer*
  - ***1 - ON*** *- Make the area of the layer INSIDE the cutout mask transparent*
  - ***2 - Invert*** *- Make the area of the layer OUTSIDE the cutout mask transparent*

- ***Brightness***

  - *Adjust Brightness of the Layer, 100 is no change*

- ***Texture Aspect***

  - *Aspect Ratio of the texture file used for this layer*
  - ***0 - Full*** *- Use Viewport Aspect*
  - ***Explicit*** *- Use Explicit Aspect*
  - ***4:3*** *- Landscape*
  - ***3:4*** *- Portrait*
  - ***16:9*** *- Landscape*
  - ***9:16*** *- Portrait*

- **Explicit Texture Aspect**

  - *The Aspect ratio used when Texture Aspect is set to Explicit*

- ***Scale Mode***

  - *Controls if this layer follows another layer's scaling* 
  - ***Full / Fullscreen*** *- Scale to the viewport*
  - ***Tube*** *- Follow the Tube Scaling*
  - ***Bezel*** *- Follow the Bezel Scaling*
  - ***Background*** *- Follow the Background Image Scaling*
  - ***Bezel Image*** *- Follow the Bezel Image Scaling*
  - ***Decal Image*** *- Follow the Decal Image Scaling*
  - ***Top Extra Image*** *- Follow the Top Extra Image Scaling*

- **Keep Aspect**

  - *The Layer image should keep its original aspect ratio*
  - *E.G. If the scale mode was **Tube** and **Keep Aspect** was on regardless of the aspect of the tube the layer's image would stay the aspect ratio set in **Texture Aspect**. If Keep Aspect is off the texture would react to the tube's changes in horizontal aspect.* 
  - **0 - OFF**
  - **1 - ON**

- **Scale**

  - *Scales image layer equally in both directions*

- **Scale X**

  - *Scales image layer horizontally*

- **Position Y**

  - *Moves the image layer vertically*

    

**[ BACKGROUND LAYER ]______________________________________________________________________________________________________**

- **Opacity**
- **Blend Mode**
- **Source Matte Color**
- **Mask
- **Cutout Mask**
- **Brightness**
- **Apply NightLight & Static Gamma (0 for Backdrop)**
  - Allows Night Lighting and Static gamma to be turned off
  - Can be used to simulate a backdrop which is self illuminated
- **Texture Aspect**
- **Explicit Texture Aspect**
- **Scale Mode**
  - **0 - FullScreen**
  - **1 - Tube**
  - **2 - Bezel**
- **Keep Aspect**
- **Scale**
- **Scale X**
- **Position Y**
- **Mirror Wrap**
  - When ON the image is wrapped when we draw out of the texture bounds
  - **0 - OFF**
  - **1 - ON**

**[ VIEWPORT VIGNETTE LAYER ]___________________________________________________________________________________________________**

- **Opacity**
- **Mask**
- **Cutout Mask**
- **Scale Mode**
  - **0 - Full**
  - **1 - Background**
  - **2 - Tube**
  - **3 - Bezel**
  - **4 - Decal**
  - **5 - Top Image**
- **Scale**
- **Scale X**
- **Position Y**

**[ CRT SCREEN LAYER ]______________________________________________________________________________________________________**

- **Blend Mode**

**[ BEZEL IMAGE LAYER ]_____________________________________________________________________________________________________**

- **Opacity**
- **Hue Offset**
- **Saturation**
- **Brightness**
- **Blend Mode**
- **Source Matte Color**
- **Mask**
- **Cutout Mask**
- **Texture Aspect**
- **Explicit Texture Aspect**
- **Scale Mode**
  - **0 - FullScreen**
  - **1 - Tube**
  - **2 - Bezel**
  - **3 - Background**
- **Keep Aspect**
- **Scale**
- **Scale X**
- **Position Y**
- **Use Curvature**
  - If Use Curvature is ON then the layer image will follow the screen curvature

**[ CABINET OR CABINET GLASS LAYER ]________________________________________________________________________________________________**

- **Opacity**
- **Brightness**
- **Blend Mode**
- **Source Matte Color**
- **Mask**
- **Cutout Mask**
- **Texture Aspect**
- **Explicit Texture Aspect**
- **Scale Mode**
  - **0 - FullScreen**
  - **1 - Tube**
  - **2 - Bezel**
  - **3 - Background**
  - **4 - Top Image**
- **Keep Aspect**
- **Scale**
- **Scale X**
- **Position Y**

**[ DECAL LAYER ]___________________________________________________________________________________________________**

- **Opacity**
- **Blend Mode**
- **Source Matte Color**
- **Mask**
- **Cutout Mask**
- **Texture Aspect**
- **Explicit Texture Aspect**
- **Scale Mode**
  - **0 - Full Screen**
  - **1 - Tube**
  - **2 - Bezel**
  - **3 - Background**
  - **4 - Bezel Image**
- **Scale Keep Aspect**
- **Scale**
- **Scale X**
- **Position Y**

**[ LED LAYER ]_________________________________________________________________________________________________________**

- **Opacity**
- **Blend Mode**
- **Source Matte Color**
- **Mask**
- **Cutout Mask**
- **Texture Aspect**
- **Explicit Texture Aspect**
- **Scale Mode**
  - **0 - Full Screen**
  - **1 - Tube**
  - **2 - Bezel**
  - **3 - Background**
  - **4 - Bezel Image**
  - **5 - Decal Image**
- **Scale Keep Aspect**
- **Scale**
- **Scale X**
- **Position Y**

**[ TOP EXTRA LAYER ]___________________________________________________________________________________________________**

- **Opacity**
- **Blend Mode**
- **Source Matte Color**
- **Mask**
- **Cutout Mask**
- **Texture Aspect**
- **Explicit Texture Aspect**
- **Scale Mode**
  - **0 - Full Screen**
  - **1 - Tube**
  - **2 - Bezel**
  - **3 - Background**
  - **4 - Bezel Image**
  - **5 - Decal Image**
- **Scale Keep Aspect**
- **Scale**
- **Scale X**
- **Position Y**
- **Mirror Wrap**
  - When drawing past the edges of the texture use mirror wrapping
