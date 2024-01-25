#pragma once

#include <vec3.h>
#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>

#define CUBE_WIDTH(obj) obj->m_w_l_h->m_xyz[0]
#define CUBE_LENGTH(obj) obj->m_w_l_h->m_xyz[1]
#define CUBE_HEIGHT(obj) obj->m_w_l_h->m_xyz[2]
#define CUBE_X(obj) obj->base.m_offset->m_xyz[0]
#define CUBE_Y(obj) obj->base.m_offset->m_xyz[1]
#define CUBE_Z(obj) obj->base.m_offset->m_xyz[2]
#define CUBE_CENTER(obj) obj->base.m_center

// 立方体
typedef struct cube
{
    D3OBJECT_BASE base;
    vec3* m_w_l_h;   // 长，宽，高
}cube;

// 计算顶点
vec3 calculate_vertices(cube* self, unsigned short index);
