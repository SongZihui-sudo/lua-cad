/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:32
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-11 22:55:20
 * @FilePath: /lua-cad/src/obj_type.h
 * @Description: 对象种类与基类的定义
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <stdbool.h>
#include <string.h>

#include <vec3.h>

#define OBJ_TYPE unsigned short

/*
 * TYPE
 */
enum TYPES
{
    D2OBJECT_BEGIN = 0,
    SQUARE,
    CIRCLE,
    POLYGON,
    D2OBJECT_END,
    D3OBJECT_BEGIN,
    USER_DEFINE,
    CUBE,
    CYLINDER,
    SPHERE,
    POLYHEDRON,
    D3OBJECT_END,
    BOOLEAN_BEGIN,
    DIFFERENCE,
    UNION,
    INTERSECTION,
    FILL,
    HULL,
    MINKOWSKI,
    OFFSET,
    BOOLEAN_END,
    TRANSFORM_BEGIN,
    TRANSLATE,
    SCALE,
    ROTATE,
    MIRROR,
    COLOR,
    LINEAR_EXTRUDE,
    ROTATE_EXTRUDE,
    TRANSFORM_END,
    INCLUDE,
    IMPORT
};

/* ouput mode */
#define OUPUT_MODE_OPENSCAD "openscad"
#define OUPUT_MODE_DEALII "dealii"
#define OUTPUT_MODE_GMSH "gmsh"

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
 * @description: 3D 对象基类
 * @return {*}
 */
typedef struct D3OBJECT_BASE
{
    OBJ_BASE m_obj_base;
    vec3 m_offset;
    vec3 m_scale;
    struct
    {
        vec3 m_rotate_v;
        vec3 m_rotate_a;
        char ROTATE_EXPORT_ARG1[64];
        char ROTATE_EXPORT_ARG2[64];
    };
    vec3 m_mirror;
    struct
    {
        union
        {
            double m_color_arr[4];
            char m_color_str[32];
        };
        double m_color_alpha;
        char COLOR_EXPORT_ARG1[64];
        char COLOR_EXPORT_ARG2[64];
    };
    bool m_center;
    enum TYPES m_op_stack[20];
} D3OBJECT_BASE;

/**
 * @description: 2D 对象基类
 * @return {*}
 */
typedef struct D2OBJECT_BASE
{
    OBJ_BASE m_obj_base;
    vec3 m_offset;
    vec3 m_scale;
    struct
    {
        vec3 m_rotate_v;
        vec3 m_rotate_a;
        char ROTATE_EXPORT_ARG1[64];
        char ROTATE_EXPORT_ARG2[64];
    };
    vec3 m_mirror;
    struct
    {
        union
        {
            double m_color_arr[4];
            char m_color_str[32];
        };
        double m_color_alpha;
        char COLOR_EXPORT_ARG1[64];
        char COLOR_EXPORT_ARG2[64];
    };
    bool m_center;
    enum TYPES m_op_stack[20];
    struct
    {
        double height;
        bool center;
        double convexity;
        double twist;
        double slices;
        double scale;
    } linear_extrude;
    struct
    {
        double angle;
        double convexity;
    } rotate_extrude;
} D2OBJECT_BASE;

static void D3OBJECT_BASE_INIT( D3OBJECT_BASE* obj )
{
    vec3_init( &obj->m_offset, 0 );
    vec3_init( &obj->m_scale, 1 );
    vec3_init( &obj->m_rotate_v, 0 );
    vec3_init( &obj->m_rotate_a, 0 );
    vec3_init( &obj->m_mirror, 0 );
    memset( obj->m_op_stack, 0, 20 );
}

#define IS_CENTER( bool_value ) center_true_false[bool_value]
#define POS_X( obj ) obj->base.m_offset->m_xyz[0]
#define POS_Y( obj ) obj->base.m_offset->m_xyz[1]
#define POS_Z( obj ) obj->base.m_offset->m_xyz[2]

#define LUA_CAD_API int

#define is_boolean( type ) type< BOOLEAN_END && type > BOOLEAN_BEGIN

#define is_d3object( type ) type > D3OBJECT_BEGIN&& type < D3OBJECT_END

#define is_d2object( type ) type > D2OBJECT_BEGIN&& type < D2OBJECT_END

#define is_transform( type ) type > TRANSFORM_BEGIN&& type < TRANSFORM_END
