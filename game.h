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
#include "charstats.h"
#include "observer.h"

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
#include <fstream>

class Game : public Observer
{
	public:
		Game(QDialog *dialog);
        ~Game();

        void onNotify(int change);

		bool loadConfiguration(const ConfigReader &reader);
		bool loadLevel(Level::Builder &levelBuilder, const ConfigReader &reader);

        void update(QTime &time);
		void render(QPainter &painter);

        StickmanAdapter *getStickman();

        bool pausedState() const;
        bool pauseEnabled() const;
        bool wonState() const;
        bool lostState() const;
        bool stage3State() const;

        int getLevelsComplete() const;

		void charMovingRight();
		void charMovingLeft();
		void charNotMoving();
		void switchPaused();

        void readObjectPath(std::string &objectSprite, const ConfigReader reader, const std::string name, bool &successful);
        void readObjectWidth(int &objectWidth, const ConfigReader reader, bool &parseOk, const std::string name, bool &successful);
        void readObjectHeight(int &objectHeight, const ConfigReader reader, bool &parseOk, const std::string name, bool &successful);
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
		bool m_movingLeft;
		bool m_movingRight;

		QImage m_pauseImage;
		QImage m_lostImage;
		QImage m_wonImage;

        int m_levelsCompleted;

		Level* m_level;
		std::vector<std::string> m_levelConfigs;
		std::vector<std::string>::const_iterator m_levelConfigIterator;

		Score *m_score;
        Lives *m_lives;
        CharStats *m_charstats;

		int m_screenWidth;
		int m_screenHeight;

		std::vector<QPixmap> m_sprites;
};

#endif // GAME_H
