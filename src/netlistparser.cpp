#include "headers/netlistparser.h"
#include "headers/characterutils.h"
#include "headers/uuidgenerator.h"

std::string NetlistParser::nextWord()
{
    if (character_utils::isQuotes(*currentCharacter)) {
        return nextDataInQuotes();
    }
    std::string result = "";
    while (character_utils::isWordComponent(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    return result;
}

std::string NetlistParser::nextDataInQuotes()
{
    std::string result = "";
    currentCharacter++;
    while (!character_utils::isQuotes(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    currentCharacter++;
    return result;
}

void NetlistParser::parseComponents(std::string::iterator last)
{
    while (currentCharacter != last) {
        parseComponent("", last);
        currentCharacter++;
    }
}

void NetlistParser::parseComponent(std::string parentUuid,
                                   std::string::iterator last)
{
    while (currentCharacter != last) {
        if (character_utils::isLeftParanthesis(*currentCharacter)) {
            parseElement(parentUuid, last);
        }
        if (character_utils::isRightParanthesis(*currentCharacter)) {
            return;
        }
        currentCharacter++;
    }
}

void NetlistParser::parseElement(std::string parentUuid,
                                 std::string::iterator last)
{
    currentCharacter++;
    std::string name = nextWord();
    currentCharacter++;
    std::string value = nextWord();
    try {
        if (character_utils::isRightParanthesis(*currentCharacter)) {
            Element* element = elementMap.at(parentUuid).get();
            element->setProperty(name, value);
            currentCharacter++;
            return;
        }
        if (character_utils::isWhitespaceCharacter(*currentCharacter)) {
            createNewElement(name, value);
            Element *newElement = elementMap.at(parentUuid).get();
            parseComponent(value, last);
            if (!parentUuid.empty()) {
                Element* element = elementMap.at(parentUuid).get();
                element->setProperty(name, newElement);
            }
        }
    } catch (std::out_of_range e) {
    }
}

void NetlistParser::createNewElement(std::string name, std::string uuid)
{
    if (name == "variant") {
        elementMap[uuid] = std::make_unique<Variant>();
    } else if (name == "netclass") {
        elementMap[uuid] = std::make_unique<NetClass>();
    } else if (name == "net") {
        elementMap[uuid] = std::make_unique<Net>();
    } else if (name == "component") {
        elementMap[uuid] = std::make_unique<Component>();
    } else if (name == "attribute") {
        std::string name = uuid;
        uuid = uuid_generator::generateUUID();
        elementMap[uuid] = std::make_unique<Attribute>();
        elementMap[uuid].get()->setProperty("name", name);
    } else if (name == "signal") {
        elementMap[uuid] = std::make_unique<Signal>();
    }
    elementMap[uuid].get()->setProperty("uuid", uuid);
}

NetlistParser::NetlistParser() {}

NetlistParser::~NetlistParser() {}

Circuit NetlistParser::parseLibreNotation(std::string input)
{
    currentCharacter = input.begin();
    char front = *currentCharacter;
    currentCharacter++;
    if (character_utils::isLeftParanthesis(front) && nextWord() == "librepcb_circuit") {
        currentCharacter++;
        parseComponents(input.end());
    }

    std::map<std::string, Net> netMap;
    std::map<std::string, Component> componentMap;

//    Element *element = elementMap.begin()->second.get();
//    Variant *variant = dynamic_cast<Variant *>(element);

    Circuit circuit = Circuit(Variant(), NetClass(), netMap, componentMap);
    return circuit;
}
