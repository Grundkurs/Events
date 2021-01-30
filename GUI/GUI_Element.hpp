//
// Created by Keen on 30.01.2021.
//

#ifndef EVENTS_GUI_ELEMENT_HPP
#define EVENTS_GUI_ELEMENT_HPP

#include <string>

class GUI_Interface;

enum class GUI_ElementType{
    Window, Label, Scrollbar, Textfield, Button,
};

class GUI_Element {
public:
    GUI_Element(const std::string& l_name, GUI_ElementType l_elementType, GUI_Interface* l_owner);
private:
};


#endif //EVENTS_GUI_ELEMENT_HPP
