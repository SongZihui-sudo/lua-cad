#include "LuaRunner.h"

#include <QSocketNotifier>
#include <QFile>

// C 标准库/系统I/O
#ifdef _WIN32
    #include <io.h>
    #include <fcntl.h>
#else
    #include <unistd.h>
#endif
#include <cstdio>

// 辅助函数：报告错误（假设你有一个 report 函数）
QString LuaRunner::report( lua_State* L, int status )
{
    if ( status != 0 && lua_isstring( L, -1 ) )
    {
        QString err = QString::fromUtf8( lua_tostring( L, -1 ) );
        lua_pop( L, 1 ); // 弹出错误信息
        return err;
    }
    return "Unknown Lua Error";
}

void LuaRunner::toLogFile( QString output )
{
    emit this->luaOutput( output );

    if ( !this->m_logFileName.isEmpty( ) )
    {
        QFile file( this->m_logFileName );
        if ( file.open( QIODevice::Append | QIODevice::Text ) )
        {
            QTextStream out( &file );
            out << output;
        }
    }
}

int LuaRunner::luaPrint( lua_State* L )
{
    int nargs = lua_gettop( L );
    QString output;
    for ( int i = 1; i <= nargs; ++i )
    {
        const char* s = lua_tostring( L, i );
        if ( !s )
            s = luaL_tolstring( L, i, nullptr );
        output += s;
        if ( i < nargs )
            output += "\t";
    }
    output += "\n";

    LuaRunner* runner = static_cast< LuaRunner* >( lua_touserdata( L, lua_upvalueindex( 1 ) ) );
    if ( runner )
    {
        runner->toLogFile( output );
    }

    return 0;
}

void LuaRunner::run( )
{
    lua_State* L = luaL_newstate( );
    if ( !L )
    {
        emit runStatus( "Error: Could not create Lua state." );
        emit finished( false );
        return;
    }
    luaL_openlibs( L );

    // 替换 print
    lua_pushlightuserdata( L, this );
    lua_pushcclosure( L, &LuaRunner::luaPrint, 1 );
    lua_setglobal( L, "print" );

    bool isError = luaL_loadfile( L, m_luaFilePath.toStdString( ).c_str( ) ) || lua_pcall( L, 0, 0, 0 );

    QString message;
    if ( isError )
    {
        message = "Running Error: " + report( L, isError );
        emit runStatus( message );
        emit finished( false );
        emit this->luaOutput( message );
        toLogFile( message );
    }
    else
    {
        message = m_luaFilePath + " Run successfully!";
        emit runStatus( message );
        emit finished( true );
    }

    emit logFilePath( m_logFileName );
    lua_close( L );
}
