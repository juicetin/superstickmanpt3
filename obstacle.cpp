#include "obstacle.h"

#include <iostream>
using namespace std;

Obstacle::Obstacle(QSize size, QPoint spawnAt, const QPixmap &texture) :
    Sprite(texture)
{
    setWidth(size.width(), IgnoreAspectRatio);
    setHeight(size.height(), IgnoreAspectRatio);
    setXPosition(spawnAt.x());
    setYPosition(spawnAt.y());

    //Store spawn position of obstacle for resetting
    setOriginalXPos(spawnAt.x());
    setOriginalYPos(spawnAt.y());
}

Obstacle::~Obstacle()
{

}

void Obstacle::render(QPainter& painter) const
{
    Sprite::render(painter);
}

void Obstacle::update(int ms)
{

}
