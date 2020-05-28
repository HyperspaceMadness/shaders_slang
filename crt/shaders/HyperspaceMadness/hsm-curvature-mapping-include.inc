
// Import Screen Scale Functions and parameters
#include "hsm-screen-scale-and-bezel-with-globals.inc"

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out float SCREEN_ASPECT;
layout(location = 2) out vec2 TUBE_COORD;

void main()
{
	gl_Position = global.MVP * Position;
	vTexCoord = TexCoord * 1.0001;

	// Coordinate in the space which includes the entire glass area including the illuminated screen and black line around it 
	SCREEN_ASPECT = HSS_GetScreenAspect();
	vec2 screen_scale = HSS_GetScreenScale(SCREEN_ASPECT);
	vec2 tube_scale = HSS_GetTubeScale(screen_scale);
	TUBE_COORD = HSS_GetTubeVTexCoord(vTexCoord, tube_scale);
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in float SCREEN_ASPECT;
layout(location = 2) in vec2 TUBE_COORD;

layout(location = 0) out vec4 FragColor;

void main()
{
	vec2 tube_curved_coord = HSS_GetCurvedCoord(TUBE_COORD, HSS_TUBE_BLACK_CURVATURE_SCALE, SCREEN_ASPECT);

	vec2 edge_mask_coord = (tube_curved_coord - 0.5) * (1 - (HBZ_BEZEL_INNER_EDGE_THICKNESS / 100 / vec2(SCREEN_ASPECT, 1))) + 0.5;
	float edge_sharpness = 0.9;

	// If this is used in the glass preset adjust the smoothness of the edge of the glass 
	#ifdef GLASS_PRESET
		edge_sharpness = HBZ_GLASS_INNER_EDGE_SOFTNESS;
	#endif

	float outside_tube_mask = 1 - HSS_GetCornerMask(tube_curved_coord, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 0.9);

	float edge_mask =  HSS_GetCornerMask(edge_mask_coord, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, edge_sharpness);

	FragColor = vec4(tube_curved_coord.x, tube_curved_coord.y, outside_tube_mask, edge_mask);
}