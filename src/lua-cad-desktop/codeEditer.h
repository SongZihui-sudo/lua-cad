#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QDebug>
#include <QPainter>
#include <QMap>
#include <QCompleter>
#include <QStringListModel>

#include "theme.h"

class CodeEditor;

// Code heightlight
class LuaCadSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit LuaCadSyntaxHighlighter( theme* cur_theme, QTextDocument* parent = nullptr )
    : QSyntaxHighlighter( parent )
    {
        keywordColor = cur_theme->keywordColor;
        classColor   = cur_theme->classColor;
        commentColor = cur_theme->commentColor;
        stringColor = cur_theme->stringColor;
        userobjColor = cur_theme->userobjColor;
        numberColor = cur_theme->numberColor;
        multiLineCommentColor = cur_theme->multiLineCommentColor;

        setupHighlightingRules( );
    }

public:
    void highlightBlock( const QString& text ) Q_DECL_OVERRIDE
    {
        for ( const HighlightingRule& rule : highlightingRules )
        {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch( text );
            while ( matchIterator.hasNext( ) )
            {
                QRegularExpressionMatch match = matchIterator.next( );
                setFormat( match.capturedStart( ), match.capturedLength( ), rule.format );
            }
        }

        highlightMultilineComments( text );
    }

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector< HighlightingRule > highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat stringFormat;
    QTextCharFormat userObjFormat;
    QTextCharFormat numberFormat;
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QColor keywordColor;
    QColor classColor;
    QColor commentColor;
    QColor stringColor;
    QColor userobjColor;
    QColor numberColor;
    QColor multiLineCommentColor;

private:
    void highlightMultilineComments( const QString& text );

    void setupHighlightingRules( );
};

// line number
class LineNumberArea : public QWidget
{
public:
    LineNumberArea( QWidget* parent, QColor lineNumberAreaColor, QColor lineNumberAreaTextColor, CodeEditor* editor = nullptr )
    : QWidget(  parent ) , codeEditor( editor )
    {
        lineNumberAreaTextColor = lineNumberAreaTextColor;
        lineNumberAreaColor = lineNumberAreaColor;
    }

protected:
    QSize sizeHint( );

    void paintEvent( QPaintEvent* event );

private:
    CodeEditor* codeEditor;
    QColor lineNumberAreaColor;
    QColor lineNumberAreaTextColor;
};

// code editor
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CodeEditor( theme* cur_theme, QStringList keywords, QWidget* parent = nullptr )
    : QPlainTextEdit( parent )
    {
        backgroundColor         = cur_theme->backgroundColor;
        lineNumberAreaTextColor = cur_theme->lineNumberAreaTextColor;
        lineNumberAreaColor     = cur_theme->lineNumberAreaColor;
        currentColor            = cur_theme->currentColor;
        fontSize                = cur_theme->fontSize;
        tabSize                 = cur_theme->tabSize;

        lineNumber = new LineNumberArea( parent, lineNumberAreaColor, lineNumberAreaTextColor, this );

        connect( this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth );
        connect( this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea );
        connect( this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine );

        updateLineNumberAreaWidth( 0 );

        setFont( QFont( "Courier", fontSize ) );
        setTabStopDistance( tabSize * fontMetrics( ).horizontalAdvance( ' ' ) );
        
        connect( this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine );
      
        QPalette p = this->palette( );
        p.setColor( QPalette::Active, QPalette::Base, backgroundColor );
        p.setColor( QPalette::Inactive, QPalette::Base, backgroundColor );
        this->setPalette( p );

        LuaCadSyntaxHighlighter* highlighter
        = new LuaCadSyntaxHighlighter( cur_theme, this->document() );

        highlightCurrentLine( );

        completer = new QCompleter( keywords, this );
        completer->setCaseSensitivity( Qt::CaseInsensitive ); // 忽略大小写
        completer->setWidget( this );

        connect( completer,
                 QOverload< const QString& >::of( &QCompleter::activated ),
                 this, &CodeEditor::insertCompletion );
    }

    int lineNumberAreaWidth( );

private:
    QColor backgroundColor;
    QColor currentColor;
    qint16 fontSize;
    QColor lineNumberAreaColor;
    QWidget* lineNumber;
    QColor lineNumberAreaTextColor;
    qint16 tabSize;
    QStringList keywords;
    QCompleter* completer;

    void resizeEvent( QResizeEvent* e )
    {
        QPlainTextEdit::resizeEvent( e );

        QRect cr = contentsRect( );
        lineNumber->setGeometry( QRect( cr.left( ), cr.top( ), lineNumberAreaWidth( ), cr.height( ) ) );
    }

private slots:
    void highlightCurrentLine( );

    void updateLineNumberAreaWidth( int /* newBlockCount */ )
    {
        setViewportMargins( lineNumberAreaWidth( ), 0, 0, 0 );
    }

    void updateLineNumberArea( const QRect& rect, int dy )
    {
        if ( dy )
            lineNumber->scroll( 0, dy );
        else
            lineNumber->update( 0, rect.y( ), lineNumber->width( ), rect.height( ) );

        if ( rect.contains( viewport( )->rect( ) ) )
            updateLineNumberAreaWidth( 0 );
    }

    void insertCompletion( const QString& completion )
    {
        if ( completer->widget( ) != this )
        {
            return;
        }

        QTextCursor cursor = textCursor( );
        cursor.select( QTextCursor::WordUnderCursor );
        cursor.insertText( completion ); // 插入补全文本
        setTextCursor( cursor );
    }

public:
    void lineNumberAreaPaintEvent( QPaintEvent* event );

protected:
    void keyPressEvent( QKeyEvent* e ) override;

     // 检查是否是开符号
    bool isOpeningSymbol( QChar symbol ) const
    {
        return symbol == '(' || symbol == '[' || symbol == '{' || symbol == '"' || symbol == '\'';
    }

    // 检查是否是闭符号
    bool isClosingSymbol( QChar symbol ) const
    {
        return symbol == ')' || symbol == ']' || symbol == '}' || symbol == '"' || symbol == '\'';
    }

    // 获取对应的闭符号
    QChar matchingClosingSymbol( QChar opening ) const
    {
        switch ( opening.unicode( ) )
        {
            case '(':
                return ')';
            case '[':
                return ']';
            case '{':
                return '}';
            case '"':
                return '"';
            case '\'':
                return '\'';
            default:
                return QChar( );
        }
    }

    // 处理开符号
    void handleOpeningSymbol( QChar opening )
    {
        QTextCursor cursor = textCursor( );

        // 插入符号对
        QChar closing = matchingClosingSymbol( opening );
        cursor.insertText( QString( opening ) + QString( closing ) );

        // 将光标移动到符号中间
        cursor.movePosition( QTextCursor::Left );
        setTextCursor( cursor );
    }

    // 处理闭符号
    bool handleClosingSymbol( QChar closing )
    {
        QTextCursor cursor = textCursor( );
        if ( !cursor.atEnd( ) && cursor.document( )->characterAt( cursor.position( ) ) == closing )
        {
            // 如果下一个字符已经是闭符号，光标跳过
            cursor.movePosition( QTextCursor::Right );
            setTextCursor( cursor );
            return true;
        }
        return false;
    }
};