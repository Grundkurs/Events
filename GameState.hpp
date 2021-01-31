//
// Created by Keen on 26.01.2021.
//

#ifndef EVENTS_GAMESTATE_HPP
#define EVENTS_GAMESTATE_HPP

#include "BaseState.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

#include <SFML/Graphics/Sprite.hpp>

class GameState : public BaseState{
public:
    GameState(StateManager* l_stateManager);
    void onCreate() override;
    void activate() override;
    void deActivate() override;
    void destroy() override;

    void update(const float &l_dt) override;
    void draw() override;

private:
    sf::Sprite m_sprite;
};


#endif //EVENTS_GAMESTATE_HPP
