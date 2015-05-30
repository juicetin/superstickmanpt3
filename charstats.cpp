#include "charstats.h"

CharStats::CharStats(Stickman *stickman, StickmanAdapter *stickmanAdapter) :
    m_stickman(stickman),
    m_stickmanAdapter(stickmanAdapter),
    m_curSize(m_stickman->getSize()),
    m_curJumpForce(m_stickmanAdapter->getJumpForce())
{

}

void CharStats::render(QPainter &painter)
{
    std::string size_text ("Your current size is: [");
    const char * s_size = m_stickman->getSizeText(m_curSize);
    size_text.append(s_size).append("]");

    QStaticText q_size(size_text.c_str());
    painter.setFont(QFont("Helvetica", 10));
    painter.drawStaticText(0, 60, q_size);

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
        m_curSize = m_stickman->getSize();
        m_curJumpForce = m_stickmanAdapter->getJumpForce();
    }
}
