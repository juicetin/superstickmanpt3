#include "level.h"
#include "obstacle.h"

#include <limits>
#include <iostream>
using namespace std;

Level::Level()
{

}

Level::~Level()
{
    for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
    {
        delete *it;
    }
}

void Level::update(int ms)
{
    std::vector<Sprite*>::iterator it;

    for (it = m_objects.begin(); it != m_objects.end(); it++) {
        (*it)->update(ms);
    }
}

void Level::render(QPainter& painter) const
{
    {
        std::vector<Sprite*>::const_iterator it;

        for (it = m_objects.begin(); it != m_objects.end(); it++) {
            (*it)->render(painter);
        }
    }
    {
        std::list<Sprite*>::const_iterator it;

        for (it = m_powerups.begin(); it != m_powerups.end(); it++) {
            (*it)->render(painter);
        }
    }
}

const Sprite* Level::findCollidingObjects(const Sprite* sprite) const
{
    std::vector<Sprite*>::const_iterator it;

    for (it = m_objects.begin(); it != m_objects.end(); it++) {
        if ((*it)->collidesWith(*sprite)) {
            return (*it);
        }
    }

    return 0;
}

int Level::findCollectedPowerups(Sprite* sprite)
{
    std::list<Sprite*>::iterator it;

    for (it = m_powerups.begin(); it != m_powerups.end(); it++) {
        if ((*it)->collidesWith(*sprite)) {
            m_powerups.erase(it);
            return static_cast<Obstacle*>((*it))->getType();
        }
    }

    return -1;
}

QRect Level::rect() const {
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();

    std::vector<Sprite*>::const_iterator it;

    for (it = m_objects.begin(); it != m_objects.end(); it++) {
        QRect spriteRect = (*it)->getBoundingRect();

        if (spriteRect.x() < minX)
            minX = spriteRect.x();

        if (spriteRect.y() < minY)
            minY = spriteRect.y();

        if (spriteRect.right() > maxX)
            maxX = spriteRect.right();

        if (spriteRect.bottom() < maxY)
            minX = spriteRect.bottom();
    }

    return QRect(minX, minY, maxX - minX, maxY - minY);
}

bool Level::checkGoalReached(const Sprite *sprite) const
{
    std::vector<Sprite*>::const_iterator it = std::find(m_objects.begin(), m_objects.end(), sprite);
    if (it != m_objects.end())
    {
        it++;
        if (it == m_objects.end())
        {
            return true;
        }
    }
    return false;
}

//###################################################################
// Everything below is the Level::Builder
//###################################################################

Level::Builder::Builder() :
    m_level(new Level())
{

}

Level::Builder::~Builder()
{

}

void Level::Builder::buildObstacle(QSize size, QPoint point, const QPixmap &texture)
{
    m_level->m_objects.push_back(
                new Obstacle(
                    size,
                    point,
                    texture
                    )
                );
}

void Level::Builder::buildPowerup(QSize size, QPoint point, const QPixmap& texture, int type)
{
    m_level->m_powerups.push_back(
                new Obstacle(
                    size,
                    point,
                    texture,
                    type
                    )
                );
}

Level* Level::Builder::getResult()
{
    return m_level;
}
