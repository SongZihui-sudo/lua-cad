#pragma once

#include <lua.h>
#include <lauxlib.h>

double get_table_field_int_value(lua_State* L, const char* key, int ss_index);