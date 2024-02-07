/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:34
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-07 19:38:47
 * @FilePath: /lua-cad/port/openscad/to_openscad_code.h
 * @Description: 对象导出
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#pragma once

#include <lua.h>
#include <obj_type.h>

static char* center_true_false[2] = { "false", "true" };

/**
 * @description: 输出 3d 对象
 * @param {lua_State*} L
 * @param {D3OBJECT_BASE*} base
 * @return {*}
 */
void obj_to_openscad_code( lua_State* L, D3OBJECT_BASE* base );

/**
 * @description: 输出 boolean
 * @param {lua_State*} L
 * @param {OBJ_TYPE*} self
 * @return {*}
 */
void boolean_to_openscad_code( lua_State* L, OBJ_TYPE* self );

/**
 * @description: 递归输出 layout
 * @param {lua_State*} L
 * @param {OBJ_TYPE*} self
 * @param {char*} temp
 * @return {*}
 */
void layout_to_code( lua_State* L, OBJ_TYPE* self, char* temp );

extern char* LAYOUT_EXPORT_RULE[];

/**
 * @description: translate 输出规则
 * @return {*}
 */
#define TRANSLATE_EXPORT_RULE "translate([%f, %f, %f])\n"

/**
 * @description: scale 输出规则
 * @return {*}
 */
#define SCALE_EXPORT_RULE "scale([%f, %f, %f])\n"

extern char ROTATE_EXPORT_ARG1[64];
extern char ROTATE_EXPORT_ARG2[64];
/**
 * @description: rotate 输出规则
 * @return {*}
 */
#define ROTATE_EXPORT_RULE "rotate( %s %s )\n"

/**
 * @description: mirrot 导出规则
 * @return {*}
 */
#define MIRROR_EXPORT_RULE "mirror([ %f, %f, %f ])\n"

extern char COLOR_EXPORT_ARG1[64];
extern char COLOR_EXPORT_ARG2[64];
/**
 * @description: color 导出规则
 * @return {*}
 */
#define COLOR_EXPORT_RULE "color(%s %s)\n"

/**
 * @description: 参数模板
 * @return {*}
 */
#define SINGLE_ARG_RULE1 "%s = %f"

/**
 * @description: 3d 点模板
 * @return {*}
 */
#define POINT3_RULE "[ %f, %f, %f ]"

/**
 * @description: 2d 点模板
 * @return {*}
 */
#define POINT2_RULE "[%f, %f]"

/*
 *  CUBE
 *  默认的输出规则
 *  规则类似于 printf 的格式
 */
#define CUBE_EXPORT_RULE "cube([%f, %f, %f], center = %s);\n"
#define CUBE_ALL_EXPORT_RULE CUBE_EXPORT_RULE
#define CUBE_EXPORT_ARGS( self )                                                           \
    CUBE_WIDTH( self ), CUBE_LENGTH( self ), CUBE_HEIGHT( self ), IS_CENTER( self->base.m_center )

/**
 * @description: 圆柱体的输出规则
 * @return {*}
 */
extern const char* CYLINDER_ARG1;
extern const char* CYLINDER_ARG2;
#define CYLINDER_EXPORT_RULE "cylinder(h = %f, %s = %f, %s center = %s);\n"
#define CYLINDER_ALL_EXPORT_RULE CYLINDER_EXPORT_RULE
#define CYLINDER_EXPORT_ARGS( self )                                                       \
    CYLINDER_H( self ), CYLINDER_ARG1, CYLINDER_R_D_1( self ), CYLINDER_ARG2, IS_CENTER( self->base.m_center )

/**
 * @description: 球体输出规则
 * @return {*}
 */
extern const char* SPHERER_ARG1;
#define SPHERE_EXPORT_RULE "sphere(%s = %f);\n"
#define SPHERE_ALL_EXPORT_RULE SPHERE_EXPORT_RULE
#define SPHERE_EXPORT_ARGS( self ) SPHERER_ARG1, SPHERE_R_OR_D( self )

/**
 * @description: 多面体输出规则
 * @return {*}
 */
extern char POLYHEDRON_ARG1[200];
extern char POLYHEDRON_ARG2[200];
#define POLYHEDRON_EXPORT_RULE "polyhedron( points = [%s], faces = [%s], convexity = %d);\n"
#define POLYHEDRON_ALL_EXPORT_RULE POLYHEDRON_EXPORT_RULE
#define POLYHEDRON_EXPORT_ARGS( self ) POLYHEDRON_ARG1, POLYHEDRON_ARG2, POLYHEDRON_CONVEXITY(self)

#define SQUARE_EXPORT_RULE "square([%f, %f], center = %s);\n"
#define SQUARE_ALL_EXPORT_RULE SQUARE_EXPORT_RULE
#define SQUARE_EXPORT_ARGS( self )                                                         \
    SQUARE_WIDTH( self ), SQUARE_LENGTH( self ), IS_CENTER( self->base.m_center )

#define CIRCLE_EXPORT_RULE "circle(%c = %f);\n"
#define CIRCLE_ALL_EXPORT_RULE CIRCLE_EXPORT_RULE
#define CIRCLE_EXPORT_ARGS( self ) CIRCLE_R_D(self), CIRCLE_VALUE(self)

extern char POLYGON_ARG1[200];
extern char POLYGON_ARG2[200];
#define POLYGON_EXPORT_RULE "polygon(points = [%s], paths = [%s], convexity = %d);\n"
#define POLYGON_ALL_EXPORT_RULE POLYGON_EXPORT_RULE
#define POLYGON_EXPORT_ARGS( self ) POLYGON_ARG1, POLYGON_ARG2, POLYGON_CONVEXITY(self)

/**
 * @description: LINEAR_EXTRUDE_EXPORT_RULE
 * @return {*}
 */
#define LINEAR_EXTRUDE_EXPORT_RULE "linear_extrude(height = %f, center = %s, convexity = %f, twist = %f, slices = %f, scale = %f)\n"

/**
 * @description: ROTATE_EXTRUDE_EXPORT_RULE
 * @return {*}
 */
#define ROTATE_EXTRUDE_EXPORT_RULE "rotate_extrude(angle = %f, convexity = %f)\n"
