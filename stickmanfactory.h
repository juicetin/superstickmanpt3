#ifndef STICKMANFACTORY_H
#define STICKMANFACTORY_H

#include "stickman.h"

#include <QPixmap>

class StickmanFactory
{
public:
    static Stickman *create(const std::string size, const std::vector<QPixmap> &sprites);
};

#endif // STICKMANFACTORY_H
