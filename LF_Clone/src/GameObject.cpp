#include "GameObject.h"


//===================================================================================================
GameObject::GameObject( std::string id ) : m_ID( id )
{
}

GameObject::~GameObject()
{
}


//===================================================================================================
std::string& GameObject::GetID()
{
	return m_ID;
}
