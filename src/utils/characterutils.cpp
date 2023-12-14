#include "characterutils.h"

namespace characterUtils {

    bool isWordComponent(QChar c)
    {
        return c.isLetterOrNumber() || c == '-' || c == '_';
    }

    bool isLeftParanthesis(QChar c)
    {
        return c == '(';
    }

    bool isRightParanthesis(QChar c)
    {
        return c == ')';
    }

    bool isQuotes(QChar c)
    {
        return c == '"';
    }

    bool isWhitespaceCharacter(QChar c)
    {
        return c.isSpace();
    }
} // namespace character_utils
