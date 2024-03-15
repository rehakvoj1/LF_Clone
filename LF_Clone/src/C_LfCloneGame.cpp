#include "C_LfCloneGame.h"

#include <typeinfo>
#include <iostream>

//===================================================================================================
I_Game* CreateGame()
{
	return new C_LfCloneGame();
}

C_LfCloneGame::C_LfCloneGame() : m_gameState( GameState::Init )
{
}

//===================================================================================================
void C_LfCloneGame::OnStart()
{
	
}

//===================================================================================================
void C_LfCloneGame::OnBeforeUpdate( float dt )
{

}

//===================================================================================================
void C_LfCloneGame::OnUpdate( float dt )
{
	m_gameState.OnUpdate();
}

//===================================================================================================
void C_LfCloneGame::OnPostUpdate( float dt )
{

}
