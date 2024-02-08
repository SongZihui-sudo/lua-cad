/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-02-08 21:20:28
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-08 23:34:48
 * @FilePath: /lua-cad/port/gmsh/gmsh.h
 * @Description: 
 * 
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved. 
 */

#pragma once

#include <lua.h>
#include <lauxlib.h>

#include <obj_type.h>

#define POINT_EXPORT_RULE1 "point(%d) = {%f, %f, %f, %f};"
#define POINT_EXPORT_RULE2 "point(%d) = {%f, %f, %f};"

void obj_to_gmsh_code(lua_State* L, D3OBJECT_BASE* obj);

void boolean_to_gmsh_code(lua_State* L, D3OBJECT_BASE* obj);

char* get_obj_table_gmsh_code( lua_State* L );