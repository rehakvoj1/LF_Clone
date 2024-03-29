#pragma once
#include "Window.h"

#include <SFML/Graphics.hpp>

#include <string>

class WindowsWindow : public Window
{
public:
	WindowsWindow( unsigned int width, unsigned int height, std::string name );

	virtual bool Init() override;

	virtual unsigned int							GetWidth() override;
	virtual unsigned int							GetHeight() override;
	virtual std::pair<unsigned int, unsigned int>	GetWindowSize() override;
	virtual void*									GetNativeWindow() const override;
	virtual bool									IsWindowOpen() override;

	virtual void									SetWidth( unsigned int width ) override;
	virtual void									SetHeight( unsigned int Height ) override;
	virtual void									SetWindowSize( std::pair<unsigned int, unsigned int> size ) override;


private:
	sf::RenderWindow m_window;
};

