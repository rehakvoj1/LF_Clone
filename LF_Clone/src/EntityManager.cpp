#include "EntityManager.h"
#include "Actor.h"
#include "C_Engine.h"
#include "ActorFactory.h"


//=======================================================================================================
EntityManager::EntityManager()
{
}


//=======================================================================================================
EntityManager::~EntityManager()
{
	for ( auto& elem : m_objects )
	{
		delete elem.second.first;
	}
}


//=======================================================================================================
EntityManager* EntityManager::Create()
{
	return new EntityManager;
}


//=======================================================================================================
Actor* EntityManager::AddObject( std::string objType, std::string objID, bool registerForUpdate )
{
	Actor* obj = C_Engine::GetActorFactory()->CreateObject( objType, objID );
	obj->OnCreate();


	EntityFlags updateFlag = static_cast<EntityFlags>( registerForUpdate );
	auto [it, exist] = m_objects.emplace( obj->GetID(), std::make_pair( obj, updateFlag ) );
	return static_cast<Actor*>( it->second.first );
}


//=======================================================================================================
void EntityManager::RemoveObject( const std::string& id )
{
	m_objects[id].second = static_cast<EntityFlags>( m_objects[id].second | EntityFlags::DELETE);
}


//=======================================================================================================
GameObject* EntityManager::GetObject( const std::string& id )
{
	return m_objects[id].first;
}


//=======================================================================================================
void EntityManager::RegisterForUpdate( const std::string& id )
{
	m_objects[id].second = static_cast<EntityFlags>( m_objects[id].second | EntityFlags::UPDATE );
}


//=======================================================================================================
void EntityManager::UnregisterForUpdate( const std::string& id )
{
	m_objects[id].second = static_cast<EntityFlags>( m_objects[id].second & ~EntityFlags::UPDATE );
}


//=======================================================================================================
void EntityManager::UpdateEntities( float dt )
{
	


	for ( auto it = m_objects.begin(); it != m_objects.end(); ++it )
	{
		if ( it->second.second & EntityFlags::UPDATE )	// Object is Updatable
		{
			Actor* actor = static_cast<Actor*>( it->second.first );
			actor->OnUpdate( dt );
		}
	}
}

void EntityManager::DeleteZombies()
{
	for ( auto it = m_objects.cbegin(); it != m_objects.cend(); )
	{
		if ( it->second.second & EntityFlags::DELETE )
		{
			delete it->second.first;
			m_objects.erase( it++ );
		}
		else
		{
			++it;
		}
	}
}
