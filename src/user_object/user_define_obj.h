/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-07 19:42:15
 * @FilePath: /lua-cad/src/user_object/user_define_obj.h
 * @Description: 用户自定义对象
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
 * @description: 引入其他文件中用户定义的对象
 * @param {lua_State*} L
 * @return {*}
 */
int user_define_from_file( lua_State* L );

/**
 * @description: 读 user_obj 表中的 code 字段
 * @param {lua_State*} L
 * @return {*}
 */
char* get_user_obj_code( lua_State* L, const char* dest );
