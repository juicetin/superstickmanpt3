#ifndef GIANTSTICKMAN_H
#define GIANTSTICKMAN_H

#include "stickman.h"

class GiantStickman : public Stickman
{
public:
    GiantStickman(const std::vector<QPixmap> &sprites);
    ~GiantStickman();

    virtual int getWidth() const;
    virtual int getHeight() const;
};

#endif // GIANTSTICKMAN_H
