//
// Created by Keen on 25.01.2021.
//

#include "EventManager.hpp"
#include "Utils.hpp"

EventInfo::EventInfo(int l_code)
: m_info(l_code){

}

EventInfo::EventInfo(const GUI_Event &l_event)
: m_info(l_event){

}

EventDetails::EventDetails(const std::string l_name)
: m_name(l_name){
    clear();
}

void EventDetails::clear() {
// don't clear name since its always needed and will never change
}

Binding::Binding(const std::string &l_name)
: m_events(), m_details(l_name), m_name(l_name), m_count(0){

}

EventManager::EventManager() {
    load_bindings();
}

void EventManager::remove_callback(StateType l_stateType, const std::string& l_callback_name) {
    auto foundContainer = m_callbacks.find(l_stateType);
    if(foundContainer == m_callbacks.end()){
        std::cout << "EventManager::remove_callback: Could not find global callback-container "
                     "for stateType with ID: " << int(l_stateType) << "\n";
        return;
    }
    auto foundCallback = foundContainer->second.find(l_callback_name);
    if(foundCallback == foundContainer->second.end()){
        std::cout << "EventManager::remove_callback: Could not find callback"
                     " with name: " << l_callback_name << "\n";
        return;
    }
    foundContainer->second.erase(foundCallback);
}


void EventManager::update() {

}

void EventManager::handle_events(const sf::Event &l_event) {

}

void EventManager::handle_events(const GUI_Event &l_event) {

}
void EventManager::set_state(StateType l_stateType) {
    m_currentState = l_stateType;
}

void EventManager::load_bindings() {
    std::string file_path = Utils::get_source_dir() + R"(\resources\config\keybindings.cfg)";
    std::ifstream file{file_path};
    if(!file.is_open()){
        Logger::get_instance().log("ERROR in EventManager::load_bindings: "
                                   "could not open " + file_path);
        return;
    }

    file.close();
}
