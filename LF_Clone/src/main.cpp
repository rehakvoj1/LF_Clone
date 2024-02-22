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
        ImVec2 frostboltPos = frostboltToRender.getPosition();
        if ( frostboltElapsed.getElapsedTime().asSeconds() < frostboltDuration )
        {
            frostboltToRender.setPosition( frostboltPos.x += frostboltSpeed * dt * spellCasted, frostboltPos.y );

        }
        else
        {
            spellCasted = false;
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


int main()
{
    // init framework
    sf::RenderWindow window( sf::VideoMode( 1280, 960 ), "ImGui + SFML = <3" );
    window.setFramerateLimit( 60 );
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
    
    
    




    // init game objects

    sf::Sprite spriteSorcerer( sorcererTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    sf::Sprite spriteSorcererMirror( sorcererTexMirror, sf::IntRect( { 720,0 }, { 80,80 } ) );
    sf::Sprite sorcererToRender;
    ImVec2 sorcererPos = spriteSorcerer.getPosition();
    float sorcererSpeed = 200.f;
    int sorcererDir = 1;
    
    sf::Sprite spriteFrostbolt( frostboltTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    sf::Sprite spriteFrostboltMirror( frostboltTexMirror, sf::IntRect( { 247,0 }, { 80,80 } ) );
    sf::Sprite frostboltToRender;
    float frostboltSpeed = 150.f;
    int spellCastedWithDir = 0;
    const float frostboltDuration = 2.0f;
    sf::Clock frostboltElapsed;

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
                 event.key.scancode == sf::Keyboard::Scan::Escape )
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
            UpdateFrostbolt( frostboltToRender, spriteSorcerer, spriteFrostbolt, spriteFrostboltMirror, frostboltSpeed, sorcererDir, dt, spellCastedWithDir, frostboltDuration, frostboltElapsed );
        }
        

        // render
        window.clear(sf::Color::Cyan);
        window.draw( sorcererToRender );
        window.draw( frostboltToRender );
        ImGui::SFML::Render( window );  // -----> renders ImGui elements
        window.display();   // -----------------> display rendered elements to window 
    }

    // cleanup
    ImGui::SFML::Shutdown();
}