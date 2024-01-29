#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

#define CYLINDER_R1(CYLINDER) CYLINDER->r1
#define CYLINDER_R2(CYLINDER) CYLINDER->r2
#define CYLINDER_R(CYLINDER) CYLINDER->r
#define CYLINDER_D1(CYLINDER) CYLINDER->d1
#define CYLINDER_D2(CYLINDER) CYLINDER->d2
#define CYLINDER_H(CYLINDER) CYLINDER->h
#define CYLINDER_X( CYLINDER ) CYLINDER->base.m_offset->m_xyz[0]
#define CYLINDER_Y( CYLINDER ) CYLINDER->base.m_offset->m_xyz[1]
#define CYLINDER_Z( CYLINDER ) CYLINDER->base.m_offset->m_xyz[2]
#define CYLINDER_CENTER( CYLINDER ) CYLINDER->base.m_center

typedef struct cylinder
{
    D3OBJECT_BASE base;
    double r1, r2, d1, d2, r, h;
}cylinder;

/**
 * @description: 计算圆柱体的顶点
 * @param {cube*} self
 * @param {unsigned short} index
 * @return {*}
 */
vec3 calculate_vertices_cylinder( cylinder* self, unsigned short index );
