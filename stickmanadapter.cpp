#define _USE_MATH_DEFINES
#include <cmath>

#include "stickmanadapter.h"

#include <QVector2D>

StickmanAdapter::StickmanAdapter(Stickman* stickman) :
    m_stickman(stickman),
    m_yVelocity(0),
    m_jumpForce(400.0f),
    m_gravity(1500.0f),
    m_currJumpCount(0),
    m_maxJumpCount(2),
    Sprite(stickman->getSprite())
{
    Sprite::setXPosition(0.0f);
    // set the exact dimensions of the sprite according to stickman
    Sprite::setHeight(m_stickman->getHeight(), IgnoreAspectRatio);
    Sprite::setWidth(m_stickman->getWidth(), IgnoreAspectRatio);
}

StickmanAdapter::~StickmanAdapter()
{
}

void StickmanAdapter::render(QPainter &painter) const
{
    Sprite::render(painter);
}

// quick clamping function for collision detection
float clampf(float value, float min, float max) {

    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

void StickmanAdapter::resolveCollisions(Level *level) {
    const Sprite* sprite = 0;

    // find colliding sprites, and resolve them by:
    // finding out which direction we collided into them with, and choose the most
    // appropriate way to move out of the collision
    while ((sprite = level->findCollidingObjects(dynamic_cast<Sprite*>(this))) != 0) {

        // find the closest point in sprite to the stickman's centre
        QVector2D closestPoint(
            clampf(getXPosition(), sprite->getBoundingRect().left(), sprite->getBoundingRect().right()),
            clampf(getYPosition(), sprite->getBoundingRect().top(), sprite->getBoundingRect().bottom())
        );

        // the direction from that point to us
        QVector2D collisionDir = QVector2D(getXPosition(), getYPosition()) - closestPoint;

        // the direction we were moving, flipped
        QVector2D movementDir = -QVector2D(m_stickman->getXVelocity(), m_yVelocity);

        // the average between these two
        QVector2D average = collisionDir.normalized() + movementDir.normalized();
        //average.normalize();

        // find the angle the vector is at, allows us to see which way we should move to avoid collision
        double angle = atan2(average.y(), average.x());
        if (angle < 0) {
            angle += 2 * M_PI;
        }

        // get the overlapping rectangle
        QRect ins = getBoundingRect().intersected(sprite->getBoundingRect());

        bool wanted_collision = false;

        // did we hit something below?
        if (angle > 0.25 * M_PI && angle <= 0.75 * M_PI) {
            setYPosition(getYPosition() + ins.height());
            m_yVelocity = 0;
            m_currJumpCount = 0;

        // did we hit a wall on the right?
        } else if (angle > 0.75 * M_PI && angle <= 1.25 * M_PI) {
            setXPosition(getXPosition() - ins.width());
            wanted_collision = true;

        // did we hit something above?
        } else if (angle > 1.25 * M_PI && angle <= 1.75 * M_PI) {
            setYPosition(getYPosition() - ins.height());
            m_yVelocity = 0;

        // did we hit a wall on the left?
        } else if ( (angle > 1.75 * M_PI && angle <= 2 * M_PI) || (angle >= 0 && angle <= 0.25 * M_PI)) {
            setXPosition(getXPosition() + ins.width());
            wanted_collision = true;
        }

        // Resets from collision only occur when hitting the right/left sides
        if (wanted_collision)
        {
            notify();
            setXPosition(0);
        }
    }
}

void StickmanAdapter::update(int ms, Level* level)
{
    m_stickman->update(ms);

    // update the positions with the velocities
    setXPosition(getXPosition() + m_stickman->getXVelocity() * (ms / 1000.0));
    setYPosition(getYPosition() + m_yVelocity * (ms / 1000.0));


    resolveCollisions(level);


    // change the sprite to the current sprite (the stickman is animated)
    changeTexture(m_stickman->getSprite());

    // cause the y position to fall if we are not on the ground
    if (getYPosition() > 0 + (m_stickman->getHeight() / 2)) {
        m_yVelocity -= m_gravity * (ms / 1000.0);
    } else {
        m_yVelocity = 0;
        m_currJumpCount = 0;
        setYPosition(0 + (m_stickman->getHeight() / 2));
    }
}

void StickmanAdapter::jump() {
    if (m_currJumpCount < m_maxJumpCount) {
        m_yVelocity = m_jumpForce;
        m_currJumpCount++;
    }
}

void StickmanAdapter::setMaxJumps(int value) {
    m_maxJumpCount = value;
}

void StickmanAdapter::setGravity(int value) {
    m_gravity = value;
}

void StickmanAdapter::setJumpForce(int value) {
    m_jumpForce = value;
}
