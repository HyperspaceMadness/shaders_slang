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

vec2 HSM_GetFrameScale(vec2 screen_scale, float screen_aspect)
{
	vec2 outer_bezel_scale = HSM_GetOuterBezelScale(screen_scale, screen_aspect);
	vec2 black_edge_scale_offset = HSM_GetTubeScale(screen_scale) / screen_scale;
	vec2 frame_scale = screen_scale * black_edge_scale_offset * outer_bezel_scale;
	return frame_scale;
}

float HSM_GetBezelCoords(vec2 screen_coord, vec2 screen_scale, float screen_aspect, inout vec2 bezel_outside_coord, inout vec2 frame_outside_coord)
{
	float output_aspect = global.OutputSize.x / global.OutputSize.y;

	vec2 frame_pos_offset = vec2(0, HSM_BZL_OUTER_POSITION_Y);

	vec2 outer_bezel_scale = HSM_GetOuterBezelScale(screen_scale, screen_aspect);

	bezel_outside_coord = screen_coord + frame_pos_offset;

	// Only run curved coordinates if requested or we are using tilt
	if ((HSM_CURVATURE_MODE > 0) && ((HSM_CURVATURE_3D_TILT_ANGLE_X != 0) || (HSM_CURVATURE_3D_TILT_ANGLE_Y != 0)))
		bezel_outside_coord = HSM_GetCurvedCoord(bezel_outside_coord, 0, outer_bezel_scale.x * output_aspect / outer_bezel_scale.y);

	vec2 black_edge_scale_offset = HSM_GetTubeScale(screen_scale) / screen_scale;

	bezel_outside_coord = HSM_GetInverseScaledCoord(bezel_outside_coord, black_edge_scale_offset * outer_bezel_scale) + vec2(0, HSM_BZL_OUTER_POSITION_Y);
	frame_outside_coord = (bezel_outside_coord + 
							vec2(0, HSM_FRM_OUTER_POS_Y) - 0.5) / 
							vec2((HSM_FRM_THICKNESS * HSM_FRM_THICKNESS_SCALE_X) / 
							(screen_scale.x / screen_scale.y * output_aspect) + 1, 
							HSM_FRM_THICKNESS + 1) + 0.5;

	if (HSM_BZL_OUTER_CURVATURE_SCALE > 0)
	{
		vec2 screen_scale_for_tube = screen_scale;

		bezel_outside_coord = HSM_GetTubeCurvedCoord(bezel_outside_coord, HSM_BZL_OUTER_CURVATURE_SCALE, screen_scale_for_tube, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y, 0);

		if ( HSM_FRM_OUTER_CURVATURE_SCALE > 0)
			frame_outside_coord = HSM_GetTubeCurvedCoord(frame_outside_coord, HSM_BZL_OUTER_CURVATURE_SCALE * HSM_FRM_OUTER_CURVATURE_SCALE, screen_scale_for_tube, outer_bezel_scale.x * global.OutputSize.x / global.OutputSize.y / outer_bezel_scale.y, 0);
	}

	return 0;
}