#version 450

// Import so all the mega bexel parameters are the first in the parameter list
#include "hsm-mega-screen-scale.inc"

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
   vec2 curved_coord = HMSS_GetCurvedCoord(HMSS_GetTubeVTexCoord(vTexCoord), 1);
   float mask = HMSS_GetCornerMask(curved_coord, 1, 0.9);
   mask *= mask * mask * mask;
   FragColor = vec4(mask);
}