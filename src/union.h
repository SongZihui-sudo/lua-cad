#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <vec3.h>

struct Union
{
    OBJ_TYPE m_type;
    char m_code[LAYOUT_CODE_LENGTH];
    OBJ_TYPE* m_children[10];
    unsigned int m_count;
};

int Union( lua_State* L );