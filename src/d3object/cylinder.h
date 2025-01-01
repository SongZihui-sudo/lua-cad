#pragma once

#include "to_openscad_code.h"
#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

#define CYLINDER_R_D_1( CYLINDER ) CYLINDER->m_r_d_1
#define CYLINDER_R_D_2( CYLINDER ) CYLINDER->m_r_d_2
#define CYLINDER_H( CYLINDER ) CYLINDER->m_h

typedef struct cylinder
{
    D3OBJECT_BASE base;
    double m_h;
    double m_r_d_1;
    double m_r_d_2;
    short arg1;
    short arg2;
} cylinder;

/**
 * @description: init cylinder object
 * @return {*}
 */
#define cylinder_obj_init( obj )                                                           \
    obj->m_h     = -1;                                                                     \
    obj->m_r_d_1 = -1;                                                                     \
    obj->m_r_d_2 = -1;                                                                     \
    D3OBJECT_BASE_INIT( &obj->base );

/**
 * @description: create cylinder object
 * @param {lua_State*} L
 * @return {*}
 */
int cylinder_init( lua_State* L );

/**
 * @description: set cylinder height
 * @param {sphere*} self
 * @param {unsigned short} index
 * @return {*}
 */
vec3 calculate_vertices_cylinder( lua_State* L, cylinder* self, unsigned short index );
