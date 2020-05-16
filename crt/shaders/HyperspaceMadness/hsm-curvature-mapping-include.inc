
// Import Screen Scale Functions and parameters
#include "hsm-screen-scale-and-bezel-with-globals.inc"

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
   
   // Coordinate in the space which includes the entire glass area including the illuminated screen and black line around it 
   tubeCoord = HMSS_GetTubeVTexCoord(vTexCoord);
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in vec2 screenCoord;
layout(location = 2) in vec2 tubeCoord;
layout(location = 0) out vec4 FragColor;

void main()
{
	float screen_aspect = HMSS_GetScreenAspect();
	
	vec2 tube_curved_coord = HMSS_GetCurvedCoord(tubeCoord, global.hmss_tube_black_edge_curvature_scale);

	vec2 edge_mask_coord = (tube_curved_coord - 0.5) * (1 - (global.hmbz_bezel_inner_edge_thickness / 100 / vec2(screen_aspect, 1))) + 0.5;
	float edge_sharpness = 0.9;

	// If this is used in the glass preset adjust the smoothness of the edge of the glass 
	#ifdef GLASS_PRESET
		edge_sharpness = HMBZ_GLASS_INNER_EDGE_SOFTNESS;
	#endif

	float outside_tube_mask = 1 - HMSS_GetCornerMask(tube_curved_coord, global.hmbz_bezel_inner_corner_radius_scale * global.hmss_screen_corner_radius, 0.9);

	float edge_mask =  HMSS_GetCornerMask(edge_mask_coord, global.hmbz_bezel_inner_corner_radius_scale * global.hmss_screen_corner_radius, edge_sharpness);

	FragColor = vec4(tube_curved_coord.x, tube_curved_coord.y, outside_tube_mask, edge_mask);
}