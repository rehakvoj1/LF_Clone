#include "imgui.h"
#include "imgui-SFML.h"

//#include <SFML/Graphics/CircleShape.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>


#include <string>
#include <iostream>
#include <list>

#include "gameplay/Player.h"
#include "gameplay/Enemy.h"
#include "C_Engine.h"
#include "I_WindowsManager.h"
#include "Window.h"

//=======================================================================================================
void CheckCollisions( Projectile& source, 
                      Player& target )
{
    ImVec2 projPos = source.GetCurrentSprite().getPosition();
    ImVec2 charPos = target.GetCurrentSprite().getPosition();
    if ( source.GetDirection() == 1 && source.IsCasted() )
    {
        if ( ( projPos.x + 80 ) - ( charPos.x + 25 ) >= 0 && ( projPos.x + 80 ) < ( charPos.x + 80 ) &&
             (projPos.y + 40) >= (charPos.y + 30) && ( ( projPos.y + 40 ) <  charPos.y + 60 ) )
        {
            source.SetCollision( true );
            target.TakeDamage( 20 );
        }
    }
    if ( source.GetDirection() == -1 && source.IsCasted() )
    {
        if ( ( projPos.x ) - ( charPos.x + 80 ) <= 0 && ( projPos.x ) > ( charPos.x ) &&
             ( projPos.y + 40 ) >= ( charPos.y + 30 ) && ( ( projPos.y + 40 ) < charPos.y + 60 ) )
        {
            source.SetCollision( true );
            target.TakeDamage( 20 );
        }
    }
}

//=======================================================================================================
/* overloaded function is stupid -> better usage of inheritance and polymorphism or even some better design patterns */
void CheckCollisions( Projectile& source,
                      Enemy& target )
{
    ImVec2 projPos = source.GetCurrentSprite().getPosition();
    ImVec2 charPos = target.GetCurrentSprite().getPosition();
    if ( source.GetDirection() == 1 && source.IsCasted() )
    {
        if ( ( projPos.x + 80 ) - ( charPos.x + 25 ) >= 0 && ( projPos.x + 80 ) < ( charPos.x + 80 ) &&
             ( projPos.y + 40 ) >= ( charPos.y + 30 ) && ( ( projPos.y + 40 ) < charPos.y + 60 ) )
        {
            source.SetCollision( true );
            target.TakeDamage( 20 );
        }
    }
    if ( source.GetDirection() == -1 && source.IsCasted() )
    {
        if ( ( projPos.x ) - ( charPos.x + 80 ) <= 0 && ( projPos.x ) > ( charPos.x ) &&
             ( projPos.y + 40 ) >= ( charPos.y + 30 ) && ( ( projPos.y + 40 ) < charPos.y + 60 ) )
        {
            source.SetCollision( true );
            target.TakeDamage( 20 );
        }
    }
}

//=======================================================================================================
// ***************************************** MAIN FUNCTION **********************************************
//=======================================================================================================
int main(int argc, char** argv)
{
    // init framework
    C_Engine engine;
    if ( !engine.Init( EngineInitParams() ) )
    {
        return -1;
    }
    engine.Run();

    

    // init resource ========== DONE
    sf::Texture sorcererTex;
    if ( !sorcererTex.loadFromFile( "./resource/sorcerer_0b.png" ) )
    {
        std::cout << "Failed to load sorcerer_0b texture." << std::endl;
    }
    sf::Texture sorcererTexMirror;
    if ( !sorcererTexMirror.loadFromFile( "./resource/sorcerer_0b_mirror.png" ) )
    {
        std::cout << "Failed to load sorcerer_0b_mirror texture." << std::endl;
    }
    sf::Texture frostboltTex;
    if ( !frostboltTex.loadFromFile( "./resource/freeze_ball.png" ) )
    {
        std::cout << "Failed to load freeze_ball texture." << std::endl;
    }
    sf::Texture frostboltTexMirror;
    if ( !frostboltTexMirror.loadFromFile( "./resource/freeze_ball_mirror.png" ) )
    {
        std::cout << "Failed to load freeze_ball_mirror texture." << std::endl;
    }
    sf::Texture enemyTex;
    if ( !enemyTex.loadFromFile( "./resource/firen_0.png" ) )
    {
        std::cout << "Failed to load firen_0 texture." << std::endl;
    }
    sf::Texture fireballTex;
    if ( !fireballTex.loadFromFile( "./resource/firen_ball.png" ) )
    {
        std::cout << "Failed to load firen_ball texture." << std::endl;
    }
    //-----------------------DONE--------------------------------------------




    // init game objects

    // player
    sf::Sprite spriteSorcerer( sorcererTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    sf::Sprite spriteSorcererMirror( sorcererTexMirror, sf::IntRect( { 720,0 }, { 80,80 } ) );
    Player player{ spriteSorcerer, spriteSorcererMirror };
    
    // player's projectile
    sf::Sprite spriteFrostbolt( frostboltTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    sf::Sprite spriteFrostboltMirror( frostboltTexMirror, sf::IntRect( { 247,0 }, { 80,80 } ) );
    player.SetProjectile( SpriteOrientation::Default, spriteFrostbolt, 400.0f, 2.0f, 0.0f );        
    player.SetProjectile( SpriteOrientation::Mirror, spriteFrostboltMirror, 400.0f, 2.0f, 0.0f );   // Bad design = redundant information, it doesn't make sense
    
    // enemy
    sf::Sprite spriteEnemy( enemyTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    Enemy enemy{ spriteEnemy };
    

    // enemy's projectile
    sf::Sprite spriteFireball( fireballTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    enemy.SetProjectile( SpriteOrientation::Default, spriteFireball, 800.f, 1.f, 1.f );


    sf::RenderWindow* window = (sf::RenderWindow*)C_Engine::GetWindowsManager()->GetActiveWindow()->GetNativeWindow();
    float dt = 0;
    sf::Time elapsed;
    // game loop
//    sf::Clock deltaClock;
//    while ( window->isOpen() )
//    {
//        sf::Time elapsed = deltaClock.restart();
//        float dt = elapsed.asSeconds();
//        // event polling
//        sf::Event event;
//        while ( window->pollEvent( event ) )
//        {
//            ImGui::SFML::ProcessEvent( *window, event );
//
//            if ( event.type == sf::Event::Closed ||
//                 sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ) )
//            {
//                window->close();
//            }
//        }
        
        // Update
        window->setTitle( "Framerate: " + std::to_string(1000.0f / elapsed.asMilliseconds()));
        ImGui::SFML::Update( *window, elapsed );
        if ( window->hasFocus() )
        {
            enemy.OnUpdate( dt );   // projectile is updated inside ---> Not good
            CheckCollisions( enemy.GetProjectile(), player);
            player.OnUpdate( dt );  // projectile is updated inside ---> Not good
            CheckCollisions( player.GetProjectile(), enemy);
        }
        

        // render
        window->clear( sf::Color::Cyan );
        player.OnRender( *window );  // projectile is rendered inside ---> Not good
        enemy.OnRender( *window );   // projectile is rendered inside ---> Not good
        
        ImGui::Begin( "healthbar",0,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs );
        ImGui::DrawRectFilled( sf::FloatRect( { 80,0 }, { 100,20 } ), sf::Color::Black );
        ImGui::DrawRectFilled( sf::FloatRect( { 80,0 }, { player.GetHealth(),20}), sf::Color::Red);
        ImGui::End();
        ImGui::SFML::Render( *window );  // -----> renders ImGui elements
        window->display();   // -----------------> display rendered elements to window 
}

    // cleanup