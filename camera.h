#ifndef CAMERA_H
#define CAMERA_H

#include <QPaintDevice>
#include <QPoint>
#include <QPointF>

class Camera
{
public:
    static Camera& getInstance() {
        static Camera instance;

        return instance;
    }

    void attachToPaintDevice(QPaintDevice* paintDevice);

    QPoint convertToScreenSpace(QPointF pos);

    void setXPosition(float value);
    void setYPosition(float value);

    float getXPosition() const;
    float getYPosition() const;

private:
    Camera() {};

    Camera(const Camera&) {};
    void operator=(const Camera&) {};

    QPaintDevice* m_paintDevice;

    QPoint m_position;
};

#endif // CAMERA_H
