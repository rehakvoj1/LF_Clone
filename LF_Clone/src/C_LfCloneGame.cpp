#include "C_LfCloneGame.h"
#include "C_Engine.h"
#include "I_WindowsManager.h"
#include "I_Publisher.h"
#include "I_SystemEventHandler.h"
#include "TextureManager.h"
#include "GameResources.h"
#include "ActorFactory.h"
#include "Player.h"
#include "Enemy.h"
#include "FrostboltProjectile.h"
#include "FireballProjectile.h"

#include <typeinfo>
#include <iostream>

//===================================================================================================
I_Game* CreateGame()
{
	return new C_LfCloneGame();
}

//===================================================================================================
C_LfCloneGame::C_LfCloneGame() : m_gameState( GameState::Init )
{
}

//===================================================================================================
void C_LfCloneGame::OnStart()
{
	Observe<KeyPressedEvent>( C_Engine::GetSystemEventHandler(), &C_LfCloneGame::OnKeyPressed);
	Observe<WindowClosedEvent>( C_Engine::GetSystemEventHandler(), &C_LfCloneGame::OnWindowClosed);

	C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::ENEMY ) );
	C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FIREBALL ) );
	C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FROSTBOLT ) );
	C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FROSTBOLT_MIRROR ) );
	C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::SORCERER ) );
	C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::SORCERER_MIRROR ) );

	C_Engine::GetActorFactory()->RegisterObject( "player", Player::Create );
	C_Engine::GetActorFactory()->RegisterObject( "enemy", Enemy::Create );
	C_Engine::GetActorFactory()->RegisterObject( "frostboltLeft", FrostboltProjectile::CreateLeft );
	C_Engine::GetActorFactory()->RegisterObject( "frostboltRight", FrostboltProjectile::CreateRight );
	C_Engine::GetActorFactory()->RegisterObject( "fireballRight", FireballProjectile::CreateRight );

}

//===================================================================================================
void C_LfCloneGame::OnUpdate( float dt )
{
	m_gameState.OnUpdate();
}


//===================================================================================================
void C_LfCloneGame::OnKeyPressed( KeyPressedEvent& e )
{
	switch ( e.GetKey() )
	{
		case sf::Keyboard::Escape:
			C_Engine::GetWindowsManager()->GetActiveWindow()->Close();
			break;
	}
}

//===================================================================================================
void C_LfCloneGame::OnWindowClosed( WindowClosedEvent& e )
{
	C_Engine::GetWindowsManager()->GetActiveWindow()->Close();
}
