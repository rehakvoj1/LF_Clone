#include "StateMachine.h"
#pragma once

//================================================================================================
template <typename DefaultStateType, typename StatesEnum>
template <typename... Args>
inline StateMachine<DefaultStateType,StatesEnum>::StateMachine( StatesEnum e_defaultState, Args&&... args ) : m_currentState( e_defaultState )
{
    m_states.emplace( e_defaultState, new DefaultStateType( std::forward<Args>( args )... ) );
}

//================================================================================================
template <typename DefaultStateType, typename StatesEnum>
template <typename StateType, typename StateEnum, typename... Args>
inline void StateMachine<DefaultStateType, StatesEnum>::AddState( StateEnum e_state, Args&&... args )
{
    static_assert( std::is_same_v<decltype( e_state ), decltype( m_currentState )> == true );
    m_states.emplace( e_state, new StateType( std::forward<Args>( args )... ) );
}


//===================================================================================================
template<typename DefaultStateType, typename StatesEnum>
inline StateMachine<DefaultStateType, StatesEnum>::~StateMachine()
{
    for ( auto it = m_states.begin(); it != m_states.end(); ++it )
    {
        delete it->second;
    }
}

//================================================================================================
template <typename DefaultStateType, typename StatesEnum>
void StateMachine<DefaultStateType, StatesEnum>::AddTransition( StatesEnum from, StatesEnum to )
{
    m_transitions.emplace( from, to );
}
//================================================================================================
template <typename DefaultStateType, typename StatesEnum>
StatesEnum StateMachine<DefaultStateType, StatesEnum>::GetCurrentState()
{
    return m_currentState;
}

//================================================================================================
template <typename DefaultStateType, typename StatesEnum>
State* StateMachine<DefaultStateType, StatesEnum>::GetCurrentStateInstance()
{
    return m_states[m_currentState];
}

//================================================================================================
template <typename DefaultStateType, typename StatesEnum>
bool StateMachine<DefaultStateType, StatesEnum>::IsInState( StatesEnum e_state )
{
    return ( e_state == m_currentState );
}

//================================================================================================
template <typename DefaultStateType, typename StatesEnum>
void StateMachine<DefaultStateType, StatesEnum>::OnUpdate()
{
    if ( m_states[m_currentState]->IsTransitionRequested() )
    {
        SwitchState();
    }
    m_states[m_currentState]->OnUpdate();

}

//================================================================================================
template <typename DefaultStateType, typename StatesEnum>
void StateMachine<DefaultStateType, StatesEnum>::SwitchState()
{
    m_states[m_currentState]->OnExit();
    m_currentState = m_transitions[m_currentState];
    m_states[m_currentState]->OnEnter();
}