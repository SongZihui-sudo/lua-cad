#pragma once
#include <QThread>
#include <QString>
#include <QObject>
#include <iostream>

extern "C" {
    #include <lauxlib.h>
    #include <lua.h>
    #include <lualib.h>
    #include "lua-cad.h"
}

class LuaRunner : public QThread
{
    Q_OBJECT
public:
    explicit LuaRunner(QObject* parent = nullptr)
        : QThread(parent)
    {
    }

    void print_version()
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

signals:
    void outputReady(const QString& text);

protected:
    void run() override
    {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);

        emit outputReady("Lua-cad interactive mode.\nType 'quit' or '\\q' to exit.\n");

        while (true) {
            std::cout << "\033[0m\033[1;34mlua-cad\033[0m \033[0m\033[1;33m>>>\033[0m ";
            std::cout.flush();

            char line[256];
            if (!fgets(line, sizeof(line), stdin))
                break;

            if (!strcmp(line, "quit\n") || !strcmp(line, "\\q\n"))
                break;

            int status = luaL_loadstring(L, line);
            if (status == LUA_OK) {
                status = lua_pcall(L, 0, LUA_MULTRET, 0);
            }

            if (status != LUA_OK) {
                const char* msg = lua_tostring(L, -1);
                emit outputReady(QString("[Error] ") + msg + "\n");
                lua_pop(L, 1);
            }
        }

        lua_close(L);
        emit outputReady("Lua session closed.\n");
    }
};
