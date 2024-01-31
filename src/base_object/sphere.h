#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

#define SPHERE_R_OR_D(SPHERE) SPHERE->m_r_or_d
#define SPHERE_X( SPHERE ) SPHERE->base.m_offset->m_xyz[0]
#define SPHERE_Y( SPHERE ) SPHERE->base.m_offset->m_xyz[1]
#define SPHERE_Z( SPHERE ) SPHERE->base.m_offset->m_xyz[2]

typedef struct sphere
{
    D3OBJECT_BASE base;
    double m_r_or_d;
}sphere;

/**
 * @description: 初始化球体
 * @param {lua_State*} L
 * @return {*}
 */
int sphere_init(lua_State* L);

/**
 * @description: 计算球体顶点
 * @param {sphere*} self
 * @param {unsigned short} index
 * @return {*}
 */
vec3 calculate_vertices_sphere( lua_State* L, sphere* self, unsigned short index );
