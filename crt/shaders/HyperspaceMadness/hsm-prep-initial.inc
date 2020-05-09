// Import so all the mega bexel parameters are the first in the parameter list

#include "hsm-text.inc"

const float hag_afterglow_persistence = 0.5;
const float hag_afterglow_saturation = 0.1;

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
layout(set = 0, binding = 2) uniform sampler2D Source;
layout(set = 0, binding = 3) uniform sampler2D PassFeedback6;

#define eps 1e-3

vec3 Phosphor = vec3(0.5, 0.6, 0.8);

void main()
{
   FragColor =  texture(Source, vTexCoord);

   // Phosphor Persistence
   if (global.hmss_phosphor_persistence != 0)
   {
      float DeltaTime = 5 - 5 * HHLP_EasePowerOut(global.hmss_phosphor_persistence, 2) + 0.1;
      vec4 prev_color = texture(PassFeedback6, vTexCoord);
      prev_color.r *= pow(Phosphor.r, DeltaTime);
      prev_color.g *= pow(Phosphor.g, DeltaTime);
      prev_color.b *= pow(Phosphor.b, DeltaTime);
      FragColor.r = max(prev_color.r, FragColor.r);
      FragColor.g = max(prev_color.g, FragColor.g);
      FragColor.b = max(prev_color.b, FragColor.b);
   }
   
   // Apply black level & gamma with input as non linearized
   FragColor = HMSS_ApplyBlackLevelGamma(FragColor, 0);

   //////// Calculate Average Luminance ////////// 
   float m = max(log2(global.SourceSize.x), log2(global.SourceSize.y));
	m = max(m - 1.0, 1.0);
	
	float luma_total = 0.0;
	
	float num_samples = 5;
	float sample_dist = 1 / (num_samples - 1);
	vec4 tex_sample = vec4(0);
	for (float i = 0; i <= num_samples; i++)
	{
		for (float j = 0; j <= num_samples; j++)
		{
			tex_sample = textureLod(Source, vec2(sample_dist * i, sample_dist * j), m);
			luma_total += max(0.0, (tex_sample.r + tex_sample.g + tex_sample.g) / 3);
			// luma_total += max(0.0, length(tex_sample.rgb));
		}
	}
	luma_total = pow(0.577350269 * luma_total / (num_samples * num_samples), 0.6);

   //////// Draw text to show resolutions ////////// 
   if (global.hmss_screen_scale_debug == 1)
   {
      FragColor = mix(FragColor, vec4(0, 0, 0, 1), GetTextMask(vTexCoord + 2 * vec2(1/global.OutputSize.x, 0), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
      FragColor = mix(FragColor, vec4(0, 0, 0, 1), GetTextMask(vTexCoord - 2 * vec2(1/global.OutputSize.x, 0), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
      FragColor = mix(FragColor, vec4(0, 0, 0, 1), GetTextMask(vTexCoord + 1 * vec2(0, 1/global.OutputSize.y), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
      FragColor = mix(FragColor, vec4(0, 0, 0, 1), GetTextMask(vTexCoord - 1 * vec2(0, 1/global.OutputSize.y), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
      FragColor = mix(FragColor, vec4(1, 1, 0, 1), GetTextMask(vTexCoord,                                      global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
   }

   FragColor = vec4(FragColor.rgb, luma_total);
}