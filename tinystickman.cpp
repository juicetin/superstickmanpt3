#include "tinystickman.h"

TinyStickman::TinyStickman(const std::vector<QPixmap> &sprites) :
    Stickman(STICKMAN_TINY, sprites)
{
}

TinyStickman::~TinyStickman()
{
}

int TinyStickman::getWidth() const
{
    return getSprite().width();
}

int TinyStickman::getHeight() const
{
    return getSprite().height();
}
