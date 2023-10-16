#include "headers/element.h"

Component::Component(const std::string &uuid, const std::string &name) : uuid(uuid),
    name(name)
{}

Component::~Component() {}
