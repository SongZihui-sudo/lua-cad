#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>

#include "codeEditer.h"
#include "stlRender.h"
#include "config.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    ReplaceDialog( QWidget* parent = nullptr )
    : QDialog( parent )
    {
        setWindowTitle( "Find and Replace" );
        setFixedSize( 300, 200 );

        QVBoxLayout* mainLayout = new QVBoxLayout( this );

        QLabel* findLabel = new QLabel( "Find:", this );
        mainLayout->addWidget( findLabel );

        findInput = new QLineEdit( this );
        mainLayout->addWidget( findInput );

        QLabel* replaceLabel = new QLabel( "Replace with:", this );
        mainLayout->addWidget( replaceLabel );

        replaceInput = new QLineEdit( this );
        mainLayout->addWidget( replaceInput );

        QHBoxLayout* buttonLayout     = new QHBoxLayout( );
        QPushButton* prevButton       = new QPushButton( "Find Prev", this );
        QPushButton* nextButton       = new QPushButton( "Find Next", this );
        QPushButton* replaceButton    = new QPushButton( "Replace", this );
        QPushButton* replaceAllButton = new QPushButton( "Replace All", this );

        connect( prevButton, &QPushButton::clicked, this, &ReplaceDialog::findPrevious );
        connect( nextButton, &QPushButton::clicked, this, &ReplaceDialog::findNext );
        connect( replaceButton, &QPushButton::clicked, this, &ReplaceDialog::replace );
        connect( replaceAllButton, &QPushButton::clicked, this, &ReplaceDialog::replaceAll );

        buttonLayout->addWidget( prevButton );
        buttonLayout->addWidget( nextButton );
        buttonLayout->addWidget( replaceButton );
        buttonLayout->addWidget( replaceAllButton );
        mainLayout->addLayout( buttonLayout );
    }

    QString getSearchText( ) const { return findInput->text( ); }

    QString getReplaceText( ) const { return replaceInput->text( ); }

signals:
    void findNext( );
    void findPrevious( );
    void replace( ); 
    void replaceAll( );

private:
    QLineEdit* findInput;
    QLineEdit* replaceInput;
};

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    SearchDialog( QWidget* parent = nullptr )
    : QDialog( parent )
    {
        setWindowTitle( "Search" );
        setFixedSize( 300, 150 );

        QVBoxLayout* mainLayout = new QVBoxLayout( this );

        QLabel* label = new QLabel( "Enter text to find:", this );
        mainLayout->addWidget( label );

        searchInput = new QLineEdit( this );
        mainLayout->addWidget( searchInput );
        QHBoxLayout* buttonLayout = new QHBoxLayout( );
        QPushButton* nextButton   = new QPushButton( "Next", this );
        QPushButton* prevButton   = new QPushButton( "Previous", this );

        connect( nextButton, &QPushButton::clicked, this, &SearchDialog::onNextClicked );
        connect( prevButton, &QPushButton::clicked, this, &SearchDialog::onPreviousClicked );

        buttonLayout->addWidget( prevButton );
        buttonLayout->addWidget( nextButton );
        mainLayout->addLayout( buttonLayout );
    }

    QString getSearchText( ) const { return searchInput->text( ); }

signals:
    void findNext( );
    void findPrevious( );

private slots:
    void onNextClicked( ) { emit findNext( ); }
    void onPreviousClicked( ) { emit findPrevious( ); }

private:
    QLineEdit* searchInput;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CodeEditor* editor;

    QAction* openAction;
    QAction* saveAction;
    QAction* runAction;
    QAction* versionAction;
    QAction* reDoAction;
    QAction* unDoAction;
    QAction* searchAction;
    QAction* cpyAction;
    QAction* pasteAction;
    QAction* cutAction;
    QAction* replaceAction;
    QAction* stlRenderAction;

    QList< QTextEdit::ExtraSelection > highlights;

    QString searchText;
    QTextCursor searchCursor;
    SearchDialog* searchDialog;
    ReplaceDialog* replaceDialog;

    QString currentFile;
    Config* currentConfig;

private:
    void createMenus( );
    void createToolBars( );
    void findPrevious( );
    void findNext( );
    void highlightCurrentMatch( );
    void openStlRender( QString path )
    {
        QWidget* window     = new QWidget(  );
        window->setWindowIcon( QIcon("./icon.ico") );
        QVBoxLayout* layout = new QVBoxLayout( window );

        stlRender* viewer = new stlRender;

        layout->addWidget( viewer );

        viewer->loadSTL( path );

        window->setWindowTitle( "STL Viewer" );
        window->resize( 800, 600 );
        window->show( );
    }

private slots:
    QString openFile( );
    QString saveFile( );
    void showVersion( );
    void run( );
    void openSearchDialog( );
    void openReplaceDialog( );
    void replaceAll( );
    void replace( );
    QString openStlFile( );
    void clearHighlights( );
};

#endif // MAINWINDOW_H
