/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:32
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-01-26 20:45:40
 * @FilePath: /lua-cad/src/boolean.c
 * @Description: bool 操作
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <string.h>

#include <boolean.h>
#include <to_code.h>

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

void boolean_init( lua_State* L, OBJ_TYPE type )
{
    // 创建一个 intersection 对象
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
        unsigned short* temp   = lua_touserdata( L, -1 );
        current->m_children[i] = temp;
        lua_pop( L, 1 );
        current->m_count++;
    }
    boolean_to_code( L, ( OBJ_TYPE* )current );
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
