/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-03 13:01:12
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

char* get_user_obj_code( lua_State* L, char* dest )
{
    lua_pushnumber( L, 1 );
    lua_gettable( L, -2 );
    const char* code = lua_tostring( L, -1 );
    dest = dynast_cast(char, malloc(sizeof(char) * strlen(code)));
    strcpy( dest, code);
    return dest;
}

LUAMOD_API int luaopen_user_define_obj( lua_State* L )
{
    luaL_newlib( L, userdefineobjlib );
    return 1;
}
