#pragma once

#include <lauxlib.h>

int cube_init( lua_State* L );

int print_code(lua_State* L);

#define LUA_CAD_FUNCTIONS { "export", lua_cad_export }, {"code", code}
