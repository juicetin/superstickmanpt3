#include "dialog.h"

#include "camera.h"
#include "configreader.h"
#include "stickmanfactory.h"

#include <ui_dialog.h>
#include <QDir>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QStaticText>

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

bool Dialog::loadLevel(Level::Builder &levelBuilder, const ConfigReader &reader)
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

    int unitsInPixels = QString(reader.get("Level", "UnitsInPixels").c_str()).toInt(&parseOk);
    if (!parseOk || unitsInPixels < 0) {
        unitsInPixels = 32;
        successful = false;
    }
    
    float obstaclePosition = this->width();
    int previousWidth = 0;
    int i = rangeStart;
    while (i <= rangeEnd) {
        std::stringstream indexStream;
        indexStream << i;

        std::string pair = reader.get("Level", indexStream.str());
        if (pair.empty()) {
            break;
        }

        std::istringstream ss(pair.c_str());

        std::string name;
        int gap;
        int height;

        ss >> name;
        ss >> gap;
        ss >> height;
        
        /* Sprite image path*/
        std::string obstacleSprite = reader.get(name, "Sprite");
        if (!parseOk || obstacleSprite == "") {
            std::cerr << "error: [" << name << "]: Sprite was not set." << std::endl;
            obstacleSprite = ":/resources/block_brown.png";
            successful = false;
        }

        /* Obstacle width */
        int obstacleWidth = QString(reader.get(name, "Width").c_str()).toInt(&parseOk);
        if (!parseOk || obstacleWidth < 0) {
            std::cerr << "error: [" << name << "]: width was not an integer." << std::endl;
            obstacleWidth = 1;
            successful = false;
        }


        int obstacleHeight = QString(reader.get(name, "Height").c_str()).toInt(&parseOk);
        if (!parseOk || obstacleHeight < 0) {
            std::cerr << "error: [" << name << "]: height was not an integer." << std::endl;
            obstacleHeight = 1;
            successful = false;
        }

        obstaclePosition += ((previousWidth / 2.0f) + (obstacleWidth / 2.0f)) * unitsInPixels;
        previousWidth = obstacleWidth;

        levelBuilder.buildObstacle(
            QSize(obstacleWidth * unitsInPixels, obstacleHeight * unitsInPixels),
            QPoint(obstaclePosition, (obstacleHeight * unitsInPixels / 2.0f) + height * unitsInPixels),
            QPixmap(obstacleSprite.c_str())
            );

        obstaclePosition += gap * unitsInPixels;

        i++;
    }

    return successful;
}

bool Dialog::loadConfiguration(const ConfigReader &reader)
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
    setFixedSize(screenWidth, screenHeight);

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
    std::vector<QPixmap> sprites;
    std::istringstream ss(reader.get("Stickman", "Sprites").c_str());

    std::string stickmanSpritePath;
    while (ss >> stickmanSpritePath) {
        QPixmap sprite;
        if (!sprite.load(stickmanSpritePath.c_str())) {
            sprites.clear();
            break;
        }
        sprites.push_back(sprite);
    }

    if (sprites.empty()) {
        sprites.push_back(QPixmap(":/resources/flap_up.png"));
        sprites.push_back(QPixmap(":/resources/flap_down.png"));
        successful = false;
    }

    // Now we've got enough information to construct a stickman
    m_stickman = StickmanFactory::create(stickmanSize, sprites);

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

    m_stickmanAdapter = new StickmanAdapter(m_stickman);
    m_stickmanAdapter->addObserver(&m_score);
    m_stickmanAdapter->addObserver(m_lives);

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

Dialog::Dialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::Dialog),
m_stickmanAdapter(NULL),
m_background(NULL),
m_paused(false),
m_pauseImage(":/resources/paused.png"),
m_lostImage(":/resources/lost.png"),
m_wonImage(":/resources/won.png"),
m_moving(false),
m_lost(false),
m_won(false)
{
    ui->setupUi(this);

    std::string configFilePath("../Stage2BaseCodeF/game.config");

    // Read the configuration file to initialise the background and stickman.
    // Opens a message box if the configuration file couldn't be read.
    ConfigReader reader(configFilePath);
    if (!loadConfiguration(reader)) {
        std::string errorMessage;
        if (reader.fileRead())
            errorMessage = std::string("Invalid values in configuration file. Using some default settings.");
        else
            errorMessage = std::string("Could not open configuration file '") + configFilePath + "'. Using default settings. \n"
        + "Base directory was '" + QDir::currentPath().toStdString() + "'";
        QMessageBox::warning(this, "Error", errorMessage.c_str());
    }

    if (m_stageThreeEnabled)
    {
        m_levelConfigIterator = m_levelConfigs.begin();
        ConfigReader level_reader(*m_levelConfigIterator);
        delete m_level;
        Level::Builder levelBuilder;
        loadLevel(levelBuilder, level_reader);
        m_level = levelBuilder.getResult();
    }

    // Create a timer to update and redraw at regular intervals.
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(m_timerMs);

    m_time.restart();

    Camera::getInstance().attachToPaintDevice(this);
    Camera::getInstance().setXPosition(this->width() / 2 - m_stickman->getXOffset());
    Camera::getInstance().setYPosition(this->height() / 2);
}

Dialog::~Dialog()
{
    delete m_background;
    delete m_stickmanAdapter;
    delete ui;
    delete m_lives;
    delete m_level;
}

void Dialog::nextFrame()
{
    // Update the game state
    if (!m_paused) {
        // Get the milliseconds since last frame
        int ms = m_time.restart();

        // Update our entities
        m_background->update(ms);
        m_level->update(ms);
        bool check_goal = m_stickmanAdapter->update(ms, m_level, m_stageThreeEnabled);

        //Load new level if goal in level has been reached
        if (check_goal)
        {
            m_levelConfigIterator++;
            if (m_levelConfigIterator == m_levelConfigs.end())
            {
                m_won = true;
                m_paused = true;
            }
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

        // Point the camera at the player (with an offset)
        Camera::getInstance().setXPosition(m_stickmanAdapter->getXPosition() + this->width() / 2 - m_stickman->getXOffset());

        // if we have passed the level, reset the player to 0 to play again
        if ( (m_level->rect().right()) < m_stickmanAdapter->getXPosition() - m_stickman->getXOffset()) {
            m_stickmanAdapter->setXPosition(0);
        }

        if (m_moving) {
            m_score.update();
        }
    }

    // Redraw the screen
    update();
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Render game components
    m_background->render(painter);
    m_stickmanAdapter->render(painter);
    m_level->render(painter);

    if (m_stageThreeEnabled)
    {
        m_score.render(painter);
        m_lives->render(painter);
        if (m_lost = m_lives->update())
        {
            m_paused = true;
        }
    }

    if (m_paused) {
        // Render a pause message, with darkened background.
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
    }
}

void Dialog::keyPressEvent(QKeyEvent *e)
{
    if (m_pauseScreenEnabled &&
        !m_won &&
        !m_lost && 
        e->key() == Qt::Key_Escape)
    {
        m_paused = !m_paused;
    }

    if (e->key() == Qt::Key_Q)
    {
        this->close();
    }

    if (e->key() == Qt::Key_Space)
    {
        m_stickmanAdapter->jump();
    }

    if (m_stageThreeEnabled && e->key() == Qt::Key_Left)
    {
        m_stickmanAdapter->setXVelocity(-170);
        m_moving = true;
    }

    if (m_stageThreeEnabled && e->key() == Qt::Key_Right)
    {
        m_stickmanAdapter->setXVelocity(170);
        m_moving = true;
    }
}

void Dialog::keyReleaseEvent(QKeyEvent *e)
{
    if (m_stageThreeEnabled && (e->key() == Qt::Key_Left || e->key() == Qt::Key_Right))
    {
        m_stickmanAdapter->setXVelocity(0);
        m_moving = false;
    }
}
