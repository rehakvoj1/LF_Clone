#include "I_WindowsManager.h"
#include "C_WindowsWindowsManager.h"

#include <iostream>

//===================================================================================================
I_WindowsManager* I_WindowsManager::Create()
{
#ifdef PLATFORM_WINDOWS
	return new C_WindowsWindowsManager;
#else
	std::cout << "Unknown platform for managing windows." << std::endl;
#endif // PLATFORM

}

//===================================================================================================
bool I_WindowsManager::SetActiveWindow( const std::string& name )
{
	auto it = m_windows.find( name );
	if ( it == m_windows.end() )
	{
		return false;
	}
	
	m_activeWindow = name;
	return true;
}

//===================================================================================================
Window* I_WindowsManager::GetActiveWindow()
{
	return m_windows[m_activeWindow.data()];
}
