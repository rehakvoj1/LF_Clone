#include "PlayerHealthbar.h"
#include "C_Engine.h"
#include "EntityManager.h"
#include "Actor.h"
#include "Event.h"
#include "Player.h"

PlayerHealthbar::PlayerHealthbar( std::string id, ImVec2 topLeft, ImVec2 size ) :
	Healthbar( id,topLeft,size )
{
}

PlayerHealthbar::~PlayerHealthbar()
{
}


void PlayerHealthbar::OnCreate()
{
	Observe<HitEvent>( dynamic_cast<I_Publisher*>( C_Engine::GetEntityManager()->GetObject( "player1" ) ), &PlayerHealthbar::OnPlayerHit );
}

void PlayerHealthbar::OnPlayerHit( HitEvent& e )
{
	Player& player = static_cast<Player&>( e.GetTarget() );
	m_health = player.m_health;
}

Actor* PlayerHealthbar::Create( std::string id )
{
	return new PlayerHealthbar( id,
						  { DEFAULT_WINDOW_WIDTH / 3, 10 },
						  { 100.0f, 20.0f }
	);
}