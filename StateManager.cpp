//
// Created by Keen on 25.01.2021.
//

#include "StateManager.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "Logger.hpp"
#include "Window.hpp"

#include <algorithm>
#include <sstream>

StateManager::StateManager()
: m_states (), m_state_factory(), m_to_delete_states(), m_shared_context(nullptr){
    register_state<MenuState>(StateType::Menu);
    register_state<GameState>(StateType::Game);
}

StateManager::~StateManager() {
    for(auto& state : m_states){
        state.second->destroy();
    }
}

void StateManager::set_shared_context(SharedContext* l_shared_context) {
    m_shared_context = l_shared_context;
}


void StateManager::switch_to(StateType l_stateType) {
    m_shared_context->m_eventManager->set_state(l_stateType);
    // check first if state already exists. If not, create a new state
    for(auto i = 0; i < m_states.size(); ++i){
        if(m_states[i].first == l_stateType){
            m_states.back().second->deActivate();
            auto temp_state = std::move(m_states[i].second);
            m_states.erase(m_states.begin() + i);
            m_states.emplace_back(l_stateType, std::move(temp_state));
            m_states.back().second->activate();
            return;
        }
    }
    if(create(l_stateType)) {
        m_states.back().second->activate();
    }
}

void StateManager::remove(StateType l_stateType) {
    // only if requested state is existing and not marked for deletion,
    // add it to the "to-be-deleted"-states
    if(has_state(l_stateType)){
        m_to_delete_states.emplace_back(l_stateType);
    }
}

bool StateManager::create(StateType l_stateType) {
    auto found = m_state_factory.find(l_stateType);
    if(found == m_state_factory.end()){
        std::stringstream ss;
        ss << "ERROR in StateManager::create: could not find registered stateType-template for statetype "
        << int(l_stateType)  << " in m_state_factory";
        Logger::get_instance().log(ss.str());
        return false;
    }

    auto state = found->second();
    state->onCreate();
    m_states.emplace_back(l_stateType, std::move(state));
    return true;
}

void StateManager::erase(StateType l_stateType) {
    auto found_state = std::find_if(m_states.begin(), m_states.end(), [l_stateType](std::pair<StateType, std::unique_ptr<BaseState>>& pair){
        return pair.first == l_stateType;
    });
    if(found_state != m_states.end()){
        found_state->second->destroy();
        m_states.erase(found_state);
    }
}

bool StateManager::has_state(StateType l_stateType) {
    // treat immediately-to-be-deleted states as non-existing
    auto to_erase = std::find(m_to_delete_states.begin(), m_to_delete_states.end(), l_stateType);
    if (to_erase != m_to_delete_states.end()){
        return false;
    }
    auto found_state = std::find_if(m_states.begin(), m_states.end(), [l_stateType](std::pair<StateType, std::unique_ptr<BaseState>>& pair){
        return pair.first == l_stateType;
    });
    return found_state != m_states.end();
}

void StateManager::process_removals() {
    while(m_to_delete_states.begin() != m_to_delete_states.end()){
        erase(*m_to_delete_states.begin());
        m_to_delete_states.erase(m_to_delete_states.begin());
    }
}

void StateManager::update(const float &l_dt) {
    if(m_states.empty()) { return; }
    if(m_states.size() > 1 && m_states.back().second->is_transcendent()){
        auto traverser = m_states.end();
        while(traverser != m_states.begin()){
            traverser--;
            if(!traverser->second->is_transcendent()){
                break;
            }
        }
        for( ; traverser != m_states.end(); ++traverser){
            traverser->second->update(l_dt);
        }
    }
    else{
        m_states.back().second->update(l_dt);
    }
}

void StateManager::draw() {
    if(m_states.empty()) { return; }
    if(m_states.size() > 1 && m_states.back().second->is_transparent()){
        auto traverser = m_states.end();
        while(traverser != m_states.begin()){
            traverser--;
            if(!traverser->second->is_transparent()){
                break;
            }
        }
        for( ; traverser != m_states.end(); ++traverser){
            m_shared_context->m_window->get_renderWindow()->setView(traverser->second->get_view());
            traverser->second->draw();
        }
    }
    else{
        m_shared_context->m_window->get_renderWindow()->setView(m_states.back().second->get_view());
        m_states.back().second->draw();
    }
}