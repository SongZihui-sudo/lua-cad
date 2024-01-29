/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:34
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-01-29 14:07:27
 * @FilePath: /lua-cad/to_code/to_code.h
 * @Description: 对象导出
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <cube.h>
#include <cylinder.h>
#include <lua.h>
#include <obj_type.h>
#include <sphere.h>

/**
 * @description: 输出立方体
 * @param {lua_State*} L
 * @param {cube*} self
 * @return {*}
 */
void cube_to_code( lua_State* L, cube* self );

/**
 * @description: 输出圆柱体
 * @param {lua_State*} L
 * @param {cylinder*} self
 * @return {*}
 */
void cylinder_to_code( lua_State* L, cylinder* self );

/**
 * @description: 输出球体
 * @param {lua_State*} L
 * @param {sphere*} self
 * @return {*}
 */
void sphere_to_code( lua_State* L, sphere* self );

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
    CUBE_X( self ), CUBE_Y( self ), CUBE_Z( self ), CUBE_WIDTH( self ),                    \
    CUBE_LENGTH( self ), CUBE_HEIGHT( self ), CUBE_CENTER( self )

/**
 * @description: 圆柱体的输出规则
 * @return {*}
 */
extern const char* CYLINDER_ARG1;
extern const char* CYLINDER_ARG2;
#define CYLINDER_EXPORT_RULE                                                               \
    "cylinder([h = %f, %s = %f, %s center = %d]);\n"
#define CYLINDER_ALL_EXPORT_RULE TRANSLATE_EXPORT_RULE CYLINDER_EXPORT_RULE
#define CYLINDER_EXPORT_ARGS                                                               \
    CYLINDER_X( self ), CYLINDER_Y( self ), CYLINDER_Z( self ), CYLINDER_H( self ),        \
    CYLINDER_ARG1, CYLINDER_R_D_1(self), CYLINDER_ARG2, CYLINDER_CENTER(self)

/**
 * @description: 球体输出规则
 * @return {*}
 */
extern const char* SPHERER_ARG1;
#define SPHERE_EXPORT_RULE "sphere(%s = %f);\n"
#define SPHERE_ALL_EXPORT_RULE TRANSLATE_EXPORT_RULE SPHERE_EXPORT_RULE
#define SPHERE_EXPORT_ARGS SPHERE_X( self ), SPHERE_Y( self ), SPHERE_Z( self ), SPHERER_ARG1, SPHERE_R_OR_D(self)
