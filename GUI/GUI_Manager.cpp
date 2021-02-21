//
// Created by Keen on 25.01.2021.
//

#include <fstream>
#include <sstream>
#include "GUI_Manager.hpp"
#include "GUI_Button.hpp"
#include "GUI_Label.hpp"
#include "GUI_Scrollbar.hpp"
#include "GUI_Textfield.hpp"
#include "../Utils.hpp"
#include "../Logger.hpp"

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
    auto currentState_interfaceContainer_pair = m_interfaces.find(m_current_state);
    if(currentState_interfaceContainer_pair == m_interfaces.end()){
        return;
    }
    for(auto& string_inferface_pair : currentState_interfaceContainer_pair->second){
        GUI_Interface* interface = string_inferface_pair.second.get();
    }
}

void GUI_Manager::load_interface_from_file(StateType l_stateType, const std::string &l_file_name,
                                           const std::string &l_interface_name) {
    std::string file_path = Utils::get_source_dir() + R"(\resources\gui_interfaces\)" + l_file_name;
    std::ifstream file;
    file.open(file_path);
    if(!file.is_open()){
        Logger::get_instance().log("Error in GUI_Manager::load_interface_from_file: could not load file " + file_path);
        return;
    }
    std::string line{};
    std::string interface_name{};
    while(std::getline(file,line)){
        if(line.empty()) { continue; }
        if(line[0] =='|') { continue; }
        if(line[0] =='#') { continue; }

        std::stringstream ss{line};
        std::string entry{};
        ss >> entry;
        if(entry == "Interface"){
            std::string style{};
            ss >> interface_name >> style;

            GUI_Interface* interface = getInterface(l_stateType, interface_name);
            if(!load_style())
        }
        else if(entry == "Element"){
            if(interface_name.empty()){
                std::stringstream temp_ss;
                temp_ss << "WARNING in GUI_Manager::load_interface_from_file: trying to read "
                           "Element before Interface in file " << l_file_name;
                Logger::get_instance().log(temp_ss.str());
                continue;
            }
        }
    }
    file.close();
}

bool GUI_Manager::load_style(const std::string &l_style_name, GUI_Element *l_element) {
    return false;
}

void GUI_Manager::add_interface(const std::string &l_interface_name, StateType l_stateType) {

}

GUI_Interface* GUI_Manager::get_interface(const std::string &l_interface_name, StateType l_stateType) {
    return nullptr;
}
