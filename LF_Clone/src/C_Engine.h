#pragma once

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>



// Constants
const unsigned int DEFAULT_WINDOW_WIDTH = 1280;
const unsigned int DEFAULT_WINDOW_HEIGHT = 960;
const std::string DEFAULT_WINDOW_NAME = "LF_CLONE";


// params for engine initialization
struct EngineInitParams
{
	unsigned int windowWidth = DEFAULT_WINDOW_WIDTH;
	unsigned int windowHeight = DEFAULT_WINDOW_HEIGHT;
	std::string windowName = DEFAULT_WINDOW_NAME;
};


class I_Game;
class I_WindowsManager;
class I_SystemEventHandler;
class TextureManager;
class ActorFactory;
class CollisionSystem;
class EntityManager;


class C_Engine
{
public:
	 C_Engine();
	~C_Engine();

	
	static I_WindowsManager*		GetWindowsManager();
	static I_SystemEventHandler*	GetSystemEventHandler();
	static TextureManager*			GetTextureManager();
	static ActorFactory*			GetActorFactory();
	static CollisionSystem*			GetCollisionSystem();
	static EntityManager*			GetEntityManager();
	static float					GetDeltaTime();
	
	
	bool Init( EngineInitParams params );
	void Run();
	bool CreateGameInstance();


private:

	void PreUpdate();
	void Update();
	void PostUpdate();
	void Render();
	bool InitStaticVariables();


	
	I_Game* m_gameInstance;
	static I_WindowsManager* m_windowsManager;
	static I_SystemEventHandler* m_sysEventHandler;
	static TextureManager* m_textureManager;
	static ActorFactory* m_actorFactory;
	static CollisionSystem* m_collisionSystem;
	static EntityManager* m_entityManager;

	sf::Clock m_updateClock;
	static float m_deltaTime;
};

