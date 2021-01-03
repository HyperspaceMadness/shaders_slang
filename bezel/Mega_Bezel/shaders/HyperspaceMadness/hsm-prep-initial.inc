// Import so all the mega bezel parameters are the first in the parameter list

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
layout(set = 0, binding = 4) uniform sampler2D IntroImage;

#define eps 1e-3

/* Composite one image over top another using the alpha to blend
 * It is expected that the input colors have been already premultiplied
 * which means their rgb has already been multiplied by their alpha */
vec4 PreMultAlphaBlend(vec4 color_under, vec4 color_over)
{
	vec4 out_color = vec4(color_over.rgb + (color_under.rgb * (1 - color_over.a)), clamp(color_under.a + color_over.a, 0, 1));
	return out_color;
}

// Assumes Opacity is already encoded in alpha
vec4 BlendModeLayerMix(vec4 color_under, vec4 color_over, float blend_mode, float layer_opacity)
{
	if (blend_mode == 0)
		return color_under;

	if (blend_mode == BLEND_MODE_OFF)
		return color_under;
	
	color_over.a *= layer_opacity;

	vec4 out_color = vec4(0);

	if (blend_mode == BLEND_MODE_NORMAL)
	{
		color_over.rgb *= color_over.a;
		out_color = PreMultAlphaBlend(color_under, color_over);
	}
	else
	{
		vec4 blend_color = color_under; 
		if (blend_mode == BLEND_MODE_ADD)  	 		blend_color.rgb = color_under.rgb + color_over.rgb ;
		if (blend_mode == BLEND_MODE_MULTIPLY)  	blend_color.rgb = color_under.rgb * color_over.rgb ;

		out_color = vec4(clamp(mix(color_under.rgb, blend_color.rgb, color_over.a), 0, 1), color_under.a);
	}
	return out_color;
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

void main()
{
   vec2 intro_image_res = vec2(HSM_INTRO_IMAGE_RES_X, HSM_INTRO_IMAGE_RES_Y);
   vec2 intro_image_scale = intro_image_res / global.OriginalSize.xy;
   vec2 coord_in_intro_image = 1 - ((1 - vTexCoord) / intro_image_scale);

   FragColor = texture(Source, vTexCoord);

   vec4 intro_image = texture(IntroImage, coord_in_intro_image);
   float logo_opacity = 0;
   float initial_wait = 20;
   float visible_wait = 30;
   float fade_in_time = 50;
   float fade_out_time = 50;
   if (global.FrameCount > initial_wait && global.FrameCount <= initial_wait + fade_in_time)
      logo_opacity =  (global.FrameCount - initial_wait) / fade_in_time;
   if (global.FrameCount > initial_wait + fade_in_time && global.FrameCount <= initial_wait + fade_in_time + visible_wait) 
      logo_opacity =  1;
   if (global.FrameCount > initial_wait + fade_in_time + visible_wait) 
      logo_opacity =  1 - clamp((global.FrameCount - (initial_wait + fade_in_time + visible_wait)) / fade_out_time, 0, 1);
   
   // if (global.FrameCount < fade_in_time)
   // logo_opacity = mod(global.FrameCount, fade_in_time)/fade_in_time;

   FragColor = BlendModeLayerMix(FragColor, intro_image, HSM_INTRO_IMAGE_BLEND_MODE, logo_opacity);



   // Apply black level & gamma with input as non linearized
   FragColor = HSM_ApplyBlackLevel(FragColor, 0);

   // Phosphor Persistence
   FragColor = HSM_ApplyPhosphorPersistence(FragColor, PassFeedback6, vTexCoord);

   // Put Average Luminance in the alpha channel
   FragColor.a = GetAverageLuma();
   
   //////// Draw text to show out_colorolutions ////////// 
   if (HSM_RESOLUTION_DEBUG_ON == 1)
   {
      FragColor = AddText(vTexCoord, FragColor);
   }
}