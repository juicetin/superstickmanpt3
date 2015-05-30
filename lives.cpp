#include "lives.h"

Lives::Lives(int lives)
{
    m_lives = lives;
}

void Lives::onNotify(int change)
{
    if (change == COLLISION) m_lives--;
}

void Lives::render(QPainter &painter)
{
	std::string lives_text("You have [");
    std::stringstream ss;
    ss << m_lives;
    lives_text.append(ss.str()).append("] lives remaining");

    QStaticText q_lives(lives_text.c_str());
    painter.setFont(QFont("Helvetica", 14));
    painter.drawStaticText(0, 30, q_lives);
}

bool Lives::update()
{
	if (m_lives < 1)
	{
        return true;
	}
    return false;
}
