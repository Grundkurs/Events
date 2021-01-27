//
// Created by Keen on 25.01.2021.
//

#ifndef EVENTS_GUIMANAGER_HPP
#define EVENTS_GUIMANAGER_HPP

#include "../StateManager.hpp"
#include "GuiEvent.hpp"
#include <unordered_map>
#include <queue>
using GUI_Events = std::unordered_map<StateType, std::queue<GUI_Event>>;
class GUI_Manager {
public:
    GUI_Manager();
    bool poll_GUI_event(GUI_Event& l_gui_event);
    void add_event(GUI_Event l_gui_event);
    void set_shared_context(SharedContext* l_shared_context);
    void set_state(StateType l_stateType);
    void update(const float& l_dt);
    void draw();
private:
    GUI_Events              m_gui_events;
    StateType               m_current_state;
    SharedContext*          m_shared_context;
};


#endif //EVENTS_GUIMANAGER_HPP
