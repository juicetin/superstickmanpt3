#ifndef TINYSTICKMAN_H
#define TINYSTICKMAN_H

#include "stickman.h"

class TinyStickman : public Stickman
{
public:
    TinyStickman(const std::vector<QPixmap> &sprites);
    ~TinyStickman();

    virtual int getWidth() const;
    virtual int getHeight() const;
};

#endif // TINYSTICKMAN_H
