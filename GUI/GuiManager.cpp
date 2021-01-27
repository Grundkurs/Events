//
// Created by Keen on 25.01.2021.
//

#include "GuiManager.hpp"

GUI_Manager::GUI_Manager()
: m_gui_events(), m_current_state(StateType::Global), m_shared_context(nullptr){}

bool GUI_Manager::poll_GUI_event(GUI_Event& l_gui_event) {
    if(m_gui_events.empty()) { return false; }

    l_gui_event = m_gui_events[m_current_state].front();
    m_gui_events[m_current_state].pop();
    return true;
}

void GUI_Manager::add_event(GUI_Event l_gui_event) {
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
