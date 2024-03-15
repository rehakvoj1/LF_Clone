#include "C_Engine.h"
#include "I_Game.h"

#include "imgui-SFML.h"

#include <iostream>


//==================================== STATIC VARIABLES =============================================
sf::RenderWindow C_Engine::m_window;
float C_Engine::m_deltaTime = 0.0f;


//===================================================================================================
C_Engine::C_Engine() : 
    m_gameInstance( nullptr )
{
}

//===================================================================================================
C_Engine::~C_Engine()
{
    delete m_gameInstance;
    ImGui::SFML::Shutdown();
}

//===================================================================================================
sf::RenderWindow& C_Engine::GetWindow()
{
    return m_window;
}

float C_Engine::GetDeltaTime()
{
    return m_deltaTime;
}

//===================================================================================================
bool C_Engine::Init( EngineInitParams params )
{
    m_window.create( sf::VideoMode( params.windowWidth, params.windowHeight ), params.windowName );
    if ( !m_window.isOpen() )
    {
        std::cout << "Failed to create a window." << std::endl;
        return false;
    }

    if ( !ImGui::SFML::Init( m_window ) )
    {
        std::cout << "Failed to initialize ImGui::SFML." << std::endl;
        return false;
    }

    return true;
}

//===================================================================================================
void C_Engine::Run()
{
    if ( !CreateGameInstance() )
    {
        std::cout << "Failed to create instance of a game." << std::endl;
        return;
    }

    m_gameInstance->OnStart();


    while ( m_window.isOpen() )
    {
        m_deltaTime = m_updateClock.restart().asSeconds();
        Update();
        Render();
    }
}

//===================================================================================================
extern I_Game* CreateGame();
bool C_Engine::CreateGameInstance()
{
    m_gameInstance = CreateGame();
    return m_gameInstance;
}

//===================================================================================================
void C_Engine::Update()
{
    m_gameInstance->OnBeforeUpdate( m_deltaTime );
    m_gameInstance->OnUpdate( m_deltaTime );
    m_gameInstance->OnPostUpdate( m_deltaTime );
}

//===================================================================================================
void C_Engine::Render()
{
}
