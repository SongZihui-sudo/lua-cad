#ifndef THEME
#define THEME

#include <QString>
#include <QColor>
#include <Qmap>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class themeItem
{
    public:
    enum Type
    {
        Color,
        Size,
        Font,
        Flag,
        Double
    };

    themeItem( )
    : type( Flag )
    , boolValue( false )
    {
    }
    themeItem( const QColor& color )
    : type( Color )
    {
        new ( &colorValue ) QColor( color );
    }
    themeItem( qint16 size )
    : type( Size )
    , intValue( size )
    {
    }
    themeItem( const QString& font )
    : type( Font )
    {
        new ( &stringValue ) QString( font );
    }
    themeItem( bool flag )
    : type( Flag )
    , boolValue( flag )
    {
    }
    themeItem( double number )
    : type( Double )
    , boolValue( number )
    {
    }

    ~themeItem( )
    {
        if ( type == Color )
            colorValue.~QColor( );
        else if ( type == Font )
            stringValue.~QString( );
    }

    // 拷贝构造和赋值操作符（需要实现）
    themeItem( const themeItem& other )
    : type( other.type )
    {
        switch ( type )
        {
            case Color:
                new ( &colorValue ) QColor( other.colorValue );
                break;
            case Size:
                intValue = other.intValue;
                break;
            case Font:
                new ( &stringValue ) QString( other.stringValue );
                break;
            case Flag:
                boolValue = other.boolValue;
                break;
            case Double:
                doubleValue = other.doubleValue;
                break;
        }
    }

    themeItem& operator=( const themeItem& other )
    {
        if ( this != &other )
        {
            this->~themeItem( );
            new ( this ) themeItem( other );
        }
        return *this;
    }

    Type getType( ) const { return type; }

    QColor getColor( ) const { return type == Color ? colorValue : QColor( ); }
    qint16 getSize( ) const { return type == Size ? intValue : 0; }
    QString getStr( ) const { return type == Font ? stringValue : QString( ); }
    bool getFlag( ) const { return type == Flag ? boolValue : false; }
    double getNumber( ) const { return type == Double ? doubleValue : 0.0; }

    private:
    Type type;
    union
    {
        QColor colorValue;
        qint16 intValue;
        QString stringValue;
        bool boolValue;
        double doubleValue;
    };
};

class theme
{
public:
    theme( QJsonObject themeConfig ) 
    {
        // 默认配置
        map["keywordColor"]               = themeItem( QColor(Qt::blue) );
        map["classColor"]                 = themeItem(QColor(Qt::darkMagenta));
        map["commentColor"]               = themeItem( QColor( Qt::darkGreen ) );
        map["stringColor"]                = themeItem( QColor( Qt::darkRed ) );
        map["userobjColor"]               = themeItem( QColor( Qt::darkMagenta ) );
        map["numberColor"]                = themeItem( QColor( Qt::darkBlue ) );
        map["multiLineCommentColor"]      = themeItem( QColor( Qt::darkGray ) );
        map["lineNumberAreaTextColor"]    = themeItem( QColor( Qt::white ) );
        map["lineNumberAreaColor"]        = themeItem( QColor( Qt::darkCyan ) );
        map["currentColor"]               = themeItem( QColor( QColor( 220, 220, 255 ) ) );
        map["fontSize"]                   = themeItem( qint16(12) );
        map["tabSize"]                    = themeItem(qint16(4));
        map["backgroundColor"]            = themeItem( QColor( Qt::white ) );
        map["errorColor"]                 = themeItem( QColor( Qt::red ) );
        map["warningColor"]               = themeItem( QColor( Qt::yellow ) );
        map["searchMatchColor"]           = themeItem( QColor( Qt::yellow ) );
        map["line_number_font"]           = themeItem( "Courier" );
        map["line_number_font_is_bold"]   = themeItem( true );
        map["font"]                       = themeItem( "Courier" );
        map["cursorWidth"]                = themeItem( qint16( 2 ) );
        map["cursorHeight"]                = themeItem( qint16( -1 ) );
        map["cursorColor"]                = themeItem( QColor( Qt::black ) );
        map["textColor"]                  = themeItem( QColor( Qt::black ) );
        map["cursorTime"]                 = themeItem( 50.0 );
    
        // 加载自定义配置
        for (QString key : map.keys())
        {
            if ( themeConfig.contains( key ) )
            {
                QJsonValue currentValue = themeConfig.value( key );
                
                bool isColor = false;
                if ( key.contains( "Color" ) )
                {
                    isColor = true;
                }
                QJsonArray arr;
                switch (currentValue.type())
                {
                    case QJsonValue::Array:
                        if ( !isColor )
                        {
                            throw std::runtime_error( "Wrong configuration type." );
                        }
                        arr = currentValue.toArray( );
                        if ( arr.size() != 3 )
                        {
                            throw std::runtime_error( "R,G,B missing configuration." );
                        }
                        map[key] = themeItem( QColor( arr[0].toInt( ), arr[1].toInt( ), arr[2].toInt( ) ) );
                        break;
                    case QJsonValue::String:
                        if ( !isColor )
                        {
                            throw std::runtime_error( "Wrong configuration type." );
                        }
                        if ( isColor )
                        {
                            map[key] = themeItem( QColor( currentValue.toString( ) ) );
                        }
                        else
                        {
                            map[key] = themeItem( currentValue.toString( ) );
                        }
                        break;
                    case QJsonValue::Double:
                        if ( !isColor )
                        {
                            map[key] = themeItem( qint16( currentValue.toInt( ) ) );
                        }
                        else
                        {
                            map[key] = themeItem( QColor( currentValue.toInt( ) ) );
                        }
                        break;
                    default:
                        if ( !isColor )
                        {
                            throw std::runtime_error( "Wrong configuration type." );
                        }
                        map[key] = themeItem( QColor( currentValue.toString( ) ) );
                        break;
                }
            }
        }
    };

    ~theme()
    {

    }

public:
    QMap< QString, themeItem > map;
};

#endif