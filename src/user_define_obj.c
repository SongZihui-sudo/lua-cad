/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-01-28 12:39:48
 * @FilePath: /lua-cad/src/user_define_obj.c
 * @Description: 用户自定义对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <user_define_obj.h>

#include <lua.h>

static const luaL_Reg userdefineobjlib[]
= { { "postion", user_code_postion }, { NULL, NULL } };

int user_code_postion( lua_State* L )
{
    // 读一个table
    const int count = luaL_len( L, 2 );
    vec3 pos;
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        lua_gettable( L, 2 );
        double temp  = lua_tonumber( L, -1 );
        pos.m_xyz[i] = temp;
        lua_pop( L, 1 );
    }
    // 读 user_define 对象表
    lua_pushnumber( L, pos.m_xyz[0] );
    lua_setfield(L, -2, "x");
    lua_pushnumber( L, pos.m_xyz[1] );
    lua_setfield(L, -2, "y");
    lua_pushnumber( L, pos.m_xyz[2] );
    lua_setfield(L, -2, "z");
    lua_setfield(L, -2, "offset");
    return 1;
}

LUAMOD_API int luaopen_user_define_obj( lua_State* L )
{
    luaL_newlib( L, userdefineobjlib );
    return 1;
}
