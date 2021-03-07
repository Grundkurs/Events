//
// Created by Keen on 30.01.2021.
//

#include "../Logger.hpp"
#include "../Utils.hpp"
#include "GUI_Interface.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <sstream>
GUI_Interface::GUI_Interface(const std::string &l_name, GUI_Manager* l_gui_manager)
: GUI_Element(l_name, GUI_ElementType::Window, this), m_gui_manager(l_gui_manager) {
    Logger::get_instance().log("created Interface " + l_name);
}

void GUI_Interface::readLine(std::stringstream& l_ss) {
    std::string movable;
    std::string is_title_shown;
    std::string title;
    //TODO: SFML-Book Loads coordinates into m_elementPadding.x, here its loaded into m_position; Maybe change later!
    l_ss >> m_position.x >> m_position.y >> movable >> is_title_shown;
    Utils::retrieve_quoted_text(l_ss, title);

    if(movable == "Movable"){
        m_is_movable = true;
    }
    if(is_title_shown == "Title"){
        m_show_title_bar = true;
    }

}

void GUI_Interface::draw(sf::RenderWindow* l_renderWindow) {



    if(!m_show_title_bar){ return; }

    std::cout << "draw title\n";
    l_renderWindow->draw(m_title_bar);

}

void GUI_Interface::reDraw() {



    set_redraw(false);
}
