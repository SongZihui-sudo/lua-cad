/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-01-30 21:40:42
 * @FilePath: /lua-cad/src/boolean.h
 * @Description: bool 操作
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lauxlib.h>
#include <obj_type.h>

/**
 * @description: 初始化一个 boolean 对象
 * @param {lua_State*} L
 * @param {OBJ_TYPE} type
 * @return {*}
 */
void boolean_init( lua_State* L, OBJ_TYPE type );

/**
 * @description: differece c 接口
 * @param {lua_State*} L
 * @return {*}
 */
int difference( lua_State* L );

/**
 * @description: intersection c 接口
 * @param {lua_State*} L
 * @return {*}
 */
int intersection( lua_State* L );

/**
 * @description: Union c 接口
 * @param {lua_State*} L
 * @return {*}
 */
int Union( lua_State* L );

/**
 * @description: fill c 接口
 * @param {lua_State*} L
 * @return {*}
 */
int fill(lua_State* L);

/**
 * @description: hull c 接口
 * @param {lua_State*} L
 * @return {*}
 */
int hull(lua_State* L);

/**
 * @description: minkowski c 接口
 * @param {lua_State*} L
 * @return {*}
 */
int minkowski(lua_State* L);

/**
 * @description: offset c 接口
 * @param {lua_State*} L
 * @return {*}
 */
int offset(lua_State* L);