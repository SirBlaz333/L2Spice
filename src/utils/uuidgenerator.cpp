#include "uuidgenerator.h"

#include <bits/random.h>
#include <random>
#include <sstream>

static std::random_device randomDevice;
static std::mt19937 generator(randomDevice());
static std::uniform_int_distribution<> distribution(0, 15);
static std::uniform_int_distribution<> distribution2(8, 11);

namespace uuid_generator {

    QString generateUUID()
    {
        std::stringstream uuid;
        int i;
        uuid << std::hex;
        for (i = 0; i < 8; i++) {
            uuid << distribution(generator);
        }
        uuid << "-";
        for (i = 0; i < 4; i++) {
            uuid << distribution(generator);
        }
        uuid << "-4";
        for (i = 0; i < 3; i++) {
            uuid << distribution(generator);
        }
        uuid << "-";
        uuid << distribution2(generator);
        for (i = 0; i < 3; i++) {
            uuid << distribution(generator);
        }
        uuid << "-";
        for (i = 0; i < 12; i++) {
            uuid << distribution(generator);
        }
        return QString::fromStdString(uuid.str());
    }

} // namespace uuid
