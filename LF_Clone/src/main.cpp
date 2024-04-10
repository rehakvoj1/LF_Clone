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


#include "C_Engine.h"
#include "I_WindowsManager.h"
#include "Window.h"


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

    // init game objects

    // player
    //sf::Sprite spriteSorcerer( sorcererTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
    //sf::Sprite spriteSorcererMirror( sorcererTexMirror, sf::IntRect( { 720,0 }, { 80,80 } ) );
    
    
    
    //// enemy
    //sf::Sprite spriteEnemy( enemyTex, sf::IntRect( { 0,0 }, { 80,80 } ) );
 


        // render
        //window->clear( sf::Color::Cyan );
        //player.OnRender( *window );  // projectile is rendered inside ---> Not good
        //enemy.OnRender( *window );   // projectile is rendered inside ---> Not good
        
        //ImGui::Begin( "healthbar",0,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs );
        //ImGui::DrawRectFilled( sf::FloatRect( { 80,0 }, { 100,20 } ), sf::Color::Black );
        ////ImGui::DrawRectFilled( sf::FloatRect( { 80,0 }, { player.GetHealth(),20}), sf::Color::Red);
        //ImGui::End();
        //ImGui::SFML::Render( *window );  // -----> renders ImGui elements
        //window->display();   // -----------------> display rendered elements to window 
}