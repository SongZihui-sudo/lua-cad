/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2025-01-5 15:06
 * @LastEditors: songzihui 1751122876@qq.com
 * @FilePath: /lua-cad/src/main.cpp
 * @Description: main.cpp
 *
 * Copyright (c) 2025 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include "luarunner.h"
#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    
    MainWindow w;
    w.show( );

    auto* luaThread = new LuaRunner( &w );
    QObject::connect( luaThread,
                      &LuaRunner::outputReady,
                      [&]( const QString& msg ) { qInfo( ).noquote( ) << msg.trimmed( ); } );
    QObject::connect( luaThread, &QThread::finished, luaThread, &QObject::deleteLater );
    luaThread->start( );

    return app.exec( );
}
