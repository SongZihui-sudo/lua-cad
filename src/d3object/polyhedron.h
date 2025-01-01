#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

#define POLYHEDRON_CONVEXITY(obj) obj->m_convexity

typedef struct polyhedron
{
    D3OBJECT_BASE base;
    vec3 m_points[64];
    int* m_faces[64];
    int m_points_count;
    int m_face_count;
    int m_convexity;
} polyhedron;

/**
 * @description: Initialize the polyhedron
 * @param {lua_State*} L
 * @return {*}
 */
int polyhedron_init( lua_State* L );

/**
 * @description: Calculate the vertices of the polyhedron
 * @param {polyhedron*} self
 * @param {unsigned short} index
 * @return {*}
 */
vec3 calculate_vertices_polyhedron( lua_State* L, polyhedron* self, unsigned short index );
