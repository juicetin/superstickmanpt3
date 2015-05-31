#include "tests.h"

#include <iostream>
using namespace std;

Tests::Tests(QDialog *tmp) : 
m_game(new Game(tmp))
{

}

Tests::~Tests()
{
	delete m_game;
}

/******************************************************************************************************/
/********************************************* Game tests *********************************************/
/******************************************************************************************************/

bool Tests::pauseStateTest()
{
	int check = 0;
	m_game->m_paused = false;
	if (!m_game->pausedState()) check ++;
	m_game->m_paused = true;
	if (m_game->pausedState()) check++;
	return check == 2;
}

bool Tests::pauseEnableTest()
{
	int check = 0;
	m_game->m_pauseScreenEnabled = false;
	if (!m_game->pauseEnabled()) check++;
	m_game->m_pauseScreenEnabled = true;
	if (m_game->pauseEnabled()) check++;
	return check == 2;
}

bool Tests::winState()
{
	int check = 0;
	m_game->m_won = false;
	if (!m_game->wonState()) check++;
	m_game->m_won = true;
	if (m_game->wonState()) check ++;
	return check == 2;
}

bool Tests::loseState()
{
	int check = 0;
	m_game->m_lost = false;
	if (!m_game->lostState()) check++;
	m_game->m_lost = true;
	if (m_game->lostState()) check ++;
	return check == 2;
}

bool Tests::stage3State()
{
	int check = 0;
	m_game->m_stageThreeEnabled = false;
	if (!m_game->stage3State()) check++;
	m_game->m_stageThreeEnabled = true;
	if (m_game->stage3State()) check ++;
	return check == 2;
}

bool Tests::jumpEnableTest()
{
	int check = 0;
	m_game->m_jumpEnabled = false;
	if (!m_game->jumpAllowed()) check++;
	m_game->m_jumpEnabled = true;
	if (m_game->jumpAllowed()) check++;
	return check == 2;
}

bool Tests::moveLeftStateTest()
{
	m_game->charMovingLeft();
	return m_game->m_movingLeft;
}

bool Tests::moveRightStateTest()
{
	m_game->charMovingRight();
	return m_game->m_movingRight;
}

bool Tests::moveNoStateTest()
{
	m_game->charNotMoving();
	return !m_game->m_movingLeft && !m_game->m_movingRight;
}

bool Tests::switchPauseStateTest()
{
	int check = 0;
	m_game->m_paused = false;
	m_game->switchPaused();
	if (m_game->m_paused) check++;
	m_game->switchPaused();
	if (!m_game->m_paused) check++;
	return check == 2;
}

/******************************************************************************************************/
/*************************************** Stickman/adapter tests ***************************************/
/******************************************************************************************************/

bool Tests::setMaxJumpsTest()
{
    int check = 0;
    m_game->m_stickmanAdapter->setMaxJumps(95);
    if (m_game->m_stickmanAdapter->m_maxJumpCount == 95) check++;
    m_game->m_stickmanAdapter->setMaxJumps(47);
    if (m_game->m_stickmanAdapter->m_maxJumpCount == 47) check++;
    m_game->m_stickmanAdapter->setMaxJumps(1);
    if (m_game->m_stickmanAdapter->m_maxJumpCount == 1) check++;
    return check == 3;
}

bool Tests::setGravityTest()
{

}

bool Tests::setJumpForceTest()
{

}

bool Tests::resetPositionTest()
{

}

bool Tests::moveRightTest()
{

}

bool Tests::moveLeftTest()
{

}

bool Tests::stopTest()
{

}

bool Tests::getJumpForceTest()
{

}

void Tests::runAllTests()
{
	int testsFailed = 0;

    /* Game Tests */
	if (!pauseStateTest())
	{
		cout << "pause state test failed" << endl;
		testsFailed++;
	}
	if (!pauseEnableTest())
	{
		cout << "pause enable test failed" << endl;
		testsFailed++;
	}
	if(!winState())
	{
		cout << "win state test failed" << endl;
		testsFailed++;
	}
	if(!loseState())
	{
		cout << "lose state test failed" << endl;
		testsFailed++;
	}
	if (!stage3State())
	{
		cout << "stage 3 state test failed" << endl;
		testsFailed++;
	}
	if (!jumpEnableTest())
	{
		cout << "jump enable test failed" << endl;
		testsFailed++;
	}
	if (!moveLeftStateTest())
	{
		cout << "move left state test failed" << endl;
		testsFailed++;
	}
	if (!moveRightStateTest())
	{
		cout << "move right state test failed" << endl;
		testsFailed++;
	}
	if (!moveNoStateTest())
	{
		cout << "not moving state test failed" << endl;
		testsFailed++;
	}
	if (!switchPauseStateTest())
	{
		cout << "switch pause state test failed" << endl;
		testsFailed++;
	}

    /* Stickman/Adapter tests */

	if (testsFailed == 0)
	{
		cout << "All tests passed!" << endl;
	}
}
