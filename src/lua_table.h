#pragma once

#include <lua.h>
#include <lauxlib.h>
#include <stdbool.h>

double get_table_field_number_value(lua_State* L, const char* key, int ss_index);

const char* get_table_field_string_value(lua_State* L, const char* key, int ss_index);

int get_table_field_number_array(lua_State* L, const char* key, int ss_index, double* buffer);

int get_table_field_string_array( lua_State* L, const char* key, int ss_index, const char** buffer );

bool get_table_field_boolean_value( lua_State* L, const char* key, int ss_index );