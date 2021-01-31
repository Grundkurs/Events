//
// Created by Keen on 26.01.2021.
//

#include "GameState.hpp"
#include "StateManager.hpp"
#include "Window.hpp"
#include "SharedContext.hpp"
#include "Logger.hpp"
#include "TextureManager.hpp"
GameState::GameState(StateManager *l_stateManager)
:   BaseState(l_stateManager) {
    Logger::get_instance().log("GameState::GameState");
}

void GameState::onCreate() {
    Logger::get_instance().log("GameState::onCreate");
    m_sprite.setTexture(*m_stateManager->get_shared_context()->m_textureManager->get("ADOM_GUI_BACKGROUND"));
}

void GameState::activate() {
    Logger::get_instance().log("GameState::activate");
}

void GameState::deActivate() {
    Logger::get_instance().log("GameState::deActivate");
}

void GameState::destroy() {
    Logger::get_instance().log("GameState::destroy");
}

void GameState::update(const float &l_dt) {

}

void GameState::draw() {
    m_stateManager->get_shared_context()->m_window->get_renderWindow()->draw(m_sprite);
}
