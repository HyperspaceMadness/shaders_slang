#version 450

/*
   Average Luminance Shader, original by adapted by HyperspaceMadness, 
   Original by guest(r) - guest.r@gmail.com

   Average Luminance is written to the alpha channel so it can be dropped
   into the shader chain without affecting the visible image

   This is expected to be placed after a linearize pass
*/

layout(push_constant) uniform Push
{
	uint FrameCount;
	vec4 SourceSize;
} params;

#define SourceSize params.SourceSize

layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
} global;

#pragma stage vertex
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 0) out vec2 vTexCoord;

void main()
{
   gl_Position = global.MVP * Position;
   vTexCoord = TexCoord * 1.0001;
}

#pragma stage fragment
layout(location = 0) in vec2 vTexCoord;
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 2) uniform sampler2D Source;

void main()
{
	// Don't write pixel if within bounds
	// if (vTexCoord.x > 0.2 || vTexCoord.y > 0.2) discard;
	
	float m = max(log2(SourceSize.x), log2(SourceSize.y));
	m = max(m - 1.0, 1.0);
	
	float ltotal = 0.0;
	
	float num_samples = 5;
	float sample_dist = 1 / (num_samples - 1);
	vec4 tex_sample = vec4(0);
	for (float i = 0; i <= num_samples; i++)
	{
		for (float j = 0; j <= num_samples; j++)
		{
			tex_sample = textureLod(Source, vec2(sample_dist * i, sample_dist * j), m);
			ltotal += max(0.0, (tex_sample.r + tex_sample.g + tex_sample.g) / 3);
			// ltotal += max(0.0, length(tex_sample.rgb));
			
		}
	}
	ltotal /= num_samples * num_samples;
	
	ltotal = pow(0.577350269 * ltotal, 0.6);
	
	vec4 source_sample = texture(Source, vTexCoord);

	FragColor = vec4(source_sample.rgb, ltotal);
}