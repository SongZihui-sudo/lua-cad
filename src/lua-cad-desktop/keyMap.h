#ifndef KEYMAP_H
#define KEYMAP_H

#include <QString>
#include <QAction>
#include <QMap>

class keyMap
{
public:
    keyMap(QString path) 
    { 
        cutKey    = "Ctrl+X";
        cpyKey = "Ctrl+C";
        pasteKey = "Ctrl+V";
        reDoKey  = "Ctrl+Y";
        unDoKey  = "Ctrl+Z";
        searchKey = "Ctrl+F";
        replaceKey = "Ctrl+H";
    }
    ~keyMap( ) = default;

public:
    bool setKey( QAction*& act, QString keyName );

private:
    QString replaceKey;
    QString cutKey;
    QString cpyKey;
    QString pasteKey;
    QString unDoKey;
    QString reDoKey;
    QString searchKey;
    
    QMap< QString, QString > keymap
    = { { "copy", cpyKey },  { "cut", cutKey },   { "paste", pasteKey },
        { "undo", unDoKey }, { "redo", reDoKey }, { "search", searchKey },
                                        { "replace", replaceKey } };
};

#endif // !KEYMAP_H
