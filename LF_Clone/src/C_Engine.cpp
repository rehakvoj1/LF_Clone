#include "C_Engine.h"
#include "I_Game.h"
#include "C_WindowsWindowsManager.h"
#include "I_SystemEventHandler.h"
#include "TextureManager.h"
#include "ActorFactory.h"

#include "imgui-SFML.h"

#include <iostream>


//==================================== STATIC VARIABLES =============================================
I_SystemEventHandler* C_Engine::m_sysEventHandler = nullptr;
I_WindowsManager* C_Engine::m_windowsManager = nullptr;
TextureManager* C_Engine::m_textureManager = nullptr;
ActorFactory* C_Engine::m_actorFactory = nullptr;

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
I_WindowsManager* C_Engine::GetWindowsManager()
{
    return m_windowsManager;
}

I_SystemEventHandler* C_Engine::GetSystemEventHandler()
{
    return m_sysEventHandler;
}

TextureManager* C_Engine::GetTextureManager()
{
    return m_textureManager;
}

ActorFactory* C_Engine::GetActorFactory()
{
    return m_actorFactory;
}

float C_Engine::GetDeltaTime()
{
    return m_deltaTime;
}

//===================================================================================================
bool C_Engine::Init( EngineInitParams params )
{
    m_windowsManager = I_WindowsManager::Create();
    if ( !m_windowsManager )
    {
        return false;
    }

    m_sysEventHandler = I_SystemEventHandler::Create();
    if ( !m_sysEventHandler )
    {
        return false;
    }

    m_textureManager = TextureManager::Create();
    if ( !m_textureManager )
    {
        return false;
    }

    m_actorFactory = ActorFactory::CreateFactoryInstance();
    if ( !m_actorFactory )
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
        m_deltaTime = m_updateClock.restart().asSeconds();
        m_sysEventHandler->PollEvents();
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
    Window* wnd = GetWindowsManager()->GetActiveWindow();
    wnd->ClearColor( 30, 30, 30 );
    wnd->Display();
}
