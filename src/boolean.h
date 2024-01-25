#pragma once

#include <lauxlib.h>
#include <obj_type.h>

void boolean_init( lua_State* L, OBJ_TYPE type );

int difference( lua_State* L );

int intersection( lua_State* L );

int Union( lua_State* L );
