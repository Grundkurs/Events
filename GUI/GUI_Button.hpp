//
// Created by Keen on 30.01.2021.
//

#ifndef EVENTS_GUI_BUTTON_HPP
#define EVENTS_GUI_BUTTON_HPP

#include "GUI_Element.hpp"
class GUI_Button : public GUI_Element{
public:
    GUI_Button(const std::string& l_name, GUI_Interface* l_owner);

    void draw(sf::RenderWindow *l_renderWindow) override;
private:
    void readLine(std::stringstream &l_ss) override;
};


#endif //EVENTS_GUI_BUTTON_HPP
