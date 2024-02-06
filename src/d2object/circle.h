/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-06 00:21:39
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-06 00:29:56
 * @FilePath: /lua-cad/src/d2object/circle.h
 * @Description: circle
 *
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <vec2.h>

#define CIRCLE_R_D(obj) obj->m_r_d
#define CIRCLE_VALUE(obj) obj->m_value

typedef struct circle
{
    D2OBJECT_BASE base;
    char m_r_d;
    double m_value;
} circle;

/**
 * @description: circle
 * @param {lua_State*} L
 * @return {*}
 */
int circle_init( lua_State* L );
