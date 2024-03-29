/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-01-31 17:32:32
 * @FilePath: /lua-cad/src/base_object/cube.h
 * @Description: cube 对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

/**
 * @description: 获取立方体内对象
 * @return {*}
 */
#define CUBE_WIDTH( obj ) obj->m_w_l_h.m_xyz[0]
#define CUBE_LENGTH( obj ) obj->m_w_l_h.m_xyz[1]
#define CUBE_HEIGHT( obj ) obj->m_w_l_h.m_xyz[2]

// 立方体
typedef struct cube
{
    D3OBJECT_BASE base;
    vec3 m_w_l_h; // 长，宽，高
} cube;

#define cube_obj_init( obj )                                                               \
    vec3_init( &obj->m_w_l_h, 1 );                                                            \
    D3OBJECT_BASE_INIT( &obj->base );

/**
 * @description: 计算立方体的顶点
 * @param {lua_State*} L
 * @param {cube*} self
 * @param {unsigned short} index
 * @return {*}
 */
vec3 calculate_vertices_cube( lua_State* L, cube* self, unsigned short index );
/*
    就是立方体的八个顶点，加六个平面的中心
    前面右上 case 1:
    前面左上 case 2:
    前面右下 case 3:
    前面左上 case 4:
    后面右上 case 5:
    后面左上 case 6:
    后面右下 case 7:
    后面左下 case 8:
    顶 case 9:
    底 case 10:
    左 case 11:
    右 case 12:
    前 case 13:
    后 case 14:
*/

/**
 * @description: 初始化立方体
 * @param {lua_State*} L
 * @return {*}
 */
int cube_init( lua_State* L );
