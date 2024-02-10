/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-08 23:13:05
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

int user_define_from_file( lua_State* L )
{
TODO从文件引入userdefine对象:
}

const char* get_user_obj_openscad_code( lua_State* L )
{
    lua_pushnumber( L, 1 );
    lua_gettable( L, -2 );
    const char* value = lua_tostring( L, -1 );
    return value;
}

LUAMOD_API int luaopen_user_define_obj( lua_State* L )
{
    luaL_newlib( L, userdefineobjlib );
    return 1;
}
