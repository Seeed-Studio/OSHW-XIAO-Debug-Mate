#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "State.h"

#define MAX_STATES 20  // Maximum number of states

class StateManager {
private:
    static StateManager* s_instance;
    State* m_states[MAX_STATES];  // Array of state pointers

    // Private constructor for singleton pattern
    StateManager();
    
public:
    ~StateManager();

    // Get singleton instance
    static StateManager* getInstance();

    // Release singleton instance
    static void releaseInstance();

    // Register a state
    bool registerState(State* state);

    // Get a state by ID
    State* getState(int stateId) const;

    // Count of registered states
    int getStateCount() const;
};

#endif // STATE_MANAGER_H
