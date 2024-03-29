#pragma once
#include "I_Game.h"
#include "StateMachine.h"

#include "GameStates.h"

enum class GameState
{
	Init,
	MainMenu,
	Running,
	Paused,
	ShouldClose
};


class C_LfCloneGame : public I_Game
{
public:

	C_LfCloneGame();
	virtual void OnStart() override;
	virtual void OnBeforeUpdate( float dt ) override;
	virtual void OnUpdate( float dt ) override;
	virtual void OnPostUpdate( float dt ) override;

private:
	StateMachine<GameStateInit, GameState> m_gameState;
};