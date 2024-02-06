/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-05 23:46:29
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-06 13:15:17
 * @FilePath: /lua-cad/src/d2object/square.h
 * @Description: square
 *
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <vec2.h>

#define SQUARE_WIDTH(obj) obj->w_l.m_xy[0]
#define SQUARE_LENGTH(obj) obj->w_l.m_xy[1]

typedef struct square
{
    D2OBJECT_BASE base;
    vec2 w_l;
} square;

/**
 * @description: 初始化 square
 * @param {lua_State*} L
 * @return {*}
 */
int square_init(lua_State* L);
