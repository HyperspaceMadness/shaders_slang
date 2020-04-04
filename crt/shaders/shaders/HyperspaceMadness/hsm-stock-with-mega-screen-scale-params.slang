#version 450

// Import so all the mega bexel parameters are the first in the parameter list
#include "hsm-mega-screen-scale.inc"
#include "hsm-text.inc"



#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D Source;

void main()
{
   FragColor = vec4(texture(Source, vTexCoord).rgb, 1);
   
   // Draw text to show resolutions
   if (global.hmss_screen_scale_debug == 1)
   {
      FragColor = mix(FragColor, vec4(0, 0, 0, 1), GetTextMask(vTexCoord + 2 * vec2(1/global.OutputSize.x, 0), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
      FragColor = mix(FragColor, vec4(0, 0, 0, 1), GetTextMask(vTexCoord - 2 * vec2(1/global.OutputSize.x, 0), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
      FragColor = mix(FragColor, vec4(0, 0, 0, 1), GetTextMask(vTexCoord + 1 * vec2(0, 1/global.OutputSize.y), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
      FragColor = mix(FragColor, vec4(0, 0, 0, 1), GetTextMask(vTexCoord - 1 * vec2(0, 1/global.OutputSize.y), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
      FragColor = mix(FragColor, vec4(1, 1, 0, 1), GetTextMask(vTexCoord,                                      global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
   }
}