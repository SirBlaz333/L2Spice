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
            currentCharacter++;
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
    if (character_utils::isWhitespaceCharacter(*currentCharacter)) {
        Element *element = createNewElement(name, value);
        parseComponent(element->getUuid(), last);
        if (!parentUuid.empty()) {
            Element *parent = elementMap[parentUuid].get();
            parent->setProperty(name, element);
        }
    } else if (character_utils::isRightParanthesis(*currentCharacter)) {
        Element *parent = elementMap[parentUuid].get();
        if (elementMap.count(value) != 0) {
            Element *element = elementMap[value].get();
            parent->setProperty(name, element);
        } else {
            parent->setProperty(name, value);
        }
    }
    currentCharacter++;
}

Element* NetlistParser::createNewElement(std::string name, std::string uuid)
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
    } else if (name == "device") {
        elementMap[uuid] = std::make_unique<Device>();
    }
    elementMap[uuid].get()->setProperty("uuid", uuid);
    return elementMap[uuid].get();
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

    Circuit circuit;
    auto iterator = elementMap.begin();
    while (iterator != elementMap.end()) {
        Element *element = iterator->second.get();
        circuit.addElement(element);
        iterator++;
    }

    return circuit;
}
