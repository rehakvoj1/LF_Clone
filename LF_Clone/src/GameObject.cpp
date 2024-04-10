#include "GameObject.h"

GameObject::GameObject( std::string id ) : m_ID( id )
{
}

std::string& GameObject::GetID()
{
	return m_ID;
}