#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

#define SPHERE_R_OR_D( SPHERE ) SPHERE->m_r_or_d

typedef struct sphere
{
    D3OBJECT_BASE base;
    double m_r_or_d;
} sphere;

#define sphere_obj_init( obj )                                                             \
    D3OBJECT_BASE_INIT( &obj->base );                                                       \
    obj->m_r_or_d = -1;

/**
 * @description: 初始化球体
 * @param {lua_State*} L
 * @return {*}
 */
int sphere_init( lua_State* L );

/**
 * @description: 计算球体顶点
 * @param {sphere*} self
 * @param {unsigned short} index
 * @return {*}
 */
vec3 calculate_vertices_sphere( lua_State* L, sphere* self, unsigned short index );
