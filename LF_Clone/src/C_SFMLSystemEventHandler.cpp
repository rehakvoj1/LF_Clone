#include "C_SFMLSystemEventHandler.h"
#include "C_Engine.h"
#include "I_WindowsManager.h"
#include "Event.h"

#include "imgui-SFML.h"

#include <SFML/Window/Event.hpp>

#include <iostream>

// =================================================================================
void C_SFMLSystemEventHandler::PollEvents()
{
    sf::RenderWindow* window = static_cast<sf::RenderWindow*>( C_Engine::GetWindowsManager()->GetActiveWindow()->GetNativeWindow() );
    sf::Event event;
    while ( window->pollEvent( event ) )
    {
        ImGui::SFML::ProcessEvent( *window, event );

        switch ( event.type )
        {
            case sf::Event::Closed:
            {
                WindowClosedEvent closedEvent;
                auto windowClosedCallbacks = m_callbacks.equal_range( typeid( WindowClosedEvent ) );
                for ( auto it = windowClosedCallbacks.first; it != windowClosedCallbacks.second; ++it )
                {
                    it->second.second->Exec( closedEvent, it->second.first );
                }
            }
                break;
            case sf::Event::Resized:
            {
                WindowResizedEvent resizedEvent( event.size.width, event.size.height );
                auto windowResizedCallbacks = m_callbacks.equal_range( typeid( WindowResizedEvent ) );
                for ( auto it = windowResizedCallbacks.first; it != windowResizedCallbacks.second; ++it )
                {
                    it->second.second->Exec( resizedEvent, it->second.first );
                }
            }
                break;
            case sf::Event::GainedFocus:
            {

            }
                break;
            case sf::Event::LostFocus:
            {

            }
                break;
            case sf::Event::JoystickButtonPressed:
            {

            }
                break;
            case sf::Event::JoystickButtonReleased:
            {

            }
                break;
            case sf::Event::JoystickConnected:
            {

            }
                break;
            case sf::Event::JoystickDisconnected:
            {

            }
                break;
            case sf::Event::JoystickMoved:
            {

            }
                break;
            case sf::Event::KeyPressed:
            {
                bool shift = event.key.shift;
                bool control = event.key.control;
                bool alt = event.key.alt;
                KeyPressedEvent::KeyModifier keyMod = static_cast<KeyPressedEvent::KeyModifier>( ( alt << 2 ) | ( shift << 1 ) | ( control ) );
                KeyPressedEvent keyPressed( keyMod, event.key.code );
                auto keyPressedCallbacks = m_callbacks.equal_range( typeid( KeyPressedEvent ) );
                for ( auto it = keyPressedCallbacks.first; it != keyPressedCallbacks.second; ++it )
                {
                    it->second.second->Exec( keyPressed, it->second.first );
                }
            }
                break;
            case sf::Event::KeyReleased:
            {
                KeyReleasedEvent keyReleased( event.key.code );
                auto keyReleasedCallbacks = m_callbacks.equal_range( typeid( KeyReleasedEvent ) );
                for ( auto it = keyReleasedCallbacks.first; it != keyReleasedCallbacks.second; ++it )
                {
                    it->second.second->Exec( keyReleased, it->second.first );
                }
            }
                break;
            case sf::Event::MouseButtonPressed:
            {

            }
                break;
            case sf::Event::MouseButtonReleased:
            {

            }
                break;
            case sf::Event::MouseEntered:
            {

            }
                break;
            case sf::Event::MouseLeft:
            {

            }
                break;
            case sf::Event::MouseMoved:
            {

            }
                break;
            case sf::Event::MouseWheelScrolled:
            {

            }
                break;
            case sf::Event::TouchBegan:
            case sf::Event::TouchEnded:
            case sf::Event::TouchMoved:
            case sf::Event::SensorChanged:
            {
                std::cout << "Unsupported events." << std::endl;
            }
                break;
        }
        
    }
}
