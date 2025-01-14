#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "codeEditer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

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

private:
    void createMenus( );
    void createToolBars( );

private slots:
    QString openFile( );
    QString saveFile( );
    void showVersion( );
    void run( );
};

#endif // MAINWINDOW_H
