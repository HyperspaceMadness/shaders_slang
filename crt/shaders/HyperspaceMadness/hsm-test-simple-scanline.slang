#version 450

/*
Simple Scanline Shader to test cropping
*/

// HSM Added
#include "./hsm-screen-scale-with-globals.inc"
// End Addition

// layout(push_constant) uniform Push
// {
// 	float scanline_darkness;
// } params;

#define FIX(c) max(abs(c), 1e-5)
#define PI 3.141592653589

vec3 get_scanline_weight(float pos, float beam, float strength)
{
    float weight = 1.0 - pow(cos(pos * 2.0 * PI) * 0.5 + 0.5, beam);
    
    weight = weight * strength * 2.0 + (1.0 - strength);
    
    return vec3(weight);
}

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out vec2 screenScale;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord;

    screenScale =  HMSS_GetScreenScale();
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in vec2 screenScale;

layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D Source;

void main()
{
    vec2 screen_coord = HMSS_GetScreenVTexCoord(vTexCoord);
    vec2 tex_size = HMSS_GetCroppedOriginalSize();

    vec2 screen_curved_coord = HMSS_GetCurvedCoord(screenCoord, 1);
    vec2 mirror_screen_curved_coord = HMSS_GetMirrorWrappedCoord(screen_curved_coord);

    vec2 quantized_coord = (floor(mirror_screen_curved_coord * tex_size) + 0.5) / tex_size;

    FragColor = HMSS_Linearize(HMSS_GetCroppedTexSample(Source, quantized_coord), HMSS_DEFAULT_CRT_GAMMA);

	FragColor = HMSS_GetPostCrtPreppedColor(FragColor, screen_curved_coord, screen_coord);
}
