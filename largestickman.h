#ifndef LARGESTICKMAN_H
#define LARGESTICKMAN_H

#include "stickman.h"

class LargeStickman : public Stickman
{
public:
    LargeStickman(const std::vector<QPixmap> &sprites);
    ~LargeStickman();

    virtual int getWidth() const;
    virtual int getHeight() const;
};

#endif // LARGESTICKMAN_H
