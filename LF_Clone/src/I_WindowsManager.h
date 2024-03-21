#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

#include "Window.h"

class I_WindowsManager
{
public:
	static I_WindowsManager* Create();

	virtual std::pair<Window*, bool>	AddWindow( unsigned int width, unsigned int height, std::string name ) = 0;
	virtual bool						IsWindowOpen( const std::string windowName ) = 0;

			bool						SetActiveWindow( const std::string& name );
			Window*						GetActiveWindow();
protected:
	std::unordered_map<std::string, Window*>	m_windows;
	std::string									m_activeWindow; // ID
};

