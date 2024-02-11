#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

#define CYLINDER_R_D_1( CYLINDER ) CYLINDER->m_r_d_1
#define CYLINDER_R_D_2( CYLINDER ) CYLINDER->m_r_d_2
#define CYLINDER_H( CYLINDER ) CYLINDER->m_h
#define CYLINDER_NAME1(CYLINDER) CYLINDER->m_name1
#define CYLINDER_NAME2(CYLINDER) CYLINDER->m_name2

typedef struct cylinder
{
    D3OBJECT_BASE base;
    double m_h;
    struct
    {
        double m_r_d_1;
        const char* m_name1;
    };
    struct
    {
        double m_r_d_2;
        const char* m_name2;
    };
} cylinder;

/**
 * @description: 圆柱体对象初始化
 * @return {*}
 */
#define cylinder_obj_init( obj )                                                           \
    obj->m_h     = -1;                                                                     \
    obj->m_r_d_1 = -1;                                                                     \
    obj->m_r_d_2 = -1;                                                                     \
    D3OBJECT_BASE_INIT( &obj->base );

/**
 * @description: 初始化圆柱体
 * @param {lua_State*} L
 * @return {*}
 */
int cylinder_init( lua_State* L );

/**
 * @description: 计算圆柱体的顶点
 * @param {sphere*} self
 * @param {unsigned short} index
 * @return {*}
 */
vec3 calculate_vertices_cylinder( lua_State* L, cylinder* self, unsigned short index );
