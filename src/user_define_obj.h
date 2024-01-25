#pragma once

#include <lua.h>

#include <obj_type.h>
#include <cube.h>

typedef struct user_define_object
{
    D3OBJECT_BASE m_base;
    OBJ_TYPE m_parent;
}user_define_object;

int user_define_object_init(lua_State* L);
