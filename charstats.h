#ifndef CHARSTATS_H
#define CHARSTATS_H

#include <QPainter>
#include <QStaticText>
#include <sstream>
#include <string>

#include "stickman.h"
#include "stickmanadapter.h"
#include "observer.h"

class CharStats : public Observer
{
public:
    CharStats(StickmanAdapter *stickmanAdapter);
    ~CharStats();
    void render(QPainter &qpainter);
    void onNotify(int change);

private:
    StickmanAdapter *m_stickmanAdapter;
    StickmanSize m_curSize;
    float m_curJumpForce;
};

#endif // CHARSTATS_H
