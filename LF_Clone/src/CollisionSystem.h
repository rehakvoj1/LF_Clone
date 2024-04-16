#pragma once

#include "I_Publisher.h"
#include "GameObject.h"

#include <map>

class CollisionSystem : public I_Publisher
{
public:
	enum CollisionFilter
	{
		None =       0,
		Projectile = 1,
		MapTile =    2,
		Character =  4
	};


public:
	static CollisionSystem* Create();

	void RegisterCollider( GameObject* obj, CollisionFilter collider, CollisionFilter collidesWith);
	void UnregisterCollider( GameObject* collider );
	void OnUpdate();

protected:
	std::map<GameObject*, std::pair<CollisionFilter, CollisionFilter> > m_colliders;

private:
};

