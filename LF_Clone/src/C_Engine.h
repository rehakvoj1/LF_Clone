#pragma once

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>


// Constants
const int DEFAULT_WINDOW_WIDTH = 1280;
const int DEFAULT_WINDOW_HEIGHT = 960;
const std::string DEFAULT_WINDOW_NAME = "LF_CLONE";


// params for engine initialization
struct EngineInitParams
{
	int windowWidth = DEFAULT_WINDOW_WIDTH;
	int windowHeight = DEFAULT_WINDOW_HEIGHT;
	std::string windowName = DEFAULT_WINDOW_NAME;
};


class I_Game;


class C_Engine
{
public:
	 C_Engine();
	~C_Engine();

	
	static sf::RenderWindow& GetWindow();
	static float GetDeltaTime();
	
	
	bool Init( EngineInitParams params );
	void Run();
	bool CreateGameInstance();


private:

	void Update();
	void Render();


	static sf::RenderWindow m_window;
	I_Game* m_gameInstance;
	sf::Clock m_updateClock;
	static float m_deltaTime;
};

