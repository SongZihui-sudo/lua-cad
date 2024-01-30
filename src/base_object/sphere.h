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

int sphere_init(lua_State* L);

vec3 calculate_vertices_sphere( sphere* self, unsigned short index );