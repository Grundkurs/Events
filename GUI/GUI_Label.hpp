//
// Created by Keen on 30.01.2021.
//

#ifndef EVENTS_GUI_LABEL_HPP
#define EVENTS_GUI_LABEL_HPP

#include "GUI_Element.hpp"

class GUI_Label : public GUI_Element{
public:
    GUI_Label(const std::string& l_name, GUI_Interface* l_owner);

    void draw(sf::RenderWindow *l_renderWindow) override;

private:
    void readLine(std::stringstream &l_ss) override;
};


#endif //EVENTS_GUI_LABEL_HPP
