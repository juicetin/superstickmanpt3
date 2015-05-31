#ifndef TESTS_H
#define TESTS_H

#include "game.h"

class Tests
{
public:
    Tests(QDialog *tmp);
    ~Tests();

    // Game tests
    bool pauseStateTest();
    bool pauseEnableTest();
    bool winState();
    bool loseState();
    bool stage3State();
    bool jumpEnableTest();
    bool moveLeftStateTest();
    bool moveRightStateTest();
    bool moveNoStateTest();
    bool switchPauseStateTest();

    // Stickman/adapter tests
    bool setMaxJumpsTest();
    bool setGravityTest();
    bool setJumpForceTest();
    bool resetPositionTest();
	bool moveRightTest();
	bool moveLeftTest();
	bool stopTest();
    bool getJumpForceTest();
    
    bool runAllTests();

    Game *m_game;
};

#endif // TESTS_H
