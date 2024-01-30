#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

typedef struct polyhedron
{
    D3OBJECT_BASE base;
    vec3 m_points[64];
    int* m_faces[64];
    int m_points_count;
    int m_face_countl
} polyhedron;

int polyhedron_init( lua_State* L );
