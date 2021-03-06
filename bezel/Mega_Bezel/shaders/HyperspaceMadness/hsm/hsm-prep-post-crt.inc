#pragma stage vertex

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 0) out vec2 vTexCoord;
layout(location = 7) out vec2 UNFLIPPED_VIEWPORT_COORD;

void main()
{
	gl_Position = global.MVP * Position;
	vTexCoord = TexCoord * 1.00001;

	UNFLIPPED_VIEWPORT_COORD = vTexCoord * 1.0001;

	if (HSM_FLIP_VIEWPORT_VERTICAL > 0.5)
		vTexCoord.y =  1 - vTexCoord.y;
}

#pragma stage fragment

layout(location = 0) in vec2 vTexCoord;
layout(location = 7) in vec2 UNFLIPPED_VIEWPORT_COORD;

layout(location = 0) out vec4 FragColor;

layout(set = 0, binding = 1) uniform sampler2D Source;
layout(set = 0, binding = 2) uniform sampler2D InfoCachePass;
layout(set = 0, binding = 3) uniform sampler2D ColoredGelImage;
layout(set = 0, binding = 4) uniform sampler2D TubeStaticReflectionImage;
layout(set = 0, binding = 5) uniform sampler2D BackgroundImage;
layout(set = 0, binding = 6)  uniform sampler2D BackgroundVertImage;
layout(set = 0, binding = 7) uniform sampler2D IntroPass;


void main()
{
	HSM_UpdateGlobalScreenValuesFromCache(InfoCachePass, vTexCoord);

	vec2 screen_curved_coord = HSM_GetCurvedCoord(SCREEN_COORD, 1, SCREEN_ASPECT);

	FragColor = texture(Source, UNFLIPPED_VIEWPORT_COORD);
	FragColor = HSM_GetPostCrtPreppedColor(FragColor, vTexCoord, screen_curved_coord, IntroPass, false, ColoredGelImage, TubeStaticReflectionImage, BackgroundImage, BackgroundVertImage);
}