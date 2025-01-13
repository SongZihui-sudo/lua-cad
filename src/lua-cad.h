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

#define LUA_CAD_VERSION_MAJOR "1"
#define LUA_CAD_VERSION_MINOR "2"
#define LUA_CAD_VERSION_RELEASE "0"

#define LUA_CAD_NUM 4
#define LUA_CAD_VERSION_RELEASE_NUM ( LUA_CAD_VERSION_NUM * 100 + 7 )

#define LUA_CAD_VERSION "Lua-Cad " LUA_CAD_VERSION_MAJOR "." LUA_CAD_VERSION_MINOR
#define LUA_CAD_RELEASE LUA_CAD_VERSION "." LUA_CAD_VERSION_RELEASE
#define LUA_CAD_COPYRIGHT LUA_CAD_RELEASE " Copyright (C) 2024 - 2025 lua-cad Lua for 3D"
#define LUA_CAD_AUTHORS "SongZihui 1751122876@qq.com https://szhwho.top"

extern char* openscad_path;
extern char* hob3l_path;

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

int set_openscad_path( lua_State* L );

int set_hob3l_path( lua_State* L );

/**
 * @description: some global functions
 * @return {*}
 */
#define LUA_CAD_FUNCTIONS                                                                          \
    { "export", lua_cad_export }, { "code", code }, { "include", include_code },                   \
    { "import", import_module }, { "render", render }, { "set_openscad", set_openscad_path }, \
    {                                                                                              \
        "set_hob3l", set_hob3l_path                                                           \
    }