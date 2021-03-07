//
// Created by Keen on 30.01.2021.
//

#ifndef EVENTS_GUI_ELEMENT_HPP
#define EVENTS_GUI_ELEMENT_HPP

#include "GUI_Style.hpp"
#include <SFML/System/Vector2.hpp>
#include <string>
#include <unordered_map>
namespace sf{
    class RenderWindow;
}
class GUI_Interface;

enum class GUI_ElementType{
    Window, Label, Scrollbar, Textfield, Button,
};

using GUI_Styles = std::unordered_map<GUI_ElementState, GUI_Style>;

class GUI_Element {
public:
    GUI_Element(const std::string& l_name, GUI_ElementType l_elementType, GUI_Interface* l_owner);
    // free function; defined in GUI_Element.cpp; needs to be declared here as friend so it can access local readLine-Method
    friend std::stringstream& operator >> (std::stringstream& l_ss, GUI_Element* l_gui_element);
    void set_elementState(GUI_ElementState l_elementState);
    void set_redraw(bool l_value);
    GUI_ElementState get_elementState() const;
    bool needs_redraw() const;
    virtual void draw(sf::RenderWindow* l_renderWindow) = 0;

protected:

    GUI_Visual              m_visual;
    std::string             m_name;
    sf::Vector2f            m_position;
    GUI_Styles              m_styles;
    GUI_ElementType         m_element_type;
    GUI_ElementState        m_currentState;
    GUI_Interface*          m_owner;

    bool                    m_needs_redraw;
    bool                    m_active;
    bool                    m_is_control;

private:
    virtual void readLine(std::stringstream& l_ss) = 0;

};


#endif //EVENTS_GUI_ELEMENT_HPP
