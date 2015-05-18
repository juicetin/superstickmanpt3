#include "background.h"

#include "camera.h"

#include <cmath>

// Clamps a value 'x' to be between 'min' and 'max'
static float clamped(float x, float min, float max) {
    return std::min(max, std::max(x, min));
}

Background::Background(const QPixmap &image)
    : m_image(image),
      m_curTimeMs(0),
      m_dayDurationMs(60000)
{
}

Background::~Background()
{
}

void Background::render(QPainter &painter) const
{
    int width = m_image.width();
    int height = m_image.height();

    // Calculate the x coordinate to start tiling the image from.
    int startX = -int(Camera::getInstance().getXPosition()) % width - width;

    // Tile multiple copies of the image to fill the screen.
    for (int x = startX; x < painter.device()->width(); x += width) {
        for (int y = 0; y < painter.device()->height(); y += height) {
            painter.drawPixmap(x, y, m_image);
        }
    }

    // Apply a night time filter
    if (m_dayDurationMs) {
        // The strength of the night effect filter varies according to a truncated sine wave
        float dayProgress = (float)m_curTimeMs / m_dayDurationMs;
        float effectStrength = clamped(-std::cos(dayProgress * 3.14159f), -0.5f, 0.5f) + 0.5f;

        QRectF windowRect(0, 0, painter.device()->width(), painter.device()->height());
        painter.fillRect(windowRect, QBrush(QColor(0, 0, 100 * effectStrength, 128 * effectStrength)));
    }
}

void Background::update(int ms)
{
    m_curTimeMs += ms;
}

void Background::setDayDuration(int ms)
{
    m_dayDurationMs = ms;
}
