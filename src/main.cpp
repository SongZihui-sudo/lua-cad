/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2025-01-5 15:06
 * @LastEditors: songzihui 1751122876@qq.com
 * @FilePath: /lua-cad/src/main.cpp
 * @Description: main.cpp
 *
 * Copyright (c) 2025 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

extern "C" {
    #include <lauxlib.h>
    #include <lua.h>
    #include <lualib.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
    #include <lua-cad.h>
}

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QApplication>

#include "lua-cad-desktop/mainwindow.h"

#pragma comment( lib, "lua.lib" )

#if !defined( LUA_PROGNAME )
#define LUA_PROGNAME "lua"
#endif

static const char* progname = LUA_PROGNAME;

/**
 * @description: load lua file
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
 * @description: print error message
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
 * @description: read error message
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
 * @description: run single line lua
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

/**
 * @description: print version message
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
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Lua-cad\nUsage: lua-cad [Options\lua_file]");
    parser.addHelpOption();

    QCommandLineOption guiOption(QStringList() << "g" << "gui", "Open the application in GUI mode");
    parser.addOption(guiOption);
    QCommandLineOption versionOption(QStringList() << "v" << "version", "Display program version");
    parser.addOption(versionOption);

    parser.process(a);

    if (parser.isSet(guiOption)) {
        MainWindow w;
        w.show();
        return a.exec();
    }
    else if(parser.isSet(versionOption))
    {
        print_version();
    }
    else
    {
        lua_State* L = luaL_newstate( );
        luaL_openlibs( L );

        if (argc > 1)
        {
            // load the script into the Lua environment
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
    }
   
    return 0;
}