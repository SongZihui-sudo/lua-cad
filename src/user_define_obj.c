/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-01-27 22:43:14
 * @FilePath: /lua-cad/src/user_define_obj.c
 * @Description: 用户自定义对象
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <user_define_obj.h>

#include <lua.h>

static const luaL_Reg userdefineobjlib[] = { {"obj_name", user_code_info}, { NULL, NULL } };

int user_code_info(lua_State* L)
{
    int index = luaL_checkinteger(L, 1);
    lua_pushstring(L, userobjects.m_names[index]);
    return 1;
}

LUAMOD_API int luaopen_user_define_obj( lua_State* L )
{
    luaL_newlib( L, userdefineobjlib );
    return 1;
}
