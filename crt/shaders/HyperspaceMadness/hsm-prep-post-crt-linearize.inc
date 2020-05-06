
#include "hsm-mega-screen-scale.inc"

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D BR_CRTPass;
layout(set = 0, binding = 3) uniform sampler2D BR_MappingPass;
layout(set = 0, binding = 10) uniform sampler2D TubeGlassImage;

void main()
{
	FragColor = HHLP_Linearize(texture(BR_CRTPass, vTexCoord));
	
	vec2 tube_coord_warped = vec2(0, 0);
	float outside_tube_mask = 0;
	float edge_mask = 0;
	HMSS_GetCachedCurvedValues(BR_MappingPass, vTexCoord.xy, tube_coord_warped, outside_tube_mask, edge_mask);
	vec2 mirrored_tube_coord = HMSS_GetMirrorWrappedCoord(tube_coord_warped);
	
	float vignette_factor = HMSS_GetVignetteFactor(mirrored_tube_coord, global.hmss_screen_vignette);

	// If this is called from the glass preset we don't want the vignette to affect mirrored area
	#ifdef GLASS_PRESET
		float tube_mask = HMSS_GetCornerMask((tube_coord_warped - 0.5) * 0.999 + 0.5, global.hmss_corner_radius, 0.9);
		vignette_factor = 1 - ((1 - vignette_factor) * tube_mask);
	#endif

	FragColor *= vignette_factor;


	// vec4 tube_glass_image = HHLP_Linearize(texture(TubeGlassImage, (tube_coord_warped - 0.5) * 0.97 + 0.5 ));
	// FragColor = FragColor + 50 / 100 * tube_glass_image.a * (1 - outside_tube_mask) * tube_glass_image;
}