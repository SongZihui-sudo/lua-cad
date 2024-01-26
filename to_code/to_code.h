#pragma once

#include <obj_type.h>
#include <cube.h>
#include <lua.h>

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
void boolean_to_code(lua_State* L, OBJ_TYPE* self);

/**
 * @description: 递归输出 layout
 * @param {lua_State*} L
 * @param {OBJ_TYPE*} self
 * @param {char*} temp
 * @return {*}
 */
void layout_to_code( lua_State* L, OBJ_TYPE* self, char* temp );

extern char* LAYOUT_EXPORT_RULE[];

/*
 *  CUBE
 *  默认的输出规则
 *  规则类似于 printf 的格式
 */
#define CUBE_EXPORT_RULE "translate([%f, %f, %f]);\ncube([%f, %f, %f], center = %d);\n"
#define CUBE_EXPORT_ARGS CUBE_WIDTH(self), CUBE_LENGTH(self), CUBE_HEIGHT(self), CUBE_X(self), CUBE_Y(self), CUBE_Z(self), CUBE_CENTER(self)
