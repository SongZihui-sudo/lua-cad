#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>
#include <QIcon>
#include <QInputDialog>

#include "stlRender.h"
#include "luaRunner.h"

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
: QMainWindow( parent )
, searchDialog( nullptr )
, replaceDialog( nullptr ) 
    , ui(new Ui::MainWindow)
{
    this->setWindowIcon( QIcon( "./icon.ico" ) );
    QWidget* editorContiner = new QWidget( parent );
    ui->setupUi(this);

    currentConfig = new Config( "./lua-cad-desktop-config.json" );
   
    editor = new CodeEditor( currentConfig->currentTheme, currentConfig->keywords, editorContiner );

    openAction = new QAction( "Open", this );
    connect( openAction, &QAction::triggered, this, &MainWindow::openFile );
    saveAction = new QAction( "Save", this );
    connect( saveAction, &QAction::triggered, this, &MainWindow::saveFile );
    versionAction = new QAction( "Version", this );
    connect( versionAction, &QAction::triggered, this, &MainWindow::showVersion );
    runAction = new QAction("Run", this);
    connect( runAction, &QAction::triggered, this, &MainWindow::run );
    unDoAction = new QAction( "UnDo", this );
    connect( unDoAction, &QAction::triggered, editor, &CodeEditor::undo );
    reDoAction = new QAction( "ReDo", this );
    connect( reDoAction, &QAction::triggered, editor, &CodeEditor::redo );
    cpyAction    = new QAction( "Copy", this );
    connect( cpyAction, &QAction::triggered, editor, &CodeEditor::copy );
    pasteAction  = new QAction( "Paste", this );
    connect( pasteAction, &QAction::triggered, editor, &CodeEditor::paste );
    cutAction = new QAction( "Cut", this );
    connect( cutAction, &QAction::triggered, editor, &CodeEditor::cut );
    searchAction = new QAction( "Search", this );
    connect( searchAction, &QAction::triggered, this, &MainWindow::openSearchDialog );
    replaceAction = new QAction( "Replace", this );
    connect( replaceAction, &QAction::triggered, this, &MainWindow::openReplaceDialog );
    stlRenderAction = new QAction( "Open Stl", this );
    connect( stlRenderAction, &QAction::triggered, this, &MainWindow::openStlFile );
    
    createMenus( );

    assert( currentConfig->currentKeyMap->setKey( replaceAction, "replace" ) );
    assert( currentConfig->currentKeyMap->setKey( unDoAction, "undo" ) );
    assert( currentConfig->currentKeyMap->setKey( reDoAction, "redo" ) );
    assert( currentConfig->currentKeyMap->setKey( searchAction, "search" ) );
    assert( currentConfig->currentKeyMap->setKey( cpyAction, "copy" ) );
    assert( currentConfig->currentKeyMap->setKey( pasteAction, "paste" ) );
    assert( currentConfig->currentKeyMap->setKey( cutAction, "cut" ) );

    QVBoxLayout* layout = new QVBoxLayout( editorContiner );
    layout->setContentsMargins( 0, 0, 0, 0 );
    layout->addWidget( editor );
    
    editorContiner->setLayout( layout );
    setCentralWidget( editorContiner );

    setWindowTitle( "Lua-cad, lua for 3D" );
    resize( 800, 600 );

    currentFile = "";
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
            currentFile = fileName;
        }
        else
        {
            QMessageBox::warning( this, "Error", "Cannot open file!" );
        }
    }

    return fileName;
}


QString MainWindow::saveFile()
{
    QString fileName = "";
    if ( currentFile == "" )
    {
        fileName = QFileDialog::getSaveFileName( this,
                                                 "Save File",
                                                 "",
                                                 "Text Files (*.lua);;All Files (*)" );
    }
    else
    {
        fileName = currentFile;
    }
     
    if ( !fileName.isEmpty( ) )
    {
        QFile file( fileName );
        if ( file.open( QIODevice::WriteOnly | QIODevice::Text ) )
        {
            QTextStream out( &file );
            out << editor->toPlainText( );
            file.close( );
            currentFile = fileName;
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
    QString fileName;
    if ( currentFile.isEmpty( ) || editor->isChange( ) )
    {
        fileName = saveFile( );
        if ( fileName.isEmpty( ) )
        {
            statusBar( )->showMessage( "Run cancelled: File not saved." );
            return;
        }
        currentFile = fileName;
    }

    QThread* thread          = new QThread( );
    LuaRunner* cur_luaRunner = new LuaRunner( );
    cur_luaRunner->setLuaFile( currentFile );
    cur_luaRunner->moveToThread( thread );

    connect( cur_luaRunner,
             &LuaRunner::luaOutput,
             this,
             [this]( const QString& txt )
             {
                 qDebug( ).noquote( ) << "[Lua] " << txt.trimmed( );
             } );

    connect( cur_luaRunner,
             &LuaRunner::runStatus,
             this,
             [this]( const QString& msg ) { this->statusBar( )->showMessage( msg ); } );

    connect( cur_luaRunner,
             &LuaRunner::logFilePath,
             this,
             [this]( const QString& path )
             { 
                 qDebug( ).noquote( ) << QString( "Output saved to log file: %1" ).arg( path );
             } );

    connect( thread, &QThread::started, cur_luaRunner, &LuaRunner::run );

    thread->start( );

    connect( cur_luaRunner, &LuaRunner::finished, thread, &QThread::quit );
    connect( thread, &QThread::finished, thread, &QThread::deleteLater );
    connect( thread, &QThread::finished, cur_luaRunner, &LuaRunner::deleteLater );
}

void MainWindow::createMenus( )
{
    QMenu* fileMenu = menuBar( )->addMenu( "File" );
    fileMenu->addAction( openAction );
    fileMenu->addAction( stlRenderAction );
    fileMenu->addAction( saveAction );
    fileMenu->addAction( runAction );

    QMenu* EditMenu = menuBar( )->addMenu( "Edit" );
    EditMenu->addAction( cpyAction );
    EditMenu->addAction( pasteAction );
    EditMenu->addAction( cutAction );
    EditMenu->addAction( unDoAction );
    EditMenu->addAction( reDoAction );
    EditMenu->addAction( searchAction );
    EditMenu->addAction( replaceAction );

    QMenu* HelpMenu = menuBar( )->addMenu( "Help" );
    HelpMenu->addAction( versionAction );
}

void MainWindow::createToolBars( )
{
    QToolBar* fileToolBar = addToolBar( "File" );
    fileToolBar->addAction( openAction );
    fileToolBar->addAction( saveAction );
}

  void MainWindow::findNext( )
{
      QString searchText;
      if (searchDialog)
      {
          searchText = searchDialog->getSearchText( );
      }
      else
      {
          searchText = replaceDialog->getSearchText( );
      }

      if ( searchText.isEmpty( ) )
      {
          return;
      }

      // 查找下一个匹配项
      searchCursor = editor->document( )->find( searchText, searchCursor );

      if ( !searchCursor.isNull( ) )
      {
          highlightCurrentMatch( );
      }
      else
      {
          searchCursor = QTextCursor( editor->document( ) );
          editor->setExtraSelections( highlights );
      }
  }

void MainWindow::findPrevious( )
{
    QString searchText;
    if ( searchDialog )
    {
        searchText = searchDialog->getSearchText( );
    }
    else
    {
        searchText = replaceDialog->getSearchText( );
    }
     
    if ( searchText.isEmpty( ) )
    {
        return;
    }

    // 查找上一个匹配项
    searchCursor = editor->document( )->find( searchText, searchCursor, QTextDocument::FindBackward );

    if ( !searchCursor.isNull( ) )
    {
        highlightCurrentMatch( );
    }
    else
    {
        searchCursor = QTextCursor( editor->document( )->end( ) );
        editor->setExtraSelections( highlights );
    }
}


void MainWindow::clearHighlights( )
{
    highlights.clear( );
    editor->setExtraSelections( highlights ); // 清空之前的高亮
}

void MainWindow::highlightCurrentMatch( )
{
    // 清除高亮
    clearHighlights( );

    // 设置高亮格式
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground( currentConfig->currentTheme->map["searchMatchColor"].getColor() );

    // 保存高亮信息
    QTextEdit::ExtraSelection highlight;
    highlight.cursor = searchCursor;
    highlight.format = highlightFormat;

    highlights.append( highlight );
    editor->setExtraSelections( highlights );
}

void MainWindow::openSearchDialog( )
{
    if ( !searchDialog )
    {
        searchDialog = new SearchDialog( this );

        // 连接信号到槽
        connect( searchDialog, &SearchDialog::findNext, this, &MainWindow::findNext );
        connect( searchDialog, &SearchDialog::findPrevious, this, &MainWindow::findPrevious );
        connect( searchDialog, &SearchDialog::finished, this, &MainWindow::clearHighlights );
    }

    searchDialog->show( );
    searchDialog->raise( );
    searchDialog->activateWindow( );
}

void MainWindow::openReplaceDialog( )
{
    if ( !replaceDialog )
    {
        replaceDialog = new ReplaceDialog( this );

        // 连接 ReplaceDialog 的信号到 MainWindow 的槽函数
        connect( replaceDialog, &ReplaceDialog::findPrevious, this, &MainWindow::findPrevious );
        connect( replaceDialog, &ReplaceDialog::findNext, this, &MainWindow::findNext );
        connect( replaceDialog, &ReplaceDialog::replace, this, &MainWindow::replace );
        connect( replaceDialog, &ReplaceDialog::replaceAll, this, &MainWindow::replaceAll );
        connect( replaceDialog, &ReplaceDialog::finished, this, &MainWindow::clearHighlights );
    }
    replaceDialog->show( );
    replaceDialog->raise( );
    replaceDialog->activateWindow( );
}

void MainWindow::replaceAll( )
{
    QString searchText  = replaceDialog->getSearchText( );
    QString replaceText = replaceDialog->getReplaceText( );
    QTextCursor cursor  = editor->document( )->find( searchText );

    while ( !cursor.isNull( ) )
    {
        cursor.insertText( replaceText );
        cursor = editor->document( )->find( searchText, cursor );
    }
}


void MainWindow::replace( )
{
    QString searchText  = replaceDialog->getSearchText( );
    QString replaceText = replaceDialog->getReplaceText( );
    if ( searchCursor.hasSelection( ) && searchCursor.selectedText( ) == searchText )
    {
        searchCursor.insertText( replaceText ); // 替换选中的文本
    }
    findNext( ); // 查找下一个匹配项
}

QString MainWindow::openStlFile( ) 
{ 
     QString fileName = QFileDialog::getOpenFileName( this,
                                                     "Open STL File",
                                                     "",
                                                     "Text Files (*.stl);;All Files (*)" );
    if ( !fileName.isEmpty( ) )
    {
        openStlRender( fileName );
    }
    else
    {
        QMessageBox::warning( this, "Error", "Cannot open file!" );
    }
    return fileName;
}
