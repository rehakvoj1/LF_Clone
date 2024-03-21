#pragma once
#include "I_WindowsManager.h"

#include <utility>

class C_WindowsWindowsManager : public I_WindowsManager
{
public:
	virtual std::pair<Window*, bool>	AddWindow( unsigned int width, unsigned int height, std::string name ) override;
	virtual bool						IsWindowOpen( const std::string windowName ) override;
private:
};

