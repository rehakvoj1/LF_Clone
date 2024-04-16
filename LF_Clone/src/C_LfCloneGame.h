#pragma once
#include "I_Game.h"
#include "StateMachine.h"

#include "GameStates.h"
#include "Event.h"

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
	virtual void OnUpdate( float dt ) override;
	
private:
	void OnKeyPressed( KeyPressedEvent& e );
	void OnWindowClosed( WindowClosedEvent& e );

private:
	StateMachine<GameStateInit, GameState> m_gameState;
};