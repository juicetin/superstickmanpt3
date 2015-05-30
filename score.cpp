#include "score.h"

Score::Score()
{
    m_score = 0;
}

void Score::onNotify(int change)
{
    if (change == COLLISION) m_score /= 2;
}

void Score::render(QPainter &painter)
{
	std::string score_text("The current score is: ");
    std::stringstream ss;
    ss << m_score;
    score_text.append(ss.str());

    QStaticText q_score(score_text.c_str());
    painter.setFont(QFont("Helvetica", 16));
    painter.drawStaticText(0, 0, q_score);
}

void Score::update()
{
	m_score++;
}
