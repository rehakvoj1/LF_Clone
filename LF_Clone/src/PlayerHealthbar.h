#pragma once
#include "Healthbar.h"
#include "Actor.h"

class PlayerHealthbar : public Healthbar
{
public:
	PlayerHealthbar( std::string id, ImVec2 topLeft, ImVec2 size ); 
	virtual ~PlayerHealthbar();

	virtual void OnCreate() override;

	void OnPlayerHit( HitEvent& e );

	static Actor* Create( std::string id );

private:
};

