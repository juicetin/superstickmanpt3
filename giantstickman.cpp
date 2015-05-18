#include "giantstickman.h"

GiantStickman::GiantStickman(const std::vector<QPixmap> &sprites) :
    Stickman(STICKMAN_GIANT, sprites)
{
}

GiantStickman::~GiantStickman()
{
}

int GiantStickman::getWidth() const
{
    return getSprite().width() * 8;
}

int GiantStickman::getHeight() const
{
    return getSprite().height() * 8;
}
