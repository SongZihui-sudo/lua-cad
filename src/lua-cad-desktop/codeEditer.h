#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QDebug>
#include <QPainter>

class CodeEditor;

// Code heightlight
class LuaCadSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    explicit LuaCadSyntaxHighlighter( QTextDocument* parent = nullptr )
    : QSyntaxHighlighter( parent )
    {
        setupHighlightingRules( );
    }

public:
    void highlightBlock( const QString& text ) override
    {
        qDebug( ) << text;
        for ( const HighlightingRule& rule : highlightingRules )
        {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch( text );
            while ( matchIterator.hasNext( ) )
            {
                QRegularExpressionMatch match = matchIterator.next( );
                setFormat( match.capturedStart( ), match.capturedLength( ), rule.format );
            }
        }
        // Support multi-line comments
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

    void highlightMultilineComments( const QString& text );

    void setupHighlightingRules( );
};

// line number
class LineNumberArea : public QWidget
{
public:
    LineNumberArea( QWidget* parent,  CodeEditor* editor = nullptr )
: QWidget(  parent )
    , codeEditor( editor )
    {
    }

protected:
    QSize sizeHint( );

    void paintEvent( QPaintEvent* event );

private:
    CodeEditor* codeEditor;
};

// code editor
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CodeEditor( QWidget* parent = nullptr )
    : QPlainTextEdit( parent )
    {
        lineNumber = new LineNumberArea(parent, this );

        connect( this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth );
        connect( this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea );
        connect( this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine );

        updateLineNumberAreaWidth( 0 );

        setFont( QFont( "Courier", 12 ) );
        setTabStopDistance( 4 * fontMetrics( ).horizontalAdvance( ' ' ) );
        connect( this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine );
        highlightCurrentLine( ); // 初始化高亮当前行
    }

    int lineNumberAreaWidth( );

private:
    QWidget* lineNumber;

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

public:
    void lineNumberAreaPaintEvent( QPaintEvent* event );
};