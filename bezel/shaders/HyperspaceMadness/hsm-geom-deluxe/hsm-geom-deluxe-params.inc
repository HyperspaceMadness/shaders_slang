layout(push_constant) uniform Push
{
   float phosphor_power, phosphor_amplitude, CRTgamma, width, aspect_x, aspect_y, d, R, angle_x, angle_y,
      aperture_strength, halation, curvature, cornersize, cornersmooth, overscan_x, overscan_y,
      monitorgamma, mask_type, SHARPER, scanline_weight, geom_lum, interlace_detect;
} params;

#pragma parameter scanline_weight "[CRT GEOM DELUXE] Scanline Weight" 0.3 0.1 0.5 0.05
// #pragma parameter phosphor_power "Phosphor decay power" 1.2 0.5 3.0 0.05
// #pragma parameter phosphor_amplitude "Phosphor persistence amplitude" 0.04 0.0 0.2 0.01
#pragma parameter halation "[HALATION]  Amplitude" 0.1 0.0 0.3 0.01
#pragma parameter width "[HALATION]  Blur Width" 2.0 0.1 4.0 0.1
#pragma parameter mask_type "[MASK]  Aperture, Delta, Slot" 1.0 1.0 19.0 1.0
#pragma parameter aperture_strength "[MASK]  Strength" 0.4 0.0 1.0 0.05
#pragma parameter geom_lum "[Luminance]" 0.0 0.0 1.0 0.01
// #pragma parameter curvature "Enable Curvature" 1.0 0.0 1.0 1.0
// #pragma parameter R "Radius of curvature" 3.5 0.5 10.0 0.1
// #pragma parameter d "Distance to screen" 2.0 0.1 10.0 0.1
// #pragma parameter angle_x "Tilt X" 0.0 -1.0 1.0 0.01
// #pragma parameter angle_y "Tilt Y" 0.0 -1.0 1.0 0.01
// #pragma parameter cornersize "Rounded corner size" 0.01 0.00 0.10 0.01
// #pragma parameter cornersmooth "Border smoothness" 1000.0 100.0 2000.0 100.0
// #pragma parameter overscan_x "Overscan X" 1.0 0.8 1.2 0.02
// #pragma parameter overscan_y "Overscan Y" 1.0 0.8 1.2 0.02
#pragma parameter CRTgamma "[GAMMA]  Gamma of Simulated CRT" 2.4 0.7 4.0 0.05 
#pragma parameter monitorgamma "[GAMMA]  Gamma of Output Display" 2.4 0.7 4.0 0.05
// #pragma parameter aspect_x "Aspect ratio X" 1.0 0.3 1.0 0.01
// #pragma parameter aspect_y "Aspect ratio Y" 0.75 0.3 1.0 0.01
// #pragma parameter interlace_detect "CRTGeom Interlacing Simulation" 0 0.0 1.0 1.0

// #define phosphor_power params.phosphor_power
// #define phosphor_amplitude params.phosphor_amplitude
#define CRTgamma params.CRTgamma
#define width params.width
// #define curvature params.curvature
// #define d params.d
// #define cornersize params.cornersize
// #define cornersmooth params.cornersmooth
#define monitorgamma params.monitorgamma
#define halation params.halation
#define aperture_strength params.aperture_strength
#define geom_lum params.geom_lum
#define scanline_weight params.scanline_weight
#define interlace_detect 0
// vec2 aspect = vec2(params.aspect_x, params.aspect_y);
vec2 aspect = vec2(1, 1);
// vec2 angle = vec2(params.angle_x, params.angle_y);
// vec2 overscan = vec2(params.overscan_x, params.overscan_y);
int mask_picker = int(params.mask_type);

const float gamma = 2.2;
