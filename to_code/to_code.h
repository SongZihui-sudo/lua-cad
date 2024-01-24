#pragma once

#include <obj_type.h>
#include <cube.h>
#include <union.h>
#include <difference.h>
#include <intersection.h>
#include <lua.h>

// 输出立方体
void cube_to_code( lua_State* L, struct cube* self );

// 输出 difference
void difference_to_code( lua_State* L, struct difference* self );

// 输出 union
void union_to_code(lua_State* L, struct Union* self);

// 输出 intersection
void intersection_to_code(lua_State* L, struct intersection* self);

// 递归输出 layout
void layout_to_code( lua_State* L, OBJ_TYPE* self, char* temp );

extern char* LAYOUT_EXPORT_RULE[];

/*
 *  CUBE
 *  默认的输出规则
 *  规则类似于 printf 的格式
 */
#define CUBE_EXPORT_RULE "translate([%f, %f, %f]);\ncube([%f, %f, %f], center = %d);\n"
#define CUBE_EXPORT_ARGS CUBE_WIDTH(self), CUBE_LENGTH(self), CUBE_HEIGHT(self), CUBE_X(self), CUBE_Y(self), CUBE_Z(self), CUBE_CENTER(self)