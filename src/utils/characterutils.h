#ifndef CHARACTERUTILS_H
#define CHARACTERUTILS_H

#include <QChar>

namespace characterUtils {
bool isWordComponent(QChar c);
bool isLeftParanthesis(QChar c);
bool isRightParanthesis(QChar c);
bool isQuotes(QChar c);
bool isWhitespaceCharacter(QChar c);
}

#endif // CHARACTERUTILS_H
