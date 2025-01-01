/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:32
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-06 13:25:58
 * @FilePath: /lua-cad/src/obj_type.h
 * @Description: object type and base class definition
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

#define CODE_LENGTH 4096

#define dynast_cast( DEST, base ) ( DEST* )( base )

/**
 * @description: object base class
 * @return {*}
 */
typedef struct OBJ_BASE
{
    OBJ_TYPE m_type;
    char* m_code;
} OBJ_BASE;

/**
 * @description: bool object base class
 * @return {*}
 */
typedef struct BOOLEAN_BASE
{
    OBJ_BASE m_obj_base;
    OBJ_TYPE* m_children[10];
    unsigned int m_count;
} BOOLEAN_BASE;

/**
 * @description: 3D object base class
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
    union
    {
        double m_color_arr[4];
        char m_color_str[32];
    };
    double m_color_alpha;
    bool m_center;
    int m_op_stack[20];
} D3OBJECT_BASE;

/**
 * @description: 2D object base class
 * @return {*}
 */
typedef struct D2OBJECT_BASE
{
    OBJ_BASE m_obj_base;
    vec3 m_offset;
    vec3 m_scale;
    vec3 m_rotate_v;
    vec3 m_rotate_a;
    vec3 m_mirror;
    union
    {
        double m_color_arr[4];
        char m_color_str[32];
    };
    double m_color_alpha;
    bool m_center;
    int m_op_stack[20];
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

bool is_boolean(OBJ_TYPE type);

bool is_d3object(OBJ_TYPE type);

bool is_d2object(OBJ_TYPE type);

bool is_transform(OBJ_TYPE type);

bool is_user_obj( OBJ_TYPE type );