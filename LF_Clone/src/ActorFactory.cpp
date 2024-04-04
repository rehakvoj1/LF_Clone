#include "ActorFactory.h"


// =================================================================================
ActorFactory* ActorFactory::CreateFactoryInstance()
{
	return new ActorFactory;
}


// =================================================================================
void ActorFactory::RegisterObject( const std::string& type, CreateObjectCallback cb )
{
	m_Callbacks[type] = cb;
}


// =================================================================================
void ActorFactory::UnregisterObject( const std::string& type )
{
	m_Callbacks.erase( type );
}


// =================================================================================
Actor* ActorFactory::CreateObject( const std::string& type, std::string id )
{
	auto it = m_Callbacks.find( type );
	if ( it != m_Callbacks.end() )
	{
		return ( it->second )( id );
	}
	return nullptr;
}
