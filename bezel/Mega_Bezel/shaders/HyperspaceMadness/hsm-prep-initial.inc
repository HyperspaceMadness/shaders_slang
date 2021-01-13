// Import so all the mega bezel parameters are the first in the parameter list

#include "hsm-text.inc"

const float hag_afterglow_persistence = 0.5;
const float hag_afterglow_saturation = 0.1;

float SCREEN_ASPECT = HSM_GetScreenAspect();
vec2 SCREEN_SCALE = HSM_GetScreenScale(SCREEN_ASPECT);

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
layout(set = 0, binding = 4) uniform sampler2D IntroImage;

#define eps 1e-3

/*
	Texture interpolation based on "Improved texture interpolation" by Inigo Quilez
	Original description: http://www.iquilezles.org/www/articles/texture/texture.htm
	Expects the texture to be using linear filtering
*/
vec4 TextureQuilez(sampler2D in_sampler_2D, vec2 in_texture_size, vec2 p)
{
	vec2 tex_size = textureSize(in_sampler_2D, 0);
	p = p * in_texture_size + vec2(0.5, 0.5);

	vec2 i = floor(p);
	vec2 f = p - i;
	f = f * f * f * (f * (f * 6.0 - vec2(15.0, 15.0)) + vec2(10.0, 10.0));
	p = i + f;

	p = (p - vec2(0.5, 0.5)) * (1/in_texture_size);

	// final sum and weight normalization
	return texture(in_sampler_2D, p);
}


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


vec4 AddText(vec2 in_coord, vec4 in_color)
{
   float screen_aspect = HSM_GetScreenAspect();
   vec2 screen_scale = HSM_GetScreenScale(screen_aspect);
   vec2 screen_size = HSM_GetScreenSize(screen_scale);
   vec2 int_scale_mult = HSM_GetIntegerScaleMult(screen_size);
   vec2 original_size = HSM_GetRotatedRawOriginalSize();
   vec2 cropped_original_size = HSM_GetCroppedRotatedOriginalSize();
   vec2 cropped_original_size_with_core_res_mult = HSM_GetCroppedRotatedOriginalSizeWithCoreResMult();
   
   if (abs(HSM_FLIP_VIEWPORT_VERTICAL - HSM_FLIP_CORE_VERTICAL) > 0.5) in_coord.y = 1 - in_coord.y;
   
   vec4 out_color = in_color;
   out_color = mix(out_color, vec4(0, 0, 0, 1), GetTextMask(in_coord + 2 * vec2(1/global.OutputSize.x, 0), global.FinalViewportSize.xy, screen_size, original_size, cropped_original_size, cropped_original_size_with_core_res_mult, int_scale_mult, global.OriginalSize.xy));
   out_color = mix(out_color, vec4(0, 0, 0, 1), GetTextMask(in_coord - 2 * vec2(1/global.OutputSize.x, 0), global.FinalViewportSize.xy, screen_size, original_size, cropped_original_size, cropped_original_size_with_core_res_mult, int_scale_mult, global.OriginalSize.xy));
   out_color = mix(out_color, vec4(0, 0, 0, 1), GetTextMask(in_coord + 1 * vec2(0, 1/global.OutputSize.y), global.FinalViewportSize.xy, screen_size, original_size, cropped_original_size, cropped_original_size_with_core_res_mult, int_scale_mult, global.OriginalSize.xy));
   out_color = mix(out_color, vec4(0, 0, 0, 1), GetTextMask(in_coord - 1 * vec2(0, 1/global.OutputSize.y), global.FinalViewportSize.xy, screen_size, original_size, cropped_original_size, cropped_original_size_with_core_res_mult, int_scale_mult, global.OriginalSize.xy));
   out_color = mix(out_color, vec4(1, 1, 0, 1), GetTextMask(in_coord,                                      global.FinalViewportSize.xy, screen_size, original_size, cropped_original_size, cropped_original_size_with_core_res_mult, int_scale_mult, global.OriginalSize.xy));
   return clamp(out_color, 0, 1);
}

// -----------------------------------------------------------------------------
// TV Startup Static Animation
// -----------------------------------------------------------------------------
vec4 GetColorWithIntro(vec4 in_color, vec2 in_coord)
{
   vec4 out_color = in_color;

   float frame_count = global.FrameCount;

   // Loop the animation so we can see the results
   if (HSM_INTRO_WHEN_TO_SHOW == 2)
      frame_count = mod(frame_count, HSM_INTRO_REPEAT_TIME);

   float mask_wait = 20 / HSM_INTRO_SPEED;
   
	float mask_fade_horizontal = 40 / HSM_INTRO_SPEED;
	float mask_fade_vertical = 60 / HSM_INTRO_SPEED;
	float mask_vert_wait = mask_fade_horizontal * 0.4;

   vec4 solid_color = vec4(HSM_HSVtoRGB(vec3(HSM_INTRO_SOLID_COLOR_HUE, HSM_INTRO_SOLID_COLOR_SAT, HSM_INTRO_SOLID_COLOR_VALUE)), 1);
   // vec4 solid_color = HSM_Linearize(vec4(HSM_HSVtoRGB(vec3(HSM_BZL_COLOR_HUE, HSM_BZL_COLOR_SATURATION, HSM_BZL_COLOR_VALUE)), 1), HSM_DEFAULT_SRGB_GAMMA).rgb;

	float solid_color_hold = HSM_INTRO_SOLID_COLOR_HOLD / HSM_INTRO_SPEED;
	float solid_color_fade_out = HSM_INTRO_SOLID_COLOR_FADE_OUT / HSM_INTRO_SPEED;

   float intro_logo_wait = HSM_INTRO_LOGO_WAIT / HSM_INTRO_SPEED;
   float intro_logo_fade_in = HSM_INTRO_LOGO_FADE_IN / HSM_INTRO_SPEED;
   float intro_logo_hold = HSM_INTRO_LOGO_HOLD / HSM_INTRO_SPEED;
   float intro_logo_fade_out = HSM_INTRO_LOGO_FADE_OUT / HSM_INTRO_SPEED;

	float static_hold = HSM_INTRO_NOISE_HOLD / HSM_INTRO_SPEED;
	float static_fade_out = HSM_INTRO_NOISE_FADE_OUT / HSM_INTRO_SPEED;

	if (frame_count <= mask_wait + mask_vert_wait + mask_fade_vertical + static_hold + static_fade_out)
	{
		vec2 noise_res = global.OriginalSize.xy;
      noise_res = min(noise_res, vec2(640, 480));
		vec2 quantized_coord = vec2(floor(in_coord.x * noise_res.x) / noise_res.x, floor(in_coord.y * noise_res.y) / noise_res.y);

		float width = (frame_count - mask_wait) / (mask_fade_horizontal/2);
		float height = (clamp((frame_count - mask_wait - mask_vert_wait) / mask_fade_vertical, 0, 1) + 0.005) * 2;
		float mask = abs(in_coord.x - 0.5) > width * 0.5 ? 0 : 1;
		mask *= HHLP_EasePowerOut(abs(in_coord.y - 0.5), 1.5) > height ? 0 : 1;

		float area = width * height;

		float solid_color_opacity = HHLP_EasePowerIn(clamp(1 - (frame_count - (mask_wait + mask_fade_horizontal/2.5 + solid_color_hold)) / solid_color_fade_out * 2, 0, 1), 1.5);
      out_color = mix(out_color, vec4(0, 0, 0, 1), solid_color_opacity);

		float static_opacity =  1 - clamp((frame_count - static_hold - mask_wait - mask_fade_horizontal) / static_fade_out, 0, 1);
		static_opacity = HHLP_EasePowerInOut(static_opacity, 4);

		// Calculate Static Noise
		float e = 2.7182818284590452353602874713527;
		float G = e + (mod(frame_count, 30)/30 + 1000);
		vec2 r = (G * sin(G * quantized_coord.xy));
		vec4 noise_color = vec4(fract(r.x * r.y * (1.0 + quantized_coord.x)));
		noise_color.a = 1;

		noise_color.rgb *= 0.60;

		out_color = HSM_BlendModeLayerMix(out_color, noise_color, HSM_INTRO_NOISE_BLEND_MODE, static_opacity);

      vec2 intro_image_res = vec2(HSM_INTRO_LOGO_RES_X, HSM_INTRO_LOGO_RES_Y);
      float intro_image_aspect = intro_image_res.x/intro_image_res.y;
      // vec2 intro_image_scale = intro_image_res / global.OriginalSize.xy / SCREEN_ASPECT;

      float intro_logo_height = HSM_INTRO_LOGO_HEIGHT;
      if (intro_logo_height == 0)
         intro_logo_height = intro_image_res.y / global.OriginalSize.y;

      vec2 intro_image_scale = vec2(intro_logo_height * intro_image_aspect / SCREEN_ASPECT, intro_logo_height);

      // Center
      vec2 coord_in_intro_image = (in_coord - 0.5) / intro_image_scale + 0.5;
      // Top Left
      if (HSM_INTRO_LOGO_PLACEMENT == 1)
         coord_in_intro_image = in_coord / intro_image_scale;
      // Top Right
      if (HSM_INTRO_LOGO_PLACEMENT == 2)
         coord_in_intro_image = (in_coord - vec2(1 - intro_image_scale.x, 0)) / intro_image_scale;
      // Bottom Left
      if (HSM_INTRO_LOGO_PLACEMENT == 3)
         coord_in_intro_image = (in_coord - vec2(0, 1 - intro_image_scale.y)) / intro_image_scale;
      // Bottom Right
      if (HSM_INTRO_LOGO_PLACEMENT == 4)
         coord_in_intro_image = (in_coord - (1 - intro_image_scale)) / intro_image_scale;

      // Quilez gives a better rescaling weighted more to the center of the pixel like bicubic
      vec4 intro_image = TextureQuilez(IntroImage, intro_image_res, coord_in_intro_image);
      float logo_opacity = 1 - HHLP_EasePowerOut(clamp(1 - (frame_count - mask_wait - mask_fade_horizontal/4) / intro_logo_fade_in, 0, 1), 1.5);
      logo_opacity *=  clamp(clamp((frame_count - intro_logo_wait) / intro_logo_fade_in, 0, 1) - 
                              clamp((frame_count - (intro_logo_wait + intro_logo_fade_in + intro_logo_hold)) / intro_logo_fade_out, 0, 1), 
                              0, 1);


      // Logo UNDER solid color
      if (HSM_INTRO_LOGO_OVER_SOLID_COLOR == 0)
         out_color = HSM_BlendModeLayerMix(out_color, intro_image, HSM_INTRO_LOGO_BLEND_MODE, logo_opacity);

		out_color = HSM_BlendModeLayerMix(out_color, solid_color, HSM_INTRO_SOLID_COLOR_BLEND_MODE, solid_color_opacity);

      // Logo OVER solid color
      if (HSM_INTRO_LOGO_OVER_SOLID_COLOR == 1)
         out_color = HSM_BlendModeLayerMix(out_color, intro_image, HSM_INTRO_LOGO_BLEND_MODE, logo_opacity);

		out_color *= mask;

      HSM_Delinearize(out_color, HSM_DEFAULT_SRGB_GAMMA);
	}
   return out_color;
}

void main()
{
   FragColor = texture(Source, vTexCoord);
   // HSM_Linearize(FragColor, HSM_DEFAULT_SRGB_GAMMA);

   if (HSM_INTRO_WHEN_TO_SHOW > 0)
      FragColor = GetColorWithIntro(FragColor, vTexCoord);

   // Apply black level & gamma with input as non linearized
   FragColor = HSM_ApplyBlackLevel(FragColor, 0);

   // Phosphor Persistence
   FragColor = HSM_ApplyPhosphorPersistence(FragColor, PassFeedback6, vTexCoord);

   // Put Average Luminance in the alpha channel
   FragColor.a = GetAverageLuma();
   
   //////// Draw text to show out_colorolutions ////////// 
   if (HSM_RESOLUTION_DEBUG_ON == 1)
      FragColor = AddText(vTexCoord, FragColor);

   // FragColor = HSM_Delinearize(FragColor, HSM_DEFAULT_SRGB_GAMMA);
}