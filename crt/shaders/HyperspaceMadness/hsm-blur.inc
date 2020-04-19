
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

void main()
{
	gl_Position = global.MVP * Position;
    vTexCoord = TexCoord * 1.0001;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D Source;
layout(set = 0, binding = 3) uniform sampler2D BR_MirrorLowResPass;
layout(set = 0, binding = 4) uniform sampler2D BR_MappingPass;

#define COMPAT_TEXTURE(c,d) texture(c,d)

float clamp_0_1(float in_value)
{
	return clamp(in_value, 0, 1);
}

void main()
{
	if (params.hbl_blur_num_samples > 0)
	{
		vec2 tube_coord_warped = HMSS_GetCachedCurvedTubeCoord(BR_MappingPass, vTexCoord.xy);

		// General variables related to the main masks referenced later
		float screen_aspect;
		vec2 outermap_scale;
		vec2 screen_scale;
		vec2 tube_scale;
		vec2 tube_coord;
		vec2 tube_warped_coord_ctr;
		vec2 outermap_coord;
		vec2 outermap_warped_coord_ctr;
		vec2 outermap_warped_outside_screen_vector;
		vec2 outermap_screen_size_from_center;
		vec2 outermap_screen_corner_ctr_coord;
		vec2 outermap_coord_warped_ctr_at_screen_corner;
		float outside_ratio_warped;
		vec2 frame_coord_ctr;
		float top_mask;
		float bottom_mask;	
		float sides_mask;
		float top_corner_mask;	
		float bottom_corner_mask;
		float outside_tube_mask;
		float outside_bezel_mask;
		float edge_mask;
		float noise_mask;

		// screen_aspect is 1.33 for a standard old-style tube placed horizontally
		screen_aspect = HMSS_GetScreenAspect();

		// Scale of the light generating part of the screen relative to the viewport
		screen_scale = HMSS_GetScreenScale();

		// Scale of tube relative to the viewport
		tube_scale = HMSS_GetTubeScale();

		// Additional scale to be applied to the tube scale to create an expanded mapping area 
		outermap_scale = vec2(1, 1) * (1.3 + 1);

		// Coordinate in the space which includes the entire glass area including the illuminated screen and black line around it 
		tube_coord = HMSS_GetInverseScaledCoord(vTexCoord, tube_scale);

		// Get a range width from the outer tube edge to the outer edge of the outermap
		float outermap_range;
		if (global.hmss_curvature_mode < 0.5)
		{
			outermap_range = 0.5 - 0.5 / outermap_scale.y;

			// Get the coord in a space which is scaled larger to avoid discontinuities outside the corners
			outermap_coord = HMSS_GetInverseScaledCoord(tube_coord, vec2(outermap_scale.x, outermap_scale.y));

			// Warp the outermap coordinate be an increased amount so the curvature around the screen matches
			outermap_warped_coord_ctr = HMSS_GetCurvedCoord(outermap_coord, global.hmss_tube_black_edge_curvature_scale * 6) - vec2(0.5, 0.5);

			// Used to scale up the calculated screen size inside the outermap, because the screen shrinks as more curvature is used
			vec2 curvature_long_short = global.hmss_tube_black_edge_curvature_scale * HMSS_GetLongShortAxisCurvatureValues();
			vec2 curvature_scale_offset = screen_aspect < 1.0 ? 1 / (1 + vec2(4.4 * curvature_long_short.y, 4.7 * curvature_long_short.x)) : 1 / (1 + vec2(4.7 * curvature_long_short.x, 4.4 * curvature_long_short.y));

			// Get vector from the screen edge outward
			vec2 outermap_coord_ctr_warped_clipped_to_screen = clamp(outermap_warped_coord_ctr, -0.5 / outermap_scale * curvature_scale_offset, 0.5 / outermap_scale * curvature_scale_offset) ;
			outermap_warped_outside_screen_vector = outermap_warped_coord_ctr - outermap_coord_ctr_warped_clipped_to_screen;

			// Get 0-1 ratio of the distance from the screen edge into the outermap range
			outside_ratio_warped = clamp(length(outermap_warped_outside_screen_vector) / outermap_range, 0, 1);

			// Min and Max values of the screen for both x and y
			outermap_screen_size_from_center = abs(vec2((-0.5 / outermap_scale.x) * curvature_scale_offset.x, (0.5 / outermap_scale.y) * curvature_scale_offset.y));

			// Create a mask to separate between the inside of the screen to the outside of the tube area
			tube_warped_coord_ctr = HMSS_GetCurvedCoord(tube_coord, global.hmss_tube_black_edge_curvature_scale * 1) - vec2(0.5, 0.5);

			// Get the corner of the screen in the outermap coordinates
			outermap_screen_corner_ctr_coord = vec2(0.5, -0.5) / outermap_scale * curvature_scale_offset;

			// Get a coordinate offset so it is centered around the corner
			outermap_coord_warped_ctr_at_screen_corner = abs(outermap_warped_coord_ctr) - (vec2(0.5) / outermap_scale * curvature_scale_offset);
		}
		else
		{
			outermap_range = 0.5 * (outermap_scale.y) * 0.7;
			tube_warped_coord_ctr = tube_coord_warped - 0.5;
			outermap_warped_coord_ctr = tube_warped_coord_ctr;
			outermap_coord = tube_warped_coord_ctr + 0.5;
			outermap_screen_size_from_center = vec2(0.5, 0.5);
			outermap_warped_outside_screen_vector = outermap_warped_coord_ctr - clamp(outermap_warped_coord_ctr, -0.490, 0.490);
			outside_ratio_warped = clamp(length(outermap_warped_outside_screen_vector) / outermap_range, 0, 1);
			outermap_screen_corner_ctr_coord = vec2(0.5, -0.5);

			// Get a coordinate offset so it is centered around the corner
			outermap_coord_warped_ctr_at_screen_corner = abs(outermap_warped_coord_ctr) - vec2(0.5);
		}

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