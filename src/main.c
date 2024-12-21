/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2024-01-26 20:10:42
 * @LastEditors: songzihui 1751122876@qq.com
 * @LastEditTime: 2024-01-27 21:58:48
 * @FilePath: /lua-cad/src/main.c
 * @Description: main.c
 *
 * Copyright (c) 2024 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#pragma comment( lib, "lua.lib" )

#if !defined( LUA_PROGNAME )
#define LUA_PROGNAME "lua"
#endif

static const char* progname = LUA_PROGNAME;

/**
 * @description: 加载 lua 文件
 * @param {lua_State*} luaEnv
 * @param {char*} fileName
 * @return {*}
 */
bool loadLuaFile( lua_State* luaEnv, const char* fileName )
{
    int result = luaL_loadfile( luaEnv, fileName );
    result = lua_pcall( luaEnv, 0, 0, 0 );
    return result;
}

/**
 * @description: 打印错误信息
 * @param {char*} pname
 * @param {char*} msg
 * @return {*}
 */
static void l_message( const char* pname, const char* msg )
{
    if ( pname )
        lua_writestringerror( "%s: ", pname );
    lua_writestringerror( "%s\n", msg );
}

/**
 * @description: 读错误信息
 * @param {lua_State*} L
 * @param {int} status
 * @return {*}
 */
static int report( lua_State* L, int status )
{
    if ( status != LUA_OK )
    {
        const char* msg = lua_tostring( L, -1 );
        l_message( progname, msg );
        lua_pop( L, 1 ); /* remove message */
    }
    return status;
}

/**
 * @description: 运行一行 lua
 * @param {lua_State*} luaEnv
 * @param {char*} line
 * @return {*}
 */
static int loadluaLine( lua_State* luaEnv, const char* line )
{

    int result = luaL_loadstring( luaEnv, line );
    if ( result )
    {
        return false;
    }

    result = lua_pcall( luaEnv, 0, 0, 0 );
    return result;
}

#define LUA_CAD_COPYRIGHT "Copyright (C) 2024 lua-cad Lua for Openscad"
#define LUA_CAD_AUTHORS "SongZihui-sudo 1751122876@qq.com https://szhwho.top"

/**
 * @description: 打印版本信息
 * @return {*}
 */
static void print_version( void )
{
    lua_writestring( LUA_COPYRIGHT, strlen( LUA_COPYRIGHT ) );
    lua_writeline( );
    lua_writestring( LUA_AUTHORS, strlen( LUA_AUTHORS ) );
    lua_writeline( );
    lua_writestring( LUA_CAD_COPYRIGHT, strlen( LUA_CAD_COPYRIGHT ) );
    lua_writeline( );
    lua_writestring( LUA_CAD_AUTHORS, strlen( LUA_CAD_AUTHORS ) );
    lua_writeline( );
}

/**
 * @description: main
 * @param {int} argc
 * @param {char**} argv
 * @return {*}
 */
int main( int argc, char** argv )
{
    lua_State* L = luaL_newstate( );
    luaL_openlibs( L );

    if ( argc > 1 )
    {
        // 加载脚本到Lua环境中.
        int status = loadLuaFile( L, argv[1] );
        report( L, status );
    }
    else
    {
        print_version( );
        while ( 1 )
        {
            printf( "\033[0m\033[1;34mlua-cad\033[0m \033[0m\033[1;33m>>>\033[0m " );
            char line[64];
            fgets(line, sizeof(line), stdin);
            if ( !strcmp( line, "quit" ) || !strcmp( line, "\\q" ) )
            {
                lua_close( L );
                return 0;
            }
            int status = loadluaLine( L, line );
            report( L, status );
        }
    }

    lua_close( L );

    return 0;
}
