#ifndef EVENT_H
#define EVENT_H

// Event type enumeration
enum EventType {
    EVENT_NONE = 0,
    EVENT_WHEEL_CLOCKWISE,       // Wheel rotated clockwise
    EVENT_WHEEL_COUNTERCLOCKWISE, // Wheel rotated counterclockwise
    EVENT_BUTTON_PRESS,          // Button pressed
    EVENT_BUTTON_RELEASE,        // Button released
    EVENT_BUTTON_LONGPRESS,      // Button long press
    EVENT_TOUCH_PRESS,           // Touch screen press
    EVENT_TOUCH_RELEASE,         // Touch screen release
    EVENT_TOUCH_MOVE,            // Touch screen move
    EVENT_TIMER,                 // Timer event
    EVENT_ERROR,                 // Error event
    EVENT_DISPLAY_DONE           // Display update complete
    // Extend with more event types if needed
};

// Base event class
class Event {
private:
    EventType m_type;
    unsigned long m_timestamp;

public:
    Event(EventType type) : 
        m_type(type), 
    m_timestamp(0) // Should actually use FreeRTOS xTaskGetTickCount()
    {}
    
    virtual ~Event() {}
    
    EventType getType() const { return m_type; }
    unsigned long getTimestamp() const { return m_timestamp; }
};

// Wheel event
class WheelEvent : public Event {
private:
    bool m_isClockwise;
    int m_steps;
    
public:
    WheelEvent(bool isClockwise, int steps = 1) 
        : Event(isClockwise ? EVENT_WHEEL_CLOCKWISE : EVENT_WHEEL_COUNTERCLOCKWISE),
          m_isClockwise(isClockwise),
          m_steps(steps) {}
    
    bool isClockwise() const { return m_isClockwise; }
    int getSteps() const { return m_steps; }
};

// Button event
class ButtonEvent : public Event {
private:
    int m_buttonId;
    
public:
    ButtonEvent(EventType type, int buttonId) 
        : Event(type), m_buttonId(buttonId) {}
    
    int getButtonId() const { return m_buttonId; }
};

#endif // EVENT_H
