 #ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QPainter>
#include <QPixmap>

class Background
{
public:
    // Creates a background from an image.
    // If the image isn't big enough to fill the screen, it'll automatically be
    // vertically and horizontally tiled.
    Background(const QPixmap &image);
    ~Background();

    // Render the background.
    // xPosition is the position of the 'camera'.
    void render(QPainter &painter) const;

    void update(int ms);

    // Set duration of a 24h day in game time milliseconds (for night time effect)
    void setDayDuration(int ms);

private:
    QPixmap m_image;
    int m_curTimeMs;
    int m_dayDurationMs; // The duration of a 24h day in game time (for night time effect)
};

#endif // BACKGROUND_H
