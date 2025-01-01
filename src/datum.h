/*
 * @Author: songzihui 1751122876@qq.com
 * @Date: 2024-02-01 10:19:22
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-05 23:47:32
 * @FilePath: /lua-cad/src/datum.h
 * @Description: 
 * 
 * Copyright (c) 2024 by songzihui 1751122876@qq.com, All Rights Reserved. 
 */

#pragma once

#include <lauxlib.h>
#include <stdbool.h>
#include <vec3.h>

typedef struct datum
{
    vec3 m_center;
} datum;

/**
 * @description: calculate the relative position of the datum
 * @param {lua_State*} L
 * @return {*}
 */
int relative_position(lua_State* L);

/**
 * @description: measure the distance between the given vector and the datum
 * @param {lua_State*} L
 * @return {*}
 */
int distance_to_datum(lua_State* L);

/**
 * @description: measure the angle between the given vector and the datum
 * @param {lua_State*} L
 * @return {*}
 */
int angle_to_datum(lua_State* L);
