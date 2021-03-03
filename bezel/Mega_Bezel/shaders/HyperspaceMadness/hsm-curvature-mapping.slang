#version 450

// Import Screen Scale Functions and parameters
#include "hsm-globals-and-reflection-params.inc"

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 0) out vec2 vTexCoord;

void main()
{
	gl_Position = global.MVP * Position;
	vTexCoord = TexCoord * 1.0001;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;

layout(location = 0) out vec4 FragColor;

layout(set = 0, binding = 1) uniform sampler2D InfoCachePass;

void main()
{
	// HSM Added
	float average_luma = 0;
	float SCREEN_ASPECT = 1;
	vec2 SCREEN_SCALE = vec2(0.5);
	vec2 SCREEN_POS = vec2(0.5);
	vec2 TUBE_SCALE = vec2(0.5);
	HSM_GetCachedScreenValues(vTexCoord, InfoCachePass, SCREEN_ASPECT, SCREEN_SCALE, TUBE_SCALE, SCREEN_POS, average_luma);
	vec2 SCREEN_COORD = HSM_GetVTexCoordWithArgs(vTexCoord, SCREEN_SCALE, SCREEN_POS);

	vec2 tube_curved_coord = HSM_GetTubeCurvedCoord(SCREEN_COORD, 1, SCREEN_SCALE, TUBE_SCALE, SCREEN_ASPECT, 1);

	// float flip_tilt = 0;

	// #ifdef HSM_SPLIT_SCREEN_PRESET
	// 	float split_pos_1 = 0;
	// 	float split_pos_2 = 0;
	// 	float split_dist = 0;
	// 	float split_axis_is_horizontal = 0;
	// 	HSM_GetSplitInfo(split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

	// 	float coord_1D = HSM_GetSplitAxisCoord1D(screen_coord, split_axis_is_horizontal);
		
	// 	// check if we are on the first screen and therfore need to flip the tilt
	// 	flip_tilt = HHLP_IsUnderValue(coord_1D, 0.5);

	// 	if (HSM_SPLITSCREEN_CENTER_FILL_MODE == 1)
	// 	{
	// 		// Get the screen scale for each sub-screen, this helps calculate the correct black edge offset
	// 		screen_scale = split_axis_is_horizontal * vec2(split_pos_1 * SCREEN_SCALE.x, SCREEN_SCALE.y) + (1 - split_axis_is_horizontal) * vec2(SCREEN_SCALE.x, (1 - split_pos_2) * SCREEN_SCALE.y);

	// 		// If this was on the first screen then flip it so we get the opposite tilt
	// 		// screen_coord = flip_tilt * HSM_GetFlippedCoordOnSplitAxis(screen_coord, SCREEN_ASPECT) + (1 - flip_tilt) * screen_coord;
	// 	}
	// #endif

	// vec2 black_edge_scale_offset = HSM_GetTubeScale(screen_scale) / screen_scale;

	// // Get the tube coord with the black edge added
	// // vec2 tube_coord = HSM_GetInverseScaledCoord(screen_coord, black_edge_scale_offset);

	// // Get the curved coordinate, setting allow_split_screen to off (0)
	// vec2 tube_curved_coord = HSM_GetCurvedCoord(screen_coord, HSM_BZL_INNER_CURVATURE_SCALE, SCREEN_ASPECT);

	// #ifdef HSM_SPLIT_SCREEN_PRESET
	// 	if (HSM_SPLITSCREEN_CENTER_FILL_MODE == 1)
	// 	{
	// 		// Take the sub-screen area and re-map it to 0-1
	// 		tube_curved_coord = HSM_Get0To1CoordFromSplitArea(tube_curved_coord, split_pos_1, split_pos_2, split_dist, split_axis_is_horizontal);

	// 		// If this was flipped then flip it back
	// 		// tube_curved_coord = flip_tilt * HSM_GetFlippedCoordOnSplitAxis(tube_curved_coord, SCREEN_ASPECT) + (1 - flip_tilt) * tube_curved_coord;
	// 	}
	// #endif

	// tube_curved_coord = HSM_GetInverseScaledCoord(tube_curved_coord, black_edge_scale_offset);



	// #ifdef HSM_SPLIT_SCREEN_PRESET
	// if (HSM_SPLITSCREEN_CENTER_FILL_MODE == 1)
	// 	{
	// 		float coord_1D = HSM_GetSplitAxisCoord1D(screen_coord, split_axis_is_horizontal);
			
	// 		float split_pos_1 = 0;
	// 		float split_pos_2 = 0;
	// 		float split_dist = 0;
	// 		HSM_GetSplitInfo(split_pos_1, split_pos_2, split_dist);
	// 		tube_curved_coord = HSM_GetSplitAreaCoordFrom0To1(screen_coord, tube_curved_coord, split_pos_1, split_pos_2, split_dist);
	// 	}
	// #endif

	vec2 edge_mask_coord = (tube_curved_coord - 0.5) * (1 - (HSM_BZL_INNER_EDGE_THICKNESS / vec2(SCREEN_ASPECT, 1))) + 0.5;

	float outside_tube_mask = 1 - HSM_GetCornerMask(tube_curved_coord, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0.99);

	float edge_mask =  HSM_GetCornerMask(edge_mask_coord, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, HSM_BZL_INNER_EDGE_SHARPNESS);

	FragColor = vec4(tube_curved_coord.x, tube_curved_coord.y, outside_tube_mask, edge_mask);
}