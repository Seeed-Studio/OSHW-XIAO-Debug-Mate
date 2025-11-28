#ifndef ERRORSTATE_H
#define ERRORSTATE_H

#include "MenuStates.h"
#include "StateManager.h"

// Error state
class ErrorState : public State {
private:
    int m_errorCode;
    const char* m_errorMessage;

public:
    enum { ID = 0 };

    ErrorState();

    void setError(int code, const char* message);

    // Implement State interface
    virtual void onEnter();
    virtual bool handleEvent(StateMachine* machine, const Event* event);
    virtual void updateDisplay(DisplayContext* display);
    int getID() const override;
    const char* getName() const override;
};

#endif //ERRORSTATE_H
