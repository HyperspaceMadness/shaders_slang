/*   

Author: HyperspaceMadness - remimcgill@hotmail.com
License: GPL
Description:

*/

float HHLP_GetMaskCenteredOnValue(float in_value, float value_to_match, float threshold)
{
	float edge_0 = value_to_match - threshold;
	float edge_1 = value_to_match - 0.5 * threshold;
	float edge_2 = value_to_match + 0.5 * threshold;
	float edge_3 = value_to_match + threshold;
	float out_mask = 1.0;
	out_mask *= smoothstep(edge_0, edge_1, in_value);
	out_mask *= smoothstep(edge_3, edge_2, in_value);
	return out_mask;
}

// Quadratic Bezier allows us to have a controlled falloff between 0 and 1 
// One use is to avoid the perception of discontinuity at the outer edge experienced with a linear gradients
float HHLP_QuadraticBezier (float x, vec2 a)
{
  // Originally adapted by @kyndinfo from BEZMATH.PS (1993) by Don Lancaster
  // http://www.tinaja.com/text/bezmath.html
  
  float epsilon = 0.00001;
  a.x = clamp(a.x,0.0,1.0); 
  a.y = clamp(a.y,0.0,1.0); 
  if (a.x == 0.5){
    a += epsilon;
  }
  
  // solve t from x (an inverse operation)
  float om2a = 1.0 - 2.0 * a.x;
  float t = (sqrt(a.x*a.x + om2a*x) - a.x)/om2a;
  float y = (1.0-2.0*a.y)*(t*t) + (2.0*a.y)*t;
  return y;
}

float HHLP_EasePowerIn(float x, float in_exponent) 
{
  x = max(0, min(x, 1));
  return pow(x, in_exponent);
}

float HHLP_EasePowerOut(float x, float in_exponent) 
{
  x = 1.0 - max(0, min(x, 1));
  return 1.0 - pow(x, in_exponent);
}

float HHLP_EasePowerInOut(float x, float in_exponent) 
{
  x = max(0, min(x, 1));
  if (x < 0.5) 
  {
    return pow(x * 2, in_exponent) * 0.5;
  } 
  else 
  {
    return 1.0 - pow((1 - x) * 2, in_exponent) * 0.5;
  }
}

float HHLP_GetDistanceToLine(float x1, float y1, float a, float b, float c)
{
    float d = abs((a * x1 + b * y1 + c)) /  
              (sqrt(a * a + b * b));
    return d; 
}

// Returns 1 if in_value < compare_value
// Useful when ifs are bad for performance
float HHLP_IsUnderValue(float in_value, float compare_value)
{
	return clamp((compare_value - in_value) * 100000, 0, 1);
}

// Returns 1 if in_value > compare_value
// Useful when ifs are bad for performance
float HHLP_IsOverValue(float in_value, float compare_value)
{
	return clamp(-1 * (compare_value - in_value) * 100000, 0, 1);
}

// Returns 1 if in_value == compare_value within the epsilon value provided
// Useful when ifs are bad for performance
float HHLP_EqualsValue(float in_value, float compare_value, float epsilon)
{
	return HHLP_IsUnderValue(in_value, compare_value + epsilon) * HHLP_IsOverValue(in_value, compare_value - epsilon);
}

float HHLP_EqualsResolution(vec2 in_res, vec2 test_res)
{
  float hardcoded_epsilon = 0.001;
  return  HHLP_EqualsValue(in_res.x, test_res.x, hardcoded_epsilon) * 
          HHLP_EqualsValue(in_res.y, test_res.y, hardcoded_epsilon);
}

vec4 HHLP_GetBilinearTextureSample(sampler2D in_sampler, vec2 in_coord, vec4 in_size)
{
   vec2 uv = in_coord * in_size.xy - 0.5; // Shift by 0.5 since the texel sampling points are in the texel center.
   vec2 a = fract(uv);
   vec2 tex = (floor(uv) + 0.5) * in_size.zw; // Build a sampling point which is in the center of the texel.

   // Sample the bilinear footprint.
   vec4 t0 = textureLodOffset(in_sampler, tex, 0.0, ivec2(0, 0));
   vec4 t1 = textureLodOffset(in_sampler, tex, 0.0, ivec2(1, 0));
   vec4 t2 = textureLodOffset(in_sampler, tex, 0.0, ivec2(0, 1));
   vec4 t3 = textureLodOffset(in_sampler, tex, 0.0, ivec2(1, 1));

   // Bilinear filter.
   vec4 result = mix(mix(t0, t1, a.x), mix(t2, t3, a.x), a.y);

   return result;
}