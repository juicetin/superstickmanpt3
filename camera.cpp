#include "camera.h"

void Camera::attachToPaintDevice(QPaintDevice* paintDevice) {
    m_paintDevice = paintDevice;
}


/*  +y is to the top of the screen
 *  +x is to the right of the screen
 */
QPoint Camera::convertToScreenSpace(QPointF pos) {
    QPoint q(
        pos.x() - getXPosition() + 0.5 * m_paintDevice->width(),
        -pos.y() + getYPosition() + 0.5 * m_paintDevice->height()
    );

    return q;
}

void Camera::setXPosition(float value) {
    m_position.setX(value);
}

void Camera::setYPosition(float value) {
   m_position.setY(value);
}

float Camera::getXPosition() const {
    return m_position.x();
}

float Camera::getYPosition() const {
    return m_position.y();
}
