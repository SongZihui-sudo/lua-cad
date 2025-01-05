#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    editor = new CodeEditor( this );
    LuaCadSyntaxHighlighter* highlighter = new LuaCadSyntaxHighlighter( editor->document( ) );

    setCentralWidget( editor );

    openAction = new QAction( "Open", this );
    connect( openAction, &QAction::triggered, this, &MainWindow::openFile );

    saveAction = new QAction( "Save", this );
    connect( saveAction, &QAction::triggered, this, &MainWindow::saveFile );

    scadAction = new QAction( "to Scad Code", this );
    renderAction = new QAction( "Render", this );

    createMenus( );

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

void MainWindow::createMenus( )
{
    QMenu* fileMenu = menuBar( )->addMenu( "File" );
    fileMenu->addAction( openAction );
    fileMenu->addAction( saveAction );
    QMenu* RunMenu = menuBar( )->addMenu( "Run" );
    RunMenu->addAction( scadAction );
    RunMenu->addAction( renderAction );
}

void MainWindow::createToolBars( )
{
    QToolBar* fileToolBar = addToolBar( "File" );
    fileToolBar->addAction( openAction );
    fileToolBar->addAction( saveAction );
}