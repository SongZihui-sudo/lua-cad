/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-01-31 17:32:32
 * @FilePath: /lua-cad/src/base_object/cube.h
 * @Description: cube object
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

/**
 * @description: get cube width, length, height
 * @return {*}
 */
#define CUBE_WIDTH( obj ) obj->m_w_l_h.m_xyz[0]
#define CUBE_LENGTH( obj ) obj->m_w_l_h.m_xyz[1]
#define CUBE_HEIGHT( obj ) obj->m_w_l_h.m_xyz[2]

// 立方体
typedef struct cube
{
    D3OBJECT_BASE base;
    vec3 m_w_l_h; // length, width, height
} cube;

#define cube_obj_init( obj )                                                               \
    vec3_init( &obj->m_w_l_h, 1 );                                                            \
    D3OBJECT_BASE_INIT( &obj->base );

/**
 * @description: calculate cube vertices
 * @param {lua_State*} L
 * @param {cube*} self
 * @param {unsigned short} index
 * @return {*}
 */
vec3 calculate_vertices_cube( lua_State* L, cube* self, unsigned short index );
/*
    That is, the eight vertices of the cube, plus the centers of the six planes
    Front upper right case 1:
    Front upper left case 2:
    Front lower right case 3:
    Front upper left case 4:
    Back upper right case 5:
    Back upper left case 6:
    Back lower right case 7:
    Back lower left case 8:
    Top case 9:
    Bottom case 10:
    Left case 11:
    Right case 12:
    Front case 13:
    Back case 14:
*/

/**
 * @description: Initialize the cube
 * @param {lua_State*} L
 * @return {*}
 */
int cube_init( lua_State* L );
