//
// Created by Keen on 25.01.2021.
//

#ifndef EVENTS_EVENTMANAGER_HPP
#define EVENTS_EVENTMANAGER_HPP

#include "StateManager.hpp"
#include "GUI/GuiEvent.hpp"
#include "Logger.hpp"
#include <SFML/Window/Event.hpp>
#include <functional>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <variant>

enum class Event{
    Closed              = sf::Event::Closed,                 ///< The window requested to be closed (no data)
    Resized             = sf::Event::Resized,                ///< The window was resized (data in event.size)
    Lost_Focus          = sf::Event::LostFocus,              ///< The window lost the focus (no data)
    Gained_Focus        = sf::Event::GainedFocus,            ///< The window gained the focus (no data)
    Text_Entered        = sf::Event::TextEntered,            ///< A character was entered (data in event.text)
    Key_Pressed         = sf::Event::KeyPressed,             ///< A key was pressed (data in event.key)
    Key_Released        = sf::Event::KeyReleased,            ///< A key was released (data in event.key)
    M_Wheel_Moved       = sf::Event::MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
    M_Wheel_Scrolled    = sf::Event::MouseWheelScrolled,     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
    M_Button_Pressed    = sf::Event::MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
    M_Button_Released   = sf::Event::MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
    M_Moved             = sf::Event::MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
    M_Entered           = sf::Event::MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
    M_Left              = sf::Event::MouseLeft,              ///< The mouse cursor left the area of the window (no data)
    J_Button_Pressed    = sf::Event::JoystickButtonPressed,  ///< A joystick button was pressed (data in event.joystickButton)
    J_Button_Released   = sf::Event::JoystickButtonReleased, ///< A joystick button was released (data in event.joystickButton)
    J_Moved             = sf::Event::JoystickMoved,          ///< The joystick moved along an axis (data in event.joystickMove)
    J_Connected         = sf::Event::JoystickConnected,      ///< A joystick was connected (data in event.joystickConnect)
    J_Disconnected      = sf::Event::JoystickDisconnected,   ///< A joystick was disconnected (data in event.joystickConnect)
    Realtime_Keyboard   = sf::Event::Count + 1,
    Realtime_Mouse,
    Realtime_Joystick,
    GUI_Clicked, GUI_Released, GUI_Hovered, GUI_Leave
};

struct EventInfo{
    EventInfo(int l_code = 0);
    EventInfo(const GUI_Event& l_event);
    std::variant<int, GUI_Event>    m_info;
};
struct EventDetails{
    explicit EventDetails(const std::string& l_name);
    void clear();

    std::string         m_name;
    sf::Vector2i        m_mouse_position;
    sf::Vector2u        m_size;
    int                 m_key_code;
    sf::Uint32          m_text_entered; // stores UTF-32 Unicode value of the character
};

struct Binding{
    explicit Binding(const std::string& l_name);
    std::vector<std::pair<Event, EventInfo>> m_events;
    EventDetails    m_details;
    // TODO: delete m_name? it may be superfluous since its stored in m_details anyway
    std::string     m_name;
    int             m_count;
};
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;
using Bindings = std::unordered_map<std::string, std::unique_ptr<Binding>>;
class EventManager {
public:
    EventManager();
    template<typename T>
    void add_callback(StateType l_stateType,
                      const std::string& l_callback_name,
                      void (T::*func)(EventDetails*),
                      T* l_instance) {
        auto func_binding = std::bind(func, l_instance, std::placeholders::_1);
        if(!m_callbacks[l_stateType].emplace(l_callback_name, func_binding).second){
            std::stringstream ss{};
            ss << "ERROR in EventManager::add_callback: Could not add callback with name: " << l_callback_name;
            Logger::get_instance().log(ss.str());
        }
    }
    void remove_callback(StateType l_stateType, const std::string& l_callback_name);
    void update();
    void handle_events(const sf::Event& l_event);
    void handle_events(const GUI_Event& l_event);

    void set_state(StateType l_stateType);
private:
    void                    load_bindings();
    Callbacks               m_callbacks;
    Bindings                m_bindings;
    StateType               m_currentState;
};


#endif //EVENTS_EVENTMANAGER_HPP
