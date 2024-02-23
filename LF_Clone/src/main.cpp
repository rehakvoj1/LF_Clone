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

//=======================================================================================================
void UpdateSorcerer( sf::Sprite& spriteToRender,
                     sf::Sprite& spriteSorcerer,
                     sf::Sprite& spriteSorcererMirror,
                     float sorcererSpeed,
                     int& sorcererDir,
                     float dt )
{
    
    ImVec2 sorcererPos = spriteSorcerer.getPosition();
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ||
         sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
    {
        spriteSorcerer.setPosition( sorcererPos.x, sorcererPos.y -= sorcererSpeed * dt );
        spriteSorcererMirror.setPosition( sorcererPos.x, sorcererPos.y -= sorcererSpeed * dt );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ||
         sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
    {
        spriteSorcerer.setPosition( sorcererPos.x, sorcererPos.y += sorcererSpeed * dt );
        spriteSorcererMirror.setPosition( sorcererPos.x, sorcererPos.y += sorcererSpeed * dt );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ||
         sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
    {
        sorcererDir = -1;
        spriteSorcerer.setPosition( sorcererPos.x += sorcererSpeed * dt * sorcererDir, sorcererPos.y );
        spriteSorcererMirror.setPosition( sorcererPos.x += sorcererSpeed * dt * sorcererDir, sorcererPos.y );
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ||
         sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
    {
        sorcererDir = 1;
        spriteSorcerer.setPosition( sorcererPos.x += sorcererSpeed * dt * sorcererDir, sorcererPos.y );
        spriteSorcererMirror.setPosition( sorcererPos.x += sorcererSpeed * dt * sorcererDir, sorcererPos.y );
    }


    if ( sorcererDir == 1 )
    {
        spriteToRender = spriteSorcerer;
    }
    else
    {
        spriteToRender = spriteSorcererMirror;
    }
}

//=======================================================================================================
void UpdateEnemy( sf::Sprite& spriteToRender,
                  sf::Sprite& spriteEnemy )
{
    spriteToRender = spriteEnemy;
}

//=======================================================================================================
void UpdateFireball( sf::Sprite& fireballToRender, 
                     sf::Sprite& spriteFireball, 
                     sf::Sprite& spriteEnemy,
                     int& enemyDir,
                     int& fireballCastedWithDir, 
                     float fireballSpeed,
                     float fireballDuration, 
                     sf::Clock& fireballElapsed,
                     sf::Clock& fireballCooldownTimer,
                     float dt,
                     float shootCooldown)
{
    if ( fireballCastedWithDir )
    {
        if ( fireballElapsed.getElapsedTime().asSeconds() < fireballDuration )
        {
            ImVec2 fireballPos = fireballToRender.getPosition();
            fireballToRender.setPosition( fireballPos.x += fireballSpeed * dt * fireballCastedWithDir, fireballPos.y );
        }
        else
        {
            fireballCastedWithDir = 0;
            fireballCooldownTimer.restart();
            fireballToRender.setColor( sf::Color::Transparent );
        }
    }
    else
    {
        if ( fireballCooldownTimer.getElapsedTime().asSeconds() > shootCooldown )
        {
            if ( enemyDir == 1 )
            {
                fireballToRender = spriteFireball;
            }
            
            fireballToRender.setPosition( spriteEnemy.getPosition().x + 25 * enemyDir, spriteEnemy.getPosition().y - 6 );
            fireballCastedWithDir = enemyDir;
            fireballElapsed.restart();
        }
    }

}

//=======================================================================================================
void UpdateFrostbolt( sf::Sprite& frostboltToRender, 
                      sf::Sprite& spriteSorcerer, 
                      sf::Sprite& spriteFrostbolt, 
                      sf::Sprite& spriteFrostboltMirror, 
                      float frostboltSpeed,
                      int& sorcererDir,
                      float dt, 
                      int& spellCasted,
                      float frostboltDuration,
                      sf::Clock& frostboltElapsed)
{
    if ( spellCasted )
    {
        if ( frostboltElapsed.getElapsedTime().asSeconds() < frostboltDuration )
        {
            ImVec2 frostboltPos = frostboltToRender.getPosition();
            frostboltToRender.setPosition( frostboltPos.x += frostboltSpeed * dt * spellCasted, frostboltPos.y );

        }
        else
        {
            spellCasted = 0;
            frostboltToRender.setColor( sf::Color::Transparent );
        }
    }
    else
    {
        if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
        {
            if ( sorcererDir == 1 )
            {
                frostboltToRender = spriteFrostbolt;
            }
            else
            {
                frostboltToRender = spriteFrostboltMirror;
            }
            frostboltToRender.setPosition( spriteSorcerer.getPosition().x + 25 * sorcererDir, spriteSorcerer.getPosition().y - 6 );
            spellCasted = sorcererDir;
            frostboltElapsed.restart();
        }
    }


}

//=======================================================================================================
void UpdatePlayerHealth( sf::Clock& healthTimer, float& playerHealth, float healthTick )
{
    if ( healthTimer.getElapsedTime().asSeconds() > healthTick )
    {
        playerHealth -= 1.f;
        if ( playerHealth < 0.0f )
        {
            playerHealth = 100.f;
        }
        healthTimer.restart();
    }
}


int main()
{
    // init framework
    sf::RenderWindow window( sf::VideoMode( 1280, 960 ), "ImGui + SFML = <3" );
    //window.setFramerateLimit( 60 );
    ImGui::SFML::Init( window );

    // init resource
    sf::Texture sorcererTex;
    if ( !sorcererTex.loadFromFile( "./resource/sorcerer_0b.png" ) )
    {
        std::cout << "Failed to load texture." << std::endl;
    }
    sf::Texture sorcererTexMirror;
    if ( !sorcererTexMirror.loadFromFile( "./resource/sorcerer_0b_mirror.png" ) )
    {
        std::cout << "Failed to load texture." << std::endl;
    }
    sf::Texture frostboltTex;
    if ( !frostboltTex.loadFromFile( "./resource/freeze_ball.png" ) )
    {
        std::cout << "Failed to load texture." << std::endl;
    }
    sf::Texture frostboltTexMirror;
    if ( !frostboltTexMirror.loadFromFile( "./resource/freeze_ball_mirror.png" ) )
    {
        std::cout << "Failed to load texture." << std::endl;
    }
    sf::Texture enemyTex;
    if ( !enemyTex.loadFromFile( "./resource/firen_0.png" ) )
    {
        std::cout << "Failed to load texture." << std::endl;
    }
    sf::Texture fireballTex;
    if ( !fireballTex.loadFromFile( "./resource/firen_ball.png" ) )
    {
        std::cout << "Failed to load texture." << std::endl;
    }
    




    // init game objects

    // player
    sf::Sprite spriteSorcerer( sorcererTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    sf::Sprite spriteSorcererMirror( sorcererTexMirror, sf::IntRect( { 720,0 }, { 80,80 } ) );
    sf::Sprite sorcererToRender;
    ImVec2 sorcererPos = spriteSorcerer.getPosition();
    float sorcererSpeed = 200.f;
    int sorcererDir = 1;
    float playerHealth = 100.f;
    sf::Clock healthTimer;
    float healthTick = .1f; // seconds
    
    // player's projectile
    sf::Sprite spriteFrostbolt( frostboltTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    sf::Sprite spriteFrostboltMirror( frostboltTexMirror, sf::IntRect( { 247,0 }, { 80,80 } ) );
    sf::Sprite frostboltToRender;
    float frostboltSpeed = 400.f;
    int frostboltCastedWithDir = 0;
    const float frostboltDuration = 2.0f;
    sf::Clock frostboltElapsed;

    // enemy
    sf::Sprite spriteEnemy( enemyTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    sf::Sprite enemyToRender;
    spriteEnemy.setPosition( 80.f, 80.f );
    int enemyDir = 1;

    // enemy's projectile
    sf::Sprite spriteFireball( fireballTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    sf::Sprite fireballToRender;
    float fireballSpeed = 800.f;
    int fireballCastedWithDir = 0;
    const float fireballDuration = 2.0f;
    sf::Clock fireballElapsed;
    sf::Clock fireballCooldownTimer;
    const float shootCooldown = 1.0f;


    // game loop
    sf::Clock deltaClock;
    while ( window.isOpen() )
    {
        float dt = deltaClock.getElapsedTime().asSeconds();
        // event polling
        sf::Event event;
        while ( window.pollEvent( event ) )
        {
            ImGui::SFML::ProcessEvent( window, event );

            if ( event.type == sf::Event::Closed ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ) )
            {
                window.close();
            }
        }
        
        // Update
        window.setTitle( "Framerate: " + std::to_string(1000.0f / deltaClock.getElapsedTime().asMilliseconds()));
        ImGui::SFML::Update( window, deltaClock.restart() );
        if ( window.hasFocus() )
        {
            UpdateSorcerer( sorcererToRender, spriteSorcerer, spriteSorcererMirror, sorcererSpeed, sorcererDir, dt );
            UpdateFrostbolt( frostboltToRender, spriteSorcerer, spriteFrostbolt, spriteFrostboltMirror, frostboltSpeed, sorcererDir, dt, frostboltCastedWithDir, frostboltDuration, frostboltElapsed );
            UpdateEnemy( enemyToRender, spriteEnemy );
            UpdateFireball( fireballToRender, spriteFireball, spriteEnemy, enemyDir, fireballCastedWithDir, fireballSpeed, fireballDuration, fireballElapsed, fireballCooldownTimer, dt, shootCooldown );
            UpdatePlayerHealth( healthTimer, playerHealth, healthTick );
            
        }
        

        // render
        window.clear(sf::Color::Cyan);
        window.draw( sorcererToRender );
        window.draw( frostboltToRender );
        window.draw( enemyToRender );
        window.draw( fireballToRender );

        ImGui::Begin( "healthbar",0,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs );
        ImGui::DrawRectFilled( sf::FloatRect( { 80,0 }, { 100,20 } ), sf::Color::Black );
        ImGui::DrawRectFilled( sf::FloatRect( { 80,0 }, { playerHealth,20 } ), sf::Color::Red );
        ImGui::End();
        ImGui::SFML::Render( window );  // -----> renders ImGui elements
        window.display();   // -----------------> display rendered elements to window 
    }

    // cleanup
    ImGui::SFML::Shutdown();
}