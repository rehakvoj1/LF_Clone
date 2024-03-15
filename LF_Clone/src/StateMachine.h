#pragma once
#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <string>
#include <type_traits>
#include <cassert>


//===================================================================================================
class State
{
public:
    virtual void OnEnter() { }
    virtual void OnExit() { }
    virtual void OnUpdate() { }
    bool IsTransitionRequested();

protected:
    bool m_transitionIsRequested = false;
private:

};

//===================================================================================================
template <typename DefaultStateType, typename StatesEnum>
class StateMachine
{
public:
    template <typename... Args>
    inline StateMachine( StatesEnum e_defaultState, Args&&... args );

    ~StateMachine();

    template <typename StateType, typename StateEnum, typename... Args>
    inline void AddState( StateEnum e_state, Args&&... args );

    
    

    void AddTransition( StatesEnum from, StatesEnum to );
    StatesEnum GetCurrentState();
    State* GetCurrentStateInstance();
    bool IsInState( StatesEnum e_state );
    void OnUpdate();
    
private:
    
    void SwitchState();

    std::unordered_map<StatesEnum, State*> m_states;
    std::unordered_map<StatesEnum, StatesEnum> m_transitions;
    StatesEnum m_currentState;

};

#include "StateMachine.inl"