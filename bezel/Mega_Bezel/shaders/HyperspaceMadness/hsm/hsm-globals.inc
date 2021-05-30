/*   
hsm-globals-and-advanced-params.inc

Globals for screen scale and bezel
*/

layout(std140, set = 0, binding = 0) uniform UBO
{
	mat4 MVP;
    vec4 SourceSize;
	vec4 OriginalSize;
	vec4 OutputSize;
	vec4 FinalViewportSize;
	vec4 internal1Size;
	vec4 ReduceCoreRezPassSize;
	uint FrameCount;

	float HSM_RESOLUTION_DEBUG_ON;
	float HSM_FLIP_VIEWPORT_VERTICAL;
	float HSM_FLIP_CORE_VERTICAL;
	float HSM_FLIP_CORE_HORIZONTAL;
	
	float HSM_ROTATE_CORE_IMAGE;
	float HSM_ASPECT_RATIO_ORIENTATION;
	float HSM_ASPECT_RATIO_MODE;
	float HSM_ASPECT_RATIO_EXPLICIT;
	float HSM_INT_SCALE_MODE;
	float HSM_NON_INTEGER_SCALE;
	float USE_IMAGE_FOR_PLACEMENT;
	float HSM_NON_INTEGER_SCALE_OFFSET;
	float HSM_SNAP_TO_INT_SCALE_TOLERANCE;
    float HSM_INT_SCALE_MULTIPLE_OFFSET;
	float HSM_INT_SCALE_MULTIPLE_OFFSET_LONG;
	float HSM_INT_SCALE_BORDER_MIN_HEIGHT;
	float HSM_SCREEN_POSITION_X;
	float HSM_SCREEN_POSITION_Y;

	float HSM_CORE_RES_SAMPLING_MULT_SCANLINE_DIR;
	float HSM_CORE_RES_SAMPLING_MULT_OPPOSITE_DIR;

	float HSM_SCANLINE_DIRECTION;
	float HSM_INTERLACE_MODE;
	float HSM_INTERLACE_TRIGGER_RES;
	float HSM_INTERLACE_EFFECT_SMOOTHNESS;
	float HSM_INTERLACE_SCANLINE_EFFECT;
	float GDV_INTERLACE_SCANLINE_SATURATION;
	float HSM_DOWNSAMPLE_BLUR;
	float HSM_FAKE_SCANLINE_OPACITY;
	float HSM_FAKE_SCANLINE_BRIGHTNESS_CUTOFF;

	float HSM_DUALSCREEN_MODE;
	float HSM_DUALSCREEN_CORE_IMAGE_SPLIT_MODE;
	float HSM_DUALSCREEN_CORE_IMAGE_SWAP_SCREENS;
	float HSM_DUALSCREEN_CORE_IMAGE_SPLIT_OFFSET;
	float HSM_DUALSCREEN_2ND_SCREEN_SIDES_CROP;
	float HSM_DUALSCREEN_VIEWPORT_SPLIT_LOCATION;
	float HSM_DUALSCREEN_SHIFT_POSITION_WITH_SCALE;
	float HSM_DUALSCREEN_2ND_SCREEN_INDEPENDENT_SCALE;
	float HSM_DUALSCREEN_2ND_SCREEN_SCALE_OFFSET;
	float HSM_DUALSCREEN_POSITION_OFFSET_BETWEEN_SCREENS;
	float HSM_DUALSCREEN_2ND_SCREEN_ASPECT_RATIO_MODE;
	float HSM_DUALSCREEN_2ND_SCREEN_POS_X;
	float HSM_DUALSCREEN_2ND_SCREEN_POS_Y;

	float HSM_CROP_PERCENT_TOP;
	float HSM_CROP_PERCENT_BOTTOM;
	float HSM_CROP_PERCENT_LEFT;
	float HSM_CROP_PERCENT_RIGHT;
	float HSM_CROP_BLACK_THRESHOLD;
	float HSM_CROP_MODE;

	float HSM_CURVATURE_MODE;
	float HSM_CURVATURE_3D_RADIUS;
	float HSM_CURVATURE_3D_VIEW_DIST;
	float HSM_CURVATURE_3D_TILT_ANGLE_X;
	float HSM_CURVATURE_3D_TILT_ANGLE_Y;

	float HSM_CURVATURE_2D_SCALE_LONG_AXIS;
	float HSM_CURVATURE_2D_SCALE_SHORT_AXIS;
	float HSM_CURVATURE_POST_SCALE_X;
	float HSM_CURVATURE_POST_SCALE_Y;

	float HSM_COLOR_BLACK_LEVEL;
	float HSM_COLOR_NEGATIVE_CROP_BRIGHTNESS;
	float HSM_GAMMA_IN_LINEARIZE;
float HSM_GAMMA_OUT_CRT;
float HSM_POST_CRT_BRIGHTNESS;
	float HSM_CRT_ORIGINAL_AB_COMPARE_ON;
	float HSM_CRT_ORIGINAL_AB_COMPARE_SPLIT_POSITION;

	float HSM_ANTI_FLICKER_ON;
	float HSM_ANTI_FLICKER_THRESHOLD;
	
	float HSM_PHOSPHOR_PERSISTENCE_BLEND;
	float HSM_PHOSPHOR_PERSISTENCE_RED;
	float HSM_PHOSPHOR_PERSISTENCE_GREEN;
	float HSM_PHOSPHOR_PERSISTENCE_BLUE;

	float HSM_SCREEN_CORNER_RADIUS;
	float HSM_SCREEN_EDGE_SHARPNESS;
	float HSM_SCREEN_VIGNETTE;
	float HSM_SCREEN_VIGNETTE_IN_REFLECTION;
	float HSM_SCREEN_REFLECTION_SCALE;
	float HSM_SCREEN_REFLECTION_POS_X;
	float HSM_SCREEN_REFLECTION_POS_Y;

	float HSM_TUBE_COLORED_GEL_IMAGE_MULTIPLY_AMOUNT;
	float HSM_TUBE_COLORED_GEL_IMAGE_NORMAL_AMOUNT;
	float HSM_TUBE_COLORED_GEL_IMAGE_ADDITIVE_AMOUNT;
	float HSM_TUBE_STATIC_REFLECTION_IMAGE_OPACITY;
	float HSM_TUBE_STATIC_REFLECTION_IMAGE_SCALE;
	float HSM_TUBE_STATIC_REFLECTION_IMAGE_DITHERING_SAMPLES;
	float HSM_TUBE_BLACK_EDGE_THICKNESS;
	float HSM_TUBE_BLACK_EDGE_CURVATURE_SCALE;

	float HSM_BZL_SCALE_OFFSET;
	float HSM_BZL_INNER_CURVATURE_SCALE;
	float HSM_BZL_USE_INDEPENDENT_SCALE;
	float HSM_BZL_INDEPENDENT_SCALE;
	float HSM_BZL_USE_INDEPENDENT_CURVATURE;
	float HSM_BZL_INDEPENDENT_CURVATURE_SCALE_LONG_AXIS;
	float HSM_BZL_INDEPENDENT_CURVATURE_SCALE_SHORT_AXIS;
	float HSM_BZL_WIDTH;
	float HSM_BZL_HEIGHT;
	float HSM_BZL_OUTER_CURVATURE_SCALE;
	float HSM_BZL_INNER_EDGE_THICKNESS;
	float HSM_BZL_INNER_EDGE_SHARPNESS;
	float HSM_BZL_INNER_CORNER_RADIUS_SCALE;
	float HSM_BZL_OUTER_CORNER_RADIUS_SCALE;
	float HSM_BZL_NOISE;

	// Generated Bezel
	float HSM_BZL_COLOR_HUE;
	float HSM_BZL_COLOR_SATURATION;
	float HSM_BZL_COLOR_VALUE;
	float HSM_BZL_BRIGHTNESS;
	float HSM_BZL_HIGHLIGHT;

	// Generated Frame
	float HSM_FRM_OUTER_CURVATURE_SCALE;
	float HSM_FRM_THICKNESS;
	float HSM_FRM_THICKNESS_SCALE_X;
	float HSM_FRM_OUTER_POS_Y;
	float HSM_FRM_INNER_EDGE_THICKNESS;
	float HSM_FRM_INNER_CORNER_RADIUS_SCALE;
	float HSM_FRM_OUTER_EDGE_THICKNESS;
	float HSM_FRM_OUTER_EDGE_SHADING;
	float HSM_FRM_OUTER_CORNER_RADIUS;
	float HSM_BZL_OUTER_POSITION_Y;
	float HSM_FRM_SHADOW_OPACITY;
	float HSM_FRM_SHADOW_WIDTH;

	// Reflection
	float HSM_REFLECT_MASK_MODE;

	float HSM_REFLECT_GLOBAL_AMOUNT;
	float HSM_REFLECT_GLOBAL_GAMMA_ADJUST;

	float HSM_REFLECT_BEZEL_INNER_EDGE_AMOUNT;
	float HSM_REFLECT_BEZEL_INNER_EDGE_FULLSCREEN_GLOW;
	float HSM_REFLECT_FRAME_INNER_EDGE_AMOUNT;
	float HSM_REFLECT_FRAME_INNER_EDGE_SHARPNESS;
	float HSM_REFLECT_DIRECT_AMOUNT;
	float HSM_REFLECT_DIFFUSED_AMOUNT;
	float HSM_REFLECT_FULLSCREEN_GLOW;
	float HSM_REFLECT_FULLSCREEN_GLOW_GAMMA;

	float HSM_REFLECT_FADE_AMOUNT;
	float HSM_REFLECT_RADIAL_FADE_WIDTH;
	float HSM_REFLECT_RADIAL_FADE_HEIGHT;

	float HSM_REFLECT_LATERAL_OUTER_FADE_POSITION;
	float HSM_REFLECT_LATERAL_OUTER_FADE_DISTANCE;
	float HSM_REFLECT_VIGNETTE_AMOUNT;

	float HSM_REFLECT_CORNER_FADE;
	float HSM_REFLECT_CORNER_INNER_SPREAD;
	float HSM_REFLECT_CORNER_OUTER_SPREAD;
	float HSM_REFLECT_CORNER_ROTATION_OFFSET_TOP;
	float HSM_REFLECT_CORNER_ROTATION_OFFSET_BOTTOM;
	float HSM_REFLECT_CORNER_SPREAD_FALLOFF;
	float HSM_REFLECT_CORNER_FADE_DISTANCE;

	float HSM_REFLECT_NOISE_AMOUNT;
	float HSM_REFLECT_NOISE_SAMPLES;
	float HSM_REFLECT_NOISE_SAMPLE_DISTANCE;

	// Blur Stuff
	float HSM_REFLECT_BLUR_NUM_SAMPLES;
	float HSM_REFLECT_BLUR_FALLOFF_DISTANCE;
	float HSM_REFLECT_BLUR_MIN;
	float HSM_REFLECT_BLUR_MAX;
	
	float HSM_REFLECT_MASK_IMG_AMOUNT;
	float HSM_REFLECT_IS_LAST_PASS;

	float HSM_GLASS_BORDER_ON;

	float HSM_STATIC_LAYERS_GAMMA;
	float HSM_STANDARD_IMG_ASPECT_RATIO_MODE;
	float HSM_STANDARD_IMG_ASPECT_RATIO_EXPLICIT;
	float HSM_STANDARD_BG_SHOW_OVER_SCREEN;
	float HSM_STANDARD_DECAL_SCALE_WITH_FRAME;
	float HSM_STANDARD_TOP_SCALE_WITH_FRAME;

	// Night Lighting
	float HSM_NIGHT_OPACITY;
	float HSM_NIGHT_SCALE;
	float HSM_NIGHT_MIRROR_HORZ;
	float HSM_NIGHT_MIRROR_VERT;
	float HSM_NIGHT_SATURATION;
	float HSM_NIGHT_HUE;
	float HSM_NIGHT_VALUE;
	float HSM_NIGHT_DITHERING_SAMPLES;

	float HSM_BG_LAYER_ORDER;
	float HSM_VIEWPORT_VIGNETTE_LAYER_ORDER;
	float HSM_CRT_LAYER_ORDER;
	float HSM_BZL_IMG_LAYER_ORDER;
	float HSM_CAB_GLASS_LAYER_ORDER;
	float HSM_BZL_LAYER_ORDER;
	float HSM_FRM_LAYER_ORDER;
	float HSM_DECAL_LAYER_ORDER;
	float HSM_REFLECT_LAYER_ORDER;
	float HSM_LED_LAYER_ORDER;
	float HSM_TOP_LAYER_ORDER;

	// Image Background
	float HSM_VIEWPORT_VIGNETTE_OPACITY;
	float HSM_VIEWPORT_VIGNETTE_MASK_MODE;
	float HSM_VIEWPORT_VIGNETTE_CUTOUT_MODE;
	float HSM_VIEWPORT_VIGNETTE_SCALE_MODE;
	float HSM_VIEWPORT_VIGNETTE_SCALE;
	float HSM_VIEWPORT_VIGNETTE_SCALE_X;
	float HSM_VIEWPORT_VIGNETTE_POS_X;
float HSM_VIEWPORT_VIGNETTE_POS_Y;

	float HSM_BG_OPACITY;
	float HSM_BG_BRIGHTNESS;
	float HSM_BG_APPLY_ADJUSTMENT;
	float HSM_BG_BLEND_MODE;
	float HSM_BG_SOURCE_MATTE_TYPE;
	float HSM_BG_MASK_MODE;
	float HSM_BG_CUTOUT_MODE;
	float HSM_BG_TEXTURE_ASPECT_MODE;
	float HSM_BG_EXPLICIT_TEXTURE_ASPECT;
	float HSM_BG_SCALE_MODE;
	float HSM_BG_SCALE_KEEP_ASPECT;
	float HSM_BG_SCALE;
	float HSM_BG_SCALE_X;
	float HSM_BG_POS_X;
float HSM_BG_POS_Y;
	float HSM_BG_MIRROR_WRAP;

	// CRT Screen
	float HSM_CRT_SCREEN_BLEND_MODE;

	// Tube Reflection
	float HSM_CAB_GLASS_OPACITY;
	float HSM_CAB_GLASS_BRIGHTNESS;
	float HSM_CAB_GLASS_BLEND_MODE;
	float HSM_CAB_GLASS_SOURCE_MATTE_TYPE;
	float HSM_BZL_INNER_EDGE_SHADOW;
	float HSM_CAB_GLASS_MASK_MODE;
	float HSM_CAB_GLASS_CUTOUT_MODE;
	float HSM_CAB_GLASS_TEXTURE_ASPECT_MODE;
	float HSM_CAB_GLASS_EXPLICIT_TEXTURE_ASPECT;
	float HSM_CAB_GLASS_SCALE_MODE;
	float HSM_CAB_GLASS_SCALE_KEEP_ASPECT;
	float HSM_CAB_GLASS_SCALE;
	float HSM_CAB_GLASS_SCALE_X;
	float HSM_CAB_GLASS_POS_X;
float HSM_CAB_GLASS_POS_Y;

	// Image Bezel
	float HSM_BZL_IMG_OPACITY;
	float HSM_BZL_IMG_HUE;
	float HSM_BZL_IMG_SATURATION;
	float HSM_BZL_IMG_BRIGHTNESS;
	float HSM_BZL_IMG_BLEND_MODE;
	float HSM_BZL_SOURCE_MATTE_TYPE;
	float HSM_BZL_IMG_MASK_MODE;
	float HSM_BZL_IMG_CUTOUT_MODE;
	float HSM_BZL_IMG_TEXTURE_ASPECT_MODE;
	float HSM_BZL_IMG_EXPLICIT_TEXTURE_ASPECT;
	float HSM_BZL_IMG_SCALE_MODE;
	float HSM_BZL_IMG_SCALE_KEEP_ASPECT;
	float HSM_BZL_IMG_SCALE;
	float HSM_BZL_IMG_SCALE_X;
	float HSM_BZL_IMG_POS_X;
float HSM_BZL_IMG_POS_Y;
	float HSM_BZL_IMG_USE_CURVATURE;
	float HSM_REFLECT_MASK_SCALE_MODE;

	// Generated Bezel & Frame
	float HSM_BZL_OPACITY;
	float HSM_BZL_BLEND_MODE;
	float HSM_FRM_OPACITY;
	float HSM_FRM_BLEND_MODE;
	float HSM_FRM_TEXTURE_OPACITY;
	float HSM_FRM_TEXTURE_BLEND_MODE;

	// Cutout
	float HSM_CUTOUT_SCALE_MODE;
	float HSM_CUTOUT_SCALE;
	float HSM_CUTOUT_SCALE_X;
	float HSM_CUTOUT_CORNER_RADIUS;
	float HSM_CUTOUT_POS_X;
float HSM_CUTOUT_POS_Y;
	float HSM_REFLECT_BLEND_MODE;

	// Decal
	float HSM_DECAL_OPACITY;
	float HSM_DECAL_BLEND_MODE;
	float HSM_DECAL_SOURCE_MATTE_TYPE;
	float HSM_STANDARD_DECAL_SHOW_UNDER_FRAME;
	float HSM_DECAL_MASK_MODE;
	float HSM_DECAL_TEXTURE_ASPECT_MODE;
	float HSM_DECAL_EXPLICIT_TEXTURE_ASPECT;
	float HSM_DECAL_SCALE_MODE;
	float HSM_DECAL_SCALE_KEEP_ASPECT;
	float HSM_DECAL_SCALE;
	float HSM_DECAL_SCALE_X;
	float HSM_DECAL_POS_X;
float HSM_DECAL_POS_Y;
	float HSM_DECAL_CUTOUT_MODE;

	// LED
	float HSM_LED_OPACITY;
	float HSM_LED_BLEND_MODE;
	float HSM_LED_SOURCE_MATTE_TYPE;
	float HSM_STANDARD_LED_SHOW_OVER_SCREEN;
	float HSM_LED_MASK_MODE;
	float HSM_LED_CUTOUT_MODE;
	float HSM_LED_TEXTURE_ASPECT_MODE;
	float HSM_LED_EXPLICIT_TEXTURE_ASPECT;
	float HSM_LED_SCALE_MODE;
	float HSM_LED_SCALE_KEEP_ASPECT;
	float HSM_LED_SCALE;
	float HSM_LED_SCALE_X;
	float HSM_LED_POS_X;
float HSM_LED_POS_Y;


	// Top Image
	float HSM_TOP_OPACITY;
	float HSM_TOP_BLEND_MODE;
	float HSM_TOP_SOURCE_MATTE_TYPE;
	float HSM_TOP_MASK_MODE;
	float HSM_TOP_CUTOUT_MODE;

	float HSM_TOP_TEXTURE_ASPECT_MODE;
	float HSM_TOP_EXPLICIT_TEXTURE_ASPECT;
	float HSM_TOP_SCALE_MODE;
	float HSM_TOP_SCALE_KEEP_ASPECT;
	float HSM_TOP_SCALE;
	float HSM_TOP_SCALE_X;
	float HSM_TOP_POS_X;
float HSM_TOP_POS_Y;	
	float HSM_TOP_MIRROR_WRAP;
	float HSM_LAYERING_DEBUG_MASK_MODE;

	float HSM_INTRO_LOGO_BLEND_MODE;
	float HSM_INTRO_LOGO_FLIP_VERTICAL;
	float HSM_INTRO_NOISE_BLEND_MODE;
	float HSM_INTRO_NOISE_HOLD;
	float HSM_INTRO_NOISE_FADE_OUT;
	float HSM_INTRO_SOLID_BLACK_HOLD;
	float HSM_INTRO_SOLID_BLACK_FADE_OUT;
	float HSM_INTRO_SOLID_COLOR_BLEND_MODE;
	float HSM_INTRO_LOGO_OVER_SOLID_COLOR;
	float HSM_INTRO_LOGO_PLACEMENT;
	float HSM_INTRO_LOGO_HEIGHT;
	float HSM_INTRO_LOGO_RES_X;
	float HSM_INTRO_LOGO_RES_Y;
	float HSM_INTRO_WHEN_TO_SHOW;
	float HSM_INTRO_SPEED;
	float HSM_INTRO_LOGO_WAIT;
	float HSM_INTRO_LOGO_FADE_IN;
	float HSM_INTRO_LOGO_HOLD;
	float HSM_INTRO_LOGO_FADE_OUT;
	float HSM_INTRO_SOLID_COLOR_HUE;
	float HSM_INTRO_SOLID_COLOR_SAT;
	float HSM_INTRO_SOLID_COLOR_VALUE;
	float HSM_INTRO_SOLID_COLOR_HOLD;
	float HSM_INTRO_SOLID_COLOR_FADE_OUT;


} global;

/////////////// DEFINES ///////////////

#define DEFAULT_TUBE_SCALE_V 0.82987
#define DEFAULT_BEZEL_SCALE_V 0.91159
#define DEFAULT_SCREEN_CORNER_RADIUS 10

int INFOCACHE_MAX_INDEX = 4;

float BLEND_MODE_OFF = 0;
float BLEND_MODE_NORMAL = 1;
float BLEND_MODE_ADD = 2;
float BLEND_MODE_MULTIPLY = 3;

float SOURCE_MATTE_PREMULTIPLIED = 0;
float SOURCE_MATTE_WHITE = 1;
float SOURCE_MATTE_NONE = 2;

float SCREEN_MASK = 0;
float TUBE_MASK = 0;
float BEZEL_MASK = 0;
float INSIDE_BEZEL_MASK = 0;
float OUTSIDE_TUBE_MASK_FOR_IMAGE = 0;
float FRAME_MASK = 0;
float FRAME_MASK_FOR_IMAGE = 0;
float OUTSIDE_BEZEL_MASK = 0;
float OUTSIDE_FRAME_MASK_FOR_IMAGE = 0;
float OUTSIDE_FRAME_MASK = 0;
float CUTOUT_MASK = 0;

float SCREEN_INDEX = 1;

float SCREEN_ASPECT = 1;
vec2 SCREEN_SCALE = vec2(1);
vec2 TUBE_SCALE = vec2(1);
vec2 FRAME_SCALE = vec2(1);
vec2 SCREEN_POS_OFFSET = vec2(0.15);
vec2 SCREEN_COORD = vec2(0.5);
float AVERAGE_LUMA = 0;
float USE_VERTICAL_SCANLINES = 0;

vec2 ROTATED_CORE_ORIGINAL_SIZE = vec2(1);

vec2 ROTATED_RAW_ORIGINAL_SIZE = vec2(1);

vec2 CROPPED_ROTATED_ORIGINAL_SIZE_WITH_CORE_RES_MULT = vec2(1);
vec2 CROPPED_ROTATED_ORIGINAL_SIZE = vec2(1);
vec2 SAMPLE_AREA_START_RAW_PIXEL_COORD = vec2(1);

// float SCREEN_ASPECT_2nd = 1;
// vec2 SCREEN_SCALE_2nd = vec2(1);
// vec2 CROPPED_ROTATED_ORIGINAL_SIZE_2nd = vec2(1);
// vec2 CROPPED_ROTATED_ORIGINAL_SIZE_WITH_CORE_RES_MULT_2nd = vec2(1);
// vec2 SAMPLE_AREA_START_RAW_PIXEL_COORD_2nd = vec2(1);