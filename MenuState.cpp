//
// Created by Keen on 26.01.2021.
//

#include "MenuState.hpp"
#include "Logger.hpp"
#include "StateManager.hpp"
#include "Window.hpp"

MenuState::MenuState(StateManager *l_stateManager)
: BaseState(l_stateManager) {
    Logger::get_instance().log("MenuState::MenuState");
}

void MenuState::onCreate() {
    Logger::get_instance().log("MenuState::onCreate");
}

void MenuState::activate() {
    Logger::get_instance().log("MenuState::activate");
}

void MenuState::deActivate() {
    Logger::get_instance().log("MenuState::deActivate");
}

void MenuState::destroy() {
    Logger::get_instance().log("MenuState::destroy");
}

void MenuState::update(const float &l_dt) {

}

void MenuState::draw() {
    m_stateManager->get_shared_context()->m_window->clear(sf::Color::Red);
}
