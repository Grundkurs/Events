//
// Created by Keen on 25.01.2021.
//

#ifndef EVENTS_GUI_MANAGER_HPP
#define EVENTS_GUI_MANAGER_HPP

#include "../StateManager.hpp"
#include "GUI_Event.hpp"
#include "GUI_Interface.hpp"
#include <unordered_map>
#include <queue>

using GUI_Events = std::unordered_map<StateType, std::queue<GUI_Event>>;
using InterfaceContainer = std::unordered_map<std::string, std::unique_ptr<GUI_Interface>>;
using Interfaces = std::unordered_map<StateType, InterfaceContainer>;
using GUI_Element_Factory = std::unordered_map<GUI_ElementType, std::function<std::unique_ptr<GUI_Element>(GUI_Interface*)>>;
using GUI_ElementTypes = std::unordered_map<std::string, GUI_ElementType>;

class GUI_Manager {
public:
    GUI_Manager();
    inline bool poll_GUI_event(GUI_Event& l_gui_event){
        if(m_gui_events[m_current_state].empty()) { return false; }

        l_gui_event = m_gui_events[m_current_state].front();
        m_gui_events[m_current_state].pop();
        return true;
    }
    inline SharedContext* get_shared_context() const { return m_shared_context; }

    template<typename T>
    void register_gui_element(GUI_ElementType l_gui_type);

    void add_event(const GUI_Event& l_gui_event);
    void set_shared_context(SharedContext* l_shared_context);
    void set_state(StateType l_stateType);
    void load_interface_from_file(StateType l_stateType, const std::string& l_file_name, const std::string& l_interface_name);

    void update(const float& l_dt);
    void draw();

private:
    GUI_Events              m_gui_events;
    Interfaces              m_interfaces;
    GUI_Element_Factory     m_gui_factory;
    GUI_ElementTypes        m_element_types;
    StateType               m_current_state;
    SharedContext*          m_shared_context;
};

template<typename T>
void GUI_Manager::register_gui_element(GUI_ElementType l_gui_type) {
    m_gui_factory[l_gui_type] = [](GUI_Interface* l_interface)->std::unique_ptr<GUI_Element>{
        return std::make_unique<T>("", l_interface);
    };
}

#endif //EVENTS_GUI_MANAGER_HPP
