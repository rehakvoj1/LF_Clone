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
}