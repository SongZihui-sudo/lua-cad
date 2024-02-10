/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-09 23:13:51
 * @FilePath: /lua-cad/src/lua-cad.h
 * @Description: 一些全局函数的实现
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lauxlib.h>
#include <obj_type.h>

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

const char* check_code( lua_State* L, int index );

const char* check_table( lua_State* L );

void check_output_mode( lua_State* L, D3OBJECT_BASE* obj );


/**
 * @description: 一些全局函数
 * @return {*}
 */
#define LUA_CAD_FUNCTIONS                                                                  \
    { "export", lua_cad_export }, { "code", code }, { "include", include_code },           \
    { "import", import_module }
