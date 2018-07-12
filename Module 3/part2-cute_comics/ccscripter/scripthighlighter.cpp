#include <QDebug>
#include "scripthighlighter.h"

ScriptHighlighter::ScriptHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    characterFormat.setFontWeight(QFont::Bold);
    characterFormat.setForeground(Qt::darkBlue);

    rule.format = characterFormat;
    rule.pattern = QRegularExpression("> \\w+:");

    highlightingRules.append(rule);
}

void ScriptHighlighter::highlightBlock(const QString &text)
{
    for (auto rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
