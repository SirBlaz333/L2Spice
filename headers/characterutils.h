#ifndef CHARACTERUTILS_H
#define CHARACTERUTILS_H

#include <cctype>

#include <QChar>

namespace character_utils {
bool isWordComponent(QChar c);
bool isLeftParanthesis(QChar c);
bool isRightParanthesis(QChar c);
bool isQuotes(QChar c);
bool isWhitespaceCharacter(QChar c);
}

#endif // CHARACTERUTILS_H
