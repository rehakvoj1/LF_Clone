#include "I_SystemEventHandler.h"
#include "C_SFMLSystemEventHandler.h"


// =================================================================================
I_SystemEventHandler* I_SystemEventHandler::Create()
{
#ifdef PLATFORM_WINDOWS
	return new C_SFMLSystemEventHandler;
#else
	std::cout << "Unknown platform for handling system events." << std::endl;
#endif // PLATFORM
}
