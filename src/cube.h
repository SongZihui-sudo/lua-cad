#pragma once

#include <vec3.h>
#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>

#define CUBE_WIDTH(obj) obj->m_w_l_h->m_xyz[0]
#define CUBE_LENGTH(obj) obj->m_w_l_h->m_xyz[1]
#define CUBE_HEIGHT(obj) obj->m_w_l_h->m_xyz[2]
#define CUBE_X(obj) obj->m_offset->m_xyz[0]
#define CUBE_Y(obj) obj->m_offset->m_xyz[1]
#define CUBE_Z(obj) obj->m_offset->m_xyz[2]
#define CUBE_CENTER(obj) obj->m_center

// 立方体
struct cube
{
    OBJ_TYPE m_type;
    char m_code[OBJECT_CODE_LENGTH];
    bool m_center;
    struct vec3* m_offset;
    struct vec3* m_w_l_h;   // 长，宽，高
};

// 计算顶点
struct vec3 calculate_vertices(struct cube* self, unsigned short index);