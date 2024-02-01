/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-01 21:25:32
 * @FilePath: /lua-cad/src/user_object/user_define_obj.c
 * @Description: 用户自定义对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <user_define_obj.h>
#include <to_openscad_code.h>
#include <lua.h>
#include <transform.h>

#include <string.h>

static const luaL_Reg userdefineobjlib[]
= { { "from_file", user_define_from_file }, { NULL, NULL } };


int user_define_from_file(lua_State* L)
{
    TODO从文件引入userdefine对象:
}

LUAMOD_API int luaopen_user_define_obj( lua_State* L )
{
    luaL_newlib( L, userdefineobjlib );
    return 1;
}
