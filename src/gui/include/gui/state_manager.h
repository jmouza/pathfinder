#pragma once

#include "constants.h"
#include "ui_elements_observers.h"

#include <unordered_map>
#include <unordered_set>

enum class State {
    Idle,     
    Running,
    Paused,
    Finished
};

using BUTTON_ENABLED_STATES_TYPE = std::unordered_map<State, std::unordered_set<std::string>>;
/* For each state, the button (name) that should be enabled. */
static const BUTTON_ENABLED_STATES_TYPE BUTTON_ENABLED_STATES_TABLE = {
    {State::Idle, {START_BUTTON_STRING, RESET_BUTTON_STRING, CLEAR_BUTTON_STRING, FINERGRID_BUTTON_STRING, COARSERGRID_BUTTON_STRING, HELP_BUTTON_STRING}},
    {State::Running, {PAUSE_BUTTON_STRING, RESET_BUTTON_STRING, CLEAR_BUTTON_STRING, HELP_BUTTON_STRING}},
    {State::Paused, {START_BUTTON_STRING, RESET_BUTTON_STRING, CLEAR_BUTTON_STRING, PREVIOUS_BUTTON_STRING, NEXT_BUTTON_STRING, FORWARD_BUTTON_STRING, BACKWARD_BUTTON_STRING, HELP_BUTTON_STRING}},
    {State::Finished, {RESET_BUTTON_STRING, CLEAR_BUTTON_STRING, PREVIOUS_BUTTON_STRING, BACKWARD_BUTTON_STRING, HELP_BUTTON_STRING}}
};

class StateManager: 
    public IStartButtonObserver, 
    public IPauseButtonObserver, 
    public IResetButtonObserver,
    public IClearButtonObserver,
    public INextButtonObserver,
    public IPreviousButtonObserver,
    public IForwardButtonObserver,
    public IBackwardButtonObserver
{
private:
    enum State current_state;

    /* For each state, the allowed next state */
    const std::unordered_map<State, std::unordered_set<State>> STATE_TRANSITIONS = {
        {State::Idle, {State::Running}},
        {State::Running, {State::Idle, State::Paused, State::Finished}},
        {State::Paused, {State::Paused, State::Idle, State::Running, State::Finished}}, 
        {State::Finished, {State::Idle, State::Paused, State::Running}}
    };

    bool TransitionToStateIsEnabled(State target_state);
    
public:
    void ChangeState(State target_state);
    State GetCurrentState() const {return current_state;}
    void NotifyStartButton() override {ChangeState(State::Running);}
    void NotifyPauseButton() override {ChangeState(State::Paused);}
    void NotifyResetButton() override {ChangeState(State::Idle);}
    void NotifyClearButton() override {ChangeState(State::Idle);}
    void NotifyNextButton() override {ChangeState(State::Paused);}
    void NotifyPreviousButton() override {ChangeState(State::Paused);}
    void NotifyForwardButton() override {ChangeState(State::Finished);}
    void NotifyBackwardButton() override {ChangeState(State::Paused);}
};