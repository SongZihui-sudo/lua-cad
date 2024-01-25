#pragma once

#include <lauxlib.h>

int cube_init( lua_State* L );

int print_code(lua_State* L);

int include_code(lua_State* L);

int import_module(lua_State* L);

#define LUA_CAD_FUNCTIONS { "export", lua_cad_export }, {"code", code}, {"include", include_code}, {"import", import_module}
