/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-01-26 20:45:26
 * @FilePath: /lua-cad/src/user_define_obj.h
 * @Description: 用户自定义对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lua.h>

#include <cube.h>
#include <obj_type.h>

typedef struct user_define_object
{
    D3OBJECT_BASE m_base;
    OBJ_TYPE m_parent;
} user_define_object;

/**
 * @description: 初始化用户自定义对象
 * @param {lua_State*} L
 * @return {*}
 */
int user_define_object_init( lua_State* L );
