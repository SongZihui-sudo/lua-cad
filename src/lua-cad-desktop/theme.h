#ifndef THEME
#define THEME

#include <QString>
#include <QColor>
#include <Qmap>

class theme
{
public:
    theme( QString path ) 
    {
        keywordColor            = Qt::blue;
        classColor              = Qt::darkMagenta;
        commentColor            = Qt::darkGreen;
        stringColor             = Qt::darkRed;
        userobjColor            = Qt::darkMagenta;
        numberColor             = Qt::darkBlue;
        multiLineCommentColor   = Qt::darkGray;
        lineNumberAreaTextColor = Qt::white;
        lineNumberAreaColor     = Qt::darkCyan;
        currentColor            = QColor( 220, 220, 255 );
        fontSize                = 12;
        tabSize                 = 4;
        backgroundColor         = Qt::white;
    };

    ~theme()
    {

    }

public:
    QColor keywordColor;
    QColor classColor;
    QColor commentColor;
    QColor stringColor;
    QColor userobjColor;
    QColor numberColor;
    QColor multiLineCommentColor;
    QColor backgroundColor;
    QColor currentColor;
    qint16 fontSize;
    QColor lineNumberAreaColor;
    QColor lineNumberAreaTextColor;
    qint16 tabSize;

};

#endif