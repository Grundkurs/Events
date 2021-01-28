//
// Created by Keen on 25.01.2021.
//

#ifndef EVENTS_GUIEVENT_HPP
#define EVENTS_GUIEVENT_HPP

#include <SFML/System/Vector2.hpp>
#include <string>

enum class GUI_Event_Type{
    None, Click, Release, Hover, Leave
};
struct GUI_Event {
    GUI_Event_Type      m_type = GUI_Event_Type::None;
    std::string         m_interface{};
    std::string         m_element{};
    sf::Vector2i        m_click_coordinates{};
};


#endif //EVENTS_GUIEVENT_HPP
