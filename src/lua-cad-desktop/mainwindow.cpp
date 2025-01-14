#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "theme.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>

extern "C" {
    #include <lua.h>
    #include <lua-cad.h>
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

    scadAction = new QAction( "to Scad Code", this );
    renderAction = new QAction( "Render", this );

    versionAction = new QAction( "Version", this );
    connect( versionAction, &QAction::triggered, this, &MainWindow::showVersion );

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

void MainWindow::openFile( ) 
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
}


void MainWindow::saveFile( )
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
}

void MainWindow::showVersion( ) 
{ 
    QString content = QString( LUA_COPYRIGHT ) + "\n" + QString(LUA_AUTHORS) + "\n"  \
        + QString( LUA_CAD_COPYRIGHT ) + "\n" + QString( LUA_CAD_AUTHORS );
    QMessageBox::information( this, "Lua-cad Version", content );
}

void MainWindow::createMenus( )
{
    QMenu* fileMenu = menuBar( )->addMenu( "File" );
    fileMenu->addAction( openAction );
    fileMenu->addAction( saveAction );
    QMenu* RunMenu = menuBar( )->addMenu( "Run" );
    RunMenu->addAction( scadAction );
    RunMenu->addAction( renderAction );
    QMenu* HelpMenu = menuBar( )->addMenu( "Help" );
    HelpMenu->addAction( versionAction );
}

void MainWindow::createToolBars( )
{
    QToolBar* fileToolBar = addToolBar( "File" );
    fileToolBar->addAction( openAction );
    fileToolBar->addAction( saveAction );
}