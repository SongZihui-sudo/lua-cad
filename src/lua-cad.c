/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:32
 * @LastEditors: SongZihui-sudo 1751122876@qq.com
 * @LastEditTime: 2024-02-08 23:36:08
 * @FilePath: /lua-cad/src/lua-cad.c
 * @Description: 一些全局函数的实现
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <lua-cad.h>
#include <lua.h>
#include <obj_type.h>
#include <stdlib.h>
#include <to_openscad_code.h>
#include <user_define_obj.h>

#ifdef DEAL_II
#include <dealii.h>
#endif

#include <gmsh.h>

static void check_output_mode( lua_State* L, D3OBJECT_BASE* obj )
{
    lua_getglobal( L, "output_mode" );
    const char* mode = lua_tostring( L, -1 );
    if ( !obj )
    {
        luaL_error( L, "object is null!" );
    }
    if ( !mode || !strcmp( mode, OUPUT_MODE_OPENSCAD ) )
    {
        if ( is_d3object( obj->m_obj_base.m_type ) || is_d2object( obj->m_obj_base.m_type ) )
        {
            obj_to_openscad_code( L, obj );
        }
        else if ( is_boolean( obj->m_obj_base.m_type ) )
        {
            boolean_to_openscad_code( L, ( OBJ_TYPE* )obj );
        }
        else
        {
            luaL_error( L, "Unsupported export object!" );
        }
    }
    else if ( !strcmp( mode, OUTPUT_MODE_GMSH ) )
    {
        if ( is_boolean( obj->m_obj_base.m_type ) )
        {
            boolean_to_gmsh_code( L, obj );
        }
        else
        {
            obj_to_gmsh_code( L, obj );
        }
    }
    else
    {
        luaL_error( L, "Unsupported output format!" );
    }
}

static char* check_table( lua_State* L )
{
    lua_getglobal( L, "output_mode" );
    const char* mode = lua_tostring( L, -1 );
    if ( !mode || !strcmp( mode, OUPUT_MODE_OPENSCAD ) )
    {
        return get_user_obj_openscad_code( L );
    }
    else if ( !strcmp( mode, OUTPUT_MODE_GMSH ) )
    {
        return get_obj_table_gmsh_code( L );
    }
    else
    {
        luaL_error( L, "Unsupported output format!" );
    }
    return NULL;
}

static char* check_code( lua_State* L, int index )
{
    char* code;
    if ( lua_istable( L, index ) )
    {
        code = check_table( L );
    }
    else if ( lua_isstring( L, index ) )
    {
        code = lua_tostring( L, index );
    }
    else
    {
        D3OBJECT_BASE* obj = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, index ) );
        check_output_mode( L, obj );
        code = obj->m_obj_base.m_code;
    }
    return code;
}

int code( lua_State* L )
{
    char* code;
    code = check_code( L, 1 );
    if ( !code )
    {
        luaL_error( L, "The code field is empty!" );
    }
    lua_pushstring( L, code );
    return 1;
}

int lua_cad_export( lua_State* L )
{
    char* code;
    code             = check_code( L, 2 );
    const char* path = lua_tostring( L, 1 );
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
    char code[64] = "include <";
    strcat( code, lua_tostring( L, 1 ) );
    strcat( code, ">\n" );
    lua_pushstring( L, code );
    return 1;
}

int import_module( lua_State* L )
{
    char code[64] = "import (";
    strcat( code, lua_tostring( L, 1 ) );
    strcat( code, ")\n" );
    lua_pushstring( L, code );
    return 1;
}

int render( lua_State* L )
{
    lua_getglobal( L, "output_mode" );
    const char* mode  = lua_tostring( L, -1 );
    OBJ_BASE* current = lua_touserdata( L, 1 );
    if ( !current )
    {
        luaL_error( L, "object is null!" );
        return -1;
    }
    return 1;
}
