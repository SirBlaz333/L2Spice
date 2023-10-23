#include "../headers/characterutils.h"

namespace character_utils {

    bool isWordComponent(char c)
    {
        return std::isalnum(c) || c == '-' || c == '_';
    }

    bool isLeftParanthesis(char c)
    {
        return c == '(';
    }

    bool isRightParanthesis(char c)
    {
        return c == ')';
    }

    bool isQuotes(char c)
    {
        return c == '"';
    }

    bool isWhitespaceCharacter(char c)
    {
        return std::isspace(c);
    }
} // namespace character_utils
