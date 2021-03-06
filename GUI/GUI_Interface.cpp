//
// Created by Keen on 30.01.2021.
//

#include "GUI_Interface.hpp"

GUI_Interface::GUI_Interface(const std::string &l_name, GUI_Manager* l_gui_manager)
: GUI_Element(l_name, GUI_ElementType::Window, this) {

}

void GUI_Interface::readLine(std::stringstream &l_ss) {

}

void GUI_Interface::draw(sf::RenderWindow *l_renderWindow) {

}

void GUI_Interface::reDraw() {

}
