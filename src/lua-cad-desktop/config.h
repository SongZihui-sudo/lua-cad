#ifndef CONFIG
#define CONFIG

#include <QJsonObject>
#include <QJsonDocument>

#include "theme.h"
#include "keyMap.h"

class Config
{
public:
    Config( QString path )
    {
        keywords = { "and", "break",    "do",     "else", "elseif", "end",   "false",
                     "for", "function", "if",     "in",   "local",  "nil",   "not",
                     "or",  "repeat",   "return", "then", "true",   "until", "while" };
        is_linenumber = true;

        QJsonDocument doc = load_from_file( path );
        QJsonObject object = doc.object( );
        QJsonObject themeConfig;
        QJsonObject keymapConfig;

        if ( !object.contains("Error") )
        {
            if ( object.contains( "theme" ) )
            {
                QJsonValue themeValue = object.value( "theme" );
                if ( themeValue.isObject( ) )
                {
                    themeConfig = themeValue.toObject( );
                }
            }

            if ( object.contains( "keymap" ) )
            {
                QJsonValue keymapValue = object.value( "keymap" );
                if ( keymapValue.isObject( ) )
                {
                    keymapConfig = keymapValue.toObject( );
                }
            }
            if ( object.contains( "lua_keywords" ) )
            {
                QJsonArray keywordsArray = object.value( "lua_keywords" ).toArray( );
                keywords     = [&keywordsArray]( )
                {
                    QStringList list;
                    for ( const auto& value : keywordsArray )
                    {
                        list << value.toString( );
                    }
                    return list;
                }( );
            }
            if (object.contains("use_linenumber"))
            {
                is_linenumber = object.value( "use_linenumber" ).toBool( );
            }
        }

        currentKeyMap = new keyMap( keymapConfig );
        currentTheme  = new theme( themeConfig );

        // 如果当前没有配置文件，把当前的默认配置保存
        if (object.contains("Error"))
        {
            save_current_config( "./lua-cad-desktop-config.json" );
        }
    };

public:
    QJsonDocument load_from_file( QString path );

    void save_current_config( QString path );

public:
    theme* currentTheme;
    keyMap* currentKeyMap;
    bool is_linenumber;
    QStringList keywords;
};

#endif
