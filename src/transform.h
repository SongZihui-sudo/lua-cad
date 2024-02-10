#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

/**
 * @description: 设置位置 --- translate
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
 * @description: 读取变换参数
 * @param {lua_State*} L
 * @param {enum TRANSFORM_TYPES} type
 * @param {D3OBJECT_BASE*} obj
 * @return {*}
 */
int transform( lua_State* L, enum TYPES type, D3OBJECT_BASE* obj );

/**
 * @description: 添加变换修饰代码
 * @param {lua_State*} L
 * @param {D3OBJECT_BASE*} obj
 * @param {enum TYPES} type
 * @return {*}
 */
void append_transform_openscad_code( lua_State* L, D3OBJECT_BASE* obj, enum TYPES type );

/**
 * @description: 返回 translate 的模式串
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_translate_openscad_fmt( lua_State* L );

/**
 * @description: 返回 mirror 模式串
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_mirror_openscad_fmt( lua_State* L );

/**
 * @description: 返回 scale 模式串
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_scale_openscad_fmt( lua_State* L );

/**
 * @description: 返回 rotate 模式串
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_rotate_openscad_fmt( lua_State* L );

/**
 * @description: 返回 color 模式串
 * @param {lua_State*} L
 * @return {*}
 */
LUA_CAD_API get_color_openscad_fmt( lua_State* L );
