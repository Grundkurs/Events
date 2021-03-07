//
// Created by Keen on 30.01.2021.
//

#include "GUI_Interface.hpp"
#include "../Logger.hpp"
#include <iostream>

GUI_Interface::GUI_Interface(const std::string &l_name, GUI_Manager* l_gui_manager)
: GUI_Element(l_name, GUI_ElementType::Window, this), m_gui_manager(l_gui_manager) {
    Logger::get_instance().log("created Interface " + l_name);
}

void GUI_Interface::readLine(std::stringstream &l_ss) {
    std::string movable;
    std::string is_title_shown;

    if(movable == "Movable"){
        m_is_movable = true;
    }
    if(is_title_shown == "Title"){
        m_is_title_shown = true;
    }

}

void GUI_Interface::draw(sf::RenderWindow *l_renderWindow) {

}

void GUI_Interface::reDraw() {



    set_redraw(false);
}
