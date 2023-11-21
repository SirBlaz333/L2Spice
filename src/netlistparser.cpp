#include "headers/netlistparser.h"
#include "headers/characterutils.h"
#include "headers/uuidgenerator.h"

QString NetlistParser::nextWord()
{
    if (character_utils::isQuotes(*currentCharacter)) {
        return nextDataInQuotes();
    }
    QString result;
    while (character_utils::isWordComponent(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    return result;
}

QString NetlistParser::nextDataInQuotes()
{
    QString result;
    currentCharacter++; //skip the opening quote.
    while (!character_utils::isQuotes(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    currentCharacter++; //skip the closing quote.
    return result;
}

void NetlistParser::parseComponents(QString::iterator last)
{
    while (currentCharacter != last) {
        parseComponent("", last); // parsing elements in netlist.
    }
}

void NetlistParser::parseComponent(QString parentUuid,
                                   QString::iterator last)
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

void NetlistParser::parseElement(QString parentUuid,
                                 QString::iterator last)
{
    currentCharacter++;
    QString name = nextWord(); // get the name of element/property/nested element.
    currentCharacter++;
    QString value = nextWord(); // get either uuid/property or attribute name.
    // if it is an element, then there is gonna be a whitespace character afterwards.
    if (character_utils::isWhitespaceCharacter(*currentCharacter)) {
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

Element* NetlistParser::createNewElement(QString name, QString uuid)
{
    // create pointer to Element's child from the factory.
    QSharedPointer<Element> element = elementFactory[name]();
    // if it is an attribute, we need to create uuid ourselves and set the name to the attribute
    if (element->getElementType() == "attribute") {
        QString name = uuid;
        uuid = uuid_generator::generateUUID();
        element->setProperty("name", name);
    }
    element->setProperty("uuid", uuid);
    elementMap[uuid] = std::move(element);
    return elementMap[uuid].get();
}

NetlistParser::NetlistParser()
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

NetlistParser::~NetlistParser() {}

Circuit NetlistParser::parseLibreNotation(QString input)
{
    elementMap = QMap<QString, QSharedPointer<Element>>();
    currentCharacter = input.begin();
    QChar front = *currentCharacter;
    currentCharacter++;
    elementMap["none"] = QSharedPointer<Net>::create();
    // check if the first character is '(' and the format is "librepcb_circuit".
    // TODO: if it is not right now or something will went wrong later, we need to show some message to the user.
    if (character_utils::isLeftParanthesis(front) && nextWord() == "librepcb_circuit") {
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
