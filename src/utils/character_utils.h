#ifndef CHARACTER_UTILS_H
#define CHARACTER_UTILS_H

#include <QChar>

namespace characterUtils {
bool isWordComponent(QChar c);
bool isLeftParanthesis(QChar c);
bool isRightParanthesis(QChar c);
bool isQuotes(QChar c);
bool isWhitespaceCharacter(QChar c);
}

#endif // CHARACTER_UTILS_H
