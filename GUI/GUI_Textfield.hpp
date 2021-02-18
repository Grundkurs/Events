//
// Created by Keen on 30.01.2021.
//

#ifndef EVENTS_GUI_TEXTFIELD_HPP
#define EVENTS_GUI_TEXTFIELD_HPP


#include "GUI_Element.hpp"

class GUI_Textfield : public GUI_Element{
public:
    GUI_Textfield(const std::string& l_name, GUI_Interface* l_owner);
private:
    void readLine(std::stringstream &l_ss) override;
};


#endif //EVENTS_GUI_TEXTFIELD_HPP
