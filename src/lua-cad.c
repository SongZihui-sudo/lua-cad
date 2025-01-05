/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:22:32
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-02-07 13:44:46
 * @FilePath: /lua-cad/src/lua-cad.c
 * @Description: some global functions
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include "lauxlib.h"
#include <lua-cad.h>
#include <lua.h>
#include <obj_type.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <to_openscad_code.h>
#include <user_define_obj.h>

char* openscad_path = "openscad";
char* hob3l_path    = "hob3l.x";

static char* check_code( lua_State* L, int index )
{
    char* code;
    if ( lua_istable( L, index ) )
    {
        code = get_user_obj_code( L, code );
    }
    else if ( lua_isstring( L, index ) )
    {
        code = lua_tostring( L, index );
    }
    else
    {
        D3OBJECT_BASE* obj = dynast_cast( D3OBJECT_BASE, lua_touserdata( L, index ) );
        lua_getglobal( L, "output_mode" );
        const char* mode = lua_tostring( L, -1 );
        if ( !obj )
        {
            luaL_error( L, "object is null!" );
            return "";
        }
        if ( ( !mode || !strcmp( mode, OUPUT_MODE_OPENSCAD ) )
             && ( is_d3object( obj->m_obj_base.m_type ) || is_d2object( obj->m_obj_base.m_type ) ) )
        {
            obj_to_openscad_code( L, obj );
        }
        else if ( ( !mode || !strcmp( mode, OUPUT_MODE_OPENSCAD ) )
                  && is_boolean( obj->m_obj_base.m_type ) )
        {
            boolean_to_openscad_code( L, ( OBJ_TYPE* )obj );
        }
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

static int write_file( lua_State* L, const char* path, const char* code )
{
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

int lua_cad_export( lua_State* L )
{
    char* code;
    code             = check_code( L, 2 );
    const char* path = lua_tostring( L, 1 );
    // write code to file
    write_file( L, path, code );
    return 0;
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

int set_openscad_path( lua_State* L )
{
    openscad_path = luaL_checkstring( L, 1 );
    return 0;
}

int set_hob3l_path( lua_State* L )
{
    hob3l_path = luaL_checkstring( L, 1 );
    return 0;
}

static const void* lua_get_value( lua_State* L, char* key, short index )
{
    lua_pushstring( L, key );
    lua_gettable( L, index ); 
    if ( lua_isstring( L, -1 ) )
    {
        const void* ret = lua_tostring( L, -1 );
        lua_pop( L, 1 );
        return ret;
    }
    return NULL;
}

int render( lua_State* L )
{
    const char* render_type = lua_tostring( L, 1 );
    fprintf( stdout, "render_type: %s\n", render_type );
    if ( !strcmp( render_type, "stl" ) || !strcmp( render_type, "STL" ) )
    {
        // save code
        char* code;
        code = check_code( L, 2 );
        char* use_hob3l;
        // read parameters
        char* scad_path      = dynast_cast(char, lua_get_value( L, "scad_path",3 ));
        if ( !scad_path )
        {
            luaL_error( L,
                        "scad file output path is not set!\n Usage: render('stl', object, "
                        "{scad_path='xx', stl_path='xx', use_hob3l=true/false});" );
        }
        // stl path
        char* output_path = dynast_cast(char, lua_get_value( L, "stl_path", 3 ));
        if ( !output_path )
        {
            luaL_error( L,
                        "stl file output path is not set!\n Usage: render('stl', object, "
                        "{scad_path='xx', stl_path='xx', use_hob3l=true/false});" );
        }
        // use hob3l
        use_hob3l = dynast_cast(char, lua_get_value( L, "use_hob3l", 3 ));
        if ( !use_hob3l )
        {
            luaL_error( L,
                        "use_hob3l is not set!\n Usage: render('stl', object, {scad_path='xx', "
                        "stl_path='xx', use_hob3l=true/false});" );
        }
        // write code to file
        write_file( L, scad_path, code );
        
        char* to_stl = dynast_cast( char, malloc( sizeof( char ) * 128 ) );
        if ( !strcmp(use_hob3l, "true") )
        {
            char* medium_ouput_path
            = dynast_cast( char, malloc( sizeof( char ) * strlen( output_path ) ) );
            sprintf( medium_ouput_path, "%s", output_path );
            medium_ouput_path[strlen( output_path ) - 1] = 'g';
            medium_ouput_path[strlen( output_path ) - 2] = 's';
            medium_ouput_path[strlen( output_path ) - 3] = 'c';
            char* to_csg = dynast_cast( char, malloc( sizeof( char ) * 128 ) );
            sprintf( to_csg, "%s %s -o %s", openscad_path, scad_path, medium_ouput_path );
            sprintf( to_stl, "%s %s -o %s", hob3l_path, medium_ouput_path, output_path );

            // run openscad
            int error = system( to_csg );
            if ( error == -1 )
            {
                luaL_error( L, "system call failed\n" );
                return -1;
            }
            else
            {
                fprintf( stdout, "Command execution completed, return value: %d\n", error );
            }

            free( medium_ouput_path );
            free( to_csg );
        }
        else
        {
            sprintf( to_stl, "%s %s -o %s", openscad_path, scad_path, output_path );
        }

        // run to stl
        int error = system( to_stl );
        if ( error == -1 )
        {
            luaL_error( L, "system call failed\n" );
            return -1;
        }
        else
        {
            fprintf( stdout, "Command execution completed, return value: %d\n", error );
        }

        free( to_stl );
    }
    else
    {
        luaL_error( L, "Unknown render type" );
    }
    return 0;
}
