#ifndef KEYMAP_H
#define KEYMAP_H

#include <QString>
#include <QAction>
#include <QMap>
#include <QJsonObject>
#include <QJsonValue>

class keyMap
{
public:
    keyMap(QJsonObject keyMapConfig) 
    { 
        // 默认配置
        keymap["cut"]   = "Ctrl+X";
        keymap["copy"]   = "Ctrl+C";
        keymap["paste"] = "Ctrl+V";
        keymap["redo"]  = "Ctrl+Y";
        keymap["undo"]  = "Ctrl+Z";
        keymap["search"] = "Ctrl+F";
        keymap["replace"] = "Ctrl+H";
        
        // 加载自定义配置
        for (QString key : keymap.keys())
        {
            if ( keyMapConfig.contains(key) )
            {
                QJsonValue curentValue = keyMapConfig.value( key );
                if ( curentValue.isString() )
                {
                    keymap[key] = curentValue.toString( );
                }
                else
                {
                    throw std::runtime_error( "The shortcut key configuration type is incorrect and should be a string." );
                }
            }
        }
    }
    ~keyMap( ) = default;

public:
    bool setKey( QAction*& act, QString keyName );

public:   
    QMap< QString, QString > keymap;
};

#endif // !KEYMAP_H
