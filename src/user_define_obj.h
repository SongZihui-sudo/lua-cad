/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-01-28 21:38:58
 * @FilePath: /lua-cad/src/user_define_obj.h
 * @Description: 用户自定义对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lua.h>

#include <cube.h>
#include <obj_type.h>


typedef struct user_define_objects {
  char m_names[128][100];
  int counts;
}user_define_objects;

extern user_define_objects user_objs;

/**
 * @description: 用户自定义对象设置位置
 * @param {lua_State*} L
 * @return {*}
 */
int user_code_postion( lua_State* L );

/**
 * @description: 用户自定义对象输出
 * @return {*}
 */
int user_define_to_code( lua_State* L );