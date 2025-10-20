/*
 * @Author: SongZihui-sudo 1751122876@qq.com
 * @Date: 2025-01-5 15:06
 * @LastEditors: songzihui 1751122876@qq.com
 * @FilePath: /lua-cad/src/main.cpp
 * @Description: main.cpp
 *
 * Copyright (c) 2025 by SongZihui-sudo 1751122876@qq.com, All Rights Reserved.
 */

#include "mainwindow.h"

#include <QApplication>

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    
    MainWindow w;
    w.show( );

    return app.exec( );
}
