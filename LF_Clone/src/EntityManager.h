#pragma once

#include <unordered_map>
#include <string>

#include "GameObject.h"


class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	static EntityManager*	Create();

	void					AddObject( GameObject* obj, bool registerForUpdate = false );
	void					RemoveObject( const std::string& id );
	GameObject*				GetObject( const std::string& id );
	void					RegisterForUpdate( const std::string& id );
	void					UnregisterForUpdate( const std::string& id );
	void					UpdateEntities( float dt );


protected:

private:
	std::unordered_map<std::string, std::pair<GameObject*, bool> > m_objects;

};

