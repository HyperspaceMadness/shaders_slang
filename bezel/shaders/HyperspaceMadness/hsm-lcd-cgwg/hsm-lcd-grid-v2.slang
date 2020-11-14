#version 450

// HSM Added
#include "../hsm-globals-and-screen-scale-params.inc"
// End Addition

layout(push_constant) uniform Push
{
    float LCD_RSUBPIX_R;
    float LCD_RSUBPIX_G;
    float LCD_RSUBPIX_B;
    float LCD_GSUBPIX_R;
    float LCD_GSUBPIX_G;
    float LCD_GSUBPIX_B;
    float LCD_BSUBPIX_R;
    float LCD_BSUBPIX_G;
    float LCD_BSUBPIX_B;
    float LCD_GAIN;
    float LCD_GAMMA;
    float LCD_BLACK_LEVEL;
    float LCD_AMBIENT;
    float LCD_BGR;
} param;

#pragma parameter LCD_RSUBPIX_R  "[EASYMODE]  Colour of R subpixel: R" 1.0 0.0 1.0 0.01
#pragma parameter LCD_RSUBPIX_G  "[EASYMODE]  Colour of R subpixel: G" 0.0 0.0 1.0 0.01
#pragma parameter LCD_RSUBPIX_B  "[EASYMODE]  Colour of R subpixel: B" 0.0 0.0 1.0 0.01
#pragma parameter LCD_GSUBPIX_R  "[EASYMODE]  Colour of G subpixel: R" 0.0 0.0 1.0 0.01
#pragma parameter LCD_GSUBPIX_G  "[EASYMODE]  Colour of G subpixel: G" 1.0 0.0 1.0 0.01
#pragma parameter LCD_GSUBPIX_B  "[EASYMODE]  Colour of G subpixel: B" 0.0 0.0 1.0 0.01
#pragma parameter LCD_BSUBPIX_R  "[EASYMODE]  Colour of B subpixel: R" 0.0 0.0 1.0 0.01
#pragma parameter LCD_BSUBPIX_G  "[EASYMODE]  Colour of B subpixel: G" 0.0 0.0 1.0 0.01
#pragma parameter LCD_BSUBPIX_B  "[EASYMODE]  Colour of B subpixel: B" 1.0 0.0 1.0 0.01
#pragma parameter LCD_GAIN       "[EASYMODE]  Gain"                    1.0 0.5 2.0 0.05
#pragma parameter LCD_GAMMA      "[EASYMODE]  LCD Gamma"               3.0 0.5 5.0 0.1
#pragma parameter LCD_BLACK_LEVEL "[EASYMODE]  Black level"            0.05 0.0 0.5 0.01
#pragma parameter LCD_AMBIENT    "[EASYMODE]  Ambient"                 0.0 0.0 0.5 0.01
#pragma parameter LCD_BGR        "[EASYMODE]  BGR"                     0 0 1 1

#define outgamma 2.2

#define fetch_offset(coord, offset) (pow(vec3(param.LCD_GAIN) * texelFetchOffset(Source, (coord), 0, (offset)).rgb + vec3(param.LCD_BLACK_LEVEL), vec3(param.LCD_GAMMA)) + vec3(param.LCD_AMBIENT))

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 0) out vec2 vTexCoord;
layout(location = 1) out vec2 CROPPED_ORIGINAL_SIZE;
layout(location = 2) out float SCREEN_ASPECT;
layout(location = 3) out vec2 SCREEN_SCALE;
layout(location = 4) out vec2 SCREEN_COORD;
layout(location = 5) out float USE_VERTICAL_SCANLINES;

void main()
{
    gl_Position = global.MVP * Position;
    vTexCoord = TexCoord;

	CROPPED_ORIGINAL_SIZE = HSM_GetCroppedRotatedOriginalSizeWithCoreResMult();
	SCREEN_ASPECT = HSM_GetScreenAspect();
	SCREEN_SCALE = HSM_GetScreenScale(SCREEN_ASPECT);
	SCREEN_COORD = HSM_GetScreenVTexCoord(vTexCoord, SCREEN_SCALE);
	USE_VERTICAL_SCANLINES = HSM_GetUseVerticalScanlines(SCREEN_ASPECT);
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 1) in vec2 CROPPED_ORIGINAL_SIZE;
layout(location = 2) in float SCREEN_ASPECT;
layout(location = 3) in vec2 SCREEN_SCALE;
layout(location = 4) in vec2 SCREEN_COORD;
layout(location = 5) in float USE_VERTICAL_SCANLINES;

layout(set = 0, binding = 5) uniform sampler2D ColoredGelImage;
layout(set = 0, binding = 6) uniform sampler2D TubeHighlightImage;

layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D Source;

// integral of (1 - x^2 - x^4 + x^6)^2
float coeffs_x[7] = float[](1.0, -2.0/3.0, -1.0/5.0, 4.0/7.0, -1.0/9.0, -2.0/11.0, 1.0/13.0);
// integral of (1 - 2x^4 + x^6)^2
float coeffs_y[7] = float[](1.0,      0.0, -4.0/5.0, 2.0/7.0,  4.0/9.0, -4.0/11.0, 1.0/13.0);

float intsmear_func(float z, float coeffs[7])
{
    float z2 = z*z;
    float zn = z;
    float ret = 0.0;
    for (int i = 0; i < 7; i++) {
        ret += zn*coeffs[i];
        zn *= z2;
    }
    return ret;
}

float intsmear(float x, float dx, float d, float coeffs[7])
{
    float zl = clamp((x-dx*0.5)/d,-1.0,1.0);
    float zh = clamp((x+dx*0.5)/d,-1.0,1.0);
    return d * ( intsmear_func(zh,coeffs) - intsmear_func(zl,coeffs) )/dx;
}

// TODO this is not working yet
// vec3 fetch_offset(vec2 coord, vec2 pixel_offset)
// {
//     vec2 offset = pixel_offset * 1/global.SourceSize.xy;
//     vec3 color = texelFetchOffset(Source, (coord), 0, (pixel_offset)).rgb;
//     // vec3 color = HSM_GetCroppedTexSample(Source, coord + offset).rgb;
//     return pow(vec3(param.LCD_GAIN) * color + vec3(param.LCD_BLACK_LEVEL), vec3(param.LCD_GAMMA)) + vec3(param.LCD_AMBIENT);
// }

void main()
{
    // TODO Add Support for Cropping?
    /* HSM Removed
    vec2 texelSize = global.SourceSize.zw;
    float2 range = IN.video_size / (IN.output_size * IN.texture_size);
    */

    // HSM Added
	vec2 screen_curved_coord = HSM_GetCurvedCoord(SCREEN_COORD, 1, SCREEN_ASPECT);
    vec2 curved_coord = HSM_GetMirrorWrappedCoord(screen_curved_coord);
    vec2 texelSize = 1 / CROPPED_ORIGINAL_SIZE;
    // End Addition

    vec2 range = global.OutputSize.zw;

    vec3 cred   = pow(vec3(param.LCD_RSUBPIX_R, param.LCD_RSUBPIX_G, param.LCD_RSUBPIX_B), vec3(outgamma));
    vec3 cgreen = pow(vec3(param.LCD_GSUBPIX_R, param.LCD_GSUBPIX_G, param.LCD_GSUBPIX_B), vec3(outgamma));
    vec3 cblue  = pow(vec3(param.LCD_BSUBPIX_R, param.LCD_BSUBPIX_G, param.LCD_BSUBPIX_B), vec3(outgamma));

    ivec2 tli = ivec2(floor(curved_coord/texelSize-vec2(0.4999)));

    vec3 lcol, rcol;
    float subpix = (curved_coord.x/texelSize.x - 0.4999 - float(tli.x))*3.0;
    float rsubpix = range.x/texelSize.x * 3.0;

    lcol = vec3(intsmear(subpix+1.0, rsubpix, 1.5, coeffs_x),
                intsmear(subpix    , rsubpix, 1.5, coeffs_x),
                intsmear(subpix-1.0, rsubpix, 1.5, coeffs_x));
    rcol = vec3(intsmear(subpix-2.0, rsubpix, 1.5, coeffs_x),
                intsmear(subpix-3.0, rsubpix, 1.5, coeffs_x),
                intsmear(subpix-4.0, rsubpix, 1.5, coeffs_x));

    if (param.LCD_BGR > 0.5) {
        lcol.rgb = lcol.bgr;
        rcol.rgb = rcol.bgr;
    }

    float tcol, bcol;
    subpix = curved_coord.y/texelSize.y - 0.4999 - float(tli.y);
    rsubpix = range.y/texelSize.y;
    tcol = intsmear(subpix    ,rsubpix, 0.63, coeffs_y);
    bcol = intsmear(subpix-1.0,rsubpix, 0.63, coeffs_y);

    vec3 topLeftColor     = fetch_offset(tli, ivec2(0,0)) * lcol * vec3(tcol);
    vec3 bottomRightColor = fetch_offset(tli, ivec2(1,1)) * rcol * vec3(bcol);
    vec3 bottomLeftColor  = fetch_offset(tli, ivec2(0,1)) * lcol * vec3(bcol);
    vec3 topRightColor    = fetch_offset(tli, ivec2(1,0)) * rcol * vec3(tcol);

    vec3 averageColor = topLeftColor + bottomRightColor + bottomLeftColor + topRightColor;

    averageColor = mat3(cred, cgreen, cblue) * averageColor;

    /* HSM Removed
    FragColor = vec4(pow(averageColor, vec3(1.0/outgamma)),0.0);
    */

    // HSM Added
    FragColor = vec4(averageColor, 1);
    FragColor = HSM_GetPostCrtPreppedColor(FragColor, screen_curved_coord, SCREEN_COORD, SCREEN_ASPECT, SCREEN_SCALE, ColoredGelImage, TubeHighlightImage);
    // End Addition
}
