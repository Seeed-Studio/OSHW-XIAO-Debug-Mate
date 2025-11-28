#ifndef STATE_H
#define STATE_H

#include "Event.h"
#include "DisplayContext.h"

class StateMachine;

// State interface
class State {
public:
    virtual ~State() {}
    
    // Called when entering this state
    virtual void onEnter() {}
    
    // Called when exiting this state
    virtual void onExit() {}
    
    // Handle incoming event
    virtual bool handleEvent(StateMachine* machine, const Event* event) = 0;
    
    // Update display contents
    virtual void updateDisplay(DisplayContext* display) = 0;
    
    // State ID
    virtual int getID() const = 0;
    
    // State name (for debugging)
    virtual const char* getName() const = 0;
};

#endif // STATE_H
