#include "StateMachine.h"

bool State::IsTransitionRequested()
{
    return m_transitionIsRequested;
}
