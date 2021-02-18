//
// Created by Keen on 30.01.2021.
//

#ifndef EVENTS_GUI_SCROLLBAR_HPP
#define EVENTS_GUI_SCROLLBAR_HPP

#include "GUI_Element.hpp"

class GUI_Scrollbar : public GUI_Element{
public:
    GUI_Scrollbar(const std::string& l_name, GUI_Interface* l_owner);
private:
    void readLine(std::stringstream &l_ss) override;
};


#endif //EVENTS_GUI_SCROLLBAR_HPP
