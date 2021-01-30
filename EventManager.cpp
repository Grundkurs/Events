//
// Created by Keen on 25.01.2021.
//

#include "EventManager.hpp"
#include "Utils.hpp"

namespace {
    GUI_Event_Type convert_eventType_to_GUI_event_type(Event l_eventType){
        switch (l_eventType){
            case(Event::GUI_Clicked): { return GUI_Event_Type::Click;}
            case(Event::GUI_Hovered): { return GUI_Event_Type::Hover;}
            case(Event::GUI_Released): { return GUI_Event_Type::Release;}
            case(Event::GUI_Leave): { return GUI_Event_Type::Leave;}
            default: { return GUI_Event_Type::None; }
        }
    }
}

EventInfo::EventInfo(int l_code)
: m_info(l_code){

}

EventInfo::EventInfo(const GUI_Event &l_event)
: m_info(l_event){

}

EventDetails::EventDetails(const std::string& l_name)
: m_name(l_name){
    clear();
}

void EventDetails::clear() {
// don't clear name since its always needed and will never change
}

Binding::Binding(const std::string& l_name)
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
    for(auto& string_binding_pair : m_bindings){
        for(auto& event_eventInfo_pair : string_binding_pair.second->m_events){
            switch(event_eventInfo_pair.first){
                // we know that EventInfo::m_info cannot be an gui_event since current Event is of type
                // "Realtime_Keyboard", thus it safe to retrieve it by std::get<int>(...)
                case (Event::Realtime_Keyboard):{
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(std::get<int>(event_eventInfo_pair.second.m_info)))){
                        ++string_binding_pair.second->m_count;
                    }
                    break;
                }
                case (Event::Realtime_Mouse):{
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button(std::get<int>(event_eventInfo_pair.second.m_info)))){
                        ++string_binding_pair.second->m_count;
                    }
                    break;
                }
                case (Event::Realtime_Joystick):{ break; }
                default: { break; }
            }
        }
        // when all events of a binding have been triggered, activate matching callback
        if(string_binding_pair.second->m_count == string_binding_pair.second->m_events.size()){
            // check for global callbacks
            auto global_callback_container = m_callbacks.find(StateType::Global);
            if(global_callback_container != m_callbacks.end()){
                auto found_global_callback = global_callback_container->second.find(string_binding_pair.first);
                if(found_global_callback != global_callback_container->second.end()){
                    found_global_callback->second(&string_binding_pair.second->m_details);
                }
            }
            // check for local callbacks
            auto local_callback_container = m_callbacks.find(m_currentState);
            if(local_callback_container != m_callbacks.end()){
                auto found_local_callback = local_callback_container->second.find(string_binding_pair.first);
                if(found_local_callback != local_callback_container->second.end()){
                    found_local_callback->second(&string_binding_pair.second->m_details);
                }
            }
        }
        string_binding_pair.second->m_count = 0;
        string_binding_pair.second->m_details.clear();
    }
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
    std::string line{};
    while(std::getline(file, line)){
        if(line.empty()){ continue; }
        if(line[0] == '#'){ continue; }
        if(line[0] == '|'){ continue; }

        std::stringstream ss{ line };
        std::string bindingName{};
        ss >> bindingName;
        std::unique_ptr<Binding> binding = std::make_unique<Binding>(bindingName);
        std::string entry{};
        while (ss >> entry){
            std::size_t first_separator = entry.find_first_of(':');
            if(first_separator == std::string::npos){
                std::stringstream tempss{};
                tempss << "ERROR in EventManager::load_bindings: file " << file_path << " binding " << bindingName
                << " has an entry with no separator";
                Logger::get_instance().log(tempss.str());
                break; // exit inner while-loop, go to next line
            }
            int first_chunk = std::stoi(entry.substr(0,first_separator));
            Event event = Event(first_chunk);
            if( event == Event::GUI_Clicked || event == Event::GUI_Hovered ||
                event == Event::GUI_Leave   || event == Event::GUI_Released ){
                // there must be more than one separator in an entry (3 chunks), thus take care of another separator
                std::size_t second_separator = entry.find_first_of(':', first_separator + 1);
                if(second_separator == std::string::npos){
                    std::stringstream tempss{};
                    tempss << "ERROR in EventManager::load_bindings: file " << file_path << " binding " << bindingName
                           << " has only one separator but there should be two separators";
                    Logger::get_instance().log(tempss.str());
                    break; // exit inner while-loop, go to next line
                }
                std::string second_chunk = entry.substr(first_separator +1, (second_separator - (first_separator + 1)));
                std::string third_chunk = entry.substr(second_separator + 1, (entry.size() - second_separator +1));

                GUI_Event gui_event;
                gui_event.m_type = convert_eventType_to_GUI_event_type(event);
                gui_event.m_interface = second_chunk;
                gui_event.m_element = third_chunk;

                EventInfo event_info{gui_event};
                binding->m_events.emplace_back(event, event_info);
            }
            else{
                int secondChunk = std::stoi(entry.substr(first_separator + 1, (entry.size() - first_separator)));
                EventInfo event_info{ secondChunk };
                binding->m_events.emplace_back(event, event_info);
            }
        }
        //after all entries in a line have been processed and added to the binding, add binding to all bindings
        m_bindings.emplace(bindingName, std::move(binding));
    }
    file.close();
}
