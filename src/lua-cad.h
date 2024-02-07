/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-07 13:24:46
 * @FilePath: /lua-cad/src/lua-cad.h
 * @Description: 一些全局函数的实现
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lauxlib.h>

/**
 * @description: 打印当前对象的 3d 代码
 * @param {lua_State*} L
 * @return {*}
 */
int print_code( lua_State* L );

/**
 * @description: include 其他 3d 代码文件
 * @param {lua_State*} L
 * @return {*}
 */
int include_code( lua_State* L );

/**
 * @description: 导入 stl 文件
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
 * @description: 一些全局函数
 * @return {*}
 */
#define LUA_CAD_FUNCTIONS                                                                  \
    { "export", lua_cad_export }, { "code", code }, { "include", include_code },           \
    { "import", import_module },                                                           \
    {                                                                                      \
        "render", render                                                                   \
    }
