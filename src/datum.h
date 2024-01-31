#pragma once

#include <lauxlib.h>
#include <stdbool.h>
#include <vec3.h>

typedef struct datum
{
    vec3 m_center;
} datum;

/**
 * @description: 计算相对于基准平面中心位置的点坐标
 * @param {lua_State*} L
 * @return {*}
 */
int relative_position(lua_State* L);

/**
 * @description: 测量给定点距离基准平面中心的距离
 * @param {lua_State*} L
 * @return {*}
 */
int distance_to_datum(lua_State* L);

/**
 * @description: 测量给定向量于基准平面间的角度
 * @param {lua_State*} L
 * @return {*}
 */
int angle_to_datum(lua_State* L);

/**
 * @description: 将 x,y,z 内容转换到数组
 * @param {lua_State*} L
 * @return {*}
 */
int to_table_datum(lua_State* L);