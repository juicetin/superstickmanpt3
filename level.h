#ifndef LEVEL_H
#define LEVEL_H

#include "sprite.h"

#include <QPainter>
#include <QRect>
#include <QPoint>

#include <vector>

// A container for all level objects.
// An associated builder - Level::Builder is used to create a level.
//
// Can also find colliding objects with another sprite. Useful for resolving
// collisions with the player.
//
// Here is an example usage:
//
//   Level* level = levelBuilder.getResult();
//   level.update(ms);
//
//   Sprite* collidedWith = level.findCollidingObjects(player);
//   if (collidedWith != nullptr) {
//       // resolve collision
//   }
class Level
{
public:
    class Builder;

    Level();
    ~Level();

    // updates all objects in the level
    void update(int ms);

    // renders all objects in the level
    void render(QPainter& painter) const;

    // finds any internal object colliding with sprite and returns it, or nullptr
    const Sprite* findCollidingObjects(const Sprite* sprite) const;

    // returns the smallest rectangle that surrounds all level objects
    QRect rect() const;

private:
    // all objects in the level
    std::vector<Sprite*> m_objects;
};

// Builds a level bit by bit. An implementation of the builder pattern.
//
// Here is an example usage:
//
//  Level::Builder levelBuilder;
//  levelBuilder.buildObstacle(...);
//  levelBuilder.buildObstacle(...);
//  Level* level = levelBuilder.getResult();
class Level::Builder {
public:
    Builder();
    ~Builder();

    // Creates an obstacle and adds it to the level
    void buildObstacle(QSize size, QPoint point, const QPixmap& texture);

    // Gets the internal level that was being built
    Level* getResult();

private:
    /// the internal level that will
    Level* m_level;
};

#endif // LEVEL_H
