#pragma once

#include <lauxlib.h>
#include <obj_type.h>
#include <vec3.h>

struct intersection
{
    OBJ_TYPE m_type;
    char m_code[LAYOUT_CODE_LENGTH];
    OBJ_TYPE* m_children[10];
    unsigned int m_count;
};

int intersection( lua_State* L );