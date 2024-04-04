#pragma once

#include <string>
#include <unordered_map>

class Actor;

class ActorFactory
{
private:
	typedef Actor* ( *CreateObjectCallback )( std::string );

public:


	static ActorFactory* CreateFactoryInstance();

	void RegisterObject( const std::string& type, CreateObjectCallback );
	void UnregisterObject( const std::string& type );

	Actor* CreateObject( const std::string& type, std::string id );


private:
	typedef std::unordered_map<std::string, CreateObjectCallback> CallbackMap;
	CallbackMap m_Callbacks;
};

