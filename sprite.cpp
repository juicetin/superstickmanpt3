#include "sprite.h"

#include "camera.h"

#include <QBrush>
#include <QVector2D>

#include <iostream>
using namespace std;

Sprite::Sprite(const QPixmap& texture, ColliderType ct) :
    m_texture(texture),
    m_size(texture.size()),
    m_position(QPoint(0,0)),
    m_colliderType(ct)
{

}

Sprite::~Sprite()
{

}

void Sprite::render(QPainter& painter) const
{
    // Convert game world coordinates to screen-space coordinates
    QPoint screenPos = Camera::getInstance().convertToScreenSpace(m_position);

    // The screenPos is the sprite's centre, change to top-left for drawing pixmaps
    screenPos.setX(screenPos.x() - getWidth() / 2);
    screenPos.setY(screenPos.y() - getHeight() / 2);

    // Pixmap needs to be scaled to match getWidth() and getHeight()
    QTransform scalingTransform = QTransform().scale(
        getWidth() / (float)m_texture.width(),
        getHeight() / (float)m_texture.height()
    );
    QPixmap transformed = m_texture.transformed(scalingTransform);

    // Draw the pixmap

    painter.drawPixmap(
        screenPos,
        transformed
    );

}

bool Sprite::collidesWith(const Sprite &otherSprite) const
{
    if (m_colliderType == None)
        return false;

    if (otherSprite.m_colliderType == None)
        return false;

    if (m_colliderType == Rectangle && otherSprite.m_colliderType == Rectangle) {
        if (otherSprite.getBoundingRect().isEmpty()) {
            return false;
        }

        return getBoundingRect().intersects(otherSprite.getBoundingRect());
    }
    return false;
}

QRect Sprite::getBoundingRect() const
{
    return QRect(
        getXPosition() - getWidth() / 2,
        getYPosition() - getHeight() / 2,
        getWidth(),
        getHeight()
    );
}

void Sprite::changeTexture(const QPixmap &texture)
{
    m_texture = texture;
}

float Sprite::getXPosition() const
{
    return m_position.x();
}

float Sprite::getYPosition() const
{
    return m_position.y();
}

void Sprite::setXPosition(float value)
{
    m_position.setX(value);
}

void Sprite::setYPosition(float value)
{
    m_position.setY(value);
}

int Sprite::getWidth() const
{
    return (int)m_size.width();
}

int Sprite::getHeight() const
{
    return (int)m_size.height();
}

void Sprite::setWidth(float value, AspectRatioMode mode)
{
    float aspectRatio = getHeight() / getWidth();

    switch (mode) {
    case KeepAspectRatio:
        m_size.setWidth(value);
        m_size.setHeight(value * aspectRatio);
        break;
    case IgnoreAspectRatio:
    default:
        m_size.setWidth(value);
        break;
    };

}

void Sprite::setHeight(float value, AspectRatioMode mode)
{

    float aspectRatio = getWidth() / getHeight();

    switch(mode) {
    case KeepAspectRatio:
        m_size.setWidth(value * aspectRatio);
        m_size.setHeight(value);
        break;
    case IgnoreAspectRatio:
    default:
        m_size.setHeight(value);
        break;
    };
}

ColliderType Sprite::getColliderType() const {
    return m_colliderType;
}

float Sprite::getOriginalXPos() const
{
    return m_originalXPos;
}

float Sprite::getOriginalYPos() const
{
    return m_originalYPos;
}

void Sprite::setOriginalXPos(float xpos)
{
    m_originalXPos = xpos;
}

void Sprite::setOriginalYPos(float ypos)
{
    m_originalYPos = ypos;
}
