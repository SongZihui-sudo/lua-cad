#include "codeEditer.h"

QSize LineNumberArea::sizeHint( ) { return QSize( codeEditor->lineNumberAreaWidth( ), 0 ); }

void LineNumberArea::paintEvent( QPaintEvent* event ) { codeEditor->lineNumberAreaPaintEvent( event ); }

void CodeEditor::lineNumberAreaPaintEvent( QPaintEvent* event )
{
    QPainter painter( lineNumber );
    painter.fillRect( event->rect( ), lineNumberAreaColor );
    QFont font( "Courier", fontSize );
    font.setBold( true );        // bold
    painter.setFont( font );

    QTextBlock block = firstVisibleBlock( );
    int blockNumber  = block.blockNumber( );
    int top = qRound( blockBoundingGeometry( block ).translated( contentOffset( ) ).top( ) );
    int bottom = top + qRound( blockBoundingRect( block ).height( ) );

    while ( block.isValid( ) && top <= event->rect( ).bottom( ) )
    {
        if ( block.isVisible( ) && bottom >= event->rect( ).top( ) )
        {
            QString number = QString::number( blockNumber + 1 );
            painter.setPen( Qt::white );
            painter.drawText( 0, top, lineNumber->width( ), fontMetrics( ).height( ), Qt::AlignRight, number );
        }

        block  = block.next( );
        top    = bottom;
        bottom = top + qRound( blockBoundingRect( block ).height( ) );
        ++blockNumber;
    }
}

int CodeEditor::lineNumberAreaWidth( )
{ 
    int digits = 1;
    int max    = qMax( 1, blockCount( ) );
    while ( max >= 10 )
    {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics( ).horizontalAdvance( QLatin1Char( '9' ) ) * digits;

    return space;
}

void CodeEditor::highlightCurrentLine( )
{
    // 清除之前的高亮
    QList< QTextEdit::ExtraSelection > extraSelections;

    if ( !isReadOnly( ) )
    {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground( currentColor ); // 高亮背景颜色
        selection.format.setProperty( QTextFormat::FullWidthSelection, true );

        // 获取当前行光标
        selection.cursor = textCursor( );
        selection.cursor.clearSelection( ); // 只高亮光标所在的行

        extraSelections.append( selection );
    }

    setExtraSelections( extraSelections );
}

void LuaCadSyntaxHighlighter::setupHighlightingRules( )
{
    // Keyword highlighting
    keywordFormat.setForeground( keywordColor );
    keywordFormat.setFontWeight( QFont::Bold );
    QStringList keywordPatterns
    = { "\\band\\b",  "\\bbreak\\b",  "\\bdo\\b", "\\belse\\b",  "\\belseif\\b",
        "\\bfunction\\b", "\\bfor\\b", "\\bfalse\\b",  "\\bend\\b", "\\bif\\b", 
        "\\bin\\b", "\\blocal\\b", "\\bnil\\b", "\\bnot\\b", "\\bor\\b", "\\brepeat\\b",  
        "\\breturn\\b", "\\bthen\\b", "\\btrue\\b", "\\buntl\\b", "\\bwhile\\b" 
    };
    for ( const QString& pattern : keywordPatterns )
    {
        HighlightingRule rule;
        rule.pattern = QRegularExpression( pattern );
        rule.format  = keywordFormat;
        highlightingRules.append( rule );
    }

    // Class name highlighting
    classFormat.setForeground( classColor );
    classFormat.setFontWeight( QFont::Bold );
    HighlightingRule classRule;
    classRule.pattern = QRegularExpression( "\\bQ[A-Za-z]+\\b" );
    classRule.format  = classFormat;
    highlightingRules.append( classRule );

    // Single line comment highlighting
    singleLineCommentFormat.setForeground( commentColor );
    HighlightingRule singleLineCommentRule;
    singleLineCommentRule.pattern = QRegularExpression( "//[^\n]*" );
    singleLineCommentRule.format  = singleLineCommentFormat;
    highlightingRules.append( singleLineCommentRule );

    // String highlighting
    stringFormat.setForeground( stringColor );
    HighlightingRule stringRule;
    stringRule.pattern = QRegularExpression( "\".*\"" );
    stringRule.format  = stringFormat;
    highlightingRules.append( stringRule );

    // User defined object highlighting
    userObjFormat.setForeground( userobjColor );
    HighlightingRule userObjRule;
    userObjRule.pattern = QRegularExpression("\\$.*\\$" );
    userObjRule.format  = userObjFormat;
    highlightingRules.append( userObjRule );

    // Digital Highlight
    numberFormat.setForeground( numberColor );
    HighlightingRule numberRule;
    numberRule.pattern = QRegularExpression( "\\b\\d+\\b" );
    numberRule.format  = numberFormat;
    highlightingRules.append( numberRule );

    // Multi-line comment highlighting
    multiLineCommentFormat.setForeground( multiLineCommentColor );
    commentStartExpression = QRegularExpression( "--\\[\\[" );
    commentEndExpression   = QRegularExpression( "\\]\\]" );
}

void LuaCadSyntaxHighlighter::highlightMultilineComments( const QString& text )
{
    setCurrentBlockState( 0 );

    int startIndex = 0;
    if ( previousBlockState( ) != 1 )
        startIndex = text.indexOf( commentStartExpression );

    while ( startIndex >= 0 )
    {
        QRegularExpressionMatch match = commentEndExpression.match( text, startIndex );
        int endIndex                  = match.capturedStart( );
        int commentLength             = 0;
        if ( endIndex == -1 )
        {
            setCurrentBlockState( 1 );
            commentLength = text.length( ) - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex + match.capturedLength( );
        }

        setFormat( startIndex, commentLength, multiLineCommentFormat );
        startIndex = text.indexOf( commentStartExpression, startIndex + commentLength );
    }
}