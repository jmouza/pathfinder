#include "gui/state_manager.h"

bool StateManager::TransitionToStateIsEnabled(State target_state) {
    auto possible_next_states = STATE_TRANSITIONS.find(current_state)->second;

    return possible_next_states.count(target_state) != 0;
}

void StateManager::ChangeState(State target_state) {
    if (TransitionToStateIsEnabled(target_state)) {
        current_state = target_state;
    }
}