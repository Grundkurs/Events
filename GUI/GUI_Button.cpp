//
// Created by Keen on 30.01.2021.
//

#include "GUI_Button.hpp"

GUI_Button::GUI_Button(const std::string& l_name, GUI_Interface* l_owner)
: GUI_Element(l_name, GUI_ElementType::Button, l_owner){
}

void GUI_Button::readLine(std::stringstream &l_ss) {

}

void GUI_Button::draw(sf::RenderWindow *l_renderWindow) {

}
