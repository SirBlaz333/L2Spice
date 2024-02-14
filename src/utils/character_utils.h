#ifndef CHARACTER_UTILS_H
#define CHARACTER_UTILS_H

#include <QChar>
/**
 * Character utils is used to what group does the character belong
 */
namespace characterUtils {
/**
 * @brief Checks whether the charatecter is a word component.
 * In our case whether it is a letter, number, dash or undescore.
 * @param c - character
 * @return true if the character is a word component, false otherwise.
 */
bool isWordComponent(QChar c);

/**
 * @brief Checks whether the character is an open paranthesis or not
 * @param c - character
 * @return true if the character is an open paranthesis, false otherwise.
 */
bool isOpenParanthesis(QChar c);

/**
 * @brief Checks whether the character is an close paranthesis or not
 * @param c - character
 * @return true if the character is an close paranthesis, false otherwise.
 */
bool isCloseParanthesis(QChar c);

/**
 * @brief Checks whether the character double quotes is or not
 * @param c - character
 * @return true if the character is double quotes, false otherwise.
 */
bool isQuotes(QChar c);

/**
 * @brief Checks whether the character a whitespace is or not
 * @param c - character
 * @return true if the character is a whitespace, false otherwise.
 */
bool isWhitespaceCharacter(QChar c);
}

#endif // CHARACTER_UTILS_H
