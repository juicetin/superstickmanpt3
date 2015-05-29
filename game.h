#ifndef GAME_H
#define GAME_H

#include "stickmanadapter.h"
#include "background.h"
#include "level.h"
#include "lives.h"
#include "score.h"

#include <QImage>
#include <string>
#include <vector>

class Game
{
public:
    Game();
	class Builder;
};

class Game::Builder
{
	public:
		Builder& setStickmanAdapater() 
		{
			
		}
		Builder& setBackground() {}
		Builder& setLevel() {}
		Builder& setLives() {}
		Builder& setScore() {}
		Builder& setPauseImage() {}
		Builder& setLostImage() {}
		Builder& setWinImage() {}
	private:

		QImage m_pauseImage;
		QImage m_lostImage;
		QImage m_wonImage;

		bool m_paused;
		bool m_lost;
		bool m_won;
		bool m_pauseScreenEnabled;
		bool m_stageThreeEnabled;
		bool m_moving;

		Stickman *m_stickman;
		StickmanAdapter *m_stickmanAdapter;
		Background *m_background;
		Level *m_level;
		Lives *m_lives;
		Score m_score;

		std::vector<std::string> m_levelConfigs;
		std::vector<std::string>::const_iterator m_levelConfigIterator;

};

#endif // GAME_H
