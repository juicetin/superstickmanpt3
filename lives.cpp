#include "lives.h"

Lives::Lives(int lives)
{
    m_lives = lives;
}

void Lives::onNotify()
{
    m_lives--;
}

void Lives::render(QPainter &painter)
{
	std::string lives_text("You have [");
    std::stringstream ss;
    ss << m_lives;
    lives_text.append(ss.str());
    lives_text.append("] lives remaining");

    QStaticText q_lives(lives_text.c_str());
    painter.drawStaticText(0, 30, q_lives);
}

void Lives::update()
{
	if (m_lives < 1)
	{
		exit(0);
	}
}