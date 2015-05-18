#include "largestickman.h"

LargeStickman::LargeStickman(const std::vector<QPixmap> &sprites) :
    Stickman(STICKMAN_LARGE, sprites)
{
}

LargeStickman::~LargeStickman()
{
}

int LargeStickman::getWidth() const
{
    return getSprite().width() * 4;
}

int LargeStickman::getHeight() const
{
    return getSprite().height() * 4;
}

