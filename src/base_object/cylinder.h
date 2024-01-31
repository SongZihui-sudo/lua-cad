#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

#define CYLINDER_R_D_1(CYLINDER) CYLINDER->m_r_d_1
#define CYLINDER_R_D_2(CYLINDER) CYLINDER->m_r_d_2
#define CYLINDER_H(CYLINDER) CYLINDER->m_h
#define CYLINDER_X( CYLINDER ) CYLINDER->base.m_offset->m_xyz[0]
#define CYLINDER_Y( CYLINDER ) CYLINDER->base.m_offset->m_xyz[1]
#define CYLINDER_Z( CYLINDER ) CYLINDER->base.m_offset->m_xyz[2]
#define CYLINDER_CENTER( CYLINDER ) CYLINDER->base.m_center

typedef struct cylinder
{
    D3OBJECT_BASE base;
    double m_h;
    double m_r_d_1;
    double m_r_d_2;
}cylinder;

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
