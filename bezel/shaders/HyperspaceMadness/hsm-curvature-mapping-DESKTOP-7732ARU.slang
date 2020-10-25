#version 450


// Import Screen Scale Functions and parameters
#include "hsm-globals-and-all-params.inc"

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out float SCREEN_ASPECT;
layout(location = 2) out vec2 SCREEN_SCALE;
layout(location = 3) out vec2 SCREEN_COORD;

void main()
{
	gl_Position = global.MVP * Position;
	vTexCoord = TexCoord * 1.0001;

	// Coordinate in the space which includes the entire glass area including the illuminated screen and black line around it 
	SCREEN_ASPECT = HSS_GetScreenAspect();
	SCREEN_SCALE = HSS_GetScreenScale(SCREEN_ASPECT);
	SCREEN_COORD = HSS_GetScreenVTexCoord(vTexCoord, SCREEN_SCALE);
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in float SCREEN_ASPECT;
layout(location = 2) in vec2 SCREEN_SCALE;
layout(location = 3) in vec2 SCREEN_COORD;

layout(location = 0) out vec4 FragColor;

void main()
{
	vec2 tube_curved_coord = HSS_GetTubeCurvedCoord(SCREEN_COORD, SCREEN_SCALE, SCREEN_ASPECT);

	vec2 edge_mask_coord = (tube_curved_coord - 0.5) * (1 - (H_BZL_INNER_EDGE_THICKNESS / vec2(SCREEN_ASPECT, 1))) + 0.5;
	float edge_sharpness = 0.99;

	// If this is used in the glass preset adjust the smoothness of the edge of the glass 
	if (HGL_GLASSBORDER_ON == 1)
		edge_sharpness = H_GLASS_INNER_EDGE_SOFTNESS;

	float outside_tube_mask = 1 - HSS_GetCornerMask(tube_curved_coord, SCREEN_ASPECT, H_BZL_INNER_CORNER_RADIUS_SCALE * H_SCREEN_CORNER_RADIUS, 0.99);

	float edge_mask =  HSS_GetCornerMask(edge_mask_coord, SCREEN_ASPECT, H_BZL_INNER_CORNER_RADIUS_SCALE * H_SCREEN_CORNER_RADIUS, edge_sharpness);

	FragColor = vec4(tube_curved_coord.x, tube_curved_coord.y, outside_tube_mask, edge_mask);
}