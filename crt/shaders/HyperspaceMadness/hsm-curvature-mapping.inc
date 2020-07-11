
// Import Screen Scale Functions and parameters
#include "hsm-screen-scale-and-bezel-with-globals.inc"

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
	vec2 screen_coord = SCREEN_COORD;
	vec2 screen_scale = SCREEN_SCALE;
	float flip_tilt = 0;

	#ifdef HSM_SPLIT_SCREEN_PRESET
		float split_pos_1 = 0;
		float split_pos_2 = 0;
		float split_dist = 0;
		float split_axis_is_horizontal = 0;
		HSS_GetSplitInfo(split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

		float coord_1D = HSS_GetSplitAxisCoord1D(screen_coord, split_axis_is_horizontal);
		
		// check if we are on the first screen and therfore need to flip the tilt
		flip_tilt = HHLP_IsUnderValue(coord_1D, 0.5);

		if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
		{
			// Get the screen scale for each sub-screen, this helps calculate the correct black edge offset
			screen_scale = split_axis_is_horizontal * vec2(split_pos_1 * SCREEN_SCALE.x, SCREEN_SCALE.y) + (1 - split_axis_is_horizontal) * vec2(SCREEN_SCALE.x, (1 - split_pos_2) * SCREEN_SCALE.y);

			// If this was on the first screen then flip it so we get the opposite tilt
			// screen_coord = flip_tilt * HSS_GetFlippedCoordOnSplitAxis(screen_coord, SCREEN_ASPECT) + (1 - flip_tilt) * screen_coord;
		}
	#endif

	vec2 black_edge_scale_offset = HSS_GetTubeScale(screen_scale) / screen_scale;

	// Get the tube coord with the black edge added
	// vec2 tube_coord = HSS_GetInverseScaledCoord(screen_coord, black_edge_scale_offset);

	// Get the curved coordinate, setting allow_split_screen to off (0)
	vec2 tube_curved_coord = HSS_GetCurvedCoord(screen_coord, HSS_TUBE_CURVATURE_SCALE, SCREEN_ASPECT);

	#ifdef HSM_SPLIT_SCREEN_PRESET
		if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
		{
			// Take the sub-screen area and re-map it to 0-1
			tube_curved_coord = HSS_Get0To1CoordFromSplitArea(tube_curved_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

			// If this was flipped then flip it back
			// tube_curved_coord = flip_tilt * HSS_GetFlippedCoordOnSplitAxis(tube_curved_coord, SCREEN_ASPECT) + (1 - flip_tilt) * tube_curved_coord;
		}
	#endif

	tube_curved_coord = HSS_GetInverseScaledCoord(tube_curved_coord, black_edge_scale_offset);

	// #ifdef HSM_SPLIT_SCREEN_PRESET
	// if (HSS_SPLIT_SCREEN_CENTER_FILL_MODE == 1)
	// 	{
	// 		float coord_1D = HSS_GetSplitAxisCoord1D(screen_coord, split_axis_is_horizontal);
			
	// 		float split_pos_1 = 0;
	// 		float split_pos_2 = 0;
	// 		float split_dist = 0;
	// 		HSS_GetSplitInfo(split_pos_1, split_pos_2, split_dist);
	// 		tube_curved_coord = HSS_GetSplitAreaCoordFrom0To1(screen_coord, tube_curved_coord, split_pos_1, split_pos_2, split_dist);
	// 	}
	// #endif

	vec2 edge_mask_coord = (tube_curved_coord - 0.5) * (1 - (HBZ_BEZEL_INNER_EDGE_THICKNESS / 100 / vec2(SCREEN_ASPECT, 1))) + 0.5;
	float edge_sharpness = 0.99;

	// If this is used in the glass preset adjust the smoothness of the edge of the glass 
	#ifdef GLASS_PRESET
		edge_sharpness = HBZ_GLASS_INNER_EDGE_SOFTNESS;
	#endif

	float outside_tube_mask = 1 - HSS_GetCornerMask(tube_curved_coord, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, 0.99);

	float edge_mask =  HSS_GetCornerMask(edge_mask_coord, SCREEN_ASPECT, HBZ_BEZEL_INNER_CORNER_RADIUS_SCALE * HSS_SCREENFX_CORNER_RADIUS, edge_sharpness);

	FragColor = vec4(tube_curved_coord.x, tube_curved_coord.y, outside_tube_mask, edge_mask);
}