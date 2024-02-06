/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-06 00:45:05
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-06 12:18:52
 * @FilePath: /lua-cad/src/d2object/polygon.h
 * @Description: polygon
 *
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <vec2.h>

#define POLYGON_CONVEXITY( obj ) obj->m_convexity

typedef struct polygon
{
    D2OBJECT_BASE base;
    vec2 m_points[64];
    int* m_paths[64];
    int m_points_count;
    int m_paths_count;
    int m_convexity;
} polygon;

int polygon_init( lua_State* L );
