#include "C_WindowsWindowsManager.h"
#include "WindowsWindow.h"

//===================================================================================================
std::pair<Window*, bool> C_WindowsWindowsManager::AddWindow( unsigned int width, unsigned int height, std::string name )
{
	// TODO: if the key is already exists, it just return iterator -> Value is not overriden
	auto it = m_windows.emplace( name, new WindowsWindow( width, height, name ) );
	bool isInitSuccessful = it.first->second->Init();
	return { it.first->second,isInitSuccessful };
}

//===================================================================================================
bool C_WindowsWindowsManager::IsWindowOpen( const std::string windowName )
{
	return m_windows[windowName]->IsWindowOpen();
}
