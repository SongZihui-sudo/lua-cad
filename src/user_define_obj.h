/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-01-27 23:44:33
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
  char m_names[32][100];
  int counts;
}user_define_objects;

extern user_define_objects userobjects;

/**
 * @description: 把用户的外部代码解释为lua中的一个table对象
 * @param {LexState*} ls
 * @return {*}
 */
int user_code_info(struct lua_State* L);

int user_code_postion( lua_State* L );
