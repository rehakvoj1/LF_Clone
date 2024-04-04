#pragma once

#include <string>

class GameObject
{
public:
	GameObject( std::string id ) : m_ID( id )
	{
	}

protected:
	std::string m_ID;	// bad choice -> better some GUID number
};