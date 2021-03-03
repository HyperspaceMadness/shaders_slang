/*   
hsm-screen-scale-params-functions

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
*/

vec2 HSM_GetOuterBezelScale(vec2 screen_scale, float screen_aspect)
{
	float screen_scale_diagonal = sqrt(screen_scale.y * screen_scale.y + (screen_scale.y * screen_aspect) * (screen_scale.y * screen_aspect));
	vec2 outer_bezel_scale = vec2(HSM_BZL_WIDTH / screen_aspect + 1, HSM_BZL_HEIGHT + 1);
	outer_bezel_scale = (outer_bezel_scale - 1) * screen_scale_diagonal + 1;
	return outer_bezel_scale;
}

vec2 HSM_GetFrameScale(vec2 screen_scale, vec2 tube_scale, float screen_aspect)
{
	vec2 outer_bezel_scale = HSM_GetOuterBezelScale(screen_scale, screen_aspect);
	vec2 black_edge_scale_offset = tube_scale / screen_scale;
	vec2 frame_scale = screen_scale * black_edge_scale_offset * outer_bezel_scale;
	return frame_scale;
}

float HSM_GetBezelCoords(vec2 screen_coord, vec2 screen_scale, vec2 tube_scale, float screen_aspect, inout vec2 bezel_outside_coord, inout vec2 frame_outside_coord)
{
	float output_aspect = global.OutputSize.x / global.OutputSize.y;

	vec2 frame_pos_offset = vec2(0, HSM_BZL_OUTER_POSITION_Y);

	vec2 outer_bezel_scale = HSM_GetOuterBezelScale(screen_scale, screen_aspect);

	bezel_outside_coord = screen_coord + frame_pos_offset;

	// Only run curved coordinates if requested or we are using tilt
	if ((HSM_CURVATURE_MODE > 0) && ((HSM_CURVATURE_3D_TILT_ANGLE_X != 0) || (HSM_CURVATURE_3D_TILT_ANGLE_Y != 0)))
		bezel_outside_coord = HSM_GetCurvedCoord(bezel_outside_coord, 0, outer_bezel_scale.x * output_aspect / outer_bezel_scale.y);

	vec2 black_edge_scale_offset = tube_scale / screen_scale;

	bezel_outside_coord = HSM_GetInverseScaledCoord(bezel_outside_coord, black_edge_scale_offset * outer_bezel_scale) + vec2(0, HSM_BZL_OUTER_POSITION_Y);
	frame_outside_coord = (bezel_outside_coord + 
							vec2(0, HSM_FRM_OUTER_POS_Y) - 0.5) / 
							vec2((HSM_FRM_THICKNESS * HSM_FRM_THICKNESS_SCALE_X) / 
							(screen_scale.x / screen_scale.y * output_aspect) + 1, 
							HSM_FRM_THICKNESS + 1) + 0.5;

	if (HSM_BZL_OUTER_CURVATURE_SCALE > 0)
	{
		bezel_outside_coord = HSM_GetTubeCurvedCoord(bezel_outside_coord, HSM_BZL_OUTER_CURVATURE_SCALE, screen_scale, tube_scale, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y, 0);

		if ( HSM_FRM_OUTER_CURVATURE_SCALE > 0)
			frame_outside_coord = HSM_GetTubeCurvedCoord(frame_outside_coord, HSM_BZL_OUTER_CURVATURE_SCALE * HSM_FRM_OUTER_CURVATURE_SCALE, screen_scale, tube_scale, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y, 0);
	}

	return 0;
}

// Returns curved coordinates for the coordinate supplied
// Cached coordinate comes from the mapping pass texture supplied
// x & y are the curved tube coordinates
vec4 HSM_GetCachedCurvedValues(vec2 in_coord, inout vec2 out_curved_coord, inout float outside_tube_mask, inout float edge_mask)
{
	// vec4 texture_sample = texture(in_mapping_pass, in_coord);
	// out_curved_coord = texture_sample.xy;
	// outside_tube_mask = texture_sample.z;
	// edge_mask = texture_sample.w;

	vec4 texture_sample = vec4(0);
	out_curved_coord = HSM_GetTubeCurvedCoord(SCREEN_COORD, 1, SCREEN_SCALE, TUBE_SCALE, SCREEN_ASPECT, 1);
	vec2 edge_mask_coord = (out_curved_coord - 0.5) * (1 - (HSM_BZL_INNER_EDGE_THICKNESS / vec2(SCREEN_ASPECT, 1))) + 0.5;
	outside_tube_mask = 1 - HSM_GetCornerMask(out_curved_coord, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, 0.99);
	edge_mask =  HSM_GetCornerMask(edge_mask_coord, SCREEN_ASPECT, HSM_BZL_INNER_CORNER_RADIUS_SCALE * HSM_SCREEN_CORNER_RADIUS, HSM_BZL_INNER_EDGE_SHARPNESS);

	return texture_sample;
}