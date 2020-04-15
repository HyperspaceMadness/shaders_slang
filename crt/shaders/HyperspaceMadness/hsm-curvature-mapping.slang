#version 450

// Import so all the mega bexel parameters are the first in the parameter list
#include "hsm-mega-screen-scale.inc"

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out vec2 screenCoord;
layout(location = 2) out vec2 tubeCoord;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord * 1.0001;
   
   // Coordinate with position offset
   vTexCoord = HMSS_GetCoordWithPositionOffset(vTexCoord);

   // Coordinate in the space which includes the entire glass area including the illuminated screen and black line around it 
   screenCoord = HMSS_GetInverseScaledCoord(vTexCoord, HMSS_GetScreenScale());

   // Coordinate in the space which includes the entire glass area including the illuminated screen and black line around it 
   tubeCoord = HMSS_GetInverseScaledCoord(vTexCoord, HMSS_GetTubeScale());
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in vec2 screenCoord;
layout(location = 2) in vec2 tubeCoord;
layout(location = 0) out vec4 FragColor;

void main()
{
   vec2 screen_curved_coord = HMSS_GetCurvedCoord(screenCoord, 1);
   vec2 tube_curved_coord = HMSS_GetCurvedCoord(tubeCoord, global.hmss_tube_black_edge_curvature_scale);
   FragColor = vec4(screen_curved_coord.x, screen_curved_coord.y, tube_curved_coord.x, tube_curved_coord.y);
}