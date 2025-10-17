#include "config.h"

#include <QFile>
#include <QTextStream>


QJsonDocument Config::load_from_file(QString path)
{
    QJsonDocument doc;
    QFile file( path );
    if ( !file.open( QFile::ReadOnly | QFile::Text ) )
    {
        doc = QJsonDocument::fromJson( "{\"Error\": \"error\"}" );
        return doc;
    }
    else
    {
        QTextStream stream( &file );
        QString str = stream.readAll( );

        file.close( );

        QJsonParseError jsonError;
        doc = QJsonDocument::fromJson( str.toUtf8( ), &jsonError );
        if ( jsonError.error != QJsonParseError::NoError && !doc.isNull( ) )
        {
            throw std::runtime_error( "jsonError.error" );
        }

    }

    return doc;
}

void Config::save_current_config( QString path ) 
{ 
    QJsonObject obj;

    QJsonValue keywords_value = QJsonValue( QJsonArray::fromStringList( keywords ) );
    obj.insert( "lua_keywords", keywords_value );

    QJsonObject themeObj;
    QJsonObject keymapObj;

    for ( auto it = currentKeyMap->keymap.begin( ); it != currentKeyMap->keymap.end( ); ++it )
    {
        keymapObj[it.key( )] = QJsonValue::fromVariant( it.value( ) );
    }

    for ( auto it = currentTheme->map.begin( ); it != currentTheme->map.end( ); ++it )
    {
        if ( it.key( ).contains( "Color" ) )
        {
            themeObj[it.key( )] = QJsonValue::fromVariant( it.value( ).getColor() );
        }
        else
        {
            themeObj[it.key( )] = QJsonValue::fromVariant( it.value( ).getSize() );
        }
    }

    QJsonValue themeValue  = QJsonValue( themeObj );
    QJsonValue keymapValue = QJsonValue( keymapObj );
    obj.insert( "theme", themeValue );
    obj.insert( "keymap", keymapValue );
    
    obj.insert( "use_linenumber", QJsonValue( is_linenumber ) );

    QJsonDocument doc;
    doc.setObject( obj );
    QFile file( "./lua-cad-desktop-config.json" );
    
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )
    {
        throw std::runtime_error( "can't open error!" );
    }

    QTextStream stream( &file );
    stream << doc.toJson( );
    file.close( );
}
