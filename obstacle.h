#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "sprite.h"

#include <QPainter>
#include <QPoint>
#include <QRect>

#define GROW 0
#define SHRINK 1

// Obstacle class representing a collidable object
class Obstacle : public Sprite
{
public:
    // constructor for obstacle
    //  size - the size of the object
    //  spawnAt - the location of the centre of the object
    //  texture - the texture of the object
    Obstacle(QSize size, QPoint spawnAt, const QPixmap &texture);
    Obstacle(QSize size, QPoint spawnAt, const QPixmap &texture, int type);

    // deconstructor
    virtual ~Obstacle();

    // overrides the Sprite::render, renders the obstacle
    virtual void render(QPainter &painter) const;

    // overrides the Sprite::update, updates the obstacle
    virtual void update(int ms);

	virtual int getType() const;

private:
    float m_runningTime;
    int m_type;
};

#endif // OBSTACLE_H
