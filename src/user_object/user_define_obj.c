/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-02 17:01:59
 * @FilePath: /lua-cad/src/user_object/user_define_obj.c
 * @Description: 用户自定义对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <lua.h>
#include <to_openscad_code.h>
#include <transform.h>
#include <user_define_obj.h>

#include <string.h>

static const luaL_Reg userdefineobjlib[] = { { "from_file", user_define_from_file }, { NULL, NULL } };

int user_define_from_file( lua_State* L ){ TODO从文件引入userdefine对象 : }

D3OBJECT_BASE* table_to_Cstruct( lua_State* L )
{
    D3OBJECT_BASE* new_obj = dynast_cast( D3OBJECT_BASE, sizeof( D3OBJECT_BASE ) );
    D3OBJECT_BASE_INIT( new_obj );
    lua_pushnumber( L, 1 );
    lua_gettable( L, 1 );
    new_obj->m_obj_base.m_code = lua_tostring( L, -1 );
    lua_pop( L, -1 );
    lua_pushstring( L, "offset" );
    lua_gettable( L, -2 );
    int count = luaL_len( L, -2 );
    for ( int i = 0; i < count; i++ )
    {
        lua_pushnumber( L, i + 1 );
        new_obj->m_offset.m_xyz[i] = lua_tonumber(L, -1);
        lua_pop( L, -1 );
    }
    return new_obj;
}

LUAMOD_API int luaopen_user_define_obj( lua_State* L )
{
    luaL_newlib( L, userdefineobjlib );
    return 1;
}
