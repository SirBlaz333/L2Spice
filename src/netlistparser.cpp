#include "headers/netlistparser.h"
#include "headers/characterutils.h"
#include "headers/uuidgenerator.h"

std::string NetlistParser::nextWord()
{
    if (character_utils::isQuotes(*currentCharacter)) {
        return nextDataInQuotes();
    }
    std::string result;
    while (character_utils::isWordComponent(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    return result;
}

std::string NetlistParser::nextDataInQuotes()
{
    std::string result;
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
        currentCharacter++;
        if (character_utils::isLeftParanthesis(*currentCharacter)) {
            parseElement(parentUuid, last);
        }
        if (character_utils::isRightParanthesis(*currentCharacter)) {
            return;
        }
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
    std::unique_ptr<Element> element = elementFactory[name]();
    if (element->getType() == "attribute") {
        std::string name = uuid;
        uuid = uuid_generator::generateUUID();
        element->setProperty("name", name);
    }
    element->setProperty("uuid", uuid);
    elementMap[uuid] = std::move(element);
    return elementMap[uuid].get();
}

NetlistParser::NetlistParser()
{
    elementFactory["variant"] = []() { return std::make_unique<Variant>(); };
    elementFactory["netclass"] = []() { return std::make_unique<NetClass>(); };
    elementFactory["net"] = []() { return std::make_unique<Net>(); };
    elementFactory["component"] = []() { return std::make_unique<Component>(); };
    elementFactory["attribute"] = []() { return std::make_unique<Attribute>(); };
    elementFactory["signal"] = []() { return std::make_unique<Signal>(); };
    elementFactory["device"] = []() { return std::make_unique<Device>(); };
}

NetlistParser::~NetlistParser() {}

Circuit NetlistParser::parseLibreNotation(std::string input)
{
    currentCharacter = input.begin();
    char front = *currentCharacter;
    currentCharacter++;
    if (character_utils::isLeftParanthesis(front) && nextWord() == "librepcb_circuit") {
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
