#ifndef STICKMAN_H
#define STICKMAN_H

#include <QPainter>
#include <QPixmap>

enum StickmanSize
{
    STICKMAN_TINY,
    STICKMAN_NORMAL,
    STICKMAN_LARGE,
    STICKMAN_GIANT
};

static const char * enumStrings[] = {"tiny", "normal", "large", "giant"};

class Stickman
{
public:
    friend class StickmanAdapter;

    // Initialises a new stickman
    // sprites is a list of animation frames
    Stickman(StickmanSize size, const std::vector<QPixmap> &sprites);
    virtual ~Stickman();

    const char * getSizeText(int enumVal);

    virtual void render(QPainter &painter) const;
    virtual void update(int ms);

    // X coordinate of the stickman on the screen
    int getXOffset() const;
    void setXOffset(int value);

    // X position of the stickman in the game world
    float getXPosition() const;

    // X velocity of the stickman in the game world
    float getXVelocity() const;
    void setXVelocity(float value);

    StickmanSize getSize() const;

    // Bounding box for the stickman
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    // Duration of each frame in ms
    int getSpriteDuration() const;
    void setSpriteDuration(int ms);

protected:
    const QPixmap &getSprite() const;

private:
    StickmanSize m_size;
    int m_xOffset;
    float m_xPosition;
    float m_xVelocity;

    std::vector<QPixmap> m_sprites; // List of sprites for each frame
    std::vector<QPixmap>::size_type m_curSpriteIdx; // Index of the current frame of the sprite
    int m_spriteDurationMs; // Duration of each frame in ms
    int m_curSpriteDurationMs; // How long the current sprite has been shown for
};

#endif // STICKMAN_H
