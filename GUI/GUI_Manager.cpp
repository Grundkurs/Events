//
// Created by Keen on 25.01.2021.
//

#include "GUI_Manager.hpp"
#include "GUI_Button.hpp"
#include "GUI_Label.hpp"
#include "GUI_Scrollbar.hpp"
#include "GUI_Textfield.hpp"
#include "../Utils.hpp"
GUI_Manager::GUI_Manager()
// as long as StateManager does not register a local state, the default state of GUI_Manager is Global
: m_gui_events(), m_interfaces(), m_gui_factory(), m_element_types(),
m_current_state(StateType::Global), m_shared_context(nullptr){

    register_gui_element<GUI_Button>(GUI_ElementType::Button);
    register_gui_element<GUI_Label>(GUI_ElementType::Label);
    register_gui_element<GUI_Scrollbar>(GUI_ElementType::Scrollbar);
    register_gui_element<GUI_Textfield>(GUI_ElementType::Textfield);

    m_element_types["Label"] = GUI_ElementType::Label;
    m_element_types["Button"] = GUI_ElementType::Button;
    m_element_types["Scrollbar"] = GUI_ElementType::Scrollbar;
    m_element_types["Textfield"] = GUI_ElementType::Textfield;
}

void GUI_Manager::add_event(const GUI_Event& l_gui_event) {
    m_gui_events[m_current_state].push(l_gui_event);
}

void GUI_Manager::set_shared_context(SharedContext* l_shared_context) {
    m_shared_context = l_shared_context;
}

void GUI_Manager::set_state(StateType l_stateType) {
    m_current_state = l_stateType;
}

void GUI_Manager::update(const float &l_dt) {

}

void GUI_Manager::draw() {

}

void GUI_Manager::load_interface_from_file(StateType l_stateType, const std::string &l_file_name,
                                           const std::string &l_interface_name) {
    std::string file_path = Utils::get_source_dir() + R"(\resources\???)" + l_file_name;
}
