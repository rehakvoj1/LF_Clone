#pragma once
#include "StateMachine.h"

class GameStateInit : public State
{
};

class GameStateMainMenu : public State
{
};

class GameStateRunning : public State
{
};

class GameStatePaused : public State
{
};

class GameStateShouldClose : public State
{
};

