//
// Created by Keen on 25.01.2021.
//

#include "GUI_Manager.hpp"
#include <iostream>
GUI_Manager::GUI_Manager()
// as long as StateManager does not register a local state, the default state of GUI_Manager is Global
: m_gui_events(), m_interfaces(), m_gui_factory(), m_element_types(),
m_current_state(StateType::Global), m_shared_context(nullptr){}

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