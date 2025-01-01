/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-03 13:02:50
 * @FilePath: /lua-cad/src/user_object/user_define_obj.h
 * @Description: user define object
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lua.h>

#include <cube.h>
#include <obj_type.h>

typedef struct user_define_objects
{
    char m_names[128][100];
    int counts;
} user_define_objects;

extern user_define_objects user_objs;

/**
 * @description: import the user define object from other file
 * @param {lua_State*} L
 * @return {*}
 */
int user_define_from_file( lua_State* L );

/**
 * @description: read the code field in the user_obj table
 * @param {lua_State*} L
 * @return {*}
 */
char* get_user_obj_code( lua_State* L, char* dest );
