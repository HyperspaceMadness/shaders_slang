/*   
hsm-mega-screen-scale

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
float HHLP_QuadraticBezier (float x, vec2 a){
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

float HHLP_GetDistanceToLine(float x1, float y1, 
                       float a, float b,  
                       float c) 
{ 
    float d = abs((a * x1 + b * y1 + c)) /  
              (sqrt(a * a + b * b));
    return d; 
}

vec4 HHLP_Linearize(vec4 in_color)
{
	return pow(in_color, vec4(2.2));
}

vec4 HHLP_Delinearize(vec4 in_color)
{
	return pow(in_color, vec4(1.0 / 2.2));
}

