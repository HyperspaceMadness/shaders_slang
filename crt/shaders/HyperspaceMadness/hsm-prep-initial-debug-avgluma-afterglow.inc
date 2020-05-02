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
layout(set = 0, binding = 3) uniform sampler2D OriginalHistory1;
layout(set = 0, binding = 4) uniform sampler2D OriginalHistory2;
layout(set = 0, binding = 5) uniform sampler2D OriginalHistory3;
layout(set = 0, binding = 6) uniform sampler2D OriginalHistory4;
layout(set = 0, binding = 7) uniform sampler2D OriginalHistory5;
layout(set = 0, binding = 8) uniform sampler2D OriginalHistory6;

#define Prev1Texture OriginalHistory1
#define Prev2Texture OriginalHistory2
#define Prev3Texture OriginalHistory3
#define Prev4Texture OriginalHistory4
#define Prev5Texture OriginalHistory5
#define Prev6Texture OriginalHistory6

#define eps 1e-3

vec3 afterglow(float number)
{
	return vec3(global.hmss_afterglow_amount) * exp2(-vec3(hag_afterglow_persistence) * vec3(number * number));
}

void main()
{
   FragColor =  texture(Source, vTexCoord);
   vec3 rgb_color = FragColor.xyz;
   ////////// Calculate Afterglow ////////// 
   if (global.hmss_afterglow_amount != 0)
   {
      vec3 glow = vec3(0);
      glow += texture(Prev1Texture, vTexCoord).rgb * afterglow(1.0);
      glow += texture(Prev2Texture, vTexCoord).rgb * afterglow(2.0);
      glow += texture(Prev3Texture, vTexCoord).rgb * afterglow(3.0);
      glow += texture(Prev4Texture, vTexCoord).rgb * afterglow(4.0);
      glow += texture(Prev5Texture, vTexCoord).rgb * afterglow(5.0);
      glow += texture(Prev6Texture, vTexCoord).rgb * afterglow(6.0);

      glow = normalize(pow(glow + vec3(eps), vec3(hag_afterglow_saturation))) * length(glow);		
      
      float glow_over_threshold = (rgb_color.r + rgb_color.g + rgb_color.b) > 7.0 / 255.0 ? 0 : 1;
      
      rgb_color += glow_over_threshold * glow;
   }
   
   // Apply black level & gamma with input as non linearized
   FragColor = HMSS_ApplyBlackLevelGamma(vec4(rgb_color, 1), 0);

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