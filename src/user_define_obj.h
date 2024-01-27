/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-01-27 15:24:10
 * @FilePath: /lua-cad/src/user_define_obj.h
 * @Description: 用户自定义对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <llex.h>
#include <lparser.h>
#include <lua.h>

#include <cube.h>
#include <obj_type.h>

typedef struct user_define_object
{
    D3OBJECT_BASE m_base;
    char* m_fmt[100];
    OBJ_TYPE* m_parent;
} user_define_object;

/**
 * @description: 把用户的外部代码解释为lua中的一个table对象
 * @param {LexState*} ls
 * @return {*}
 */
Table user_code_praser(LexState* ls);
