#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QDebug>

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

// code editor
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit CodeEditor( QWidget* parent = nullptr )
    : QPlainTextEdit( parent )
    {
        setFont( QFont( "Courier", 12 ) );
        setTabStopDistance( 4 * fontMetrics( ).horizontalAdvance( ' ' ) );
        connect( this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine );
        highlightCurrentLine( ); // 初始化高亮当前行
    }

protected:
    void highlightCurrentLine( );
};