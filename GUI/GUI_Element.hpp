//
// Created by Keen on 30.01.2021.
//

#ifndef EVENTS_GUI_ELEMENT_HPP
#define EVENTS_GUI_ELEMENT_HPP

#include "GUI_Style.hpp"
#include <SFML/System/Vector2.hpp>
#include <string>
#include <unordered_map>
class GUI_Interface;

enum class GUI_ElementType{
    Window, Label, Scrollbar, Textfield, Button,
};

using GUI_Styles = std::unordered_map<GUI_ElementState, GUI_Style>;

class GUI_Element {
public:
    GUI_Element(const std::string& l_name, GUI_ElementType l_elementType, GUI_Interface* l_owner);
private:
    GUI_Visual              m_visual;
    std::string             m_name;
    sf::Vector2f            m_position;
    GUI_Styles              m_styles;
    GUI_ElementType         m_type;
    GUI_ElementState        m_currentState;
    GUI_Interface*          m_owner;
    bool                    m_needs_redraw;
    bool                    m_active;
    bool                    m_is_control;
};


#endif //EVENTS_GUI_ELEMENT_HPP
