#pragma once

#include <unordered_map>
#include <string>

#include "GameObject.h"


class Actor;

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	static EntityManager*	Create();

	Actor*					AddObject( std::string objType, std::string objID, bool registerForUpdate = false );
	void					RemoveObject( const std::string& id );
	GameObject*				GetObject( const std::string& id );
	void					RegisterForUpdate( const std::string& id );
	void					UnregisterForUpdate( const std::string& id );
	void					UpdateEntities( float dt );
	void					DeleteZombies();

protected:

private:

	enum EntityFlags
	{
		NONE	= 0,
		UPDATE	= 1,
		DELETE	= 2
	};


	std::unordered_map<std::string, std::pair<GameObject*, EntityFlags> > m_objects;

};

