/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:34
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-01-29 10:54:50
 * @FilePath: /lua-cad/to_code/to_code.h
 * @Description: 对象导出
 * 
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved. 
 */

#pragma once

#include <cube.h>
#include <lua.h>
#include <obj_type.h>

/**
 * @description: 输出立方体
 * @param {lua_State*} L
 * @param {cube*} self
 * @return {*}
 */
void cube_to_code( lua_State* L, struct cube* self );

/**
 * @description: 输出 boolean
 * @param {lua_State*} L
 * @param {OBJ_TYPE*} self
 * @return {*}
 */
void boolean_to_code( lua_State* L, OBJ_TYPE* self );

/**
 * @description: 递归输出 layout
 * @param {lua_State*} L
 * @param {OBJ_TYPE*} self
 * @param {char*} temp
 * @return {*}
 */
void layout_to_code( lua_State* L, OBJ_TYPE* self, char* temp );

extern char* LAYOUT_EXPORT_RULE[];

#define TRANSLATE_EXPORT_RULE "translate([%f, %f, %f])\n"

/*
 *  CUBE
 *  默认的输出规则
 *  规则类似于 printf 的格式
 */
#define CUBE_EXPORT_RULE "cube([%f, %f, %f], center = %d);\n"
#define CUBE_ALL_EXPORT_RULE TRANSLATE_EXPORT_RULE CUBE_EXPORT_RULE
#define CUBE_EXPORT_ARGS                                                                   \
    CUBE_WIDTH( self ), CUBE_LENGTH( self ), CUBE_HEIGHT( self ), CUBE_X( self ),          \
    CUBE_Y( self ), CUBE_Z( self ), CUBE_CENTER( self )
