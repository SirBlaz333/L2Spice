#include "libre_netlist_parser.h"
#include "src/utils/character_utils.h"
#include "src/utils/uuid_generator.h"

QString LibreNetlistParser::nextWord()
{
    if (CharacterUtils::isQuotes(*currentCharacter)) {
        return nextDataInQuotes();
    }
    QString result;
    while (CharacterUtils::isWordComponent(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    return result;
}

QString LibreNetlistParser::nextDataInQuotes()
{
    QString result;
    currentCharacter++; //skip the opening quote.
    while (!CharacterUtils::isQuotes(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    currentCharacter++; //skip the closing quote.
    return result;
}

void LibreNetlistParser::parseComponents(QString::iterator last)
{
    while (currentCharacter < last) {
        parseComponent("", last); // parsing elements in netlist.
    }
}

void LibreNetlistParser::parseComponent(QString parentUuid,
                                   QString::iterator last)
{
    while (currentCharacter < last) {
        currentCharacter++;
        if (CharacterUtils::isOpenParanthesis(*currentCharacter)) {
            parseElement(parentUuid, last); // parse element in ();
        }
        if (CharacterUtils::isCloseParanthesis(*currentCharacter)) {
            return; // return, because it is the end of the element;
        }
    }
}

void LibreNetlistParser::parseElement(QString parentUuid,
                                 QString::iterator last)
{
    currentCharacter++;
    QString name = nextWord(); // get the name of element/property/nested element.
    currentCharacter++;
    QString value = nextWord(); // get either uuid/property or attribute name.
    // if it is an element, then there is gonna be a whitespace character afterwards.
    if (CharacterUtils::isWhitespaceCharacter(*currentCharacter)) {
        // create new element based on its name and uuid (name for attribute).
        Element *element = createNewElement(name, value);
        parseComponent(element->getUuid(), last); //parse the nested properties or elements.
        // if the element has an parent element, we need to add it to the parent as a property.
        // only the highest elements in hierarchy don't have parents.
        if (!parentUuid.isEmpty()) {
            Element *parent = elementMap[parentUuid].get();
            parent->setProperty(name, element);
        }
    }
    // if it as property, then there is gonna be ')' afterwards.
    else if (CharacterUtils::isCloseParanthesis(*currentCharacter)) {
        // get the parent element from the storage using uuid
        Element *parent = elementMap[parentUuid].get();
        //if an element with current uuid is already in the storage, just add it to the parent.
        if (elementMap.contains(value)) {
            Element *element = elementMap[value].get();
            parent->setProperty(name, element);
        } else {
            parent->setProperty(name, value);
        }
    }
    currentCharacter++;
}

Element* LibreNetlistParser::createNewElement(QString name, QString uuid)
{
    // create pointer to Element's child from the factory.
    QSharedPointer<Element> element = elementFactory[name]();
    // if it is an attribute, we need to create uuid ourselves and set the name to the attribute
    if (element->getElementType() == "attribute") {
        QString name = uuid;
        uuid = UUIDGenerator::generateUUID();
        element->setProperty("name", name);
    }
    element->setProperty("uuid", uuid);
    elementMap[uuid] = std::move(element);
    return elementMap[uuid].get();
}

LibreNetlistParser::LibreNetlistParser()
{
    elementFactory["variant"] = []() { return QSharedPointer<Variant>::create(); };
    elementFactory["netclass"] = []() { return QSharedPointer<NetClass>::create(); };
    elementFactory["net"] = []() { return QSharedPointer<Net>::create(); };
    elementFactory["component"] = []() { return QSharedPointer<Component>::create(); };
    elementFactory["model"] = []() { return QSharedPointer<Component>::create(); };
    elementFactory["attribute"] = []() { return QSharedPointer<Attribute>::create(); };
    elementFactory["signal"] = []() { return QSharedPointer<Signal>::create(); };
    elementFactory["device"] = []() { return QSharedPointer<Device>::create(); };
}

Circuit LibreNetlistParser::parseLibreNotation(QString input)
{
    elementMap = QMap<QString, QSharedPointer<Element>>();
    currentCharacter = input.begin();
    QChar front = *currentCharacter;
    currentCharacter++;
    // check if the first character is '(' and the format is "librepcb_circuit".
    // TODO: if it is not right now or something will went wrong later, we need to show some message to the user.
    if (CharacterUtils::isOpenParanthesis(front) && nextWord() == "librepcb_circuit") {
        elementMap["none"] = QSharedPointer<Net>::create();
        parseComponents(input.end());
    }

    // create the circuit from the elements.
    Circuit circuit;
    auto iterator = elementMap.begin();
    while (iterator != elementMap.end()) {
        Element *element = iterator.value().get();
        circuit.addElement(element);
        iterator++;
    }

    return circuit;
}
