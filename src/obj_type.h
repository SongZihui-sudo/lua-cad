/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:32
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-01-30 22:22:06
 * @FilePath: /lua-cad/src/obj_type.h
 * @Description: 对象种类与基类的定义
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <stdbool.h>

#include <vec3.h>

#define OBJ_TYPE unsigned short

/*
 * TYPE
 */
enum TYPES
{
    OBJECT_BEGIN = 0,
    USER_DEFINE,
    CUBE,
    CYLINDER,
    SPHERE,
    POLYHEDRON,
    OBJECT_END,
    BOOLEAN_BEGIN,
    DIFFERENCE,
    UNION,
    INTERSECTION,
    FILL,
    HULL,
    MINKOWSKI,
    OFFSET,
    BOOLEAN_END
};

#define CODE_LENGTH 3000

#define dynast_cast( DEST, base ) ( DEST* )( base )

/**
 * @description: 对象基类
 * @return {*}
 */
typedef struct OBJ_BASE
{
    OBJ_TYPE m_type;
    char* m_code;
} OBJ_BASE;

/**
 * @description: bool 对象基类
 * @return {*}
 */
typedef struct BOOLEAN_BASE
{
    OBJ_BASE m_obj_base;
    OBJ_TYPE* m_children[10];
    unsigned int m_count;
} BOOLEAN_BASE;

/**
 * @description: 3d 对象基类
 * @return {*}
 */
typedef struct D3OBJECT_BASE
{
    OBJ_BASE m_obj_base;
    vec3 m_offset;
    vec3 m_scale;
    vec3 m_rotate_v;
    vec3 m_rotate_a;
    vec3 m_mirror;
    bool m_center;
    double m_color_arr[4];
    char m_color_str[32];
    double m_color_alpha;
} D3OBJECT_BASE;
