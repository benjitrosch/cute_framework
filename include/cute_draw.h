/*
	Cute Framework
	Copyright (C) 2023 Randy Gaul https://randygaul.github.io/

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	   claim that you wrote the original software. If you use this software
	   in a product, an acknowledgment in the product documentation would be
	   appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	   misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CUTE_DRAW_H
#define CUTE_DRAW_H

#include "cute_defines.h"
#include "cute_math.h"
#include "cute_result.h"
#include "cute_graphics.h"
#include "cute_sprite.h"

//--------------------------------------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @function cf_draw_sprite
 * @category draw
 * @brief    Draws a sprite.
 * @param    sprite     The sprite.
 * @related  cf_draw_sprite cf_draw_quad camera_look_at cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_sprite(const CF_Sprite* sprite);

/**
 * @function cf_draw_quad
 * @category draw
 * @brief    Draws a quad wireframe.
 * @param    bb         The AABB (Axis-Aligned Bounding Box) to draw a quad over.
 * @param    thickness  The thickness of each line to draw.
 * @related  cf_draw_quad cf_draw_quad2 cf_draw_quad3 cf_draw_quad_fill cf_draw_quad_fill2 cf_draw_quad_fill3 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_quad(CF_Aabb bb, float thickness);

/**
 * @function cf_draw_quad2
 * @category draw
 * @brief    Draws a quad wireframe.
 * @param    p0         A corner of the quad.
 * @param    p1         A corner of the quad.
 * @param    p2         A corner of the quad.
 * @param    p3         A corner of the quad.
 * @param    thickness  The thickness of each line to draw.
 * @remarks  All points `p0` through `p3` are encouraged to be in counter-clockwise order.
 * @related  cf_draw_quad cf_draw_quad2 cf_draw_quad3 cf_draw_quad_fill cf_draw_quad_fill2 cf_draw_quad_fill3 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_quad2(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_V2 p3, float thickness);

/**
 * @function cf_draw_quad3
 * @category draw
 * @brief    Draws a quad wireframe.
 * @param    p0         A corner of the quad.
 * @param    p1         A corner of the quad.
 * @param    p2         A corner of the quad.
 * @param    p3         A corner of the quad.
 * @param    thickness  The thickness of each line to draw.
 * @param    c0         The color of a corner of the quad.
 * @param    c1         The color of a corner of the quad.
 * @param    c2         The color of a corner of the quad.
 * @param    c3         The color of a corner of the quad.
 * @remarks  All points `p0` through `p3` are encouraged to be in counter-clockwise order.
 * @related  cf_draw_quad cf_draw_quad2 cf_draw_quad3 cf_draw_quad_fill cf_draw_quad_fill2 cf_draw_quad_fill3 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_quad3(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_V2 p3, float thickness, CF_Color c0, CF_Color c1, CF_Color c2, CF_Color c3);

/**
 * @function cf_draw_quad_fill
 * @category draw
 * @brief    Draws a quad.
 * @param    bb         The AABB (Axis-Aligned Bounding Box) to draw a quad over.
 * @related  cf_draw_quad cf_draw_quad2 cf_draw_quad3 cf_draw_quad_fill cf_draw_quad_fill2 cf_draw_quad_fill3 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_quad_fill(CF_Aabb bb);

/**
 * @function cf_draw_quad_fill2
 * @category draw
 * @brief    Draws a quad.
 * @param    p0         A corner of the quad.
 * @param    p1         A corner of the quad.
 * @param    p2         A corner of the quad.
 * @param    p3         A corner of the quad.
 * @remarks  All points `p0` through `p3` are encouraged to be in counter-clockwise order.
 * @related  cf_draw_quad cf_draw_quad2 cf_draw_quad3 cf_draw_quad_fill cf_draw_quad_fill2 cf_draw_quad_fill3 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_quad_fill2(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_V2 p3);

/**
 * @function cf_draw_quad_fill3
 * @category draw
 * @brief    Draws a quad wireframe.
 * @param    p0         A corner of the quad.
 * @param    p1         A corner of the quad.
 * @param    p2         A corner of the quad.
 * @param    p3         A corner of the quad.
 * @param    c0         The color of a corner of the quad.
 * @param    c1         The color of a corner of the quad.
 * @param    c2         The color of a corner of the quad.
 * @param    c3         The color of a corner of the quad.
 * @remarks  All points `p0` through `p3` are encouraged to be in counter-clockwise order.
 * @related  cf_draw_quad cf_draw_quad2 cf_draw_quad3 cf_draw_quad_fill cf_draw_quad_fill2 cf_draw_quad_fill3 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_quad_fill3(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_V2 p3, CF_Color c0, CF_Color c1, CF_Color c2, CF_Color c3);

/**
 * @function cf_draw_circle
 * @category draw
 * @brief    Draws a circle wireframe.
 * @param    p          Center of the circle.
 * @param    r          Radius of the circle.
 * @param    iters      Number of edges used for the circle. More looks smoother, but renders slower.
 * @param    thickness  The thickness of each line to draw.
 * @related  cf_draw_circle cf_draw_circle_fill cf_draw_circle_arc cf_draw_circle_arc_fill cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_circle(CF_V2 p, float r, int iters, float thickness);

/**
 * @function cf_draw_circle_fill
 * @category draw
 * @brief    Draws a circle.
 * @param    p          Center of the circle.
 * @param    r          Radius of the circle.
 * @param    iters      Number of edges used for the circle. More looks smoother, but renders slower.
 * @related  cf_draw_circle cf_draw_circle_fill cf_draw_circle_arc cf_draw_circle_arc_fill cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_circle_fill(CF_V2 p, float r, int iters);

/**
 * @function cf_draw_circle_arc
 * @category draw
 * @brief    Draws an arc of a circle wireframe.
 * @param    p              Center of the arc.
 * @param    center_of_arc  Radius of the circle.
 * @param    range          Angle the arc covers.
 * @param    iters          Number of edges used for the circle. More looks smoother, but renders slower.
 * @param    thickness      The thickness of each line to draw.
 * @related  cf_draw_circle cf_draw_circle_fill cf_draw_circle_arc cf_draw_circle_arc_fill cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_circle_arc(CF_V2 p, CF_V2 center_of_arc, float range, int iters, float thickness);

/**
 * @function cf_draw_circle_arc_fill
 * @category draw
 * @brief    Draws an arc of a circle, like a pie-slice.
 * @param    p              Center of the arc.
 * @param    center_of_arc  Radius of the circle.
 * @param    range          Angle the arc covers.
 * @param    iters          Number of edges used for the circle. More looks smoother, but renders slower.
 * @related  cf_draw_circle cf_draw_circle_fill cf_draw_circle_arc cf_draw_circle_arc_fill cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_circle_arc_fill(CF_V2 p, CF_V2 center_of_arc, float range, int iters);

/**
 * @function cf_draw_capsule
 * @category draw
 * @brief    Draws a capsule wireframe.
 * @param    p0         An endpoint of the interior line-segment of the capsule (the center of one end-cap).
 * @param    p1         An endpoint of the interior line-segment of the capsule (the center of one end-cap).
 * @param    r          Radius of the capsule.
 * @param    iters      Number of edges used for the circle-caps. More looks smoother, but renders slower.
 * @param    thickness  The thickness of each line to draw.
 * @related  cf_draw_capsule cf_draw_capsule_fill cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_capsule(CF_V2 p0, CF_V2 p1, float r, int iters, float thickness);

/**
 * @function cf_draw_capsule_fill
 * @category draw
 * @brief    Draws a capsule.
 * @param    p0         An endpoint of the interior line-segment of the capsule (the center of one end-cap).
 * @param    p1         An endpoint of the interior line-segment of the capsule (the center of one end-cap).
 * @param    r          Radius of the capsule.
 * @param    iters      Number of edges used for the circle-caps. More looks smoother, but renders slower.
 * @related  cf_draw_capsule cf_draw_capsule_fill cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_capsule_fill(CF_V2 p0, CF_V2 p1, float r, int iters);

/**
 * @function cf_draw_tri
 * @category draw
 * @brief    Draws a triangle wireframe.
 * @param    p0         A corner of the triangle.
 * @param    p1         A corner of the triangle.
 * @param    p2         A corner of the triangle.
 * @param    thickness  The thickness of each line to draw.
 * @related  cf_draw_tri cf_draw_tri_fill cf_draw_tri_fill2 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_tri(CF_V2 p0, CF_V2 p1, CF_V2 p2, float thickness);

/**
 * @function cf_draw_tri_fill
 * @category draw
 * @brief    Draws a triangle.
 * @param    p0         A corner of the triangle.
 * @param    p1         A corner of the triangle.
 * @param    p2         A corner of the triangle.
 * @related  cf_draw_tri cf_draw_tri_fill cf_draw_tri_fill2 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_tri_fill(CF_V2 p0, CF_V2 p1, CF_V2 p2);

/**
 * @function cf_draw_tri_fill2
 * @category draw
 * @brief    Draws a triangle.
 * @param    p0         A corner of the triangle.
 * @param    p1         A corner of the triangle.
 * @param    p2         A corner of the triangle.
 * @param    c0         The color of one corner of the triangle.
 * @param    c1         The color of one corner of the triangle.
 * @param    c2         The color of one corner of the triangle.
 * @related  cf_draw_tri cf_draw_tri_fill cf_draw_tri_fill2 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_tri_fill2(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_Color c0, CF_Color c1, CF_Color c2);

/**
 * @function cf_draw_line
 * @category draw
 * @brief    Draws a line.
 * @param    p0         An endpoint of the line.
 * @param    p1         An endpoint of the line.
 * @param    thickness  The thickness of the line to draw.
 * @related  cf_draw_line cf_draw_line2 cf_draw_polyline cf_draw_bezier_line cf_draw_bezier_line2 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_line(CF_V2 p0, CF_V2 p1, float thickness);

/**
 * @function cf_draw_line2
 * @category draw
 * @brief    Draws a line.
 * @param    p0         An endpoint of the line.
 * @param    p1         An endpoint of the line.
 * @param    thickness  The thickness of the line to draw.
 * @param    c0         The color one endpoint of the line.
 * @param    c1         The color one endpoint of the line.
 * @related  cf_draw_line cf_draw_line2 cf_draw_polyline cf_draw_bezier_line cf_draw_bezier_line2 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_line2(CF_V2 p0, CF_V2 p1, float thickness, CF_Color c0, CF_Color c1);

/**
 * @function cf_draw_polyline
 * @category draw
 * @brief    Draws a chain of connected line segments.
 * @param    points       An array of line segment endpoints.
 * @param    count        The number of points in the polyline.
 * @param    thickness    The thickness of the line to draw.
 * @param    loop         True to connect the first and last point to form a loop. False otherwise.
 * @param    bevel_count  The number of edges used to smooth corners.
 * @related  cf_draw_line cf_draw_line2 cf_draw_polyline cf_draw_bezier_line cf_draw_bezier_line2 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_polyline(CF_V2* points, int count, float thickness, bool loop, int bevel_count);

/**
 * @function cf_draw_bezier_line
 * @category draw
 * @brief    Draws line segments over a quadratic bezier line.
 * @param    a          The starting point.
 * @param    c0         A bezier control point.
 * @param    b          The end point.
 * @param    thickness  The thickness of the line to draw.
 * @param    iters      The number of lines used to draw the bezier spline.
 * @related  cf_draw_line cf_draw_line2 cf_draw_polyline cf_draw_bezier_line cf_draw_bezier_line2 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_bezier_line(CF_V2 a, CF_V2 c0, CF_V2 b, int iters, float thickness);

/**
 * @function cf_draw_bezier_line2
 * @category draw
 * @brief    Draws line segments over a cubic bezier line.
 * @param    a          The starting point.
 * @param    c0         A bezier control point.
 * @param    c1         A bezier control point.
 * @param    b          The end point.
 * @param    thickness  The thickness of the line to draw.
 * @param    iters      The number of lines used to draw the bezier spline.
 * @related  cf_draw_line cf_draw_line2 cf_draw_polyline cf_draw_bezier_line cf_draw_bezier_line2 cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_bezier_line2(CF_V2 a, CF_V2 c0, CF_V2 c1, CF_V2 b, int iters, float thickness);

/**
 * @function cf_draw_push_layer
 * @category draw
 * @brief    Pushes a draw layer.
 * @param    layer      The layer.
 * @remarks  Draw layers are sorted before rendering. Lower numbers are rendered fast, while larger numbers are rendered last.
 *           This can be used to pick which sprites/shapes should draw on top of each other.
 * @related  cf_draw_push_layer cf_draw_pop_layer cf_draw_peek_layer
 */
CUTE_API void CUTE_CALL cf_draw_push_layer(int layer);

/**
 * @function cf_draw_pop_layer
 * @category draw
 * @brief    Pops and returns the last draw layer.
 * @remarks  Draw layers are sorted before rendering. Lower numbers are rendered fast, while larger numbers are rendered last.
 *           This can be used to pick which sprites/shapes should draw on top of each other.
 * @related  cf_draw_push_layer cf_draw_pop_layer cf_draw_peek_layer
 */
CUTE_API int CUTE_CALL cf_draw_pop_layer();

/**
 * @function cf_draw_peek_layer
 * @category draw
 * @brief    Returns the last draw layer.
 * @remarks  Draw layers are sorted before rendering. Lower numbers are rendered fast, while larger numbers are rendered last.
 *           This can be used to pick which sprites/shapes should draw on top of each other.
 * @related  cf_draw_push_layer cf_draw_pop_layer cf_draw_peek_layer
 */
CUTE_API int CUTE_CALL cf_draw_peek_layer();

/**
 * @function cf_draw_push_color
 * @category draw
 * @brief    Pushes a draw color.
 * @param    c          The color.
 * @remarks  Various draw functions do not specify a color. In these cases, the last color pushed will be used.
 * @related  cf_draw_push_color cf_draw_pop_color cf_draw_peek_color
 */
CUTE_API void CUTE_CALL cf_draw_push_color(CF_Color c);

/**
 * @function cf_draw_pop_color
 * @category draw
 * @brief    Pops and returns the last draw color.
 * @remarks  Various draw functions do not specify a color. In these cases, the last color pushed will be used.
 * @related  cf_draw_push_color cf_draw_pop_color cf_draw_peek_color
 */
CUTE_API CF_Color CUTE_CALL cf_draw_pop_color();

/**
 * @function cf_draw_peek_color
 * @category draw
 * @brief    Returns the last draw color.
 * @remarks  Various draw functions do not specify a color. In these cases, the last color pushed will be used.
 * @related  cf_draw_push_color cf_draw_pop_color cf_draw_peek_color
 */
CUTE_API CF_Color CUTE_CALL cf_draw_peek_color();

/**
 * @function cf_draw_push_tint
 * @category draw
 * @brief    Pushes a tint color.
 * @param    c          The color.
 * @remarks  Sprites and shapes can be tinted. This is useful for certain effects such as damage flashes, or
 *           dynamic color variations.
 * @related  cf_draw_push_tint cf_draw_pop_tint cf_draw_peek_tint
 */
CUTE_API void CUTE_CALL cf_draw_push_tint(CF_Color c);

/**
 * @function cf_draw_pop_tint
 * @category draw
 * @brief    Pops and returns the last tint color.
 * @remarks  Sprites and shapes can be tinted. This is useful for certain effects such as damage flashes.
 * @related  cf_draw_push_tint cf_draw_pop_tint cf_draw_peek_tint
 */
CUTE_API CF_Color CUTE_CALL cf_draw_pop_tint();

/**
 * @function cf_draw_peek_tint
 * @category draw
 * @brief    Returns the last tint color.
 * @remarks  Sprites and shapes can be tinted. This is useful for certain effects such as damage flashes.
 * @related  cf_draw_push_tint cf_draw_pop_tint cf_draw_peek_tint
 */
CUTE_API CF_Color CUTE_CALL cf_draw_peek_tint();

/**
 * @function cf_draw_push_antialias
 * @category draw
 * @brief    Pushes whether or not to apply antialiasing.
 * @param    antialias  True to antialias, false otherwise.
 * @remarks  Various shape drawing functions can be drawn in antialiased mode, or in plain mode. Antialiasing is slightly slower,
 *           but looks much smoother.
 * @related  cf_draw_push_antialias cf_draw_pop_antialias cf_draw_peek_antialias
 */
CUTE_API void CUTE_CALL cf_draw_push_antialias(bool antialias);

/**
 * @function cf_draw_pop_antialias
 * @category draw
 * @brief    Pops and returns the last antialias state.
 * @remarks  Various shape drawing functions can be drawn in antialiased mode, or in plain mode. Antialiasing is slightly slower,
 *           but looks much smoother.
 * @related  cf_draw_push_antialias cf_draw_pop_antialias cf_draw_peek_antialias
 */
CUTE_API bool CUTE_CALL cf_draw_pop_antialias();

/**
 * @function cf_draw_peek_antialias
 * @category draw
 * @brief    Returns the last antialias state.
 * @remarks  Various shape drawing functions can be drawn in antialiased mode, or in plain mode. Antialiasing is slightly slower,
 *           but looks much smoother.
 * @related  cf_draw_push_antialias cf_draw_pop_antialias cf_draw_peek_antialias
 */
CUTE_API bool CUTE_CALL cf_draw_peek_antialias();

/**
 * @function cf_make_font
 * @category text
 * @brief    Constructs a font for rendering text.
 * @param    path        A virtual path (TODO_LINK) to the font file.
 * @param    font_name   A unique name for this font. Used by `cf_push_font` and friends.
 * @return   Returns any errors as `CF_Result`.
 * @remarks  Memory is only consumed when you draw a certain glyph (text character). Just loading up the font initially is
 *           a low-cost operation. You may load up many fonts with low overhead. Please note that bold, italic, etc. are actually
 *           _different fonts_ and each must be loaded up individually.
 * @related  cf_make_font cf_make_font_mem cf_destroy_font cf_push_font cf_push_font_size cf_push_font_blur cf_draw_text
 */
CUTE_API CF_Result CUTE_CALL cf_make_font(const char* path, const char* font_name);

/**
 * @function cf_make_font_mem
 * @category text
 * @brief    Constructs a font for rendering text from memory.
 * @param    data        A buffer containing the bytes of a font file in memory.
 * @param    size        The size of `data` in bytes.
 * @param    font_name   A unique name for this font. Used by `cf_push_font` and friends.
 * @return   Returns any errors as `CF_Result`.
 * @remarks  Memory is only consumed when you draw a certain glyph (text character). Just loading up the font initially is
 *           a low-cost operation. You may load up many fonts with low overhead. Please note that bold, italic, etc. are actually
 *           _different fonts_ and each must be loaded up individually.
 * @related  cf_make_font cf_make_font_mem cf_destroy_font cf_push_font cf_push_font_size cf_push_font_blur cf_draw_text
 */
CUTE_API CF_Result CUTE_CALL cf_make_font_mem(void* data, int size, const char* font_name);

/**
 * @function cf_destroy_font
 * @category text
 * @brief    Destroys a font previously made by `cf_make_font` or `cf_make_font_mem`.
 * @param    font_name   The unique name for this font.
 * @related  cf_make_font cf_make_font_mem cf_destroy_font cf_push_font cf_push_font_size cf_push_font_blur cf_draw_text
 */
CUTE_API void CUTE_CALL cf_destroy_font(const char* font_name);

/**
 * @function cf_font_add_backup_codepoints
 * @category text
 * @brief    When drawing text, and missing glyphs from the font will be replaced by any backup codepoints.
 * @param    font_name   The unique name for this font.
 * @param    codepoints  An array of backup codepoints. Highest priority comes first in the array.
 * @param    count       The number of elements in `codepoints`.
 * @related  cf_draw_text
 */
CUTE_API void CUTE_CALL cf_font_add_backup_codepoints(const char* font_name, int* codepoints, int count);

/**
 * @function cf_push_font
 * @category text
 * @brief    Pushes a font to use for text drawing.
 * @param    font_name   The unique name for this font.
 * @related  cf_make_font cf_push_font cf_pop_font cf_peek_font cf_push_font_size cf_push_font_blur cf_draw_text
 */
CUTE_API void CUTE_CALL cf_push_font(const char* font);

/**
 * @function cf_pop_font
 * @category text
 * @brief    Pops and returns the last font name used.
 * @related  cf_make_font cf_push_font cf_pop_font cf_peek_font cf_push_font_size cf_push_font_blur cf_draw_text
 */
CUTE_API const char* CUTE_CALL cf_pop_font();

/**
 * @function cf_peek_font
 * @category text
 * @brief    Returns the last font name used.
 * @related  cf_make_font cf_push_font cf_pop_font cf_peek_font cf_push_font_size cf_push_font_blur cf_draw_text
 */
CUTE_API const char* CUTE_CALL cf_peek_font();

/**
 * @function cf_push_font_size
 * @category text
 * @brief    Pushes a font size to use for text drawing.
 * @param    size       The size to use for text drawing.
 * @related  cf_make_font cf_push_font cf_push_font_size cf_pop_font_size cf_peek_font_size cf_push_font_blur cf_draw_text
 */
CUTE_API void CUTE_CALL cf_push_font_size(float size);

/**
 * @function cf_pop_font_size
 * @category text
 * @brief    Pops and returns the last font size.
 * @related  cf_make_font cf_push_font cf_push_font_size cf_pop_font_size cf_peek_font_size cf_push_font_blur cf_draw_text
 */
CUTE_API float CUTE_CALL cf_pop_font_size();

/**
 * @function cf_peek_font_size
 * @category text
 * @brief    Returns the last font size.
 * @related  cf_make_font cf_push_font cf_push_font_size cf_pop_font_size cf_peek_font_size cf_push_font_blur cf_draw_text
 */
CUTE_API float CUTE_CALL cf_peek_font_size();

/**
 * @function cf_push_font_blur
 * @category text
 * @brief    Pushes a font blur to use for text drawing.
 * @param    blur       The blur to use for text drawing.
 * @related  cf_make_font cf_push_font cf_push_font_size cf_push_font_blur cf_pop_font_blur cf_peek_font_blur cf_draw_text
 */
CUTE_API void CUTE_CALL cf_push_font_blur(int blur);

/**
 * @function cf_pop_font_blur
 * @category text
 * @brief    Pops and returns the last font blur.
 * @related  cf_make_font cf_push_font cf_push_font_size cf_push_font_blur cf_pop_font_blur cf_peek_font_blur cf_draw_text
 */
CUTE_API int CUTE_CALL cf_pop_font_blur();

/**
 * @function cf_peek_font_blur
 * @category text
 * @brief    Returns the last font blur.
 * @related  cf_make_font cf_push_font cf_push_font_size cf_push_font_blur cf_pop_font_blur cf_peek_font_blur cf_draw_text
 */
CUTE_API int CUTE_CALL cf_peek_font_blur();

/**
 * @function cf_push_text_wrap_width
 * @category text
 * @brief    Pushes a text wrap width to use for text drawing.
 * @param    width      The text wrap width to use for text drawing.
 * @related  cf_make_font cf_push_font cf_push_text_wrap_width cf_pop_text_wrap_width cf_peek_text_wrap_width cf_push_text_clip_box cf_draw_text
 */
CUTE_API void CUTE_CALL cf_push_text_wrap_width(float width);

/**
 * @function cf_pop_text_wrap_width
 * @category text
 * @brief    Pops and returns the last text wrap width.
 * @related  cf_make_font cf_push_font cf_push_text_wrap_width cf_pop_text_wrap_width cf_peek_text_wrap_width cf_push_text_clip_box cf_draw_text
 */
CUTE_API float CUTE_CALL cf_pop_text_wrap_width();

/**
 * @function cf_peek_text_wrap_width
 * @category text
 * @brief    Returns the last text wrap width.
 * @related  cf_make_font cf_push_font cf_push_text_wrap_width cf_pop_text_wrap_width cf_peek_text_wrap_width cf_push_text_clip_box cf_draw_text
 */
CUTE_API float CUTE_CALL cf_peek_text_wrap_width();

/**
 * @function cf_push_text_clip_box
 * @category text
 * @brief    Pushes a text clip box to use for text drawing.
 * @param    clip_box   The text clip box to use for text drawing.
 * @related  cf_make_font cf_push_font cf_push_text_wrap_width cf_push_text_clip_box cf_pop_text_clip_box cf_peek_text_clip_box cf_draw_text
 */
CUTE_API void CUTE_CALL cf_push_text_clip_box(CF_Aabb clip_box);

/**
 * @function cf_pop_text_clip_box
 * @category text
 * @brief    Pops and returns the last text clip box.
 * @related  cf_make_font cf_push_font cf_push_text_wrap_width cf_push_text_clip_box cf_pop_text_clip_box cf_peek_text_clip_box cf_draw_text
 */
CUTE_API CF_Aabb CUTE_CALL cf_pop_text_clip_box();

/**
 * @function cf_peek_text_clip_box
 * @category text
 * @brief    Returns the last text clip box.
 * @related  cf_make_font cf_push_font cf_push_text_wrap_width cf_push_text_clip_box cf_pop_text_clip_box cf_peek_text_clip_box cf_draw_text
 */
CUTE_API CF_Aabb CUTE_CALL cf_peek_text_clip_box();

/**
 * @function cf_push_text_vertical_layout
 * @category text
 * @brief    Pushes a whether or not to layout text vertically (as opposed to the default or horizontally).
 * @param    layout_vertically  True to layout vertically, false otherwise.
 * @related  cf_make_font cf_push_font cf_push_text_vertical_layout cf_pop_text_vertical_layout cf_peek_text_vertical_layout cf_draw_text
 */
CUTE_API void CUTE_CALL cf_push_text_vertical_layout(bool layout_vertically);

/**
 * @function cf_pop_text_vertical_layout
 * @category text
 * @brief    Pops and returns the last vertical layout state.
 * @related  cf_make_font cf_push_font cf_push_text_vertical_layout cf_pop_text_vertical_layout cf_peek_text_vertical_layout cf_draw_text
 */
CUTE_API bool CUTE_CALL cf_pop_text_vertical_layout();

/**
 * @function cf_peek_text_vertical_layout
 * @category text
 * @brief    Returns the last vertical layout state.
 * @related  cf_make_font cf_push_font cf_push_text_vertical_layout cf_pop_text_vertical_layout cf_peek_text_vertical_layout cf_draw_text
 */
CUTE_API bool CUTE_CALL cf_peek_text_vertical_layout();

/**
 * @function cf_text_width
 * @category text
 * @brief    Returns the width of a text given the currently pushed font.
 * @param    text      The text considered for rendering.
 * @related  cf_make_font cf_text_width cf_text_height cf_draw_text
 */
CUTE_API float CUTE_CALL cf_text_width(const char* text);

/**
 * @function cf_text_height
 * @category text
 * @brief    Returns the height of a text given the currently pushed font.
 * @param    height     The text considered for rendering.
 * @related  cf_make_font cf_text_width cf_text_height cf_draw_text
 */
CUTE_API float CUTE_CALL cf_text_height(const char* text);

/**
 * @function cf_draw_text
 * @category text
 * @brief    Draws text.
 * @param    text      The text to draw.
 * @param    position  The top-left corner of the text.
 * @related  cf_make_font cf_draw_text cf_text_effect_register cf_draw_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_draw_text(const char* text, CF_V2 position);

/**
 * @struct   CF_TextEffect
 * @category text
 * @brief    A user-defined text effect that can be triggered with text codes.
 * @example > Quick example listing some valid strings using text effects. These are all built-in text effects, and not user-defined custom ones.
 *     "This text is white. And this is <color=0x55b6f2ff>blue text</color>!"
 *     "<fade>This text shows a fade example~</fade>"
 * @remarks  A text code is an XML-style markup for strings. See the above code example for what this looks like. See `CF_TextEffect` and
 *           `cf_text_effect_register` on registering a custom-made text effect. See `cf_text_effect_register` for a big list of built-in text effects
 *           that work out-of-the-box. Members of this struct that can be mutated freely within a custom text effect are noted with "User-modifiable"
 *           in their description.
 * @related  CF_TextEffect CF_TextEffectFn cf_text_effect_register
 */
typedef struct CF_TextEffect
{
	/* @member Name of this effect, as registered by `cf_text_effect_register`. */
	const char* effect_name;

	/* @member UTF8 codepoint of the current character. */
	int character;

	/* @member The index into the string in `cf_draw_text` currently affected. */
	int index_into_string;

	/* @member Starts at 0 and increments for each character affected. */
	int index_into_effect;

	/* @member The number of glyphs spanning the entire effect. */
	int glyph_count;

	/* @member How long this effect has persisted for. */
	float elapsed;

	/* @member Center of this glyp's space -- not the same as the center of the glyph quad. */
	CF_V2 center;

	/* @member User-modifiable. This glyph's renderable quad. q0 is the min vertex, while q1 is the max vertex. */
	CF_V2 q0, q1;

	/* @member Width and height of the glyph. */
	int w, h;

	/* @member User-modifiable. The color to render this glyph with. */
	CF_Color color;

	/* @member User-modifiable. The opacity to render this glyph with. */
	float opacity;

	/* @member User-modifiable. How far the text will advance along the x-axis (only applicable for non-vertical layout mode). */
	float xadvance;

	/* @member User-modifiable. Whether or not this glyph is visibly rendered (e.g. not visible for spaces ' '). */
	bool visible;

	/* @member The last size passed to `cf_push_font_size`. */
	float font_size;
} CF_TextEffect;
// @end

/**
 * @function CF_TextEffectFn
 * @category text
 * @brief    Implements a custom text effect, called once per glyph.
 * @param    fx        The text effect state.
 * @return   Return true to go to the next glyph. Return false to stop processing the string.
 * @example  > Internally the text shake effect is implemented something like this.
 *     // Given a string like this:
 *     "Some <shake freq=50 x=2.5 y=1>shaking text</shake> drawing!"
 *     
 *     static bool s_text_fx_shake(TextEffect* effect)
 *     {
 *         double freq = effect->get_number("freq", 35);
 *         int seed = (int)(effect->elapsed * freq);
 *         float x = (float)effect->get_number("x", 2);
 *         float y = (float)effect->get_number("y", 2);
 *         CF_Rnd rnd = cf_rnd_seed(seed);
 *         v2 offset = V2(rnd_next_range(rnd, -x, y), rnd_next_range(rnd, -x, y));
 *         effect->q0 += offset;
 *         effect->q1 += offset;
 *         return true;
 *     }
 * @remarks  The text between your custom text-code will get passed to `fn` for you, and called one time per glyph in
 *           the text just before it gets rendered. You have the chance to modify things such as the text color, size, scale,
 *           position, visibility, etc. You should use `cf_text_effect_get_number`, `cf_text_effect_get_color`, or
 *           `cf_text_effect_get_string` to fetch values from your codes. As a convenience, you can see if the current
 *           character is the first or last to render using `cf_text_effect_on_start` or `cf_text_effect_on_finish` respectively.
 * @related  CF_TextEffect CF_TextEffectFn cf_text_effect_register cf_text_effect_on_start cf_text_effect_on_finish cf_text_effect_get_number cf_text_effect_get_color cf_text_effect_get_string
 */
typedef bool (CF_TextEffectFn)(CF_TextEffect* fx);

/**
 * @function cf_text_effect_register
 * @category text
 * @brief    Registers a custom text effect.
 * @param    name      A unique name for your text effect.
 * @param    fn        The `CF_TextEffectFn` function you must implement to perform the custom effect.
 * @example  > Internally the text shake effect is implemented something like this.
 *     // Given a string like this:
 *     "Some <shake freq=50 x=2.5 y=1>shaking text</shake> drawing!"
 *     
 *     static bool s_text_fx_shake(TextEffect* effect)
 *     {
 *         double freq = effect->get_number("freq", 35);
 *         int seed = (int)(effect->elapsed * freq);
 *         float x = (float)effect->get_number("x", 2);
 *         float y = (float)effect->get_number("y", 2);
 *         CF_Rnd rnd = cf_rnd_seed(seed);
 *         v2 offset = V2(rnd_next_range(rnd, -x, y), rnd_next_range(rnd, -x, y));
 *         effect->q0 += offset;
 *         effect->q1 += offset;
 *         return true;
 *     }
 *     
 *     // Register it like so:
 *     cf_text_effect_register("shake", s_text_fx_shake);
 * @remarks  The `name` of the text effect will be used within the string text codes. For example, for the "shake" effect in the above
 *           example, the text code <shake> will be used.
 *           ```
 *           + color
 *                example : "Here's some <color=#2c5ee8>blue text</color>."
 *                        : default (white) - The color to render text with.
 *           + shake
 *                example : "<shake freq=30 x=3 y=3>This text is all shaky.</shake>"
 *                example : "<shake y=20>Shake this text with default values, but override for a big height.</shake>"
 *                freq    : default (35)    - Number of times per second to shake.
 *                x       : default (2)     - Max +/- distance to shake on x-axis.
 *                y       : default (2)     - Max +/- distance to shake on y-axis.
 *           + fade
 *                example : "<fade speed=10 span=3>Fading some text like a ghost~</fade>"
 *                example : "<fade>Fading some text like a ghost~</fade>"
 *                speed   : default (2)     - Number of times per second to find in and then out.
 *                span    : default (5)     - Number of characters long for the fade to loop.
 *           + wave
 *                example : "<wave>Wobbly wave text.</wave>"
 *                speed   : default (5)     - Number of times per second to bob up and down.
 *                span    : default (10)    - Number of characters long for the wave to loop.
 *                height. : default (5)     - How many characters high the wave will go.
 *           + strike
 *                example : "<strike>Strikethrough</strike>"
 *                example : "<strike=10>Thick Strikethrough</strike>"
 *                        : default (font_height / 20) - The thickness of the strike line.
 *           ```
 *           When registering a custom text effect, any parameters in the string will be stored for you
 *           automatically. You only need to fetch them with the appropriate cf_text_effect_get*** function.
 * @related  CF_TextEffect CF_TextEffectFn cf_text_effect_register cf_text_effect_on_start cf_text_effect_on_finish cf_text_effect_get_number cf_text_effect_get_color cf_text_effect_get_string
 */
CUTE_API void CUTE_CALL cf_text_effect_register(const char* name, CF_TextEffectFn* fn);

/**
 * @function cf_text_effect_on_start
 * @category text
 * @brief    Helper function to see if the current glyph is the beginning of the text, from within a custom text effect.
 * @param    fx        The text effect state.
 * @return   Return true to continue to the next glyph, false otherwise.
 * @related  CF_TextEffect CF_TextEffectFn cf_text_effect_register cf_text_effect_on_start cf_text_effect_on_finish cf_text_effect_get_number cf_text_effect_get_color cf_text_effect_get_string
 */
CUTE_API bool CUTE_CALL cf_text_effect_on_start(CF_TextEffect* fx);

/**
 * @function cf_text_effect_on_finish
 * @category text
 * @brief    Helper function to see if the current glyph is the end of the text, from within a custom text effect.
 * @param    fx        The text effect state.
 * @return   Return true to continue to the next glyph, false otherwise.
 * @related  CF_TextEffect CF_TextEffectFn cf_text_effect_register cf_text_effect_on_start cf_text_effect_on_finish cf_text_effect_get_number cf_text_effect_get_color cf_text_effect_get_string
 */
CUTE_API bool CUTE_CALL cf_text_effect_on_finish(CF_TextEffect* fx);

/**
 * @function cf_text_effect_get_number
 * @category text
 * @brief    Returns the text parameter as a number.
 * @param    fx           The text effect state.
 * @param    key          The name of the text code parameter
 * @param    default_val  A default value for the text code parameter if doesn't exist in the text.
 * @return   Returns the value of the text code parameter.
 * @related  CF_TextEffect CF_TextEffectFn cf_text_effect_register cf_text_effect_on_start cf_text_effect_on_finish cf_text_effect_get_number cf_text_effect_get_color cf_text_effect_get_string
 */
CUTE_API double CUTE_CALL cf_text_effect_get_number(CF_TextEffect* fx, const char* key, double default_val);

/**
 * @function cf_text_effect_get_color
 * @category text
 * @brief    Returns the text parameter as a color.
 * @param    fx           The text effect state.
 * @param    key          The name of the text code parameter
 * @param    default_val  A default value for the text code parameter if doesn't exist in the text.
 * @return   Returns the value of the text code parameter.
 * @related  CF_TextEffect CF_TextEffectFn cf_text_effect_register cf_text_effect_on_start cf_text_effect_on_finish cf_text_effect_get_number cf_text_effect_get_color cf_text_effect_get_string
 */
CUTE_API CF_Color CUTE_CALL cf_text_effect_get_color(CF_TextEffect* fx, const char* key, CF_Color default_val);

/**
 * @function cf_text_effect_get_string
 * @category text
 * @brief    Returns the text parameter as a string.
 * @param    fx           The text effect state.
 * @param    key          The name of the text code parameter
 * @param    default_val  A default value for the text code parameter if doesn't exist in the text.
 * @return   Returns the value of the text code parameter.
 * @related  CF_TextEffect CF_TextEffectFn cf_text_effect_register cf_text_effect_on_start cf_text_effect_on_finish cf_text_effect_get_number cf_text_effect_get_color cf_text_effect_get_string
 */
CUTE_API const char* CUTE_CALL cf_text_effect_get_string(CF_TextEffect* fx, const char* key, const char* default_val);

/**
 * @function cf_render_settings_filter
 * @category draw
 * @brief    Sets a rendering `CF_Filter`, used for sampling from textures.
 * @param    filter       The filter.
 * @related  cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_push_scissor cf_render_settings_push_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_render_settings_filter(CF_Filter filter);

/**
 * @function cf_render_settings_push_viewport
 * @category draw
 * @brief    Pushes a `CF_Rect` for the viewport to render within.
 * @param    viewport     The viewport.
 * @related  cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_pop_viewport cf_render_settings_peek_viewport cf_render_settings_push_scissor cf_render_settings_push_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_render_settings_push_viewport(CF_Rect viewport);

/**
 * @function cf_render_settings_pop_viewport
 * @category draw
 * @brief    Pops and returns the last `CF_Rect` for the viewport.
 * @related  cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_pop_viewport cf_render_settings_peek_viewport cf_render_settings_push_scissor cf_render_settings_push_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API CF_Rect CUTE_CALL cf_render_settings_pop_viewport();

/**
 * @function cf_render_settings_peek_viewport
 * @category draw
 * @brief    Returns the last `CF_Rect` for the viewport.
 * @related  cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_pop_viewport cf_render_settings_peek_viewport cf_render_settings_push_scissor cf_render_settings_push_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API CF_Rect CUTE_CALL cf_render_settings_peek_viewport();

/**
 * @function cf_render_settings_push_scissor
 * @category draw
 * @brief    Pushes a `CF_Rect` for the scissor to render within.
 * @param    scissor      The scissor box.
 * @related  cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_push_scissor cf_render_settings_pop_scissor cf_render_settings_peek_scissor cf_render_settings_push_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_render_settings_push_scissor(CF_Rect scissor);

/**
 * @function cf_render_settings_pop_scissor
 * @category draw
 * @brief    Pops and returns the last `CF_Rect` for the scissor box.
 * @related  cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_push_scissor cf_render_settings_pop_scissor cf_render_settings_peek_scissor cf_render_settings_push_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API CF_Rect CUTE_CALL cf_render_settings_pop_scissor();

/**
 * @function cf_render_settings_peek_scissor
 * @category draw
 * @brief    Returns the last `CF_Rect` for the scissor box.
 * @related  cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_push_scissor cf_render_settings_pop_scissor cf_render_settings_peek_scissor cf_render_settings_push_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API CF_Rect CUTE_CALL cf_render_settings_peek_scissor();

/**
 * @function cf_render_settings_push_render_state
 * @category draw
 * @brief    Pushes a `CF_RenderState` for controlling various rendering settings.
 * @param    render_state  Various types of rendering states.
 * @related  CF_RenderState cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_push_scissor cf_render_settings_push_render_state cf_render_settings_pop_render_state cf_render_settings_peek_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API void CUTE_CALL cf_render_settings_push_render_state(CF_RenderState render_state);

/**
 * @function cf_render_settings_pop_render_state
 * @category draw
 * @brief    Pops and returns the last `CF_RenderState`.* @related  CF_RenderState cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_push_scissor cf_render_settings_push_render_state cf_render_settings_pop_render_state cf_render_settings_peek_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API CF_RenderState CUTE_CALL cf_render_settings_pop_render_state();

/**
 * @function cf_render_settings_peek_render_state
 * @category draw
 * @brief    Returns the last `CF_RenderState`.* @related  CF_RenderState cf_render_settings_filter cf_render_settings_push_viewport cf_render_settings_push_scissor cf_render_settings_push_render_state cf_render_settings_pop_render_state cf_render_settings_peek_render_state cf_render_to cf_app_draw_onto_screen
 */
CUTE_API CF_RenderState CUTE_CALL cf_render_settings_peek_render_state();

/**
 * @function cf_camera_dimensions
 * @category camera
 * @brief    Sets the width and height of the camera's view.
 * @param    w          The width of the camera's view.
 * @param    h          The height of the camera's view.
 * @related  cf_camera_dimensions cf_camera_look_at cf_camera_rotate cf_camera_push cf_camera_pop cf_app_draw_onto_screen cf_render_to
 */
CUTE_API void CUTE_CALL cf_camera_dimensions(float w, float h);

/**
 * @function cf_camera_look_at
 * @category camera
 * @brief    Sets where in the world the camera sees.
 * @param    x          The x position of the camera's view.
 * @param    y          The y position of the camera's view.
 * @related  cf_camera_dimensions cf_camera_look_at cf_camera_rotate cf_camera_push cf_camera_pop cf_app_draw_onto_screen cf_render_to
 */
CUTE_API void CUTE_CALL cf_camera_look_at(float x, float y);

/**
 * @function cf_camera_rotate
 * @category camera
 * @brief    Rotates the camera.
 * @param    radians    The angle of camera rotation.
 * @related  cf_camera_dimensions cf_camera_look_at cf_camera_rotate cf_camera_push cf_camera_pop cf_app_draw_onto_screen cf_render_to
 */
CUTE_API void CUTE_CALL cf_camera_rotate(float radians);

/**
 * @function cf_camera_push
 * @category camera
 * @brief    Pushes a copy of the camera state.
 * @related  cf_camera_dimensions cf_camera_look_at cf_camera_rotate cf_camera_push cf_camera_pop cf_app_draw_onto_screen cf_render_to
 */
CUTE_API void CUTE_CALL cf_camera_push();

/**
 * @function cf_camera_pop
 * @category camera
 * @brief    Pops the current camera state, and uses the previously pushed camera state.
 * @related  cf_camera_dimensions cf_camera_look_at cf_camera_rotate cf_camera_push cf_camera_pop cf_app_draw_onto_screen cf_render_to
 */
CUTE_API void CUTE_CALL cf_camera_pop();

/**
 * @function cf_render_to
 * @category draw
 * @brief    Renders to a `CF_Canvas`.
 * @param    canvas     The canvas to render to.
 * @param    clear      True to clear the canvas's previous contents, false otherwise.
 * @remarks  This is advanced function. It's useful for off-screen rendering for certain rendering effects, such as multi-pass
 *           effects like reflections, or advanced lighting techniques. By default, everything will get renderered to the app's
 *           canvas, so this function is not necessary to call at all. Instead, calling `cf_app_draw_onto_screen` should be the go-to.
 * @related  cf_camera_dimensions cf_camera_look_at cf_camera_rotate cf_camera_push cf_camera_pop cf_app_draw_onto_screen cf_render_to
 */
CUTE_API void CUTE_CALL cf_render_to(CF_Canvas canvas, bool clear);

/**
 * @struct   CF_TemporaryImage
 * @category draw
 * @brief    Returns temporal information about a sprite's rendering internals.
 * @remarks  Useful to render a sprite in an external system, e.g. Dear ImGui. This struct is only valid until the next time `cf_render_to` or
 *           `cf_app_draw_onto_screen` is called.
 * @related  CF_TemporaryImage cf_fetch_image
 */
typedef struct CF_TemporaryImage
{
	/* @member A handle representing the texture for this image. */
	CF_Texture tex;

	/* @member Width in pixels of the image. */
	int w;

	/* @member Height in pixels of the image. */
	int h;

	/* @member u coordinate of the image in the texture. */
	CF_V2 u;

	/* @member v coordinate of the image in the texture. */
	CF_V2 v;
} CF_TemporaryImage;
// @end

/**
 * @function cf_fetch_image
 * @category draw
 * @brief    Returns a `CF_TemporaryImage` for a given sprite.
 * @param    sprite     The sprite.
 * @remarks  Useful to render a sprite in an external system, e.g. Dear ImGui. This struct is only valid until the next time `cf_render_to` or
 *           `cf_app_draw_onto_screen` is called.
 * @related  CF_TemporaryImage cf_fetch_image
 */
CUTE_API CF_TemporaryImage CUTE_CALL cf_fetch_image(const CF_Sprite* sprite);

//--------------------------------------------------------------------------------------------------
// "Hidden" API -- Just here for some inline C++ functions below.

enum CF_TextCodeValType
{
	CF_TEXT_CODE_VAL_TYPE_NONE,
	CF_TEXT_CODE_VAL_TYPE_COLOR,
	CF_TEXT_CODE_VAL_TYPE_NUMBER,
	CF_TEXT_CODE_VAL_TYPE_STRING,
};

struct CF_TextCodeVal
{
	enum CF_TextCodeValType type;
	union
	{
		CF_Color color;
		double number;
		const char* string;
	} u;
};

#ifdef __cplusplus
}
#endif // __cplusplus

//--------------------------------------------------------------------------------------------------
// C++ API

#ifdef CUTE_CPP

namespace Cute
{

using TemporaryImage = CF_TemporaryImage;

CUTE_INLINE void draw_sprite(const CF_Sprite* sprite) { cf_draw_sprite(sprite); }
CUTE_INLINE void draw_quad(CF_Aabb bb, float thickness) { cf_draw_quad(bb, thickness); }
CUTE_INLINE void draw_quad(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_V2 p3, float thickness) { cf_draw_quad2(p0, p1, p2, p3, thickness); }
CUTE_INLINE void draw_quad(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_V2 p3, float thickness, CF_Color c0, CF_Color c1, CF_Color c2, CF_Color c3) { cf_draw_quad3(p0, p1, p2, p3, thickness, c0, c1, c2, c3); }
CUTE_INLINE void draw_quad_fill(CF_Aabb bb) { cf_draw_quad_fill(bb); }
CUTE_INLINE void draw_quad_fill(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_V2 p3) { cf_draw_quad_fill2(p0, p1, p2, p3); }
CUTE_INLINE void draw_quad_fill(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_V2 p3, CF_Color c0, CF_Color c1, CF_Color c2, CF_Color c3) { cf_draw_quad_fill3(p0, p1, p2, p3, c0, c1, c2, c3); }
CUTE_INLINE void draw_circle(CF_V2 p, float r, int iters, float thickness) { cf_draw_circle(p, r, iters, thickness); }
CUTE_INLINE void draw_circle_fill(CF_V2 p, float r, int iters) { cf_draw_circle_fill(p, r, iters); }
CUTE_INLINE void draw_circle_arc(CF_V2 p, CF_V2 center_of_arc, float range, int iters, float thickness) { cf_draw_circle_arc(p, center_of_arc, range, iters, thickness); }
CUTE_INLINE void draw_circle_arc_fill(CF_V2 p, CF_V2 center_of_arc, float range, int iters) { draw_circle_arc_fill(p, center_of_arc, range, iters); }
CUTE_INLINE void draw_capsule(CF_V2 p0, CF_V2 p1, float r, int iters, float thickness) { cf_draw_capsule(p0, p1, r, iters, thickness); }
CUTE_INLINE void draw_capsule_fill(CF_V2 p0, CF_V2 p1, float r, int iters) { cf_draw_capsule_fill(p0, p1, r, iters); }
CUTE_INLINE void draw_tri(CF_V2 p0, CF_V2 p1, CF_V2 p2, float thickness) { cf_draw_tri(p0, p1, p2, thickness); }
CUTE_INLINE void draw_tri_fill(CF_V2 p0, CF_V2 p1, CF_V2 p2) { cf_draw_tri_fill(p0, p1, p2); }
CUTE_INLINE void draw_tri_fill(CF_V2 p0, CF_V2 p1, CF_V2 p2, CF_Color c0, CF_Color c1, CF_Color c2) { cf_draw_tri_fill2(p0, p1, p2, c0, c1, c2); }
CUTE_INLINE void draw_line(CF_V2 p0, CF_V2 p1, float thickness) { cf_draw_line(p0, p1, thickness); }
CUTE_INLINE void draw_line(CF_V2 p0, CF_V2 p1, float thickness, CF_Color c0, CF_Color c1) { cf_draw_line2(p0, p1, thickness, c0, c1); }
CUTE_INLINE void draw_polyline(CF_V2* points, int count, float thickness, bool loop, int bevel_count) { cf_draw_polyline(points, count, thickness, loop, bevel_count); }

CUTE_INLINE void draw_push_layer(int layer) { cf_draw_push_layer(layer); }
CUTE_INLINE int draw_pop_layer() { return cf_draw_pop_layer(); }
CUTE_INLINE int draw_peek_layer() { return cf_draw_peek_layer(); }
CUTE_INLINE void draw_push_color(CF_Color c) { cf_draw_push_color(c); }
CUTE_INLINE CF_Color draw_pop_color() { return cf_draw_pop_color(); }
CUTE_INLINE CF_Color draw_peek_color() { return cf_draw_peek_color(); }
CUTE_INLINE void draw_push_tint(CF_Color c) { cf_draw_push_tint(c); }
CUTE_INLINE CF_Color draw_pop_tint() { return cf_draw_pop_tint(); }
CUTE_INLINE CF_Color draw_peek_tint() { return cf_draw_peek_tint(); }
CUTE_INLINE void draw_push_antialias(bool antialias) { cf_draw_push_antialias(antialias); }
CUTE_INLINE bool draw_pop_antialias() { return cf_draw_pop_antialias(); }
CUTE_INLINE bool draw_peek_antialias() { return cf_draw_peek_antialias(); }

CUTE_INLINE CF_Result make_font(const char* path, const char* font_name) { return cf_make_font(path, font_name); }
CUTE_INLINE CF_Result make_font_mem(void* data, int size, const char* font_name) { return cf_make_font_mem(data, size, font_name); }
CUTE_INLINE void destroy_font(const char* font_name) { cf_destroy_font(font_name); }
CUTE_INLINE void font_add_backup_codepoints(const char* font_name, int* codepoints, int count) { cf_font_add_backup_codepoints(font_name, codepoints, count); }
CUTE_INLINE void push_font(const char* font_name) { cf_push_font(font_name); }
CUTE_INLINE const char* pop_font() { return cf_pop_font(); }
CUTE_INLINE const char* peek_font() { return cf_peek_font(); }
CUTE_INLINE void push_font_size(float size) { cf_push_font_size(size); }
CUTE_INLINE float pop_font_size() { return cf_pop_font_size(); }
CUTE_INLINE float peek_font_size() { return cf_peek_font_size(); }
CUTE_INLINE void push_font_blur(int blur) { cf_push_font_blur(blur); }
CUTE_INLINE int pop_font_blur() { return cf_pop_font_blur(); }
CUTE_INLINE int peek_font_blur() { return cf_peek_font_blur(); }
CUTE_INLINE void push_text_wrap_width(float width) { cf_push_text_wrap_width(width); }
CUTE_INLINE float pop_text_wrap_width() { return cf_pop_text_wrap_width(); }
CUTE_INLINE float peek_text_wrap_width() { return cf_peek_text_wrap_width(); }
CUTE_INLINE void push_text_clip_box(CF_Aabb clip_box) { cf_push_text_clip_box(clip_box); }
CUTE_INLINE CF_Aabb pop_text_clip_box() { return cf_pop_text_clip_box(); }
CUTE_INLINE CF_Aabb peek_text_clip_box() { return cf_peek_text_clip_box(); }
CUTE_INLINE float text_width(const char* text) { return cf_text_width(text); }
CUTE_INLINE float text_height(const char* text) { return cf_text_height(text); }
CUTE_INLINE void draw_text(const char* text, CF_V2 position) { cf_draw_text(text, position); }

struct TextEffect : public CF_TextEffect
{
	CUTE_INLINE bool on_start() const { return index_into_effect == 0; }
	CUTE_INLINE bool on_finish() const { return index_into_effect == glyph_count - 1; }

	CUTE_INLINE double get_number(const char* key, double default_val = 0)
	{
		const CF_TextCodeVal* v = params->try_find(sintern(key));
		if (v && v->type == CF_TEXT_CODE_VAL_TYPE_NUMBER) {
			return v->u.number;
		} else {
			return default_val;
		}
	}
	
	CUTE_INLINE CF_Color get_color(const char* key, CF_Color default_val = cf_color_white())
	{
		const CF_TextCodeVal* v = params->try_find(sintern(key));
		if (v && v->type == CF_TEXT_CODE_VAL_TYPE_COLOR) {
			return v->u.color;
		} else {
			return default_val;
		}
	}
	
	CUTE_INLINE const char* get_string(const char* key, const char* default_val = NULL)
	{
		const CF_TextCodeVal* v = params->try_find(sintern(key));
		if (v && v->type == CF_TEXT_CODE_VAL_TYPE_STRING) {
			return v->u.string;
		} else {
			return default_val;
		}
	}

	// "private" state -- don't touch.
	const Cute::Map<const char*, CF_TextCodeVal>* params;
	CF_TextEffectFn* fn;
};

typedef bool (TextEffectFn)(TextEffect* fx);

CUTE_INLINE void text_effect_register(const char* name, TextEffectFn* fn) { cf_text_effect_register(name, (CF_TextEffectFn*)fn); }

CUTE_INLINE void render_settings_filter(CF_Filter filter) { cf_render_settings_filter(filter); }
CUTE_INLINE void render_settings_push_viewport(CF_Rect viewport) { cf_render_settings_push_viewport(viewport); }
CUTE_INLINE CF_Rect render_settings_pop_viewport() { return cf_render_settings_pop_viewport(); }
CUTE_INLINE CF_Rect render_settings_peek_viewport() { return cf_render_settings_peek_viewport(); }
CUTE_INLINE void render_settings_push_scissor(CF_Rect scissor) { cf_render_settings_push_scissor(scissor); }
CUTE_INLINE CF_Rect render_settings_pop_scissor() { return cf_render_settings_pop_scissor(); }
CUTE_INLINE CF_Rect render_settings_peek_scissor() { return cf_render_settings_peek_scissor(); }
CUTE_INLINE void render_settings_push_render_state(CF_RenderState render_state) { render_settings_push_render_state(render_state); }
CUTE_INLINE CF_RenderState render_settings_pop_render_state() { return render_settings_pop_render_state(); }
CUTE_INLINE CF_RenderState render_settings_peek_render_state() { return render_settings_peek_render_state(); }

CUTE_INLINE void camera_dimensions(float w, float h) { cf_camera_dimensions(w, h); }
CUTE_INLINE void camera_look_at(float x, float y) { cf_camera_look_at(x, y); }
CUTE_INLINE void camera_rotate(float radians) { cf_camera_rotate(radians); }
CUTE_INLINE void camera_push() { cf_camera_push(); }
CUTE_INLINE void camera_pop() { cf_camera_pop(); }

CUTE_INLINE void render_to(CF_Canvas canvas, bool clear = false) { cf_render_to(canvas, clear); }

CUTE_INLINE CF_TemporaryImage fetch_image(const CF_Sprite* sprite) { return cf_fetch_image(sprite); }

}

#endif // CUTE_CPP

#endif // CUTE_DRAW_H
