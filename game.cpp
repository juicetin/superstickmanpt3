#include "game.h"

#include <QInputDialog>
#include <QString>
#include <iostream>
#include <cstdio>
using namespace std;

Game::Game(QDialog *dialog) :
m_dialog(dialog),
m_stickmanAdapter(NULL),
m_background(NULL),
m_paused(false),
m_pauseImage(":/resources/paused.png"),
m_lostImage(":/resources/lost.png"),
m_wonImage(":/resources/won.png"),
m_movingRight(false),
m_movingLeft(false),
m_lost(false),
m_won(false),
m_levelsCompleted(0)
{
	std::string configFilePath("../Stage2BaseCodeF/game.config");

	ConfigReader reader(configFilePath);
	if (!loadConfiguration(reader))
	{
		std::string errorMessage;
		if (reader.fileRead())
			errorMessage = std::string("Invalid values in config file. Using some default settings.");
		else
			errorMessage = std::string("Could not open configuration file '") + configFilePath + "'. Using default settings. \n"
		+ "Base directory was '" + QDir::currentPath().toStdString() + "'";
		QMessageBox::warning(m_dialog, "Error", errorMessage.c_str());
	}

	if (m_stageThreeEnabled)
	{
		m_levelConfigIterator = m_levelConfigs.begin();
		ConfigReader level_reader(*m_levelConfigIterator);

        //  Delete level before assigning it the next one
		delete m_level;
		Level::Builder levelBuilder;
		loadLevel(levelBuilder, level_reader);
		m_level = levelBuilder.getResult();
	}

	Camera::getInstance().attachToPaintDevice(m_dialog);
	Camera::getInstance().setXPosition(m_dialog->width() / 2 - m_stickman->getXOffset());
	Camera::getInstance().setYPosition(m_dialog->height() / 2);
}

Game::~Game()
{
    if (m_stageThreeEnabled && (m_won || m_lost))
    {
        QString text = QInputDialog::getText(m_dialog, ("Player Name"),
                                             ("Please enter your name"));
        if (text.isEmpty()) text = "Unnamed";
        //	Print final score, stages completed, lives remaining, lives lost
        FILE *f = fopen("../Stage2BaseCodeF/highscores.txt", "a+");
        fprintf(f, "[Player: %s]\n"
                   "Final Score:     %d\n"
                   "Lives Remaining: %d\n"
                   "Lives Lost:      %d\n"
                   "Levels Complete: %d\n\n",
                text.toStdString().c_str(), m_score->getScore(), m_lives->getLives(),
                m_lives->getLivesLost(), getLevelsComplete());
        fclose(f);
    }

	delete m_stickmanAdapter;
	delete m_score;
	delete m_background;
	delete m_level;
	delete m_lives;
	delete m_charstats;
}
void Game::readObjectPath(std::string &objectSprite, const ConfigReader reader, const std::string name, bool &successful)
{
	objectSprite = reader.get(name, "Sprite");
	if (objectSprite == "") {
		std::cerr << "error: [" << name << "]: Sprite was not set." << std::endl;
		objectSprite = ":/resources/block_brown.png";
		successful = false;
	}
}

void Game::readObjectWidth(int &objectWidth, const ConfigReader reader, bool &parseOk, const std::string name, bool &successful)
{
	objectWidth = QString(reader.get(name, "Width").c_str()).toInt(&parseOk);
	if (!parseOk || objectWidth < 0) {
		std::cerr << "error: [" << name << "]: width was not an integer." << std::endl;
		objectWidth = 1;
		successful = false;
	}
}

void Game::readObjectHeight(int &objectHeight, const ConfigReader reader, bool &parseOk, const std::string name, bool &successful)
{
	objectHeight = QString(reader.get(name, "Height").c_str()).toInt(&parseOk);
	if (!parseOk || objectHeight < 0) {
		std::cerr << "error: [" << name << "]: height was not an integer." << std::endl;
		objectHeight = 1;
		successful = false;
	}
}

bool Game::loadLevel(Level::Builder &levelBuilder, const ConfigReader &reader)
{

	bool parseOk = false;
	bool successful = true;

	int rangeStart = QString(reader.get("Level", "RangeStart").c_str()).toInt(&parseOk);
	if (!parseOk || rangeStart < 0) {
		rangeStart = 0;
		successful = false;
	}

	int rangeEnd = QString(reader.get("Level", "RangeEnd").c_str()).toInt(&parseOk);
	if (!parseOk || rangeEnd < 0) {
		rangeEnd = 0;
		successful = false;
	}

	int obst_unitsInPixels = QString(reader.get("Level", "UnitsInPixels").c_str()).toInt(&parseOk);
	if (!parseOk || obst_unitsInPixels < 0) {
		obst_unitsInPixels = 32;
		successful = false;
	}

	int powup_unitsInPixels = QString(reader.get("Powerups", "UnitsInPixels").c_str()).toInt(&parseOk);
	if (!parseOk || powup_unitsInPixels < 0) {
		powup_unitsInPixels = 32;
		successful = false;
	}

	float obstaclePosition = m_dialog->width(), powerUpPosition = m_dialog->width();
	int obst_previousWidth = 0, powup_previousWidth = 0;
	int i = rangeStart;
	while (i <= rangeEnd) {
		std::stringstream indexStream;
		indexStream << i;

		std::string obstacle_pair = reader.get("Level", indexStream.str());
		std::string powerup_pair = reader.get("Powerups", indexStream.str());

		if (obstacle_pair.empty() && powerup_pair.empty()) {
			break;
		}

		std::string name;
		int gap;
		int height;

		if (!obstacle_pair.empty())
		{
			std::istringstream ss(obstacle_pair.c_str());
			ss >> name;
			ss >> gap;
			ss >> height;

			/* Sprite image path*/
			std::string obstacleSprite;
			readObjectPath(obstacleSprite, reader, name, successful);

			/* Obstacle width */
			int obstacleWidth;
			readObjectWidth(obstacleWidth, reader, parseOk, name, successful);

			/* Obstacle height */
			int obstacleHeight;
			readObjectHeight(obstacleHeight, reader, parseOk, name, successful);

			obstaclePosition += ((obst_previousWidth / 2.0f) + (obstacleWidth / 2.0f)) * obst_unitsInPixels;
			obst_previousWidth = obstacleWidth;

			levelBuilder.buildObstacle(
					QSize(obstacleWidth * obst_unitsInPixels, obstacleHeight * obst_unitsInPixels),
					QPoint(obstaclePosition, (obstacleHeight * obst_unitsInPixels / 2.0f) + height * obst_unitsInPixels),
					QPixmap(obstacleSprite.c_str())
					);

			obstaclePosition += gap * obst_unitsInPixels;
		}

		if (!powerup_pair.empty())
		{
			std::istringstream ss(powerup_pair.c_str());
			ss >> name;
			ss >> gap;
			ss >> height;

			/* Sprite image path*/
			std::string powerUpSprite;
			readObjectPath(powerUpSprite, reader, name, successful);

			/* Obstacle width */
			int powerUpWidth;
			readObjectWidth(powerUpWidth, reader, parseOk, name, successful);

			/* Obstacle height */
			int powerUpHeight;
			readObjectHeight(powerUpHeight, reader, parseOk, name, successful);

			powerUpPosition += ((powup_previousWidth / 2.0f) + (powerUpWidth / 2.0f)) * powup_unitsInPixels;
			powup_previousWidth = powerUpWidth;

			levelBuilder.buildPowerup(
					QSize(powerUpWidth * powup_unitsInPixels, powerUpHeight * powup_unitsInPixels),
					QPoint(powerUpPosition, (powerUpHeight * powup_unitsInPixels / 2.0f) + height * powup_unitsInPixels),
					QPixmap(powerUpSprite.c_str())
					);

			powerUpPosition += gap * powup_unitsInPixels;
		}

		i++;
	}

	return successful;
}


bool Game::loadConfiguration(const ConfigReader &reader)
{
	bool successful = true;
	bool parseOk = false;
	// Parse frame rate
	int frameRate = QString(reader.get("Game", "FrameRate").c_str()).toInt(&parseOk);
	if (!parseOk || frameRate <= 0 || frameRate > 1000) {
		frameRate = 30;
		successful = false;
	}
	m_timerMs = 1000 / frameRate;

	// Parse pause screen on/off
	std::string pauseScreenStatus = reader.get("Game", "PauseScreen");
	if (pauseScreenStatus != "on" && pauseScreenStatus != "off") {
		pauseScreenStatus = "on";
		successful = false;
	}
	m_pauseScreenEnabled = (pauseScreenStatus == "on");

	// Check for stage 3 or 1/2 compatability mode
	std::string stageThreeStatus = reader.get("Game", "Stage3");
	if (stageThreeStatus != "on") {
		stageThreeStatus = "off";
	}
	m_stageThreeEnabled = (stageThreeStatus == "on");

	// Parse background image
	QPixmap bgImage;
	if (!bgImage.load(QString(reader.get("Background", "Sprite").c_str()))) {
		bgImage.load(":/resources/background.png");
		successful = false;

	}
	m_background = new Background(bgImage);

	//THIS BLOCK LEAVE TO DIALOG CLASS
	// Parse background size
	int screenWidth = QString(reader.get("Background", "Width").c_str()).toInt(&parseOk);
	if (!parseOk || screenWidth <= 0) {
		screenWidth = bgImage.width() * 2;
		successful = false;
	}
	int screenHeight = QString(reader.get("Background", "Height").c_str()).toInt(&parseOk);
	if (!parseOk || screenHeight <= 0) {
		screenHeight = bgImage.height();
		successful = false;
	}
	m_dialog->setFixedSize(screenWidth, screenHeight);

	// Parse day duration for night filter effect
	int dayDuration = QString(reader.get("Background", "DayDuration").c_str()).toInt(&parseOk);
	if (!parseOk || dayDuration < 0) {
		dayDuration = 60000; // Defaults to 1 minute
		successful = false;
	}
	m_background->setDayDuration(dayDuration);

	/*************************************************************************************/
	/***************************    LOAD ALL OBSTACLES    ********************************/
	/*************************************************************************************/
	Level::Builder levelBuilder;
	loadLevel(levelBuilder, reader);
	m_level = levelBuilder.getResult();
	/*************************************************************************************/

	/*************************************************************************************/
	/*****************************    LOAD ALL LEVELS    *********************************/
	/*************************************************************************************/
	//  Memory efficient design - not loading all levels at the get-go, but instead load
	//  as each level is completed
	int numLevels = QString(reader.get("Levels", "Levels").c_str()).toInt(&parseOk);
	if (!parseOk || numLevels < 1) {
		numLevels = 0;
		// Disable stage 3 if no levels are present - default to stage 1/2 compatability if
		// no levels are provided. I.e. use any obstacles that may be present from stage 2
		m_stageThreeEnabled = false;
		successful = false;
	}

	for (int i = 1; i <= numLevels; ++i)
	{
		std::stringstream ss;
		ss << i;
		std::string file_path = QString( reader.get("Levels", ss.str().c_str()).c_str()).toStdString();
		m_levelConfigs.push_back(file_path);
	}
	/*************************************************************************************/

	// Parse stickman size
	std::string stickmanSize = reader.get("Stickman", "Size");
	if (stickmanSize != "tiny" && stickmanSize != "normal" && stickmanSize != "large" && stickmanSize != "giant") {
		stickmanSize = "normal";
		successful = false;
	}

	// Parse stickman sprites
	std::istringstream ss(reader.get("Stickman", "Sprites").c_str());

	std::string stickmanSpritePath;
	while (ss >> stickmanSpritePath) {
		QPixmap sprite;
		if (!sprite.load(stickmanSpritePath.c_str())) {
			m_sprites.clear();
			break;
		}
		m_sprites.push_back(sprite);
	}

	if (m_sprites.empty()) {
		m_sprites.push_back(QPixmap(":/resources/flap_up.png"));
		m_sprites.push_back(QPixmap(":/resources/flap_down.png"));
		successful = false;
	}

	// Now we've got enough information to construct a stickman
	m_stickman = StickmanFactory::create(stickmanSize, m_sprites);

	// Parse other stickman properties
	int stickmanXOffset = QString(reader.get("Stickman", "XOffset").c_str()).toInt(&parseOk);
	if (!parseOk) {
		stickmanXOffset = 0;
		successful = false;
	}
	m_stickman->setXOffset(stickmanXOffset);

	float stickmanXVelocity = QString(reader.get("Stickman", "XVelocity").c_str()).toFloat(&parseOk);
	if (!parseOk) {
		stickmanXVelocity = 10.0;
		successful = false;
	}
	if (m_stageThreeEnabled) { m_stickman->setXVelocity(0); }
	else { m_stickman->setXVelocity(stickmanXVelocity); }

	int stickmanSpriteDuration = QString(reader.get("Stickman", "SpriteDuration").c_str()).toInt(&parseOk);
	if (!parseOk || stickmanSpriteDuration <= 0) {
		stickmanSpriteDuration = 300;
		successful = false;
	}
	m_stickman->setSpriteDuration(stickmanSpriteDuration);

	int lives = QString(reader.get("Stickman", "Lives").c_str()).toInt(&parseOk);
	if (!parseOk || lives < 1) {
		lives = 1;
		successful = false;
	}
	m_lives = new Lives(lives);
	m_score = new Score(m_lives);

	m_stickmanAdapter = new StickmanAdapter(m_stickman);

	m_charstats = new CharStats(m_stickmanAdapter);

	m_stickmanAdapter->addObserver(m_score);
	m_stickmanAdapter->addObserver(m_lives);
	m_stickmanAdapter->addObserver(m_charstats);
	m_stickmanAdapter->addObserver(this);

	int stickmanMaxJumps = QString(reader.get("Stickman", "MaxJumps").c_str()).toInt(&parseOk);
	if (!parseOk || stickmanMaxJumps <= 0) {
		stickmanMaxJumps = 0;
		successful = false;
	}
	m_stickmanAdapter->setMaxJumps(stickmanMaxJumps);

	int stickmanJumpForce = QString(reader.get("Stickman", "JumpForce").c_str()).toInt(&parseOk);
	if (!parseOk || stickmanJumpForce <= 0) {
		stickmanJumpForce = 400;
		successful = false;
	}

	int stickmanGravity = QString(reader.get("Stickman", "Gravity").c_str()).toInt(&parseOk);
	if (!parseOk || stickmanGravity <= 0) {
		stickmanGravity = 1500;
		successful = false;
	}

	return successful;
}

void Game::update(QTime &time)
{

	// Update the game state
	if (!m_paused) {
		// Get the milliseconds since last frame
		int ms = time.restart();

		// Update our entities
		m_background->update(ms);
		m_level->update(ms);
		m_stickmanAdapter->update(ms, m_level, m_stageThreeEnabled);

		// Point the camera at the player (with an offset)
		Camera::getInstance().setXPosition(m_stickmanAdapter->getXPosition() + m_dialog->width() / 2 - m_stickman->getXOffset());

		// if we have passed the level, reset the player to 0 to play again
		if (!m_stageThreeEnabled && (m_level->rect().right()) < m_stickmanAdapter->getXPosition() - m_stickman->getXOffset()) {
			m_stickmanAdapter->setXPosition(0);
		}

        if (m_movingLeft || m_movingRight) {
            m_score->update(m_movingLeft, m_movingRight);
		}
	}
}

void Game::onNotify(int change)
{
	// When a level is finished
	if (change == REACHEDGOAL && m_stageThreeEnabled)
	{
        m_levelsCompleted++;
		// Finish the game if last level
		m_levelConfigIterator++;
		if (m_levelConfigIterator == m_levelConfigs.end())
		{
			m_won = true;
			m_paused = true;
		}
		// Move onto the next level
		else
		{
			delete m_level;
			ConfigReader level_reader(*m_levelConfigIterator);
			Level::Builder levelBuilder;
			loadLevel(levelBuilder, level_reader);
			m_level = levelBuilder.getResult();
			m_stickmanAdapter->resetPosition();
		}
	}
}

void Game::render(QPainter &painter)
{
	m_background->render(painter);
	m_stickmanAdapter->render(painter);
	m_level->render(painter);

	if (m_stageThreeEnabled)
	{
		m_charstats->render(painter);
		m_score->render(painter);
		m_lives->render(painter);
		if (m_lost = m_lives->update())
		{
			m_paused = true;
		}
	}

	if (m_paused) {
		//Render a pause message, with darkened background.
		QRectF windowRect(0, 0, painter.device()->width(), painter.device()->height());
		painter.fillRect(windowRect, QBrush(QColor(0, 0, 0, 128)));

		int x = painter.device()->width() / 2 - m_pauseImage.width() / 2;
		int y = painter.device()->height() / 2 - m_pauseImage.height() / 2;

		if (m_won)
		{
			painter.drawImage(x, y, m_wonImage);
		}
		else if (m_lost)
		{
			painter.drawImage(x, y, m_lostImage);
		}
		else
		{
			painter.drawImage(x, y, m_pauseImage);
		}

		//	Print final score
		if (m_won || m_lost)
		{
			std::string score_text("YOUR FINAL SCORE IS: ");
			std::stringstream ss;
			ss << m_score->getScore();
			score_text.append(ss.str());

			QStaticText q_score(score_text.c_str());
			painter.setFont(QFont("Helvetica", 16));
			painter.setPen(Qt::white);
			painter.drawStaticText(m_dialog->width()/2-105, m_dialog->height()/2+40, q_score);
		}
	}
}

StickmanAdapter *Game::getStickman()
{
	return m_stickmanAdapter;
}

bool Game::pausedState() const
{
	return m_paused;
}

bool Game::pauseEnabled() const
{
	return m_pauseScreenEnabled;
}

bool Game::wonState() const
{
	return m_won;
}

bool Game::lostState() const
{
	return m_lost;
}

bool Game::stage3State() const
{
	return m_stageThreeEnabled;
}

int Game::getLevelsComplete() const
{
    return m_levelsCompleted;
}

void Game::charMovingLeft()
{
	m_movingLeft = true;
}

void Game::charMovingRight()
{
	m_movingRight = true;
}

void Game::charNotMoving()
{
	m_movingLeft = false;
	m_movingRight = false;
}

void Game::switchPaused()
{
	m_paused = !m_paused;
}
