#ifndef NORMALSTICKMAN_H
#define NORMALSTICKMAN_H

#include "stickman.h"

class NormalStickman : public Stickman
{
public:
    NormalStickman(const std::vector<QPixmap> &sprites);
    ~NormalStickman();

    virtual int getWidth() const;
    virtual int getHeight() const;
};

#endif // NORMALSTICKMAN_H
