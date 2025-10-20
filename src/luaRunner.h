#ifndef LUARUNNER
#define LUARUNNER

#include <QObject>
#include <QString>
#include <QDateTime>

extern "C" {
    #include <lauxlib.h>
    #include <lua.h>
    #include <lualib.h>
    
    #include "lua-cad.h"
}

class LuaRunner : public QObject
{
    Q_OBJECT
public:
    explicit LuaRunner( QObject* parent = nullptr )
    {
        QString timestamp = QDateTime::currentDateTime( ).toString( "yyyyMMdd_hhmmsszzz" );
        m_logFileName     = QString( "./lua-cad_output_%1.log" ).arg( timestamp );
    };

    void setLuaFile( const QString& luaPath ) { m_luaFilePath = luaPath; }

    void setLogFile( const QString& logPath ) { m_logFileName = logPath; }

    QString getLogFile( ) { return m_logFileName; }

    void printVersion( )
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
    void finished( bool success );
    void runStatus( const QString& message );
    void logFilePath( const QString& path );
    void luaOutput( const QString& text ); // 新增，用于实时显示 Lua print 输出

public slots:
    void run( );

private:
    QString m_luaFilePath;
    QString m_logFileName;
    QString report( lua_State* L, int status );

    static int luaPrint( lua_State* L ); // 静态函数
    void toLogFile( QString output );
};

#endif
