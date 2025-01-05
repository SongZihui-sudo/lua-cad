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

    QAction* scadAction;
    QAction* renderAction;

private:
    void createMenus( );
    void createToolBars( );

private slots:
    void openFile( );
    void saveFile( );

};

#endif // MAINWINDOW_H
