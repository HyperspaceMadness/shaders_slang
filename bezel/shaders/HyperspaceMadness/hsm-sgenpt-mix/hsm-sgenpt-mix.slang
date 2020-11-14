#version 450

/*
   SGENPT-MIX - Sega Genesis Pseudo Transparency Mixer Shader

   hsm-sgenpt-mix combines V2 and V3 and allows it to be turned off
   
   2011-2020 Hyllian - sergiogdb@gmail.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is 
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

*/


layout(push_constant) uniform Push
{
	vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	uint FrameCount;
   float SGPT_MODE;
	float SGPT_SHARPNESS;
	float SGPT_AR_STRENGTH;
	float SGPT_BLEND_OPTION;
} params;

#pragma parameter SGPT_MODE "[ GENESIS TRANSPARENCY - SGENPT-MIX ] - Mode OFF | V2 | V4" 0 0 2 1
#define SGPT_MODE params.SGPT_MODE

#pragma parameter SGPT_SHARPNESS "[ GENESIS TRANSPARENCY - SGENPT-MIX ] - Sharpness" 1 0 2 0.1
#define SGPT_SHARPNESS params.SGPT_SHARPNESS

// #pragma parameter SGPT_AR_STRENGTH "[ GENESIS TRANSPARENCY - SGENPT-MIX ] - (V2) Anti-ringing " 1 0 1 0.1
// #define SGPT_AR_STRENGTH params.SGPT_AR_STRENGTH

#define SGPT_AR_STRENGTH 1

// #pragma parameter SGPT_BLEND_OPTION "[ SGENPT-MIX ] - (V4) Blend Mode - OFF | Transparency" 1 0 1 1
// #define SGPT_BLEND_OPTION params.SGPT_BLEND_OPTION


layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
} global;


// These weights are chosen specifically to blend vertical line pixels, creating new colors.
mat2x4 weights_v2()
{
	if (SGPT_SHARPNESS < 0.1)
	{
		return mat2x4(0.004343062, -0.017526903, 0.2467891, 0.532789482, 0.2467891, -0.017526903, 0.004343062, 0.0);
	}
	else if (SGPT_SHARPNESS < 1.1)
	{
		return mat2x4(-0.006737355, -0.046654754, 0.256859037, 0.593066142, 0.256859037, -0.046654754, -0.006737355, 0.0);
	}
	else if (SGPT_SHARPNESS > 1.90)
	{
		return mat2x4(0.001012575, -0.089888149, 0.249726319, 0.678298509, 0.249726319, -0.089888149, 0.001012575, 0.0);
	}
}
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

void main()
{
   vec3 color = texture(Source, vTexCoord).xyz;

   // Version 2
   if (SGPT_MODE == 1)
   {
      vec2 dx = vec2(1.0, 0.0);
      vec2 dy = vec2(0.0, 1.0);

      vec2 tc = vTexCoord*params.SourceSize.xy;

      dx = dx * params.SourceSize.zw;
      dy = dy * params.SourceSize.zw;
      tc = tc * params.SourceSize.zw;
     
      // reading the texels
      vec3 c0 = texture(Source, tc-3.0*dx).xyz;
      vec3 c1 = texture(Source, tc-2.0*dx).xyz;
      vec3 c2 = texture(Source, tc    -dx).xyz;
      vec3 c3 = texture(Source, tc       ).xyz;
      vec3 c4 = texture(Source, tc    +dx).xyz;
      vec3 c5 = texture(Source, tc+2.0*dx).xyz;
      vec3 c6 = texture(Source, tc+3.0*dx).xyz;

      mat2x4 w = weights_v2();

      color = mat4x3(c0, c1, c2, c3)*w[0];
      color+= mat3x3(c4, c5, c6)*w[1].xyz;

      //  Get min/max samples
      vec3 min_sample = max(min(c3, c2), min(c3, c4));
      vec3 max_sample = min(max(c3, c2), max(c3, c4));

      // Anti-ringing
      vec3 aux = color;
      color = clamp(color, min_sample, max_sample);
      color = mix(aux, color, SGPT_AR_STRENGTH);
   }

   // Version 4
   if (SGPT_MODE == 2)
   {
		vec2 dx = vec2(1.0, 0.0)*params.SourceSize.zw;
      vec2 dy = vec2(0.0, 1.0)*params.SourceSize.zw;

      // Reading the texels.
      vec3 C = texture(Source, vTexCoord    ).xyz;
      vec3 L = texture(Source, vTexCoord -dx).xyz;
      vec3 R = texture(Source, vTexCoord +dx).xyz;
      vec3 U = texture(Source, vTexCoord -dy).xyz;
      vec3 D = texture(Source, vTexCoord +dy).xyz;

      color = C;

      // if (SGPT_BLEND_OPTION > 0.0)
      // {
         //  Get min/max samples
         vec3 min_sample = min(C, max(L, R));
         vec3 max_sample = max(C, min(L, R));

         color = 0.5*C + 0.25*(L + R);

         // // if (SGPT_BLEND_OPTION > 1.0)
         // // {
         //    //  Get min/max samples
         //    min_sample = max(min_sample, min(C, max(U, D)));
         //    max_sample = min(max_sample, max(C, min(U, D)));

         //    color = 0.5*C + 0.125*(L + R + U + D);
         // // }

         // Sharpness control
         vec3 aux = color;
         color = clamp(color, min_sample, max_sample);
         color = mix(aux, color, SGPT_SHARPNESS);
      // }
   }

    FragColor = vec4(color, 1.0);
}
