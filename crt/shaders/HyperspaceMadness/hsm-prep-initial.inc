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

#ifndef ROYALE_PRESET
   layout(set = 0, binding = 4) uniform sampler2D SamplerLUT3;
#endif

#define eps 1e-3


float GetAverageLuma()
{
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
   return luma_total;
}

// Fixes Undefined values with different GPU vendors. 
// Keeps values within a safe range
vec4 mixfix(vec4 a, vec4 b, float c)
{
	return (a.z < 1.0) ? mix(a, b, c) : a;
}

// Borrowed from Guest's Guest-Venom Shader
// LUT is from Torridgristle
vec4 ApplyLUT(vec4 in_color, sampler2D in_LUT)
{
   if (global.hmss_color_lut_colors_on < 0.5) return in_color;

   float LUT_Size = 32;

   float red = ( in_color.r * (LUT_Size - 1.0) + 0.499999 ) / (LUT_Size * LUT_Size);
   float green = ( in_color.g * (LUT_Size - 1.0) + 0.499999 ) / LUT_Size;
   float blue1 = (floor( in_color.b  * (LUT_Size - 1.0) ) / LUT_Size) + red;
   float blue2 = (ceil( in_color.b  * (LUT_Size - 1.0) ) / LUT_Size) + red;
   float mixer = clamp(max((in_color.b - blue1) / (blue2 - blue1), 0.0), 0.0, 32.0);

   vec4 color1 = texture( in_LUT, vec2( blue1, green ));
   vec4 color2 = texture( in_LUT, vec2( blue2, green ));
   vec4 out_color = mixfix(color1, color2, mixer);

   out_color.rgb = pow(out_color.rgb, vec3(1.0 / 1.20));

   // HSM Added
   // Avoids clipped pixels showing up black
   out_color.rgb = clamp(out_color.rgb, 0, 1);
   
   float mx = max(out_color.r, max(out_color.g, out_color.b));
   out_color.rgb = mix(in_color.rgb, out_color.rgb, clamp(25.0 * (mx - 0.05), 0, 1));		
   float l = length(in_color.rgb);
   out_color.rgb = normalize(out_color.rgb + 1e-10) * l;

   return out_color;
}

vec4 AddText(vec4 in_color)
{
   vec4 out_color = in_color;
   out_color = mix(out_color, vec4(0, 0, 0, 1), GetTextMask(vTexCoord + 2 * vec2(1/global.OutputSize.x, 0), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
   out_color = mix(out_color, vec4(0, 0, 0, 1), GetTextMask(vTexCoord - 2 * vec2(1/global.OutputSize.x, 0), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
   out_color = mix(out_color, vec4(0, 0, 0, 1), GetTextMask(vTexCoord + 1 * vec2(0, 1/global.OutputSize.y), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
   out_color = mix(out_color, vec4(0, 0, 0, 1), GetTextMask(vTexCoord - 1 * vec2(0, 1/global.OutputSize.y), global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
   out_color = mix(out_color, vec4(1, 1, 0, 1), GetTextMask(vTexCoord,                                      global.FinalViewportSize.xy, HMSS_GetScreenSize(), HMSS_GetCroppedOriginalSize(), HMSS_GetIntegerScaleMult()));
   return out_color;
}

void main()
{
   FragColor =  texture(Source, vTexCoord);

   // Phosphor Persistence
   FragColor = HMSS_ApplyPhosphorPersistence(FragColor, PassFeedback6, vTexCoord);
   
   // Royale can't currently is currently at the limit of number of textures so we can't add the LUT
   #ifndef ROYALE_PRESET
      FragColor = ApplyLUT(FragColor, SamplerLUT3);
   #endif

   // Apply black level & gamma with input as non linearized
   FragColor = HMSS_ApplyBlackLevelGamma(FragColor, 0);

   // Add Color Temperature
   FragColor = HMSS_ApplyColorTemperature_D65_D50(FragColor);

   // Put Average Luminance in the alpha channel
   FragColor.a = GetAverageLuma();

   //////// Draw text to show out_colorolutions ////////// 
   if (global.hmss_screen_scale_debug == 1)
   {
      FragColor = AddText(FragColor);
   }

}