#ifndef GAME_H
#define GAME_H

#include "background.h"
#include "camera.h"
#include "configreader.h"
#include "level.h"
#include "stickman.h"
#include "stickmanadapter.h"
#include "score.h"
#include "lives.h"
#include "stickmanfactory.h"

#include <QImage>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QDir>
#include <string>
#include <vector>
#include <iostream>
#include <QDialog>
#include <QPainter>

class Game
{
	public:
		Game(QDialog *dialog);
        ~Game();
		bool loadConfiguration(const ConfigReader &reader);
		bool loadLevel(Level::Builder &levelBuilder, const ConfigReader &reader);
        void update(QTime &time);
		void render(QPainter &painter);

		StickmanAdapter *getStickman();
		bool pausedState();
		bool pauseEnabled();
		bool wonState();
		bool lostState();
		bool stage3State();
		void charMoving();
		void charNotMoving();
		void switchPaused();

    private:
        int m_timerMs;

		QDialog *m_dialog;

		Stickman *m_stickman;
		StickmanAdapter *m_stickmanAdapter;
		Background *m_background;

		bool m_paused;
		bool m_lost;
		bool m_won;
		bool m_pauseScreenEnabled;
		bool m_stageThreeEnabled;
		bool m_moving;

		QImage m_pauseImage;
		QImage m_lostImage;
		QImage m_wonImage;

		Level* m_level;
		std::vector<std::string> m_levelConfigs;
		std::vector<std::string>::const_iterator m_levelConfigIterator;

		Score m_score;
		Lives *m_lives;

		int m_screenWidth;
		int m_screenHeight;
};

#endif // GAME_H
