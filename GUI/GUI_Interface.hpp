//
// Created by Keen on 30.01.2021.
//

#ifndef EVENTS_GUI_INTERFACE_HPP
#define EVENTS_GUI_INTERFACE_HPP

#include "GUI_Element.hpp"
class GUI_Manager;

class GUI_Interface : public GUI_Element{
public:
    GUI_Interface(const std::string& l_name, GUI_Manager* l_gui_manager);
    void draw(sf::RenderWindow* l_renderWindow) override;
    void reDraw();
private:
    void readLine(std::stringstream &l_ss) override;
};


#endif //EVENTS_GUI_INTERFACE_HPP
