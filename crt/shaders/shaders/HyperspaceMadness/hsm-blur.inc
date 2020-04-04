
//#define ShowPlacementGuide

// Import Screen Scale Functions and global structure
#include "hsm-mega-screen-scale.inc"

layout(push_constant) uniform Push
{
	float hbl_blur_num_samples;
	float hbl_blur_min;
	float hbl_blur_max;
} params;

// Above variables are referenced in this include
#include "hsm-mega-bezel-params.inc"

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out vec2 tubeScale;

void main()
{
	gl_Position = global.MVP * Position;
    vTexCoord = TexCoord * 1.0001;

	tubeScale = HMSS_GetTubeScale();
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in vec2 tubeScale;
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D Source;
layout(set = 0, binding = 3) uniform sampler2D BR_MirrorLowResPass;

#define COMPAT_TEXTURE(c,d) texture(c,d)

float clamp_0_1(float in_value)
{
	return clamp(in_value, 0, 1);
}

void main()
{
	if (params.hbl_blur_num_samples > 0)
	{
		vec2 outermap_scale = vec2(1, 1) * (1.3 + 1);

		// Get -0.5 to 0.5 coordinates, the center of the screen is 0,0
		float outermap_range = 0.5 - 0.5 / outermap_scale.y;

		vec2 tube_coord = HMSS_GetInverseScaledCoord(vTexCoord, tubeScale);

		vec2 outermap_coord = HMSS_GetInverseScaledCoord(tube_coord, vec2(outermap_scale.x, outermap_scale.y));
		vec2 outermap_coord_ctr = outermap_coord - vec2(0.5, 0.5);

		// Get -0.5 to 0.5 Coordinates 0,0 is the center of the 0-1 space
		vec2 outermap_coord_warped = HMSS_GetCurvedCoord(outermap_coord, 1 * 6);
		vec2 outermap_warped_coord_ctr = outermap_coord_warped - vec2(0.5, 0.5);

		// Multiply by a factor driven by how much curvature is used, because the screen shrinks as more curvature is used
		vec2 curvature_long_short = 1 * HMSS_GetLongShortAxisCurvatureValues();
		vec2 curvature_scale_offset = HMSS_GetScreenAspectRatio() < 1.0 ? 1 / (1 + vec2(4.4 * curvature_long_short.y, 4.7 * curvature_long_short.x)) : 1 / (1 + vec2(4.7 * curvature_long_short.x, 4.4 * curvature_long_short.y));

		vec2 outermap_coord_ctr_warped_clipped_to_screen = clamp(outermap_warped_coord_ctr, -0.5 / outermap_scale * curvature_scale_offset, 0.5 / outermap_scale * curvature_scale_offset);
		vec2 outermap_warped_outside_screen_vector = outermap_warped_coord_ctr - outermap_coord_ctr_warped_clipped_to_screen;

		vec2 outermap_coord_ctr_clipped_to_screen = clamp(outermap_coord_ctr, -0.5 / outermap_scale, 0.5 / outermap_scale);	
		vec2 coord_ctr_inside_outermap_range = outermap_coord_ctr - outermap_coord_ctr_clipped_to_screen;	
		
		vec2 outermap_screen_size_from_center = vec2((-0.5 / outermap_scale.x) * curvature_scale_offset.x, (0.5 / outermap_scale.y) * curvature_scale_offset.y);
		float outside_ratio = clamp_0_1(length(coord_ctr_inside_outermap_range) / outermap_range);
		float outside_ratio_warped = clamp_0_1(length(outermap_warped_outside_screen_vector) / outermap_range);

		float hbl_sharpness_falloff_distance = 7;
		float blur_ratio = clamp_0_1(outside_ratio_warped / (hbl_sharpness_falloff_distance / 100));
		float blur_midpoint = 0.12;
		float hbl_sharpness_falloff_speed = 1;
		blur_ratio = HHLP_QuadraticBezier (clamp_0_1(blur_ratio - blur_midpoint), vec2(0.05, hbl_sharpness_falloff_speed));
		blur_ratio = params.hbl_blur_min + blur_ratio * (params.hbl_blur_max - params.hbl_blur_min);

		vec3 col = vec3(0.0);
		
		#ifdef VERTICAL_BLUR
			float dx = 0;
			float dy = global.SourceSize.w;
		#else
			float dx = global.SourceSize.z;
			float dy = 0;
		#endif

		// This bizarre bit is to try to take the non linear nature of the blur falloff value and make it into a more linear behavior
		float first_blur_ratio_blend_point = 0.2;
		float last_blur_ratio_blend_point = 0.6;

		float max_blur_range = 7;
		float mid_blur_range = 7;
		float min_blur_range = 10;
		float blur_falloff = (
								0.5 +
								max_blur_range * smoothstep(1, last_blur_ratio_blend_point, blur_ratio) +
								min_blur_range * smoothstep(last_blur_ratio_blend_point, 0, blur_ratio)
								) / 100;


		// Stuff for debugging the mapping space
		#ifdef ShowPlacementGuide
			float placement_guide_red_alpha = 0;
			float placement_guide_green_alpha = 0;
			float placement_guide_blue_alpha = 0;

			//placement_guide_red_alpha += HHLP_GetMaskCenteredOnValue(blur_falloff, 0.01, 0.001);
		#endif

		float k_total = 0.;
		for (float i = -params.hbl_blur_num_samples; i <= params.hbl_blur_num_samples; i++)
		{
			float k = exp(-blur_falloff * (i) * (i));
			k_total += k;
			
			vec4 sampled_color = COMPAT_TEXTURE(Source, vTexCoord + vec2(float(i) * dx, float(i) * dy));
			
			col += k * sampled_color.rgb;
		}
		vec4 blurred_color = vec4(col / k_total, 1.0);
		float blend_with_unblurred = smoothstep(-0.3, 0.3, HHLP_QuadraticBezier(blur_ratio, vec2(0.5, 0.5)));
		
		vec4 unblurred_color = COMPAT_TEXTURE(BR_MirrorLowResPass, vTexCoord);
		FragColor = mix(unblurred_color, blurred_color, blend_with_unblurred);

		// Add the color for the debug Stuff
		#ifdef ShowPlacementGuide
			FragColor += vec4(1, 0, 0, 1) * placement_guide_red_alpha;
			FragColor += vec4(0, 1, 0, 1) * placement_guide_green_alpha;
			FragColor += vec4(0, 0, 1, 1) * placement_guide_blue_alpha;
			FragColor = clamp(FragColor - HHLP_GetMaskCenteredOnValue(blur_ratio, 0.995, 0.002), 0, 1);
			FragColor = clamp(FragColor - HHLP_GetMaskCenteredOnValue(blur_ratio, 0.5, 0.002), 0, 1);
		#endif
	}
	else
	{
		FragColor = COMPAT_TEXTURE(Source, vTexCoord);
	}
}