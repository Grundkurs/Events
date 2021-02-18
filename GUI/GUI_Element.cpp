//
// Created by Keen on 30.01.2021.
//

#include "GUI_Element.hpp"

std::stringstream& operator >> (std::stringstream& l_ss, GUI_Element* l_gui_element){
    l_gui_element->readLine(l_ss);
    return l_ss;
}

GUI_Element::GUI_Element(const std::string& l_name, GUI_ElementType l_elementType, GUI_Interface* l_owner)
:   m_visual(), m_name(l_name), m_position(), m_styles(), m_element_type(l_elementType),
    m_currentState(GUI_ElementState::Neutral), m_owner(l_owner), m_needs_redraw(false),
    m_active(true), m_is_control(false){

}
