#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

/**
 * @description: set postion --- translate
 * @param {lua_State*} L
 * @return {*}
 */
int transform_postion( lua_State* L );

/**
 * @description: Scales its child elements using the specified vector. The argument name is optional.
 * @param {lua_State*} L
 * @return {*}
 */
int transform_scale( lua_State* L );

/**
 * @description: Rotates its child 'a' degrees about the axis of the coordinate system or around
 * an arbitrary axis. The argument names are optional if the arguments are given in the same order as specified.
 * @param {lua_State*} L
 * @return {*}
 */
int transform_rotate( lua_State* L );

/**
 * @description:
 * @param {lua_State*} L
 * @return {*}
 */
int transform_mirror( lua_State* L );

/**
 * @description: Displays the child elements using the specified RGB color + alpha value.
 * This is only used for the F5 preview as CGAL and STL (F6) do not currently support color.
 * The alpha value defaults to 1.0 (opaque) if not specified.
 * @param {lua_State*} L
 * @return {*}
 */
int color( lua_State* L );

/**
 * @description: read transform parameters
 * @param {lua_State*} L
 * @param {enum TRANSFORM_TYPES} type
 * @param {D3OBJECT_BASE*} obj
 * @return {*}
 */
int transform( lua_State* L, enum TYPES type, D3OBJECT_BASE* obj );

/**
 * @description: add transform code
 * @param {lua_State*} L
 * @param {D3OBJECT_BASE*} obj
 * @param {enum TYPES} type
 * @return {*}
 */
void append_transform_openscad_code( lua_State* L, D3OBJECT_BASE* obj, enum TYPES type );

/**
 * @description: return translate format string
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_translate_fmt( lua_State* L );

/**
 * @description: return mirror format string
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_mirror_fmt( lua_State* L );

/**
 * @description: return scale format string
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_scale_fmt( lua_State* L );

/**
 * @description: return rotate format string
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_rotate_fmt( lua_State* L );

/**
 * @description: return color format string
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_color_fmt( lua_State* L );
