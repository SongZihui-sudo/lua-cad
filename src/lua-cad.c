/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:32
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-02 00:21:18
 * @FilePath: /lua-cad/src/lua-cad.c
 * @Description: 一些全局函数的实现
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <lua-cad.h>
#include <lua.h>
#include <obj_type.h>
#include <stdlib.h>

int code( lua_State* L )
{
    D3OBJECT_BASE* obj = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, 1 ) );
    if ( !obj )
    {
        luaL_error( L, "object is null!" );
        return -1;
    }
    if ( obj->m_obj_base.m_type < OBJECT_END )
    {
        d3obj_to_code( L, obj );
    }
    const char* code = obj->m_obj_base.m_code;
    if ( !code )
    {
        luaL_error( L, "The code field is empty!" );
    }
    lua_pushstring( L, code );
    return 1;
}

int lua_cad_export( lua_State* L )
{
    const char* path = luaL_checkstring( L, 1 );
    D3OBJECT_BASE* obj    = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, 2 ) );
    if ( !obj )
    {
        luaL_error( L, "object is null!" );
        return -1;
    }
    if ( obj->m_obj_base.m_type < OBJECT_END )
    {
        d3obj_to_code( L, obj );
    }
    const char* code = obj->m_obj_base.m_code;
    // 写入文件
    FILE* fptr;
    fptr = fopen( path, "w" );
    if ( fptr == NULL )
    {
        luaL_error( L, "File write failed!" );
        exit( 1 );
    }
    fprintf( fptr, "%s", code );
    fclose( fptr );
    return 1;
}

int include_code( lua_State* L )
{
TODOinclude其他文件:
    return 1;
}

int import_module( lua_State* L )
{
TODO导入其他stl文件:
    return 1;
}
