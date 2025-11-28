#ifndef EVENT_H
#define EVENT_H

// 事件类型枚举
enum EventType {
    EVENT_NONE = 0,
    EVENT_WHEEL_CLOCKWISE,       // 滚轮顺时针旋转
    EVENT_WHEEL_COUNTERCLOCKWISE, // 滚轮逆时针旋转
    EVENT_BUTTON_PRESS,          // 按钮按下
    EVENT_BUTTON_RELEASE,        // 按钮释放
    EVENT_BUTTON_LONGPRESS,      // 按钮长按
    EVENT_TOUCH_PRESS,           // 触摸屏按下
    EVENT_TOUCH_RELEASE,         // 触摸屏释放
    EVENT_TOUCH_MOVE,            // 触摸屏移动
    EVENT_TIMER,                 // 定时器事件
    EVENT_ERROR,                 // 错误事件
    EVENT_DISPLAY_DONE           // 显示更新完成
    // 可扩展更多事件类型
};

// 基本事件类
class Event {
private:
    EventType m_type;
    unsigned long m_timestamp;

public:
    Event(EventType type) : 
        m_type(type), 
        m_timestamp(0) // 实际应使用FreeRTOS的xTaskGetTickCount()
    {}
    
    virtual ~Event() {}
    
    EventType getType() const { return m_type; }
    unsigned long getTimestamp() const { return m_timestamp; }
};

// 滚轮事件
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

// 按钮事件
class ButtonEvent : public Event {
private:
    int m_buttonId;
    
public:
    ButtonEvent(EventType type, int buttonId) 
        : Event(type), m_buttonId(buttonId) {}
    
    int getButtonId() const { return m_buttonId; }
};

#endif // EVENT_H
