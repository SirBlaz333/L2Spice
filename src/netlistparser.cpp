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
    currentCharacter++; //skip the opening quote.
    while (!character_utils::isQuotes(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    currentCharacter++; //skip the closing quote.
    return result;
}

void NetlistParser::parseComponents(std::string::iterator last)
{
    while (currentCharacter != last) {
        parseComponent("", last); // parsing elements in netlist.
    }
}

void NetlistParser::parseComponent(std::string parentUuid,
                                   std::string::iterator last)
{
    while (currentCharacter != last) {
        currentCharacter++;
        if (character_utils::isLeftParanthesis(*currentCharacter)) {
            parseElement(parentUuid, last); // parse element in ();
        }
        if (character_utils::isRightParanthesis(*currentCharacter)) {
            return; // return, because it is the end of the element;
        }
    }
}

void NetlistParser::parseElement(std::string parentUuid,
                                 std::string::iterator last)
{
    currentCharacter++;
    std::string name = nextWord(); // get the name of element/property/nested element.
    currentCharacter++;
    std::string value = nextWord(); // get either uuid/property or attribute name.
    // if it is an element, then there is gonna be a whitespace character afterwards.
    if (character_utils::isWhitespaceCharacter(*currentCharacter)) {
        // create new element based on its name and uuid (name for attribute).
        Element *element = createNewElement(name, value);
        parseComponent(element->getUuid(), last); //parse the nested properties or elements.
        // if the element has an parent element, we need to add it to the parent as a property.
        // only the highest elements in hierarchy don't have parents.
        if (!parentUuid.empty()) {
            Element *parent = elementMap[parentUuid].get();
            parent->setProperty(name, element);
        }
    }
    // if it as property, then there is gonna be ')' afterwards.
    else if (character_utils::isRightParanthesis(*currentCharacter)) {
        // get the parent element from the storage using uuid
        Element *parent = elementMap[parentUuid].get();
        //if an element with current uuid is already in the storage, just add it to the parent.
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
    // create pointer to Element's child from the factory.
    std::unique_ptr<Element> element = elementFactory[name]();
    // if it is an attribute, we need to create uuid ourselves and set the name to the attribute
    if (element->getElementType() == "attribute") {
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
    elementMap = std::map<std::string, std::unique_ptr<Element>>();
    currentCharacter = input.begin();
    char front = *currentCharacter;
    currentCharacter++;
    elementMap["none"] = std::make_unique<Net>();
    // check if the first character is '(' and the format is "librepcb_circuit".
    // TODO: if it is not right now or something will went wrong later, we need to show some message to the user.
    if (character_utils::isLeftParanthesis(front) && nextWord() == "librepcb_circuit") {
        parseComponents(input.end());
    }

    // create the circuit from the elements.
    Circuit circuit;
    auto iterator = elementMap.begin();
    while (iterator != elementMap.end()) {
        Element *element = iterator->second.get();
        circuit.addElement(element);
        iterator++;
    }

    return circuit;
}
