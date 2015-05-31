#include "stickman.h"

Stickman::Stickman(StickmanSize size, const std::vector<QPixmap> &sprites) :
    m_size(size),
    m_xOffset(0),
    m_xPosition(0),
    m_xVelocity(0),
    m_sprites(sprites),
    m_curSpriteIdx(0),
    m_spriteDurationMs(1000),
    m_curSpriteDurationMs(0)
//    m_enumStrings({"tiny", "normal", "large", "giant"})
{
//     m_enumStrings = {"tiny", "normal", "large", "giant"};
     m_enumStrings[0] = "tiny";
     m_enumStrings[1] = "normal";
     m_enumStrings[2] = "large";
     m_enumStrings[3] = "giant";
}

Stickman::~Stickman()
{
}

const std::string Stickman::getSizeText(int enumVal)
{
    return m_enumStrings[enumVal];
}

void Stickman::render(QPainter &painter) const
{
    // Draw the stickman at the bottom of the screen
    int yPos = painter.device()->height() - getHeight();

    // Find how much to scale the sprite image by to match the bounding box of the stickman
    // If x velocity is negative, we flip the image as well.
    float scaleX = getWidth() / getSprite().width() * (m_xVelocity < 0 ? -1 : 1);
    float scaleY = getHeight() / getSprite().height();

    painter.drawPixmap(m_xOffset, yPos, getSprite().transformed(QTransform().scale(scaleX, scaleY)));
}

void Stickman::update(int ms)
{
    // Move the stickman
    m_xPosition += m_xVelocity * (ms / 1000.0);

    // Change the stickman's sprite to the next frame if we've spent too long on the current frame.
    m_curSpriteDurationMs += ms;
    if (m_curSpriteDurationMs > m_spriteDurationMs) {
        m_curSpriteIdx = (m_curSpriteIdx + 1) % m_sprites.size();
        m_curSpriteDurationMs = 0;
    }
}

int Stickman::getXOffset() const
{
    return m_xOffset;
}

void Stickman::setXOffset(int value)
{
    m_xOffset = value;
}

float Stickman::getXPosition() const
{
    return m_xPosition;
}

float Stickman::getXVelocity() const
{
    return m_xVelocity;
}

float Stickman::getXMoveVelocity() const
{
    return m_xMoveVelocity;
}

void Stickman::setXVelocity(float value)
{
    m_xVelocity = value;
    m_xMoveVelocity = value;
}

StickmanSize Stickman::getSize() const
{
    return m_size;
}

int Stickman::getSpriteDuration() const
{
    return m_spriteDurationMs;
}

void Stickman::setSpriteDuration(int ms)
{
    m_spriteDurationMs = ms;
}

const QPixmap &Stickman::getSprite() const
{
    return m_sprites[m_curSpriteIdx];
}

std::vector<QPixmap> Stickman::getSprites() const
{
    return m_sprites;
}
