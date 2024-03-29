#ifndef STICKMANADAPTER_H
#define STICKMANADAPTER_H

#include "sprite.h"
#include "level.h"
#include "stickman.h"
#include "subject.h"
#include "camera.h"
#include "stickmanfactory.h"

#include <QPainter>
#include <QPixmap>
#include <vector>

// Adapt the Stickman class for Sprite
// Sprite adds the benefits of
//  - collision detection
//  - consistent coordinate system
//  - future extensibility (as everything on screen is a sprite)
class StickmanAdapter : public Sprite, public Subject
{
    friend class Tests;
public:
    // stores a stickman and adapts it
    StickmanAdapter(Stickman* stickman);
    virtual ~StickmanAdapter();

    // render the stickman through Sprite
    virtual void render(QPainter &painter) const;

    // update the adapter code and stickman
    virtual bool update(int ms, Level* level, bool stage_three);

    // adds a upward force to the player
    virtual bool jump();

    void setMaxJumps(int value);
    void setGravity(int value);
    void setJumpForce(int value);

    void resetPosition();
	void moveRight();
	void moveLeft();
	void stop();

    float getJumpForce();

    Stickman *getStickman();

    void growStickman();
    void shrinkStickman();

private:
    // hide the original stickman update, we need to know about Level
    void update(int ms) { (void)ms; }

    // resolves any collisions Stickman has with the level
    bool resolveCollisions(Level* level, bool stage_three);
    void collectPowerups(Level* level, bool stage_three);

private:

    Stickman* m_stickman;
    Stickman* m_stickmen[4];

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
