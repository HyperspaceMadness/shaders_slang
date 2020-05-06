
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
layout(location = 1) out vec2 viewportCoord;

void main()
{
	gl_Position = global.MVP * Position;
    vTexCoord = TexCoord * 1.0001;
	viewportCoord = vTexCoord;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in vec2 viewportCoord;
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
		vec2 tube_coord_warped = vec2(0, 0);
		float outside_tube_mask = 0;
		float edge_mask = 0;
		HMSS_GetCachedCurvedValues(BR_MappingPass, viewportCoord.xy, tube_coord_warped, outside_tube_mask, edge_mask);

		vec2 tube_warped_coord_ctr = tube_coord_warped - 0.5;

		//----------------------------------------------------
		//  Calculate Outside mapping Coords
		//----------------------------------------------------

		/* This first big chunk is to get a mapping of the space outside of the screen which is continuous
		This is more complicated than you would expect because since we are using curved coordinates 
		there are discontinuities outside the normal screen corners, e.g. where x > 1 and y > 1
		So instead of trying to use the coordinates from the screen/tube we use a larger space 
		and subtract the screen space to see how far we are outside of the sreen
		*/

		// General variables related to the main masks referenced later
		float screen_aspect;
		vec2 outermap_scale;
		vec2 screen_scale;
		vec2 tube_scale;
		vec2 tube_coord;
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
		// float outside_tube_mask;
		float outside_bezel_mask;
		// float edge_mask;
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
		float outermap_range = 0.5 * (outermap_scale.y) * 0.7;
		outermap_warped_coord_ctr = tube_warped_coord_ctr;
		outermap_coord = tube_warped_coord_ctr + 0.5;
		outermap_screen_size_from_center = vec2(0.5, 0.5);
		outermap_warped_outside_screen_vector = outermap_warped_coord_ctr - clamp(outermap_warped_coord_ctr, -0.490, 0.490);
		outside_ratio_warped = clamp(length(outermap_warped_outside_screen_vector) / outermap_range, 0, 1);

		// Get a coordinate offset so it is centered around the corner
		outermap_coord_warped_ctr_at_screen_corner = abs(outermap_warped_coord_ctr) - vec2(0.5);

		#ifdef GLASS_PRESET
			float hbl_sharpness_falloff_distance = 20;
		#else
			float hbl_sharpness_falloff_distance = 7;
		#endif

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
		float blur_falloff = (  0.5 +
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
			
			vec2 sample_coord = vTexCoord + vec2(float(i) * dx, float(i) * dy);
			vec4 sampled_color = COMPAT_TEXTURE(Source, sample_coord);
			
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