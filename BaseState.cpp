//
// Created by Keen on 26.01.2021.
//

#include "BaseState.hpp"
#include "StateManager.hpp"
#include "SharedContext.hpp"
#include "Window.hpp"
BaseState::BaseState(StateManager *l_stateManager)
:   m_view(l_stateManager->get_shared_context()->m_window->get_renderWindow()->getDefaultView()),
    m_stateManager(l_stateManager), m_is_transparent(false), m_is_transcendent(false){

}

