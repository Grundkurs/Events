//
// Created by Keen on 26.01.2021.
//

#include "GameState.hpp"
#include "StateManager.hpp"
#include "Window.hpp"
#include "Logger.hpp"

GameState::GameState(StateManager *l_stateManager)
:   BaseState(l_stateManager) {
    Logger::get_instance().log("GameState::GameState");
}

void GameState::onCreate() {
    Logger::get_instance().log("GameState::onCreate");
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
