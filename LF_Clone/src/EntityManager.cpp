#include "EntityManager.h"
#include "Actor.h"


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
void EntityManager::AddObject( GameObject* obj, bool registerForUpdate )
{
	m_objects.emplace( obj->GetID(), std::make_pair( obj, registerForUpdate ) );
}


//=======================================================================================================
void EntityManager::RemoveObject( const std::string& id )
{
	m_objects.erase( id );
}


//=======================================================================================================
GameObject* EntityManager::GetObject( const std::string& id )
{
	return m_objects[id].first;
}


//=======================================================================================================
void EntityManager::RegisterForUpdate( const std::string& id )
{
	m_objects[id].second = true;
}


//=======================================================================================================
void EntityManager::UnregisterForUpdate( const std::string& id )
{
	m_objects[id].second = false;
}


//=======================================================================================================
void EntityManager::UpdateEntities( float dt )
{
	for ( auto it = m_objects.begin(); it != m_objects.end(); ++it )
	{
		if ( it->second.second )	// Object is Updatable
		{
			Actor* actor = static_cast<Actor*>( it->second.first );
			actor->OnUpdate( dt );
		}
	}
}
