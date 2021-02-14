//
// Created by Keen on 26.01.2021.
//

#include "GameState.hpp"
#include "StateManager.hpp"
#include "Window.hpp"
#include "SharedContext.hpp"
#include "Logger.hpp"
#include "TextureManager.hpp"
#include "GUI/GUI_Manager.hpp"
GameState::GameState(StateManager *l_stateManager)
:   BaseState(l_stateManager) {
    Logger::get_instance().log("GameState::GameState");
}

void GameState::onCreate() {
    Logger::get_instance().log("GameState::onCreate");
    auto gui_manager = m_stateManager->get_shared_context()->m_gui_manager;
    gui_manager->load_interface_from_file(StateType::Game, "MainMenu.interface", "Main Menu");
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
}
