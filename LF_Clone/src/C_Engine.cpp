#include "C_Engine.h"
#include "I_Game.h"
#include "C_WindowsWindowsManager.h"
#include "I_SystemEventHandler.h"
#include "TextureManager.h"
#include "ActorFactory.h"
#include "CollisionSystem.h"
#include "EntityManager.h"
#include "Renderer2D.h"

#include "imgui-SFML.h"

#include <iostream>


//==================================== STATIC VARIABLES =============================================
I_SystemEventHandler* C_Engine::m_sysEventHandler = nullptr;
I_WindowsManager* C_Engine::m_windowsManager = nullptr;
TextureManager* C_Engine::m_textureManager = nullptr;
ActorFactory* C_Engine::m_actorFactory = nullptr;
CollisionSystem* C_Engine::m_collisionSystem = nullptr;
EntityManager* C_Engine::m_entityManager = nullptr;
Renderer2D* C_Engine::m_renderer = nullptr;

sf::Time C_Engine::m_time;


//===================================================================================================
C_Engine::C_Engine() : 
    m_gameInstance( nullptr ),
    m_deltaTime( 0.0f )
{
}

//===================================================================================================
C_Engine::~C_Engine()
{
    delete m_gameInstance;
    ImGui::SFML::Shutdown();
}

//===================================================================================================
I_WindowsManager* C_Engine::GetWindowsManager()
{
    return m_windowsManager;
}

//===================================================================================================
I_SystemEventHandler* C_Engine::GetSystemEventHandler()
{
    return m_sysEventHandler;
}

//===================================================================================================
TextureManager* C_Engine::GetTextureManager()
{
    return m_textureManager;
}

//===================================================================================================
ActorFactory* C_Engine::GetActorFactory()
{
    return m_actorFactory;
}

//===================================================================================================
CollisionSystem* C_Engine::GetCollisionSystem()
{
    return m_collisionSystem;
}

//===================================================================================================
EntityManager* C_Engine::GetEntityManager()
{
    return m_entityManager;
}

//===================================================================================================
Renderer2D* C_Engine::GetRenderer()
{
    return m_renderer;
}

//===================================================================================================
float C_Engine::GetDeltaTime()
{
    return m_time.asSeconds();
}

//===================================================================================================
bool C_Engine::Init( EngineInitParams params )
{
   
    if ( !InitStaticVariables() )
    {
        return false;
    }

    auto [window, initSuccessful] = m_windowsManager->AddWindow( params.windowWidth, params.windowHeight, params.windowName );
    if ( !initSuccessful )
    {
        return false;
    }

    m_windowsManager->SetActiveWindow( params.windowName );  

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


    while ( m_windowsManager->GetActiveWindow()->IsWindowOpen())
    {
        m_time = m_updateClock.restart();
        m_deltaTime = m_time.asSeconds();
        m_sysEventHandler->PollEvents();
        PreUpdate();
        Update();
        PostUpdate();
        Render();
        PostRender();
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
void C_Engine::PreUpdate()
{
}

//===================================================================================================
void C_Engine::Update()
{
    
    m_collisionSystem->OnUpdate();
    m_gameInstance->OnUpdate( m_deltaTime );
    m_entityManager->UpdateEntities( m_deltaTime );

#ifdef PLATFORM_WINDOWS
    sf::RenderWindow* winWnd = static_cast<sf::RenderWindow*>( GetWindowsManager()->GetActiveWindow()->GetNativeWindow() );
    ImGui::SFML::Update( *winWnd, m_time );
#endif
}


//===================================================================================================
void C_Engine::PostUpdate()
{
}

//===================================================================================================
void C_Engine::Render()
{
    Window* wnd = GetWindowsManager()->GetActiveWindow();
    wnd->ClearColor( 200, 200, 250 );

    GetRenderer()->OnRender();

    wnd->Display();
}


//===================================================================================================
void C_Engine::PostRender()
{
    GetRenderer()->OnPostRender();
    GetEntityManager()->DeleteZombies();
}


//===================================================================================================
bool C_Engine::InitStaticVariables()
{
    m_windowsManager = I_WindowsManager::Create();
    if ( !m_windowsManager )
    {
        std::cout << "Failed to init " << "WINDOWS MANAGER" << std::endl;
        return false;
    }

    m_sysEventHandler = I_SystemEventHandler::Create();
    if ( !m_sysEventHandler )
    {
        std::cout << "Failed to init " << "SYSTEM EVENT HANDLER" << std::endl;
        return false;
    }

    m_textureManager = TextureManager::Create();
    if ( !m_textureManager )
    {
        std::cout << "Failed to init " << "TEXTURE MANAGER" << std::endl;
        return false;
    }

    m_actorFactory = ActorFactory::CreateFactoryInstance();
    if ( !m_actorFactory )
    {
        std::cout << "Failed to init " << "ACTOR FACTORY" << std::endl;
        return false;
    }

    m_collisionSystem = CollisionSystem::Create();
    if ( !m_collisionSystem )
    {
        std::cout << "Failed to init " << "COLLISION SYSTEM" << std::endl;
        return false;
    }

    m_entityManager = EntityManager::Create();
    if ( !m_entityManager )
    {
        std::cout << "Failed to init " << "ENTITY MANAGER" << std::endl;
        return false;
    }

    m_renderer = Renderer2D::Create();
    if ( !m_renderer )
    {
        std::cout << "Failed to init " << "RENDERER" << std::endl;
        return false;
    }

    return true;
}
