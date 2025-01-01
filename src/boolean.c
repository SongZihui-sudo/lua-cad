/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:32
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-03 13:34:45
 * @FilePath: /lua-cad/src/boolean.c
 * @Description: bool 操作
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include "lua.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <boolean.h>
#include <to_openscad_code.h>
#include <user_define_obj.h>

double OFFSET_ARG;

/**
 * @description: 布尔操作
 * @return {*}
 */
static const luaL_Reg booleanlib[]
= { { "difference", difference }, { "union", Union }, { "intersection", intersection }, { NULL, NULL } };

int difference( lua_State* L )
{
    boolean_init( L, DIFFERENCE );
    return 1;
}

int intersection( lua_State* L )
{
    boolean_init( L, INTERSECTION );
    return 1;
}

int Union( lua_State* L )
{
    boolean_init( L, UNION );
    return 1;
}

int fill(lua_State* L)
{
    boolean_init( L, FILL );
    return 1;
}

int hull(lua_State* L)
{
    boolean_init( L, HULL );
    return 1;
}

int minkowski(lua_State* L)
{
    boolean_init( L, MINKOWSKI );
    return 1;
}

int offset(lua_State* L)
{
    boolean_init( L, OFFSET );
    OFFSET_ARG = lua_tonumber(L, 2);
    return 1;
}

void boolean_init( lua_State* L, OBJ_TYPE type )
{
    unsigned int i_bytes = sizeof( BOOLEAN_BASE );
    BOOLEAN_BASE* current;
    current                    = dynast_cast( BOOLEAN_BASE, lua_newuserdata( L, i_bytes ) );
    current->m_obj_base.m_type = type;
    current->m_count           = 0;
    // 读一个 table
    // 读输入的参数
    const int count = luaL_len( L, 1 );
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 1 );
        OBJ_TYPE* temp = NULL;
        if (lua_isuserdata(L, -1)) {
            // 标准对象可以直接读
            temp   = lua_touserdata( L, -1 );
        }
        else {
            // 读自定义对象表
            D3OBJECT_BASE* user_define = dynast_cast(D3OBJECT_BASE, malloc(sizeof(D3OBJECT_BASE)));
            D3OBJECT_BASE_INIT(user_define);
            user_define->m_obj_base.m_type = USER_DEFINE;
            user_define->m_obj_base.m_code = get_user_obj_code(L, user_define->m_obj_base.m_code);
            temp = dynast_cast(OBJ_TYPE, user_define);
            lua_pop( L, 1 );
        }
        lua_pop( L, 1 );
        current->m_children[i] = temp;
        current->m_count++;
    }
}

/**
 * @description: 创建库
 * @param {lua_State*} L
 * @return {*}
 */
LUAMOD_API int luaopen_boolean( lua_State* L )
{
    luaL_newlib( L, booleanlib );
    return 1;
}
