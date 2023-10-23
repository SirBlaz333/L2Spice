#ifndef CHARACTERUTILS_H
#define CHARACTERUTILS_H

#include <cctype>

namespace character_utils {
bool isWordComponent(char c);
bool isLeftParanthesis(char c);
bool isRightParanthesis(char c);
bool isQuotes(char c);
bool isWhitespaceCharacter(char c);
}

#endif // CHARACTERUTILS_H
