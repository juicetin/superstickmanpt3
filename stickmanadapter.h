#ifndef STICKMANADAPTER_H
#define STICKMANADAPTER_H

#include "sprite.h"
#include "level.h"
#include "stickman.h"
#include "subject.h"
#include "camera.h"

#include <QPainter>

// Adapt the Stickman class for Sprite
// Sprite adds the benefits of
//  - collision detection
//  - consistent coordinate system
//  - future extensibility (as everything on screen is a sprite)
class StickmanAdapter : public Sprite, public Subject
{
public:
    // stores a stickman and adapts it
    StickmanAdapter(Stickman* stickman);
    virtual ~StickmanAdapter();

    // render the stickman through Sprite
    virtual void render(QPainter &painter) const;

    // update the adapter code and stickman
    virtual void update(int ms, Level* level);

    // adds a upward force to the player
    virtual void jump();

    void setMaxJumps(int value);
    void setGravity(int value);
    void setJumpForce(int value);

private:
    // hide the original stickman update, we need to know about Level
    void update(int ms) { (void)ms; }

    // resolves any collisions Stickman has with the level
    void resolveCollisions(Level* level);

private:

    Stickman* m_stickman;

    // the up and down velocity, + is up-on-screen
    float m_yVelocity;

    // the initial velocity for jumping
    float m_jumpForce;

    // the force pulling us to the ground
    float m_gravity;

    // the current jumps stickman has down while in air
    int m_currJumpCount;

    // the maximum jumps stickman can do while in air
    int m_maxJumpCount;
};

#endif // STICKMANADAPTER_H
