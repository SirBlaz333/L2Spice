#include "text_utils.h"

#include <qtextdocument.h>

QString TextUtils::convertHtmlToPlain(QString htmlText) {
    QTextDocument htmlDoc;
    htmlDoc.setHtml(htmlText);
    return htmlDoc.toPlainText();
}
