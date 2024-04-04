#include "WindowsWindow.h"

#include "imgui-SFML.h"

#include <iostream>

//===================================================================================================
WindowsWindow::WindowsWindow( unsigned int width, unsigned int height, std::string name )
{
	m_window.create( sf::VideoMode( width, height ), name );
}

//===================================================================================================
bool WindowsWindow::Init()
{
	if ( !m_window.isOpen() )
	{
		std::cout << "Failed to open the window." << std::endl;
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
unsigned int WindowsWindow::GetWidth()
{
	return m_window.getSize().x;
}

//===================================================================================================
unsigned int WindowsWindow::GetHeight()
{
	return m_window.getSize().y;
}

//===================================================================================================
std::pair<unsigned int, unsigned int> WindowsWindow::GetWindowSize()
{
	sf::Vector2u windowSize = m_window.getSize();
	return { windowSize.x,windowSize.y };
}

//===================================================================================================
void* WindowsWindow::GetNativeWindow() const
{
	return (void*) &m_window;
}

//===================================================================================================
void WindowsWindow::SetWidth( unsigned int width )
{
	sf::Vector2u windowSize = m_window.getSize();
	m_window.setSize( { width,windowSize.y } );
}

//===================================================================================================
void WindowsWindow::SetHeight( unsigned int height )
{
	sf::Vector2u windowSize = m_window.getSize();
	m_window.setSize( { windowSize.x,height } );
}

//===================================================================================================
void WindowsWindow::SetWindowSize( std::pair<unsigned int, unsigned int> size )
{
	m_window.setSize( { size.first, size.second } );
}

//===================================================================================================
bool WindowsWindow::IsWindowOpen()
{
	return m_window.isOpen();
}

//===================================================================================================
void WindowsWindow::Close()
{
	m_window.close();
}

//===================================================================================================
void WindowsWindow::Display()
{
	m_window.display();
}

//===================================================================================================
void WindowsWindow::ClearColor( uint8_t r, uint8_t g, uint8_t b )
{
	m_window.clear( { r,g,b } );
}
