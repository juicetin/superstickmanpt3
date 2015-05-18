#include "normalstickman.h"

NormalStickman::NormalStickman(const std::vector<QPixmap> &sprites) :
    Stickman(STICKMAN_NORMAL, sprites)
{
}

NormalStickman::~NormalStickman()
{
}

int NormalStickman::getWidth() const
{
    return getSprite().width() * 2;
}

int NormalStickman::getHeight() const
{
    return getSprite().height() * 2;
}
