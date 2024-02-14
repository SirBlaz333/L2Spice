#include "character_utils.h"

namespace characterUtils {

    bool isWordComponent(QChar c)
    {
        return c.isLetterOrNumber() || c == '-' || c == '_';
    }
    
    bool isOpenParanthesis(QChar c)
    {
        return c == '(';
    }
    
    bool isCloseParanthesis(QChar c)
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
