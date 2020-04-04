
// #pragma parameter convergence_offset_x_r "Convergence - Offset X Red" 0.0 -4.0 4.0 0.05
// #define convergence_offset_x_r global.convergence_offset_x_r
// #pragma parameter convergence_offset_x_g "Convergence - Offset X Green" 0.0 -4.0 4.0 0.05
// #define convergence_offset_x_g global.convergence_offset_x_g
// #pragma parameter convergence_offset_x_b "Convergence - Offset X Blue" 0.0 -4.0 4.0 0.05
// #define convergence_offset_x_b global.convergence_offset_x_b
// #pragma parameter convergence_offset_y_r "Convergence - Offset Y Red" 0.0 -2.0 2.0 0.05
// #define convergence_offset_y_r global.convergence_offset_y_r
// #pragma parameter convergence_offset_y_g "Convergence - Offset Y Green" 0.0 -2.0 2.0 0.05
// #define convergence_offset_y_g global.convergence_offset_y_g
// #pragma parameter convergence_offset_y_b "Convergence - Offset Y Blue" 0.0 -2.0 2.0 0.05
// #define convergence_offset_y_b global.convergence_offset_y_b

    static const float convergence_offset_x_r = clamp(convergence_offsets_r_static.x, -4.0, 4.0);
    static const float convergence_offset_x_g = clamp(convergence_offsets_g_static.x, -4.0, 4.0);
    static const float convergence_offset_x_b = clamp(convergence_offsets_b_static.x, -4.0, 4.0);
    static const float convergence_offset_y_r = clamp(convergence_offsets_r_static.y, -4.0, 4.0);
    static const float convergence_offset_y_g = clamp(convergence_offsets_g_static.y, -4.0, 4.0);
    static const float convergence_offset_y_b = clamp(convergence_offsets_b_static.y, -4.0, 4.0);


#include "..\..\HyperspaceMadness\hsm-mega-screen-scale-params-functions.inc"

void main()
{
   gl_Position = global.MVP * Position;
   tex_uv = TexCoord;

   // Added
   tex_uv = HMSS_GetScreenVTexCoord(tex_uv);

    // vec2 ctr_mirror_coord = tex_uv;
	// if (abs(ctr_mirror_coord.x) > 0.5)
	// {
	// 	ctr_mirror_coord.x = ctr_mirror_coord.x - 2 * sign(ctr_mirror_coord.x) * (abs(ctr_mirror_coord.x) - 0.5);
	// }
	// if (abs(ctr_mirror_coord.y) > 0.5)
	// {
	// 	ctr_mirror_coord.y = ctr_mirror_coord.y - 2 * sign(ctr_mirror_coord.y) * (abs(ctr_mirror_coord.y) - 0.5);
	// }

    // tex_uv = ctr_mirror_coord;