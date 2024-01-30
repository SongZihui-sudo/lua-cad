#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <stdbool.h>
#include <vec3.h>

/**
 * @description: 设置位置 --- translate
 * @param {lua_State*} L
 * @return {*}
 */
int transform_postion(lua_State* L);
