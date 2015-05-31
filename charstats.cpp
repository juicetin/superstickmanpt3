#include "charstats.h"

#include <iostream>
using namespace std;

CharStats::CharStats(StickmanAdapter *stickmanAdapter) :
    m_stickmanAdapter(stickmanAdapter),
    m_curSize(m_stickmanAdapter->getStickman()->getSize()),
    m_curJumpForce(m_stickmanAdapter->getJumpForce())
{

}

CharStats::~CharStats()
{

}

void CharStats::render(QPainter &painter)
{
    /* Current size */
    std::string size_text ("Your current size is: [");
    std::string s_size = m_stickmanAdapter->getStickman()->getSizeText(m_curSize);
    size_text.append(s_size.c_str()).append("]");

    QStaticText q_size(size_text.c_str());
    painter.setFont(QFont("Helvetica", 10));
    painter.drawStaticText(0, 60, q_size);

    /* Current jump force */
    std::string jump_text("Your current jump force is: [");
    std::stringstream ss;
    ss << m_curJumpForce;
    jump_text.append(ss.str().c_str()).append("]");

    QStaticText q_jump(jump_text.c_str());
    painter.drawStaticText(0, 80, q_jump);
}

void CharStats::onNotify(int change)
{
    if (change == POWERUP)
    {
        m_curSize = m_stickmanAdapter->getStickman()->getSize();
        m_curJumpForce = m_stickmanAdapter->getJumpForce();
    }
}

std::string CharStats::getSize() const
{
    return m_stickmanAdapter->getStickman()->getSizeText(m_curSize);
}

float CharStats::getJumpForce() const
{
    return m_curJumpForce;
}
