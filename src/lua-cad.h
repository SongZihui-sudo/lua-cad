/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-07 13:24:46
 * @FilePath: /lua-cad/src/lua-cad.h
 * @Description: some global functions
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lauxlib.h>
#include <user_define_obj.h>

/**
 * @description: print the 3d code of the current object
 * @param {lua_State*} L
 * @return {*}
 */
int print_code( lua_State* L );

/**
 * @description: include other 3d code
 * @param {lua_State*} L
 * @return {*}
 */
int include_code( lua_State* L );

/**
 * @description: import stl file
 * @param {lua_State*} L
 * @return {*}
 */
int import_module( lua_State* L );

/**
 * @description: 渲染
 * @param {lua_State*} L
 * @return {*}
 */
int render( lua_State* L );

/**
 * @description: some global functions
 * @return {*}
 */
#define LUA_CAD_FUNCTIONS                                                                  \
    { "export", lua_cad_export }, { "code", code }, { "include", include_code },           \
    { "import", import_module },                                                           \
    {                                                                                      \
        "render", render                                                                   \
    }
