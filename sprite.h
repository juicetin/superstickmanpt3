#ifndef SPRITE_H
#define SPRITE_H

#include <QPainter>
#include <QPixmap>
#include <QPointF>
#include <QRect>
#include <QSize>

enum AspectRatioMode {
    IgnoreAspectRatio,
    KeepAspectRatio
};

enum ColliderType {
    None,
    Rectangle
};

// Sprite is meant to be the base class for all objects that can be seen
// It contains some basic functionality for rendering and collision.
//
// Collision example:
//      Sprite a(textureA);
//      Sprite b(textureB);
//      if (a.collidesWith(b)) {
//          QRect intersection = a.getBoundingRect().intersected(b.getBoundingRect());
//          // handle intersection
//      }
class Sprite
{
public:
    // takes a texture to render, and a collision type for collidesWith()
    Sprite(const QPixmap& texture, ColliderType ct = Rectangle);
    virtual ~Sprite();

    // update logic, should be called in Dialog::nextFrame()
    virtual void update(int ms) = 0;

    // render the texture, should be called in Dialog::paintEvent()
    virtual void render(QPainter& painter) const;

    // detects with this Sprite is colliding with otherSprite
    // takes into account the Sprite::m_colliderType
    // if the type is None on either sprite, there is no collision
    bool collidesWith(const Sprite& otherSprite) const;

    // gets the bounding rectangle for the sprite
    QRect getBoundingRect() const;

    // changes the texture to another for rendering
    void changeTexture(const QPixmap& texture);

    float getXPosition() const;
    float getYPosition() const;

    void setXPosition(float value);
    void setYPosition(float value);

    int getWidth() const;
    int getHeight() const;

    void setWidth(float value, AspectRatioMode mode = KeepAspectRatio);
    void setHeight(float value, AspectRatioMode mode = KeepAspectRatio);

    ColliderType getColliderType() const;

    float getOriginalXPos() const;
    float getOriginalYPos() const;

    void setOriginalXPos(float xpos);
    void setOriginalYPos(float ypos);

private:
    QPixmap m_texture;

    QPointF m_position;
    QSize m_size;

    ColliderType m_colliderType;

    float m_originalYPos;
    float m_originalXPos;
};

#endif // RENDERABLE_H

