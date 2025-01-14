#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "theme.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>

extern "C" {
    #include <lua.h>
    #include <lua-cad.h>
    #include <lualib.h>
     #include <lauxlib.h>
}

static QString report( lua_State* L, int status )
{
    QString msg;
    if ( status != LUA_OK )
    {
        msg = lua_tostring( L, -1 );
        lua_pop( L, 1 ); /* remove message */
    }
    return msg;
}

static bool loadLuaFile( lua_State* luaEnv, const char* fileName )
{
    int result = luaL_loadfile( luaEnv, fileName );
    result     = lua_pcall( luaEnv, 0, 0, 0 );
    return result;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QWidget* editorContiner = new QWidget( parent );
    ui->setupUi(this);
    
    theme* currentTheme = new theme("./");

    editor = new CodeEditor( currentTheme, editorContiner );

    openAction = new QAction( "Open", this );
    connect( openAction, &QAction::triggered, this, &MainWindow::openFile );

    saveAction = new QAction( "Save", this );
    connect( saveAction, &QAction::triggered, this, &MainWindow::saveFile );

    versionAction = new QAction( "Version", this );
    connect( versionAction, &QAction::triggered, this, &MainWindow::showVersion );

    runAction = new QAction("Run", this);
    connect( runAction, &QAction::triggered, this, &MainWindow::run );

    createMenus( );

    QVBoxLayout* layout = new QVBoxLayout( editorContiner );
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->addWidget( editor );
    
    editorContiner->setLayout( layout );
    setCentralWidget( editorContiner );

    setWindowTitle( "Lua-cad, lua for 3D" );
    resize( 800, 600 );
}

MainWindow::~MainWindow()
{
    delete ui; 
}

QString MainWindow::openFile( )
{
    QString fileName = QFileDialog::getOpenFileName( this,
                                                     "Open File",
                                                     "",
                                                     "Text Files (*.lua);;All Files (*)" );
    if ( !fileName.isEmpty( ) )
    {
        QFile file( fileName );
        if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            QTextStream in( &file );
            editor->setPlainText( in.readAll( ) );
            file.close( );
        }
        else
        {
            QMessageBox::warning( this, "Error", "Cannot open file!" );
        }
    }

    return fileName;
}


QString MainWindow::saveFile( )
{
    QString fileName = QFileDialog::getSaveFileName( this,
                                                     "Save File",
                                                     "",
                                                     "Text Files (*.lua);;All Files (*)" );
    if ( !fileName.isEmpty( ) )
    {
        QFile file( fileName );
        if ( file.open( QIODevice::WriteOnly | QIODevice::Text ) )
        {
            QTextStream out( &file );
            out << editor->toPlainText( );
            file.close( );
        }
        else
        {
            QMessageBox::warning( this, "Error", "Cannot save file!" );
        }
    }

    return fileName;
}

void MainWindow::showVersion( ) 
{ 
    QString content = QString( LUA_COPYRIGHT ) + "\n" + QString(LUA_AUTHORS) + "\n"  \
        + QString( LUA_CAD_COPYRIGHT ) + "\n" + QString( LUA_CAD_AUTHORS );
    QMessageBox::information( this, "Lua-cad Version", content );
}

void MainWindow::run( ) 
{
    lua_State* L = luaL_newstate( );
    luaL_openlibs( L );

    QString fileName = saveFile( );
    bool flag = loadLuaFile( L, fileName.toStdString().c_str() );
    qDebug( ) << flag;
    if ( flag )
    {
        QMessageBox::warning( this, "Run Error!", report(L, flag) );
    }
    else
    {
        QMessageBox::information( this, "Run OK!", fileName + " Run successfully!" );
    }

    lua_close( L );
}

void MainWindow::createMenus( )
{
    QMenu* fileMenu = menuBar( )->addMenu( "File" );
    fileMenu->addAction( openAction );
    fileMenu->addAction( saveAction );
    fileMenu->addAction( runAction );

    QMenu* HelpMenu = menuBar( )->addMenu( "Help" );
    HelpMenu->addAction( versionAction );
}

void MainWindow::createToolBars( )
{
    QToolBar* fileToolBar = addToolBar( "File" );
    fileToolBar->addAction( openAction );
    fileToolBar->addAction( saveAction );
}